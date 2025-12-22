// 72_vptr_vtable_task1.cpp
// TASK 1: AnimalStandalone - NO VIRTUAL FUNCTION
// ANNOTATED WITH REAL ASSEMBLY FROM 72_vptr_vtable_task1.s

#include <iostream>

// ═══════════════════════════════════════════════════════════════════════════
// REGISTER REFERENCE (System V AMD64 ABI)
// ═══════════════════════════════════════════════════════════════════════════
//
// RDI = 1st argument (or "this" pointer for member functions)
// RSI = 2nd argument
// RDX = 3rd argument
// RCX = 4th argument
// R8  = 5th argument
// R9  = 6th argument
// RAX = return value
// RBP = base pointer (frame pointer)
// RSP = stack pointer
//
// For 32-bit values: EDI, ESI, EDX, ECX, EAX (lower 32 bits)
// For 64-bit values: RDI, RSI, RDX, RCX, RAX (full 64 bits)
//
// ═══════════════════════════════════════════════════════════════════════════

class AnimalStandalone {
// ═══════════════════════════════════════════════════════════════════════════
// MEMORY LAYOUT (verified from output):
// ═══════════════════════════════════════════════════════════════════════════
//
// sizeof(AnimalStandalone) = 8 bytes
//
// Object at address 0x7ffcbf677390:
// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Offset │ Address        │ Bytes           │ Value  │ Field               │
// ├────────┼────────────────┼─────────────────┼────────┼─────────────────────┤
// │ 0      │ 0x7ffcbf677390 │ [64 00 00 00]   │ 100    │ weight (int, 4B)    │
// │ 4      │ 0x7ffcbf677394 │ [05 00 00 00]   │ 5      │ age (int, 4B)       │
// └───────────────────────────────────────────────────────────────────────────┘
//
// NO VPTR! Offset 0 = weight, not pointer
// 0x64 = 100 in hex (little-endian: 64 00 00 00)
// 0x05 = 5 in hex
//
// PROOF: &obj = &obj.weight = 0x7ffcbf677390 (same address!)
//        &obj.age = 0x7ffcbf677394 = 0x7ffcbf677390 + 4

public:
    int weight;   // offset 0, 4 bytes, at (this + 0)
    int age;      // offset 4, 4 bytes, at (this + 4)
    
    // ═══════════════════════════════════════════════════════════════════════
    // CONSTRUCTOR
    // ═══════════════════════════════════════════════════════════════════════
    // 
    // C++ SOURCE: AnimalStandalone(100, 5)
    // 
    // CALLING CONVENTION at call site (main, lines 168-172):
    // ┌────────────────────────────────────────────────────────────────────────┐
    // │ Line 168: leaq -16(%rbp), %rax    ; RAX = &obj (stack address)         │
    // │           -16(%rbp) = RBP - 16 = 0x7ffcbf6773a0 - 16 = 0x7ffcbf677390  │
    // │                                                                        │
    // │ Line 169: movl $5, %edx           ; EDX = age = 5 (3rd param)          │
    // │           $5 = immediate value 5                                       │
    // │           EDX = lower 32 bits of RDX                                   │
    // │                                                                        │
    // │ Line 170: movl $100, %esi         ; ESI = weight = 100 = 0x64 (2nd)    │
    // │           $100 = immediate value 100                                   │
    // │           ESI = lower 32 bits of RSI                                   │
    // │                                                                        │
    // │ Line 171: movq %rax, %rdi         ; RDI = this = &obj                  │
    // │           movq = move 64-bit quad word                                 │
    // │           RDI = 0x7ffcbf677390 (this pointer)                          │
    // │                                                                        │
    // │ Line 172: call _ZN16AnimalStandaloneC1Eii                              │
    // │           _ZN = namespace (none)                                       │
    // │           16AnimalStandalone = class name (16 chars)                   │
    // │           C1 = complete object constructor                             │
    // │           E = end of name                                              │
    // │           ii = two int parameters                                      │
    // │           DIRECT CALL → address embedded in instruction                │
    // └────────────────────────────────────────────────────────────────────────┘
    //
    // CONSTRUCTOR BODY (.s lines 10-31):
    // ┌────────────────────────────────────────────────────────────────────────┐
    // │ Line 14: pushq %rbp               ; save old base pointer              │
    // │          RSP -= 8, *(RSP) = RBP                                        │
    // │                                                                        │
    // │ Line 17: movq %rsp, %rbp          ; RBP = RSP (new frame)              │
    // │          RBP = 0x7ffcbf677370 (example)                                │
    // │                                                                        │
    // │ Line 19: movq %rdi, -8(%rbp)      ; save this to stack                 │
    // │          *(RBP - 8) = RDI = 0x7ffcbf677390                             │
    // │          Why: need this for later, can't keep in register              │
    // │                                                                        │
    // │ Line 20: movl %esi, -12(%rbp)     ; save w to stack                    │
    // │          *(RBP - 12) = ESI = 100 = 0x64                                │
    // │          movl = 32-bit move (int is 32-bit)                            │
    // │                                                                        │
    // │ Line 21: movl %edx, -16(%rbp)     ; save a to stack                    │
    // │          *(RBP - 16) = EDX = 5                                         │
    // │                                                                        │
    // │ Line 22: movq -8(%rbp), %rax      ; RAX = this                         │
    // │          RAX = *(RBP - 8) = 0x7ffcbf677390                             │
    // │                                                                        │
    // │ Line 23: movl -12(%rbp), %edx     ; EDX = w = 100                      │
    // │          EDX = *(RBP - 12) = 100                                       │
    // │                                                                        │
    // │ Line 24: movl %edx, (%rax)        ; this->weight = 100                 │
    // │          *(RAX + 0) = EDX                                              │
    // │          *(0x7ffcbf677390) = 100                                       │
    // │          Write 4 bytes: [64 00 00 00]                                  │
    // │                                                                        │
    // │ Line 25: movq -8(%rbp), %rax      ; RAX = this (reload)                │
    // │                                                                        │
    // │ Line 26: movl -16(%rbp), %edx     ; EDX = a = 5                        │
    // │          EDX = *(RBP - 16) = 5                                         │
    // │                                                                        │
    // │ Line 27: movl %edx, 4(%rax)       ; this->age = 5                      │
    // │          *(RAX + 4) = EDX                                              │
    // │          *(0x7ffcbf677394) = 5                                         │
    // │          Write 4 bytes: [05 00 00 00]                                  │
    // │                                                                        │
    // │ Line 28: nop                      ; NO VPTR INITIALIZATION!            │
    // │          If virtual existed, would see:                                │
    // │          leaq _ZTV16AnimalStandalone+16(%rip), %rax                    │
    // │          movq %rax, (%rdi)        ; store vptr at offset 0             │
    // │          BUT WE DON'T SEE THIS → no virtual                            │
    // │                                                                        │
    // │ Line 29-31: popq %rbp, ret        ; cleanup and return                 │
    // └────────────────────────────────────────────────────────────────────────┘
    //
    AnimalStandalone(int w, int a) : weight(w), age(a) {}
    
    // ═══════════════════════════════════════════════════════════════════════
    // MEMBER FUNCTION speak(int volume)
    // ═══════════════════════════════════════════════════════════════════════
    //
    // C++ SOURCE: obj.speak(42)
    //
    // CALL SITE (.s lines 173-176):
    // ┌────────────────────────────────────────────────────────────────────────┐
    // │ Line 173: leaq -16(%rbp), %rax    ; RAX = &obj                         │
    // │           leaq = load effective address (compute address, don't load)  │
    // │           RAX = RBP - 16 = 0x7ffcbf677390                              │
    // │                                                                        │
    // │ Line 174: movl $42, %esi          ; ESI = volume = 42 = 0x2A           │
    // │           $42 = immediate value                                        │
    // │           ESI = 2nd argument register (32-bit)                         │
    // │           Why ESI not EDI? EDI/RDI holds "this"                        │
    // │                                                                        │
    // │ Line 175: movq %rax, %rdi         ; RDI = this = &obj                  │
    // │           movq = 64-bit move (pointers are 64-bit)                     │
    // │           RDI = 0x7ffcbf677390                                         │
    // │                                                                        │
    // │ Line 176: call _ZN16AnimalStandalone5speakEi                           │
    // │           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                             │
    // │           DIRECT CALL - function address known at compile time         │
    // │           NOT: call *(%rax) which would be indirect (vtable)           │
    // │           NOT: call *8(%rax) which would be vtable slot 1              │
    // │                                                                        │
    // │           Mangled name breakdown:                                      │
    // │           _Z = C++ mangled                                             │
    // │           N = nested name                                              │
    // │           16AnimalStandalone = class (16 chars)                        │
    // │           5speak = function (5 chars)                                  │
    // │           E = end of nested name                                       │
    // │           i = int parameter                                            │
    // └────────────────────────────────────────────────────────────────────────┘
    //
    // FUNCTION BODY (.s lines 50-102):
    // ┌────────────────────────────────────────────────────────────────────────┐
    // │ Line 60: movq %rdi, -8(%rbp)      ; save this                          │
    // │ Line 61: movl %esi, -12(%rbp)     ; save volume = 42                   │
    // │                                                                        │
    // │ Line 68: movq -8(%rbp), %rax      ; RAX = this                         │
    // │ Line 69: movl (%rax), %eax        ; EAX = *(this+0) = weight = 100     │
    // │          (%rax) means *(RAX + 0) = dereference at offset 0             │
    // │          EAX = 100 = 0x64                                              │
    // │                                                                        │
    // │ Line 79-80: movl 4(%rax), %eax    ; EAX = *(this+4) = age = 5          │
    // │             4(%rax) means *(RAX + 4) = dereference at offset 4         │
    // │             EAX = 5                                                    │
    // │                                                                        │
    // │ Line 90: movl -12(%rbp), %eax     ; EAX = volume = 42                  │
    // │          volume was saved at RBP-12                                    │
    // └────────────────────────────────────────────────────────────────────────┘
    //
    void speak(int volume) {
        std::cout << "Weight=" << weight << ", Age=" << age 
                  << ", Volume=" << volume << "\n";
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // GETTER FUNCTION getWeight()
    // ═══════════════════════════════════════════════════════════════════════
    //
    // ASSEMBLY (.s lines 110-124):
    // ┌────────────────────────────────────────────────────────────────────────┐
    // │ Line 119: movq %rdi, -8(%rbp)     ; save this                          │
    // │                                                                        │
    // │ Line 120: movq -8(%rbp), %rax     ; RAX = this = 0x7ffcbf677390        │
    // │                                                                        │
    // │ Line 121: movl (%rax), %eax       ; EAX = *(this+0) = weight           │
    // │           (%rax) = *(RAX) = *(0x7ffcbf677390) = 100                    │
    // │           Return value goes in EAX (32-bit int)                        │
    // │                                                                        │
    // │ Line 122-124: popq %rbp, ret      ; return with EAX = 100              │
    // └────────────────────────────────────────────────────────────────────────┘
    //
    // Mangled name: _ZNK16AnimalStandalone9getWeightEv
    //               K = const member function
    //               9getWeight = function name (9 chars)
    //               v = void (no parameters)
    //
    int getWeight() const {
        return weight;
        // Assembly: movl (%rax), %eax ; return value in EAX
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN FUNCTION
// ═══════════════════════════════════════════════════════════════════════════
//
// STACK FRAME (.s line 151):
//   subq $32, %rsp    ; allocate 32 bytes on stack
//   
// Stack layout:
// ┌────────────────────────────────────────────────────────────────────────────┐
// │ RBP - 8   │ stack canary (security)                                        │
// │ RBP - 12  │ unused                                                         │
// │ RBP - 16  │ obj.weight = 100 (4 bytes)                                     │
// │ RBP - 20  │ obj.age = 5 (mapped to RBP-16+4)                               │
// │ ...       │                                                                │
// └────────────────────────────────────────────────────────────────────────────┘

int main() {
    // .s line 160: movl $8, %esi → sizeof = 8 (embedded as immediate)
    std::cout << "sizeof(AnimalStandalone) = " << sizeof(AnimalStandalone) << "\n";
    
    // ═══════════════════════════════════════════════════════════════════════
    // CREATE OBJECT
    // ═══════════════════════════════════════════════════════════════════════
    //
    // .s lines 168-172:
    //   leaq -16(%rbp), %rax      ; RAX = stack address for obj
    //   movl $5, %edx             ; EDX = 5 (age, 3rd param)
    //   movl $100, %esi           ; ESI = 100 (weight, 2nd param)
    //   movq %rax, %rdi           ; RDI = this
    //   call _ZN16AnimalStandaloneC1Eii   ; DIRECT CALL to ctor
    //
    AnimalStandalone obj(100, 5);
    
    // MEMORY STATE after line above:
    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ Stack Address   │ Value        │ Field                              │
    // ├─────────────────┼──────────────┼────────────────────────────────────┤
    // │ RBP-16 (obj+0)  │ 0x00000064   │ weight = 100                       │
    // │ RBP-12 (obj+4)  │ 0x00000005   │ age = 5                            │
    // └─────────────────────────────────────────────────────────────────────┘
    
    // ═══════════════════════════════════════════════════════════════════════
    // CALL MEMBER FUNCTION
    // ═══════════════════════════════════════════════════════════════════════
    //
    // .s lines 173-176:
    //   leaq -16(%rbp), %rax      ; RAX = &obj
    //   movl $42, %esi            ; ESI = 42 (volume param)
    //   movq %rax, %rdi           ; RDI = this
    //   call _ZN16AnimalStandalone5speakEi   ; DIRECT CALL (not *(%rax)!)
    //
    obj.speak(42);
    
    // ═══════════════════════════════════════════════════════════════════════
    // CALL GETTER
    // ═══════════════════════════════════════════════════════════════════════
    //
    // .s lines 177-180:
    //   leaq -16(%rbp), %rax      ; RAX = &obj
    //   movq %rax, %rdi           ; RDI = this
    //   call _ZNK16AnimalStandalone9getWeightEv
    //   movl %eax, -20(%rbp)      ; save return value (EAX = 100)
    //
    int w = obj.getWeight();
    std::cout << "getWeight() = " << w << "\n";
    
    // ═══════════════════════════════════════════════════════════════════════
    // ADDRESS VERIFICATION
    // ═══════════════════════════════════════════════════════════════════════
    //
    // Output from run:
    //   &obj        = 0x7ffcbf677390
    //   &obj.weight = 0x7ffcbf677390   ← SAME! weight at offset 0
    //   &obj.age    = 0x7ffcbf677394   ← offset 4
    //
    // Calculation: 0x7ffcbf677394 - 0x7ffcbf677390 = 4
    //
    // .s line 233: addq $4, %rax  ; compute &obj.age = &obj + 4
    //
    std::cout << "&obj = " << &obj << "\n";
    std::cout << "&obj.weight = " << &obj.weight << "\n";
    std::cout << "&obj.age = " << &obj.age << "\n";
    
    return 0;
}

// ═══════════════════════════════════════════════════════════════════════════
// KEY TAKEAWAYS FOR TASK 1:
// ═══════════════════════════════════════════════════════════════════════════
//
// 1. sizeof = 8 (two ints, no vptr)
// 2. No _ZTV symbol in assembly → no vtable
// 3. All calls are DIRECT: call _ZN16AnimalStandalone...
//    NOT: call *(%rax) or call *8(%rax)
// 4. Ctor just stores members, no vptr write
// 5. RDI = this, ESI = 1st param, EDX = 2nd param, EAX = return
// 6. Offset 0 = first member (weight), NOT vptr
//
// NEXT: TASK 2 will add virtual function → vptr will appear at offset 0
// ═══════════════════════════════════════════════════════════════════════════
