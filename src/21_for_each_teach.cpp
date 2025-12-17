// Problem 21: std::for_each Teaching File
// Objective: Understand for_each mechanism, assembly output, and traps
// Compile: g++ -O2 -S -o 21_for_each.s 21_for_each_teach.cpp  (generates assembly)
// Compile: g++ -O0 -o 21_for_each_debug 21_for_each_teach.cpp (for debugging)
// Compile: g++ -O2 -o 21_for_each_fast 21_for_each_teach.cpp  (for benchmarking)

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

// ============================================================================
// SECTION 1: MECHANISM - std::for_each expands to this exact loop
// ============================================================================

// Step 1: This is what std::for_each(first, last, f) expands to internally
template <typename InputIt, typename UnaryFunction>
UnaryFunction my_for_each(InputIt first, InputIt last, UnaryFunction f) {
    // Expansion: for (; first != last; ++first) f(*first);
    // Address 0x401240 (example): cmp rsi, rdx  → compares first != last
    // Address 0x401244:           jne .L3       → jumps to loop body if not equal
    for (; first != last; ++first) {
        f(*first);  // Call f with dereferenced iterator
    }
    return f;  // for_each returns the function object (useful for stateful functors)
}

// Step 2: Examine what happens at -O2
// The compiler will:
//   - Inline 'f' if it's a lambda or small function
//   - Unroll the loop 4-8 times (process 4-8 elements per iteration)
//   - Emit: cmp, jne, mov, operation, inc (repeat pattern)

// ============================================================================
// SECTION 2: VISIBLE LOOP - The source hides it, assembly reveals it
// ============================================================================

// Function to multiply by 2 (simple enough to inline)
void multiply_by_2(int& x) { x *= 2; }

// Lambda version (more likely to inline)
[[maybe_unused]] auto lambda_mult_2 = [](int& x) { x *= 2; };

// Test function to see assembly
// Compile with: g++ -O2 -S -fno-inline -o section2.s 21_for_each_teach.cpp
// Look for: .L3: (loop label), cmp (comparison), jne (jump if not equal)
void section2_loop_visibility(std::vector<int>& v) {
    // "Source hides the loop" → You only see this one line
    std::for_each(v.begin(), v.end(), [](int& x) { x *= 2; });

    // "Assembly reveals it" → In section2.s you will see:
    // .LFB123:
    //   mov rax, rdi       # rax = v.begin()
    //   mov rdx, rsi       # rdx = v.end()
    // .L3:                 # Loop label
    //   cmp rax, rdx       # first != last?
    //   je .L1             # Exit if equal
    //   shl DWORD PTR [rax], 1  # x *= 2 (shift left = multiply by 2)
    //   add rax, 4         # ++first (move to next int, 4 bytes)
    //   jmp .L3            # Back to loop start
    // .L1:
    //   ret
}

// ============================================================================
// SECTION 3: IMPLICATIONS - Boilerplate reduction, but hardware cost remains
// ============================================================================

// Off-by-one bug prone code (manual loop)
void manual_loop_buggy(std::vector<int>& v) {
    // BUG: Using <= instead of < causes buffer overflow
    // for (size_t i = 0; i <= v.size(); ++i) { v[i] *= 2; }  // DON'T DO THIS

    // Correct manual version:
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] *= 2;
    }
}

// for_each version - no off-by-one possible
void for_each_safe(std::vector<int>& v) {
    // Cannot have off-by-one - iterator range is correct by construction
    std::for_each(v.begin(), v.end(), [](int& x) { x *= 2; });
}

// Branch prediction penalty demonstration
// Run with: perf stat ./21_for_each_fast
void branch_prediction_demo(std::vector<int>& v) {
    // The loop still has a branch: (first != last) → jne instruction
    // Branch Predictor Table entry at 0x401240 (example address)
    // Pattern: T, T, T, T, T, ... N (taken until final iteration)
    // Misprediction cost: ~15 cycles at loop exit
    std::for_each(v.begin(), v.end(), [](int& x) { x += 1; });
}

// ============================================================================
// SECTION 4: TRAPS - Tiny ranges and the "zero overhead" myth
// ============================================================================

// TRAP 1: for_each overhead for tiny arrays
// For N < 4 elements, hand-written code is faster

// Hand-written unrolled version for N=3 (FASTER for tiny)
void unrolled_3(int* data) {
    // 3 operations, 0 loop overhead
    // Assembly: 3 mov/add/shl instructions only
    data[0] *= 2;
    data[1] *= 2;
    data[2] *= 2;
}

// for_each version for N=3 (HAS OVERHEAD)
void for_each_3(int* data) {
    // Still has: compare, jump, increment instructions
    // Assembly: mov, cmp, jne, shl, add, jmp pattern
    int* end = data + 3;
    std::for_each(data, end, [](int& x) { x *= 2; });
}

// Benchmark to prove the overhead
void benchmark_tiny_range() {
    const int iterations = 10000000;
    int tiny[3] = {1, 2, 3};

    // Benchmark unrolled
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        unrolled_3(tiny);
        tiny[0] = 1;
        tiny[1] = 2;
        tiny[2] = 3;  // Reset
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    // Benchmark for_each
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        for_each_3(tiny);
        tiny[0] = 1;
        tiny[1] = 2;
        tiny[2] = 3;  // Reset
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    auto unrolled_time = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    auto for_each_time = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);

    std::cout << "=== TRAP: Tiny Range Overhead ===\n";
    std::cout << "Unrolled (N=3): " << unrolled_time.count() << " µs\n";
    std::cout << "for_each (N=3): " << for_each_time.count() << " µs\n";
    std::cout << "Overhead ratio: "
              << static_cast<double>(for_each_time.count()) /
                     static_cast<double>(unrolled_time.count())
              << "x\n";
}

// ============================================================================
// SECTION 5: HANDS-ON EXERCISES (TODO)
// ============================================================================

int main() {
    std::cout << "=== Problem 21: std::for_each Deep Dive ===\n\n";

    // EXERCISE 1: See the expansion
    std::cout << "-- Exercise 1: Manual expansion --\n";
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    my_for_each(v1.begin(), v1.end(), [](int& x) {
        std::cout << "Processing: " << x << " → ";
        x *= 2;
        std::cout << x << "\n";
    });

    // EXERCISE 2: Assembly visibility
    std::cout << "\n-- Exercise 2: Compile with -S to see assembly --\n";
    std::cout << "Run: g++ -O2 -S -o for_each.s src/21_for_each_teach.cpp\n";
    std::cout << "Look for: .L3, cmp, jne instructions in the .s file\n";
    std::vector<int> v2 = {10, 20, 30, 40};
    section2_loop_visibility(v2);
    std::cout << "v2 after for_each: ";
    for (int x : v2) std::cout << x << " ";
    std::cout << "\n";

    // EXERCISE 3: Branch prediction
    std::cout << "\n-- Exercise 3: Branch prediction cost --\n";
    std::cout << "Run: perf stat -e branch-misses ./21_for_each_fast\n";
    std::vector<int> v3(1000, 1);
    branch_prediction_demo(v3);
    std::cout << "Branch misprediction at loop exit: ~15 cycles penalty\n";

    // EXERCISE 4: Tiny range benchmark
    std::cout << "\n-- Exercise 4: Tiny range trap --\n";
    benchmark_tiny_range();

    // EXERCISE 5: Address printing (verify addresses)
    std::cout << "\n-- Exercise 5: Address verification --\n";
    std::vector<int> v5 = {100, 200, 300};
    std::cout << "v5 data address: " << v5.data() << "\n";
    std::cout << "v5.begin() addr: " << &(*v5.begin()) << "\n";
    std::cout << "v5.end() addr:   " << &(*v5.end()) << " (past-the-end, don't dereference)\n";

    // TODO EXERCISES (for the learner):
    std::cout << "\n=== TODO Exercises ===\n";
    std::cout << "1. Compile with -S and find the loop label in assembly\n";
    std::cout << "2. Add -funroll-loops and observe the unrolled pattern\n";
    std::cout << "3. Compare perf stat for for_each vs manual loop\n";
    std::cout << "4. Modify benchmark_tiny_range() for N=1, N=2, N=8, N=16\n";
    std::cout << "5. Use -fno-inline to see the function call overhead\n";

    return 0;
}
