#include <iostream>
#include <vector>
#include <chrono>

int main() {
    std::cout << "=== WHY CARE ABOUT && ? ===\n\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 1: Create large data (10 million ints = 40 MB)
    // ════════════════════════════════════════════════════════════════════════════
    std::vector<int> data(10'000'000, 42);
    size_t mb = data.size() * sizeof(int) / 1'000'000;
    std::cout << "Created vector: " << mb << " MB (" << data.size() << " ints)\n\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 2: WITHOUT && (COPY)
    // ════════════════════════════════════════════════════════════════════════════
    // Operation: std::vector<int> copy = data;
    // What happens:
    //   1. Allocate new 40MB on heap
    //   2. Copy 10 million ints (40MB memcpy)
    //   3. Result: TWO 40MB blocks (80MB total)
    
    std::cout << "=== TEST 1: WITHOUT && (COPY) ===\n";
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> copy = data;  // COPY 40MB
    
    auto end = std::chrono::high_resolution_clock::now();
    auto copy_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "Time:   " << copy_us << " microseconds\n";
    std::cout << "Memory: " << mb << " MB (original) + " << mb << " MB (copy) = " << mb*2 << " MB\n";
    std::cout << "Work:   Allocate " << mb << "MB + memcpy " << mb << "MB\n\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 3: WITH && (MOVE)
    // ════════════════════════════════════════════════════════════════════════════
    // Operation: std::vector<int> moved = std::move(copy);
    // What happens:
    //   1. Copy 3 pointers (24 bytes: data*, size, capacity)
    //   2. Set source to nullptr
    //   3. Result: ONE 40MB block only
    
    std::cout << "=== TEST 2: WITH && (MOVE) ===\n";
    start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> moved = std::move(copy);  // MOVE (steal pointer)
    
    end = std::chrono::high_resolution_clock::now();
    auto move_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "Time:   " << move_us << " microseconds\n";
    std::cout << "Memory: " << mb << " MB only (no duplicate)\n";
    std::cout << "Work:   Copy 24 bytes (3 pointers)\n\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 4: NUMBERS
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "=== COMPARISON (NUMBERS) ===\n";
    std::cout << "Copy: " << copy_us << " us, " << mb*2 << " MB, " << mb << " MB work\n";
    std::cout << "Move: " << move_us << " us, " << mb << " MB, 24 bytes work\n\n";
    
    if (move_us > 0) {
        std::cout << "Speed:  " << (double)copy_us / move_us << "x faster with &&\n";
    } else {
        std::cout << "Speed:  Move too fast to measure (< 1 us)\n";
    }
    std::cout << "Memory: " << mb << " MB saved with && (-50%)\n";
    std::cout << "Data:   " << mb * 1'000'000 / 24 << "x less data moved\n\n";
    
    // ════════════════════════════════════════════════════════════════════════════
    // STEP 5: WHEN TO CARE
    // ════════════════════════════════════════════════════════════════════════════
    std::cout << "=== WHEN TO USE && ===\n";
    std::cout << "1. Returning large objects from functions\n";
    std::cout << "2. Inserting into containers (vector, map, etc.)\n";
    std::cout << "3. Transferring ownership (unique_ptr)\n";
    std::cout << "4. Avoiding unnecessary copies\n\n";
    
    std::cout << "=== REAL-WORLD IMPACT ===\n";
    std::cout << "Small data (10 ints = 40 bytes):\n";
    std::cout << "  Copy: ~1 us, Move: ~1 us → No difference\n\n";
    std::cout << "Medium data (1000 ints = 4 KB):\n";
    std::cout << "  Copy: ~10 us, Move: ~1 us → 10x faster\n\n";
    std::cout << "Large data (10M ints = 40 MB):\n";
    std::cout << "  Copy: " << copy_us << " us, Move: " << move_us << " us → " 
              << (move_us > 0 ? std::to_string((int)(copy_us/move_us)) : ">1000") << "x faster\n\n";
    
    std::cout << "CONCLUSION: && matters for LARGE data or FREQUENT operations\n";
    
    return 0;
}
