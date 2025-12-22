// 72_vptr_vtable_task2.cpp
// TASK 2: AnimalBaseVirtual - WITH VIRTUAL FUNCTION
// ANNOTATED WITH REAL ASSEMBLY FROM 72_vptr_vtable_task2.s

#include <iostream>

// ═══════════════════════════════════════════════════════════════════════════
// REGISTER REFERENCE (System V AMD64 ABI)
// ═══════════════════════════════════════════════════════════════════════════
//
// RDI = 1st argument (or "this" pointer)
// RSI = 2nd argument  
// RDX = 3rd argument
// RAX = return value
// RBP = base pointer (frame pointer)
// RSP = stack pointer
//
// ═══════════════════════════════════════════════════════════════════════════

class AnimalBaseVirtual {
// ═══════════════════════════════════════════════════════════════════════════
// MEMORY LAYOUT (verified from output):
// ═══════════════════════════════════════════════════════════════════════════
//
// sizeof(AnimalBaseVirtual) = 16 bytes
//
// Object at address 0x7ffef8e34840:
// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Offset │ Address          │ Bytes                    │ Field             │
// ├────────┼──────────────────┼──────────────────────────┼───────────────────┤
// │ 0      │ 0x7ffef8e34840   │ [ptr to vtable, 8 bytes] │ vptr              │
// │ 8      │ 0x7ffef8e34848   │ [64 00 00 00]            │ weight = 100      │
// │ 12     │ 0x7ffef8e3484c   │ [05 00 00 00]            │ age = 5           │
// └───────────────────────────────────────────────────────────────────────────┘
//
// PROOF: &obj = 0x7ffef8e34840
//        &obj.weight = 0x7ffef8e34848 = obj + 8 → vptr occupies offset 0-7
//        &obj.age = 0x7ffef8e3484c = obj + 12 → weight at 8-11, age at 12-15
//
// CONTRAST WITH TASK 1:
// ┌──────────────────────────────────────────────────────────────────────────┐
// │ Task 1 (no virtual)     │ Task 2 (virtual)                              │
// ├─────────────────────────┼───────────────────────────────────────────────┤
// │ sizeof = 8              │ sizeof = 16                                   │
// │ offset 0 = weight       │ offset 0 = vptr (8 bytes)                     │
// │ offset 4 = age          │ offset 8 = weight, offset 12 = age            │
// │ no vtable               │ vtable at _ZTV17AnimalBaseVirtual             │
// └──────────────────────────────────────────────────────────────────────────┘

public:
    int weight;   // offset 8, 4 bytes, at (this + 8)
    int age;      // offset 12, 4 bytes, at (this + 12)
    
    // ═══════════════════════════════════════════════════════════════════════
    // CONSTRUCTOR
    // Mangled: _ZN17AnimalBaseVirtualC2Eii (C2=complete ctor, ii=int,int)
    // Assembly: .s lines 10-35
    // ═══════════════════════════════════════════════════════════════════════
    //
    // CALL SITE (main, .s lines 249-253):
    // ┌────────────────────────────────────────────────────────────────────────┐
    // │ Line 249: leaq -48(%rbp), %rax   ; RAX = &obj (stack: RBP - 48)        │
    // │           │                                                            │
    // │           └── obj is at RBP-48 = 0x7ffef8e34840                        │
    // │                                                                        │
    // │ Line 250: movl $5, %edx          ; EDX = age = 5                       │
    // │                                                                        │
    // │ Line 251: movl $100, %esi        ; ESI = weight = 100 = 0x64           │
    // │                                                                        │
    // │ Line 252: movq %rax, %rdi        ; RDI = this = 0x7ffef8e34840         │
    // │                                                                        │
    // │ Line 253: call _ZN17AnimalBaseVirtualC1Eii                             │
    // │           DIRECT CALL to ctor                                          │
    // └────────────────────────────────────────────────────────────────────────┘
    //
    // CONSTRUCTOR BODY (.s lines 10-35):
    // ┌────────────────────────────────────────────────────────────────────────┐
    // │ Line 14: pushq %rbp              ; save old frame                      │
    // │ Line 17: movq %rsp, %rbp         ; new frame                           │
    // │                                                                        │
    // │ Line 19: movq %rdi, -8(%rbp)     ; save this = 0x7ffef8e34840          │
    // │ Line 20: movl %esi, -12(%rbp)    ; save w = 100                        │
    // │ Line 21: movl %edx, -16(%rbp)    ; save a = 5                          │
    // │                                                                        │
    // │ ═══════════════════════════════════════════════════════════════════   │
    // │ VPTR INITIALIZATION (NEW! Not in Task 1)                               │
    // │ ═══════════════════════════════════════════════════════════════════   │
    // │                                                                        │
    // │ Line 22: leaq 16+_ZTV17AnimalBaseVirtual(%rip), %rdx                   │
    // │          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                      │
    // │          RDX = address of vtable + 16                                  │
    // │                                                                        │
    // │          WHY +16?                                                      │
    // │          vtable layout:                                                │
    // │          ┌───────────────────────────────────────────┐                 │
    // │          │ offset -16 │ 0 (offset-to-top)            │                 │
    // │          │ offset -8  │ RTTI pointer                 │                 │
    // │          │ offset 0   │ &speak() ← vptr points HERE  │  slot 0         │
    // │          │ offset 8   │ &~dtor()                     │  slot 1         │
    // │          │ offset 16  │ &deleting_dtor()             │  slot 2         │
    // │          └───────────────────────────────────────────┘                 │
    // │                                                                        │
    // │          16+_ZTV... means skip first 16 bytes → point to slot 0        │
    // │                                                                        │
    // │ Line 23: movq -8(%rbp), %rax     ; RAX = this = 0x7ffef8e34840         │
    // │                                                                        │
    // │ Line 24: movq %rdx, (%rax)       ; *(this + 0) = vptr                  │
    // │          ^^^^^^^^^^^^^                                                 │
    // │          STORE VPTR AT OFFSET 0!                                       │
    // │          *(0x7ffef8e34840) = &vtable[0]                                │
    // │          8 bytes written: pointer to vtable                            │
    // │                                                                        │
    // │ ═══════════════════════════════════════════════════════════════════   │
    // │ MEMBER INITIALIZATION (same as Task 1, but different offsets)          │
    // │ ═══════════════════════════════════════════════════════════════════   │
    // │                                                                        │
    // │ Line 25: movq -8(%rbp), %rax     ; RAX = this                          │
    // │ Line 26: movl -12(%rbp), %edx    ; EDX = w = 100                       │
    // │ Line 27: movl %edx, 8(%rax)      ; *(this + 8) = 100                   │
    // │          ^^^^^^^^^^^^                                                  │
    // │          weight at OFFSET 8 (was offset 0 in Task 1!)                  │
    // │          *(0x7ffef8e34848) = 100 = 0x64                                │
    // │                                                                        │
    // │ Line 28: movq -8(%rbp), %rax     ; RAX = this                          │
    // │ Line 29: movl -16(%rbp), %edx    ; EDX = a = 5                         │
    // │ Line 30: movl %edx, 12(%rax)     ; *(this + 12) = 5                    │
    // │          ^^^^^^^^^^^^^                                                 │
    // │          age at OFFSET 12 (was offset 4 in Task 1!)                    │
    // │          *(0x7ffef8e3484c) = 5                                         │
    // │                                                                        │
    // │ Line 31: nop                                                           │
    // │ Line 32-34: popq %rbp, ret                                             │
    // └────────────────────────────────────────────────────────────────────────┘
    //
    AnimalBaseVirtual(int w, int a) : weight(w), age(a) {
        // IMPLICIT: vptr = &vtable[0] stored at offset 0 BEFORE user code runs
        // Assembly line 24: movq %rdx, (%rax) ← this happens before :weight(w)
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // NON-VIRTUAL FUNCTION
    // Mangled: _ZN17AnimalBaseVirtual7nonVirtEi
    // Assembly: .s lines 51-93
    // ═══════════════════════════════════════════════════════════════════════
    //
    // CALL SITE (main, .s lines 254-258):
    // ┌────────────────────────────────────────────────────────────────────────┐
    // │ Line 254: leaq -48(%rbp), %rax   ; RAX = &obj                          │
    // │ Line 255: movl $42, %esi         ; ESI = x = 42 = 0x2A                 │
    // │ Line 256: movq %rax, %rdi        ; RDI = this                          │
    // │ Line 258: call _ZN17AnimalBaseVirtual7nonVirtEi                        │
    // │           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                         │
    // │           DIRECT CALL                                                  │
    // │           Function address embedded in instruction                     │
    // │           NOT: call *(%rax) (would be indirect via vtable)             │
    // └────────────────────────────────────────────────────────────────────────┘
    //
    // FUNCTION BODY (.s lines 51-93):
    // ┌────────────────────────────────────────────────────────────────────────┐
    // │ Line 61: movq %rdi, -8(%rbp)     ; save this                           │
    // │ Line 62: movl %esi, -12(%rbp)    ; save x = 42                         │
    // │                                                                        │
    // │ Line 69: movq -8(%rbp), %rax     ; RAX = this = 0x7ffef8e34840         │
    // │ Line 70: movl 8(%rax), %eax      ; EAX = *(this+8) = weight = 100      │
    // │          ^^^^^^^^^^                                                    │
    // │          OFFSET 8! (was offset 0 in Task 1)                            │
    // │          vptr at 0-7, weight at 8-11                                   │
    // │                                                                        │
    // │ Line 80: movl -12(%rbp), %eax    ; EAX = x = 42                        │
    // └────────────────────────────────────────────────────────────────────────┘
    //
    void nonVirt(int x) {
        std::cout << "nonVirt: weight=" << weight << ", x=" << x << "\n";
        // Assembly line 70: movl 8(%rax), %eax → weight at offset 8
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // VIRTUAL FUNCTION
    // Mangled: _ZN17AnimalBaseVirtual5speakEi
    // Assembly: .s lines 106-148
    // ═══════════════════════════════════════════════════════════════════════
    //
    // CALL SITE (main, .s lines 259-262):
    // ┌────────────────────────────────────────────────────────────────────────┐
    // │ Line 259: leaq -48(%rbp), %rax   ; RAX = &obj                          │
    // │ Line 260: movl $77, %esi         ; ESI = volume = 77 = 0x4D            │
    // │ Line 261: movq %rax, %rdi        ; RDI = this                          │
    // │ Line 262: call _ZN17AnimalBaseVirtual5speakEi                          │
    // │           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                        │
    // │           STILL DIRECT! Compiler devirtualized because:                │
    // │           - obj is declared as AnimalBaseVirtual (not pointer to base) │
    // │           - Compiler knows exact type at compile time                  │
    // │           - No derived class override possible here                    │
    // │                                                                        │
    // │           TO SEE INDIRECT CALL: Use Base* ptr = &derived;              │
    // │           Then you'd see:                                              │
    // │             movq (%rdi), %rax    ; load vptr from object               │
    // │             call *(%rax)         ; call through vtable slot 0          │
    // └────────────────────────────────────────────────────────────────────────┘
    //
    // VTABLE ENTRY (.s line 376):
    //   .quad _ZN17AnimalBaseVirtual5speakEi   ← slot 0 in vtable
    //
    // If indirect call happened:
    //   movq (%rdi), %rax     ; RAX = vptr = *(this+0)
    //   call *(%rax)          ; call *(vptr+0) = *(slot 0) = &speak
    //
    virtual void speak(int volume) {
        std::cout << "AnimalBaseVirtual::speak: weight=" << weight 
                  << ", volume=" << volume << "\n";
        // Assembly line 125: movl 8(%rax), %eax → weight at offset 8
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // VIRTUAL DESTRUCTOR
    // Mangled: _ZN17AnimalBaseVirtualD2Ev (D2 = complete dtor)
    //          _ZN17AnimalBaseVirtualD0Ev (D0 = deleting dtor)
    // Assembly: .s lines 155-203
    // ═══════════════════════════════════════════════════════════════════════
    //
    // DESTRUCTOR BODY (.s lines 155-172):
    // ┌────────────────────────────────────────────────────────────────────────┐
    // │ Line 164: movq %rdi, -8(%rbp)    ; save this                           │
    // │                                                                        │
    // │ Line 165: leaq 16+_ZTV17AnimalBaseVirtual(%rip), %rdx                  │
    // │           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                         │
    // │           RESET VPTR back to this class's vtable!                      │
    // │           WHY? In case derived class set a different vptr.             │
    // │                                                                        │
    // │ Line 166: movq -8(%rbp), %rax    ; RAX = this                          │
    // │ Line 167: movq %rdx, (%rax)      ; *(this+0) = vptr (reset)            │
    // │                                                                        │
    // │ Line 168: nop                                                          │
    // │ Line 169-171: popq %rbp, ret                                           │
    // └────────────────────────────────────────────────────────────────────────┘
    //
    // DELETING DESTRUCTOR (.s lines 181-203):
    //   Calls D1 (complete destructor) then calls operator delete
    //   Line 196: movl $16, %esi    ; sizeof = 16 bytes to free
    //   Line 198: call _ZdlPvm@PLT  ; operator delete(ptr, 16)
    //
    virtual ~AnimalBaseVirtual() = default;
};

// ═══════════════════════════════════════════════════════════════════════════
// VTABLE (.s lines 368-378)
// ═══════════════════════════════════════════════════════════════════════════
//
// _ZTV17AnimalBaseVirtual:            ; vtable for AnimalBaseVirtual
//   .quad 0                           ; offset -16: offset-to-top = 0
//   .quad _ZTI17AnimalBaseVirtual     ; offset -8:  RTTI (typeinfo)
//   .quad _ZN17AnimalBaseVirtual5speakEi   ; offset 0: slot[0] = &speak
//   .quad _ZN17AnimalBaseVirtualD1Ev       ; offset 8: slot[1] = &complete_dtor
//   .quad _ZN17AnimalBaseVirtualD0Ev       ; offset 16: slot[2] = &deleting_dtor
//
// SIZE: 40 bytes (5 quads × 8 bytes)
//
// vptr points to offset +16 (slot 0):
// ┌────────────────────────────────────────────────────────────────────────────┐
// │ vtable addr  │ offset │ Content                          │ Access         │
// ├──────────────┼────────┼──────────────────────────────────┼────────────────┤
// │ base + 0     │ -16    │ 0 (offset-to-top)                │ vptr[-2]       │
// │ base + 8     │ -8     │ _ZTI17AnimalBaseVirtual (RTTI)   │ vptr[-1]       │
// │ base + 16    │ 0      │ &speak() ← vptr points here!     │ vptr[0]        │
// │ base + 24    │ 8      │ &~dtor()                         │ vptr[1]        │
// │ base + 32    │ 16     │ &deleting_dtor()                 │ vptr[2]        │
// └────────────────────────────────────────────────────────────────────────────┘
//
// To call speak():
//   movq (%this), %rax      ; rax = vptr
//   call *(%rax)            ; call *(vptr + 0) = &speak
//
// To call destructor:
//   movq (%this), %rax      ; rax = vptr
//   call *8(%rax)           ; call *(vptr + 8) = &dtor

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// Assembly: .s lines 217-342
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // ═══════════════════════════════════════════════════════════════════════
    // SIZEOF CHECK
    // Assembly line 240: movl $16, %esi ← sizeof embedded as immediate
    // ═══════════════════════════════════════════════════════════════════════
    std::cout << "sizeof(AnimalBaseVirtual) = " << sizeof(AnimalBaseVirtual) << "\n";
    // Output: 16 (was 8 in Task 1)
    // Breakdown: 8 (vptr) + 4 (weight) + 4 (age) = 16
    
    // ═══════════════════════════════════════════════════════════════════════
    // CREATE OBJECT
    // Assembly lines 249-253:
    //   leaq -48(%rbp), %rax    ; RAX = &obj = RBP - 48
    //   movl $5, %edx           ; EDX = age = 5
    //   movl $100, %esi         ; ESI = weight = 100
    //   movq %rax, %rdi         ; RDI = this
    //   call _ZN17AnimalBaseVirtualC1Eii
    // ═══════════════════════════════════════════════════════════════════════
    AnimalBaseVirtual obj(100, 5);
    
    // MEMORY STATE after construction:
    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ Stack Address   │ Offset │ Value              │ Field               │
    // ├─────────────────┼────────┼────────────────────┼─────────────────────┤
    // │ RBP-48 (obj+0)  │ 0      │ ptr→vtable[0]      │ vptr (8 bytes)      │
    // │ RBP-40 (obj+8)  │ 8      │ 0x00000064         │ weight = 100        │
    // │ RBP-36 (obj+12) │ 12     │ 0x00000005         │ age = 5             │
    // └─────────────────────────────────────────────────────────────────────┘
    //
    // vptr → _ZTV17AnimalBaseVirtual + 16
    //         ↓
    //      [&speak][&dtor][&del_dtor]
    
    // ═══════════════════════════════════════════════════════════════════════
    // CALL NON-VIRTUAL FUNCTION
    // Assembly lines 254-258:
    //   leaq -48(%rbp), %rax    ; RAX = &obj
    //   movl $42, %esi          ; ESI = 42
    //   movq %rax, %rdi         ; RDI = this
    //   call _ZN17AnimalBaseVirtual7nonVirtEi  ← DIRECT CALL
    // ═══════════════════════════════════════════════════════════════════════
    obj.nonVirt(42);
    // Output: nonVirt: weight=100, x=42
    
    // ═══════════════════════════════════════════════════════════════════════
    // CALL VIRTUAL FUNCTION
    // Assembly lines 259-262:
    //   leaq -48(%rbp), %rax    ; RAX = &obj
    //   movl $77, %esi          ; ESI = 77
    //   movq %rax, %rdi         ; RDI = this
    //   call _ZN17AnimalBaseVirtual5speakEi   ← STILL DIRECT (devirtualized)
    //
    // WHY DIRECT? Compiler knows obj is exactly AnimalBaseVirtual
    //             No derived class in scope could override speak()
    //             Optimization: skip vtable lookup when type is known
    //
    // FOR INDIRECT CALL, need:
    //   AnimalBaseVirtual* ptr = &obj;  // or = new Derived();
    //   ptr->speak(77);                 // now compiler doesn't know type
    //   Assembly would be:
    //     movq (%rdi), %rax             ; load vptr
    //     call *(%rax)                  ; indirect call via slot 0
    // ═══════════════════════════════════════════════════════════════════════
    obj.speak(77);
    // Output: AnimalBaseVirtual::speak: weight=100, volume=77
    
    // ═══════════════════════════════════════════════════════════════════════
    // ADDRESS VERIFICATION
    // Assembly lines 284-285:
    //   leaq -48(%rbp), %rax    ; RAX = &obj
    //   addq $8, %rax           ; RAX = &obj + 8 = &obj.weight
    //
    // Assembly lines 300-301:
    //   leaq -48(%rbp), %rax    ; RAX = &obj
    //   addq $12, %rax          ; RAX = &obj + 12 = &obj.age
    // ═══════════════════════════════════════════════════════════════════════
    std::cout << "&obj = " << &obj << "\n";
    std::cout << "&obj.weight = " << &obj.weight << "\n";
    std::cout << "&obj.age = " << &obj.age << "\n";
    
    // Output:
    //   &obj = 0x7ffef8e34840
    //   &obj.weight = 0x7ffef8e34848  (0x840 + 8 = 0x848)
    //   &obj.age = 0x7ffef8e3484c     (0x840 + 12 = 0x84c)
    //
    // PROOF: vptr at offset 0 (8 bytes)
    //        weight at offset 8 (4 bytes)
    //        age at offset 12 (4 bytes)
    
    return 0;
    
    // ═══════════════════════════════════════════════════════════════════════
    // DESTRUCTOR CALL
    // Assembly lines 312-314:
    //   leaq -48(%rbp), %rax    ; RAX = &obj
    //   movq %rax, %rdi         ; RDI = this
    //   call _ZN17AnimalBaseVirtualD1Ev  ← DIRECT (devirtualized)
    //
    // Destructor resets vptr (line 165-167 in dtor body):
    //   leaq 16+_ZTV17AnimalBaseVirtual(%rip), %rdx
    //   movq %rdx, (%rax)       ; reset vptr
    // ═══════════════════════════════════════════════════════════════════════
}

// ═══════════════════════════════════════════════════════════════════════════
// KEY DIFFERENCES: TASK 1 vs TASK 2
// ═══════════════════════════════════════════════════════════════════════════
//
// ┌─────────────────────┬─────────────────────────┬──────────────────────────┐
// │ Aspect              │ Task 1 (no virtual)     │ Task 2 (virtual)         │
// ├─────────────────────┼─────────────────────────┼──────────────────────────┤
// │ sizeof              │ 8                       │ 16                       │
// │ offset 0            │ weight                  │ vptr                     │
// │ offset 4            │ age                     │ (part of vptr)           │
// │ offset 8            │ N/A                     │ weight                   │
// │ offset 12           │ N/A                     │ age                      │
// │ ctor vptr init      │ none                    │ leaq+movq at lines 22-24 │
// │ vtable symbol       │ none                    │ _ZTV17AnimalBaseVirtual  │
// │ vtable size         │ 0                       │ 40 bytes (5 slots)       │
// │ virtual call        │ N/A                     │ devirtualized here       │
// └─────────────────────┴─────────────────────────┴──────────────────────────┘
//
// NEXT: Task 3 will add derived class, Task 4 will show actual indirect call
// ═══════════════════════════════════════════════════════════════════════════
