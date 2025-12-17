#include <algorithm>  // for ranges::transform
#include <iostream>
#include <numeric>  // for std::iota
#include <vector>

int main() {
    // ════════════════════════════════════════════════════════════════════════
    // PROBLEM 31: Iota & Transform (Multiples of 7)
    // ════════════════════════════════════════════════════════════════════════
    //
    // OBJECTIVE:
    // Generate a vector v of size 20 containing {0, 7, 14, ..., 133}.
    //
    // PIPELINE:
    // 1. std::iota -> Fill with {0, 1, 2, ..., 19}
    // 2. std::ranges::transform -> Apply (n * 7)

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 1: Setup & Iota
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Declare vector v(20).
    // 2. Use std::iota(v.begin(), v.end(), 0).
    // 3. TRACE: v[0]=0, v[1]=1, ... v[19]=19.

    std::vector<int> v(20);
    std::iota(v.begin(), v.end(), 0);

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 2: Transform
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Use std::ranges::transform to multiply each element by 7.
    // 2. TRACE: 0->0, 1->7, 2->14...

    std::ranges::transform(v.begin(), v.end(), v.begin(), [](int n) { return n * 7; });

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 3: Any Of (Multiple of 28?)
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Use std::ranges::any_of(v, lambda) to check if any element is divisible by 28.
    // 2. TRACE:
    //    v[0]=0   -> 0 % 28 == 0? (Careful with 0, usually considered multiple)
    //    v[1]=7   -> 7 % 28 == 7
    //    v[2]=14  -> 14 % 28 == 14
    //    v[3]=21  -> 21 % 28 == 21
    //    v[4]=28  -> 28 % 28 == 0 -> Found!

    // bool has_multiple_28 = std::ranges::any_of(...);

    // ════════════════════════════════════════════════════════════════════════
    // VERIFICATION
    // ════════════════════════════════════════════════════════════════════════

    std::cout << "v = {";
    for (size_t i = 0; i < v.size(); ++i) std::cout << v[i] << (i < v.size() - 1 ? ", " : "");

    std::cout << "}\n";

    return 0;
}
