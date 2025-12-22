// 71_copy_ctor_assign_assembly.cpp
// COMPLETE ASSEMBLY ANNOTATION WITH REAL ADDRESSES AND BYTE CALCULATIONS
// Every line shows assembly instruction, register state, memory writes

#include <iostream>

struct Widget {
    int val;  
    // sizeof(Widget) = 4 bytes
    // alignof(Widget) = 4 bytes
    // Offset 0: val (4 bytes)
    // Stack layout: -16(%rbp) = b.val, -12(%rbp) = a.val
    // Memory: *(rbp-16) = 0x7FFF0080, *(rbp-12) = 0x7FFF0084
    
    // ═══════════════════════════════════════════════════════════════════════
    // PARAM CTOR: Widget(int v)
    // Mangled: _ZN6WidgetC2Ei (C2=complete ctor, Ei=int param)
    // ═══════════════════════════════════════════════════════════════════════
    // 
    // STACK FRAME:
    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Address     │ Content      │ Description                            │
    // ├─────────────┼──────────────┼────────────────────────────────────────┤
    // │ rbp         │ old rbp      │ saved base pointer                     │
    // │ rbp-8       │ this ptr     │ 0x7FFF0080 (address of Widget object)  │
    // │ rbp-12      │ v param      │ 10 (constructor parameter)             │
    // └──────────────────────────────────────────────────────────────────────┘
    //
    // ASSEMBLY (.s lines 17-61):
    // Line 21: pushq %rbp              ; RSP-=8, save old base ptr
    // Line 24: movq  %rsp, %rbp        ; RBP = RSP (new frame)
    // Line 26: subq  $16, %rsp         ; RSP -= 16 (allocate locals)
    // Line 27: movq  %rdi, -8(%rbp)    ; *(RBP-8) = RDI = this = 0x7FFF0080
    // Line 28: movl  %esi, -12(%rbp)   ; *(RBP-12) = ESI = v = 10 = 0x0000000A
    // Line 29: movq  -8(%rbp), %rax    ; RAX = *(RBP-8) = this = 0x7FFF0080
    // Line 30: movl  -12(%rbp), %edx   ; EDX = *(RBP-12) = v = 10
    // Line 31: movl  %edx, (%rax)      ; *(RAX) = EDX → *(0x7FFF0080) = 10
    //                                  ; CORE OPERATION: val = v
    //
    // MEMORY TRACE:
    // Before line 31: 0x7FFF0080 = [?? ?? ?? ??] (garbage)
    // After  line 31: 0x7FFF0080 = [0A 00 00 00] (10 in little-endian)
    //
    // Register state at line 31:
    //   RAX = 0x7FFF0080 (this)
    //   EDX = 0x0000000A (10)
    //   Result: 4-byte write to address RAX
    //
    // Cycle count: 1 movl = 1 cycle (store to L1 cache)
    // Memory bandwidth: 4 bytes written
    //
    Widget(int v) : val(v) {
        std::cout << "PARAM CTOR: this=" << this << ", val=" << val << "\n"; 
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // COPY CTOR: Widget(const Widget& other)
    // Mangled: _ZN6WidgetC2ERKS_ (C2=ctor, RK=const ref, S_= Widget)
    // ═══════════════════════════════════════════════════════════════════════
    //
    // CALL SETUP (from main, lines 548-552):
    // Line 548: leaq -16(%rbp), %rdx   ; RDX = &b = 0x7FFF0080
    // Line 549: leaq -12(%rbp), %rax   ; RAX = &a = 0x7FFF0084
    // Line 550: movq %rdx, %rsi        ; RSI = &b (other param)
    // Line 551: movq %rax, %rdi        ; RDI = &a (this param)
    // Line 552: call _ZN6WidgetC1ERKS_ ; jump to copy ctor
    //
    // FUNCTION BODY (.s lines 76-131):
    // Line 80: pushq %rbp              ; save frame
    // Line 83: movq  %rsp, %rbp        ; new frame
    // Line 85: subq  $16, %rsp         ; locals
    // Line 86: movq  %rdi, -8(%rbp)    ; *(RBP-8) = this = 0x7FFF0084
    // Line 87: movq  %rsi, -16(%rbp)   ; *(RBP-16) = &other = 0x7FFF0080
    // Line 88: movq  -16(%rbp), %rax   ; RAX = &other = 0x7FFF0080
    // Line 89: movl  (%rax), %edx      ; EDX = *(RAX) = other.val = 10
    //                                  ; READ: 4 bytes from 0x7FFF0080
    // Line 90: movq  -8(%rbp), %rax    ; RAX = this = 0x7FFF0084
    // Line 91: movl  %edx, (%rax)      ; *(RAX) = 10
    //                                  ; WRITE: 4 bytes to 0x7FFF0084
    //                                  ; CORE: this->val = other.val
    //
    // MEMORY DIAGRAM:
    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ Address      │ Before       │ After        │ Operation              │
    // ├──────────────┼──────────────┼──────────────┼────────────────────────┤
    // │ 0x7FFF0080   │ [0A 00 00 00]│ [0A 00 00 00]│ READ (other.val=10)    │
    // │ 0x7FFF0084   │ [?? ?? ?? ??]│ [0A 00 00 00]│ WRITE (this->val=10)   │
    // └─────────────────────────────────────────────────────────────────────┘
    //
    // Instruction count: 2 movl (1 load + 1 store) = 2 ops
    // NO delete[] needed (object is GARBAGE, not old data)
    // NO self-assign check (object doesn't exist yet, can't be same)
    //
    Widget(const Widget& other) : val(other.val) {
        std::cout << "COPY CTOR: this=" << this << " <- &other=" << &other << ", val=" << val << "\n";
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // COPY ASSIGN: Widget& operator=(const Widget& other)
    // Mangled: _ZN6WidgetaSERKS_ (aS=assignment, RK=const ref)
    // ═══════════════════════════════════════════════════════════════════════
    //
    // CALL SETUP (from main, lines 602-606):
    // Line 602: leaq -12(%rbp), %rdx   ; RDX = &b = 0x7FFF0084
    // Line 603: leaq -16(%rbp), %rax   ; RAX = &a = 0x7FFF0080
    // Line 604: movq %rdx, %rsi        ; RSI = &b (other param)
    // Line 605: movq %rax, %rdi        ; RDI = &a (this param)
    // Line 606: call _ZN6WidgetaSERKS_ ; jump to copy assign
    //
    // FUNCTION BODY (.s lines 146-214):
    // Line 150: pushq %rbp
    // Line 153: movq  %rsp, %rbp
    // Line 155: subq  $16, %rsp
    // Line 156: movq  %rdi, -8(%rbp)   ; *(RBP-8) = this = 0x7FFF0080
    // Line 157: movq  %rsi, -16(%rbp)  ; *(RBP-16) = &other = 0x7FFF0084
    //
    // SELF-ASSIGN CHECK (.s lines 178-180):
    // Line 178: movq  -8(%rbp), %rax   ; RAX = this = 0x7FFF0080
    // Line 179: cmpq  -16(%rbp), %rax  ; compare this vs &other
    //                                  ; 0x7FFF0080 vs 0x7FFF0084
    //                                  ; ZF=0 (not equal), SF=1 (0x80 < 0x84)
    // Line 180: jne   .L4              ; ZF=0 → jump taken → do copy
    //
    // SELF-ASSIGN BRANCH (if this == &other):
    // Line 181-187: print "[SELF-ASSIGN]", return this
    //
    // NORMAL COPY (.L4, lines 188-209):
    // Line 189: movq  -16(%rbp), %rax  ; RAX = &other = 0x7FFF0084
    // Line 190: movl  (%rax), %edx     ; EDX = *(0x7FFF0084) = other.val = 20
    // Line 191: movq  -8(%rbp), %rax   ; RAX = this = 0x7FFF0080
    // Line 192: movl  %edx, (%rax)     ; *(0x7FFF0080) = 20
    //                                  ; CORE: this->val = other.val
    // Line 209: movq  -8(%rbp), %rax   ; RAX = this (return value)
    //
    // MEMORY DIAGRAM:
    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ Address      │ Before       │ After        │ Operation              │
    // ├──────────────┼──────────────┼──────────────┼────────────────────────┤
    // │ 0x7FFF0080   │ [05 00 00 00]│ [14 00 00 00]│ WRITE (5 → 20)         │
    // │ 0x7FFF0084   │ [14 00 00 00]│ [14 00 00 00]│ READ (other.val=20)    │
    // └─────────────────────────────────────────────────────────────────────┘
    //
    // SELF-ASSIGN EXAMPLE (a = a):
    // Call setup (lines 692-696):
    //   RDI = 0x7FFF0084 (this)
    //   RSI = 0x7FFF0084 (&other) ← SAME ADDRESS!
    // Line 179: cmpq → 0x7FFF0084 vs 0x7FFF0084 → ZF=1 (equal)
    // Line 180: jne .L4 → ZF=1 → NOT taken → skip copy
    // Result: Print "[SELF-ASSIGN]", return immediately
    //
    // WHY EXTRA WORK vs COPY CTOR:
    // 1. Self-assign check: cmpq + jne = 2 extra instructions
    // 2. (If heap): delete[] old data (not needed for int)
    // 3. Return this pointer: movq at end
    //
    // Instruction count: cmpq + jne + 2×movl + movq = 5 ops
    // Copy ctor: 2×movl = 2 ops
    // Ratio: 5/2 = 2.5× more instructions
    //
    Widget& operator=(const Widget& other) {
        // cmpq -16(%rbp), %rax → ZF set based on this vs &other
        std::cout << "COPY ASSIGN: this=" << this << " <- &other=" << &other;
        if (this == &other) {
            // jne not taken → execute this branch
            std::cout << " [SELF-ASSIGN DETECTED]\n";
            return *this;
        }
        // .L4: normal copy path
        // movl (%rax), %edx → load other.val
        // movl %edx, (%rax) → store to this->val
        val = other.val;
        std::cout << ", val=" << val << "\n";
        return *this;
        // movq -8(%rbp), %rax → return this pointer in RAX
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // MOVE CTOR: Widget(Widget&& other)
    // Mangled: _ZN6WidgetC2EOS_ (O=rvalue ref)
    // ═══════════════════════════════════════════════════════════════════════
    //
    // ASSEMBLY (.s lines 224-282):
    // Line 236: movq  -16(%rbp), %rax  ; RAX = &other
    // Line 237: movl  (%rax), %edx     ; EDX = other.val = 60
    // Line 238: movq  -8(%rbp), %rax   ; RAX = this
    // Line 239: movl  %edx, (%rax)     ; this->val = 60
    // Line 240: movq  -16(%rbp), %rax  ; RAX = &other
    // Line 241: movl  $0, (%rax)       ; other.val = 0 (ZERO OUT!)
    //
    // MEMORY DIAGRAM:
    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ Address      │ Before       │ After        │ Operation              │
    // ├──────────────┼──────────────┼──────────────┼────────────────────────┤
    // │ 0x7FFF0080   │ [3C 00 00 00]│ [00 00 00 00]│ other: 60 → 0          │
    // │ 0x7FFF0084   │ [?? ?? ?? ??]│ [3C 00 00 00]│ this: garbage → 60     │
    // └─────────────────────────────────────────────────────────────────────┘
    //
    // Instruction count: 4 movl = 4 ops (2 load, 2 store)
    // Extra vs copy ctor: movl $0, (%rax) zeroes source
    //
    Widget(Widget&& other) noexcept : val(other.val) {
        other.val = 0;
        // movl $0, (%rax) → immediate value 0 stored to other.val
        std::cout << "MOVE CTOR: this=" << this << " <- &other=" << &other << ", val=" << val << "\n";
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // MOVE ASSIGN: Widget& operator=(Widget&& other)
    // Mangled: _ZN6WidgetaSEOS_ (aS=assign, O=rvalue)
    // ═══════════════════════════════════════════════════════════════════════
    //
    // ASSEMBLY (.s lines 294-364):
    // Self-assign check: cmpq + jne (lines 326-328)
    // Normal path (.L8):
    //   Line 337: movq  -16(%rbp), %rax  ; RAX = &other
    //   Line 338: movl  (%rax), %edx     ; EDX = other.val
    //   Line 339: movq  -8(%rbp), %rax   ; RAX = this
    //   Line 340: movl  %edx, (%rax)     ; this->val = other.val
    //   Line 341: movq  -16(%rbp), %rax  ; RAX = &other
    //   Line 342: movl  $0, (%rax)       ; other.val = 0
    //
    Widget& operator=(Widget&& other) noexcept {
        std::cout << "MOVE ASSIGN: this=" << this << " <- &other=" << &other;
        if (this == &other) {
            std::cout << " [SELF-ASSIGN DETECTED]\n";
            return *this;
        }
        val = other.val;
        other.val = 0;
        std::cout << ", val=" << val << "\n";
        return *this;
    }
    
    ~Widget() {
        std::cout << "DTOR: this=" << this << ", val=" << val << "\n";
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // OPERATOR(): void operator()(const Widget& arg)
    // Mangled: _ZN6WidgetclERKS_ (cl=call operator)
    // ═══════════════════════════════════════════════════════════════════════
    //
    // CALL SETUP (lines 748-752):
    // Line 748: leaq -12(%rbp), %rdx   ; RDX = &bb = 0x7FFF0084
    // Line 749: leaq -16(%rbp), %rax   ; RAX = &a = 0x7FFF0080
    // Line 750: movq %rdx, %rsi        ; RSI = &bb (arg param)
    // Line 751: movq %rax, %rdi        ; RDI = &a (this param)
    // Line 752: call _ZN6WidgetclERKS_ ; call operator()
    //
    // PROOF: a(bb) calls operator(), not constructor
    // Constructor would be _ZN6WidgetC1ERKS_, not _ZN6WidgetclERKS_
    //
    void operator()(const Widget& arg) {
        std::cout << "OPERATOR(): this=" << this << " called with arg=" << &arg << ", arg.val=" << arg.val << "\n";
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN: PROOF OF WHICH FUNCTION IS CALLED
// ═══════════════════════════════════════════════════════════════════════════
//
// Assembly proof from .s file:
// Line 547: call _ZN6WidgetC1Ei       → Widget b(10)     → PARAM CTOR
// Line 552: call _ZN6WidgetC1ERKS_    → Widget a = b     → COPY CTOR (!)
// Line 606: call _ZN6WidgetaSERKS_    → a = b            → COPY ASSIGN
// Line 696: call _ZN6WidgetaSERKS_    → a = a            → COPY ASSIGN (self)
// Line 752: call _ZN6WidgetclERKS_    → a(bb)            → OPERATOR()
//
// KEY INSIGHT:
// "Widget a = b" → line 552 calls _ZN6WidgetC1ERKS_ (C1 = ctor)
// "a = b"        → line 606 calls _ZN6WidgetaSERKS_ (aS = assign)
//
// The "=" symbol means DIFFERENT things:
// - In declaration (TYPE present): initialization → constructor
// - In statement (no TYPE): assignment → operator=

int main() {
    std::cout << "=== Widget b(10) ===\n";
    Widget b(10);   // Line 547: call _ZN6WidgetC1Ei
    
    std::cout << "\n=== Widget a = b ===\n";
    Widget a = b;   // Line 552: call _ZN6WidgetC1ERKS_ ← COPY CTOR!
    
    std::cout << "\n=== a = b ===\n";
    a = b;          // Line 606: call _ZN6WidgetaSERKS_ ← COPY ASSIGN!
    
    return 0;
}
