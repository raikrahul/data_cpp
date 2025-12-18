#include <iostream>
#include <ranges>
#include <vector>

int main() {
    // ════════════════════════════════════════════════════════════════════════
    // PROBLEM 33: C++ Ranges Views vs Vector Memory Layout
    // ════════════════════════════════════════════════════════════════════════
    //
    // GOAL: Understand memory footprint difference between view and vector
    // METHOD: Calculate by hand using concrete addresses
    //
    // Assumptions (for manual calculation):
    // - 64-bit system: sizeof(void*) = 8, sizeof(size_t) = 8
    // - view object located at stack address: 0x1000
    // - vector object located at stack address: 0x3000
    // - vector's heap data located at: 0x4000
    // - Data range that view references: [0x2000, 0x2080)
    // - sizeof(int) = 4 bytes
    // - Little-endian byte order

    std::vector<int> source = {10, 20, 30, 40, 50, 60, 70, 80};
    auto view = std::ranges::ref_view(source);
    (void)view;  // Suppress unused warning until verification code uncommented

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 1: Calculate sizeof(view)
    // ════════════════════════════════════════════════════════════════════════
    //
    // Step 1: view is a struct with how many pointer members? ____
    // Step 2: On 64-bit system, sizeof(pointer) = __8__
    // Step 3: Calculate: _2___ pointers × ___8_ bytes/pointer = _16___ bytes
    // Step 4: Check alignment: 16 bytes aligned to ____ boundary? yes/no: _yes___
    // Step 5: Any padding needed? _no___ (yes/no, justify)
    //
    // Write actual measurement:
    std::cout << "sizeof(view) = " << sizeof(view) << "\n";
    // Expected from calculation: _16___ bytes , no just 8 
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 2: Calculate sizeof(vector)
    // ════════════════════════════════════════════════════════════════════════
    //
    // Step 1: vector is a struct with members: {T* data, size_t size, size_t capacity}
    // Step 2: sizeof(T*) on 64-bit = _4___
    // Step 3: sizeof(size_t) on 64-bit = _4___
    // Step 4: Calculate: ____ + ____ + ____ = ____ bytes
    // Step 5: Alignment check: ____ bytes aligned to ____ boundary? ____
    //
    // Write actual measurement:
    std::cout << "sizeof(vector) = " << sizeof(source) << "\n";
    // Expected: ____ bytes
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 3: Memory layout of view at 0x1000
    // ════════════════════════════════════════════════════════════════════════
    //
    // Assume view object starts at address 0x1000
    //
    // Memory layout:
    // [0x1000 - 0x1007]: begin pointer → points to address 0x____1000
    // [0x1008 - 0x100F]: end pointer   → points to address 0x_100f___
    //
    // If view references data in range [0x2000, 0x2080):
    // Step 1: begin_ptr value stored at [0x1000-0x1007] = 0x2000
    //         In little-endian bytes: [00,20,00,00,00,00,00,00]
    //         Verify: byte at 0x1000 = 0x__, byte at 0x1001 = 0x__, ..., byte at 0x1007 = 0x__
    //
    // Step 2: end_ptr value stored at [0x1008-0x100F] = 0x2080
    //         In little-endian bytes: [80,20,00,00,00,00,00,00]
    //         Verify: byte at 0x1008 = 0x__, byte at 0x1009 = 0x__, ..., byte at 0x100F = 0x__
    //
    // Step 3: Range size = end - begin = 0x2080 - 0x2000 = 0x80 = 128 bytes
    // Step 4: Element count = 128 bytes ÷ sizeof(int) = 128 ÷ 4 = 32 elements
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 4: Memory layout of vector at 0x3000
    // ════════════════════════════════════════════════════════════════════════
    //
    // Assume vector object starts at 0x3000, heap data at 0x4000
    //
    // Stack memory layout:
    // [0x3000 - 0x3007]: data pointer → value = 0x4000 (heap address)
    //         Little-endian bytes: [00,40,00,00,00,00,00,00]
    // [0x3008 - 0x300F]: size → value = 8 (number of elements)
    //         Little-endian bytes: [08,00,00,00,00,00,00,00]
    // [0x3010 - 0x3017]: capacity → value = 8
    //         Little-endian bytes: [08,00,00,00,00,00,00,00]
    //
    // Total stack footprint = ____ bytes
    //
    // Heap memory layout at 0x4000:
    // [0x4000-0x4003]: element[0] = 10 → bytes[0A,00,00,00]
    // [0x4004-0x4007]: element[1] = 20 → bytes[14,00,00,00]
    // [0x4008-0x400B]: element[2] = 30 → bytes[__,__,__,__]
    // [0x400C-0x400F]: element[3] = 40 → bytes[__,__,__,__]
    // [0x4010-0x4013]: element[4] = 50 → bytes[__,__,__,__]
    // [0x4014-0x4017]: element[5] = 60 → bytes[__,__,__,__]
    // [0x4018-0x401B]: element[6] = 70 → bytes[__,__,__,__]
    // [0x401C-0x401F]: element[7] = 80 → bytes[__,__,__,__]
    //
    // Heap footprint = 8 elements × 4 bytes = 32____ bytes
    //
    // Total vector memory = stack 4____ + heap _32___ = ____ bytes
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 5: Compare memory footprints
    // ════════════════════════════════════════════════════════════════════════
    //
    // View total memory:
    // - Stack: ____8 bytes (from TODO 1)
    // - Heap: ____0 bytes (view does not allocate)
    // - Total: ____8 bytes
    //
    // Vector total memory:
    // - Stack: _8___ bytes (from TODO 2)
    // - Heap: ___32_ bytes (from TODO 4)
    // - Total: ____ + ____ = _40___ bytes
    //
    // Savings: ____ - ____ = ____ bytes
    // Percentage: (____ ÷ ____) × 100 = _____%
    //
    // Verify the claim: "savings = 40 bytes → 71.43% reduction"
    // Your calculation: savings = ____ bytes → ____% reduction
    // Match? yes/no: ____
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 6: Heap allocation analysis
    // ════════════════════════════════════════════════════════════════════════
    //
    // Vector construction: std::vector<int> v(8);
    //
    // Step 1: Requested allocation = 8 elements × 4 bytes = ____ bytes
    // Step 2: Malloc overhead (metadata header) ≈ 16 bytes
    // Step 3: Alignment requirement = 16 bytes
    // Step 4: Actual heap block = ____ + ____ = ____ bytes, rounded to ____ bytes
    //
    // View construction: auto view = std::ranges::ref_view(v);
    //
    // Step 1: Heap allocation = ____ bytes (trick question!)
    // Step 2: Why? (explain in symbols):
    //         view → stores_pointers_only → no_malloc_call → heap=0
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 7: DANGER ZONE - Lifetime analysis
    // ════════════════════════════════════════════════════════════════════════
    //
    // Scenario: View outlives source vector
    //
    // Code:
    // auto get_view() {
    //     std::vector<int> temp = {1, 2, 3};  // temp allocated on stack @ 0x7FFF9000
    //     // temp.data() on heap @ 0x5000
    //     auto v = std::ranges::ref_view(temp);
    //     // v.begin_ptr = 0x5000, v.end_ptr = 0x500B
    //     return v;// temp destroyed here
    // }  // What happens to addresses 0x7FFF9000 and 0x5000?
    //
    // Analysis:
    // Step 1: After function returns, temp destructor called
    // /         - Stack memory [0x7FFF9000 - 0x7FFF9017] → ___free_
    //         - Heap memory [0x5000 - 0x500B] → free(0x5000) called
    //
    // Step 2: Returned view object has:
    //         - begin_ptr = 0x5000 (points to freed memory)
    //         - end_ptr = 0x500B (points to freed memory)
    //
    // Step 3: If caller dereferences view:
    //         auto v = get_view();
    //         int x = *v.begin();  // Dereferences address 0x5000
    //
    // Step 4: Consequence:
    //         [ ] Segmentation fault (SIGSEGV)
    //         [ ] Heap-use-after-free (ASAN detected)
    //         [ ] Undefined behavior (garbage value)
    //         [ ] All of the above
    //
    // Prevention strategy:____NO
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 8: Copy semantics comparison
    // ════════════════════════════════════════════════════════════════════════
    //
    // View copy:
    // auto v1 = std::ranges::ref_view(source);
    // auto v2 = v1;  // Copy
    //
    // Step 1: Bytes copied = sizeof(view) = ____ bytes 8
    // Step 2: memcpy operation:
    //         Source: [0x1000 - 0x100F] (16 bytes)
    //         Dest:   [0x1020 - 0x102F] (16 bytes)
    //         Copy: [00,20,00,00,00,00,00,00,80,20,00,00,00,00,00,00]
    // Step 3: CPU cycles ≈ 4 cycles (memcpy 16 bytes)
    // Step 4: v1 and v2 both point to address 0x____ (same or different?)
    // /  / SAME 
    // Vector copy:
    // std::vector<int> vec1 = {1,2,3,4,5,6,7,8};
    // std::vector<int> vec2 = vec1;  // Copy
    //
    // Step 1: Stack copy = sizeof(vector) = 8____ bytes
    // Step 2: Heap allocation = 8 elements × 4 = _32___ bytes
    // Step 3: Heap copy = memcpy(____32 bytes)
    // Step 4: Total bytes copied = ____ + ____ = ____40 bytes
    // Step 5: CPU cycles ≈ 4 (stack) + ____ (heap alloc) + ____ (memcpy) = ____ cycles
    // Step 6: vec1.data() = 0x8000____, vec2.data() = 0x__8004__ (same or different?)
    //
    // Ratio: vector_copy_cost ÷ view_copy_cost = ____ ÷ 4 = ____×
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // VERIFICATION (uncomment after filling above)
    // ════════════════════════════════════════════════════════════════════════

    std::cout << "sizeof(view) = " << sizeof(view) << " bytes\n";
    std::cout << "sizeof(vector) = " << sizeof(source) << " bytes\n";
    std::cout << "source.size() = " << source.size() << "\n";
    std::cout << "source.capacity() = " << source.capacity() << "\n";

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // Reverse using traditional loop to avoid ranges::for_each issues
    size_t n = v.size();
    for (size_t i = 0; i < n/2; ++i) {
        std::swap(v[i], v[n-1-i]);
    }
    
    // Print reversed vector
    std::cout << "Reversed vector: ";
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    auto multiples_of_18 = std::views::iota(1, 10) | std::views::transform([](int i){ return i * 18; });
    auto multiples_of_27 = std::views::iota(1, 10) | std::views::transform([](int i){ return i * 27; });
    (void)multiples_of_27;  // Unused for now
    auto first_two = std::views::take(2);
    auto result = multiples_of_18
                     | std::views::filter([](int x){ return x % 27 == 0; })
                     | first_two;
    
    std::cout << "Result: ";
    for (int x : result) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    return 0;
}
