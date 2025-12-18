#include <iostream>
#include <array>
#include <memory>
#include <algorithm>
#include <ranges>

int main() {
    // ════════════════════════════════════════════════════════════════════════════
    // GOAL: Initialize array of unique_ptr using ranges::for_each
    // ════════════════════════════════════════════════════════════════════════════
    // REQUIREMENT: Each unique_ptr<int> should point to int with value 1
    // METHOD: ranges::for_each(range, function)
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 1: Declare array
    // ════════════════════════════════════════════════════════════════════════════
    // p@Stack: 80 bytes (10 × 8B pointers)
    // Initial state: all nullptr (default constructed unique_ptr)
    std::array<std::unique_ptr<int>, 10> p;
    
    std::cout << "=== BEFORE INITIALIZATION ===\n";
    std::cout << "sizeof(p) = " << sizeof(p) << " bytes\n";  // OUTPUT: 80
    std::cout << "p[0].get() = " << p[0].get() << " (nullptr)\n";  // OUTPUT: 0
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 2: Understanding ranges::for_each
    // ════════════════════════════════════════════════════════════════════════════
    // SIGNATURE: ranges::for_each(Range, Function)
    //   Range: container to iterate over (p)
    //   Function: lambda that receives REFERENCE to each element
    //
    // ITERATION:
    // i=0: function receives p[0] as unique_ptr<int>&
    // i=1: function receives p[1] as unique_ptr<int>&
    // ...
    // i=9: function receives p[9] as unique_ptr<int>&
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 3: Lambda function for initialization
    // ════════════════════════════════════════════════════════════════════════════
    // LAMBDA: [](auto& ptr) { ptr = make_unique<int>(1); }
    //         ^^    ^^^^^     ^^^^^^^^^^^^^^^^^^^^^^^^^^
    //         |     |         BODY: assign new unique_ptr
    //         |     PARAM: reference to unique_ptr<int>
    //         CAPTURE: empty (stateless lambda)
    //
    // MEMORY OPERATION (per iteration):
    // 1. make_unique<int>(1) → allocate 4B heap, store value 1
    // 2. ptr = ... → move-assign to array element
    // 3. Old ptr (nullptr) deleted (no-op, already null)
    
    std::cout << "\n=== INITIALIZATION WITH ranges::for_each ===\n";
    
    std::ranges::for_each(p, [](auto& ptr) {
        // ptr is unique_ptr<int>&
        // Allocate new int on heap with value 1
        ptr = std::make_unique<int>(1);
        std::cout << "Allocated: " << ptr.get() << ", value = " << *ptr << "\n";
    });
    
    // OUTPUT (example):
    // Allocated: 0x5e42643b76c0, value = 1
    // Allocated: 0x5e42643b76e0, value = 1
    // ...
    // Allocated: 0x5e42643b77e0, value = 1
    
    // ════════════════════════════════════════════════════════════════════════════
    // MEMORY STATE AFTER INITIALIZATION:
    // ════════════════════════════════════════════════════════════════════════════
    // Stack (p):
    // p[0]@0x7ffc... = 0x5e42643b76c0 → Heap: int(1) @ 0x5e42643b76c0 (4B)
    // p[1]@0x7ffc...+8 = 0x5e42643b76e0 → Heap: int(1) @ 0x5e42643b76e0 (4B)
    // ...
    // p[9]@0x7ffc...+72 = 0x5e42643b77e0 → Heap: int(1) @ 0x5e42643b77e0 (4B)
    //
    // Total Stack: 80B
    // Total Heap: 10 × 4B = 40B (data) + overhead
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 4: Verify all values
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== VERIFICATION ===\n";
    for (size_t i = 0; i < p.size(); ++i) {
        std::cout << "p[" << i << "] = " << p[i].get() 
                  << ", *p[" << i << "] = " << *p[i] << "\n";
    }
    // OUTPUT: All values = 1 ✓
    
    // ════════════════════════════════════════════════════════════════════════════
    // CALCULATIONS:
    // ════════════════════════════════════════════════════════════════════════════
    // N=10:
    //   for_each iterations: 10
    //   make_unique calls: 10
    //   heap allocations: 10 × 4B = 40B
    //   Time: 10 × (alloc + assign) = O(N)
    //
    // N=1000:
    //   for_each iterations: 1000
    //   heap allocations: 1000 × 4B = 4000B
    //   Time: O(1000)
    //
    // N=0 (edge):
    //   for_each iterations: 0 (empty range)
    //   heap allocations: 0B
    //   Time: O(1) (no-op)
    
    return 0;
}
