#include <vector>
#include <iostream>
#include <iomanip>
#include <functional>
#include <cmath>

// -----------------------------------------------------------------------------
// STEP 0: MATH & MEMORY WARMUP (DO NOT SKIP)
// -----------------------------------------------------------------------------
// DATA:
//   Vector u starts at memory address 0x1000. Double = 8 bytes.
//   u = {0.0, 1.0, 4.0, 9.0, 16.0, 25.0} (Values of x^2)
//   Indices: 0    1    2    3     4     5
//   Addrs: 1000 1008 1016 1024  1032  1040
//
// PROBLEM:
//   Calculate d^2u/dx^2 at i=2 (Value 4.0).
//   Formula: (u[i-1] - 2*u[i] + u[i+1]) / 1.0
//
// EXERCISE 0.1: POINTER ARITHMETIC
//   Address of u[2] = 0x1000 + (2 * 8) = 0x1016.
//   Address of u[i-1] (u[1]) = 0x1016 - 8 = 0x1008.
//   Address of u[i+1] (u[3]) = 0x1016 + 8 = 0x1024.
//   Value at 0x1008 = ______ (Answer: 1.0)
//   Value at 0x1016 = ______ (Answer: 4.0)
//   Value at 0x1024 = ______ (Answer: 9.0)
//   Calculation: (1.0 - 2.0*4.0 + 9.0) = 1.0 - 8.0 + 9.0 = 2.0.
//
// -----------------------------------------------------------------------------
// STEP 1: THE HANDWRITTEN STENCIL (The "Fastest" Code)
// -----------------------------------------------------------------------------
// We want the compiler to generate EXACTLY these instructions:
//   MOVSD xmm0, [rdi + 8]   ; Load u[i-1] (relative to u[i-2]?? No, u[i])
//   MULSD xmm0, [weight0]
//   ADDSD xmm1, xmm0
//   ...
// No loops. No jumps. No "checking if k < N".
//
// EXERCISE 1 (Mental):
//   Imagine writing a function `stencil_fixed_3(u, i)`.
//   Return u[i-1]*1.0 + u[i]*-2.0 + u[i+1]*1.0;
//   Why is this annoying?
//   Answer: What if we want 5 points? 7 points? 9 points?
//   We have to rewrite the function every time.
//
// -----------------------------------------------------------------------------
// STEP 2: THE RUNTIME LOOP (The "Generic" Code)
// -----------------------------------------------------------------------------
// We fix the annoyance by using arrays for offsets/weights.
// offsets = {-1, 0, 1}
// weights = {1.0, -2.0, 1.0}
//
// MENTAL TRACE OF `stencil_runtime`:
//   Loop k=0:
//     Load offsets[0] (-1).
//     Compute index = i + (-1).
//     Check if index valid (optional).
//     Load u[index].
//     Load weights[0].
//     Multiply. Add to sum.
//     Increment k.
//     Compare k < 3.
//     Jump if true.
//
// WHY IS THIS SLOW?
//   1. Loop Control Overhead: (Inc k, Cmp k, Jne) x 3 times.
//   2. Memory Access Overhead: Reading `offsets` and `weights` arrays from memory (cache misses?).
//
// -----------------------------------------------------------------------------
// STEP 3: COMPILE-TIME UNROLLING (The Solution)
// -----------------------------------------------------------------------------
// We want "Generic" code (works for any N) but "Handwritten" performance (no execution of K++, CMP, JMP).
//
// HOW?
//   Template Recursion.
//   Compiler runs the "Loop" of generating code.
//   Resulting binary contains only the math, no control flow.
// -----------------------------------------------------------------------------

// 1. Runtime Stencil (The "Slow" Way)
double stencil_runtime(const std::vector<double>& u, int i,
                       const std::vector<int>& offsets,
                       const std::vector<double>& weights) {
    double sum = 0.0;
    // EXERCISE: Write this loop.
    // Use `offsets[k]` and `weights[k]`.
    for (size_t k = 0; k < offsets.size(); ++k) {
        sum += u[i + offsets[k]] * weights[k];
    }
    return sum;
}

// 2. Compile-Time Unroller
// ------------------------
// We need a structure that takes an integer N and "explodes" it into N calls.
//
// Unroller<2>::execute(f) should call:
//   f(2);
//   Unroller<1>::execute(f);
//
// Unroller<1>::execute(f) should call:
//   f(1);
//   Unroller<0>::execute(f);
//
// Unroller<0>::execute(f) should call:
//   f(0);
//   Unroller<-1>::execute(f); --> TERMINATE.

template <int N, typename F>
struct Unroller {
    static void execute(F f) {
        // Run the current iteration Logic
        f(N);
        // Recurse to the next iteration (at compile time!)
        Unroller<N - 1, F>::execute(f);
    }
};

// TERMINATION CASE (Base Case)
// When N becomes -1, stop recursion. Function does is empty.
template <typename F>
struct Unroller<-1, F> {
    static void execute(F /*f*/) {
        // DO NOTHING. Recursion stops here.
        // This function compiles to 0 instructions.
    }
};

template <int Count, typename F>
void unrolled_loop(F f) {
    // Start at Count-1 (e.g., if Size 3, start at index 2).
    Unroller<Count - 1, F>::execute(f);
}

// 3. The "Unrolled" Stencil Function
// ----------------------------------
// StencilSize must be known at compile time (Template Argument).
template<int StencilSize>
double stencil_compiled(const std::vector<double>& u, int i,
                        const std::vector<int>& offsets,
                        const std::vector<double>& weights) {
    double sum = 0.0;
    
    // We define a Lambda that represents ONE iteration.
    // The compiler will inline this lambda into the unrolled calls.
    auto computation = [&](int k) {
        // PURE MATH. NO LOOP CONTROL.
        // Compiler knows 'k' is 2, then 1, then 0 constant inside each instance.
        sum += u[i + offsets[k]] * weights[k];
    };

    // TRIGGER THE EXPLOSION
    unrolled_loop<StencilSize>(computation);
    
    return sum;
}

int main() {
    // DATA SETUP
    // u(x) = x^2. u = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81}
    // Addresses:       0  1  2  3   4   5   6   7   8   9
    std::vector<double> u;
    for(int x=0; x<10; ++x) u.push_back(double(x*x));
    
    // 3-Point Stencil: Weights {1, -2, 1}, Offsets {-1, 0, 1}
    std::vector<int> offsets = {-1, 0, 1};
    std::vector<double> weights = {1.0, -2.0, 1.0};

    // TEST 1: The Loop Version
    double res_runtime = stencil_runtime(u, 2, offsets, weights);
    std::cout << "Runtime Loop Result: " << res_runtime 
              << " (Expected 2.0)" << std::endl;

    // TEST 2: The Unrolled Version
    // We MUST pass <3> as template argument. 
    // If we passed a variable 'n', it wouldn't compile!
    // Why? Template args must be CONSTANT.
    double res_unrolled = stencil_compiled<3>(u, 2, offsets, weights);
    std::cout << "Unrolled Result:     " << res_unrolled 
              << " (Expected 2.0)" << std::endl;

    // =========================================================================
    // EXERCISES: DO BY HAND. NO LOOKING AT ANSWERS. DERIVE EVERYTHING.
    // =========================================================================
    
    // -------------------------------------------------------------------------
    // EXERCISE A: MEMORY ADDRESS CALCULATION (fill blanks)
    // -------------------------------------------------------------------------
    // Given: u starts at 0x7000. sizeof(double) = 8.
    // u = {100.0, 200.0, 300.0, 400.0, 500.0}
    //
    // A1. Address of u[0] = 0x7000 + (_____ * 8) = _________
    // A2. Address of u[3] = 0x7000 + (_____ * 8) = _________
    // A3. If pointer p = 0x7018, what is *p? ____________
    // A4. If pointer p = 0x7020, what index is that? u[_____]
    // A5. &u[4] - &u[1] = _____ bytes = _____ elements
    
    // -------------------------------------------------------------------------
    // EXERCISE B: LOOP TRACE (fill table)
    // -------------------------------------------------------------------------
    // Code: for(k=0; k<3; ++k) sum += data[k] * coeff[k];
    // data  = {5.0, 10.0, 15.0}
    // coeff = {2.0, -1.0, 3.0}
    //
    // | k | data[k] | coeff[k] | product | sum_after |
    // |---|---------|----------|---------|-----------|
    // | 0 | _______ | ________ | _______ | _________ |
    // | 1 | _______ | ________ | _______ | _________ |
    // | 2 | _______ | ________ | _______ | _________ |
    //
    // Final sum = _________

    // -------------------------------------------------------------------------
    // EXERCISE C: OFFSET ARITHMETIC (fill blanks)
    // -------------------------------------------------------------------------
    // i = 5
    // offsets = {-2, -1, 0, +1, +2}
    //
    // C1. i + offsets[0] = 5 + _____ = _____
    // C2. i + offsets[1] = 5 + _____ = _____
    // C3. i + offsets[2] = 5 + _____ = _____
    // C4. i + offsets[3] = 5 + _____ = _____
    // C5. i + offsets[4] = 5 + _____ = _____
    //
    // Which u[] elements are accessed? u[___], u[___], u[___], u[___], u[___]

    // -------------------------------------------------------------------------
    // EXERCISE D: STENCIL BY HAND (no code, just math)
    // -------------------------------------------------------------------------
    // u = {0, 1, 8, 27, 64, 125, 216}  (Values of x^3)
    // i = 3 (u[3] = 27)
    // offsets = {-1, 0, +1}
    // weights = {1.0, -2.0, 1.0}
    //
    // D1. term[0] = u[3 + (-1)] * 1.0 = u[2] * 1.0 = 8.0 * 1.0 = 8.0
    // D2. term[1] = u[3 + 0] * (-2.0) = u[3] * (-2.0) = 27.0 * (-2.0) = -54.0
    // D3. term[2] = u[3 + 1] * 1.0 = u[4] * 1.0 = 64.0 * 1.0 = 64.0
    // D4. sum = 8.0 + (-54.0) + 64.0 = 18.0
    //
    // D5. True 2nd derivative of x^3 at x=3 is d^2(x^3)/dx^2 = 6x = 18 at x=3.
    // D6. Does stencil match? (yes/no): yes

    // -------------------------------------------------------------------------
    // EXERCISE E: ASSEMBLY MATCHING (draw arrows to connect)
    // -------------------------------------------------------------------------
    // C++ code:                        Assembly:
    //
    // B sum += u[idx] * w;               A. addq $1, %rax
    //  Ck < 3                            B. mulsd (%rcx), %xmm0
    //  A ++k                              C. cmpq $3, %rax
    // E u[idx]                           D. addsd %xmm0, %xmm1
    //                                  E. movsd (%rdi,%rdx,8), %xmm0
    //
    // Match: sum+=... → ___   k<3 → ___   ++k → ___   u[idx] → ___

    // -------------------------------------------------------------------------
    // EXERCISE F: TEMPLATE INSTANTIATION TRACE (fill call stack)
    // -------------------------------------------------------------------------
    // Code: unrolled_loop<4>(myFunc);
    // Unroller starts at Count-1 = 4-1 = 3.
    //
    // Call 1: Unroller<3_____>::execute → calls myFunc(3)
    // Call 2: Unroller<_2____>::execute → calls myFunc(2)
    // Call 3: Unroller<__1___>::execute → calls myFunc(1)
    // Call 4: Unroller<___0__>::execute → calls myFunc(0)
    // Call 5: Unroller<_____>::execute → _____________ (what happens?)
    //
    // Total template instantiations generated by compiler: _____

    // -------------------------------------------------------------------------
    // EXERCISE G: OVERHEAD COUNT (calculate)
    // -------------------------------------------------------------------------
    // Loop runs N = 7 iterations.
    // Per iteration: 1 INC + 1 CMP + 1 JMP = 3 overhead instructions.
    // Per iteration: 5 useful instructions (load, load, mul, add, store).
    //
    // G1. Total overhead instructions = 3 * _____ = _____
    // G2. Total useful instructions   = 5 * _____ = _____  
    // G3. Total instructions          = _____ + _____ = _____
    // G4. Overhead percentage         = _____ / _____ = _____% 
    // G5. If CPU runs at 3 GHz, how many nanoseconds wasted? _____ / 3 = _____ ns

    // -------------------------------------------------------------------------
    // EXERCISE H: PREDICT COMPILER BEHAVIOR (circle one)
    // -------------------------------------------------------------------------
    // H1. for(int k=0; k<5; ++k)            → Compiler unrolls? (YES / NO / MAYBE)
    // H2. for(int k=0; k<vec.size(); ++k)   → Compiler unrolls? (YES / NO / MAYBE)
    // H3. for(int k=0; k<N; ++k) where N is template param → (YES / NO / MAYBE)
    // H4. for(int k=0; k<argc; ++k)         → Compiler unrolls? (YES / NO / MAYBE)
    //
    // WHY for each answer (1 word): 
    // H1: ____________  H2: ____________  H3: ____________  H4: ____________

    // -------------------------------------------------------------------------
    // EXERCISE I: FIND THE BUG (what goes wrong?)
    // -------------------------------------------------------------------------
    // offsets has 3 elements: {-1, 0, +1}
    // weights has 3 elements: {1.0, -2.0, 1.0}
    // Code: stencil_compiled<5>(u, 4, offsets, weights);
    //
    // I1. Unroller calls: f(4), f(3), f(2), f(1), f(0).
    // I2. f(4) tries to access offsets[_____] → valid? (YES / NO)
    // I3. f(3) tries to access offsets[_____] → valid? (YES / NO)
    // I4. What happens at runtime? ________________________
    // I5. Does compiler catch this error? (YES / NO) Why? _______________

    // -------------------------------------------------------------------------
    // EXERCISE J: WRITE THE ASSEMBLY (by hand, no compiler)
    // -------------------------------------------------------------------------
    // Convert this to assembly (use movsd, mulsd, addsd):
    //
    // double a = arr[0];  // arr at %rdi
    // double b = arr[1];
    // double c = a * b;
    //
    // J1. movsd (%rdi), %xmm0    ; load arr[0]
    // J2. movsd (%rdi+8), %xmm1    ; load arr[1]  
    // J3. mulsd %xmm1, %xmm0      ; multiply
    // J4. Result is in register: %xmm0

    return 0;
}
