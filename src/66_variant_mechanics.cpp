
#include <variant>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <stdexcept>

// -----------------------------------------------------------------------------
// USER INSTRUCTIONS:
// 1. Read src/66_variant_mechanics.md carefully.
// 2. Do the paper/pencil calculations first.
// 3. Fill in the TODO blocks below with proper code.
// 4. Run the code to verify your manual derivations.
// -----------------------------------------------------------------------------

// A sample custom type to use in variant
struct Circle {
    double radius;
    void print() const { std::cout << "Circle(" << radius << ")\n"; }
};

struct Square {
    double side;
    void print() const { std::cout << "Square(" << side << ")\n"; }
};

// 01. Define a variant type named 'Shape' capable of holding Circle, Square, or simple int (for debugging)
using Shape = std::variant<Circle, Square, int>;

// 02. Helper to print which index is active (without using visit yet)
void print_index(const Shape& s) {
    std::cout << "Current index: " << s.index() << "\n";
    // NOTE: std::variant has NO .type() method, only .index() returns size_t
}

int main() {
    std::cout << "--- 01. Basic variant mechanics ---\n";
    
    // TODO: Create a Shape holding a Circle with radius 5.0
    Shape s1 = Circle{5.0};
    
    // Verify index (Circle is 0th type?) -> indices are 0-based
    // TODO: Assert index is 0
    if (s1.index() == 0) {
        std::cout << "Index is 0 (Circle) as expected.\n";
    } else {
        std::cout << "Index is " << s1.index() << " (Expected 0)\n";
    }
    print_index(s1);

    // TODO: Reassign s1 to hold a Square with side 2.0
    s1 = Square{2.0};
    // Verify index
    print_index(s1);

    // TODO: Reassign s1 to hold int 42
    s1 = 42;
    print_index(s1);

    std::cout << "--- 02. std::get and exceptions ---\n";
    // Current s1 holds int(42).
    // TODO: Try to get Circle from s1 (which holds int). Catch the exception.
    try {
        std::get<Circle>(s1);
    } catch (const std::bad_variant_access& e) {
        std::cout << "Caught expected error: " << e.what() << "\n";
    }

    // TODO: Get the int value safely
    int val = std::get<int>(s1);
    std::cout << "Got int value: " << val << "\n";

    std::cout << "--- 03. std::get_if (non-throwing) ---\n";
    // TODO: Use get_if to check for Square. Should return nullptr.
    if (auto* ptr = std::get_if<Square>(&s1)) {
        ptr->print();
    } else {
        std::cout << "Not a Square\n";
    }

    // TODO: Use get_if to check for int. Should return pointer to value.
    if (auto* ptr = std::get_if<int>(&s1)) {
        std::cout << "Found int: " << *ptr << "\n";
    }

    std::cout << "--- 04. std::visit (The Power) ---\n";
    // Restore s1 to Square
    s1 = Square{10.0};

    // TODO: Use std::visit with a lambda that handles all 3 types (Circle, Square, int)
    // The lambda should print "Visiting [Type]: [Value]"
    // usage: std::visit([](auto&& arg) { ... }, s1);
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Circle>) {
            std::cout << "Visiting Circle: radius=" << arg.radius << "\n";
        } else if constexpr (std::is_same_v<T, Square>) {
            std::cout << "Visiting Square: side=" << arg.side << "\n";
        } else if constexpr (std::is_same_v<T, int>) {
            std::cout << "Visiting int: val=" << arg << "\n";
        }
    }, s1);
    
    
    std::cout << "\n--- 05. Size and Layout ---\n";
    // TODO: Print sizeof(Shape). 
    // Analyze why: sizeof(largest_member) + align + sizeof(index) + align
    std::cout << "sizeof(Circle): " << sizeof(Circle) << "\n";
    std::cout << "sizeof(Square): " << sizeof(Square) << "\n";
    std::cout << "sizeof(int): " << sizeof(int) << "\n";
    std::cout << "sizeof(Shape): " << sizeof(Shape) << "\n";

    return 0;
}
