#include <algorithm>  // for generate
#include <cmath>      // for sqrt
#include <iostream>
#include <numeric>  // for transform_reduce
#include <random>
#include <vector>

struct Stats {
    double sum;
    double sum_sq;
};

// Start strict derivation here...
// We need a binary operation to combine two Stats objects (Reduce)
// We need a unary operation to convert int -> Stats (Map)

int main() {
    // ════════════════════════════════════════════════════════════════════════
    // PROBLEM 32: Transform Reduce (Avg & StdDev)
    // ════════════════════════════════════════════════════════════════════════
    //
    // OBJECTIVE:
    // 1. Generate 100,000 random integers (1-99).
    // 2. Use transform_reduce to calculate Sum and SumSq in ONE pass.
    // 3. Compute Mean and StdDev.

    const size_t N = 100000;
    std::vector<int> v(N);

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 1: Generate Data
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Setup mt19937 and uniform_int_distribution(1, 99).
    // 2. Fill v using ranges::generate.

    std::mt19937 gen(1234);
    std::uniform_int_distribution<> dist(1, 99);
    std::ranges::generate(v, [&] { return dist(gen); });

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 2: Transform Reduce
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Map: int x -> Stats{x, x*x}
    // 2. Reduce: Stats a, Stats b -> Stats{a.sum+b.sum, a.sum_sq+b.sum_sq}
    // 3. Initial Value: Stats{0, 0}

    Stats result = std::transform_reduce(
        v.begin(), v.end(), Stats{0.0, 0.0},
        [](Stats a, Stats b) { return Stats{a.sum + b.sum, a.sum_sq + b.sum_sq}; },
        [](int x) { return Stats{static_cast<double>(x), static_cast<double>(x * x)}; });

    // ════════════════════════════════════════════════════════════════════════
    // VERIFICATION
    // ════════════════════════════════════════════════════════════════════════

    // Calculate Mean = Sum / N
    // Calculate Variance = (SumSq / N) - Mean^2
    // Calculate StdDev = sqrt(Variance)

    double mean = result.sum / N;
    double variance = (result.sum_sq / N) - (mean * mean);
    double stddev = std::sqrt(variance);

    std::cout << "Mean: " << mean << "\n";
    std::cout << "StdDev: " << stddev << "\n";

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 3: Ranges Transform (Square Each Element)
    // ════════════════════════════════════════════════════════════════════════
    //
    // 1. Create a small vector w = {2, 3, 4, 5}.
    // 2. Use std::ranges::transform(w, w.begin(), lambda).
    // 3. Lambda: takes int, returns int*int.
    // 4. TRACE:
    //    w[0]=2 -> 2*2=4 -> w[0]=4
    //    w[1]=3 -> 3*3=9 -> w[1]=9
    //    w[2]=4 -> 4*4=16 -> w[2]=16
    //    w[3]=5 -> 5*5=25 -> w[3]=25

    std::vector<int> w = {2, 3, 4, 5};
    std::ranges::transform(w, w.begin(), [](int x) { return x * x; });

    std::ranges::for_each(w, [](int x) { std::cout << x << " "; });

    std::cout << "w after squaring: {";
    for (size_t i = 0; i < w.size(); ++i) std::cout << w[i] << (i < w.size() - 1 ? ", " : "");
    std::cout << "}\n";

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 4: Neighbor Average (w[i] = 0.5 * (v[i-1] + v[i+1]))
    // ════════════════════════════════════════════════════════════════════════
    //
    // FORMULA: w[i] = 0.5 * (v[i-1] + v[i+1])  for i = 1 to n-2
    //
    // INPUT:  src = {10, 20, 30, 40, 50}  (n=5)
    // OUTPUT: dst = {0, 20, 30, 40, 0}    (endpoints=0)
    //
    // TRACE:
    //   i=1: dst[1] = 0.5 * (src[0] + src[2]) = 0.5 * (10 + 30) = 20
    //   i=2: dst[2] = 0.5 * (src[1] + src[3]) = 0.5 * (20 + 40) = 30
    //   i=3: dst[3] = 0.5 * (src[2] + src[4]) = 0.5 * (30 + 50) = 40
    //
    // HINT: for_each iterates indices [1, n-1), lambda captures &src and &dst

    std::vector<double> src = {10, 20, 30, 40, 50};
    std::vector<double> dst(src.size(), 0);

    // Index range [1, n-1) = {1, 2, 3}
    std::vector<size_t> indices(src.size() - 2);
    std::iota(indices.begin(), indices.end(), 1);

    std::ranges::for_each(indices, [&](size_t i) { dst[i] = 0.5 * (src[i - 1] + src[i + 1]); });

    std::cout << "Neighbor avg: {";
    for (size_t i = 0; i < dst.size(); ++i) std::cout << dst[i] << (i < dst.size() - 1 ? ", " : "");
    std::cout << "}\n";

    return 0;
}
