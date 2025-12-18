#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    // ════════════════════════════════════════════════════════════════════════
    // PROBLEM 27: std::equal vs std::mismatch - TEACHING PROGRAM
    // ════════════════════════════════════════════════════════════════════════
    //
    // DO NOT READ AHEAD. DO EACH TODO BY HAND WITH PEN AND PAPER.
    //
    // Memory layout (assume):
    // v1.data() = 0x1000
    // v2.data() = 0x2000
    // sizeof(int) = 4 bytes
    // Little-endian byte order

    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 99, 5};

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 1: Trace comparison iteration 0
    // ════════════════════════════════════════════════════════════════════════
    //
    // Given: p1 = 0x1000, p2 = 0x2000 (initial pointers)
    //
    // Calculate by hand:
    // Step 1: p1_offset = 0x1000 + 0×4 = 0x____ (write hex address)
    // Step 2: Read 4 bytes from memory at 0x1000:
    //         [0x1000]=0x01, [0x1001]=0x00, [0x1002]=0x00, [0x1003]=0x00
    //         Assemble little-endian: 0x01 | (0x00<<8) | (0x00<<16) | (0x00<<24)
    //         Result: *p1 = ____ (decimal)
    // Step 3: p2_offset = 0x2000 + 0×4 = 0x____ (write hex address)
    // Step 4: Read 4 bytes from memory at 0x2000:
    //         [0x2000]=0x01, [0x2001]=0x00, [0x2002]=0x00, [0x2003]=0x00
    //         Assemble: Result: *p2 = ____ (decimal)
    // Step 5: Compare *p1 == *p2 → ____ == ____ → ✓ or ✗ ?
    // Step 6: If match, p1++ → p1 = 0x1000 + 4 = 0x____
    //                  p2++ → p2 = 0x2000 + 4 = 0x____
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 2: Trace comparison iteration 1
    // ════════════════════════════════════════════════════════════════════════
    //
    // Given: p1 = 0x____ (from TODO 1), p2 = 0x____ (from TODO 1)
    //
    // Step 1: Calculate index: (p1 - v1_base) ÷ sizeof(int)
    //         = (0x____ - 0x1000) ÷ 4 = ____ (decimal index)
    // Step 2: Load *p1 from address 0x____:
    //         Memory bytes: [0x____]=0x02, [0x____]=0x00, [0x____]=0x00, [0x____]=0x00
    //         Assemble: *p1 = ____
    // Step 3: Load *p2 from address 0x____:
    //         Memory bytes: [0x____]=0x__, [0x____]=0x__, [0x____]=0x__, [0x____]=0x__
    //         Assemble: *p2 = ____
    // Step 4: Compare ____ == ____ → Result: ✓ or ✗ ?
    // Step 5: Update pointers: p1 = 0x____ + 4 = 0x____
    //                          p2 = 0x____ + 4 = 0x____
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 3: Trace comparison iteration 2
    // ════════════════════════════════════════════════════════════════════════
    //
    // Given: p1 = 0x____ (from TODO 2), p2 = 0x____ (from TODO 2)
    //
    // Step 1: Index = (0x____ - 0x1000) ÷ 4 = ____
    // Step 2: Address of v1[____] = 0x____
    //         Load bytes: [0x____]=0x__, [0x____+1]=0x__, [0x____+2]=0x__, [0x____+3]=0x__
    //         *p1 = ____
    // Step 3: Address of v2[____] = 0x____
    //         Load bytes: [0x____]=0x__, [0x____+1]=0x__, [0x____+2]=0x__, [0x____+3]=0x__
    //         *p2 = ____
    // Step 4: ____ == ____ → ✓ / ✗
    // Step 5: p1 = 0x____, p2 = 0x____
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 4: Trace comparison iteration 3 - THE SURPRISE
    // ════════════════════════════════════════════════════════════════════════
    //
    // Given: p1 = 0x____ (from TODO 3), p2 = 0x____ (from TODO 3)
    //
    // Step 1: Index = (0x____ - 0x1000) ÷ 4 = ____
    // Step 2: v1[____] address = 0x____
    //         Memory lookup in data array v1 = {1, 2, 3, 4, 5}
    //         v1[____] = ____
    //         Hex representation: 0x00000004
    //         Bytes: [0x____]=0x04, [0x____+1]=0x00, [0x____+2]=0x00, [0x____+3]=0x00
    // Step 3: v2[____] address = 0x____
    //         Memory lookup in data array v2 = {1, 2, 3, 99, 5}
    //         v2[____] = ____
    //         Hex representation: 99 decimal = 0x00000063
    //         Bytes: [0x____]=0x63, [0x____+1]=0x00, [0x____+2]=0x00, [0x____+3]=0x00
    // Step 4: Compare: ____ == ____ → ✓ / ✗ ?
    // Step 5: If mismatch detected:
    //         - std::equal algorithm stops immediately
    //         - Return value = false
    //         - v1[4] at 0x____ is NEVER accessed
    //         - v2[4] at 0x____ is NEVER accessed
    // Step 6: Total iterations before stop = ____
    //         Total memory loads = ____ (each iteration loads 2 values)
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 5: Implement std::equal call (NO SOLUTION - JUST SYNTAX)
    // ════════════════════════════════════════════════════════════════════════
    //
    // Write the function call:
    // bool result = std::equal( _______________, _______________, _______________ );
    //                             ^fill arg1       ^fill arg2       ^fill arg3
    //
    // Arg 1: Iterator to first element of v1 → v1.______()
    // Arg 2: Iterator past last element of v1 → v1.______()
    // Arg 3: Iterator to first element of v2 → v2.______()
    //
    // Expected result after execution: result = true / false ? ____
    //
    // ════════════════════════════════════════════════════════════════════════

    // TODO: Remove this solution and fill above
    // bool result = std::equal(v1.begin(), v1.end(), v2.begin());

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 6: std::mismatch analysis
    // ════════════════════════════════════════════════════════════════════════
    //
    // std::mismatch returns different type than std::equal
    //
    // Step 1: Return type = std::pair<_____________, _____________>
    //         (fill iterator types)
    // Step 2: If vectors match completely:
    //         - pair.first points to _____________ (v1.end() or something else?)
    //         - pair.second points to _____________
    // Step 3: If mismatch at index 3:
    //         - pair.first address = v1.begin() + ____ × 4 = 0x1000 + ____ = 0x____
    //         - pair.second address = v2.begin() + ____ × 4 = 0x2000 + ____ = 0x____
    //         - *pair.first value = ____
    //         - *pair.second value = ____
    //
    // Write the call:
    // auto mis = std::mismatch( _______, _______, _______ );
    //
    // ════════════════════════════════════════════════════════════════════════

    // TODO: Implement mismatch call here
    // auto mis = std::mismatch(v1.begin(), v1.end(), v2.begin());

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 7: DANGER ZONE - Size mismatch scenario
    // ════════════════════════════════════════════════════════════════════════
    //
    // Predict failure case:
    // v3 = {10, 20, 30, 40, 50} (size 5) at address 0x3000
    // v4 = {10, 20, 30} (size 3) at address 0x4000
    //
    // Call: std::equal(v3.begin(), v3.end(), v4.begin())
    //
    // Step 1: Iteration 0, 1, 2 will pass (why? ____)
    // Step 2: Iteration 3:
    //         - p3 = 0x3000 + 3×4 = 0x____
    //         - p4 = 0x4000 + 3×4 = 0x____
    //         - v4.end() = 0x4000 + 3×4 = 0x____
    //         - p4 == v4.end() ? ____ (yes/no)
    //         - Does std::equal check this? ____ (yes/no)
    // Step 3: Algorithm accesses memory at 0x____
    //         This address is: [ ] inside v4 allocation
    //                          [ ] outside v4 allocation
    // Step 4: Consequence:
    //         [ ] Segmentation fault (SIGSEGV)
    //         [ ] Garbage value read
    //         [ ] Undefined behavior
    //         [ ] All of the above
    // Step 5: Prevention:
    //         Use ___-parameter version of std::equal:
    //         std::equal(v3.begin(), v3.end(), v4.begin(), v4._____)
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // VERIFICATION (fill these after completing above TODOs)
    // ════════════════════════════════════════════════════════════════════════

    std::cout << "v1 = {1, 2, 3, 4, 5}\n";
    std::cout << "v2 = {1, 2, 3, 99, 5}\n";

    // Uncomment after implementing TODO 5:
    // std::cout << "Equal? " << (result ? "YES" : "NO") << "\n";
    // std::cout << "Expected: NO\n";

    // Uncomment after implementing TODO 6:
    // std::cout << "Mismatch at index: " << (mis.first - v1.begin()) << "\n";
    // std::cout << "v1[" << (mis.first - v1.begin()) << "] = " << *mis.first << "\n";
    // std::cout << "v2[" << (mis.second - v2.begin()) << "] = " << *mis.second << "\n";

    return 0;
}
