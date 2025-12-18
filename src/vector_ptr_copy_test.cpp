#include <iostream>
#include <vector>
#include <array>
#include <memory>

int main() {
    // ════════════════════════════════════════════════════════════════════════════
    // PROBLEM STATEMENT:
    // ════════════════════════════════════════════════════════════════════════════
    // 1. Create vector p of RAW POINTERS to 2-element arrays
    // 2. p[i] points to array {i, i+1}
    // 3. Create vector q of UNIQUE POINTERS to COPIES of those arrays
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 1: Declare p (vector of raw pointers)
    // ════════════════════════════════════════════════════════════════════════════
    // TYPE: std::vector<std::array<int, 2>*>
    //                   ^^^^^^^^^^^^^^^^^^^
    //                   Pointer to 2-element array
    std::vector<std::array<int, 2>*> p;
    
    std::cout << "=== STEP 1: Create vector of raw pointers ===\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 2: Allocate arrays and populate p
    // ════════════════════════════════════════════════════════════════════════════
    // OPERATION: For i=0 to 4:
    //   Allocate array<int, 2> on heap
    //   Initialize: {i, i+1}
    //   Store pointer in p
    //
    // i=0: new array{0, 1} @ 0x... → p[0] = 0x...
    // i=1: new array{1, 2} @ 0x... → p[1] = 0x...
    // i=2: new array{2, 3} @ 0x... → p[2] = 0x...
    // i=3: new array{3, 4} @ 0x... → p[3] = 0x...
    // i=4: new array{4, 5} @ 0x... → p[4] = 0x...
    
    for (int i = 0; i < 5; ++i) {
        // Allocate new array on heap
        auto* arr = new std::array<int, 2>{i, i + 1};
        p.push_back(arr);
        
        std::cout << "p[" << i << "] = " << p[i] 
                  << " → {" << (*p[i])[0] << ", " << (*p[i])[1] << "}\n";
    }
    // OUTPUT (example):
    // p[0] = 0x5e42643b76c0 → {0, 1}
    // p[1] = 0x5e42643b76e0 → {1, 2}
    // p[2] = 0x5e42643b7700 → {2, 3}
    // p[3] = 0x5e42643b7720 → {3, 4}
    // p[4] = 0x5e42643b7740 → {4, 5}
    
    // ════════════════════════════════════════════════════════════════════════════
    // MEMORY STATE AFTER STEP 2:
    // ════════════════════════════════════════════════════════════════════════════
    // Stack:
    //   p (vector): size=5, capacity=8?, data=0x...
    //
    // Heap Block 1 (vector's array):
    //   0x...: [0x5e42643b76c0, 0x5e42643b76e0, 0x5e42643b7700, 0x5e42643b7720, 0x5e42643b7740]
    //          (5 × 8B pointers = 40B)
    //
    // Heap Block 2-6 (arrays):
    //   0x5e42643b76c0: [0, 1] (8B)
    //   0x5e42643b76e0: [1, 2] (8B)
    //   0x5e42643b7700: [2, 3] (8B)
    //   0x5e42643b7720: [3, 4] (8B)
    //   0x5e42643b7740: [4, 5] (8B)
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 3: Create q (vector of unique_ptr to COPIES)
    // ════════════════════════════════════════════════════════════════════════════
    // TYPE: std::vector<std::unique_ptr<std::array<int, 2>>>
    //                   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //                   unique_ptr to 2-element array
    std::vector<std::unique_ptr<std::array<int, 2>>> q;
    
    std::cout << "\n=== STEP 3: Create vector of unique_ptr to COPIES ===\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 4: Copy arrays from p to q
    // ════════════════════════════════════════════════════════════════════════════
    // OPERATION: For each pointer in p:
    //   1. Dereference to get array: *p[i]
    //   2. Create COPY on heap: make_unique<array<int,2>>(*p[i])
    //   3. Store unique_ptr in q
    //
    // i=0: *p[0] = {0, 1} → make_unique → new heap @ 0x... → q[0]
    // i=1: *p[1] = {1, 2} → make_unique → new heap @ 0x... → q[1]
    // ...
    //
    // RESULT: q[i] points to DIFFERENT memory than p[i]
    //         BUT contains SAME VALUES
    
    for (size_t i = 0; i < p.size(); ++i) {
        // Create unique_ptr to COPY of array
        q.push_back(std::make_unique<std::array<int, 2>>(*p[i]));
        //                                                ^^^^^^
        //                                                Dereference p[i] to copy array
        
        std::cout << "q[" << i << "] = " << q[i].get() 
                  << " → {" << (*q[i])[0] << ", " << (*q[i])[1] << "}"
                  << " (copied from p[" << i << "] = " << p[i] << ")\n";
    }
    // OUTPUT (example):
    // q[0] = 0x5e42643b7760 → {0, 1} (copied from p[0] = 0x5e42643b76c0)
    // q[1] = 0x5e42643b7780 → {1, 2} (copied from p[1] = 0x5e42643b76e0)
    // q[2] = 0x5e42643b77a0 → {2, 3} (copied from p[2] = 0x5e42643b7700)
    // q[3] = 0x5e42643b77c0 → {3, 4} (copied from p[3] = 0x5e42643b7720)
    // q[4] = 0x5e42643b77e0 → {4, 5} (copied from p[4] = 0x5e42643b7740)
    
    // ════════════════════════════════════════════════════════════════════════════
    // VERIFICATION: Addresses are DIFFERENT (independent copies)
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== VERIFICATION: Independent copies ===\n";
    for (size_t i = 0; i < p.size(); ++i) {
        std::cout << "p[" << i << "] = " << p[i] 
                  << ", q[" << i << "] = " << q[i].get() 
                  << " → Same? " << (p[i] == q[i].get() ? "YES" : "NO ✓") << "\n";
    }
    // OUTPUT: All "NO ✓" (different addresses)
    
    // ════════════════════════════════════════════════════════════════════════════
    // MODIFY q to prove independence
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== MODIFY q[0] ===\n";
    (*q[0])[0] = 999;  // Change first element of q[0]
    
    std::cout << "p[0]: {" << (*p[0])[0] << ", " << (*p[0])[1] << "}\n";  // 0, 1 (unchanged)
    std::cout << "q[0]: {" << (*q[0])[0] << ", " << (*q[0])[1] << "}\n";  // 999, 1 (modified)
    
    // ════════════════════════════════════════════════════════════════════════════
    // CLEANUP: Delete raw pointers in p (unique_ptr auto-deletes)
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== CLEANUP ===\n";
    for (auto* ptr : p) {
        delete ptr;  // Free heap array
    }
    std::cout << "Deleted " << p.size() << " arrays from p\n";
    // q auto-deletes when out of scope (unique_ptr destructor)
    
    // ════════════════════════════════════════════════════════════════════════════
    // FINAL MEMORY STATE:
    // ════════════════════════════════════════════════════════════════════════════
    // p's arrays: DELETED (manual delete)
    // q's arrays: WILL BE DELETED when q goes out of scope (unique_ptr auto)
    
    return 0;
}
