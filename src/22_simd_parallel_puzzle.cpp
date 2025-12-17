// Problem 22: SIMD Vectorization & Parallel Execution PUZZLE FILE
// Objective: Derive vectorization speedup, parallel overhead, verify false claims
// NO SOLUTIONS - ONLY DIAGRAMS AND TODO BLOCKS
// Compile: g++ -O3 -march=native -S -o 22.s src/22_simd_parallel_puzzle.cpp

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#ifdef HAS_TBB
#include <execution>  // For std::execution::par (C++17, requires TBB)
#endif

// ============================================================================
// PUZZLE 1: SIMD Register Capacity
// ============================================================================
//
// WHY THIS DIAGRAM: You claim to know SIMD but never counted the bytes.
//
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  ymm0 register (AVX/AVX2):                                              │
// │  ┌────┬────┬────┬────┬────┬────┬────┬────┐                              │
// │  │ d0 │ d1 │ d2 │ d3 │    │    │    │    │  ← 4 doubles (8 bytes each) │
// │  └────┴────┴────┴────┴────┴────┴────┴────┘                              │
// │  Total: 256 bits = 32 bytes                                             │
// │                                                                          │
// │  TODO: How many floats fit? _4__                                         │
// │  TODO: How many ints fit? ___4                                           │
// │  TODO: How many chars fit? ___32                                          │
// └─────────────────────────────────────────────────────────────────────────┘

void puzzle1_register_capacity() {
    // TODO: Calculate and verify
    std::cout << "sizeof(double) = " << sizeof(double) << " bytes\n";
    std::cout << "sizeof(float) = " << sizeof(float) << " bytes\n";
    std::cout << "sizeof(int) = " << sizeof(int) << " bytes\n";

    // TODO: 256 bits = __32_ bytes
    // TODO: __32_ bytes / 8 = __4_ doubles
    // TODO: __32_ bytes / 4 = __8_ floats
    // TODO: __32_ bytes / 4 = __8_ ints

    // FILL IN YOUR PREDICTIONS BEFORE UNCOMMENTING:
    // std::cout << "Doubles per ymm: " << 256/8/8 << "\n";
    // std::cout << "Floats per ymm: " << 256/8/4 << "\n";
}

// ============================================================================
// PUZZLE 2: Vectorization Speedup Calculation
// ============================================================================
//
// WHY THIS DIAGRAM: Real speedup ≠ theoretical speedup.
//
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  SCALAR (1 element/iteration):                                          │
// │  .L3:                                                                    │
// │    movsd xmm0, [rax]    ; 1 double                                      │
// │    mulsd xmm0, xmm1     ; 1 multiply                                    │
// │    movsd [rbx], xmm0    ; 1 store                                       │
// │    add rax, 8                                                            │
// │    add rbx, 8                                                            │
// │    cmp rax, rdx                                                          │
// │    jne .L3                                                               │
// │  Total: 7  instructions / 1 element = ___ instr/elem                       │
// │                                                                          │
// │  SIMD (4 elements/iteration):                                           │
// │  .L3:                                                                    │
// │    vmovupd ymm0, [rax]  ; 4 doubles                                     │
// │    vmulpd ymm0, ymm0, ymm1 ; 4 multiplies                               │
// │    vmovupd [rbx], ymm0  ; 4 stores                                      │
// │    add rax, 32                                                           │
// │    add rbx, 32                                                           │
// │    cmp rax, rdx                                                          │
// │    jne .L3                                                               │
// │  Total: 7 instructions / 4 elements = ___ instr/elem                    │
// │                                                                          │
// │  Speedup: 7 / ___ = ___x  ◀── TODO: CALCULATE                           │
// └─────────────────────────────────────────────────────────────────────────┘

void puzzle2_speedup_calculation() {
    const size_t N = 1000000;
    std::vector<double> v(N, 2.0);
    std::vector<double> w(N);

    // TODO: Predict speedup BEFORE measuring
    // Scalar: 7 instructions per element
    // SIMD: 7 instructions per 4 elements = _2__ per element
    // Theoretical speedup: ___x

    auto start = std::chrono::high_resolution_clock::now();
    std::transform(v.begin(), v.end(), w.begin(), [](double x) { return x * 2.0; });
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Transform time (N=" << N << "): " << duration.count() << " µs\n";

    // TODO: Calculate throughput
    // Throughput = N / duration = ___ million elements/second
}

// ============================================================================
//
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  YOUR MACHINE: AMD Ryzen 5 4600H                                        │
// │  L1d cache: 32 KB per core (192 KB total / 6 cores)                     │
// │  L2 cache: 512 KB per core (3 MB total / 6 cores)                       │
// │  L3 cache: 4 MB per CCX (8 MB total / 2 CCX)                            │
// │                                                                          │
// │  SIMD demand: 32 bytes load + 32 bytes store = 64 bytes/iteration      │
// │                                                                          │
// │  N = 1000 → data = 1000 × 8 × 2 = 16 KB → fits in L1d (32 KB) ✓        │
// │  N = 4000 → data = 4000 × 8 × 2 = 64 KB → exceeds L1d, hits L2 (512 KB)│
// │  N = 30000 → data = 30000 × 8 × 2 = 480 KB → still in L2 ✓            │
// │  N = 100000 → data = 100000 × 8 × 2 = 1.6 MB → exceeds L2, hits L3    │
// │  N = 1000000 → data = 1000000 × 8 × 2 = 16 MB → exceeds L3, hits RAM  │
// └─────────────────────────────────────────────────────────────────────────┘

void puzzle3_memory_crossover() {
    // Test different sizes around cache boundaries
    // L1d = 32KB → N = 2000 (16KB data)
    // L2 = 512KB → N = 32000 (512KB data)
    // L3 = 4MB → N = 250000 (4MB data)
    for (size_t N : {500UL, 1000UL, 2000UL, 4000UL, 8000UL, 16000UL, 32000UL, 64000UL, 128000UL,
                     256000UL, 512000UL, 1000000UL}) {
        std::vector<double> v(N, 2.0);
        std::vector<double> w(N);

        // Warm up cache
        std::transform(v.begin(), v.end(), w.begin(),
                       [](double x) { return std::sqrt(x) + std::sin(x); });

        auto start = std::chrono::high_resolution_clock::now();
        std::transform(v.begin(), v.end(), w.begin(),
                       [](double x) { return std::sqrt(x) + std::sin(x); });
        auto end = std::chrono::high_resolution_clock::now();

        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (us == 0) us = 1;  // Avoid division by zero
        double throughput = static_cast<double>(N) / static_cast<double>(us);
        size_t data_kb = N * 8 * 2 / 1024;

        std::cout << "N=" << N << " (" << data_kb << "KB): " << us << " µs, " << throughput
                  << " M elems/s\n";
    }

    // TODO: At which N does throughput drop significantly?
    // TODO: Calculate L1/L2/L3 boundaries from your measurements
}

// ============================================================================
// PUZZLE 4: Parallel Break-Even Point
// ============================================================================
//
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  Thread overhead: ~10,000 cycles                                        │
// │  Work per element: ~10 cycles                                           │
// │  Threads: 8                                                              │
// │                                                                          │
// │  Serial: N × 10 cycles                                                  │
// │  Parallel: (N × 10 ÷ 8) + 10,000 cycles                                │
// │                                                                          │
// │  Break-even: N × 10 = (N × 10 ÷ 8) + 10,000                            │
// │  Solve: N = ___                                                         │
// │                                                                          │
// │  For N < ___: Serial wins                                               │
// │  For N > ___: Parallel wins                                             │
// └─────────────────────────────────────────────────────────────────────────┘

void puzzle4_parallel_breakeven() {
    // Compare serial vs parallel for different N
    for (size_t N : {100UL, 1000UL, 10000UL, 100000UL}) {
        std::vector<double> v(N, 2.0);
        std::vector<double> w(N);

        // Serial
        auto start1 = std::chrono::high_resolution_clock::now();
        std::transform(v.begin(), v.end(), w.begin(), [](double x) { return x * 2.0; });
        auto end1 = std::chrono::high_resolution_clock::now();
        auto serial_us =
            std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count();

#ifdef HAS_TBB
        // Parallel (requires linking with TBB: -ltbb)
        auto start2 = std::chrono::high_resolution_clock::now();
        std::transform(std::execution::par, v.begin(), v.end(), w.begin(),
                       [](double x) { return x * 2.0; });
        auto end2 = std::chrono::high_resolution_clock::now();
        auto parallel_us =
            std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();

        std::cout << "N=" << N << ": Serial=" << serial_us << "µs, Parallel=" << parallel_us << "µs"
                  << " → " << (serial_us < parallel_us ? "Serial wins" : "Parallel wins") << "\n";
#else
        std::cout << "N=" << N << ": Serial=" << serial_us
                  << "µs (TBB not available for parallel)\n";
#endif
    }

    // TODO: What is the break-even N on your machine?
}

// ============================================================================
// PUZZLE 5: FALSE CLAIM VERIFICATION
// ============================================================================
//
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  CLAIM: "Algorithms parallelize automatically"                          │
// │                                                                          │
// │  TEST: Compile without execution policy, check for TBB calls           │
// │                                                                          │
// │  Command: g++ -O3 -S -o nopar.s src/22_simd_parallel_puzzle.cpp        │
// │  Command: grep "tbb" nopar.s                                            │
// │                                                                          │
// │  If NO TBB calls → NOT parallel → CLAIM IS FALSE                        │
// └─────────────────────────────────────────────────────────────────────────┘

void puzzle5_false_claim() {
    std::vector<double> v(10000, 2.0);
    std::vector<double> w(10000);

    // This transform: Does it parallelize automatically?
    // Compile with -S and check assembly
    std::transform(v.begin(), v.end(), w.begin(), [](double x) { return x * 2.0; });

    // TODO: Run these commands:
    // g++ -O3 -S -o nopar.s src/22_simd_parallel_puzzle.cpp
    // grep -c "call.*tbb" nopar.s
    // grep -c "lock" nopar.s
    // grep -c "pthread" nopar.s

    // If all return 0 → NO parallelization → Lecture is WRONG

    std::cout << "Check assembly: grep 'tbb' nopar.s\n";
    std::cout << "Expected: 0 matches (NO automatic parallelization)\n";
}

// ============================================================================
// PUZZLE 6: Alignment Verification
// ============================================================================
//
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  std::vector alignment: typically 16 bytes (not 32!)                    │
// │  AVX2 prefers: 32-byte alignment                                        │
// │  AVX-512 prefers: 64-byte alignment                                     │
// │                                                                          │
// │  Misaligned penalty: 4-8 cycles per split                               │
// └─────────────────────────────────────────────────────────────────────────┘

void puzzle6_alignment() {
    std::vector<double> v = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

    uintptr_t addr = reinterpret_cast<uintptr_t>(v.data());

    std::cout << "v.data() address: 0x" << std::hex << addr << std::dec << "\n";
    std::cout << "Aligned to 16? " << (addr % 16 == 0 ? "YES" : "NO") << "\n";
    std::cout << "Aligned to 32? " << (addr % 32 == 0 ? "YES" : "NO") << "\n";
    std::cout << "Aligned to 64? " << (addr % 64 == 0 ? "YES" : "NO") << "\n";

    // TODO: Is 32-byte alignment guaranteed?
    // TODO: What happens if not aligned?
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    std::cout << "=== Problem 22: SIMD & Parallel Execution ===\n\n";

    std::cout << "-- Puzzle 1: Register Capacity --\n";
    puzzle1_register_capacity();

    std::cout << "\n-- Puzzle 2: Speedup Calculation --\n";
    puzzle2_speedup_calculation();

    std::cout << "\n-- Puzzle 3: Memory Crossover --\n";
    puzzle3_memory_crossover();

    std::cout << "\n-- Puzzle 4: Parallel Break-Even --\n";
    puzzle4_parallel_breakeven();

    std::cout << "\n-- Puzzle 5: False Claim --\n";
    puzzle5_false_claim();

    std::cout << "\n-- Puzzle 6: Alignment --\n";
    puzzle6_alignment();

    return 0;
}
