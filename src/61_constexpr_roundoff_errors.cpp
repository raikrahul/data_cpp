// 61_constexpr_roundoff_errors.cpp
//
// QUESTION: Where do round-off errors occur in constexpr?
// ANSWER: At COMPILE TIME, inside the compiler's floating-point interpreter
//
// The binary contains an ALREADY-ROUNDED result. No additional rounding at runtime.
//
// NOTE: std::sin is NOT constexpr in C++20. We use custom constexpr sin via Taylor series.

#include <iostream>
#include <iomanip>
#include <numbers>
#include <cmath>
#include <cstdint>
#include <chrono>

// ┌─────────────────────────────────────────────────────────────────────────────────────────┐
// │ CONSTEXPR TAYLOR SERIES FOR sin(x):                                                     │
// │ sin(x) = x - x³/3! + x⁵/5! - x⁷/7! + x⁹/9! - ...                                       │
// │                                                                                         │
// │ Each term: (-1)^n * x^(2n+1) / (2n+1)!                                                 │
// │                                                                                         │
// │ ROUND-OFF ERROR SOURCES:                                                                │
// │ 1. Representation of PI: 3.14159265358979... → float has 23-bit mantissa              │
// │ 2. Each multiplication: result rounded to nearest representable float                  │
// │ 3. Each division: result rounded                                                        │
// │ 4. Each addition/subtraction: result rounded                                            │
// │                                                                                         │
// │ All rounding happens in COMPILER's interpreter, NOT at runtime                         │
// └─────────────────────────────────────────────────────────────────────────────────────────┘

constexpr float constexpr_pow(float base, int exp) {
    float result = 1.0f;
    for (int i = 0; i < exp; ++i) {
        result *= base;  // ← ROUND-OFF at each multiplication
    }
    return result;
}

constexpr float constexpr_factorial(int n) {
    float result = 1.0f;
    for (int i = 2; i <= n; ++i) {
        result *= static_cast<float>(i);  // ← ROUND-OFF for large factorials
    }
    return result;
}

constexpr float constexpr_sin(float x, int terms = 10) {
    // Taylor series: sin(x) = Σ (-1)^n * x^(2n+1) / (2n+1)!
    float result = 0.0f;
    for (int n = 0; n < terms; ++n) {
        int exp = 2 * n + 1;                    // 1, 3, 5, 7, 9, ...
        float sign = (n % 2 == 0) ? 1.0f : -1.0f;
        float term = sign * constexpr_pow(x, exp) / constexpr_factorial(exp);
        result += term;  // ← ROUND-OFF at each addition
        //
        // TRACE for sin(1.0):
        // n=0: +x^1/1! = +1.0/1 = +1.0
        // n=1: -x^3/3! = -1.0/6 = -0.166667
        // n=2: +x^5/5! = +1.0/120 = +0.00833333
        // n=3: -x^7/7! = -1.0/5040 = -0.000198413
        // n=4: +x^9/9! = +1.0/362880 = +0.00000275573
        // ...
        // result = 0.841471... (each step has round-off)
    }
    return result;
}

// Helper to print float as hex bits
void print_float_bits(float f, const char* name) {
    union { float f; uint32_t u; } conv;
    conv.f = f;
    std::cout << std::setw(20) << name << ": " 
              << std::fixed << std::setprecision(20) << f 
              << " (0x" << std::hex << conv.u << std::dec << ")\n";
}

int main() {
    // ┌─────────────────────────────────────────────────────────────────────────────────────┐
    // │ COMPILE-TIME COMPUTATIONS                                                           │
    // │ All round-off happens in compiler's interpreter during compilation                  │
    // └─────────────────────────────────────────────────────────────────────────────────────┘
    
    constexpr float pi_f = std::numbers::pi_v<float>;     // 3.14159265... → float
    constexpr float sin_of_1 = constexpr_sin(1.0f);        // sin(1) ≈ 0.8414709848...
    constexpr float sin_of_pi = constexpr_sin(pi_f);       // sin(π) = 0.0 (exact math)
    constexpr float sin_of_half_pi = constexpr_sin(pi_f / 2.0f);  // sin(π/2) = 1.0 (exact math)
    
    std::cout << "=== COMPILE-TIME RESULTS (round-off already happened in compiler) ===\n\n";
    
    print_float_bits(pi_f, "PI (float)");
    print_float_bits(sin_of_1, "sin(1.0)");
    print_float_bits(sin_of_pi, "sin(PI)");
    print_float_bits(sin_of_half_pi, "sin(PI/2)");
    
    std::cout << "\n=== RUNTIME RESULTS (using std::sin from cmath) ===\n\n";
    
    float runtime_sin_1 = std::sin(1.0f);
    float runtime_sin_pi = std::sin(pi_f);
    float runtime_sin_half_pi = std::sin(pi_f / 2.0f);
    
    print_float_bits(runtime_sin_1, "std::sin(1.0)");
    print_float_bits(runtime_sin_pi, "std::sin(PI)");
    print_float_bits(runtime_sin_half_pi, "std::sin(PI/2)");
    
    std::cout << "\n=== ROUND-OFF ERROR ANALYSIS ===\n\n";
    
    // sin(π) should be exactly 0.0 mathematically
    std::cout << "MATHEMATICAL sin(π) = 0.0 EXACTLY\n";
    std::cout << "constexpr sin(π)    = " << std::scientific << sin_of_pi << "\n";
    std::cout << "std::sin(π)         = " << std::scientific << runtime_sin_pi << "\n";
    std::cout << "Difference (constexpr vs std): " << std::abs(sin_of_pi - runtime_sin_pi) << "\n\n";
    
    // sin(π/2) should be exactly 1.0 mathematically
    std::cout << "MATHEMATICAL sin(π/2) = 1.0 EXACTLY\n";
    std::cout << "constexpr sin(π/2)    = " << std::fixed << std::setprecision(20) << sin_of_half_pi << "\n";
    std::cout << "std::sin(π/2)         = " << std::fixed << std::setprecision(20) << runtime_sin_half_pi << "\n";
    std::cout << "Error constexpr: " << std::scientific << std::abs(sin_of_half_pi - 1.0f) << "\n";
    std::cout << "Error std::sin:  " << std::scientific << std::abs(runtime_sin_half_pi - 1.0f) << "\n\n";
    
    // ┌─────────────────────────────────────────────────────────────────────────────────────┐
    // │ WHERE IS THE ROUND-OFF?                                                             │
    // │                                                                                     │
    // │ 1. PI representation:                                                               │
    // │    π = 3.14159265358979323846...                                                   │
    // │    float π = 3.14159274 (rounded to 23-bit mantissa)                               │
    // │    Error = 0.00000008... from PI representation alone                              │
    // │                                                                                     │
    // │ 2. Taylor series computation:                                                       │
    // │    Each pow() call: multiple multiplications, each rounded                         │
    // │    Each factorial() call: for large n, exceeds float precision                     │
    // │    Each term addition: catastrophic cancellation possible                          │
    // │                                                                                     │
    // │ 3. WHEN does this happen:                                                          │
    // │    COMPILE TIME - compiler's FP interpreter does all operations                    │
    // │    Result stored in binary as pre-rounded immediate                                │
    // │    RUNTIME - just loads immediate, NO additional rounding                          │
    // └─────────────────────────────────────────────────────────────────────────────────────┘
    
    // ┌─────────────────────────────────────────────────────────────────────────────────────┐
    // │ BENCHMARK: CONSTEXPR vs RUNTIME                                                     │
    // └─────────────────────────────────────────────────────────────────────────────────────┘
    //
    // ┌─────────────────────────────────────────────────────────────────────────────────────┐
    // │ WHY IS YOUR constexpr_sin SLOWEST AT RUNTIME?                                       │
    // │                                                                                      │
    // │ DIAGRAM: What happens in each case                                                  │
    // │                                                                                      │
    // │ CASE 1: CONSTEXPR LOAD (2.07 ns)                                                   │
    // │ ┌─────────────────────────────────────────────────────────────────────────────────┐ │
    // │ │ COMPILE TIME (g++ running):                                                     │ │
    // │ │   constexpr_sin(3.14159274f)                                                   │ │
    // │ │   → pow(3.14,1)=3.14, pow(3.14,3)=31.0, pow(3.14,5)=306.0...                  │ │
    // │ │   → factorial(1)=1, factorial(3)=6, factorial(5)=120...                        │ │
    // │ │   → 10 terms computed by g++ = 0xb2435010                                      │ │
    // │ │   → Stored in .rodata section of binary                                        │ │
    // │ │                                                                                 │ │
    // │ │ RUN TIME (CPU executing):                                                       │ │
    // │ │   movss .LC12(%rip), %xmm0  ← 1 instruction, 4 bytes from memory              │ │
    // │ │   TIME: 2.07 ns                                                                │ │
    // │ └─────────────────────────────────────────────────────────────────────────────────┘ │
    // │                                                                                      │
    // │ CASE 2: std::sin (6.70 ns)                                                         │
    // │ ┌─────────────────────────────────────────────────────────────────────────────────┐ │
    // │ │ RUN TIME (CPU executing):                                                       │ │
    // │ │   call sinf@PLT                                                                 │ │
    // │ │   → libc uses OPTIMIZED Chebyshev approximation                               │ │
    // │ │   → SSE SIMD instructions                                                       │ │
    // │ │   → Range reduction (x mod 2π)                                                 │ │
    // │ │   → Only ~7 terms needed (better polynomial)                                   │ │
    // │ │   TIME: 6.70 ns                                                                │ │
    // │ └─────────────────────────────────────────────────────────────────────────────────┘ │
    // │                                                                                      │
    // │ CASE 3: YOUR constexpr_sin AT RUNTIME (359 ns) ← SLOWEST!                          │
    // │ ┌─────────────────────────────────────────────────────────────────────────────────┐ │
    // │ │ RUN TIME (CPU executing):                                                       │ │
    // │ │   call _Z13constexpr_sinfi                                                      │ │
    // │ │   → NAIVE Taylor series: 10 terms                                               │ │
    // │ │   → constexpr_pow: LOOP n multiplications (not optimized)                      │ │
    // │ │   → constexpr_factorial: LOOP n multiplications (not optimized)               │ │
    // │ │   → NO SIMD, NO range reduction, NO Chebyshev                                   │ │
    // │ │   TIME: 359 ns                                                                  │ │
    // │ └─────────────────────────────────────────────────────────────────────────────────┘ │
    // │                                                                                      │
    // │ WHY YOUR CODE IS SLOW:                                                              │
    // │ ┌─────────────────────────────────────────────────────────────────────────────────┐ │
    // │ │ YOUR constexpr_pow(3.14, 9) = 9 multiplications in a LOOP                     │ │
    // │ │   for (int i = 0; i < 9; ++i) result *= 3.14;                                  │ │
    // │ │   = 9 imul + 9 loop iterations + 9 stores                                      │ │
    // │ │                                                                                 │ │
    // │ │ YOUR constexpr_factorial(9) = 8 multiplications in a LOOP                     │ │
    // │ │   for (int i = 2; i <= 9; ++i) result *= i;                                   │ │
    // │ │   = 8 imul + 8 loop iterations + 8 stores                                      │ │
    // │ │                                                                                 │ │
    // │ │ PER TERM: ~17 multiplications + 17 loop iterations + 17 stores                │ │
    // │ │ 10 TERMS: ~170 multiplications + 170 loop iterations + 170 stores             │ │
    // │ │                                                                                 │ │
    // │ │ std::sin: Uses Horner's method, no loops, ~7 FMA instructions total           │ │
    // │ └─────────────────────────────────────────────────────────────────────────────────┘ │
    // │                                                                                      │
    // │ WHY CONSTEXPR IS STILL VALUABLE:                                                    │
    // │ ┌─────────────────────────────────────────────────────────────────────────────────┐ │
    // │ │ SLOW CODE RUN BY COMPILER = FREE                                               │ │
    // │ │ SLOW CODE RUN BY CPU = SLOW                                                    │ │
    // │ │                                                                                 │ │
    // │ │ When you write:                                                                │ │
    // │ │   constexpr float x = constexpr_sin(pi);                                       │ │
    // │ │ The 170 multiplications happen in g++, not in ./a.out                         │ │
    // │ │ CPU just loads 4 bytes → 2.07 ns                                               │ │
    // │ │                                                                                 │ │
    // │ │ MORAL: Constexpr code can be SLOPPY because compiler pays the price           │ │
    // │ └─────────────────────────────────────────────────────────────────────────────────┘ │
    // └─────────────────────────────────────────────────────────────────────────────────────┘
    
    std::cout << "=== BENCHMARK: CONSTEXPR vs RUNTIME (10 million iterations) ===\n\n";
    
    constexpr int ITERATIONS = 10'000'000;
    volatile float sink = 0.0f;  // Prevent optimization from eliminating loop
    
    // Benchmark CONSTEXPR (just loading pre-computed value)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            sink = sin_of_pi;  // Load pre-computed constexpr value
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto ns = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
        std::cout << "CONSTEXPR load:     " << ns / 1'000'000.0 << " ms total, "
                  << ns / ITERATIONS << " ns/iter\n";
    }
    
    // Benchmark RUNTIME (calling std::sin each time)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            sink = std::sin(pi_f);  // Compute std::sin at runtime
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto ns = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
        std::cout << "RUNTIME std::sin:   " << ns / 1'000'000.0 << " ms total, "
                  << ns / ITERATIONS << " ns/iter\n";
    }
    
    // Benchmark RUNTIME (calling our Taylor series each time)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            sink = constexpr_sin(pi_f);  // Compute Taylor series at runtime
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto ns = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
        std::cout << "RUNTIME Taylor sin: " << ns / 1'000'000.0 << " ms total, "
                  << ns / ITERATIONS << " ns/iter\n";
    }
    
    std::cout << "\nCONCLUSION: constexpr = just load, runtime = full computation\n";
    std::cout << "(sink=" << sink << " to prevent optimization)\n\n";

    std::cout << "=== TRACE: ROUND-OFF ACCUMULATION in sin(π) ===\n\n";
    
    // Show how error accumulates term by term
    float x = pi_f;
    float running_sum = 0.0f;
    for (int n = 0; n < 10; ++n) {
        int exp = 2 * n + 1;
        float sign = (n % 2 == 0) ? 1.0f : -1.0f;
        float power = constexpr_pow(x, exp);
        float fact = constexpr_factorial(exp);
        float term = sign * power / fact;
        running_sum += term;
        
        std::cout << "n=" << n << " term=" << std::scientific << std::setw(15) << term 
                  << " sum=" << std::setw(15) << running_sum << "\n";
    }
    std::cout << "\nFinal sum should be 0.0, actual = " << running_sum << "\n";
    std::cout << "This error was computed at COMPILE TIME and baked into binary.\n";
    
    return 0;
}

// ┌─────────────────────────────────────────────────────────────────────────────────────────┐
// │ SUMMARY:                                                                                │
// │                                                                                         │
// │ Q: Where do round-off errors occur?                                                    │
// │ A: In the COMPILER'S floating-point interpreter, DURING COMPILATION                   │
// │                                                                                         │
// │ The binary contains:                                                                    │
// │   movss .LC1(%rip), %xmm0   ← Load pre-rounded result from .rodata                     │
// │                                                                                         │
// │ NOT: Taylor series computation at runtime                                               │
// │                                                                                         │
// │ The 0.0000001234... error in sin(π) was computed by g++ on your machine               │
// │ and stored as a float literal in the binary. CPU just loads it.                       │
// └─────────────────────────────────────────────────────────────────────────────────────────┘
