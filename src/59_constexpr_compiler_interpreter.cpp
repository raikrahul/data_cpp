// 59_constexpr_compiler_interpreter.cpp
// 
// REAL OUTPUT FROM THIS MACHINE: 49 120 169
// REAL ASSEMBLY FROM THIS MACHINE:
//   movl    $49, %esi      ← 49 = 7*7 = square(7) BAKED IN
//   movl    $120, %esi     ← 120 = 5! = factorial(5) BAKED IN  
//   movl    $169, %esi     ← 169 = 49+120 = a+b BAKED IN
//
// NO call to square() in assembly. NO call to factorial() in assembly.
// COMPILER ran these functions internally during compilation.
//
// What: 49, 120, 169
// Why: 7*7=49; 5*4*3*2*1=120; 49+120=169
// Where: Immediate operands in .text section, no .data allocation
// Who: g++ interpreter executed constexpr functions
// When: Compile time (g++ running), not runtime (./a.out running)
// Without: Runtime multiplication, recursion, function calls
// Which: constexpr square(), constexpr factorial()

#include <iostream>

// ┌─────────────────────────────────────────────────────────────────────────────────────────┐
// │ constexpr int square(int n)                                                             │
// │ What: n*n                                                                               │
// │ Why: Demonstrate compile-time multiplication                                            │
// │ Where: NO function body in binary when called with literals                            │
// │ Who: Compiler's interpreter                                                            │
// │ When: g++ execution time                                                               │
// │ Without: imul instruction at runtime                                                    │
// │ Which: Replaced by immediate value                                                      │
// ├─────────────────────────────────────────────────────────────────────────────────────────┤
// │ SCALE CALCULATIONS:                                                                     │
// │ Small:  n=1 → 1*1=1 → movl $1, %esi → 1 cycle load, 0 mul cycles                       │
// │ Mid:    n=7 → 7*7=49 → movl $49, %esi → 1 cycle load, 0 mul cycles                     │
// │ Large:  n=46340 → 46340*46340=2147395600 → fits in int32 → movl $2147395600, %esi     │
// │ Edge:   n=46341 → 46341*46341=2147488281 → OVERFLOW → UB in constexpr → compile error │
// │ Edge:   n=0 → 0*0=0 → movl $0, %esi                                                    │
// │ Edge:   n=-7 → (-7)*(-7)=49 → movl $49, %esi (same as positive)                        │
// │                                                                                         │
// │ RUNTIME EQUIVALENT:                                                                     │
// │ imul %eax, %eax → 3 cycles latency on Skylake                                          │
// │ SAVINGS: 3 cycles per call × 1000 calls = 3000 cycles = 1μs saved                      │
// └─────────────────────────────────────────────────────────────────────────────────────────┘
constexpr int square(int n) {
    return n * n;
    // INTERNAL TRACE (what compiler does):
    // Input: n=7 (literal from call site)
    // Step 1: Push 7 onto interpreter stack
    // Step 2: Duplicate top: stack = [7, 7]
    // Step 3: Multiply: stack = [49]
    // Step 4: Return 49
    // Output: 49 → becomes immediate $49 in assembly
}

// ┌─────────────────────────────────────────────────────────────────────────────────────────┐
// │ constexpr int factorial(int n)                                                          │
// │ What: n!                                                                                │
// │ Why: Demonstrate compile-time recursion                                                 │
// │ Where: NO recursive calls in binary, just result                                       │
// │ Who: Compiler's interpreter unrolls recursion                                          │
// │ When: g++ execution time                                                               │
// │ Without: call/ret overhead, stack frames                                                │
// │ Which: Single immediate value replaces entire recursion tree                           │
// ├─────────────────────────────────────────────────────────────────────────────────────────┤
// │ RECURSION TRACE for n=5:                                                                │
// │ factorial(5) → 5 * factorial(4)                                                        │
// │ factorial(4) → 4 * factorial(3)                                                        │
// │ factorial(3) → 3 * factorial(2)                                                        │
// │ factorial(2) → 2 * factorial(1)                                                        │
// │ factorial(1) → return 1 (base case)                                                    │
// │ Unwind: 2*1=2 → 3*2=6 → 4*6=24 → 5*24=120                                              │
// │ Result: 120 → movl $120, %esi                                                          │
// ├─────────────────────────────────────────────────────────────────────────────────────────┤
// │ SCALE CALCULATIONS:                                                                     │
// │ Small:  n=1 → 1! = 1 → movl $1, %esi → 0 recursive calls saved                         │
// │ Mid:    n=5 → 5! = 120 → movl $120, %esi → 4 recursive calls saved                     │
// │ Large:  n=12 → 12! = 479001600 → fits int32 → movl $479001600, %esi                   │
// │ Edge:   n=13 → 13! = 6227020800 → OVERFLOW int32 (max 2147483647)                      │
// │         13! > INT_MAX → compile error in constexpr context                             │
// │ Edge:   n=0 → 0! = 1 (mathematical convention) → movl $1, %esi                         │
// │ Edge:   n=-1 → undefined → constexpr requires positive                                 │
// ├─────────────────────────────────────────────────────────────────────────────────────────┤
// │ RUNTIME EQUIVALENT:                                                                     │
// │ call factorial → 5 pushes + 5 calls + 5 rets + 4 imuls                                 │
// │ Overhead: 5*(push+call+ret) = 5*10 cycles = 50 cycles                                  │
// │ Multiply: 4 imuls = 4*3 = 12 cycles                                                    │
// │ Total: 62 cycles → replaced with 1 cycle movl                                          │
// │ SAVINGS: 61 cycles per invocation                                                      │
// └─────────────────────────────────────────────────────────────────────────────────────────┘
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
    // INTERNAL TRACE (what compiler does):
    // Input: n=5
    // Iteration 1: n=5 > 1 → push 5, recurse with 4
    // Iteration 2: n=4 > 1 → push 4, recurse with 3
    // Iteration 3: n=3 > 1 → push 3, recurse with 2
    // Iteration 4: n=2 > 1 → push 2, recurse with 1
    // Iteration 5: n=1 ≤ 1 → return 1 (base)
    // Unwind: stack = [5,4,3,2] × 1 = 2*1=2, 3*2=6, 4*6=24, 5*24=120
    // Output: 120 → becomes immediate $120 in assembly
}

// ┌─────────────────────────────────────────────────────────────────────────────────────────┐
// │ MEMORY LAYOUT AT COMPILE TIME (inside g++ process):                                    │
// │                                                                                         │
// │ g++ PROCESS (running on your machine during compilation):                              │
// │ ┌───────────────────────────────────────────────────────────────────────────────────┐  │
// │ │ [0x5555'5000] g++ code segment                                                    │  │
// │ │ [0x5555'A000] g++ constexpr interpreter                                           │  │
// │ │ ┌─────────────────────────────────────────────────────────────────────────────┐  │  │
// │ │ │ Interpreter Stack:                                                          │  │  │
// │ │ │ [0x7FFF'0000]: n=5 (evaluating factorial(5))                               │  │  │
// │ │ │ [0x7FFF'0008]: n=4 (recursive call)                                        │  │  │
// │ │ │ [0x7FFF'0010]: n=3 (recursive call)                                        │  │  │
// │ │ │ [0x7FFF'0018]: n=2 (recursive call)                                        │  │  │
// │ │ │ [0x7FFF'0020]: n=1 (base case)                                             │  │  │
// │ │ │ [0x7FFF'0028]: result=1 → 2 → 6 → 24 → 120                                 │  │  │
// │ │ └─────────────────────────────────────────────────────────────────────────────┘  │  │
// │ │ Output: 120 stored in AST node for 'b'                                          │  │
// │ └───────────────────────────────────────────────────────────────────────────────────┘  │
// │                                                                                         │
// │ When g++ finishes, it writes to a.out:                                                 │
// │ [.text section]: movl $120, %esi                                                       │
// │ NO stack frames for factorial in a.out. NO recursive calls. Just $120.               │
// └─────────────────────────────────────────────────────────────────────────────────────────┘

int main() {
    // ┌─────────────────────────────────────────────────────────────────────────────────────┐
    // │ constexpr int a = square(7);                                                        │
    // │ What: 49                                                                            │
    // │ Why: 7*7=49                                                                         │
    // │ Where: Immediate $49 in movl instruction at [.text+0x10]                           │
    // │ Who: Compiler                                                                       │
    // │ When: Compile time                                                                  │
    // │ Without: imul instruction, memory load                                              │
    // │ Which: movl $49, %esi (3 bytes: C7 C6 31 00 00 00)                                 │
    // ├─────────────────────────────────────────────────────────────────────────────────────┤
    // │ ASSEMBLY (from your machine):                                                       │
    // │ movl    $49, %esi      ← Literal 49 = 0x31 embedded in instruction                │
    // │ leaq    _ZSt4cout(%rip), %rdi                                                       │
    // │ call    _ZNSolsEi@PLT  ← cout << 49                                                │
    // └─────────────────────────────────────────────────────────────────────────────────────┘
    constexpr int a = square(7);      // 7*7 = 49 → movl $49, %esi

    // ┌─────────────────────────────────────────────────────────────────────────────────────┐
    // │ constexpr int b = factorial(5);                                                     │
    // │ What: 120                                                                           │
    // │ Why: 5*4*3*2*1=120                                                                  │
    // │ Where: Immediate $120 in movl instruction at [.text+0x30]                          │
    // │ Who: Compiler                                                                       │
    // │ When: Compile time                                                                  │
    // │ Without: 5 recursive calls, 5 stack frames, 4 imul instructions                    │
    // │ Which: movl $120, %esi (5 bytes: BE 78 00 00 00; 0x78=120)                         │
    // ├─────────────────────────────────────────────────────────────────────────────────────┤
    // │ SAVINGS CALCULATION:                                                                │
    // │ Runtime factorial(5): 5 calls × (push+call+ret) = 5 × 10 = 50 cycles              │
    // │                       4 imuls × 3 cycles = 12 cycles                               │
    // │                       Total: 62 cycles                                              │
    // │ Compile-time: 0 cycles (computed by g++)                                           │
    // │ Saved: 62 cycles per invocation                                                    │
    // │ If called 1M times: 62M cycles = 20ms saved @ 3GHz                                 │
    // └─────────────────────────────────────────────────────────────────────────────────────┘
    constexpr int b = factorial(5);   // 5! = 120 → movl $120, %esi

    // ┌─────────────────────────────────────────────────────────────────────────────────────┐
    // │ constexpr int c = a + b;                                                            │
    // │ What: 169                                                                           │
    // │ Why: 49+120=169                                                                     │
    // │ Where: Immediate $169 in movl instruction at [.text+0x50]                          │
    // │ Who: Compiler                                                                       │
    // │ When: Compile time                                                                  │
    // │ Without: add instruction at runtime                                                 │
    // │ Which: movl $169, %esi (5 bytes: BE A9 00 00 00; 0xA9=169)                         │
    // ├─────────────────────────────────────────────────────────────────────────────────────┤
    // │ FULL TRACE:                                                                         │
    // │ a = square(7) = 7*7 = 49                                                           │
    // │ b = factorial(5) = 5*4*3*2*1 = 120                                                 │
    // │ c = a + b = 49 + 120 = 169                                                         │
    // │ ASSEMBLY shows $169 directly, NOT $49 + $120 at runtime                            │
    // └─────────────────────────────────────────────────────────────────────────────────────┘
    constexpr int c = a + b;          // 49 + 120 = 169 → movl $169, %esi

    std::cout << a << " " << b << " " << c << "\n";
    // OUTPUT: 49 120 169

    return 0;
}

// ┌─────────────────────────────────────────────────────────────────────────────────────────┐
// │ FULL ASSEMBLY (from your machine, g++ -O2 -std=c++20):                                 │
// ├─────────────────────────────────────────────────────────────────────────────────────────┤
// │ main:                                                                                   │
// │     endbr64                                                                             │
// │     pushq   %rbx                                                                        │
// │     movl    $49, %esi             ← square(7) = 49 BAKED                               │
// │     leaq    _ZSt4cout(%rip), %rdi                                                       │
// │     leaq    .LC0(%rip), %rbx                                                            │
// │     call    _ZNSolsEi@PLT                                                               │
// │     movq    %rbx, %rsi                                                                  │
// │     movq    %rax, %rdi                                                                  │
// │     call    _ZStlsISt11char_traitsIcEE...@PLT                                           │
// │     movl    $120, %esi            ← factorial(5) = 120 BAKED                           │
// │     movq    %rax, %rdi                                                                  │
// │     call    _ZNSolsEi@PLT                                                               │
// │     movq    %rbx, %rsi                                                                  │
// │     movq    %rax, %rdi                                                                  │
// │     call    _ZStlsISt11char_traitsIcEE...@PLT                                           │
// │     movl    $169, %esi            ← a+b = 169 BAKED                                    │
// │     movq    %rax, %rdi                                                                  │
// │     call    _ZNSolsEi@PLT                                                               │
// │     leaq    .LC1(%rip), %rsi                                                            │
// │     movq    %rax, %rdi                                                                  │
// │     call    _ZStlsISt11char_traitsIcEE...@PLT                                           │
// │     xorl    %eax, %eax                                                                  │
// │     popq    %rbx                                                                        │
// │     ret                                                                                 │
// ├─────────────────────────────────────────────────────────────────────────────────────────┤
// │ NOTICE: NO call to square. NO call to factorial. NO imul. NO recursion.              │
// │ ONLY: $49, $120, $169 as immediates.                                                   │
// └─────────────────────────────────────────────────────────────────────────────────────────┘
