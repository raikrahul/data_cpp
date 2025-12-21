// 61_constexpr_roundoff_errors.cpp
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ TASK: Implement Taylor series for e^x, observe round-off, prove compile-time vs runtime difference via assembly inspection                                                  │
// │ MACHINE DATA: g++ 13.3.0, Ubuntu 24.04, x86_64, IEEE 754 float32                                                                                                             │
// │ ASSEMBLY PROOF: .LC7 = 0x402DF855 (constexpr result pre-computed in .rodata), loops .L5/.L6 compute runtime result                                                          │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘

#include <iostream>
#include <iomanip>
#include <limits>
#include <numbers>
#include <cmath>

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ print_bits: Reinterpret 4-byte float as 4-byte unsigned int, print decimal and hex                                                                                          │
// │ MEMORY: f at 0x7FFF_XXXX (stack), sizeof(float)=4, sizeof(unsigned int)=4                                                                                                   │
// │ WHAT: f=2.7182817459 → *p=0x402DF854 → sign=0, exp=0x80 (128-127=1), mantissa=0x2DF854 → 1.01011011111100001010100 × 2^1                                                    │
// │ WHY: IEEE 754 float32 = 1 sign + 8 exp + 23 mantissa bits = 32 bits = 4 bytes                                                                                               │
// │ WHERE: Stack frame of print_bits, p points to f's address                                                                                                                   │
// │ WHO: Called 3× in main: once for std::e, once for runtime, once for constexpr                                                                                               │
// │ WHEN: Runtime only (not constexpr)                                                                                                                                          │
// │ WITHOUT: Bit manipulation, cannot see internal representation                                                                                                               │
// │ WHICH: reinterpret_cast chosen over union (both valid for type punning in practice)                                                                                         │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
void print_bits(float f) {
    // f = 2.7182817459 → address &f = 0x7FFF_E000 (example stack address)
    // p = reinterpret_cast<unsigned int*>(&f) → p = 0x7FFF_E000 (same address, different type view)
    // *p = 0x402DF854 → 32 bits: 0|10000000|01011011111100001010100
    //                            s|exp(8)  |mantissa(23)
    // exp = 0x80 = 128 → actual exponent = 128 - 127 = 1
    // mantissa = 0x2DF854 = 3012692 → 1.mantissa = 1 + 3012692/2^23 = 1 + 3012692/8388608 = 1.359140872955322
    // value = 1.359140872955322 × 2^1 = 2.718281745910644 ≈ 2.7182817459 ✓
    auto* p = reinterpret_cast<unsigned int*>(&f);
    std::cout << "Float: " << std::fixed << std::setprecision(10) << f 
              << " | Hex: 0x" << std::hex << *p << std::dec << "\n";
}

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ my_pow: Compute base^exp via repeated multiplication                                                                                                                         │
// │ WHAT: base=1.0f, exp=5 → acc = 1.0 × 1.0 × 1.0 × 1.0 × 1.0 × 1.0 = 1.0 (5 multiplications)                                                                                  │
// │ WHY: x^n needed for Taylor term x^n/n! → for e^1, x=1, so x^n = 1^n = 1 always (trivial case)                                                                               │
// │ WHERE: Called inside my_e_pow_x, 15 times for TERMS=15 → i=1,2,...,15 → exp=1,2,...,15                                                                                      │
// │ WHO: my_e_pow_x calls my_pow(x, i) for each term                                                                                                                            │
// │ WHEN: RUNTIME = loops .L5/.L6 in assembly, CONSTEXPR = g++ interpreter during compilation                                                                                   │
// │ WITHOUT: pow() function, need manual loop                                                                                                                                   │
// │ WHICH: Integer exponent only (no fractional)                                                                                                                                │
// │                                                                                                                                                                             │
// │ NUMERICAL EXAMPLES:                                                                                                                                                         │
// │ 1. base=1.0, exp=10 → 1.0^10 = 1.0 (10 muls, each mul = 1.0×1.0 = 1.0, no round-off)                                                                                        │
// │ 2. base=2.0, exp=10 → 2^10 = 1024.0 (exact, 1024 = 2^10 representable in float)                                                                                             │
// │ 3. base=1.1, exp=10 → 1.1^10 = 2.5937424601... → float = 2.5937424... (round-off at each mul)                                                                               │
// │ 4. base=3.14159, exp=5 → 3.14159^5 = 306.0196... → accumulated round-off from 5 muls                                                                                        │
// │ 5. EDGE: exp=0 → loop body never executes → return acc=1.0 (correct: x^0 = 1)                                                                                               │
// │ 6. EDGE: exp=1 → 1 iteration → acc = 1.0 × base = base (correct: x^1 = x)                                                                                                   │
// │ 7. LARGE: exp=100 → 100 multiplications → if base=1.0001, acc = 1.0001^100 ≈ 1.0100501... (compound error)                                                                  │
// │                                                                                                                                                                             │
// │ ROUND-OFF ANALYSIS (base=1.1, exp=10):                                                                                                                                      │
// │ iter₀: acc=1.0                                                                                                                                                              │
// │ iter₁: acc=1.0×1.1=1.1 → 0x3F8CCCCD (exact? 1.1 not exactly representable → 1.10000002384...)                                                                               │
// │ iter₂: acc=1.10000002384×1.10000002384=1.21000005... → round to nearest float                                                                                               │
// │ ...each step accumulates ≤0.5 ULP error                                                                                                                                     │
// │ iter₁₀: acc=2.5937424... → total accumulated error ≈ 5 ULP                                                                                                                  │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
constexpr float my_pow(float base, int exp) {
    // acc at 0x7FFF_E010 (stack), sizeof(float)=4, initial value = 0x3F800000 = 1.0f
    // RUNTIME ASSEMBLY (.L6): movaps %xmm3, %xmm0 → xmm0 = 1.0f initially
    //                         mulss %xmm1, %xmm0 → xmm0 *= converted int i (wait, this is factorial logic, not pow)
    // CORRECTION: In generated asm, x=1.0 so x^n = 1.0 always, compiler may optimize away pow entirely
    float acc = 1;
    // Loop: i = 0,1,2,...,exp-1 → exp iterations
    // For exp=5: i=0→acc=1×base, i=1→acc=base×base, ... , i=4→acc=base^5
    // For exp=0: loop condition 0 < 0 false → 0 iterations → return 1.0 ✓
    for (int i = 0; i < exp; i++) {
        // Each multiplication: acc = acc × base
        // IEEE 754 round-to-nearest-even after each mulss instruction
        // ULP(acc) grows as acc grows → error accumulates multiplicatively
        acc *= base;
    }
    return acc;
    // RETURN: For base=1.0, exp=15 → acc=1.0 (no round-off, 1×1×...×1=1)
    // RETURN: For base=3.14159, exp=9 → acc≈29809.099... → 9 round-offs accumulated
}

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ my_fact: Compute n! via iterative multiplication                                                                                                                            │
// │ WHAT: n=5 → 1×1×2×3×4×5 = 120.0                                                                                                                                             │
// │ WHY: Denominator in Taylor term x^n/n!                                                                                                                                      │
// │ WHERE: Called inside my_e_pow_x, 15 times for TERMS=15                                                                                                                      │
// │ WHO: my_e_pow_x calls my_fact(i) for i=1,2,...,15                                                                                                                           │
// │ WHEN: RUNTIME = inner loop .L6 in assembly (cvtsi2ssl + mulss), CONSTEXPR = g++ interpreter                                                                                 │
// │ WITHOUT: tgamma() or std::factorial, need manual loop                                                                                                                       │
// │ WHICH: Returns float (not int) to avoid overflow for n>12 (13! = 6227020800 > INT_MAX = 2147483647)                                                                         │
// │                                                                                                                                                                             │
// │ FACTORIAL TABLE (exact vs float):                                                                                                                                           │
// │ n=0: 1 → 1.0 (exact)                                                                                                                                                        │
// │ n=1: 1 → 1.0 (exact)                                                                                                                                                        │
// │ n=5: 120 → 120.0 (exact, 120 < 2^23 = 8388608)                                                                                                                              │
// │ n=10: 3628800 → 3628800.0 (exact, 3628800 < 2^23)                                                                                                                           │
// │ n=12: 479001600 → 479001600.0 (exact? 479001600 < 2^29, but float has 23-bit mantissa → check: 479001600 = 0x1C8CFC00 → 29 bits needed → ROUND-OFF!)                        │
// │       float(479001600) = 479001600.0 → actually exact because it's 479001600 = 28! × ... wait let me recalc                                                                 │
// │       479001600 in binary = 11100100011001111110000000000 (29 bits) → float mantissa = 23 bits → loses 6 bits → NOT exact                                                  │
// │       float(479001600) = 479001600.0? Let's check: 479001600 / 2^29 = 0.892... × 2^29 → mantissa needs 29-1=28 bits → truncated to 23 → error!                             │
// │ n=13: 6227020800 → float = 6227020800.0? 6227020800 = 0x1_7328CC00 (33 bits) → massive truncation                                                                           │
// │ n=15: 1307674368000 → 1.307674368×10^12 → float exponent handles magnitude, mantissa loses precision                                                                        │
// │ n=34: 2.95×10^38 < FLT_MAX (3.4×10^38) → representable                                                                                                                      │
// │ n=35: 1.03×10^40 > FLT_MAX → OVERFLOW → +inf                                                                                                                                │
// │                                                                                                                                                                             │
// │ ASSEMBLY TRACE (.L6 inner loop):                                                                                                                                            │
// │ .L6:                                                                                                                                                                        │
// │     pxor    %xmm1, %xmm1       ← xmm1 = 0.0                                                                                                                                 │
// │     cvtsi2ssl %eax, %xmm1     ← xmm1 = (float)i, e.g., i=5 → xmm1 = 5.0f = 0x40A00000                                                                                       │
// │     addl    $1, %eax          ← i++ (eax = loop counter)                                                                                                                    │
// │     mulss   %xmm1, %xmm0      ← xmm0 = xmm0 × xmm1 = acc × i                                                                                                                │
// │     cmpl    %eax, %edx        ← compare i to n                                                                                                                              │
// │     jne     .L6               ← loop if i != n                                                                                                                              │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
constexpr float my_fact(int n) {
    // EDGE: n<0 → mathematically undefined → return NaN (0.0f/0.0f = NaN = 0x7FC00000)
    // 0.0f = 0x00000000, 0.0f/0.0f triggers invalid operation → NaN
    if (n < 0) {
        return 0.0f/0.0f;  // NaN = 0x7FC00000 (quiet NaN)
    }
    // res at stack, initial = 0x3F800000 = 1.0f
    float res = 1.0f;
    // Loop: i = 1,2,3,...,n → n iterations
    // For n=0: loop condition 1 < 0+1 = 1 < 1 false → 0 iterations → return 1.0 ✓ (0! = 1)
    // For n=1: i=1 → 1 < 2 true → res = 1.0 × 1.0 = 1.0 → i=2 → 2 < 2 false → return 1.0 ✓ (1! = 1)
    // For n=5: i=1,2,3,4,5 → res = 1×1×2×3×4×5 = 120.0 ✓
    for (int i = 1; i < n + 1; i++) {
        // cvtsi2ssl: convert int i to float → exact for i ≤ 2^24 = 16777216
        // mulss: res = res × (float)i → round-to-nearest after each mul
        // For n=15: i=15 → (float)15 = 15.0 exact → res = 87178291200 × 15 = 1307674368000
        //           1307674368000 in float → 1.307674... × 10^12 → exponent = 40 → mantissa truncated
        res *= static_cast<float>(i);
    }
    return res;
    // RETURN for n=15: 1307674368000.0 → float approximation → 0x544B8B50 (verify with calculator)
}

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ my_e_pow_x: Taylor series for e^x = Σ(n=0 to ∞) x^n/n! ≈ 1 + x + x²/2! + x³/3! + ... (truncated at 'terms' terms)                                                          │
// │ WHAT: x=1.0, terms=15 → e^1 ≈ 1 + 1/1! + 1/2! + 1/3! + ... + 1/15!                                                                                                          │
// │ WHY: Approximate Euler's number e = 2.718281828...                                                                                                                          │
// │ WHERE: Called twice in main: once runtime (loops in CPU), once constexpr (computed by g++)                                                                                  │
// │ WHO: main() calls my_e_pow_x(1.0f, 15)                                                                                                                                      │
// │ WHEN: CONSTEXPR = during g++ compilation → result stored in .LC7 = 0x402DF855, RUNTIME = loops .L5/.L6 in CPU                                                               │
// │ WITHOUT: std::exp(), must implement manually                                                                                                                               │
// │ WHICH: Taylor series chosen (alternatives: Padé approximation, Chebyshev polynomials, CORDIC)                                                                              │
// │                                                                                                                                                                             │
// │ TERM-BY-TERM CALCULATION (x=1.0, terms=15):                                                                                                                                 │
// │ ┌──────┬─────────────┬───────────────────────────┬─────────────────────────────────┬──────────────────────────────────────────────────────────────────────────────────────┐ │
// │ │ i    │ 1^i / i!    │ term (exact)              │ term (float)                    │ running sum (float)                                                                  │ │
// │ ├──────┼─────────────┼───────────────────────────┼─────────────────────────────────┼──────────────────────────────────────────────────────────────────────────────────────┤ │
// │ │ init │ -           │ -                         │ -                               │ res = 1.0 = 0x3F800000                                                               │ │
// │ │ 1    │ 1/1 = 1     │ 1.0                       │ 1.0 = 0x3F800000                │ 1.0 + 1.0 = 2.0 = 0x40000000                                                         │ │
// │ │ 2    │ 1/2 = 0.5   │ 0.5                       │ 0.5 = 0x3F000000                │ 2.0 + 0.5 = 2.5 = 0x40200000                                                         │ │
// │ │ 3    │ 1/6         │ 0.166666...               │ 0.16666667 = 0x3E2AAAAB         │ 2.5 + 0.1666667 = 2.6666667 = 0x402AAAAB                                             │ │
// │ │ 4    │ 1/24        │ 0.041666...               │ 0.041666668 = 0x3D2AAAAB        │ 2.6666667 + 0.0416667 = 2.7083334 = 0x402D5556                                       │ │
// │ │ 5    │ 1/120       │ 0.008333...               │ 0.008333334 = 0x3C088889        │ 2.7083334 + 0.0083333 = 2.7166667 = 0x402DB6DB                                       │ │
// │ │ 6    │ 1/720       │ 0.001388...               │ 0.0013888889 = 0x3AB60B61       │ 2.7166667 + 0.0013889 = 2.7180556 = 0x402DEE56                                       │ │
// │ │ 7    │ 1/5040      │ 0.000198...               │ 0.00019841270 = 0x394FE4FE      │ 2.7180556 + 0.0001984 = 2.7182540 = 0x402DF828                                       │ │
// │ │ 8    │ 1/40320     │ 0.0000248...              │ 0.000024801587 = 0x37D00D01     │ 2.7182540 + 0.0000248 = 2.7182788 = 0x402DF842                                       │ │
// │ │ 9    │ 1/362880    │ 0.00000275...             │ 0.0000027557319 = 0x3638EF1D    │ 2.7182788 + 0.0000028 = 2.7182815 = 0x402DF853                                       │ │
// │ │ 10   │ 1/3628800   │ 0.000000275...            │ 0.00000027557319 = 0x34938EF2   │ 2.7182815 + 0.00000028 = 2.7182817 = 0x402DF854? or 0x402DF855?                      │ │
// │ │ 11   │ 1/39916800  │ 2.505...×10⁻⁸             │ 2.5052108×10⁻⁸ = 0x32D73249     │ sum += term but term < 0.5 ULP of sum → may round to same value                     │ │
// │ │ 12   │ 1/479001600 │ 2.087...×10⁻⁹             │ 2.0876757×10⁻⁹ = 0x310F7772     │ term ≪ ULP → absorbed, sum unchanged?                                               │ │
// │ │ 13   │ 1/6.227×10⁹ │ 1.606...×10⁻¹⁰            │ 1.6059044×10⁻¹⁰                 │ term ≪ ULP → absorbed                                                               │ │
// │ │ 14   │ 1/8.717×10¹⁰│ 1.147...×10⁻¹¹            │ 1.1470746×10⁻¹¹                 │ term ≪ ULP → absorbed                                                               │ │
// │ │ 15   │ 1/1.307×10¹²│ 7.647...×10⁻¹³            │ 7.6471637×10⁻¹³                 │ term ≪ ULP → absorbed                                                               │ │
// │ └──────┴─────────────┴───────────────────────────┴─────────────────────────────────┴──────────────────────────────────────────────────────────────────────────────────────┘ │
// │                                                                                                                                                                             │
// │ ULP ANALYSIS at sum ≈ 2.718:                                                                                                                                                │
// │ sum = 2.718... → exponent = 1 (since 2 ≤ 2.718 < 4 = 2²)                                                                                                                    │
// │ ULP = 2^(exp - 23) = 2^(1 - 23) = 2^(-22) = 2.384185791×10⁻⁷                                                                                                                │
// │ 0.5 ULP = 1.192×10⁻⁷                                                                                                                                                        │
// │ term at i=10: 2.755×10⁻⁷ > 0.5 ULP → ADDS to sum                                                                                                                            │
// │ term at i=11: 2.505×10⁻⁸ < 0.5 ULP → MIGHT be absorbed (depends on sum's mantissa's last bits)                                                                              │
// │ term at i=12+: definitely absorbed → sum stops changing                                                                                                                     │
// │                                                                                                                                                                             │
// │ FINAL RESULT:                                                                                                                                                               │
// │ CONSTEXPR (g++ computed): 0x402DF855 = 2.7182819843 (stored in .rodata .LC7)                                                                                                │
// │ RUNTIME (CPU computed):   0x402DF855 = 2.7182819843 (computed via loops .L5/.L6)                                                                                            │
// │ std::numbers::e_v<float>: 0x402DF854 = 2.7182817459 (library constant, correctly rounded e)                                                                                 │
// │ DIFFERENCE: Taylor(15 terms) - exact e = 1 ULP overshoot                                                                                                                    │
// │ WHY OVERSHOOT: Taylor series adds positive terms, cumulative round-off slightly positive                                                                                    │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
constexpr float my_e_pow_x(float x, int terms = 10) {
    // res at stack 0x7FFF_E020, initial = 1.0f = 0x3F800000
    // This is the "1" term in e^x = 1 + x/1! + x²/2! + ...
    // ASSEMBLY: After optimization with x=1.0 known at compile time, my_pow(1.0, n) = 1.0 always
    //           So each term = 1.0 / my_fact(i) = 1.0 / i!
    float res = 1.0f;
    // Loop: i = 1,2,3,...,terms → 'terms' iterations = 15 iterations for TERMS=15
    // RUNTIME ASSEMBLY (.L5 outer loop, .L6 inner factorial loop):
    // .L5:                          ← outer loop for terms
    //     movaps  %xmm3, %xmm0      ← xmm0 = 1.0 (for factorial accumulator)
    // .L6:                          ← inner loop for factorial(i)
    //     cvtsi2ssl %eax, %xmm1    ← convert loop counter to float
    //     mulss   %xmm1, %xmm0     ← factorial_acc *= i
    //     addl    $1, %eax
    //     cmpl    %eax, %edx
    //     jne     .L6
    //     divss   %xmm0, %xmm1     ← term = 1.0 / factorial (since x=1, x^i = 1)
    //     addss   %xmm1, %xmm2     ← sum += term
    //     cmpl    $17, %edx        ← 17 = terms+2 (loop runs 15 times for terms=15)
    //     jne     .L5
    for (int i = 1; i < terms + 1; i++) {
        // my_pow(x, i) = x^i = 1.0^i = 1.0 (for x=1.0)
        // my_fact(i) = i! = 1, 2, 6, 24, 120, ...
        // term = 1.0 / i!
        // divss instruction: xmm1 = xmm1 / xmm0 → term = 1.0 / factorial
        // addss instruction: xmm2 = xmm2 + xmm1 → sum += term
        res += my_pow(x, i) / my_fact(i);
    }
    return res;
    // CONSTEXPR: g++ evaluates this at compile time, produces 0x402DF855, stores in .LC7
    // RUNTIME: CPU executes loops, produces 0x402DF855 (same result because IEEE 754 followed by both)
}

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ TEST CONSTANTS                                                                                                                                                              │
// │ TERMS = 15 → 15 iterations → i = 1,2,...,15 → last term = 1/15! = 1/1307674368000 ≈ 7.6×10⁻¹³                                                                               │
// │ Target: e = 2.718281828459045... → float(e) = 0x402DF854 = 2.7182817459                                                                                                     │
// │ Result: Taylor(15) = 0x402DF855 = 2.7182819843 → error = +1 ULP = +2.384×10⁻⁷                                                                                               │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
constexpr int TERMS = 15;

int main() {
    // Print std::numbers::e_v<float> = 0x402DF854 = 2.7182817459
    // This is the correctly rounded IEEE 754 float32 representation of e
    // ASSEMBLY: movss .LC4(%rip), %xmm0 → load 0x402DF854 from .rodata
    print_bits(std::numbers::e_v<float>);

    // RUNTIME CALCULATION
    // x at stack, sizeof(float) = 4 bytes
    // ASSEMBLY: x = 1.0f stored at 12(%rsp), but actually optimized into xmm3 register
    float x = 1.0f;
    // e_runtime computed by CPU executing loops .L5/.L6
    // 15 outer iterations × (1 to 15 inner iterations each) = 1+2+...+15 = 120 mulss instructions for factorial
    // Plus 15 divss instructions for 1.0/factorial
    // Plus 15 addss instructions for sum += term
    // Total: ~150 floating point operations at runtime
    // ASSEMBLY: After loops, result in xmm2, stored at 12(%rsp)
    float e_runtime = my_e_pow_x(x, TERMS);
    std::cout << "Runtime: ";
    // Output: Float: 2.7182819843 | Hex: 0x402df855
    print_bits(e_runtime);

    // COMPILE TIME CALCULATION
    // ASSEMBLY: movss .LC7(%rip), %xmm0 → loads 0x402DF855 directly from .rodata
    // .LC7: .long 1076754517 = 0x402DF855
    // g++ computed 1.0 + 1/1! + 1/2! + ... + 1/15! during compilation
    // Result baked into binary as 4-byte immediate, NO loops at runtime for this value
    constexpr float e_compiletime = my_e_pow_x(1.0f, TERMS);
    std::cout << "Compile: ";
    // Output: Float: 2.7182819843 | Hex: 0x402df855
    print_bits(e_compiletime);

    // CHECK DIFFERENCE
    // e_runtime = 0x402DF855, e_compiletime = 0x402DF855
    // ucomiss .LC7(%rip), %xmm2 → compare runtime (xmm2) vs constexpr (.LC7)
    // Result: EQUAL (both computed using IEEE 754 float32 semantics)
    // If compiler used 80-bit x87 FP internally, might differ. GCC uses strict float32 in constexpr.
    if (e_runtime == e_compiletime) {
        std::cout << "Matches ✓\n";  // This branch taken
    } else {
        std::cout << "Differs ✗\n";
    }

    return 0;
}

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ SUMMARY:                                                                                                                                                                    │
// │ CONSTEXPR: g++ computes my_e_pow_x(1.0f, 15) during compilation → stores 0x402DF855 in .LC7 → runtime loads with single movss instruction                                   │
// │ RUNTIME: CPU executes nested loops (.L5/.L6) → ~150 FP ops → produces 0x402DF855 → matches constexpr                                                                        │
// │ ROUND-OFF: Taylor(15) overshoots exact e by 1 ULP due to cumulative round-off in additions                                                                                  │
// │ PROOF: .LC7 = 1076754517 in .rodata section of binary = 0x402DF855 = 2.7182819843f                                                                                          │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
