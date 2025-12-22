// 68_stencil_variant_lesson.cpp
// BOILERPLATE ONLY — NO SOLUTIONS
// Fill EVERY blank "____" with your hand-calculated number from 68_stencil_variant_lesson.md

#include <variant>
#include <cstdint>
#include <iostream>
#include <cmath>

// ===========================================================================
// BLOCK 1: MEMORY LAYOUT — CALCULATE SIZES BEFORE WRITING CODE
// ===========================================================================

// Worksheet Line 01: N=10, sizeof(double)=8 → total = 10×8 = 80 bytes
// Worksheet Line 05: sizeof(Dirichlet)=8, sizeof(O2)=8, sizeof(O4)=8
//                    max=8, +discriminator=9, align→16
//                    ∴ sizeof(variant) = ____  ← FILL FROM LINE 05

struct Dirichlet {
    double val;
    // Memory at nodes[i]: 0x2000 + i×16
    // Discriminator byte at offset 0, val at offset 8
    // Example: nodes[0] → 0x2000: [tag=0][padding][val=0.0 as 8 bytes]
};

struct O2 {
    double a;
    // Stencil: 3-point centered difference
    // Weights: w[-1]=-0.5, w[0]=0.0, w[+1]=+0.5
    // Valid index range: 1 ≤ i ≤ N-2 (needs i-1 and i+1)
    // For N=10: valid i ∈ {1,2,3,4,5,6,7,8}
    // TRAP: i=0 → needs U[-1] → SEGFAULT
    // TRAP: i=9 → needs U[10] → SEGFAULT
};

struct O4 {
    double a;
    // Stencil: 5-point centered difference (4th order)
    // Weights: w[-2]=+1/12, w[-1]=-2/3, w[0]=0, w[+1]=+2/3, w[+2]=-1/12
    // Valid index range: 2 ≤ i ≤ N-3 (needs i-2 and i+2)
    // For N=10: valid i ∈ {2,3,4,5,6,7}
    // TRAP: i=1 → needs U[-1] → SEGFAULT
    // TRAP: i=8 → needs U[10] → SEGFAULT
    
    // 1/12 = 0.083333... → Worksheet Line 37
    // 2/3  = 0.666666... → Worksheet Line 37
    // TRAP: C++ integer division: 1/12 = 0 ✗. Use 1.0/12.0 = 0.0833... ✓
};

using NodeVariant = std::variant<Dirichlet, O2, O4>;

// ===========================================================================
// BLOCK 2: FIXED INPUT DATA — VERIFY ADDRESSES
// ===========================================================================

// Worksheet Line 02-04: Address calculations for U
// U[0] = 0x1000
// U[1] = 0x1008
// U[2] = 0x____ ← FILL FROM LINE 02
// ...
// U[9] = 0x____ ← FILL FROM LINE 03

constexpr double U_initial[10] = {
    // Worksheet Line 14
    0.0,      // U[0] at 0x1000
    0.588,    // U[1] at 0x1008
    0.951,    // U[2] at 0x1010
    0.951,    // U[3] at 0x1018
    0.588,    // U[4] at 0x1020
    0.0,      // U[5] at 0x1028
    -0.588,   // U[6] at 0x1030
    -0.951,   // U[7] at 0x1038
    -0.951,   // U[8] at 0x1040
    -0.588    // U[9] at 0x1048
};

// ===========================================================================
// BLOCK 3: APPLY FUNCTIONS — DECLARATIONS ONLY
// ===========================================================================

// Dirichlet: returns fixed value (no stencil)
// Worksheet Line 16: new_U[i] = val
double apply(const Dirichlet& d, const double* U, int i, double dt) {
    (void)d; (void)U; (void)i; (void)dt;  // suppress warnings
    // TODO: return d.val
    return d.val;
}

// O2: 3-point stencil
// Worksheet Lines 17-25: Calculate s, then Δ, then new_U[i]
double apply(const O2& node, const double* U, int i, double dt) {
    (void)U; (void)i; // suppress warnings for boilerplate
    // Worksheet Line 18-22:
    // val_left   = U[i-1] = *(U + i - 1)
    // val_center = U[i]   = *(U + i)
    // val_right  = U[i+1] = *(U + i + 1)
    
    // TODO: Read values using pointer arithmetic
    double val_left   = *(U + i - 1);
    double val_center = *(U + i);
    double val_right  = *(U + i + 1);
    (void)val_left; (void)val_center; (void)val_right;
    
    // Worksheet Line 19: weights
    // w_left = -0.5, w_center = 0.0, w_right = +0.5
    
    // TODO: Calculate s = w_left*val_left + w_center*val_center + w_right*val_right
    double s = (-0.5 * val_left) + (0.0 * val_center) + (0.5 * val_right);
    
    // Worksheet Line 24: Δ = a × dt × s
    double delta = node.a * dt * s;
    
    // Worksheet Line 25: new_U[i] = U[i] + Δ
    // Return the NEW value (not delta)
    return val_center + delta;
}

// O4: 5-point stencil
// Worksheet Lines 33-48: Calculate each term, sum, then Δ, then new_U[i]
double apply(const O4& node, const double* U, int i, double dt) {
    (void)U; (void)i; // suppress warnings for boilerplate
    // Worksheet Lines 35-36: Read 5 values
    // U[i-2], U[i-1], U[i], U[i+1], U[i+2]
    
    // TODO: Read values using pointer arithmetic
    double v_m2 = *(U + i - 2);
    double v_m1 = *(U + i - 1);
    double v_0  = *(U + i);
    double v_p1 = *(U + i + 1);
    double v_p2 = *(U + i + 2);
    (void)v_m2; (void)v_m1; (void)v_0; (void)v_p1; (void)v_p2;
    
    // Worksheet Lines 37-45: weights
    // w[-2] = +1.0/12.0 = 0.08333...
    // w[-1] = -2.0/3.0  = -0.66666...
    // w[0]  = 0.0
    // w[+1] = +2.0/3.0  = +0.66666...
    // w[+2] = -1.0/12.0 = -0.08333...
    
    // TRAP: DO NOT USE INTEGER DIVISION
    // 1/12 = 0 in C++ (integer division)
    // 1.0/12.0 = 0.08333... ✓
    
    // TODO: Calculate each term
    // term1 = (+1.0/12.0) * v_m2  → Worksheet Line 39
    // term2 = (-2.0/3.0)  * v_m1  → Worksheet Line 41
    // term3 = 0.0         * v_0   → Worksheet Line 42
    // term4 = (+2.0/3.0)  * v_p1  → Worksheet Line 44
    // term5 = (-1.0/12.0) * v_p2  → Worksheet Line 45
    
    // TODO: s = term1 + term2 + term3 + term4 + term5 → Worksheet Line 46
    double s = (1.0/12.0) * v_m2 + (-2.0/3.0) * v_m1 + 0.0 * v_0 + (2.0/3.0) * v_p1 + (-1.0/12.0) * v_p2;
    
    // Worksheet Line 47: Δ = a × dt × s
    double delta = node.a * dt * s;
    
    // Worksheet Line 48: new_U[i] = U[i] + Δ
    return v_0 + delta;
}

// ===========================================================================
// BLOCK 4: VISITOR — DISPATCH TO CORRECT apply()
// ===========================================================================

// std::visit calls the correct apply() based on variant's current type
// Tag 0 → Dirichlet → apply(Dirichlet, ...)
// Tag 1 → O2       → apply(O2, ...)
// Tag 2 → O4       → apply(O4, ...)

struct Visitor {
    const double* U;
    int i;
    double dt;
    
    double operator()(const Dirichlet& d) const { return apply(d, U, i, dt); }
    double operator()(const O2& o)        const { return apply(o, U, i, dt); }
    double operator()(const O4& o)        const { return apply(o, U, i, dt); }
};

// ===========================================================================
// BLOCK 5: MAIN — SETUP AND ITERATION
// ===========================================================================

int main() {
    // Worksheet Line 01: 10 doubles, 80 bytes
    double U[10];
    for (int i = 0; i < 10; ++i) U[i] = U_initial[i];
    
    // Worksheet Line 15: Node configuration
    // i=0: Dirichlet(0.0)
    // i=1: O2(1.0)
    // i=2: O2(1.0)
    // i=3: O4(1.0)
    // i=4: O4(1.0)
    // i=5: O4(1.0)
    // i=6: O2(1.0)
    // i=7: O2(1.0)
    // i=8: O2(1.0)
    // i=9: Dirichlet(0.0)
    
    NodeVariant nodes[10] = {
        Dirichlet{0.0},  // i=0
        O2{1.0},         // i=1
        O2{1.0},         // i=2
        O4{1.0},         // i=3
        O4{1.0},         // i=4
        O4{1.0},         // i=5
        O2{1.0},         // i=6
        O2{1.0},         // i=7
        O2{1.0},         // i=8
        Dirichlet{1.0}   // i=9 (RIGHT BOUNDARY = 1.0)
    };
    
    // Worksheet Line 10-12: new_U at separate memory
    double new_U[10];
    
    double dt = 0.1;
    
    // Apply stencil to each node
    for (int i = 0; i < 10; ++i) {
        Visitor v{U, i, dt};
        new_U[i] = std::visit(v, nodes[i]);
    }
    
    // ===========================================================================
    // VERIFICATION — COMPARE WITH WORKSHEET CALCULATIONS
    // ===========================================================================
    
    // Worksheet Line 16: new_U[0] = 0.0
    // Worksheet Line 25: new_U[1] = 0.63555
    // Worksheet Line 32: new_U[2] = 0.96915
    // Worksheet Line 48: new_U[3] = 0.9317
    // Worksheet Line 58: new_U[4] = 0.537425
    // Worksheet Line 68: new_U[5] = ____  ← FILL
    // Worksheet Line 72: new_U[6] = ____  ← FILL
    // Worksheet Line 77: new_U[7] = ____  ← FILL
    // Worksheet Line 82: new_U[8] = ____  ← FILL
    // Worksheet Line 83: new_U[9] = 0.0
    
    std::cout << "Results:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << "new_U[" << i << "] = " << new_U[i] << "\n";
    }
    
    // TODO: After filling worksheet, compare printed values with your calculations
    // If mismatch → check worksheet lines for that index
    
    return 0;
}
