#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

// Trap 6 Helper: Check for vectorization (inspect assembly)
void manual_tiny_loop(int* data) {
    // 3 cycles ideally
    data[0] *= 2;
    data[1] *= 2;
    data[2] *= 2;
}

int main() {
    std::cout << "=== Problem 21: std::for_each Deep Dive ===\n";

    // Section 1: Mechanism
    // Range [0x1000, 0x1040) simulated
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};  // 32 bytes
    std::cout << "Vector start address: " << &v[0] << "\n";

    // "Hidden loop" revealed
    std::for_each(v.begin(), v.end(), [](int& x) {
        // Breakpoint here shows stack trace inside std::for_each
        x *= 2;
    });

    // Address 0x401240 simulation (Loop Header)
    // In assembly: look for 'cmp rsi, rdx' around here

    // Section 3: Traps - Tiny Range
    std::vector<int> tiny = {10, 20, 30};

    // std::for_each overhead test
    std::for_each(tiny.begin(), tiny.end(), [](int& x) { x += 1; });

    // Manual unroll comparison
    manual_tiny_loop(tiny.data());

    std::cout << "Tiny processed: " << tiny[0] << ", " << tiny[1] << "\n";

    return 0;
}
