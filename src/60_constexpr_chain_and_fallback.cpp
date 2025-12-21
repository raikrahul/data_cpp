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
// │ REAL ASSEMBLY FROM YOUR MACHINE (g++ -O2 -std=c++20 -fno-inline):                       │
// │                                                                                         │
// │ === COMPILE-TIME CASES (in main) ===                                                    │
// │                                                                                         │
// │ constexpr int a = cube(3):                                                              │
// │   NO call to cube()                                                                     │
// │   NO call to square()                                                                   │
// │   JUST: movl    $27, %esi   ← 0x1B = 27 = 3³ BAKED                                      │
// │                                                                                         │
// │ constexpr int b = sum_of_cubes(2,3):                                                    │
// │   NO call to sum_of_cubes()                                                             │
// │   NO call to cube() (twice)                                                             │
// │   NO call to square() (twice)                                                           │
// │   JUST: movl    $35, %esi   ← 0x23 = 35 = 8+27 BAKED                                    │
// │                                                                                         │
// │ ENTIRE CHAIN of 5 function calls → 2 immediate values                                  │
// ├─────────────────────────────────────────────────────────────────────────────────────────┤
// │ === RUNTIME CASES (with cin input x,y) ===                                              │
// │                                                                                         │
// │ int c = cube(x):                                                                        │
// │   movl    (%rsp), %r12d       ← Load x from stack (offset 0)                            │
// │   movl    %r12d, %edi         ← Copy x to arg register                                  │
// │   call    _Z4cubei            ← Actual call to cube(x)                                  │
// │   movl    %eax, %r14d         ← Store result in r14d (c)                                │
// │                                                                                         │
// │ int d = sum_of_cubes(x, y):                                                             │
// │   movl    4(%rsp), %esi       ← Load y from stack (offset 4)                            │
// │   movl    %r12d, %edi         ← x still in r12d, copy to arg1                           │
// │   call    _Z12sum_of_cubesii  ← Actual call to sum_of_cubes(x,y)                        │
// │   movl    %eax, %r12d         ← Store result in r12d (d)                                │
// ├─────────────────────────────────────────────────────────────────────────────────────────┤
// │ === FUNCTION BODIES (runtime versions) ===                                              │
// │                                                                                         │
// │ _Z6squarei (square):                                                                    │
// │   endbr64                                                                               │
// │   imull   %edi, %edi          ← n * n                                                   │
// │   movl    %edi, %eax          ← Move result to return register                          │
// │   ret                                                                                   │
// │                                                                                         │
// │ _Z4cubei (cube):                                                                        │
// │   endbr64                                                                               │
// │   pushq   %rbx                                                                          │
// │   movl    %edi, %ebx          ← Save n in rbx                                           │
// │   call    _Z6squarei          ← Call square(n)                                          │
// │   imull   %ebx, %eax          ← n * square(n) = n * n² = n³                             │
// │   popq    %rbx                                                                          │
// │   ret                                                                                   │
// │                                                                                         │
// │ _Z12sum_of_cubesii (sum_of_cubes):                                                      │
// │   endbr64                                                                               │
// │   pushq   %rbp                                                                          │
// │   movl    %esi, %ebp          ← Save b in rbp                                           │
// │   pushq   %rbx                                                                          │
// │   subq    $8, %rsp                                                                      │
// │   call    _Z4cubei            ← Call cube(a) - a already in %edi                        │
// │   movl    %ebp, %edi          ← Move b to arg register                                  │
// │   movl    %eax, %ebx          ← Save cube(a) result in rbx                              │
// │   call    _Z4cubei            ← Call cube(b)                                            │
// │   addq    $8, %rsp                                                                      │
// │   addl    %ebx, %eax          ← cube(a) + cube(b)                                       │
// │   popq    %rbx                                                                          │
// │   popq    %rbp                                                                          │
// │   ret                                                                                   │
// └─────────────────────────────────────────────────────────────────────────────────────────┘

// ┌─────────────────────────────────────────────────────────────────────────────────────────┐
// │ REAL OUTPUT FROM YOUR MACHINE (input: 3 4):                                             │
// │   Compile-time a: 27                                                                    │
// │   Compile-time b: 35                                                                    │
// │   Runtime c=cube(3): 27                                                                 │
// │   Runtime d=sum_of_cubes(3,4): 91 ← 27 + 64 = 91                                        │
// ├─────────────────────────────────────────────────────────────────────────────────────────┤
// │ CALL GRAPH for sum_of_cubes(3,4) at runtime:                                            │
// │   sum_of_cubes(3,4)                                                                     │
// │       ├── cube(3)                                                                       │
// │       │       └── square(3) → imull 3,3 → 9                                             │
// │       │       → imull 3,9 → 27                                                          │
// │       ├── cube(4)                                                                       │
// │       │       └── square(4) → imull 4,4 → 16                                            │
// │       │       → imull 4,16 → 64                                                         │
// │       └── addl 27,64 → 91                                                               │
// │                                                                                         │
// │ Total instructions: 2 calls + 4 imull + 1 addl = 7 operations                          │
// │ Saved at compile-time: ALL 7 operations → just movl $35                                │
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

