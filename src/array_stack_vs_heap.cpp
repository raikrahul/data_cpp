#include <iostream>
#include <array>

int main() {
    // ════════════════════════════════════════════════════════════════════════════
    // MISCONCEPTION: "std::array is only on compile time stack"
    // ════════════════════════════════════════════════════════════════════════════
    // WRONG ✗
    // TRUTH: std::array SIZE is compile-time, LOCATION is YOUR CHOICE
    
    std::cout << "=== CASE 1: std::array on STACK ===\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // CASE 1: Stack allocation (what you THINK is the ONLY way)
    // ════════════════════════════════════════════════════════════════════════════
    std::array<int, 2> stack_arr = {10, 20};
    
    std::cout << "&stack_arr = " << &stack_arr << " (stack address)\n";
    std::cout << "stack_arr[0] = " << stack_arr[0] << "\n";
    std::cout << "stack_arr[1] = " << stack_arr[1] << "\n";
    // OUTPUT:
    // &stack_arr = 0x7ffc12345678 (high address = stack)
    // stack_arr[0] = 10
    // stack_arr[1] = 20
    
    // DIAGRAM 1: Stack allocation
    // ┌─────────────────────────────────────┐
    // │ Stack Frame (main)                  │
    // │ 0x7ffc12345678: [10, 20]            │ ← stack_arr lives HERE
    // │                 (8 bytes)           │
    // └─────────────────────────────────────┘
    // WHY: Default declaration puts object on stack
    // WHY: No new/malloc → stack automatic storage
    
    std::cout << "\n=== CASE 2: std::array on HEAP (via new) ===\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // CASE 2: Heap allocation (what you DIDN'T KNOW was possible)
    // ════════════════════════════════════════════════════════════════════════════
    std::array<int, 2>* heap_arr = new std::array<int, 2>{30, 40};
    
    std::cout << "heap_arr (ptr) = " << heap_arr << " (heap address)\n";
    std::cout << "&heap_arr (ptr location) = " << &heap_arr << " (stack address)\n";
    std::cout << "(*heap_arr)[0] = " << (*heap_arr)[0] << "\n";
    std::cout << "(*heap_arr)[1] = " << (*heap_arr)[1] << "\n";
    // OUTPUT:
    // heap_arr (ptr) = 0x5e42643b76c0 (low address = heap)
    // &heap_arr (ptr location) = 0x7ffc12345680 (high address = stack)
    // (*heap_arr)[0] = 30
    // (*heap_arr)[1] = 40
    
    // DIAGRAM 2: Heap allocation
    // ┌─────────────────────────────────────┐
    // │ Stack Frame (main)                  │
    // │ 0x7ffc12345680: [0x5e42643b76c0]    │ ← heap_arr POINTER lives on stack (8B)
    // └───────────────────┬─────────────────┘
    //                     │
    //                     │ points to
    //                     ↓
    // ┌─────────────────────────────────────┐
    // │ Heap                                │
    // │ 0x5e42643b76c0: [30, 40]            │ ← std::array<int,2> lives on HEAP (8B)
    // │                 (8 bytes)           │
    // └─────────────────────────────────────┘
    // WHY: new operator allocates on heap
    // WHY: Pointer stored on stack, object stored on heap
    // WHY: SIZE still known at compile time (2 elements)
    
    std::cout << "\n=== CASE 3: Comparing addresses ===\n";
    std::cout << "Stack object: " << &stack_arr << "\n";
    std::cout << "Heap object:  " << heap_arr << "\n";
    std::cout << "Stack high? " << (&stack_arr > heap_arr ? "YES ✓" : "NO") << "\n";
    // OUTPUT: Stack high? YES ✓ (stack addresses > heap addresses on typical Linux)
    
    // ════════════════════════════════════════════════════════════════════════════
    // CRITICAL DIFFERENCE:
    // ════════════════════════════════════════════════════════════════════════════
    // STACK:
    //   Declaration: std::array<int, 2> arr;
    //   Location: Stack frame
    //   Lifetime: Automatic (dies at end of scope)
    //   Cleanup: Automatic
    //
    // HEAP:
    //   Declaration: std::array<int, 2>* arr = new std::array<int, 2>{...};
    //   Pointer Location: Stack frame (8 bytes)
    //   Object Location: Heap
    //   Lifetime: Manual (until delete)
    //   Cleanup: MUST call delete

    
    // ════════════════════════════════════════════════════════════════════════════
    // CASE 4: Your ACTUAL code from previous example
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== CASE 4: What YOU wrote (heap allocation) ===\n";
    
    auto* arr = new std::array<int, 2>{50, 60};
    //        ^^^
    //        new → HEAP ALLOCATION ✓
    //        NOT stack ✗
    
    std::cout << "arr (ptr) = " << arr << " (heap)\n";
    std::cout << "(*arr)[0] = " << (*arr)[0] << "\n";
    std::cout << "(*arr)[1] = " << (*arr)[1] << "\n";
    
    // DIAGRAM 3: Your actual code
    // ┌─────────────────────────────────────┐
    // │ Stack                               │
    // │ 0x7ffc...: [0x5e42643b7700]         │ ← arr pointer (8B)
    // └───────────────────┬─────────────────┘
    //                     │
    //                     ↓
    // ┌─────────────────────────────────────┐
    // │ Heap                                │
    // │ 0x5e42643b7700: [50, 60]            │ ← YOUR ARRAY (8B)
    // └─────────────────────────────────────┘
    // WHY YOU WERE CONFUSED:
    //   You saw "std::array" and assumed "stack only"
    //   You SKIPPED the "new" keyword
    //   You didn't READ the pointer type
    //   SLOPPY ✗
    
    // ════════════════════════════════════════════════════════════════════════════
    // NUMERICAL PROOF:
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== ADDRESS COMPARISON (PROOF) ===\n";
    long long distance = (long long)((char*)&stack_arr - (char*)heap_arr);
    std::cout << "Stack addr: " << &stack_arr << "\n";
    std::cout << "Heap addr:  " << heap_arr << "\n";
    std::cout << "Distance: " << distance << " bytes\n";
    std::cout << "Stack higher? " << (distance > 0 ? "YES ✓" : "NO") << "\n";
    // OUTPUT (typical):
    // Stack addr: 0x7ffc... (high address)
    // Heap addr:  0x5e42... (low address)
    // Distance: positive = stack higher in virtual memory ✓

    
    // CLEANUP
    delete heap_arr;  // Must manually free heap
    delete arr;       // Must manually free heap
    // stack_arr auto-deleted when main() ends
    
    std::cout << "\n=== CONCLUSION ===\n";
    std::cout << "std::array SIZE: compile-time ✓\n";
    std::cout << "std::array LOCATION: stack OR heap (YOUR CHOICE) ✓\n";
    std::cout << "Your misconception: BUSTED ✓\n";
    
    return 0;
}
