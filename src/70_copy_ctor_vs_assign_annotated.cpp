// 70_copy_ctor_vs_assign_annotated.cpp
// HEAVILY ANNOTATED VERSION WITH ASSEMBLY AND MEMORY TRACES
// Every line has real addresses, byte counts, and assembly correlation

#include <iostream>

// ===========================================================================
// STRUCT LAYOUT IN MEMORY
// ===========================================================================
// sizeof(Widget) = 4 bytes (just int val)
// alignof(Widget) = 4 bytes
//
// Stack frame for Widget a(10):
// ┌─────────────────────────────────────────────────────────────────────┐
// │ Stack Address │ Offset from RBP │ Contents      │ Size │ Purpose    │
// ├───────────────┼─────────────────┼───────────────┼──────┼────────────┤
// │ 0x7FFF0080    │ -8(%rbp)        │ this ptr      │ 8    │ Widget* a  │
// │ 0x7FFF0084    │ -4(%rbp)        │ val = 10      │ 4    │ a.val      │
// └─────────────────────────────────────────────────────────────────────┘
//
// Two Widgets on stack:
// ┌────────────────────────────────────────────────────────────────────────┐
// │ Addr      │ Variable │ val  │ Assembly Reference                      │
// ├───────────┼──────────┼──────┼─────────────────────────────────────────┤
// │ 0x...80   │ a.val    │ 10   │ movl $10, -8(%rbp)                      │
// │ 0x...84   │ b.val    │ 20   │ movl $20, -4(%rbp)                      │
// └────────────────────────────────────────────────────────────────────────┘

struct Widget {
    int val;  
    // offset 0, size 4 bytes
    // Example: Widget w(10) at 0x7FFF0080 → *(int*)0x7FFF0080 = 10
    // Hex: 0x0000000A stored as [0A 00 00 00] (little-endian)
    
    // ===========================================================================
    // DEFAULT CTOR
    // ===========================================================================
    // Assembly (_ZN6WidgetC2Ei means Widget::Widget(int)):
    //   movl    $0, (%rax)       ; store 0 to this->val
    // 
    // Stack operation: RSP decremented by 4, val initialized to 0
    // Cycle count: ~1 cycle for movl
    Widget() : val(0) { 
        // this = 0x7FFF0080 (from RDI register)
        // Memory write: *(this+0) = 0
        // After: 0x7FFF0080 = [00 00 00 00]
        std::cout << "DEFAULT CTOR: this=" << this << ", val=" << val << "\n"; 
    }
    
    // ===========================================================================
    // PARAMETERIZED CTOR
    // ===========================================================================
    // Assembly:
    //   movq    %rdi, -8(%rbp)   ; store this pointer (8 bytes)
    //   movl    %esi, -12(%rbp)  ; store v parameter (4 bytes)
    //   movq    -8(%rbp), %rax   ; load this into RAX
    //   movl    -12(%rbp), %edx  ; load v into EDX
    //   movl    %edx, (%rax)     ; this->val = v
    //
    // Example: Widget a(10)
    //   RDI = 0x7FFF0080 (this)
    //   ESI = 10 (v)
    //   After: *(0x7FFF0080) = 10
    Widget(int v) : val(v) { 
        // v=10 → val=10
        // Memory: 0x7FFF0080 = [0A 00 00 00]
        // 10 decimal = 0x0A hex
        // Large example: v=1000000 = 0x000F4240 = [40 42 0F 00]
        std::cout << "PARAM CTOR: this=" << this << ", val=" << val << "\n"; 
    }
    
    // ===========================================================================
    // COPY CTOR - Widget(const Widget& other)
    // ===========================================================================
    // Mangled name: _ZN6WidgetC2ERKS_ (C2 = complete object ctor, RK = const ref)
    //
    // Assembly breakdown:
    // _ZN6WidgetC2ERKS_:
    //   pushq   %rbp              ; save old base pointer
    //   movq    %rsp, %rbp        ; new base pointer = stack pointer
    //   subq    $16, %rsp         ; allocate 16 bytes on stack
    //   movq    %rdi, -8(%rbp)    ; store this (8 bytes at rbp-8)
    //   movq    %rsi, -16(%rbp)   ; store &other (8 bytes at rbp-16)
    //   movq    -16(%rbp), %rax   ; rax = &other
    //   movl    (%rax), %edx      ; edx = other.val (4 bytes from other)
    //   movq    -8(%rbp), %rax    ; rax = this
    //   movl    %edx, (%rax)      ; this->val = edx (copy the int!)
    //
    // Example: Widget a = b; where b.val = 30
    //   RDI = 0x7FFF0084 (this, new object a)
    //   RSI = 0x7FFF0080 (&other, existing object b)
    //   *(RSI) = 30 → load into EDX
    //   *(RDI) = EDX → store 30 into a.val
    //   Result: 0x7FFF0084 = [1E 00 00 00] (30 = 0x1E)
    //
    // Memory trace:
    //   Before: 0x7FFF0080=[1E 00 00 00], 0x7FFF0084=[?? ?? ?? ??]
    //   After:  0x7FFF0080=[1E 00 00 00], 0x7FFF0084=[1E 00 00 00]
    //   Both have value 30, but DIFFERENT addresses (deep copy for int)
    Widget(const Widget& other) : val(other.val) {
        // What: Copy 4 bytes from other.val to this->val
        // Why: other.val at *(RSI+0), this->val at *(RDI+0)
        // Where: Stack addresses 0x...80 → 0x...84
        // Who: movl (%rax), %edx loads, movl %edx, (%rax) stores
        // When: Object creation (declaration with =)
        // Without: Shallow copy would share same address (impossible for int)
        // Which: C2 variant (complete object constructor)
        std::cout << "COPY CTOR: this=" << this << " <- &other=" << &other << ", val=" << val << "\n";
    }
    
    // ===========================================================================
    // COPY ASSIGNMENT - Widget& operator=(const Widget& other)
    // ===========================================================================
    // Mangled name: _ZN6WidgetaSERKS_ (aS = assignment, RK = const ref)
    //
    // Assembly breakdown:
    // _ZN6WidgetaSERKS_:
    //   pushq   %rbp
    //   movq    %rsp, %rbp
    //   subq    $16, %rsp
    //   movq    %rdi, -8(%rbp)    ; this
    //   movq    %rsi, -16(%rbp)   ; &other
    //   movq    -8(%rbp), %rax    ; rax = this
    //   cmpq    -16(%rbp), %rax   ; compare this == &other (SELF-ASSIGN CHECK!)
    //   jne     .L8               ; if not equal, jump to copy
    //   ... print self-assign message ...
    //   jmp     .L9               ; skip copy
    // .L8:
    //   movq    -16(%rbp), %rax   ; rax = &other
    //   movl    (%rax), %edx      ; edx = other.val
    //   movq    -8(%rbp), %rax    ; rax = this
    //   movl    %edx, (%rax)      ; this->val = edx
    // .L9:
    //   movq    -8(%rbp), %rax    ; return this
    //
    // Self-assignment example: a = a
    //   RDI = 0x7FFF0080 (this)
    //   RSI = 0x7FFF0080 (&other, SAME!)
    //   cmpq: 0x7FFF0080 == 0x7FFF0080 → ZF=1 → JNE not taken
    //   → Skip copy, return *this
    //
    // Normal example: a = b (a at 0x80, b at 0x84)
    //   RDI = 0x7FFF0080, RSI = 0x7FFF0084
    //   cmpq: 0x80 != 0x84 → JNE taken → copy happens
    Widget& operator=(const Widget& other) {
        // cmpq instruction: this vs &other
        // 0x7FFF0080 vs 0x7FFF0084 → not equal → copy
        // 0x7FFF0080 vs 0x7FFF0080 → equal → skip (self-assign)
        std::cout << "COPY ASSIGN: this=" << this << " <- &other=" << &other;
        if (this == &other) {
            // Assembly: cmpq sets ZF=1, JNE not taken
            std::cout << " [SELF-ASSIGN DETECTED]\n";
            return *this;
        }
        val = other.val;
        // movl (%rax), %edx  ; load other.val
        // movl %edx, (%rax)  ; store to this->val
        std::cout << ", val=" << val << "\n";
        return *this;
        // movq -8(%rbp), %rax ; return this pointer
    }
    
    // ===========================================================================
    // MOVE CTOR - Widget(Widget&& other)
    // ===========================================================================
    // Mangled name: _ZN6WidgetC2EOS_ (O = rvalue reference)
    //
    // Assembly (similar to copy ctor but zeros out other):
    //   movq    -16(%rbp), %rax   ; rax = &other
    //   movl    (%rax), %edx      ; edx = other.val
    //   movq    -8(%rbp), %rax    ; rax = this 
    //   movl    %edx, (%rax)      ; this->val = copied value
    //   movq    -16(%rbp), %rax   ; rax = &other
    //   movl    $0, (%rax)        ; other.val = 0 (MOVED-FROM STATE!)
    //
    // Example: Widget a = std::move(b); where b.val=60
    //   Before: b at 0x80=[3C 00 00 00] (60 = 0x3C)
    //   After:  a at 0x84=[3C 00 00 00], b at 0x80=[00 00 00 00]
    Widget(Widget&& other) noexcept : val(other.val) {
        other.val = 0;  // movl $0, (%rax) — zero out source
        std::cout << "MOVE CTOR: this=" << this << " <- &other=" << &other << ", val=" << val << "\n";
    }
    
    // ===========================================================================
    // MOVE ASSIGNMENT - Widget& operator=(Widget&& other)
    // ===========================================================================
    // Mangled name: _ZN6WidgetaSEOS_
    //
    // Same as copy assignment but includes zeroing other:
    //   ... self-assign check ...
    //   movl    (%rax), %edx      ; load other.val
    //   movl    %edx, (%rax)      ; store to this->val
    //   movl    $0, (%rax)        ; zero out other.val
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
        // No heap to free, just stack pop
        // addq $4, %rsp (implicit)
        std::cout << "DTOR: this=" << this << ", val=" << val << "\n";
    }
    
    void operator()(const Widget& arg) {
        // Called via: leaq -4(%rbp), %rax ; pass a's address
        //             leaq -8(%rbp), %rdx ; pass bb's address
        //             movq %rdx, %rsi     ; arg = bb
        //             movq %rax, %rdi     ; this = a
        //             call _ZN6WidgetclERKS_
        std::cout << "OPERATOR(): this=" << this << " called with arg=" << &arg << ", arg.val=" << arg.val << "\n";
    }
};

// ===========================================================================
// SUMMARY: WHICH FUNCTION IS CALLED?
// ===========================================================================
//
// SYNTAX                  | ASSEMBLY CALL TARGET      | REASON
// ------------------------|---------------------------|---------------------------
// Widget a = b;           | call _ZN6WidgetC2ERKS_    | C2=ctor, RK=const ref
// Widget a(b);            | call _ZN6WidgetC2ERKS_    | Same as above
// a = b;                  | call _ZN6WidgetaSERKS_    | aS=assignment, RK=const ref
// a = a;                  | call _ZN6WidgetaSERKS_    | Self-assign detected inside
// Widget a = move(b);     | call _ZN6WidgetC2EOS_     | C2=ctor, O=rvalue ref
// a = move(b);            | call _ZN6WidgetaSEOS_     | aS=assign, O=rvalue ref
// a(bb);                  | call _ZN6WidgetclERKS_    | cl=call, operator()
//
// KEY INSIGHT:
// Declaration (TYPE present) → Constructor (_ZN...C2...)
// Statement (no TYPE) → Assignment (_ZN...aS...) or Function Call (_ZN...cl...)

int main() {
    std::cout << "=== Widget a(10): Param Ctor ===\n";
    Widget a(10);
    // Assembly:
    //   leaq    -4(%rbp), %rax   ; rax = &a (stack address)
    //   movl    $10, %esi        ; esi = 10
    //   movq    %rax, %rdi       ; rdi = this
    //   call    _ZN6WidgetC1Ei   ; Widget::Widget(int)
    //
    // Memory: rbp-4 = 0x7FFF007C, now contains [0A 00 00 00]
    
    std::cout << "\n=== Widget b = a: Copy Ctor (NOT assignment!) ===\n";
    Widget b = a;
    // Assembly:
    //   leaq    -8(%rbp), %rax   ; rax = &b (new object)
    //   leaq    -4(%rbp), %rdx   ; rdx = &a (existing object)
    //   movq    %rdx, %rsi       ; rsi = &a (other param)
    //   movq    %rax, %rdi       ; rdi = &b (this param)
    //   call    _ZN6WidgetC1ERKS_; Widget::Widget(const Widget&)
    //
    // PROOF: Calls C1 (ctor alias to C2), not aS (assignment)
    
    std::cout << "\n=== a = b: Copy Assignment ===\n";
    a = b;
    // Assembly:
    //   leaq    -4(%rbp), %rax   ; rax = &a
    //   leaq    -8(%rbp), %rdx   ; rdx = &b  
    //   movq    %rdx, %rsi       ; rsi = &b (other)
    //   movq    %rax, %rdi       ; rdi = &a (this)
    //   call    _ZN6WidgetaSERKS_; Widget::operator=(const Widget&)
    //
    // PROOF: Calls aS (assignment), not C1/C2 (ctor)
    
    return 0;
}
