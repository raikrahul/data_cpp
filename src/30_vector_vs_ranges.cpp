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

    auto v1 = std::vector<int>(N, 8);

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 2: Case 2 - Default Construct + Fill
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Construct v2 with N elements (default initialized to 0).
    std::vector<int> v2(N);

    // 2. Fill v2 with value 8 using std::ranges::fill (Modification).
    std::ranges::fill(v2, 8);

    // ════════════════════════════════════════════════════════════════════════
    // VERIFICATION
    // ════════════════════════════════════════════════════════════════════════

    std::cout << "Case 1 (Constructor): Initializes v1. Size=" << v1.size() << "\n";
    std::cout << "Case 2 (Ranges Fill): Modifies v2.    Size=" << v2.size() << "\n";

    if (v1 == v2) {
        std::cout << "Result: Vectors are IDENTICAL content-wise.\n";
        std::cout << "Difference: Initialization vs Modification.\n";
    } else {
        std::cout << "Result: Vectors DIFFER.\n";
    }

    return 0;
}
