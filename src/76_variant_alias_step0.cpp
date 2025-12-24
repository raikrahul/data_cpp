// 76_variant_alias_step0.cpp
// STEP 0: Direct std::variant usage WITHOUT template alias.
// GOAL: See the pain. See the repetition. Feel the annoyance.
// NO SOLUTIONS YET. JUST THE PROBLEM.

#include <cstdint>
#include <iostream>
#include <variant>

// ═══════════════════════════════════════════════════════════════════════════
// STRUCT DEFINITIONS (The Types We Want to Store)
// ═══════════════════════════════════════════════════════════════════════════

struct Circle {
    // What: 3 doubles = center (x,y) + radius r.
    // Why: Minimal data to define a circle in 2D.
    // Where: Stack @ 0x7FFF1000 (example).
    // Size: 3 × 8 bytes = 24 bytes.
    // Alignment: alignof(double) = 8 bytes.
    // Memory Layout:
    //   +0x00: x (8B) = 1.0 → 0x3FF0000000000000
    //   +0x08: y (8B) = 2.0 → 0x4000000000000000
    //   +0x10: r (8B) = 0.5 → 0x3FE0000000000000
    double x{};  // Center X: range [-1e9, +1e9]
    double y{};  // Center Y: range [-1e9, +1e9]
    double r{};  // Radius:   range (0, +1e9]
};

struct Rectangle {
    // What: 4 doubles = corners (x1,y1) bottom-left, (x2,y2) top-right.
    // Why: Axis-aligned bounding box representation.
    // Where: Stack @ 0x7FFF2000.
    // Size: 4 × 8 bytes = 32 bytes.
    // Alignment: 8 bytes.
    // Memory Layout:
    //   +0x00: x1 (8B) = 0.0 → 0x0000000000000000
    //   +0x08: y1 (8B) = 0.0 → 0x0000000000000000
    //   +0x10: x2 (8B) = 5.0 → 0x4014000000000000
    //   +0x18: y2 (8B) = 3.0 → 0x4008000000000000
    double x1{}, y1{};
    double x2{}, y2{};
};

struct Ellipse {
    // What: 4 doubles = center (cx,cy) + semi-axes (a,b).
    // Why: General ellipse equation: ((x-cx)/a)² + ((y-cy)/b)² = 1.
    // Where: Stack @ 0x7FFF3000.
    // Size: 4 × 8 bytes = 32 bytes.
    // Alignment: 8 bytes.
    // Memory Layout:
    //   +0x00: cx (8B) = 4.0 → 0x4010000000000000
    //   +0x08: cy (8B) = 4.0 → 0x4010000000000000
    //   +0x10: a  (8B) = 2.0 → 0x4000000000000000
    //   +0x18: b  (8B) = 1.0 → 0x3FF0000000000000
    double cx{}, cy{};
    double a{}, b{};
};

// ═══════════════════════════════════════════════════════════════════════════
// STEP 0: DIRECT VARIANT USAGE (The Painful Way)
// ═══════════════════════════════════════════════════════════════════════════
//
// ANNOYANCE CALCULATION:
// Characters in "std::variant<Circle, Rectangle, Ellipse>" = 42 chars.
// If used 100 times in codebase: 100 × 42 = 4200 characters typed.
// If used 1000 times: 1000 × 42 = 42,000 characters typed.
// Change "Ellipse" to "Oval"? Find-replace 1000 locations.
// Probability of missing one: P(miss) ≈ 1 - (0.999)^1000 = 63% chance of bug.
//
// VARIANT SIZE CALCULATION:
// max(sizeof(Circle), sizeof(Rectangle), sizeof(Ellipse)) = max(24, 32, 32) = 32 bytes.
// Index storage: 1 byte (since 3 types < 256).
// Padding to alignment: 7 bytes (next multiple of 8 after 1 is 8).
// Total: 8 (header) + 32 (union) = 40 bytes.
//
// MEMORY LAYOUT of std::variant<Circle, Rectangle, Ellipse> @ 0x7FFF0000:
// ┌──────────────┬────────┬─────────────────────────────────────────────────┐
// │ Address      │ Size   │ Content                                         │
// ├──────────────┼────────┼─────────────────────────────────────────────────┤
// │ 0x7FFF0000   │ 1B     │ Index: 0x00=Circle, 0x01=Rectangle, 0x02=Ellipse│
// ├──────────────┼────────┼─────────────────────────────────────────────────┤
// │ 0x7FFF0001   │ 7B     │ Padding: 0xCC 0xCC 0xCC 0xCC 0xCC 0xCC 0xCC     │
// ├──────────────┼────────┼─────────────────────────────────────────────────┤
// │ 0x7FFF0008   │ 32B    │ Union Storage (holds ONE of the 3 types)       │
// └──────────────┴────────┴─────────────────────────────────────────────────┘
// Total: 40 bytes per variant instance.
//
// CACHE ANALYSIS:
// L1 cache line = 64 bytes.
// Variants per cache line = floor(64 / 40) = 1 variant + 24B wasted.
// Efficiency = 40/64 = 62.5%.
// If N=1000 variants: 1000 cache lines touched = 1000 × ~100 cycles = 100,000 cycles.
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // ───────────────────────────────────────────────────────────────────────
    // INSTANCE 1: shape1 @ Stack
    // What: First shape variable.
    // Why: Store a Circle.
    // Where: Stack @ RSP+0x00 (40 bytes).
    // Memory after assignment:
    //   [0x00] = 0x00 (index=Circle)
    //   [0x08] = 1.0 (x), [0x10] = 2.0 (y), [0x18] = 0.5 (r)
    //   [0x20..0x27] = unused (8 bytes padding in union)
    // ───────────────────────────────────────────────────────────────────────
    std::variant<Circle, Rectangle, Ellipse> shape1 = Circle{1.0, 2.0, 0.5};
    // CHARACTER COUNT: 42 characters for type name.

    // ───────────────────────────────────────────────────────────────────────
    // INSTANCE 2: shape2 @ Stack
    // What: Second shape variable.
    // Why: Store a Rectangle.
    // Where: Stack @ RSP+0x28 (40 bytes, after shape1).
    // Memory after assignment:
    //   [0x28] = 0x01 (index=Rectangle)
    //   [0x30] = 0.0 (x1), [0x38] = 0.0 (y1)
    //   [0x40] = 5.0 (x2), [0x48] = 3.0 (y2)
    // ───────────────────────────────────────────────────────────────────────
    std::variant<Circle, Rectangle, Ellipse> shape2 = Rectangle{0.0, 0.0, 5.0, 3.0};
    // CHARACTER COUNT: 42 characters for type name. AGAIN.

    // ───────────────────────────────────────────────────────────────────────
    // INSTANCE 3: shape3 @ Stack
    // What: Third shape variable.
    // Why: Store an Ellipse.
    // Where: Stack @ RSP+0x50 (40 bytes, after shape2).
    // Memory after assignment:
    //   [0x50] = 0x02 (index=Ellipse)
    //   [0x58] = 4.0 (cx), [0x60] = 4.0 (cy)
    //   [0x68] = 2.0 (a),  [0x70] = 1.0 (b)
    // ───────────────────────────────────────────────────────────────────────
    std::variant<Circle, Rectangle, Ellipse> shape3 = Ellipse{4.0, 4.0, 2.0, 1.0};
    // CHARACTER COUNT: 42 characters for type name. AGAIN. AGAIN.

    // ───────────────────────────────────────────────────────────────────────
    // ANNOYANCE SUMMARY:
    // Total characters typed for type names: 42 + 42 + 42 = 126 characters.
    // For 100 variables: 100 × 42 = 4,200 characters.
    // For 1000 variables: 1000 × 42 = 42,000 characters.
    // Bug risk: Each repetition is a copy-paste opportunity for error.
    // Maintenance: Change list? Edit 1000 locations.
    // ───────────────────────────────────────────────────────────────────────

    // ═══════════════════════════════════════════════════════════════════════
    // VERIFICATION: Print sizes and indices to confirm memory layout.
    // ═══════════════════════════════════════════════════════════════════════
    std::cout << "sizeof(Circle)    = " << sizeof(Circle) << " bytes\n";
    std::cout << "sizeof(Rectangle) = " << sizeof(Rectangle) << " bytes\n";
    std::cout << "sizeof(Ellipse)   = " << sizeof(Ellipse) << " bytes\n";
    std::cout << "sizeof(variant)   = " << sizeof(shape1) << " bytes\n";
    std::cout << "\n";
    std::cout << "shape1.index() = " << shape1.index() << " (expected 0 = Circle)\n";
    std::cout << "shape2.index() = " << shape2.index() << " (expected 1 = Rectangle)\n";
    std::cout << "shape3.index() = " << shape3.index() << " (expected 2 = Ellipse)\n";

    // ═══════════════════════════════════════════════════════════════════════
    // STACK FRAME DIAGRAM (Approximate):
    //
    // High Address
    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ Return Address                                                      │
    // ├─────────────────────────────────────────────────────────────────────┤
    // │ shape3 (40 bytes) @ RSP+0x50                                        │
    // │   [0x50]: index=0x02                                                │
    // │   [0x58]: cx=4.0, cy=4.0, a=2.0, b=1.0                              │
    // ├─────────────────────────────────────────────────────────────────────┤
    // │ shape2 (40 bytes) @ RSP+0x28                                        │
    // │   [0x28]: index=0x01                                                │
    // │   [0x30]: x1=0.0, y1=0.0, x2=5.0, y2=3.0                            │
    // ├─────────────────────────────────────────────────────────────────────┤
    // │ shape1 (40 bytes) @ RSP+0x00                                        │
    // │   [0x00]: index=0x00                                                │
    // │   [0x08]: x=1.0, y=2.0, r=0.5, padding=8B                           │
    // └─────────────────────────────────────────────────────────────────────┘
    // Low Address (RSP)
    //
    // Total stack usage: 40 × 3 = 120 bytes.
    // ═══════════════════════════════════════════════════════════════════════

    return 0;
}
