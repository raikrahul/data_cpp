// 60_constexpr_chain_and_fallback.cpp
//
// QUESTIONS ANSWERED:
// Q1: Why compiler error with runtime variable in constexpr function?
// Q2: But coeff(dyn_x, dyn_y) works - why?
// Q3: Can constexpr function call another constexpr function?
//
// ANSWERS:
// A1: Error ONLY if you assign to constexpr VARIABLE
// A2: coeff(dyn_x, dyn_y) works because result assigned to REGULAR variable
// A3: YES! constexpr functions can call other constexpr functions

#include <iostream>

// ┌─────────────────────────────────────────────────────────────────────────────────────────┐
// │ CONSTEXPR CHAIN: square() calls nothing, cube() calls square()                         │
// └─────────────────────────────────────────────────────────────────────────────────────────┘

constexpr int square(int n) {
    return n * n;
    // What: n*n
    // Why: Base function in chain
    // Where: May be inlined into cube() or main()
    // Who: Compiler interpreter
    // When: Compile time (if args known) or runtime (if args unknown)
    // Without: Nothing - leaf function
    // Which: movl $(n*n), %esi if compile-time
}

constexpr int cube(int n) {
    return n * square(n);  // ← CONSTEXPR CALLING CONSTEXPR! Valid.
    // What: n * n * n = n³
    // Why: Demonstrate constexpr chain
    // Where: Compiler evaluates square(n) first, then multiplies by n
    // Who: Compiler interpreter (if compile-time) or CPU (if runtime)
    // When: Compile time if n is literal, runtime if n is from cin
    // Without: Two function calls at runtime if computed at compile-time
    // Which: movl $(n³), %esi if compile-time
    //
    // TRACE for cube(3):
    // Step 1: n = 3
    // Step 2: Call square(3) → 3*3 = 9
    // Step 3: Return 3 * 9 = 27
    // Result: 27 → movl $27, %esi
}

constexpr int sum_of_cubes(int a, int b) {
    return cube(a) + cube(b);  // ← CONSTEXPR CALLING CONSTEXPR! Valid.
    // TRACE for sum_of_cubes(2, 3):
    // Step 1: cube(2) → 2 * square(2) → 2 * 4 = 8
    // Step 2: cube(3) → 3 * square(3) → 3 * 9 = 27
    // Step 3: 8 + 27 = 35
    // Result: 35 → movl $35, %esi
}

int main() {
    // ┌─────────────────────────────────────────────────────────────────────────────────────┐
    // │ CASE 1: COMPILE-TIME - All literals                                                 │
    // │ constexpr VARIABLE = constexpr FUNCTION(LITERALS)                                   │
    // │ RESULT: Compiler computes, bakes result as immediate                                │
    // └─────────────────────────────────────────────────────────────────────────────────────┘
    constexpr int a = cube(3);           // 3³ = 27 → movl $27, %esi
    constexpr int b = sum_of_cubes(2,3); // 8 + 27 = 35 → movl $35, %esi
    
    static_assert(a == 27, "cube(3) must be 27");
    static_assert(b == 35, "sum_of_cubes(2,3) must be 35");
    
    std::cout << "Compile-time a: " << a << "\n";
    std::cout << "Compile-time b: " << b << "\n";

    // ┌─────────────────────────────────────────────────────────────────────────────────────┐
    // │ CASE 2: RUNTIME - cin values, REGULAR variable                                      │
    // │ REGULAR VARIABLE = constexpr FUNCTION(RUNTIME VALUES)                               │
    // │ RESULT: CPU executes function at runtime                                            │
    // └─────────────────────────────────────────────────────────────────────────────────────┘
    int x, y;
    std::cin >> x >> y;
    
    int c = cube(x);             // ← VALID! Regular variable, runtime call
    int d = sum_of_cubes(x, y);  // ← VALID! Regular variable, runtime call
    
    std::cout << "Runtime c=cube(" << x << "): " << c << "\n";
    std::cout << "Runtime d=sum_of_cubes(" << x << "," << y << "): " << d << "\n";

    // ┌─────────────────────────────────────────────────────────────────────────────────────┐
    // │ CASE 3: ERROR - cin values, CONSTEXPR variable                                      │
    // │ constexpr VARIABLE = constexpr FUNCTION(RUNTIME VALUES)                             │
    // │ RESULT: COMPILE ERROR!                                                              │
    // └─────────────────────────────────────────────────────────────────────────────────────┘
    // UNCOMMENT TO SEE ERROR:
    // constexpr int e = cube(x);  // ERROR: x is not a constant expression
    //
    // WHY ERROR:
    // constexpr VARIABLE demands compile-time value
    // x is from cin → unknown at compile time
    // Compiler cannot compute cube(x) → cannot assign to constexpr e
    // 
    // THE KEY DISTINCTION:
    // ┌─────────────────────────────────────────────────────────────────────────────────────┐
    // │ constexpr FUNCTION = "I CAN run at compile time IF args are known"                 │
    // │ constexpr VARIABLE = "I MUST have compile-time value"                              │
    // │                                                                                     │
    // │ FUNCTION + RUNTIME ARGS → Degrades to runtime call → OK                            │
    // │ VARIABLE + RUNTIME ARGS → Cannot compute → ERROR                                   │
    // └─────────────────────────────────────────────────────────────────────────────────────┘

    return 0;
}

// ┌─────────────────────────────────────────────────────────────────────────────────────────┐
// │ EXPECTED ASSEMBLY (compile-time cases):                                                 │
// │                                                                                         │
// │ constexpr int a = cube(3):                                                              │
// │   NO call to cube()                                                                     │
// │   NO call to square()                                                                   │
// │   JUST: movl $27, %esi                                                                  │
// │                                                                                         │
// │ constexpr int b = sum_of_cubes(2,3):                                                    │
// │   NO call to sum_of_cubes()                                                             │
// │   NO call to cube() (twice)                                                             │
// │   NO call to square() (twice)                                                           │
// │   JUST: movl $35, %esi                                                                  │
// │                                                                                         │
// │ ENTIRE CHAIN of 5 function calls → 1 immediate value                                   │
// ├─────────────────────────────────────────────────────────────────────────────────────────┤
// │ EXPECTED ASSEMBLY (runtime cases):                                                      │
// │                                                                                         │
// │ int c = cube(x):                                                                        │
// │   movl (%rsp), %edi        ← Load x from stack                                         │
// │   call _Z4cubei            ← Actual function call                                       │
// │   movl %eax, (%rsp+4)      ← Store result in c                                          │
// │                                                                                         │
// │ int d = sum_of_cubes(x, y):                                                             │
// │   movl (%rsp), %edi        ← Load x                                                    │
// │   movl (%rsp+4), %esi      ← Load y                                                    │
// │   call _Z12sum_of_cubesii  ← Actual function call                                      │
// │   movl %eax, (%rsp+8)      ← Store result in d                                          │
// └─────────────────────────────────────────────────────────────────────────────────────────┘

// ┌─────────────────────────────────────────────────────────────────────────────────────────┐
// │ WHY CONSTEXPR CAN CALL CONSTEXPR:                                                       │
// │                                                                                         │
// │ Compiler's interpreter can evaluate ANY constexpr function                             │
// │ If cube() calls square(), interpreter just evaluates square() first                    │
// │ No special restriction - just needs ALL functions in chain to be constexpr            │
// │                                                                                         │
// │ INVALID:                                                                                │
// │ constexpr int bad(int n) {                                                              │
// │     return n * some_runtime_function(n);  // ERROR: non-constexpr call                 │
// │ }                                                                                       │
// │                                                                                         │
// │ VALID:                                                                                  │
// │ constexpr int good(int n) {                                                             │
// │     return n * another_constexpr_function(n);  // OK: constexpr calls constexpr       │
// │ }                                                                                       │
// └─────────────────────────────────────────────────────────────────────────────────────────┘
