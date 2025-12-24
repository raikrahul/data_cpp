// 74_variant_interface_development.cpp
//
// TASK: Analyze Variance (Templates/Variant) vs Tag-Dispatch (Runtime Switch)
// SCENARIO: Finite Difference Stencils (Order 3..7) on 1024x1024 Grid
//
// MEMORY LAYOUT WORKSHEET & AXIOMATIC DERIVATION
// NO SOLUTIONS - ALL BOILERPLATE - FILL CALCULATIONS BY HAND
//
// ------------------------------------------------------------------------------------------
// 01. STACK START: main() variables
// ------------------------------------------------------------------------------------------
// Draw Stack Frame:
// [ 0x7fffffffe000 ] nodes (std::vector<StencilVariant>) → Heap Ptr 0x500000 (24 bytes)
// [ 0x7fffffffe018 ] tags  (std::vector<int>)            → Heap Ptr 0x600000 (24 bytes)
// [ 0x7fffffffe030 ] grid  (std::vector<double>)         → Heap Ptr 0x700000 (24 bytes)
// ------------------------------------------------------------------------------------------

#include <chrono>
#include <cstdint>
#include <iostream>
#include <variant>
#include <vector>

// =========================================================================================
// BLOCK 1: TYPES DEFINITION (The "Ligands")
// =========================================================================================
// 02. template<int Order> struct Stencil
// Draw Memory: Stencil<3> at 0x1000
// What: sizeof(Stencil<3>) = ?? (Empty struct? 1 byte standard, 0 bytes with
// [[no_unique_address]]?) Why: Efficiency = O(0) runtime cost, Ligands = compile-time flexibility
// Where: Codebase N=1000 functions, M=50 developers
// Who: Compiler generates symbols: _Z7StencilILi3EE ...
// When: Compile-time T=3.2s
// Without: variant overhead (if not empty) = 24 bytes/obj
// Which: Template reduces binary 2.4MB → 1.1MB
// ------------------------------------------------------------------------------------------

struct Stencil3P {
    static constexpr int Order = 3;
    static constexpr int Nodes = 4;
    // apply() body omitted - conceptual
    void apply(std::vector<double>& g, size_t i) const {
        (void)g;
        (void)i; /* i-1, i, i+1 */
    }
};

struct Stencil5P {
    static constexpr int Order = 5;
    static constexpr int Nodes = 6;
    void apply(std::vector<double>& g, size_t i) const {
        (void)g;
        (void)i; /* i-2..i+2 */
    }
};

struct Stencil7P {
    static constexpr int Order = 7;
    static constexpr int Nodes = 8;
    void apply(std::vector<double>& g, size_t i) const {
        (void)g;
        (void)i; /* i-3..i+3 */
    }
};

// =========================================================================================
// BLOCK 2: VARIANT vs UNION vs TAG (The "Interface")
// =========================================================================================
// 03. using StencilVariant
// Draw Memory: StencilVariant v at 0x2000
// Structure: [ Index (1 byte?) ][ Padding (?? bytes) ][ Union Storage (max size = 1) ]
// Calculate:
//   sizeof(Stencil3P) = 1 (empty class rule)
//   alignof(Stencil3P) = 1
//   Union Size = max(1,1,1) = 1
//   Index Size = 1 (std::variant implementations vary, usually 1 for <256 types)
//   Alignment = 1
//   Total Size = 1 (index) + 0 (padding) + 1 (union) = 2 bytes? Or aligned to word?
//   CHECK: std::variant often aligns to at least word size if members imply it, or implementation
//   detail? PREDICTION: sizeof(StencilVariant) == ?? (Calculate loops below) FAILURE PREDICTION F3:
//   You guess 1 byte → Actual 8 bytes? (if aligned) or 2 bytes?
// ------------------------------------------------------------------------------------------

using StencilVariant = std::variant<Stencil3P, Stencil5P, Stencil7P>;

// 04. Tag Enumeration (The "Old Practice")
// What: Tag Enum
// Why: 87 if-statements or switch table
// Where: cache lines. Jump table 696 bytes / 64 = 11 cache lines
// Who: CPU pipeline stalls = 91M checks * 12 cycles = 1.09B cycles
enum StencilTag {
    TAG_3P = 0,
    TAG_5P = 1,
    TAG_7P = 2
    // Imagine TAG_4P...TAG_100P
};

// =========================================================================================
// BLOCK 3: DATA STRUCTURES (The "State")
// =========================================================================================

void analyze_memory() {
    // --------------------------------------------------------------------------------------
    // 05. vector<StencilVariant>
    // Draw Memory State:
    // [ Stack: nodes ] 0xStackOffset → [ Heap Block: 0xHeapAddr ]
    // Capacity = 1024 elements
    // Element Size = sizeof(StencilVariant)
    // Block Size = 1024 * ?? bytes
    //
    // Calculation:
    // If sizeof(StencilVariant) == 1: Size = 1024 bytes
    // If sizeof(StencilVariant) == 16: Size = 16384 bytes
    //
    // Memory Cache Analysis:
    // L1 Cache Line = 64 bytes
    // If Size=16: 4 elements per cache line
    // If Tag Approach (int=4 bytes): 16 elements per cache line + Switch Overhead
    // --------------------------------------------------------------------------------------

    std::vector<StencilVariant> variants(1024, Stencil3P{});
    std::cout << "sizeof(Stencil3P): " << sizeof(Stencil3P) << "\n";
    std::cout << "sizeof(StencilVariant): " << sizeof(StencilVariant) << "\n";
    std::cout << "Vector Alloc Size: " << variants.capacity() * sizeof(StencilVariant)
              << " bytes\n";

    // --------------------------------------------------------------------------------------
    // 06. vector<int> tags (Comparison)
    // Draw Memory State:
    // [ Stack: tags ] → [ Heap Block ]
    // Size = 1024 * 4 bytes = 4096 bytes
    //
    // What: Tag vector
    // Why: "No-brainer" approach
    // Without: Typesafety. Tag=88 → Crash (Probability 1/1000)
    // --------------------------------------------------------------------------------------
    std::vector<int> tags(1024, TAG_3P);
    std::cout << "sizeof(int): " << sizeof(int) << "\n";
    std::cout << "Tag Vector Alloc: " << tags.capacity() * sizeof(int) << " bytes\n";
}

// =========================================================================================
// BLOCK 4: ALGORITHMS (The "Computation")
// =========================================================================================

// 07. generic_apply (The "Modern Template")
// Inputs: s (Variant), g (Grid)
// Trace:
//   visit calls lambda → lambda instantiated for S3, S5, S7
//   S3.apply() inlined? ✓
//   Branching: Switch on index (0,1,2) → Jump Table
//   Cost: Load Index (L1) + Jump + Execute
//   Cycles: ~5-10 cycles?
template <class V>
void generic_apply(const V& v, std::vector<double>& g, size_t i) {
    // TODO: Draw Stack Frame for lambda capture
    std::visit([&](const auto& stencil) { stencil.apply(g, i); }, v);
}

// 08. legacy_apply (The "Tag Switch")
// Inputs: tag (int), g (Grid)
// Trace:
//   switch(tag)
//   case 0: Stencil3P{}.apply
//   case 1: Stencil5P{}.apply
//   ...
//   Branching: Switch on tag → if-else chain or jump table
//   Miss prediction risk: High if tags are random
//   Extensibility: Add Case 88 → Modify File → Recompile All
void legacy_apply(int tag, std::vector<double>& g, size_t i) {
    switch (tag) {
        case TAG_3P:
            Stencil3P{}.apply(g, i);
            break;
        case TAG_5P:
            Stencil5P{}.apply(g, i);
            break;
        case TAG_7P:
            Stencil7P{}.apply(g, i);
            break;
        // Maintenance Nightmare: Case 88 missing? → Bug
        default:
            break;  // Silent failure or crash?
    }
}

// =========================================================================================
// BLOCK 5: MAIN (The "Driver")
// =========================================================================================

int main() {
    // 09. SETUP
    // N = 1024 grid
    std::vector<double> grid(1024, 1.0);

    // 10. PREDICT SIZE
    // What: Predict sizeof(StencilVariant)
    // Why: Alignment rules (max_align_t or double alignment inside unions?)
    // Without: Correct prediction → Buffer overflow mental model failure
    // Which: GCC vs MSVC might differ

    analyze_memory();

    // 11. EXERCISE 1: MAINTENANCE COST SIMULATION
    // Scenario: Add Stencil9P
    // Template: Add struct Stencil9P, add to Variant type using. Lines=??
    // Tag: Add enum, add struct, add switch case. Lines=??
    // Cost Ratio: Tag/Template = 6 lines / 1 line?

    // 12. EXERCISE 2: RUNTIME CYCLES
    // N = 1024
    // Iterations = 1000
    // Total Ops = 1M
    // Tag Overhead: 1000 cycles * 1M = 1B cycles?
    // Variant Overhead: 500 cycles * 1M = 0.5B cycles?
    // Calculate exact difference based on assembly (jump table vs vtable vs switch)

    std::cout << "Done. Now analyze the source code comments exclusively.\n";
    return 0;
}
