#include <iostream>
#include <vector>
#include <memory>

int main() {
    // ════════════════════════════════════════════════════════════════════════════
    // TEST 1: MOVE - Transfer ownership, no copy
    // ════════════════════════════════════════════════════════════════════════════
    // HEAP ALLOCATIONS: 2 total
    //   1) v1 initial array [10,20] = 8 bytes at 0x60dbbac916e0
    //   2) make_shared: CtrlBlock(16B) + vector(24B) = 40 bytes at 0x60dbbac91710
    // Array TRANSFERRED (no copy, pointer stolen)
    std::cout << "=== TEST 1: MOVE (what we did before) ===\n";
    std::vector<int> v1;  // Stack: 24 bytes at 0x7ffc49e42860
    v1.push_back(10);  // Heap alloc: [10] at 0x60dbbac916e0, size 1→1, capacity 0→1
    v1.push_back(20);  // Realloc: [10,20] at 0x60dbbac916e0, size 1→2, capacity 1→2
    
    std::cout << "BEFORE move:\n";
    std::cout << "&v1          = " << &v1 << "\n";  // OUTPUT: 0x7ffc49e42860
    std::cout << "v1.data()    = " << v1.data() << "\n";  // OUTPUT: 0x60dbbac916e0 (heap array)
    std::cout << "v1.size()    = " << v1.size() << "\n";  // OUTPUT: 2
    void* v1_old_data = v1.data();  // SAVE: 0x60dbbac916e0
    
    // OPERATION: make_shared<vector<int>>(std::move(v1))
    // STEP 1: Allocate CtrlBlock(16B) + vector(24B) = 40B at 0x60dbbac91710 (approximate)
    // STEP 2: Call vector move constructor:
    //         new_vec._M_start = v1._M_start = 0x60dbbac916e0  (STEAL pointer)
    //         new_vec._M_finish = v1._M_finish
    //         new_vec._M_end_of_storage = v1._M_end_of_storage
    //         v1._M_start = nullptr  (RESET source)
    //         v1._M_finish = nullptr
    //         v1._M_end_of_storage = nullptr
    // RESULT: Array [10,20]@0x60dbbac916e0 now owned by (*p1)
    //         v1 is empty (size=0, capacity=0, data=nullptr)
    auto p1 = std::make_shared<std::vector<int>>(std::move(v1));
    
    std::cout << "\nAFTER move:\n";
    std::cout << "v1.data()    = " << v1.data() << " (should be nullptr)\n";  // OUTPUT: 0 ✓
    std::cout << "v1.size()    = " << v1.size() << " (should be 0)\n";  // OUTPUT: 0 ✓
    std::cout << "(*p1).data() = " << (*p1).data() << "\n";  // OUTPUT: 0x60dbbac916e0 (SAME as v1_old_data ✓)
    std::cout << "(*p1).size() = " << (*p1).size() << "\n";  // OUTPUT: 2 ✓
    std::cout << "SAME HEAP? " << ((*p1).data() == v1_old_data ? "YES ✓" : "NO ✗") << "\n";  // OUTPUT: YES ✓
    
    // MEMORY STATE AFTER MOVE:
    // Stack:
    //   v1@0x7ffc49e42860 (24B): [nullptr, nullptr, nullptr] (moved-from, empty)
    //   p1@0x7ffc49e42850 (16B): points to 0x60dbbac91710
    // Heap:
    //   0x60dbbac91710 (40B): [CtrlBlock(16B): vptr+strong=1+weak=0 | vector(24B): 0x60dbbac916e0+size=2+cap=2]
    //   0x60dbbac916e0 (8B): [10, 20]
    // Total Heap: 48 bytes (40 + 8)
    
    // ════════════════════════════════════════════════════════════════════════════
    // TEST 2: COPY - Duplicate data, both vectors alive
    // ════════════════════════════════════════════════════════════════════════════
    // HEAP ALLOCATIONS: 3 total
    //   1) v2 initial array [30,40] = 8 bytes at 0x60dbbac91730
    //   2) make_shared: CtrlBlock(16B) + vector(24B) = 40 bytes at 0x60dbbac91750 (approx)
    //   3) COPY of array [30,40] = 8 bytes at 0x60dbbac916c0 (NEW allocation)
    std::cout << "\n=== TEST 2: COPY (your question) ===\n";
    std::vector<int> v2;  // Stack: 24 bytes at 0x7ffc49e42880
    v2.push_back(30);  // Heap alloc: [30] at 0x60dbbac91730, size 0→1, capacity 0→1
    v2.push_back(40);  // Realloc: [30,40] at 0x60dbbac91730, size 1→2, capacity 1→2
    
    std::cout << "BEFORE copy:\n";
    std::cout << "&v2          = " << &v2 << "\n";  // OUTPUT: 0x7ffc49e42880
    std::cout << "v2.data()    = " << v2.data() << "\n";  // OUTPUT: 0x60dbbac91730 (heap array)
    std::cout << "v2.size()    = " << v2.size() << "\n";  // OUTPUT: 2
    void* v2_data = v2.data();  // SAVE: 0x60dbbac91730
    
    // OPERATION: make_shared<vector<int>>(v2)
    // STEP 1: Allocate CtrlBlock(16B) + vector(24B) = 40B at 0x60dbbac91750 (approximate)
    // STEP 2: Call vector COPY constructor:
    //         new_vec.allocate(2)  → NEW heap block 8B at 0x60dbbac916c0
    //         memcpy(0x60dbbac916c0, v2.data(), 8)  → copy [30,40]
    //         new_vec._M_start = 0x60dbbac916c0  (DIFFERENT from v2)
    //         new_vec.size = 2
    //         new_vec.capacity = 2
    // STEP 3: v2 UNCHANGED (still owns 0x60dbbac91730)
    // RESULT: TWO independent arrays exist
    //         v2.data() = 0x60dbbac91730 (original)
    //         (*p2).data() = 0x60dbbac916c0 (copy)
    auto p2 = std::make_shared<std::vector<int>>(v2);  // NO std::move → COPY
    
    std::cout << "\nAFTER copy:\n";
    std::cout << "v2.data()    = " << v2.data() << " (should be SAME)\n";  // OUTPUT: 0x60dbbac91730 ✓
    std::cout << "v2.size()    = " << v2.size() << " (should be 2)\n";  // OUTPUT: 2 ✓
    std::cout << "v2[0]        = " << v2[0] << "\n";  // OUTPUT: 30
    std::cout << "(*p2).data() = " << (*p2).data() << " (should be DIFFERENT)\n";  // OUTPUT: 0x60dbbac916c0 ✗
    std::cout << "(*p2).size() = " << (*p2).size() << "\n";  // OUTPUT: 2
    std::cout << "(*p2)[0]     = " << (*p2)[0] << "\n";  // OUTPUT: 30 (copied value)
    std::cout << "SAME HEAP? " << ((*p2).data() == v2_data ? "YES" : "NO ✗") << "\n";  // OUTPUT: NO ✗
    
    // MEMORY STATE AFTER COPY:
    // Stack:
    //   v2@0x7ffc49e42880 (24B): [0x60dbbac91730, size=2, cap=2] (ALIVE)
    //   p2@0x7ffc49e42870 (16B): points to 0x60dbbac91750
    // Heap:
    //   0x60dbbac91730 (8B): [30, 40] ← owned by v2
    //   0x60dbbac91750 (40B): [CtrlBlock(16B) | vector(24B): 0x60dbbac916c0+size=2+cap=2]
    //   0x60dbbac916c0 (8B): [30, 40] ← COPY, owned by (*p2)
    // Total Heap: 56 bytes (8 + 40 + 8)
    // COST vs MOVE: +8 bytes (duplicate array)
    
    // ════════════════════════════════════════════════════════════════════════════
    // TEST 3: Independence - Modify both, verify separation
    // ════════════════════════════════════════════════════════════════════════════
    // OPERATION 1: v2.push_back(99)
    //   Current: size=2, capacity=2 → FULL
    //   Allocate new: 4×4B=16B at 0x60dbbac91760 (approx)
    //   Copy old [30,40] → new[0,1]
    //   Append 99 → new[2]
    //   Free old 0x60dbbac91730
    //   v2.data() → 0x60dbbac91760 (new location)
    //
    // OPERATION 2: (*p2).push_back(88)
    //   Current: size=2, capacity=2 → FULL
    //   Allocate new: 4×4B=16B at 0x60dbbac91770 (approx)
    //   Copy old [30,40] → new[0,1]
    //   Append 88 → new[2]
    //   Free old 0x60dbbac916c0
    //   (*p2).data() → 0x60dbbac91770 (different from v2)
    //
    // RESULT: Two INDEPENDENT reallocations
    //   v2 = [30, 40, 99]
    //   (*p2) = [30, 40, 88]
    std::cout << "\n=== TEST 3: Modify both independently ===\n";
    v2.push_back(99);  // v2: size 2→3, capacity 2→4, realloc to new heap
    (*p2).push_back(88);  // (*p2): size 2→3, capacity 2→4, realloc to DIFFERENT heap
    
    std::cout << "v2:   [" << v2[0] << ", " << v2[1] << ", " << v2[2] << "]\n";  // OUTPUT: [30, 40, 99]
    std::cout << "(*p2): [" << (*p2)[0] << ", " << (*p2)[1] << ", " << (*p2)[2] << "]\n";  // OUTPUT: [30, 40, 88]
    std::cout << "INDEPENDENT ✓\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // FINAL ANSWER TO YOUR QUESTION
    // ════════════════════════════════════════════════════════════════════════════
    // Q: "copying copies stuff from one heap to another heap, first heap is of the
    //     vector data block and second heap of second vector data block, and THEN,
    //     AND THEN THE MAKE SHARED PUTS this address AGAIN ON THE HEAP"
    //
    // A: YES, EXACTLY ✓
    //
    // HEAP ALLOCATION SEQUENCE FOR COPY:
    // 1) v2.push_back(30,40) → Heap1: [30,40]@0x60dbbac91730 (8B)
    // 2) make_shared allocates → Heap2: CtrlBlock+vector@0x60dbbac91750 (40B)
    // 3) vector copy constructor → Heap3: [30,40]@0x60dbbac916c0 (8B, DUPLICATE)
    //
    // Total: 3 heap blocks (8 + 40 + 8 = 56 bytes)
    //
    // MEMORY LAYOUT:
    // v2 (stack) → Heap1: [30,40]@0x60dbbac91730
    // p2 (stack) → Heap2: [Ctrl+vec]@0x60dbbac91750 → Heap3: [30,40]@0x60dbbac916c0
    //
    // CONTRAST WITH MOVE (only 2 heap blocks):
    // v1 (stack, empty)
    // p1 (stack) → Heap1: [Ctrl+vec]@0x60dbbac91710 → Heap2: [10,20]@0x60dbbac916e0 (TRANSFERRED)
    //
    // CALCULATIONS:
    // Small scale (N=2 ints):
    //   MOVE: 2 heap blocks (40+8=48B)
    //   COPY: 3 heap blocks (8+40+8=56B)
    //   Overhead: +8B (+16.7%)
    //
    // Large scale (N=1000000 ints = 4MB):
    //   MOVE: 2 blocks (40B + 4MB = 4000040B)
    //   COPY: 3 blocks (4MB + 40B + 4MB = 8000040B)
    //   Overhead: +4MB (+100%)
    //   Time: memcpy(4MB) ≈ 1ms on 4GB/s memory bandwidth
    //
    // Edge (N=0 ints):
    //   MOVE: 2 blocks (40B + 0B = 40B)
    //   COPY: 3 blocks (0B + 40B + 0B = 40B)
    //   Overhead: +0B (both have nullptr data)
    //
    // Mid scale (N=100 ints = 400B):
    //   MOVE: 2 blocks (40B + 400B = 440B)
    //   COPY: 3 blocks (400B + 40B + 400B = 840B)
    //   Overhead: +400B (+90.9%)
    
    return 0;
}
