#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // ════════════════════════════════════════════════════════════════════════
    // PROBLEM 30: Vector Constructor vs Ranges Fill (The Hidden Cost)
    // ════════════════════════════════════════════════════════════════════════
    //
    // OBJECTIVE:
    // Demonstrate the memory traffic difference between:
    // Case 1: std::vector<int> v1(N, 8);
    // Case 2: std::vector<int> v2(N); std::ranges::fill(v2, 8);
    //
    // CONSTANTS:
    // N = 100 (Small scale trace)
    // N_LARGE = 1,048,576 (2^20) (Punishment calculation)

    const size_t N = 100;
    (void)N;  // Suppress unused variable warning

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 1: Case 1 - Direct Construction
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Construct v1 with N elements of value 8.
    // 2. TRACE: How many times is memory written?
    //    Allocation -> uninitialized_fill_n -> Done.
    //    Writes = N.

    // std::vector<int> v1...

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 2: Case 2 - Default Construct + Fill
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Construct v2 with N elements (default initialized to 0).
    // 2. Fill v2 with value 8 using std::ranges::fill.
    // 3. TRACE: How many times is memory written?
    //    Allocation -> uninitialized_fill_n(0) -> ranges::fill(8).
    //    Writes = N (Zero) + N (Eight) = 2N.

    // std::vector<int> v2...
    // std::ranges::fill...

    // ════════════════════════════════════════════════════════════════════════
    // VERIFICATION
    // ════════════════════════════════════════════════════════════════════════

    std::cout << "Case 1 (Constructor): Optimal (1 pass)\n";
    std::cout << "Case 2 (Fill): Suboptimal (2 passes)\n";
    std::cout << "Punishment N=2^20: Extra 4MB writes in Case 2.\n";

    return 0;
}
