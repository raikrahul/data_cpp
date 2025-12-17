#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // ════════════════════════════════════════════════════════════════════════
    // PROBLEM 26: Transform Parity Practice
    // ════════════════════════════════════════════════════════════════════════
    //
    // INPUT DATA (given):
    // v = {10, 23, 44, 15, 6, 91, 108}
    //
    // EXPECTED OUTPUT (to fill):
    // w = {?, ?, ?, ?, ?, ?, ?}
    //
    // RULE (from Problem 25):
    // v[i] even → w[i] = 1
    // v[i] odd  → w[i] = -1

    std::vector<int> v = {10, 23, 44, 15, 6, 91, 108};
    std::vector<int> w(v.size());  // Allocated but empty

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 1: Data Analysis Table
    // ════════════════════════════════════════════════════════════════════════
    //
    // Index | Value | % 2 | Even? | Expected w[i]
    // 0     | 10    | 0   | YES   | 1
    // 1     | 23    | 1   | NO    | -1
    // 2     | 44    | ?   | ?     | ?   <-- CALCULATE THIS
    // 3     | 15    | ?   | ?     | ?   <-- CALCULATE THIS
    // 4     | 6     | ?   | ?     | ?   <-- CALCULATE THIS
    // 5     | 91    | ?   | ?     | ?   <-- CALCULATE THIS
    // 6     | 108   | ?   | ?     | ?   <-- CALCULATE THIS
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 2: Logic Flow
    // ════════════════════════════════════════════════════════════════════════
    //
    // FUNCTION: f(x)
    // INPUT: int x
    // LOGIC:
    //    if (x % 2 == ___) return ___;
    //    else return ___;
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 3: Implementation
    // ════════════════════════════════════════════════════════════════════════

    // 1. Write the std::transform call below.
    // 2. Use a lambda function for the operation.
    // 3. DO NOT look at previous files. Derive syntax from memory/logic.

    // std::transform(...);

    // ════════════════════════════════════════════════════════════════════════
    // VERIFICATION
    // ════════════════════════════════════════════════════════════════════════

    std::cout << "v = {";
    for (size_t i = 0; i < v.size(); ++i) std::cout << v[i] << (i < v.size() - 1 ? ", " : "");
    std::cout << "}\n";

    std::cout << "w = {";
    for (size_t i = 0; i < w.size(); ++i) std::cout << w[i] << (i < w.size() - 1 ? ", " : "");
    std::cout << "}\n";

    std::cout << "\nExpected: {1, -1, 1, -1, 1, -1, 1}\n";

    return 0;
}
