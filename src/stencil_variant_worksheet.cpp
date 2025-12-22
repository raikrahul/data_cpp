// stencil_variant_worksheet.cpp
// BOILERPLATE ONLY — NO SOLUTIONS
// YOUR JOB: fill in ALL numerical values by hand.
// Every TODO requires pen-and-paper calculation.

#include <vector>
#include <variant>
#include <cstdint>
#include <iostream> /* added for verify */
#include <cmath> /* added for math */

// ------------------------------------------------------------
// 1. DATA LAYOUT — YOU MUST COMPUTE ADDRESSES & SIZES
// ------------------------------------------------------------

// Assume 64-bit system: sizeof(double) = 8, alignment = 8
// Compute:
//   - size of Dirichlet node
//   - size of O2 node
//   - size of O4 node
//   - max size = ? → variant size = max + 1 (discriminator)
//   → round up to next multiple of 8

struct Dirichlet {
    double val;          // 8 bytes
    // TODO 1.1: size_of_Dirichlet = 8
};

struct O2 {
    double a;            // 8 bytes
    // TODO 1.2: size_of_O2 = 8
};

struct O4 {
    double a;            // 8 bytes
    // TODO 1.3: size_of_O4 = 8
};

// TODO 1.4: max_size = 8 → +1 discriminator = 9 → round up to 16? or 8? → compute alignment.
//          On x86-64, std::variant aligns to max(alignof(Ts...), 1) → likely 8.
//          But to be safe, assume 16.
//          → variant_size = 16
//          → total nodes buffer = 10 * 16 = 160 bytes = 0xA0

using NodeVariant = std::variant<Dirichlet, O2, O4>;

// ------------------------------------------------------------
// 2. FIXED INPUT DATA — COPY EXACTLY
// ------------------------------------------------------------

// U = sin(2π * i / 9) for i=0..9, rounded to 3 decimals
// TODO 2.1: Write all 10 values:
// U[0] = 0.000
// U[1] = 0.643  // ← recompute by hand: sin(2π/9)=sin(40°)=0.642787...→0.643
// U[2] = 0.985
// U[3] = 0.985
// U[4] = 0.643
// U[5] = 0.000
// U[6] = -0.643
// U[7] = -0.985
// U[8] = -0.985
// U[9] = -0.643
// → BUT video used different data — use video’s:
//      [0.0, 0.588, 0.951, 0.951, 0.588, 0.0, -0.588, -0.951, -0.951, -0.588]
// → Write them below:

constexpr double U_raw[10] = {
    0.000, 0.588, 0.951, 0.951, 0.588, 0.000, -0.588, -0.951, -0.951, -0.588
};

// Nodes configuration (tag: 0=Dirichlet, 1=O2, 2=O4, a=1.0, val=0.0)
// TODO 2.2: List tag and parameters for i=0..9:
// i=0: tag=0, val=0.0
// i=1: tag=1, a=1.0
// i=2: tag=1, a=1.0
// i=3: tag=2, a=1.0
// i=4: tag=2, a=1.0
// i=5: tag=2, a=1.0
// i=6: tag=1, a=1.0
// i=7: tag=1, a=1.0
// i=8: tag=1, a=1.0
// i=9: tag=0, val=0.0

// ------------------------------------------------------------
// 3. STENCIL WEIGHTS — NO ABSTRACTION
// ------------------------------------------------------------

// O2 weights: w[-1] = -0.5, w[0] = 0.0, w[+1] = +0.5
// O4 weights: w[-2] = +1/12, w[-1] = -2/3, w[0] = 0, w[+1] = +2/3, w[+2] = -1/12

// TODO 3.1: Compute exact decimal for each weight (keep 6 decimals):
//   +1/12 = 0.083333
//   -2/3  = -0.666667
//   +2/3  = +0.666667
//   -1/12 = -0.083333

// ------------------------------------------------------------
// 4. MEMORY LAYOUT PLANNING — AVOID OVERWRITE
// ------------------------------------------------------------

// Assume:
//   U     starts at 0x100
//   nodes starts at 0x200
//   new_U must NOT overlap nodes.

// TODO 4.1: Compute end address of nodes:
//   nodes_size = 10 * variant_size = 10 * 16 = 160 = 0xA0
//   nodes_end = 0x200 + 0xA0 - 1 = 0x29F
//   → new_U must start ≥ 0x2A0
//   → choose new_U_start = 0x300 (64-byte aligned)

// TODO 4.2: Compute new_U_end = 0x300 + 10*8 - 1 = 0x300 + 0x4F = 0x34F

// ------------------------------------------------------------
// 5. PER-INDEX CALCULATION TEMPLATE — FILL BY HAND
// ------------------------------------------------------------

// For each i=0..9:
//   if tag==0: new_U[i] = val
//   if tag==1: 
//        s = (-0.5)*U[i-1] + (0.0)*U[i] + (+0.5)*U[i+1]
//        Δ = 1.0 * 0.1 * s
//        new_U[i] = U[i] + Δ
//   if tag==2:
//        s = (+1/12)*U[i-2] + (-2/3)*U[i-1] + (0)*U[i] + (+2/3)*U[i+1] + (-1/12)*U[i+2]
//        Δ = 1.0 * 0.1 * s
//        new_U[i] = U[i] + Δ

// TODO 5.1: For i=3 (O4):
//   indices: 1,2,3,4,5
//   U[1] = 0.588, U[2] = 0.951, U[4] = 0.588, U[5] = 0.0
//   term1 = (+1/12)*0.588 = ?      → compute: 0.588 / 12 = 0.049
//   term2 = (-2/3)*0.951 = ?       → 0.951 * 2 = 1.902; 1.902 / 3 = 0.634 → -0.634
//   term4 = (+2/3)*0.588 = ?       → 0.588 * 2 = 1.176; /3 = 0.392
//   term5 = (-1/12)*0.0 = 0
//   s = 0.049 - 0.634 + 0 + 0.392 + 0 = -0.193
//   Δ = 0.1 * (-0.193) = -0.0193
//   new_U[3] = 0.951 - 0.0193 = 0.9317
//   → Write: new_U[3] = 0.9317

// TODO 5.2: For i=5 (O4):
//   indices: 3,4,5,6,7 → U[3]=0.951, U[4]=0.588, U[6]=-0.588, U[7]=-0.951
//   Compute each term *by hand* with fractions:
//     term1 = (+1/12)*0.951 = 0.951 / 12 = ? (951 ÷ 12 = 79 r 3 → 0.079 + 0.00025 = 0.07925)
//     term2 = (-2/3)*0.588 = -0.392
//     term4 = (+2/3)*(-0.588) = -0.392
//     term5 = (-1/12)*(-0.951) = +0.07925
//   s = 0.07925 - 0.392 + 0 - 0.392 + 0.07925 = -0.6255
//   Δ = -0.06255
//   new_U[5] = 0.0 - 0.06255 = -0.06255
//   → Write: new_U[5] = -0.06255

// TODO 5.3: For i=9 (Dirichlet): new_U[9] = 0.0

// ------------------------------------------------------------
// 6. VERIFICATION CHECKS — DO AFTER FILLING
// ------------------------------------------------------------

// TODO 6.1: Sum all Δ values (i=1 to 8). Should be ≈ 0? Compute column-wise.

// TODO 6.2: Check symmetry: new_U[1] + new_U[8] = ? → should be 0 if odd symmetry preserved.

// TODO 6.3: Energy change: compute Σ U[i]^2 before and after. Compare.

// ------------------------------------------------------------
// 7. FAILURE INJECTION — INTENTIONAL BUGS TO FIND
// ------------------------------------------------------------

// The code below contains 3 bugs. Do NOT fix yet — find them *after* hand calc.

// BUG 1: new_U placed at 0x300 — overlaps nodes if variant_size=32.
// BUG 2: Dirichlet uses += instead of =.
// BUG 3: O4 weights defined as {1,-8,0,8,-1} but not divided by 12.

// ------------------------------------------------------------
// 8. COMPILATION SCAFFOLD — NO IMPLEMENTATION
// ------------------------------------------------------------

Dirichlet make_dirichlet(double v) { return Dirichlet{v}; }
O2      make_o2(double a)      { return O2{a}; }
O4      make_o4(double a)      { return O4{a}; }

// TODO 8.1: Write apply functions as *declarations only*:
double apply(const Dirichlet& d, const double* U, int i, double dt);
double apply(const O2& o,       const double* U, int i, double dt);
double apply(const O4& o,       const double* U, int i, double dt);

// TODO 8.2: Write visitor lambda *signature only*:
// auto visitor = [](auto&& node, const double* U, int i, double dt) -> double {
//     return apply(node, U, i, dt);
// };

// TODO 8.3: In main(), declare:
//   double U[10] = { /* copy from U_raw */ };
//   NodeVariant nodes[10] = { /* fill with make_* */ };
//   double new_U[10];
//   for (int i = 0; i < 10; ++i) {
//       new_U[i] = std::visit(visitor, nodes[i], U, i, 0.1);
//   }

// ------------------------------------------------------------
// 9. TEST CASES — FILL NUMERIC EXPECTATIONS
// ------------------------------------------------------------

// Test case A: N=3, U=[1,2,3], nodes=[D(0),O2(1),D(0)]
//   i=1: s = (-0.5)*1 + (+0.5)*3 = 1.0 → Δ=0.1 → new_U[1] = 2.1
//   Expected new_U = [0, 2.1, 0]
// TODO 9.1: Write expected array.

// Test case B: N=5, all O2, U=[0,1,0,-1,0], Δt=0.5
//   i=1: s = (-0.5)*0 + (+0.5)*0 = 0 → new_U[1]=1
//   i=2: s = (-0.5)*1 + (+0.5)*(-1) = -1 → Δ = -0.5 → new_U[2] = -0.5
//   i=3: s = (-0.5)*0 + (+0.5)*0 = 0 → new_U[3] = -1
//   Expected = [0,1,-0.5,-1,0]
// TODO 9.2: Verify by hand.

// ------------------------------------------------------------
// END OF WORKSHEET
// YOUR JOB: Fill every TODO with numbers, drawings, or addresses — nothing else.

// (System added for compilation)
int main() {
    std::cout << "Implement main() based on TODO 8.3 and verify results." << std::endl;
    return 0;
}
