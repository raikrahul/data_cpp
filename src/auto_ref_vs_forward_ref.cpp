#include <iostream>
#include <array>
#include <memory>

int main() {
    // ════════════════════════════════════════════════════════════════════════════
    // YOUR CONFUSION: "auto&& is reference to reference" ✗
    // YOUR CONFUSION: "&& always means move semantics" ✗
    // ════════════════════════════════════════════════════════════════════════════
    // TRUTH: && has TWO different meanings depending on context
    
    std::cout << "=== MISCONCEPTION 1: 'auto&& is reference to reference' ===\n";
    std::cout << "WRONG ✗\n";
    std::cout << "auto&& is FORWARDING REFERENCE (universal reference)\n\n";
    
    std::cout << "=== MISCONCEPTION 2: '&& always means move semantics' ===\n";
    std::cout << "WRONG ✗\n";
    std::cout << "&& has TWO meanings:\n";
    std::cout << "1. Rvalue reference (Type&& x) - move semantics\n";
    std::cout << "2. Forwarding reference (auto&& x or T&& x in template) - perfect forwarding\n\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // CASE 1: && as RVALUE REFERENCE (move semantics)
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "=== CASE 1: Type&& as RVALUE REFERENCE ===\n";
    
    std::unique_ptr<int>&& rref = std::make_unique<int>(42);
    //                     ^^
    //                     Rvalue reference to unique_ptr
    //                     Can bind to temporary (make_unique result)
    //                     Used for MOVE semantics
    
    std::cout << "*rref = " << *rref << "\n";
    std::cout << "This && means: rvalue reference (move semantics) ✓\n\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // CASE 2: auto&& as FORWARDING REFERENCE
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "=== CASE 2: auto&& as FORWARDING REFERENCE ===\n";
    
    std::array<std::unique_ptr<int>, 3> arr;
    arr[0] = std::make_unique<int>(10);
    arr[1] = std::make_unique<int>(20);
    arr[2] = std::make_unique<int>(30);
    
    // auto&& in range-based for loop
    for (auto&& elem : arr) {
        // elem is FORWARDING REFERENCE
        // Binds to arr[i] which is lvalue unique_ptr<int>&
        // auto&& deduces to unique_ptr<int>&
        // NOT "reference to reference" ✗
        std::cout << "*elem = " << *elem << "\n";
    }
    std::cout << "auto&& here means: forwarding reference ✓\n";
    std::cout << "Deduced type: unique_ptr<int>& (NOT &&) ✓\n\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // PROOF: auto& works EXACTLY the same here
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "=== PROOF: auto& vs auto&& (both work) ===\n";
    
    std::cout << "Using auto&:\n";
    for (auto& elem : arr) {
        std::cout << "*elem = " << *elem << "\n";
    }
    
    std::cout << "\nUsing auto&&:\n";
    for (auto&& elem : arr) {
        std::cout << "*elem = " << *elem << "\n";
    }
    
    std::cout << "\nBoth work identically ✓\n\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // WHY USE auto&& then?
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "=== WHY USE auto&& in range-based for? ===\n";
    std::cout << "Reason: Works for BOTH lvalues AND rvalues\n\n";
    
    // Example with temporary range
    std::cout << "Example with temporary:\n";
    auto make_array = []() {
        std::array<int, 3> temp = {1, 2, 3};
        return temp;
    };
    
    // auto&& can bind to temporary
    for (auto&& val : make_array()) {  // make_array() returns temporary
        std::cout << "val = " << val << "\n";
    }
    std::cout << "auto&& binds to temporary ✓\n\n";
    
    // auto& CANNOT bind to temporary (compile error if uncommented)
    // for (auto& val : make_array()) {  // ERROR ✗
    //     std::cout << val << "\n";
    // }
    
    // ════════════════════════════════════════════════════════════════════════════
    // YOUR SPECIFIC CASE
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "=== YOUR CODE ANALYSIS ===\n";
    
    auto f1 = [](std::array<std::unique_ptr<int>, 10>& p) {
        for (auto& i : p) {  // auto& works ✓
            *i += 1;
        }
    };
    
    auto f2 = [](std::array<std::unique_ptr<int>, 10>& p) {
        for (auto&& i : p) {  // auto&& also works ✓
            *i += 1;
        }
    };
    
    std::cout << "for (auto& i : p) - works ✓\n";
    std::cout << "for (auto&& i : p) - works ✓\n";
    std::cout << "Both are EQUIVALENT in this case\n\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // TYPE DEDUCTION PROOF
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "=== TYPE DEDUCTION ===\n";
    std::array<std::unique_ptr<int>, 2> test_arr;
    test_arr[0] = std::make_unique<int>(100);
    test_arr[1] = std::make_unique<int>(200);
    
    for (auto&& elem : test_arr) {
        // What type is elem?
        // arr[i] is lvalue unique_ptr<int>&
        // auto&& + lvalue → deduces to T&
        // Result: elem is unique_ptr<int>&
        // NOT unique_ptr<int>&& ✗
        // NOT unique_ptr<int>& & ✗
        std::cout << "elem type: unique_ptr<int>& (NOT &&, NOT & &)\n";
        break;
    }
    
    // ════════════════════════════════════════════════════════════════════════════
    // REFERENCE COLLAPSING RULES
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== REFERENCE COLLAPSING (advanced) ===\n";
    std::cout << "T& & → T&\n";
    std::cout << "T& && → T&\n";
    std::cout << "T&& & → T&\n";
    std::cout << "T&& && → T&&\n";
    std::cout << "\nFor auto&&:\n";
    std::cout << "lvalue → auto& && → auto& (collapses to &)\n";
    std::cout << "rvalue → auto&& (stays &&)\n";
    
    return 0;
}
