#include <iostream>
#include <ranges>
#include <vector>

int main() {
    // ════════════════════════════════════════════════════════════════════════
    // PROBLEM 34: View Abstraction Layer - Pointer Chasing Exercise
    // ════════════════════════════════════════════════════════════════════════
    //
    // GOAL: Understand why views hide data behind pointers
    // YOU WILL: Trace memory manually, chase pointers, find the actual ints

    std::vector<int> source = {10, 20, 30, 40, 50, 60, 70, 80};
    auto view = std::ranges::ref_view(source);

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 1: Memory Layout Analysis
    // ════════════════════════════════════════════════════════════════════════
    //
    // Assume: view @ 0x1000, source @ 0x2000, heap data @ 0x3000
    //
    // DRAW THIS BY HAND:
    // ┌─────────────────────────────────────────┐
    // │ view @ 0x1000 (8 bytes)                 │
    // │  [0x1000-0x1007]: _M_r = 0x100-1007         │──→ points to ____
    // └─────────────────────────────────────────┘
    //                      │
    //                      ▼
    // ┌─────────────────────────────────────────┐
    // │ source @ 0x____ (24 bytes)              │
    // │  [0x____-0x____]: data_ptr = 0x____     │──→ points to ____
    // │  [0x____-0x____]: size = ____           │
    // │  [0x____-0x____]: capacity = ____       │
    // └─────────────────────────────────────────┘
    //                      │
    //                      ▼
    // ┌─────────────────────────────────────────┐
    // │ heap @ 0x____ (32 bytes)                │
    // │  [0x____]: int[0] = 10                │  ← ACTUAL DATA HERE
    // │  [0x____]: int[1] = 20                │
    // │  ...                                     │
    // │  [0x____]: int[7] = 80jjjj                │
    // └─────────────────────────────────────────┘
    //
    // Question: How many pointer jumps to reach int[0]? 2
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 2: Byte-Level Memory Trace
    // ════════════════════════════════════════════════════════════════════════
    //
    // Given memory dump (little-endian):
    //
    // 0x1000: 00 20 00 00 00 00 00 00     ← view._M_r bytes
    //
    // Step 1: Assemble pointer from bytes
    //         byte[0]=0x00, byte[1]=0x20, byte[2]=0x00, ... byte[7]=0x00
    //         little-endian: value = byte[0] | (byte[1]<<8) | (byte[2]<<16) | ...
    //         = 0x00 | (0x20 << 8) | (0x00 << 16) | ...
    //         = 0x00 | 0x2000 | 0x00 | ...
    //         = 0x________________
    //
    // Step 2: This address is the vector object location
    //         vector @ 0x____
    //
    // Continue tracing (you fill in):
    //
    // 0x2000: 00 30 00 00 00 00 00 00     ← vector.data_ptr bytes
    // 0x2008: 08 00 00 00 00 00 00 00     ← vector.size bytes
    // 0x2010: 08 00 00 00 00 00 00 00     ← vector.capacity bytes
    //
    // Step 3: Assemble data_ptr = 0x________________
    // Step 4: Assemble size = ____
    // Step 5: Assemble capacity = ____
    //
    // 0x3000: 0A 00 00 00                 ← int[0] bytes
    // 0x3004: 14 00 00 00                 ← int[1] bytes
    //
    // Step 6: Assemble int[0] = 0x0A = ____ decimal
    // Step 7: Assemble int[1] = 0x14 = ____ decimal
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 3: Access Cost Analysis
    // ════════════════════════════════════════════════════════════════════════
    //
    // To access view's first element:
    //
    // Step 1: Read view._M_r @ 0x1000 → 8 bytes → ptr = 0x2000
    //         Cost: 1 memory load = ____ cycles (assume 4 cycles/load)
    //
    // Step 2: Read vector.data @ 0x2000 → 8 bytes → ptr = 0x3000
    //         Cost: 1 memory load = ____ cycles
    //
    // Step 3: Read int @ 0x3000 → 4 bytes → value = 10
    //         Cost: 1 memory load = ____ cycles
    //
    // Total cost: ____ + ____ + ____ = ____ cycles
    //
    // vs. Direct array access: int arr[8]; arr[0];
    //         Cost: 1 memory load = ____ cycles
    //
    // Overhead ratio: view_cost / direct_cost = ____ / ____ = ____×
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 4: Cannot Print View Directly
    // ════════════════════════════════════════════════════════════════════════
    //
    // This FAILS:
    // std::cout << view;  // error: no match for 'operator<<'
    //
    // Why? view is NOT a container with operator<<
    //      view is a description, not data
    //
    // This WORKS:
    // for (auto x : view) std::cout << x << " ";
    //
    // What happens in the for-loop?
    // Step 1: begin(view) called → returns iterator pointing to 0x___heap statrt_
    // Step 2: end(view) called → returns iterator pointing to 0x___heap end_
    // Step 3: *iterator → dereferences 0x____ → loads value ____
    // Step 4: ++iterator → advances pointer by sizeof(int) = ____ bytes
    //         new_addr = 0x____ + ____ = 0x____
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 5: Cannot Subscript View
    // ════════════════════════════════════════════════════════════════════════
    //
    // This FAILS:
    // auto x = view[5];  // error: no match for 'operator[]'
    //
    // This WORKS:
    // auto it = std::ranges::begin(view);
    // auto x = *(it + 5);
    //
    // Calculate address manually:
    // it = begin(view) = address of first element = 0x3000
    // it + 5 = 0x3000 + 5 × sizeof(int)
    //        = 0x3000 + 5 × 4
    //        = 0x3000 + 20
    //        = 0x3000 + 0x14
    //        = 0x___3014_
    //
    // *(it + 5) = value at 0x____ = ____
    //
    // Verify: element[5] of {10,20,30,40,50,60,70,80} = ____
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 6: Contrast with iota_view (no pointer chasing)
    // ════════════════════════════════════════════════════════════════════════
    //
    auto iota = std::views::iota(0, 32);
    (void)iota;
    //
    // iota_view stores: {_M_value = 0, _M_bound = 32}
    //
    // Memory layout @ 0x5000:
    // ┌─────────────────────────────────────────┐
    // │ iota @ 0x5000 (8 bytes)                 │
    // │  [0x5000-0x5003]: _M_value = 0          │  ← NO pointer
    // │  [0x5004-0x5007]: _M_bound = 32         │  ← NO pointer
    // └─────────────────────────────────────────┘
    //
    // To access iota's first element:
    // Step 1: Read _M_value @ 0x5000 → 4 bytes → value = 0
    //         Cost: 1 memory load = ____ cycles
    //         NO POINTER CHASING NEEDED
    //
    // To access iota's element[5]:
    // value = _M_value + 5 = 0 + 5 = 5
    // This is COMPUTED, not LOADED
    // Cost: 1 ADD instruction = ____ cycle
    //
    // ref_view element access: ____ cycles
    // iota_view element access: ____ cycle
    // Speedup: ____× I am confused here 
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 7: DANGER - Empty View
    // ════════════════════════════════════════════════════════════════════════
    //
    // std::vector<int> empty_vec;
    // auto empty_view = std::ranges::ref_view(empty_vec);
    //
    // empty_vec state:
    //   data_ptr = nullptr (0x0) or some sentinel
    //   size = 0
    //   capacity = 0
    //
    // empty_view._M_r = address of empty_vec
    //
    // begin(empty_view) = ____  (nullptr or sentinel)
    // end(empty_view) = ____
    // begin == end? ____ (yes/no)
    // /yes/
    // If user does: *empty_view.begin()
    //   = dereference address 0x____
    //   = crash? yes
    //   = signal number = ____
    //   = exit code = ____
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════

    std::cout << "sizeof(view) = " << sizeof(view) << " bytes\n";
    std::cout << "sizeof(source) = " << sizeof(source) << " bytes\n";
    std::cout << "sizeof(iota) = " << sizeof(iota) << " bytes\n";
    
    std::cout << "\nIterating view (hidden pointer chasing):\n";
    for (auto x : view) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\nIterating iota (pure computation):\n";
    for (auto x : iota | std::views::take(8)) std::cout << x << " ";
    std::cout << "\n";

    // Access element by pointer arithmetic (since no operator[])
    auto it = std::ranges::begin(view);
    std::cout << "\n*(begin + 5) = " << *(it + 5) << " (expected: 60)\n";

    return 0;
}
