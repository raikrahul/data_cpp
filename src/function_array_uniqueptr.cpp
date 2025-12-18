#include <iostream>
#include <array>
#include <memory>

// ════════════════════════════════════════════════════════════════════════════
// YOUR CODE (WRONG):
// ════════════════════════════════════════════════════════════════════════════
// void fn(std::array<std::unique_ptr<int>, 10> p) {  // COPY by value ✗
//     for e in p {  // Invalid syntax ✗
//         *p +=1;   // p is array, not pointer ✗
//     }
// }

// ════════════════════════════════════════════════════════════════════════════
// ERROR 1: Parameter by VALUE
// ════════════════════════════════════════════════════════════════════════════
// std::array<std::unique_ptr<int>, 10> p
//                                      ^
//                                      By value → COPY
// unique_ptr CANNOT be copied (deleted copy constructor)
// COMPILE ERROR: use of deleted function

// FIX: Pass by REFERENCE
// std::array<std::unique_ptr<int>, 10>& p
//                                      ^
//                                      By reference → NO COPY

// ════════════════════════════════════════════════════════════════════════════
// ERROR 2: Loop syntax
// ════════════════════════════════════════════════════════════════════════════
// for e in p  // This is Python, not C++ ✗

// FIX: C++ range-based for
// for (auto& e : p)  // C++11+ ✓
//      ^^^^^ ^   ^
//      |     |   container
//      |     element
//      auto deduces type

// ════════════════════════════════════════════════════════════════════════════
// ERROR 3: Dereference wrong variable
// ════════════════════════════════════════════════════════════════════════════
// *p += 1;  // p is array, not unique_ptr ✗

// FIX: Dereference loop variable
// *e += 1;  // e is unique_ptr<int>& ✓

// ════════════════════════════════════════════════════════════════════════════
// CORRECT VERSION 1: Pass by non-const reference
// ════════════════════════════════════════════════════════════════════════════
// Allows modification of the pointed-to values
void increment_all(std::array<std::unique_ptr<int>, 10>& p) {
    // p@Stack → caller's array (NO COPY)
    // p[i] → caller's unique_ptr (NO COPY)
    // *p[i] → caller's int on heap (MODIFY)
    
    for (auto& ptr : p) {
        // ptr is unique_ptr<int>&
        // *ptr is int&
        *ptr += 1;  // Increment the int value
    }
}

// ════════════════════════════════════════════════════════════════════════════
// CORRECT VERSION 2: Pass by const reference (read-only)
// ════════════════════════════════════════════════════════════════════════════
void print_all(const std::array<std::unique_ptr<int>, 10>& p) {
    // const → cannot modify array or pointers
    // Can still read pointed-to values
    
    for (const auto& ptr : p) {
        // ptr is const unique_ptr<int>&
        // *ptr is const int&
        std::cout << *ptr << " ";
    }
    std::cout << "\n";
}

int main() {
    // ════════════════════════════════════════════════════════════════════════════
    // TEST: Create and initialize array
    // ════════════════════════════════════════════════════════════════════════════
    std::array<std::unique_ptr<int>, 10> arr;
    
    // Initialize: arr[i] → int(i) on heap
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = std::make_unique<int>(static_cast<int>(i));
    }
    
    std::cout << "=== INITIAL VALUES ===\n";
    print_all(arr);
    // OUTPUT: 0 1 2 3 4 5 6 7 8 9
    
    // ════════════════════════════════════════════════════════════════════════════
    // CALL increment_all (modifies through reference)
    // ════════════════════════════════════════════════════════════════════════════
    // OPERATION: increment_all(arr)
    // STEP 1: arr passed by reference → NO COPY
    // STEP 2: for loop iterates arr[0..9]
    // STEP 3: *arr[0] += 1 → 0 → 1
    //         *arr[1] += 1 → 1 → 2
    //         ...
    //         *arr[9] += 1 → 9 → 10
    increment_all(arr);
    
    std::cout << "\n=== AFTER INCREMENT ===\n";
    print_all(arr);
    // OUTPUT: 1 2 3 4 5 6 7 8 9 10
    
    // ════════════════════════════════════════════════════════════════════════════
    // MEMORY TRACE:
    // ════════════════════════════════════════════════════════════════════════════
    // main() stack:
    //   arr@0x7ffc... (80B) → [ptr0, ptr1, ..., ptr9]
    //
    // increment_all() stack:
    //   p@0x7ffc... (8B reference) → SAME as arr (NO COPY)
    //
    // Heap (unchanged addresses):
    //   0x61ba695906c0: 1 (was 0)
    //   0x61ba695906e0: 2 (was 1)
    //   ...
    //   0x61ba695907e0: 10 (was 9)
    
    // ════════════════════════════════════════════════════════════════════════════
    // CALCULATIONS:
    // ════════════════════════════════════════════════════════════════════════════
    // Pass by value (if unique_ptr was copyable):
    //   Stack: 80B (original array)
    //   Stack: 80B (function copy)
    //   Heap: 40B (original data)
    //   Heap: 40B (copied data)
    //   Total: 240B
    //   Time: O(N) copy
    //
    // Pass by reference:
    //   Stack: 80B (original array)
    //   Stack: 8B (reference)
    //   Heap: 40B (original data)
    //   Total: 128B
    //   Time: O(1) (no copy)
    //   Savings: 112B (-46.7%)
    //
    // N=1000:
    //   By value: 8000B + 8000B + 4000B + 4000B = 24000B
    //   By reference: 8000B + 8B + 4000B = 12008B
    //   Savings: 11992B (-50%)
    
    return 0;
}
