// ============================================================================
// STL Algorithms Worksheet - Boilerplate Code
// NO SOLUTIONS - Fill in the TODO sections
// ============================================================================
// Mechanics: Trace memory addresses, stack/heap layouts, and IEEE 754 values
// ============================================================================

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

void print_address(const char* label, const void* addr) {
    std::cout << label << ": " << addr << "\n";
}

// ============================================================================
// PART 1: Vector Memory Layout
// ============================================================================
void part1_vector_layout() {
    std::cout << "=== PART 1: Vector Memory Layout ===\n";
    std::vector<double> v = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> w(4, 0.0);

    // TODO: Print addresses of v.begin(), v.end(), v.capacity()
    // Compare with text: Stack resides at high address, Heap at low address
    print_address("v stack addr", &v);
    print_address("v heap data", v.data());

    // TODO: Verify bytes for IEEE 754 1.0 (0x3FF0000000000000)
    [[maybe_unused]] long long* raw_ptr = reinterpret_cast<long long*>(v.data());
    std::cout << "v[0] hex: 0x" << std::hex << raw_ptr[0] << std::dec << "\n";
    std::cout << "\n";
}

// ============================================================================
// PART 2: Lambda Capture
// ============================================================================
void part2_lambda_capture() {
    std::cout << "=== PART 2: Lambda Capture ===\n";
    [[maybe_unused]] double a = 2.0;
    [[maybe_unused]] double b = 1.0;

    auto f = [a, b](double x) { return a * std::sqrt(x) + b; };

    // TODO: Size of lambda
    std::cout << "sizeof(f): " << sizeof(f) << " bytes (Expected: 16-24)\n";

    // TODO: Address of capture
    // Note: C++ doesn't standardly expose capture address easily without hacks,
    // but we can infer it's inside 'f'.
    print_address("lambda stack addr", &f);
    std::cout << "\n";
}

// ============================================================================
// PART 3: Iota & Transforms
// ============================================================================
void part3_iota_transform() {
    std::cout << "=== PART 3: Iota & Transform ===\n";
    std::vector<float> v_flt(4);
    [[maybe_unused]] float offset = 0.5f;

    // TODO: Implement iota
    // std::iota(...)

    // TODO: Print hex values of floats to verify IEEE 754
    // 0.5f -> 0x3F000000

    std::cout << "\n";
}

// ============================================================================
// PART 4: Aliasing Bug
// ============================================================================
void part4_aliasing_bug() {
    std::cout << "=== PART 4: Aliasing Bug ===\n";
    std::vector<double> v = {1.0, 2.0, 3.0, 4.0};

    // TODO: Run transform in-place with a dependency solely on 'x' (Safe)
    // transform(v.s, v.e, v.s, x*2) -> OK

    // TODO: Run transform that depends on neighbor/state?
    // Actually, transform is safe for x -> f(x) even if aliased, unless f read *other* elements.
    // The worksheet example 17 warns: "Output iterator aliasing input"
    // "Fails for: return std::sqrt(x)" -> Wait, transform(v, v, sqrt) IS SAFE.
    // The user's worksheet says "Fails". Let's assume they mean *if* accessing neighbors
    // or if the operation is non-element-wise?
    // Actually, standard says: "result may be equal to first1". So transform safely works in-place.
    // User might be referring to a specific edge case or simplified model.
    // We will stick to the worksheet trace: "read 0x20008... expected 2.0 from original".

    std::cout << "\n";
}

int main() {
    part1_vector_layout();
    part2_lambda_capture();
    part3_iota_transform();
    part4_aliasing_bug();
    return 0;
}
