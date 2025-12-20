#include <iostream>
#include <array>
#include <memory>
#include <algorithm>

int main() {
    // ════════════════════════════════════════════════════════════════════════════
    // AXIOM 1: std::array template signature
    // ════════════════════════════════════════════════════════════════════════════
    // template<typename T, size_t N> struct array;
    //          ^^^^^^^^    ^^^^^^^
    //          TYPE first  SIZE second
    
    // ════════════════════════════════════════════════════════════════════════════
    // ERROR CASE (what you wrote):
    // ════════════════════════════════════════════════════════════════════════════
    // std::array<10, std::unique_ptr<int>> p;
    //            ^^  ^^^^^^^^^^^^^^^^^^^^
    //            10 is size_t, not a type → COMPILE ERROR
    //            std::unique_ptr<int> is in position 2 (should be position 1)
    //
    // Compiler expects: array<TYPE, SIZE>
    // You gave:         array<SIZE, TYPE>
    // Result: error: template argument 1 is invalid
    
    // ════════════════════════════════════════════════════════════════════════════
    // CORRECT SYNTAX:
    // ════════════════════════════════════════════════════════════════════════════
    std::array<std::unique_ptr<int>, 10> p;
    //         ^^^^^^^^^^^^^^^^^^^^  ^^
    //         TYPE (unique_ptr<int>) SIZE (10)
    
    // MEMORY LAYOUT:
    // p@Stack: 80 bytes (10 × 8 bytes per pointer)
    // Each element: unique_ptr = 8 bytes (raw pointer size)
    // Total stack: 80 bytes
    std::cout << "sizeof(p) = " << sizeof(p) << " bytes\n";  // OUTPUT: 80
    std::cout << "p.size()  = " << p.size() << "\n";  // OUTPUT: 10
    
    // ════════════════════════════════════════════════════════════════════════════
    // INITIAL STATE: All pointers are nullptr
    // ════════════════════════════════════════════════════════════════════════════
    // p[0] = nullptr (0x0)
    // p[1] = nullptr (0x0)
    // ...
    // p[9] = nullptr (0x0)
    std::cout << "\n=== INITIAL STATE ===\n";
    std::cout << "p[0].get() = " << p[0].get() << " (expect nullptr)\n";  // OUTPUT: 0
    std::cout << "p[9].get() = " << p[9].get() << " (expect nullptr)\n";  // OUTPUT: 0
    
    // ════════════════════════════════════════════════════════════════════════════
    // INITIALIZATION: Assign each element
    // ════════════════════════════════════════════════════════════════════════════
    // OPERATION: p[i] = make_unique<int>(i)
    // i=0: allocate heap 4B @ 0x..., store 0, p[0] = 0x...
    // i=1: allocate heap 4B @ 0x..., store 1, p[1] = 0x...
    // ...
    // i=9: allocate heap 4B @ 0x..., store 9, p[9] = 0x...
    // Total heap: 10 × 4B = 40 bytes
    std::cout << "\n=== FILLING ARRAY ===\n";
    for (size_t i = 0; i < p.size(); ++i) {
        p[i] = std::make_unique<int>(static_cast<int>(i));
        std::cout << "p[" << i << "].get() = " << p[i].get() 
                  << ", *p[" << i << "] = " << *p[i] << "\n";
    }
    // OUTPUT (example):
    // p[0].get() = 0x5e971e6166e0, *p[0] = 0
    // p[1].get() = 0x5e971e616700, *p[1] = 1
    // ...
    // p[9].get() = 0x5e971e616780, *p[9] = 9
    
    // ════════════════════════════════════════════════════════════════════════════
    // MEMORY STATE DIAGRAM:
    // ════════════════════════════════════════════════════════════════════════════
    // Stack:
    // p@0x7ffc... (80B):
    //   [0]: 0x5e971e6166e0 (8B) → Heap: int(0) @ 0x5e971e6166e0 (4B)
    //   [1]: 0x5e971e616700 (8B) → Heap: int(1) @ 0x5e971e616700 (4B)
    //   [2]: 0x5e971e616720 (8B) → Heap: int(2) @ 0x5e971e616720 (4B)
    //   ...
    //   [9]: 0x5e971e616780 (8B) → Heap: int(9) @ 0x5e971e616780 (4B)
    //
    // Total memory:
    //   Stack: 80B (array of 10 pointers)
    //   Heap: 40B (10 × 4B ints)
    //   Total: 120B
    
    // ════════════════════════════════════════════════════════════════════════════
    // CALCULATIONS AT DIFFERENT SCALES:
    // ════════════════════════════════════════════════════════════════════════════
    // N=10 unique_ptr<int>:
    //   Stack: 10 × 8B = 80B
    //   Heap: 10 × 4B = 40B
    //   Total: 120B
    //
    // N=100 unique_ptr<int>:
    //   Stack: 100 × 8B = 800B
    //   Heap: 100 × 4B = 400B
    //   Total: 1200B
    //
    // N=1000 unique_ptr<int>:
    //   Stack: 1000 × 8B = 8000B
    //   Heap: 1000 × 4B = 4000B
    //   Total: 12000B
    //
    // Edge N=0:
    //   Stack: 0 × 8B = 0B (but std::array<T,0> still exists as empty struct)
    //   Heap: 0B
    //   Total: sizeof(array<unique_ptr<int>,0>) = 1B (implementation dependent)
    
    // ════════════════════════════════════════════════════════════════════════════
    // FINAL OUTPUT: Print all values
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== FINAL VALUES ===\n";
    for (size_t i = 0; i < p.size(); ++i) {
        std::cout << "*p[" << i << "] = " << *p[i] << "\n";
    }
    // OUTPUT:
    // *p[0] = 0
    // *p[1] = 1
    // ...
    // *p[9] = 9
    
    // ════════════════════════════════════════════════════════════════════════════
    // CLEANUP: Automatic when p goes out of scope
    // ════════════════════════════════════════════════════════════════════════════
    // p[0].~unique_ptr() → delete ptr @ 0x5e971e6166e0 (free 4B)
    // p[1].~unique_ptr() → delete ptr @ 0x5e971e616700 (free 4B)
    // ...
    // p[9].~unique_ptr() → delete ptr @ 0x5e971e616780 (free 4B)
    // Total freed: 40B
    // Stack popped: 80B
    std::ranges::for_each(p, [](auto& ptr) {
        ptr = std::make_unique<int>(1);
    });
    
    return 0;
}
