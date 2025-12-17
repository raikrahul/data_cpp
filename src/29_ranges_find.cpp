#include <algorithm>
#include <iostream>
#include <iterator>  // for distance
#include <vector>

int main() {
    // ════════════════════════════════════════════════════════════════════════
    // PROBLEM 29: Ranges: Find & Equal (The "Fine" Algorithm)
    // ════════════════════════════════════════════════════════════════════════
    //
    // Transcript Analysis Data:
    // w = {5, 8, 2, 9, 2, 7}
    // Memory: Heap Data @ 0x2000
    // Search Target: 2
    // Correct Match: Index 2 (Address 0x2008)
    // False Info: "Index 4" (Transcript line 15 error)

    std::vector<int> w = {5, 8, 2, 9, 2, 7};

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 1: Manual Memory Trace (std::ranges::find)
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Trace the loop for std::ranges::find(w, 2).
    // 2. Calculate the iterators for each step.
    // 3. Identify the EXACT return address.
    //
    // Iter 0: Addr 0x2000 | Val 5 | Match? NO
    // Iter 1: Addr 0x2004 | Val 8 | Match? NO
    // Iter 2: Addr 0x2008 | Val 2 | Match? YES -> BREAK

    auto it = std::ranges::find(w, 2);

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 2: Iterator to Index (std::ranges::distance)
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Use std::ranges::distance(begin, it).
    // 2. Manually calculate the pointer arithmetic: (0x2008 - 0x2000) / 4.
    // 3. Confirm result is 2, NOT 4.

    long index = std::ranges::distance(w.begin(), it);

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 3: Ranges Equal (Reduction)
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Define v = {5, 8, 2, 9, 2, 7} (Identical).
    // 2. Define x = {5, 8, 2} (Prefix).
    // 3. Check equality.

    std::vector<int> v = {5, 8, 2, 9, 2, 7};
    std::vector<int> x = {5, 8, 2};
    std::cout << "v == x? " << std::boolalpha << std::ranges::equal(v, x) << "\n";

    // ════════════════════════════════════════════════════════════════════════
    // VERIFICATION
    // ════════════════════════════════════════════════════════════════════════

    std::cout << "w = {5, 8, 2, 9, 2, 7}\n";
    std::cout << "Expected Find Result: Index 2 (Address 0x2008)\n";
    std::cout << "Computed Index: " << index << "\n";

    return 0;
}
