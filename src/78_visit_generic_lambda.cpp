// 78_visit_generic_lambda.cpp
// DERIVE: std::visit + generic lambda + duck typing pattern
// NO SOLUTIONS. BOILERPLATE ONLY. DERIVE BY HAND.

#include <iostream>
#include <variant>
#include <vector>

// ═══════════════════════════════════════════════════════════════════════════
// INPUT → OUTPUT EXAMPLE (TOP):
// ═══════════════════════════════════════════════════════════════════════════
// MyShape = variant<Circle, Rectangle> @ 0x1000
// shape.index() = 0 → Circle{x=1.0, y=2.0, r=0.5}
// intersectShape(shape, a=1.0, b=0.0) → vector<double>{0.707, -0.707}
// GOAL: Call shape.intersect(a,b) without knowing which type is inside.
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// STRUCT DEFINITIONS
// ═══════════════════════════════════════════════════════════════════════════

struct Circle {
    double x{}, y{}, r{};
    // 01. sizeof(Circle) = 3×8 = 24 bytes
    // 02. Circle{1.0, 2.0, 0.5} @ 0x1008 = [0x3FF0..., 0x4000..., 0x3FE0...]

    std::vector<double> intersect(double a, double b) const {
        // TODO: DERIVE MATH BY HAND
        // 03. Line: y = ax + b
        // 04. Circle: (x-cx)² + (y-cy)² = r²
        // 05. Substitute: (x-1.0)² + (1.0*x + 0.0 - 2.0)² = 0.5²
        // 06. Expand: (x-1)² + (x-2)² = 0.25
        // 07. x² - 2x + 1 + x² - 4x + 4 = 0.25
        // 08. 2x² - 6x + 5 = 0.25
        // 09. 2x² - 6x + 4.75 = 0
        // 10. A=2, B=-6, C=4.75
        // 11. D = B² - 4AC = 36 - 38 = -2 < 0 → 0 roots
        // TRAP: Wrong example! r=0.5 too small. Redo with r=2.0.
        (void)a;
        (void)b;
        return {};  // TODO
    }
};

struct Rectangle {
    double x1{}, y1{}, x2{}, y2{};
    // 12. sizeof(Rectangle) = 4×8 = 32 bytes

    std::vector<double> intersect(double a, double b) const {
        // TODO: DERIVE BY HAND
        (void)a;
        (void)b;
        return {};  // TODO
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// VARIANT DEFINITION
// ═══════════════════════════════════════════════════════════════════════════
// 13. using MyShape = std::variant<Circle, Rectangle>
// 14. sizeof(MyShape) = 8 + max(24, 32) = 40 bytes
// 15. Layout @ 0x1000: [index 1B][pad 7B][union 32B]
// 16. index=0 → Circle, index=1 → Rectangle
// ═══════════════════════════════════════════════════════════════════════════

using MyShape = std::variant<Circle, Rectangle>;

// ═══════════════════════════════════════════════════════════════════════════
// THE PATTERN TO DERIVE:
// ═══════════════════════════════════════════════════════════════════════════
// std::vector<double> intersectShape(const MyShape& shape, double a, double b) {
//     return std::visit([a, b](const auto& s) -> std::vector<double> {
//         return s.intersect(a, b);
//     }, shape);
// }
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// DERIVATION STEP 1: WHAT IS std::visit?
// ═══════════════════════════════════════════════════════════════════════════
// 17. std::visit(visitor, variant) → calls visitor(get<i>(variant))
// 18. i = variant.index()
// 19. Compiler generates switch:
//     switch(shape.index()) {
//         case 0: return visitor(std::get<0>(shape));  // visitor(Circle&)
//         case 1: return visitor(std::get<1>(shape));  // visitor(Rectangle&)
//     }
// 20. Generated at COMPILE time. All cases known.
// 21. Cost: 1 indirect jump (switch table) vs vptr (2 indirects).
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// DERIVATION STEP 2: WHAT IS [a, b](...)?
// ═══════════════════════════════════════════════════════════════════════════
// 22. [a, b] = capture list. Copy a,b into lambda closure.
// 23. Lambda closure @ 0x2000: [double a=1.0][double b=0.0] = 16 bytes.
// 24. sizeof(closure) = 2×8 = 16 bytes (if capturing by value).
// 25. Capture by ref [&a, &b]: sizeof = 2×8 = 16 bytes (two pointers).
// 26. [a, b] copies values. Safe if a,b outlive lambda.
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// DERIVATION STEP 3: WHAT IS (const auto& s)?
// ═══════════════════════════════════════════════════════════════════════════
// 27. `auto` in lambda parameter = TEMPLATE (C++14).
// 28. Compiler generates multiple operator():
//     operator()(const Circle& s)    { return s.intersect(a,b); }
//     operator()(const Rectangle& s) { return s.intersect(a,b); }
// 29. One per type in variant. N types = N operator() generated.
// 30. Duck typing: s.intersect(a,b) must exist for ALL types.
// 31. If one type lacks .intersect → COMPILE ERROR (good!).
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// DERIVATION STEP 4: WHAT IS -> std::vector<double>?
// ═══════════════════════════════════════════════════════════════════════════
// 32. Explicit return type. All operator() must return same type.
// 33. Without: auto deduction. Works if all .intersect return same type.
// 34. With: Forces return type. Clearer intent. Catches mismatch.
// 35. If Circle::intersect returns vector<double>
//     and Rectangle::intersect returns vector<int> → ERROR.
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// REGISTER REFERENCE: x86-64 REGISTERS USED IN std::visit
// ═══════════════════════════════════════════════════════════════════════════
//
// ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │                              x86-64 REGISTER FILE (64-bit mode) │
// ├──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
// │ │ │  GENERAL PURPOSE REGISTERS (64-bit): │ │
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ │  │ %rax │ 64 bits │ [63..0] │ accumulator, return value │ 0x0000000000000000 │ │ │  │      │
// │         │ ROLE IN visit: tag index storage after movzbl                                   │ │
// │  │      │         │         │ DERIVATION: tag@0x3000=0x00 → movzbl → %eax=0x00 → %rax=0x00
// (zero-extended)    │ │ │  │ %eax │ 32 bits │ [31..0] │ low 32 of %rax │ │ │  │      │         │
// │ TRAP: write to %eax zeros bits [63..32] of %rax (x86-64 rule)                   │ │ │  │ %ax  │
// 16 bits │ [15..0] │ low 16 of %rax │ │ │  │ %al  │  8 bits │ [7..0]  │ low 8 of %rax │ │ │  │ %ah
// │  8 bits │ [15..8] │ high 8 of %ax (legacy) │ │ │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// │ │ │ │
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ │  │ %rdi │ 64 bits │ 1st function argument (System V ABI) │ │ │  │      │         │ ROLE IN
// visit: lambda object pointer (this for operator())                                │ │ │  │      │
// │ DERIVATION: caller passes &lambda → %rdi = 0x7fff8020                                     │ │
// │  │      │         │ LATER: moved to this for Circle::intersect → %rdi = 0x3008 │ │ │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// │ │ │ │
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ │  │ %rsi │ 64 bits │ 2nd function argument (System V ABI) │ │ │  │      │         │ ROLE IN
// visit: variant pointer                                                             │ │ │  │ │ │
// DERIVATION: caller passes &variant → %rsi = 0x3000                                        │ │ │
// │      │         │ MODIFIED: addq $8, %rsi → %rsi = 0x3008 (skip tag+padding to union) │ │ │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// │ │ │ │
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ │  │ %rdx │ 64 bits │ 3rd function argument (System V ABI) │ │ │  │      │         │ ROLE IN
// visit: handler function pointer from dispatch table                               │ │ │  │      │
// │ DERIVATION: dispatch_table[index] loaded here                                             │ │
// │  │      │         │ VALUE: 0x2100 (Circle handler) or 0x2200 (Rectangle handler) │ │ │  │ │ │
// USED BY: jmpq *%rdx (indirect jump to handler)                                            │ │ │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// │ │ │ │
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ │  │ %rcx │ 64 bits │ 4th function argument (System V ABI) │ │ │  │      │         │ ROLE IN
// visit: dispatch_table base address                                                 │ │ │  │ │ │
// DERIVATION: leaq dispatch_table(%rip), %rcx → %rcx = 0x23A0                               │ │ │
// │      │         │ CALCULATION: %rip + offset = 0x1520 + 0x0E80 = 0x23A0 │ │ │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// │ │ │ │  SPECIAL PURPOSE REGISTERS: │ │
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ │  │ %rip │ 64 bits │ instruction pointer │ next instruction address │ │ │  │      │         │
// ROLE IN visit: target of jmpq *%rdx                                                        │ │ │
// │      │         │ BEFORE jmp: %rip = 0x1540 (jmpq instruction) │ │ │  │      │         │ AFTER
// jmp:  %rip = 0x2100 (Circle handler entry)                                           │ │ │  │ │
// │ DERIVATION: %rip ← %rdx                                                                    │ │
// │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// │ │ │ │
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ │  │ %rsp │ 64 bits │ stack pointer │ top of stack │ │ │  │      │         │ ROLE IN visit:
// stack frame management                                                      │ │ │  │      │ │
// VALUE: 0x7fff8000 (grows downward)                                                         │ │ │
// │      │         │ DERIVATION: set by function prologue (push %rbp; mov %rsp,%rbp) │ │ │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// │ │ │ │
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ │  │ %rbp │ 64 bits │ base pointer │ stack frame base │ │ │  │      │         │ ROLE IN visit:
// local variable access                                                       │ │ │  │      │ │
// VALUE: 0x7fff8008                                                                          │ │ │
// │      │         │ DERIVATION: push %rbp; mov %rsp,%rbp at function entry │ │ │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// │ │ │ │  FLAGS REGISTER (RFLAGS): │ │
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ │  │ CF │ bit 0  │ Carry Flag    │ unsigned overflow/borrow │ │ │  │    │        │ ROLE IN
// visit: set by cmpq for bounds check                                                   │ │ │  │ │
// │ EXAMPLE: cmpq $1, %rax → 0 - 1 = -1 → borrow → CF=1                                          │
// │ │
// ├────┼────────┼───────────────┼────────────────────────────────────────────────────────────────────────────────┤
// │ │  │ ZF │ bit 6  │ Zero Flag     │ result = 0 │ │ │  │    │        │ ROLE IN visit: checked by
// je (jump if equal)                                                  │ │ │  │    │        │
// EXAMPLE: 0 - 1 ≠ 0 → ZF=0                                                                     │ │
// │
// ├────┼────────┼───────────────┼────────────────────────────────────────────────────────────────────────────────┤
// │ │  │ SF │ bit 7  │ Sign Flag     │ result < 0 (MSB of result) │ │ │  │    │        │ EXAMPLE: 0
// - 1 = -1 (negative) → SF=1                                                         │ │ │
// ├────┼────────┼───────────────┼────────────────────────────────────────────────────────────────────────────────┤
// │ │  │ OF │ bit 11 │ Overflow Flag │ signed overflow │ │ │  │    │        │ EXAMPLE: 0 - 1 = -1
// (no signed overflow) → OF=0                                               │ │ │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// │ │ │ │  SSE FLOATING POINT REGISTERS (128-bit, low 64 used for double): │ │
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ │  │ %xmm0 │ 128 bits │ 1st FP argument / FP return value │ │ │  │       │          │ ROLE:
// captured 'a' = 1.5                                                                  │ │ │  │ │ │
// DERIVATION: movsd (%rdi), %xmm0 → load from lambda@0x7fff8020                            │ │ │  │
// │          │ HEX: 0x3FF8000000000000 │ │ │  │       │          │ IEEE754: sign=0,
// exp=0x3FF-0x3FF=0, mant=0.5 → 2^0 × 1.5 = 1.5                           │ │ │
// ├───────┼──────────┼───────────────────────────────────────────────────────────────────────────────────────────┤
// │ │  │ %xmm1 │ 128 bits │ 2nd FP argument │ │ │  │       │          │ ROLE: captured 'b' = 0.5 │
// │ │  │       │          │ DERIVATION: movsd 8(%rdi), %xmm1 → load from lambda@0x7fff8028 │ │ │  │
// │          │ HEX: 0x3FE0000000000000 │ │ │  │       │          │ IEEE754: sign=0,
// exp=0x3FE-0x3FF=-1, mant=0 → 2^(-1) × 1.0 = 0.5                         │ │ │
// ├───────┼──────────┼───────────────────────────────────────────────────────────────────────────────────────────┤
// │ │  │ %xmm2 │ 128 bits │ 3rd FP argument │ │ │  │       │          │ ROLE: Circle.x = cx = 2.0
// │ │ │  │       │          │ DERIVATION: movsd (%rdi), %xmm2 → load from Circle@0x3008 │ │ │  │ │
// │ HEX: 0x4000000000000000                                                                   │ │
// │  │       │          │ IEEE754: sign=0, exp=0x400-0x3FF=1, mant=0 → 2^1 × 1.0 = 2.0 │ │ │
// ├───────┼──────────┼───────────────────────────────────────────────────────────────────────────────────────────┤
// │ │  │ %xmm3 │ 128 bits │ 4th FP argument │ │ │  │       │          │ ROLE: Circle.y = cy = 3.0
// │ │ │  │       │          │ DERIVATION: movsd 8(%rdi), %xmm3 → load from Circle@0x3010 │ │ │  │
// │          │ HEX: 0x4008000000000000 │ │ │  │       │          │ IEEE754: sign=0,
// exp=0x400-0x3FF=1, mant=0.5 → 2^1 × 1.5 = 3.0                           │ │ │
// ├───────┼──────────┼───────────────────────────────────────────────────────────────────────────────────────────┤
// │ │  │ %xmm4 │ 128 bits │ 5th FP argument │ │ │  │       │          │ ROLE: Circle.r = radius
// = 4.0                                                             │ │ │  │       │          │
// DERIVATION: movsd 16(%rdi), %xmm4 → load from Circle@0x3018                              │ │ │  │
// │          │ HEX: 0x4010000000000000 │ │ │  │       │          │ IEEE754: sign=0,
// exp=0x401-0x3FF=2, mant=0 → 2^2 × 1.0 = 4.0                             │ │ │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// │ │ │
// └──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
//
// ═══════════════════════════════════════════════════════════════════════════
// REGISTER FLOW DIAGRAM: std::visit execution
// ═══════════════════════════════════════════════════════════════════════════
//
// ENTRY:
// ┌─────────┐     ┌─────────┐
// │  %rdi   │     │  %rsi   │
// │0x7fff8020│    │ 0x3000  │
// │ lambda  │     │ variant │
// └────┬────┘     └────┬────┘
//      │               │
//      │               ▼
//      │         ┌─────────────────────┐
//      │         │  movzbl (%rsi), %eax│
//      │         │  memory[0x3000]=0x00│
//      │         │  %eax ← 0x00000000  │
//      │         │  %rax ← 0x00...00   │
//      │         └──────────┬──────────┘
//      │                    │
//      │                    ▼
//      │         ┌─────────────────────┐
//      │         │leaq table(%rip),%rcx│
//      │         │  %rcx ← 0x23A0      │
//      │         └──────────┬──────────┘
//      │                    │
//      │                    ▼
//      │         ┌─────────────────────────────┐
//      │         │ movq (%rcx,%rax,8), %rdx    │
//      │         │ addr = 0x23A0 + 0×8 = 0x23A0│
//      │         │ %rdx ← memory[0x23A0]       │
//      │         │ %rdx ← 0x2100               │
//      │         └──────────┬──────────────────┘
//      │                    │
//      │         ┌──────────┴──────────┐
//      │         │  addq $8, %rsi      │
//      │         │  %rsi: 0x3000→0x3008│
//      │         └──────────┬──────────┘
//      │                    │
//      │                    ▼
//      │         ┌─────────────────────┐
//      │         │   jmpq *%rdx        │
//      │         │   %rip ← 0x2100     │
//      │         └──────────┬──────────┘
//      │                    │
//      ▼                    ▼
// ┌────────────────────────────────────┐
// │     @0x2100 (Circle handler)       │
// │  %rdi = 0x7fff8020 (lambda)        │
// │  %rsi = 0x3008 (Circle data)       │
// └────────────────────────────────────┘
//

// ═══════════════════════════════════════════════════════════════════════════
// HOW DOES std::visit KNOW WHERE TO JUMP? (Compile-Time Code Generation)
// ═══════════════════════════════════════════════════════════════════════════
//
// QUESTION: "0x2100 is Circle handler. 0x2200 is Rectangle handler. WHO DECIDED?"
// ANSWER: COMPILER. At COMPILE TIME. Not runtime. Not programmer.
//
// ═══════════════════════════════════════════════════════════════════════════
// STEP-BY-STEP DERIVATION:
// ═══════════════════════════════════════════════════════════════════════════
//
// 01. SOURCE CODE INPUT:
//     std::visit([a, b](const auto& s) -> std::vector<double> {
//         return s.intersect(a, b);
//     }, shape);
//
// 02. COMPILER READS variant<Circle, Rectangle>:
//     → 2 types enumerated
//     → types[0] = Circle
//     → types[1] = Rectangle
//
// 03. COMPILER READS (const auto& s):
//     → auto = template parameter
//     → must generate 1 function per type in variant
//     → N types = N functions generated
//
// 04. COMPILER GENERATES 2 operator() FUNCTIONS:
//
//     // Function 1: generated for Circle (placed at address 0x2100 by linker)
//     std::vector<double> __lambda::operator()(const Circle& s) const {
//         return s.intersect(a, b);  // a,b from captures
//     }
//
//     // Function 2: generated for Rectangle (placed at address 0x2200 by linker)
//     std::vector<double> __lambda::operator()(const Rectangle& s) const {
//         return s.intersect(a, b);  // a,b from captures
//     }
//
// 05. LINKER ASSIGNS ADDRESSES:
//     → operator()(Circle&)    placed at 0x2100 (linker decision)
//     → operator()(Rectangle&) placed at 0x2200 (linker decision)
//     → Addresses depend on: code order, optimization, other functions, etc.
//     → NOT hardcoded. Different build = different addresses.
//
// 06. COMPILER GENERATES dispatch_table IN .rodata SECTION:
//
//     // In assembly output:
//     .section .rodata
//     dispatch_table:
//         .quad 0x2100    // dispatch_table[0] = address of Circle handler
//         .quad 0x2200    // dispatch_table[1] = address of Rectangle handler
//
// 07. COMPILER GENERATES std::visit CODE:
//
//     // Pseudocode for what std::visit becomes:
//     auto index = shape.index();           // read tag byte
//     auto handler = dispatch_table[index]; // lookup function pointer
//     return handler(this_lambda, &shape.storage);  // call handler
//
// ═══════════════════════════════════════════════════════════════════════════
// WHO DOES WHAT:
// ═══════════════════════════════════════════════════════════════════════════
//
// ┌──────────────────┬──────────────────────────────────────────────────────────────────────────────────────┐
// │ PROGRAMMER       │ writes [a,b](const auto& s){...} │ │ (you)            │ does NOT specify
// addresses                                                          │ │                  │ does
// NOT create dispatch table                                                      │ │ │ does NOT
// write operator() for each type                                             │
// ├──────────────────┼──────────────────────────────────────────────────────────────────────────────────────┤
// │ COMPILER         │ reads variant<Circle, Rectangle> → {Circle, Rectangle} │ │ (g++/clang++) │
// generates operator()(Circle&) and operator()(Rectangle&)                           │ │ │
// generates dispatch table with placeholders                                          │ │ │ creates
// jump instruction: jmpq *%rdx                                                │
// ├──────────────────┼──────────────────────────────────────────────────────────────────────────────────────┤
// │ LINKER           │ assigns 0x2100 to operator()(Circle&) │ │ (ld)             │ assigns 0x2200
// to operator()(Rectangle&)                                            │ │                  │ fills
// dispatch_table with actual addresses                                          │ │ │ resolves all
// address placeholders                                                   │
// └──────────────────┴──────────────────────────────────────────────────────────────────────────────────────┘
//
// ═══════════════════════════════════════════════════════════════════════════
// TIMELINE:
// ═══════════════════════════════════════════════════════════════════════════
//
// COMPILE TIME:
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ t₁: Compiler parses variant<Circle, Rectangle> │ │ t₂: Compiler sees (const auto& s) → template
// │ │ t₃: Compiler instantiates operator()(const Circle&) │ │ t₄: Compiler instantiates
// operator()(const Rectangle&)                                                     │ │ t₅: Compiler
// emits dispatch_table = {?, ?} (placeholders)                                                  │
// │ t₆: Compiler emits jmpq *%rdx instruction │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
//
// LINK TIME:
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ t₇: Linker assigns 0x2100 to operator()(Circle&) │ │ t₈: Linker assigns 0x2200 to
// operator()(Rectangle&)                                                        │ │ t₉: Linker
// fills dispatch_table = {0x2100, 0x2200}                                                         │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
//
// RUN TIME:
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ t₁₀: shape.index() = 0 (Circle) │ │ t₁₁: dispatch_table[0] = 0x2100 │ │ t₁₂: jmpq *%rdx → %rip
// = 0x2100                                                                            │ │ t₁₃:
// Circle handler executes │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
//
// ═══════════════════════════════════════════════════════════════════════════
// TRAP: "Why 0x2100 and not 0x3000 or 0x1234?"
// ═══════════════════════════════════════════════════════════════════════════
//
// 0x2100 is EXAMPLE ADDRESS. Real address depends on:
// 01. Size of other functions compiled before this one
// 02. Compiler optimization level (-O0 vs -O3)
// 03. Link order in CMakeLists.txt
// 04. Other object files linked
// 05. ASLR (Address Space Layout Randomization) at runtime (base differs)
//
// NUMERICAL EXAMPLE:
// Build 1: operator()(Circle&) at 0x2100
// Build 2: add 50 lines → operator()(Circle&) at 0x2180 (shifted by ~128 bytes)
// Build 3: -O3 inlines → operator()(Circle&) at 0x1900 (smaller code before)
//
// ∴ NEVER hardcode addresses. Always use dispatch table (just like vptr).
//
// ═══════════════════════════════════════════════════════════════════════════
// COMPARISON: std::visit vs vptr
// ═══════════════════════════════════════════════════════════════════════════
//
// ┌─────────────────────┬────────────────────────────────────────┬────────────────────────────────────────────┐
// │                     │ std::visit                             │ virtual function (vptr) │
// ├─────────────────────┼────────────────────────────────────────┼────────────────────────────────────────────┤
// │ Table created       │ Compile time (dispatch_table in .rodata)│ Compile time (vtable in
// .rodata)          │
// ├─────────────────────┼────────────────────────────────────────┼────────────────────────────────────────────┤
// │ Table location      │ Called from std::visit code            │ Stored in each object
// (vptr→vtable)        │
// ├─────────────────────┼────────────────────────────────────────┼────────────────────────────────────────────┤
// │ Index source        │ variant.index() (tag byte)             │ Object's vptr │
// ├─────────────────────┼────────────────────────────────────────┼────────────────────────────────────────────┤
// │ Indirections        │ 1 (dispatch_table[index])              │ 2 (obj→vptr→vtable[offset]) │
// ├─────────────────────┼────────────────────────────────────────┼────────────────────────────────────────────┤
// │ Size overhead       │ 8 bytes per type in variant            │ 8 bytes per object (vptr) │
// └─────────────────────┴────────────────────────────────────────┴────────────────────────────────────────────┘
//

// ═══════════════════════════════════════════════════════════════════════════
// DERIVATION STEP 5: FULL DEBUGGER TRACE (Circle{2.0,3.0,4.0} + line y=1.5x+0.5)
// ═══════════════════════════════════════════════════════════════════════════
//
// 36. intersectShape(shape@0x3000,a=1.5,b=0.5) entry → RSP=0x7fff8000, RBP=0x7fff8008, return
// address @0x7fff8000=0x1000
//
// 37. Memory @0x3000: std::variant<Circle,Rectangle>
//     ┌─────────────┬─────────────────────────────────────────────────────────────────────────────────────┐
//     │ 0x3000      │ tag = 0x00 (uint8_t) → Circle │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x3001-3007 │ padding = {0x00,0x00,0x00,0x00,0x00,0x00,0x00} │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x3008      │ cx = 0x4000000000000000 (2.0) │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x3010      │ cy = 0x4008000000000000 (3.0) │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x3018      │ radius = 0x4010000000000000 (4.0) │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x3020-3027 │ unused (padding to 32B union) │
//     └─────────────┴─────────────────────────────────────────────────────────────────────────────────────┘
//
// 38. Stack frame @0x7fff8000:
//     ┌─────────────┬─────────────────────────────────────────────────────────────────────────────────────┐
//     │ 0x7fff8000  │ return address = 0x0000000000001000 │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x7fff8008  │ saved RBP │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x7fff8010  │ a = 0x3FF8000000000000 (1.5) │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x7fff8018  │ b = 0x3FE0000000000000 (0.5) │
//     └─────────────┴─────────────────────────────────────────────────────────────────────────────────────┘
//
// 39. Lambda object created @0x7fff8020:
//     ┌─────────────┬─────────────────────────────────────────────────────────────────────────────────────┐
//     │ 0x7fff8020  │ capture_a = 0x3FF8000000000000 (1.5) │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x7fff8028  │ capture_b = 0x3FE0000000000000 (0.5) │
//     └─────────────┴─────────────────────────────────────────────────────────────────────────────────────┘
//     sizeof(lambda) = 16 bytes
//
// ═══════════════════════════════════════════════════════════════════════════
// 40. std::visit DISPATCH - AXIOMATIC DERIVATION
// ═══════════════════════════════════════════════════════════════════════════
//
// INPUT STATE:
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ %rdi = 0x7fff8020 (lambda object address) │ │ %rsi = 0x3000 (variant address) │ │ RIP = 0x1500
// (std::visit entry)                                                                             │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 40a: movzbl (%rsi), %eax
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// REGISTER: %rsi
//   BEFORE: %rsi = 0x0000000000003000
//   SOURCE: passed as 2nd argument to std::visit
//   DERIVATION: &variant = 0x3000 (from caller's stack)
//
// MEMORY READ:
//   ADDRESS: (%rsi) = *(0x3000) = memory[0x3000]
//   BYTE VALUE: 0x00
//   DERIVATION: variant tag byte = 0x00 (Circle = index 0)
//   ┌─────────┐
//   │ 0x3000  │ ← %rsi points here
//   │  0x00   │ ← this byte read
//   └─────────┘
//
// INSTRUCTION: movzbl
//   mov = move
//   z = zero-extend (fill upper bits with 0)
//   b = source is byte (8 bits)
//   l = destination is long (32 bits = %eax)
//
// REGISTER: %eax
//   BEFORE: %eax = 0xXXXXXXXX (garbage)
//   AFTER:  %eax = 0x00000000
//   DERIVATION: byte 0x00 → zero-extend to 32 bits → 0x00000000
//   CALCULATION: 0x00 | (0x00 << 8) | (0x00 << 16) | (0x00 << 24) = 0x00000000
//
// FULL %rax REGISTER:
//   %rax = 0x0000000000000000
//   DERIVATION: writing to %eax zeros upper 32 bits of %rax (x86-64 rule)
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 40b: cmpq $1, %rax  (check if index in valid range)
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// REGISTER: %rax
//   VALUE: 0x0000000000000000
//   SOURCE: from step 40a
//
// IMMEDIATE: $1
//   VALUE: 0x0000000000000001
//   DERIVATION: variant<Circle, Rectangle> has 2 types → max valid index = 1
//
// COMPUTATION: %rax - $1 = 0 - 1 = -1 (for flags only, result discarded)
//
// FLAGS REGISTER (RFLAGS):
//   CF (Carry) = 1 (unsigned: 0 < 1 → borrow occurred)
//   ZF (Zero)  = 0 (result ≠ 0)
//   SF (Sign)  = 1 (result is negative)
//   OF (Overflow) = 0
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 40c: ja .L_BAD_VARIANT_ACCESS  (jump if above = unsigned greater)
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// CONDITION: ja = jump if (CF=0 AND ZF=0)
//   CF = 1, ZF = 0
//   CF=0? NO → condition FALSE → no jump
//
// DERIVATION: index=0, max=1 → 0 ≤ 1 ✓ → valid index → continue
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 40d: leaq dispatch_table(%rip), %rcx
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// RIP-RELATIVE ADDRESSING:
//   %rip = 0x1520 (current instruction address)
//   dispatch_table offset = 0x0E80 (from linker)
//   CALCULATION: 0x1520 + 0x0E80 = 0x23A0
//
// REGISTER: %rcx
//   BEFORE: %rcx = 0xXXXXXXXXXXXXXXXX (garbage)
//   AFTER:  %rcx = 0x0000000000023A0
//   DERIVATION: address of dispatch_table in .rodata section
//
// DISPATCH TABLE IN MEMORY @0x23A0:
// ┌─────────────┬────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ 0x23A0      │ 0x0000000000002100 (pointer to Circle handler = operator()(const Circle&)) │
// ├─────────────┼────────────────────────────────────────────────────────────────────────────────────────────────┤
// │ 0x23A8      │ 0x0000000000002200 (pointer to Rectangle handler = operator()(const Rectangle&))
// │
// └─────────────┴────────────────────────────────────────────────────────────────────────────────────────────────┘
// DERIVATION: 2 types in variant → 2 entries × 8 bytes = 16 bytes table
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 40e: movq (%rcx,%rax,8), %rdx
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// ADDRESSING MODE: (%rcx, %rax, 8) = base + index × scale
//   %rcx = 0x23A0 (dispatch_table base)
//   %rax = 0x0000000000000000 (variant index = 0)
//   scale = 8 (sizeof pointer on x86-64)
//
// CALCULATION: 0x23A0 + 0 × 8 = 0x23A0 + 0 = 0x23A0
//
// MEMORY READ:
//   ADDRESS: 0x23A0
//   VALUE: 0x0000000000002100 (8 bytes, little-endian)
//   DERIVATION: dispatch_table[0] = Circle handler address
//
// REGISTER: %rdx
//   BEFORE: %rdx = 0xXXXXXXXXXXXXXXXX (garbage)
//   AFTER:  %rdx = 0x0000000000002100
//   DERIVATION: function pointer to operator()(const Circle&)
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 40f: addq $8, %rsi  (advance pointer past tag to union storage)
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// REGISTER: %rsi
//   BEFORE: %rsi = 0x0000000000003000 (variant start = tag byte)
//   AFTER:  %rsi = 0x0000000000003008 (union storage = actual Circle data)
//   DERIVATION: tag(1B) + padding(7B) = 8 bytes offset
//   CALCULATION: 0x3000 + 0x08 = 0x3008
//
// MEMORY LAYOUT VERIFICATION:
// ┌─────────────┬────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ 0x3000      │ tag = 0x00 (Circle)     ← %rsi was here │
// ├─────────────┼────────────────────────────────────────────────────────────────────────────────────────────────┤
// │ 0x3001-3007 │ padding │
// ├─────────────┼────────────────────────────────────────────────────────────────────────────────────────────────┤
// │ 0x3008      │ Circle.x = 2.0          ← %rsi now here (union storage) │
// └─────────────┴────────────────────────────────────────────────────────────────────────────────────────────────┘
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 40g: jmpq *%rdx  (indirect jump to handler)
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// REGISTER: %rdx
//   VALUE: 0x0000000000002100
//   SOURCE: from step 40e (dispatch_table[index])
//
// INSTRUCTION: jmpq *%rdx
//   * = indirect (jump TO address IN register, not TO register address)
//   q = quad word (64-bit address)
//
// REGISTER: %rip
//   BEFORE: %rip = 0x1540 (jmpq instruction)
//   AFTER:  %rip = 0x2100 (Circle handler entry)
//   DERIVATION: %rip ← %rdx = 0x2100
//
// CALLING CONVENTION STATE AT HANDLER ENTRY:
// ┌─────────────┬────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ %rdi        │ 0x7fff8020 (lambda object = this pointer for operator()) │
// ├─────────────┼────────────────────────────────────────────────────────────────────────────────────────────────┤
// │ %rsi        │ 0x3008 (Circle& s = pointer to Circle data in variant) │
// ├─────────────┼────────────────────────────────────────────────────────────────────────────────────────────────┤
// │ %rip        │ 0x2100 (operator()(const Circle&) entry point) │
// └─────────────┴────────────────────────────────────────────────────────────────────────────────────────────────┘
//
// ═══════════════════════════════════════════════════════════════════════════
// 41. LAMBDA operator()(const Circle& s) - AXIOMATIC DERIVATION
// ═══════════════════════════════════════════════════════════════════════════
//
// ENTRY STATE @0x2100:
// ┌─────────────┬────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ %rdi        │ 0x7fff8020 (this = lambda closure) │
// ├─────────────┼────────────────────────────────────────────────────────────────────────────────────────────────┤
// │ %rsi        │ 0x3008 (const Circle& s) │
// └─────────────┴────────────────────────────────────────────────────────────────────────────────────────────────┘
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 41a: movsd (%rdi), %xmm0  (load captured 'a')
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// MEMORY READ:
//   ADDRESS: (%rdi) = *(0x7fff8020) = memory[0x7fff8020..0x7fff8027]
//   VALUE: 0x3FF8000000000000 (8 bytes, little-endian)
//   DERIVATION: captured a = 1.5
//
// IEEE 754 VERIFICATION:
//   0x3FF8000000000000
//   Sign: 0 (positive)
//   Exponent: 0x3FF = 1023 → bias = 1023 → exp = 1023 - 1023 = 0
//   Mantissa: 0x8000000000000 → 1.5 in binary = 1.1₂ → mantissa = 0.5
//   Value: (-1)^0 × 2^0 × 1.5 = 1.5 ✓
//
// REGISTER: %xmm0
//   BEFORE: %xmm0 = garbage
//   AFTER:  %xmm0 = 1.5 (low 64 bits = 0x3FF8000000000000)
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 41b: movsd 8(%rdi), %xmm1  (load captured 'b')
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// MEMORY READ:
//   ADDRESS: 8 + (%rdi) = 8 + 0x7fff8020 = 0x7fff8028
//   CALCULATION: 0x7fff8020 + 0x08 = 0x7fff8028
//   VALUE: 0x3FE0000000000000 (8 bytes)
//   DERIVATION: captured b = 0.5
//
// IEEE 754 VERIFICATION:
//   0x3FE0000000000000
//   Sign: 0
//   Exponent: 0x3FE = 1022 → exp = 1022 - 1023 = -1
//   Mantissa: 0x0000000000000 → 1.0
//   Value: (-1)^0 × 2^(-1) × 1.0 = 0.5 ✓
//
// REGISTER: %xmm1
//   BEFORE: %xmm1 = garbage
//   AFTER:  %xmm1 = 0.5 (low 64 bits = 0x3FE0000000000000)
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 41c: call Circle::intersect  (tail call or inlined)
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// ARGUMENT PASSING (System V AMD64 ABI):
//   %rdi = 0x3008 (this = Circle*)  ← moved from %rsi
//   %xmm0 = 1.5 (a)
//   %xmm1 = 0.5 (b)
//
// ═══════════════════════════════════════════════════════════════════════════
// 42. Circle::intersect(a=1.5, b=0.5) - AXIOMATIC DERIVATION
// ═══════════════════════════════════════════════════════════════════════════
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 42a: movsd (%rdi), %xmm2  (load this->x = cx)
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// MEMORY READ:
//   ADDRESS: (%rdi) = *(0x3008)
//   VALUE: 0x4000000000000000
//   IEEE 754: exp=0x400-0x3FF=1, mant=0 → 2^1 × 1.0 = 2.0
//
// REGISTER: %xmm2 = 2.0
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 42b: movsd 8(%rdi), %xmm3  (load this->y = cy)
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// MEMORY READ:
//   ADDRESS: 8 + 0x3008 = 0x3010
//   VALUE: 0x4008000000000000
//   IEEE 754: exp=0x400-0x3FF=1, mant=0.5 → 2^1 × 1.5 = 3.0
//
// REGISTER: %xmm3 = 3.0
//
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// STEP 42c: movsd 16(%rdi), %xmm4  (load this->r = radius)
// ───────────────────────────────────────────────────────────────────────────────────────────────────────────────
// MEMORY READ:
//   ADDRESS: 16 + 0x3008 = 0x3018
//   CALCULATION: 0x3008 + 0x10 = 0x3018
//   VALUE: 0x4010000000000000
//   IEEE 754: exp=0x401-0x3FF=2, mant=0 → 2^2 × 1.0 = 4.0
//
// REGISTER: %xmm4 = 4.0
//
// REGISTER STATE SUMMARY:
// ┌─────────────┬────────────────┬────────────────────────────────────────────────────────────────────────────────┐
// │ Register    │ Value          │ Derivation │
// ├─────────────┼────────────────┼────────────────────────────────────────────────────────────────────────────────┤
// │ %xmm0       │ 1.5            │ captured a from lambda closure @0x7fff8020 │
// ├─────────────┼────────────────┼────────────────────────────────────────────────────────────────────────────────┤
// │ %xmm1       │ 0.5            │ captured b from lambda closure @0x7fff8028 │
// ├─────────────┼────────────────┼────────────────────────────────────────────────────────────────────────────────┤
// │ %xmm2       │ 2.0            │ Circle.x from variant storage @0x3008 │
// ├─────────────┼────────────────┼────────────────────────────────────────────────────────────────────────────────┤
// │ %xmm3       │ 3.0            │ Circle.y from variant storage @0x3010 │
// ├─────────────┼────────────────┼────────────────────────────────────────────────────────────────────────────────┤
// │ %xmm4       │ 4.0            │ Circle.r from variant storage @0x3018 │
// └─────────────┴────────────────┴────────────────────────────────────────────────────────────────────────────────┘
//
// 43. QUADRATIC DERIVATION (Circle-Line intersection):
//     Line: y = 1.5x + 0.5
//     Circle: (x - 2.0)² + (y - 3.0)² = 4.0² = 16.0
//     Substitute y: (x - 2.0)² + (1.5x + 0.5 - 3.0)² = 16.0
//                   (x - 2.0)² + (1.5x - 2.5)² = 16.0
//
// 44. Expand (x - 2.0)²:
//     x² - 4.0x + 4.0
//
// 45. Expand (1.5x - 2.5)²:
//     (1.5)²x² - 2×1.5×2.5×x + (2.5)²
//     = 2.25x² - 7.5x + 6.25
//
// 46. Sum:
//     x² - 4.0x + 4.0 + 2.25x² - 7.5x + 6.25 = 16.0
//     (1 + 2.25)x² + (-4.0 - 7.5)x + (4.0 + 6.25) = 16.0
//     3.25x² - 11.5x + 10.25 = 16.0
//     3.25x² - 11.5x + 10.25 - 16.0 = 0
//     3.25x² - 11.5x - 5.75 = 0
//
// 47. Coefficients: A=3.25, B=-11.5, C=-5.75
//
// 48. Discriminant D = B² - 4AC:
//     D = (-11.5)² - 4 × 3.25 × (-5.75)
//     D = 132.25 - 4 × 3.25 × (-5.75)
//     D = 132.25 - (-74.75)
//     D = 132.25 + 74.75
//     D = 207.0
//     D > 0 → 2 real roots ✓
//
// 49. √D = √207.0 = 14.387494569938159
//
// 50. Roots:
//     x₁ = (-B + √D) / (2A) = (11.5 + 14.387494) / (2 × 3.25) = 25.887494 / 6.5 = 3.982691
//     x₂ = (-B - √D) / (2A) = (11.5 - 14.387494) / (2 × 3.25) = -2.887494 / 6.5 = -0.444230
//
// 51. vector<double> result @0x4000 construction:
//     ┌─────────────┬─────────────────────────────────────────────────────────────────────────────────────┐
//     │ 0x4000      │ _M_start = nullptr (0x0000000000000000) │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x4008      │ _M_finish = nullptr (0x0000000000000000) │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x4010      │ _M_end_of_storage = nullptr (0x0000000000000000) │
//     └─────────────┴─────────────────────────────────────────────────────────────────────────────────────┘
//
// 52. D > 0 → allocate double[2] @0x5000 via operator new(16):
//     ┌─────────────┬─────────────────────────────────────────────────────────────────────────────────────┐
//     │ 0x5000      │ x₁ = 0x400FE1893B6E5F97 (3.982691) │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x5008      │ x₂ = 0xBFDC71B54B9EFCD6 (-0.444230) │
//     └─────────────┴─────────────────────────────────────────────────────────────────────────────────────┘
//
// 53. Update vector @0x4000:
//     ┌─────────────┬─────────────────────────────────────────────────────────────────────────────────────┐
//     │ 0x4000      │ _M_start = 0x5000 │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x4008      │ _M_finish = 0x5010 (0x5000 + 2×8) │
//     ├─────────────┼─────────────────────────────────────────────────────────────────────────────────────┤
//     │ 0x4010      │ _M_end_of_storage = 0x5010 │
//     └─────────────┴─────────────────────────────────────────────────────────────────────────────────────┘
//     size() = (_M_finish - _M_start) / 8 = (0x5010 - 0x5000) / 8 = 16 / 8 = 2 ✓
//
// 54. Return: move vector from 0x4000 to caller's stack → RVO possible, no copy.
//

// ═══════════════════════════════════════════════════════════════════════════
// DERIVATION STEP 6: COMPILE-TIME EXPANSION
// ═══════════════════════════════════════════════════════════════════════════
// 39. Lambda with (const auto& s) is equivalent to:
//
//     struct __AnonymousLambda {
//         double a;  // captured
//         double b;  // captured
//
//         // Generated for Circle:
//         std::vector<double> operator()(const Circle& s) const {
//             return s.intersect(a, b);
//         }
//
//         // Generated for Rectangle:
//         std::vector<double> operator()(const Rectangle& s) const {
//             return s.intersect(a, b);
//         }
//     };
//
// 40. N types in variant → N operator() generated.
// 41. sizeof(__AnonymousLambda) = 16 bytes (2 doubles captured).
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// FAILURE PREDICTIONS
// ═══════════════════════════════════════════════════════════════════════════
// F1. Type lacks .intersect method → Compile ✗: "no member named 'intersect'"
// F2. .intersect has wrong signature → Compile ✗: "no matching function"
// F3. Return types differ → Compile ✗: "inconsistent return types"
// F4. Forget capture [a,b] → Compile ✗: "a not declared in this scope"
// F5. Capture by ref but a,b die → Runtime ✗: dangling reference
// F6. variant is std::monostate → Runtime ✗: std::bad_variant_access
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// FUNCTION IMPLEMENTATION (BOILERPLATE - NO MATH)
// ═══════════════════════════════════════════════════════════════════════════

std::vector<double> intersectShape(const MyShape& shape, double a, double b) {
    // 42. Invoke std::visit with generic lambda.
    // 43. Lambda captures a,b by value (copies).
    // 44. Lambda parameter (const auto& s) triggers template expansion.
    // 45. Compiler generates 2 operator() for Circle and Rectangle.
    return std::visit(
        [a, b](const auto& s) -> std::vector<double> {
            // 46. Duck typing: s.intersect(a,b) called.
            // 47. Which s? Depends on runtime variant index.
            // 48. Which operator()? Decided by std::visit switch.
            return s.intersect(a, b);
        },
        shape);
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN: TEST DRIVER
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // 49. Create Circle variant.
    MyShape circleShape = Circle{1.0, 2.0, 2.0};
    // 50. circleShape @ stack: [index=0][pad][Circle{1.0,2.0,2.0}]

    // 51. Create Rectangle variant.
    MyShape rectShape = Rectangle{0.0, 0.0, 4.0, 3.0};
    // 52. rectShape @ stack: [index=1][pad][Rectangle{0,0,4,3}]

    // 53. Call intersectShape on Circle.
    std::vector<double> result1 = intersectShape(circleShape, 1.0, 0.0);
    // 54. std::visit reads index=0 → calls operator()(const Circle&).
    // 55. Circle::intersect(1.0, 0.0) called. TODO: implement math.

    // 56. Call intersectShape on Rectangle.
    std::vector<double> result2 = intersectShape(rectShape, 0.5, 1.0);
    // 57. std::visit reads index=1 → calls operator()(const Rectangle&).
    // 58. Rectangle::intersect(0.5, 1.0) called. TODO: implement math.

    // 59. Print results.
    std::cout << "Circle intersection count: " << result1.size() << "\n";
    std::cout << "Rectangle intersection count: " << result2.size() << "\n";

    // 60. Print variant sizes.
    std::cout << "sizeof(MyShape) = " << sizeof(MyShape) << " bytes\n";
    std::cout << "circleShape.index() = " << circleShape.index() << "\n";
    std::cout << "rectShape.index() = " << rectShape.index() << "\n";

    return 0;
}

// ═══════════════════════════════════════════════════════════════════════════
// TRIP-UP POINTS (Designed to confuse):
// ═══════════════════════════════════════════════════════════════════════════
// T1. `auto` in lambda = template, NOT type deduction from initializer.
// T2. `const auto&` generates N functions, not 1 polymorphic function.
// T3. std::visit uses jump table, not virtual dispatch.
// T4. Lambda closure size = sum of captured values' sizes.
// T5. `-> std::vector<double>` is explicit return type, not always needed.
// T6. If variant holds monostate, visitor must handle it (or crash).
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// COMPLEXITY:
// Time: O(1) dispatch + O(intersect_implementation)
// Space: 16 bytes (lambda closure) + 40 bytes (variant) = 56 bytes stack
// ═══════════════════════════════════════════════════════════════════════════
