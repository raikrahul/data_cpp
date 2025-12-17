// Problem 23: Lambda Anatomy Worksheet
// Objective: Trace lambda capture, type deduction, and memory layout
// NO SOLUTIONS - ONLY DIAGRAMS AND TODO BLOCKS

#include <cstdint>
#include <iostream>

int main() {
    std::cout << "=== Problem 23: Lambda Anatomy ===\n\n";

    // ════════════════════════════════════════════════════════════════════════
    // PUZZLE 1: Basic Lambda - What does auto deduce?
    // ════════════════════════════════════════════════════════════════════════
    //
    // LINE: auto f=[](int i){auto j=2*i;};
    //
    // ABI: x86-64, LP64, alignof(int)=4, sizeof(int)=4
    // Lambda type: empty capture = trivial struct with operator()
    //
    // ────────────────────────────────────────────────────────────────────────
    // EX-1: i=5, f@0x7ffd1000, call f(5)
    //   stack: [0x7ffd0fc0]=5 (i)
    //   j deduced=int, j@0x7ffd0fbc
    //   2*i = 2*5 = 10
    //   [0x7ffd0fbc] <- 10
    //   return void
    //   post: i=5, j=10 (discarded)
    //
    // EX-2: i=-3, f@0x7ffd2000, call f(-3)
    //   [0x7ffd1fc0] = -3
    //   2*(-3) = -6
    //   [0x7ffd1fbc] <- -6
    //
    // EX-3: i=0, call f(0)
    //   2*0 = 0
    //   [stack] <- 0
    //
    // EX-4: i=INT_MAX=2147483647, call f(2147483647)
    //   [stack] = 0x7fffffff
    //   2*i = 4294967294 (exceeds INT_MAX!)
    //   j deduced=int → overflow → j=-2 (2's complement wrap)
    //   [stack] <- 0xfffffffe
    //
    // EX-5: i=1073741824, 2*i=2147483648
    //   j=int → -2147483648 (signed overflow, UB!)
    //   [stack] <- 0x80000000
    //
    // EX-6: i=1, 2*i=2
    //   [stack] <- 2
    //
    // EX-7: i=65536, 2*i=131072
    //   [stack] <- 131072
    // ────────────────────────────────────────────────────────────────────────
    //
    // W (EX-1):
    //   What?   f(5) → j=10, return void
    //   Why?    auto deduces j=int (type of 2*int)
    //   Where?  i@stack, j@stack, f@stack (1 byte)
    //   Who?    lambda::operator()(int)
    //   When?   call sequence 1
    //   Without? j unused → optimized away (g++ -O2)
    //   Which?  lambda object @stack, sizeof=1
    //
    // ANN: auto j=2*i deduces j=int NOT double → overflow on 2*INT_MAX → -2
    // FAIL: i=1073741824 → j=-2147483648, signed overflow = UB
    //
    // TODO: What is return type of f? ___
    // TODO: What is type of j? ___
    // TODO: Does f return j? YES/NO ___
    // ════════════════════════════════════════════════════════════════════════

    auto f = [](int i) {
        auto j = 2 * i;
        (void)j;
    };

    std::cout << "sizeof(f) = " << sizeof(f) << " bytes\n";
    std::cout << "f(5) returns: (void)\n";
    f(5);  // Compiles, returns void, j is discarded

    // ════════════════════════════════════════════════════════════════════════
    // PUZZLE 2: Lambda with Return
    // ════════════════════════════════════════════════════════════════════════
    //
    // auto g = [](int i) { auto j = 2 * i; return j; };
    //                                      ↑
    //                              NOW returns j
    //
    // TODO: Return type of g? ___
    // TODO: g(5) = ???
    // ════════════════════════════════════════════════════════════════════════

    auto g = [](int i) {
        auto j = 2 * i;
        return j;
    };

    std::cout << "sizeof(g) = " << sizeof(g) << " bytes\n";
    std::cout << "g(5) = " << g(5) << "\n";

    // ════════════════════════════════════════════════════════════════════════
    // PUZZLE 3: Capture by Value
    // ════════════════════════════════════════════════════════════════════════
    //
    // int x = 10;
    // auto h = [x](int i) { return x + i; };
    //           ↑
    //       CAPTURED by value (copied)
    //
    // Memory layout of h:
    // ┌──────────────┐
    // │ x_copy = 10  │  ← 4 bytes (copy of x)
    // └──────────────┘
    //
    // TODO: sizeof(h) = ??? bytes
    // TODO: If x changes after capture, does h see new value? YES/NO ___
    // ════════════════════════════════════════════════════════════════════════

    int x = 10;
    auto h = [x](int i) { return x + i; };

    std::cout << "\nsizeof(h) = " << sizeof(h) << " bytes\n";
    std::cout << "h(5) = " << h(5) << "\n";

    x = 100;  // Change x after capture
    std::cout << "x changed to 100, h(5) = " << h(5) << " (still uses old x?)\n";

    // ════════════════════════════════════════════════════════════════════════
    // PUZZLE 4: Capture by Reference
    // ════════════════════════════════════════════════════════════════════════
    //
    // int y = 20;
    // auto k = [&y](int i) { return y + i; };
    //           ↑
    //       CAPTURED by reference (pointer)
    //
    // Memory layout of k:
    // ┌──────────────┐
    // │ y_ptr → y    │  ← 8 bytes (pointer to y)
    // └──────────────┘
    //
    // TODO: sizeof(k) = ??? bytes
    // TODO: If y changes after capture, does k see new value? YES/NO ___
    // ════════════════════════════════════════════════════════════════════════

    int y = 20;
    auto k = [&y](int i) { return y + i; };

    std::cout << "\nsizeof(k) = " << sizeof(k) << " bytes\n";
    std::cout << "k(5) = " << k(5) << "\n";

    y = 200;  // Change y after capture
    std::cout << "y changed to 200, k(5) = " << k(5) << " (sees new y?)\n";

    // ════════════════════════════════════════════════════════════════════════
    // PUZZLE 5: Mixed Capture
    // ════════════════════════════════════════════════════════════════════════
    //
    // int a = 1, b = 2;
    // auto m = [a, &b](int i) { return a + b + i; };
    //           ↑  ↑
    //           │  └── b by reference (8 bytes pointer)
    //           └── a by value (4 bytes copy)
    //
    // TODO: sizeof(m) = ??? bytes (hint: alignment padding)
    // ════════════════════════════════════════════════════════════════════════

    int a = 1, b = 2;
    auto m = [a, &b](int i) { return a + b + i; };

    std::cout << "\nsizeof(m) = " << sizeof(m) << " bytes\n";
    std::cout << "m(3) = " << m(3) << "\n";

    // ════════════════════════════════════════════════════════════════════════
    // PUZZLE 6: Lambda Address
    // ════════════════════════════════════════════════════════════════════════

    std::cout << "\nLambda addresses:\n";
    std::cout << "&f = " << reinterpret_cast<uintptr_t>(&f) << "\n";
    std::cout << "&g = " << reinterpret_cast<uintptr_t>(&g) << "\n";
    std::cout << "&h = " << reinterpret_cast<uintptr_t>(&h) << "\n";

    // TODO: Are these on stack or heap? ___

    return 0;
}
