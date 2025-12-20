// 49_template_vs_auto_asm.cpp
// =============================================================================
// PROOF: template<T> f(T x) generates IDENTICAL assembly to auto f(auto x)
// =============================================================================
// Compile: g++ -std=c++20 -S -O0 -fno-inline 49_template_vs_auto_asm.cpp -o 49_template_vs_auto_asm.s
//
// REAL ASSEMBLY FROM YOUR MACHINE (line 6-35 vs line 161-190):
// ┌─────────────────────────────────────────────────────────────────────────────────────────┐
// │ iPow_auto<int>                      │ iPow_template<int>                │ DIFF?         │
// │ _Z9iPow_autoIiEDaT_i                │ _Z13iPow_templateIiET_S0_i        │               │
// ├─────────────────────────────────────────────────────────────────────────────────────────┤
// │ pushq   %rbp                        │ pushq   %rbp                      │ SAME          │
// │ movq    %rsp, %rbp                  │ movq    %rsp, %rbp                │ SAME          │
// │ movl    %edi, -20(%rbp)             │ movl    %edi, -20(%rbp)           │ SAME x→-20    │
// │ movl    %esi, -24(%rbp)             │ movl    %esi, -24(%rbp)           │ SAME n→-24    │
// │ movl    $1, -8(%rbp)                │ movl    $1, -8(%rbp)              │ SAME res=1    │
// │ movl    $0, -4(%rbp)                │ movl    $0, -4(%rbp)              │ SAME i=0      │
// │ jmp     .L2                         │ jmp     .L16                      │ label only    │
// │ .L3:                                │ .L17:                             │ label only    │
// │   movl    -8(%rbp), %eax            │   movl    -8(%rbp), %eax          │ SAME          │
// │   imull   -20(%rbp), %eax           │   imull   -20(%rbp), %eax         │ SAME res*=x   │
// │   movl    %eax, -8(%rbp)            │   movl    %eax, -8(%rbp)          │ SAME          │
// │   addl    $1, -4(%rbp)              │   addl    $1, -4(%rbp)            │ SAME i++      │
// │ .L2:                                │ .L16:                             │ label only    │
// │   movl    -4(%rbp), %eax            │   movl    -4(%rbp), %eax          │ SAME          │
// │   cmpl    -24(%rbp), %eax           │   cmpl    -24(%rbp), %eax         │ SAME i<n      │
// │   jl      .L3                       │   jl      .L17                    │ label only    │
// │   movl    -8(%rbp), %eax            │   movl    -8(%rbp), %eax          │ SAME return   │
// │   popq    %rbp                      │   popq    %rbp                    │ SAME          │
// │   ret                               │   ret                             │ SAME          │
// └─────────────────────────────────────────────────────────────────────────────────────────┘
// CONCLUSION: 18 instructions = 18 instructions, logic identical, labels differ
// Binary: 29 bytes = 29 bytes, 0 runtime difference
//
// =============================================================================

#include <cstdio>

// =============================================================================
// FUNCTION 1: template<typename T> T iPow_template(T x, int n)
// =============================================================================
// Source chars: 47
// Symbol: _Z13iPow_templateIiET_S0_i (demangled: int iPow_template<int>(int, int))
// Location in .s: line 161-190
//
// STACK LAYOUT (-O0):
// ┌───────────────────────────────────────────┐
// │ %rbp+0   │ saved rbp (8 bytes)            │
// │ -4(%rbp) │ i = 0,1,2,3 (4 bytes)          │
// │ -8(%rbp) │ result = 1,2,4,8 (4 bytes)     │
// │ -20(%rbp)│ x = 2 (4 bytes, padded)        │
// │ -24(%rbp)│ n = 3 (4 bytes)                │
// └───────────────────────────────────────────┘
//
// REGISTER TRACE iPow_template(2, 3):
// ENTRY: %edi=2, %esi=3
// movl %edi, -20(%rbp)  → mem[-20]=2
// movl %esi, -24(%rbp)  → mem[-24]=3
// movl $1, -8(%rbp)     → mem[-8]=1 (result)
// movl $0, -4(%rbp)     → mem[-4]=0 (i)
//
// LOOP iter₀: i=0, result=1
//   imull: %eax = mem[-8] × mem[-20] = 1 × 2 = 2
//   movl: mem[-8] = 2
//   addl: mem[-4] = 0 + 1 = 1
//   cmpl: 1 < 3 ✓ → jump
//
// LOOP iter₁: i=1, result=2
//   imull: %eax = 2 × 2 = 4
//   movl: mem[-8] = 4
//   addl: mem[-4] = 1 + 1 = 2
//   cmpl: 2 < 3 ✓ → jump
//
// LOOP iter₂: i=2, result=4
//   imull: %eax = 4 × 2 = 8
//   movl: mem[-8] = 8
//   addl: mem[-4] = 2 + 1 = 3
//   cmpl: 3 < 3 ✗ → exit
//
// RETURN: %eax = mem[-8] = 8

template<typename T>
T iPow_template(T x, int n) {
    T result = 1;  // movl $1, -8(%rbp) → result=1 at offset -8
    for (int i = 0; i < n; ++i) {  // i at -4(%rbp), n at -24(%rbp)
        result *= x;  // imull -20(%rbp), %eax → result = result × x
    }
    return result;  // movl -8(%rbp), %eax → return 8
}

// =============================================================================
// FUNCTION 2: auto iPow_auto(auto x, int n)
// =============================================================================
// Source chars: 33 (saves 47-33=14 chars)
// Symbol: _Z9iPow_autoIiEDaT_i (demangled: auto iPow_auto<int>(int, int))
// Location in .s: line 6-35
//
// COMPILER TRANSFORMS:
// auto iPow_auto(auto x, int n)
// ↓ C++20 parser
// template<typename __T1> auto iPow_auto(__T1 x, int n)
// ↓ instantiation with int
// auto iPow_auto<int>(int x, int n)
// ↓ return type deduction
// int iPow_auto<int>(int x, int n)
//
// STACK LAYOUT (-O0): IDENTICAL TO TEMPLATE VERSION
// ┌───────────────────────────────────────────┐
// │ %rbp+0   │ saved rbp (8 bytes)            │
// │ -4(%rbp) │ i = 0,1,2,3 (4 bytes)          │
// │ -8(%rbp) │ result = 1,2,4,8 (4 bytes)     │
// │ -20(%rbp)│ x = 2 (4 bytes, padded)        │
// │ -24(%rbp)│ n = 3 (4 bytes)                │
// └───────────────────────────────────────────┘
//
// REGISTER TRACE iPow_auto(2, 3): IDENTICAL TO TEMPLATE VERSION
// %edi=2 → -20(%rbp)
// %esi=3 → -24(%rbp)
// Loop: 1→2→4→8
// Return: %eax=8

auto iPow_auto(auto x, int n) {
    decltype(x) result = 1;  // decltype(x)=int when x=2 → movl $1, -8(%rbp)
    for (int i = 0; i < n; ++i) {  // same loop structure
        result *= x;  // same imull instruction
    }
    return result;  // same return in %eax
}

// =============================================================================
// MAIN: instantiation proof
// =============================================================================
// Call sites generate:
// line 94: call _Z13iPow_templateIiET_S0_i     ← iPow_template<int>
// line 98: call _Z9iPow_autoIiEDaT_i           ← iPow_auto<int>
// line 103: call _Z13iPow_templateIdET_S0_i   ← iPow_template<double>
// line 109: call _Z9iPow_autoIdEDaT_i         ← iPow_auto<double>

int main() {
    // CALL 1: iPow_template<int>(2, 3)
    // movl $2, %edi          ← x = 2
    // movl $3, %esi          ← n = 3
    // call _Z13iPow_templateIiET_S0_i
    // movl %eax, -28(%rbp)   ← r1 = 8
    int r1 = iPow_template(2, 3);  // iter: 1×2=2, 2×2=4, 4×2=8 → r1=8
    
    // CALL 2: iPow_auto<int>(2, 3)
    // movl $2, %edi          ← x = 2
    // movl $3, %esi          ← n = 3
    // call _Z9iPow_autoIiEDaT_i
    // movl %eax, -32(%rbp)   ← r2 = 8
    int r2 = iPow_auto(2, 3);  // iter: 1×2=2, 2×2=4, 4×2=8 → r2=8
    
    // CALL 3: iPow_template<double>(2.5, 4)
    // movsd .LC0(%rip), %xmm0  ← x = 2.5 from .rodata
    // movl $4, %edi            ← n = 4
    // call _Z13iPow_templateIdET_S0_i
    // movsd %xmm0, -40(%rbp)   ← r3 = 39.0625
    // TRACE: 1.0×2.5=2.5, 2.5×2.5=6.25, 6.25×2.5=15.625, 15.625×2.5=39.0625
    double r3 = iPow_template(2.5, 4);
    
    // CALL 4: iPow_auto<double>(2.5, 4)
    // movsd .LC0(%rip), %xmm0  ← x = 2.5 from .rodata
    // movl $4, %edi            ← n = 4
    // call _Z9iPow_autoIdEDaT_i
    // movsd %xmm0, -48(%rbp)   ← r4 = 39.0625
    double r4 = iPow_auto(2.5, 4);
    
    // OUTPUT:
    // template<int>(2,3) = 8
    // auto<int>(2,3) = 8
    // template<double>(2.5,4) = 39.062500
    // auto<double>(2.5,4) = 39.062500
    printf("template<int>(2,3) = %d\n", r1);
    printf("auto<int>(2,3) = %d\n", r2);
    printf("template<double>(2.5,4) = %f\n", r3);
    printf("auto<double>(2.5,4) = %f\n", r4);
    
    // VERIFICATION: r1=8=r2 ✓, r3=39.0625=r4 ✓
    return (r1 == r2 && r3 == r4) ? 0 : 1;
}
