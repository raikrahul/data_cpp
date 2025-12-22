// 70_copy_ctor_vs_assign.cpp
// PROOF: When copy constructor vs copy assignment is called
// Compile with: g++ -std=c++20 -O0 -S -o 70_copy.s 70_copy_ctor_vs_assign.cpp

#include <iostream>

struct Widget {
    int val;
    
    // Default ctor
    Widget() : val(0) { 
        std::cout << "DEFAULT CTOR: this=" << this << ", val=" << val << "\n"; 
    }
    
    // Parameterized ctor
    Widget(int v) : val(v) { 
        std::cout << "PARAM CTOR: this=" << this << ", val=" << val << "\n"; 
    }
    
    // Copy ctor
    Widget(const Widget& other) : val(other.val) {
        std::cout << "COPY CTOR: this=" << this << " <- &other=" << &other << ", val=" << val << "\n";
    }
    
    // Copy assignment
    Widget& operator=(const Widget& other) {
        std::cout << "COPY ASSIGN: this=" << this << " <- &other=" << &other;
        if (this == &other) {
            std::cout << " [SELF-ASSIGN DETECTED]\n";
            return *this;
        }
        val = other.val;
        std::cout << ", val=" << val << "\n";
        return *this;
    }
    
    // Move ctor
    Widget(Widget&& other) noexcept : val(other.val) {
        other.val = 0;
        std::cout << "MOVE CTOR: this=" << this << " <- &other=" << &other << ", val=" << val << "\n";
    }
    
    // Move assignment
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
    
    // operator() - function call operator
    void operator()(const Widget& arg) {
        std::cout << "OPERATOR(): this=" << this << " called with arg=" << &arg << ", arg.val=" << arg.val << "\n";
    }
};

int main() {
    std::cout << "=== CASE 1: Widget a = b; (b exists) ===\n";
    // Step 1: b is constructed
    // Step 2: a is INITIALIZED from b → COPY CTOR (not assignment!)
    // Why? 'a' does not exist yet. This is initialization, not assignment.
    {
        Widget b(10);           // PARAM CTOR
        Widget a = b;           // COPY CTOR (a is being created)
        std::cout << "a.val=" << a.val << ", b.val=" << b.val << "\n";
    }
    std::cout << "\n";

    std::cout << "=== CASE 2: a = b; (both exist) ===\n";
    // Step 1: a exists
    // Step 2: b exists
    // Step 3: a = b → COPY ASSIGNMENT (a already exists, just copying data)
    {
        Widget a(5);            // PARAM CTOR
        Widget b(20);           // PARAM CTOR
        a = b;                  // COPY ASSIGN
        std::cout << "a.val=" << a.val << ", b.val=" << b.val << "\n";
    }
    std::cout << "\n";

    std::cout << "=== CASE 3: Widget a(b); (b exists) ===\n";
    // Explicit copy construction syntax
    // Same as Widget a = b; → COPY CTOR
    {
        Widget b(30);           // PARAM CTOR
        Widget a(b);            // COPY CTOR
        std::cout << "a.val=" << a.val << "\n";
    }
    std::cout << "\n";

    std::cout << "=== CASE 4: a = a; (self-assignment) ===\n";
    // a already exists, a = a → COPY ASSIGNMENT
    // Self-assignment check should detect this
    {
        Widget a(40);           // PARAM CTOR
        a = a;                  // COPY ASSIGN (self)
        std::cout << "a.val=" << a.val << "\n";
    }
    std::cout << "\n";

    std::cout << "=== CASE 5: Widget a(a); ??? ===\n";
    // This is ILL-FORMED! You cannot use 'a' before it's constructed.
    // Compiler error: 'a' was not declared in this scope (if a doesn't exist)
    // If a exists: Widget a(a); would be a redefinition error.
    // SKIPPED - won't compile
    std::cout << "SKIPPED: Widget a(a); is ill-formed.\n";
    std::cout << "\n";

    std::cout << "=== CASE 6: a(bb); where a already exists ===\n";
    // a exists, bb exists
    // a(bb) → calls a.operator()(bb) → NOT construction
    {
        Widget a(100);          // PARAM CTOR
        Widget bb(200);         // PARAM CTOR
        a(bb);                  // OPERATOR() call
        std::cout << "a.val=" << a.val << ", bb.val=" << bb.val << "\n";
    }
    std::cout << "\n";
    std::cout << "\n";

    std::cout << "=== CASE 7: Widget a(cc); when a does not exist, cc exists ===\n";
    // cc exists, a does not exist
    // Widget a(cc); → COPY CTOR (a is being created from cc)
    {
        Widget cc(50);          // PARAM CTOR
        Widget a(cc);           // COPY CTOR
        std::cout << "a.val=" << a.val << "\n";
    }
    std::cout << "\n";

    std::cout << "=== CASE 8: Widget a = std::move(b); ===\n";
    // a does not exist, b exists
    // MOVE CTOR (a is being created, stealing from b)
    {
        Widget b(60);           // PARAM CTOR
        Widget a = std::move(b);// MOVE CTOR
        std::cout << "a.val=" << a.val << ", b.val=" << b.val << "\n";
    }
    std::cout << "\n";

    std::cout << "=== CASE 9: a = std::move(b); (both exist) ===\n";
    // a exists, b exists
    // MOVE ASSIGNMENT (a already exists, stealing from b)
    {
        Widget a(70);           // PARAM CTOR
        Widget b(80);           // PARAM CTOR
        a = std::move(b);       // MOVE ASSIGN
        std::cout << "a.val=" << a.val << ", b.val=" << b.val << "\n";
    }
    std::cout << "\n";

    return 0;
}

// ===========================================================================
// SUMMARY TABLE
// ===========================================================================
// | Syntax              | a exists? | Which is called?     | Reason                    |
// |---------------------|-----------|----------------------|---------------------------|
// | Widget a = b;       | NO        | COPY CTOR            | a is being created        |
// | Widget a(b);        | NO        | COPY CTOR            | a is being created        |
// | a = b;              | YES       | COPY ASSIGNMENT      | a exists, just copy data  |
// | a = a;              | YES       | COPY ASSIGNMENT      | self-assign, check needed |
// | Widget a(a);        | NO        | ILL-FORMED           | can't use a before create |
// | a(b);               | YES       | operator() call      | not construction          |
// | Widget a = move(b); | NO        | MOVE CTOR            | a is being created        |
// | a = move(b);        | YES       | MOVE ASSIGNMENT      | a exists, steal data      |
// ===========================================================================

// C++ DESIGN RULE:
// "=" in DECLARATION (with type) → INITIALIZATION → CONSTRUCTOR
// "=" in STATEMENT (no type) → ASSIGNMENT → operator=
//
// Widget a = b;   ← Declaration with type "Widget" → Copy Ctor
// a = b;          ← Statement, no type → Copy Assign
