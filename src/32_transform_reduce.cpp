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

    return 0;
}
