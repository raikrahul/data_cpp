#include <iostream>
#include <ranges>

// This file teaches: iota_view is a FORMULA, not stored data

int main() {
    // ════════════════════════════════════════════════════════════════════════
    // EXPERIMENT 1: Look at actual iota_view source from libstdc++
    // ════════════════════════════════════════════════════════════════════════
    //
    // From /usr/include/c++/14/ranges line ~600:
    //
    // template<weakly_incrementable _Winc, ...>
    // class iota_view : public view_interface<iota_view<_Winc, _Bound>>
    // {
    // private:
    //     _Winc _M_value = _Winc();   // ← START value stored here
    //     _Bound _M_bound = _Bound(); // ← END value stored here
    //     
    //     // NO array, NO vector, NO heap pointer, NOTHING else
    // };
    //
    // sizeof(iota_view<int,int>) = sizeof(int) + sizeof(int) = 4 + 4 = 8 bytes
    //
    // ════════════════════════════════════════════════════════════════════════

    auto iota = std::views::iota(1, 6);  // Creates range [1, 2, 3, 4, 5]

    std::cout << "sizeof(iota_view) = " << sizeof(iota) << " bytes\n";
    // Expected: 8 bytes (just two ints: start=1, end=6)

    // ════════════════════════════════════════════════════════════════════════
    // EXPERIMENT 2: Trace iterator increment
    // ════════════════════════════════════════════════════════════════════════
    //
    // iota_view::iterator stores ONE value: the current position
    //
    // struct iterator {
    //     _Winc _M_value;  // current position, that's it
    // };
    //
    // operator*() returns: _M_value (no dereference, just return the value)
    // operator++() does: ++_M_value (increment the value, not a pointer)
    //
    // ════════════════════════════════════════════════════════════════════════

    auto it = iota.begin();
    std::cout << "\nIterator trace:\n";

    // Step 1: *begin() = _M_value = 1 (read the stored start value)
    std::cout << "Step 1: *it = " << *it << " (iterator stores value 1)\n";

    // Step 2: ++it increments _M_value: 1 → 2
    ++it;
    std::cout << "Step 2: ++it, *it = " << *it << " (iterator now stores 2)\n";

    // Step 3: ++it increments _M_value: 2 → 3
    ++it;
    std::cout << "Step 3: ++it, *it = " << *it << " (iterator now stores 3)\n";

    // ════════════════════════════════════════════════════════════════════════
    // EXPERIMENT 3: Memory state diagram
    // ════════════════════════════════════════════════════════════════════════
    //
    // Before iteration:
    //
    // iota_view @ 0x7FFFA000 (8 bytes on stack):
    // ┌───────────────────────────────────────────┐
    // │ [0x7FFFA000-0x7FFFA003]: _M_value = 1     │  ← start
    // │ [0x7FFFA004-0x7FFFA007]: _M_bound = 6     │  ← end (exclusive)
    // └───────────────────────────────────────────┘
    //
    // iterator @ 0x7FFFA010 (4 bytes on stack):
    // ┌───────────────────────────────────────────┐
    // │ [0x7FFFA010-0x7FFFA013]: _M_value = 1     │  ← current position
    // └───────────────────────────────────────────┘
    //
    // After ++it:
    // ┌───────────────────────────────────────────┐
    // │ [0x7FFFA010-0x7FFFA013]: _M_value = 2     │  ← incremented
    // └───────────────────────────────────────────┘
    //
    // TOTAL MEMORY: 8 (view) + 4 (iterator) = 12 bytes
    // NO HEAP ALLOCATION
    // NO ARRAY OF [1,2,3,4,5] ANYWHERE
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // EXPERIMENT 4: Prove no array exists - take 1000000 elements
    // ════════════════════════════════════════════════════════════════════════

    auto huge_iota = std::views::iota(0, 1000000);
    std::cout << "\nHuge iota(0, 1000000):\n";
    std::cout << "sizeof(huge_iota) = " << sizeof(huge_iota) << " bytes\n";
    // Still 8 bytes! No array of 1 million ints (which would be 4 MB)

    // Access element 999999 directly:
    auto it2 = huge_iota.begin();
    std::advance(it2, 999999);
    std::cout << "element[999999] = " << *it2 << "\n";
    // Value 999999 was COMPUTED by: 0 + 999999 increments
    // NOT loaded from memory address [heap + 999999 * 4]

    // ════════════════════════════════════════════════════════════════════════
    // EXPERIMENT 5: infinite iota - impossible with array
    // ════════════════════════════════════════════════════════════════════════

    auto infinite = std::views::iota(0);  // No end bound!
    std::cout << "\nInfinite iota(0):\n";
    std::cout << "sizeof(infinite) = " << sizeof(infinite) << " bytes\n";
    // Still 8 bytes (or 4 if unbounded uses different type)

    // Take first 10:
    std::cout << "First 10: ";
    for (auto x : infinite | std::views::take(10)) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    // Generates 0,1,2,3,4,5,6,7,8,9 on the fly
    // No array of infinite size needed

    // ════════════════════════════════════════════════════════════════════════
    // KEY INSIGHT: The iterator IS the value
    // ════════════════════════════════════════════════════════════════════════
    //
    // For ref_view:
    //   iterator = pointer to data → *it = load from memory address
    //
    // For iota_view:
    //   iterator = current integer value → *it = return the value itself
    //
    // operator*() implementation:
    //
    // ref_view:    return *_M_current;  // dereference pointer
    // iota_view:   return _M_value;     // just return the int
    //
    // operator++() implementation:
    //
    // ref_view:    ++_M_current;  // move pointer by sizeof(T)
    // iota_view:   ++_M_value;    // add 1 to the integer
    //
    // ════════════════════════════════════════════════════════════════════════

    return 0;
}
