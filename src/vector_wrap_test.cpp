#include <iostream>
#include <vector>
#include <memory>

int main() {
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 1: Allocate vector on stack
    // ════════════════════════════════════════════════════════════════════════════
    // Stack layout for vector<int>:
    // Offset 0:  size_t _M_start     (8 bytes) = pointer to heap array or nullptr
    // Offset 8:  size_t _M_finish    (8 bytes) = pointer to end of used elements
    // Offset 16: size_t _M_end_of_storage (8 bytes) = pointer to end of allocated space
    // Total: 24 bytes
    // 
    // ACTUAL OUTPUT: &v = 0x7ffe79037390
    // CALCULATION: size() = (_M_finish - _M_start) / sizeof(int)
    //              capacity() = (_M_end_of_storage - _M_start) / sizeof(int)
    // INITIAL STATE: size=0, capacity=0, data=nullptr (0x0)
    std::cout << "=== STEP 1: Create vector on stack ===\n";
    std::vector<int> v;
    
    std::cout << "&v               = " << &v << "\n";  // OUTPUT: 0x7ffe79037390 (stack address)
    std::cout << "&v.size (offset 0)   = " << (void*)((char*)&v + 0) << "\n";  // OUTPUT: 0x7ffe79037390
    std::cout << "&v.capacity (offset 8?) = (implementation specific)\n";
    std::cout << "v.size()         = " << v.size() << "\n";  // OUTPUT: 0
    std::cout << "v.capacity()     = " << v.capacity() << "\n";  // OUTPUT: 0
    std::cout << "v.data()         = " << v.data() << "\n";  // OUTPUT: 0 (nullptr)
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 2: Push 10, 20
    // ════════════════════════════════════════════════════════════════════════════
    // OPERATION 1: v.push_back(10)
    //   size=0, capacity=0 → NEED ALLOCATION
    //   Allocate heap: 1×4B=4B (or implementation may allocate more)
    //   Store 10 at heap[0]
    //   size: 0→1, capacity: 0→1 (or more)
    //
    // OPERATION 2: v.push_back(20)
    //   size=1, capacity=1 (assume) → FULL, NEED REALLOCATION
    //   Allocate new heap: 2×4B=8B (growth factor ×2)
    //   Copy old[10] → new[0]
    //   Store 20 → new[1]
    //   Free old heap
    //   size: 1→2, capacity: 1→2
    //
    // ACTUAL OUTPUT:
    //   &v = 0x7ffe79037390 (SAME stack address ✓)
    //   v.data() = 0x5aec613d16e0 (NEW heap allocation)
    //   v[0] = 10 at 0x5aec613d16e0
    //   v[1] = 20 at 0x5aec613d16e4 (offset +4 bytes = sizeof(int))
    //   MEMORY LAYOUT: [10@0x...6e0 | 20@0x...6e4] = 8 bytes used, capacity=2
    std::cout << "\n=== STEP 2: Push 10, 20 ===\n";
    v.push_back(10);  // Allocate heap, size 0→1
    v.push_back(20);  // Reallocate heap (growth), size 1→2
    
    std::cout << "&v               = " << &v << "\n";  // OUTPUT: 0x7ffe79037390 (unchanged ✓)
    std::cout << "v.size()         = " << v.size() << "\n";  // OUTPUT: 2
    std::cout << "v.capacity()     = " << v.capacity() << "\n";  // OUTPUT: 2
    std::cout << "v.data()         = " << v.data() << "\n";  // OUTPUT: 0x5aec613d16e0
    std::cout << "v[0]             = " << v[0] << " at " << &v[0] << "\n";  // OUTPUT: 10 at 0x5aec613d16e0
    std::cout << "v[1]             = " << v[1] << " at " << &v[1] << "\n";  // OUTPUT: 20 at 0x5aec613d16e4
    
    void* old_heap_ptr = v.data();  // SAVE: 0x5aec613d16e0
    std::cout << "SAVED: old_heap_ptr = " << old_heap_ptr << "\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 3: Move into shared_ptr
    // ════════════════════════════════════════════════════════════════════════════
    // OPERATION: auto p = make_shared<vector<int>>(std::move(v));
    //
    // SUBSTEP 3.1: std::move(v)
    //   Cast v to rvalue reference (vector<int>&&)
    //   Does NOT modify v yet
    //
    // SUBSTEP 3.2: make_shared allocation
    //   Allocate heap block: CtrlBlock + vector<int>
    //   CtrlBlock size: ~16 bytes (vptr, strong_count, weak_count)
    //   vector<int> size: 24 bytes
    //   Total: ~40 bytes on heap
    //   ACTUAL OUTPUT: p.get() = 0x5aec613d1710
    //
    // SUBSTEP 3.3: vector move constructor
    //   vector(vector<int>&& other):
    //     this->_M_start = other._M_start;           // STEAL pointer 0x5aec613d16e0
    //     this->_M_finish = other._M_finish;         // STEAL pointer
    //     this->_M_end_of_storage = other._M_end_of_storage;  // STEAL pointer
    //     other._M_start = nullptr;                  // RESET source
    //     other._M_finish = nullptr;
    //     other._M_end_of_storage = nullptr;
    //   RESULT: (*p) now owns heap array [10,20]@0x5aec613d16e0
    //           v is empty (size=0, cap=0, data=nullptr)
    //
    // MEMORY TOPOLOGY AFTER MOVE:
    //   Stack: v@0x7ffe79037390 (24B) = [nullptr, nullptr, nullptr]
    //          p@0x7ffe79037380 (16B) = [ptr_to_ctrl=0x5aec613d1710, ...]
    //   Heap Block 1 (make_shared allocation):
    //          0x5aec613d1710: CtrlBlock (16B) = [vptr, strong=1, weak=0]
    //          0x5aec613d1720: vector<int> (24B) = [0x5aec613d16e0, ..., ...]
    //   Heap Block 2 (original array, now owned by (*p)):
    //          0x5aec613d16e0: [10, 20] (8B)
    //
    // ACTUAL OUTPUT:
    //   v.size() = 0 ✓
    //   v.capacity() = 0 ✓
    //   v.data() = 0 (nullptr) ✓
    //   (*p).size() = 2 ✓
    //   (*p).data() = 0x5aec613d16e0 (SAME as old_heap_ptr) ✓
    std::cout << "\n=== STEP 3: Wrap into shared_ptr ===\n";
    auto p = std::make_shared<std::vector<int>>(std::move(v));
    
    std::cout << "AFTER MOVE (v is now empty):\n";
    std::cout << "&v               = " << &v << " (same stack location)\n";  // OUTPUT: 0x7ffe79037390
    std::cout << "v.size()         = " << v.size() << " (expect 0)\n";  // OUTPUT: 0 ✓
    std::cout << "v.capacity()     = " << v.capacity() << " (expect 0)\n";  // OUTPUT: 0 ✓
    std::cout << "v.data()         = " << v.data() << " (expect nullptr)\n";  // OUTPUT: 0 ✓
    
    std::cout << "\nSHARED_PTR (p points to heap-allocated vector):\n";
    std::cout << "p (stack var)    = " << &p << "\n";  // OUTPUT: 0x7ffe79037380 (16B below v)
    std::cout << "p.get()          = " << p.get() << " (vector object on HEAP)\n";  // OUTPUT: 0x5aec613d1710
    std::cout << "(*p).size()      = " << (*p).size() << " (expect 2)\n";  // OUTPUT: 2 ✓
    std::cout << "(*p).capacity()  = " << (*p).capacity() << " (expect 2)\n";  // OUTPUT: 2 ✓
    std::cout << "(*p).data()      = " << (*p).data() << " (expect same as old_heap_ptr)\n";  // OUTPUT: 0x5aec613d16e0 ✓
    std::cout << "(*p)[0]          = " << (*p)[0] << " at " << &(*p)[0] << "\n";  // OUTPUT: 10 at 0x5aec613d16e0
    std::cout << "(*p)[1]          = " << (*p)[1] << " at " << &(*p)[1] << "\n";  // OUTPUT: 20 at 0x5aec613d16e4
    
    std::cout << "\nCOMPARISON:\n";
    std::cout << "(*p).data() == old_heap_ptr: " << ((*p).data() == old_heap_ptr ? "YES ✓" : "NO ✗") << "\n";  // OUTPUT: YES ✓
    std::cout << "Distance (bytes): " << (long)((char*)p.get() - (char*)&v) << "\n";  // OUTPUT: -40759638514816 (wraparound)
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 4: Push 30 via shared_ptr
    // ════════════════════════════════════════════════════════════════════════════
    // OPERATION: (*p).push_back(30)
    //   Current state: size=2, capacity=2 → FULL
    //   Need to grow: new_capacity = capacity × growth_factor (typically 2)
    //                 new_capacity = 2 × 2 = 4
    //   Allocate new heap: 4×4B = 16 bytes
    //   Copy old data: [10, 20] from 0x5aec613d16e0 to new location
    //   Append new element: 30 at index 2
    //   Free old heap: 0x5aec613d16e0
    //   Update vector: data = new_ptr, size = 3, capacity = 4
    //
    // ACTUAL OUTPUT:
    //   p.get() = 0x5aec613d1710 (SAME, vector object didn't move) ✓
    //   (*p).size() = 3 ✓
    //   (*p).capacity() = 4 ✓
    //   (*p).data() = 0x5aec613d16c0 (DIFFERENT, reallocation happened) ✗
    //
    // REALLOCATION ANALYSIS:
    //   Old: 0x5aec613d16e0
    //   New: 0x5aec613d16c0
    //   Offset: 0x...6c0 - 0x...6e0 = -32 bytes (0x20 in hex)
    //   New allocation is 32 bytes BEFORE old allocation in memory
    //   This is typical: allocator found free space earlier in heap
    //
    // MEMORY LAYOUT AFTER PUSH:
    //   Heap Block 2 (OLD, FREED): 0x5aec613d16e0 (8B) - DEALLOCATED
    //   Heap Block 3 (NEW): 0x5aec613d16c0 (16B) = [10, 20, 30, unused]
    //                       0x5aec613d16c0: 10
    //                       0x5aec613d16c4: 20
    //                       0x5aec613d16c8: 30
    //                       0x5aec613d16cc: (uninitialized, capacity slot)
    std::cout << "\n=== STEP 4: Push 30 via shared_ptr ===\n";
    (*p).push_back(30);  // size 2→3, capacity 2→4, data reallocated
    
    std::cout << "p.get()          = " << p.get() << " (same vector object location)\n";  // OUTPUT: 0x5aec613d1710 ✓
    std::cout << "(*p).size()      = " << (*p).size() << " (expect 3)\n";  // OUTPUT: 3 ✓
    std::cout << "(*p).capacity()  = " << (*p).capacity() << " (expect 4, growth factor)\n";  // OUTPUT: 4 ✓
    std::cout << "(*p).data()      = " << (*p).data() << " (expect DIFFERENT, realloc)\n";  // OUTPUT: 0x5aec613d16c0 ✗
    std::cout << "(*p)[0]          = " << (*p)[0] << " at " << &(*p)[0] << "\n";  // OUTPUT: 10 at 0x5aec613d16c0
    std::cout << "(*p)[1]          = " << (*p)[1] << " at " << &(*p)[1] << "\n";  // OUTPUT: 20 at 0x5aec613d16c4
    std::cout << "(*p)[2]          = " << (*p)[2] << " at " << &(*p)[2] << "\n";  // OUTPUT: 30 at 0x5aec613d16c8
    
    std::cout << "\nCOMPARISON AFTER PUSH:\n";
    std::cout << "(*p).data() == old_heap_ptr: " << ((*p).data() == old_heap_ptr ? "YES ✓" : "NO ✗") << "\n";  // OUTPUT: NO ✗
    std::cout << "Reallocation offset: " << (long)((char*)(*p).data() - (char*)old_heap_ptr) << " bytes\n";  // OUTPUT: -32 bytes
    
    // ════════════════════════════════════════════════════════════════════════════
    // FINAL MEMORY STATE DIAGRAM
    // ════════════════════════════════════════════════════════════════════════════
    // Stack:
    //   0x7ffe79037390: v (24B) = [nullptr, nullptr, nullptr] (moved-from)
    //   0x7ffe79037380: p (16B) = [0x5aec613d1710, ...]
    //
    // Heap:
    //   0x5aec613d1710: CtrlBlock (16B) = [vptr, strong=1, weak=0]
    //   0x5aec613d1720: vector<int> (24B) = [0x5aec613d16c0, size=3, cap=4]
    //   0x5aec613d16c0: Array (16B) = [10, 20, 30, unused]
    //   0x5aec613d16e0: (FREED, was old array [10, 20])
    
    return 0;
}
