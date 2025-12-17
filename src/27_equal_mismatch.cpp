#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // ════════════════════════════════════════════════════════════════════════
    // PROBLEM 27: std::equal vs std::mismatch
    // ════════════════════════════════════════════════════════════════════════
    //
    // INPUT DATA (given):
    // v1 = {1, 2, 3, 4, 5}
    // v2 = {1, 2, 3, 99, 5}
    //
    // OBJECTIVE:
    // 1. Manually trace the comparison of v1 and v2.
    // 2. Identify the exact index and values where they differ.
    // 3. Implement the check using std::equal.

    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 99, 5};

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 1: Memory & Address Calculation
    // ════════════════════════════════════════════════════════════════════════
    //
    // Calculate addresses assuming v1 starts at 0x1000 and v2 at 0x2000.
    // sizeof(int) = 4 bytes.
    //
    // Index | v1 Addr | v1 Val | v2 Addr | v2 Val | Match?
    // 0     | 0x1000  | 1      | 0x2000  | 1      | YES
    // 1     | ???     | ?      | ???     | ?      | ?
    // 2     | ???     | ?      | ???     | ?      | ?
    // 3     | ???     | ?      | ???     | ?      | ?  <-- SURPRISE HERE
    // 4     | ???     | ?      | ???     | ?      | ?
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 2: Logic Trace
    // ════════════════════════════════════════════════════════════════════════
    //
    // LOOP TRACE:
    // Iteration 0: *p1 (1) == *p2 (1) ? continue
    // Iteration 1: ...
    // ...
    //
    // RESULT: Are vectors equal? YES/NO ___
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 3: Implementation
    // ════════════════════════════════════════════════════════════════════════

    // 1. Write std::equal call.
    bool result = std::equal(v1.begin(), v1.end(), v2.begin());

    // ════════════════════════════════════════════════════════════════════════
    // VERIFICATION
    // ════════════════════════════════════════════════════════════════════════

    std::cout << "v1 = {1, 2, 3, 4, 5}\n";
    std::cout << "v2 = {1, 2, 3, 99, 5}\n";

    // Uncomment when implemented:
    std::cout << "Equal? " << (result ? "YES" : "NO") << "\n";
    std::cout << "Expected: NO\n";

    return 0;
}
