#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <cstdint>

// 38_functor_vs_lambda.cpp
// Worksheet: Counter functor with operator(), memory layout, register passing, copy semantics

struct counter {
    int count{};
    int operator()(int increment) { return count += increment; }
};

void test_basic_calls() {
    std::cout << "=== TEST 1: Basic Calls ===\n";
    // TODO: counter c1{0};
    // TODO: int r0 = c1.count; // r0 = 0
    // TODO: int r1 = c1(1);    // r1 = 1, c1.count = 1
    // TODO: int r2 = c1(2);    // r2 = 3, c1.count = 3
    // TODO: int r3 = c1(3);    // r3 = 6, c1.count = 6
    // TODO: Verify: 0+1=1, 1+2=3, 3+3=6 ✓
    // TODO: Print addresses and values
    
    counter c1{0};
    std::cout << "&c1 = " << static_cast<const void*>(&c1) << "\n";
    std::cout << "sizeof(counter) = " << sizeof(counter) << " (expected: 4)\n";
    std::cout << "alignof(counter) = " << alignof(counter) << " (expected: 4)\n";
    
    int r0 = c1.count;
    std::cout << "r0 = c1.count = " << r0 << " (expected: 0)\n";
    
    int r1 = c1(1);
    std::cout << "r1 = c1(1) = " << r1 << " (expected: 1), c1.count = " << c1.count << "\n";
    
    int r2 = c1(2);
    std::cout << "r2 = c1(2) = " << r2 << " (expected: 3), c1.count = " << c1.count << "\n";
    
    int r3 = c1(3);
    std::cout << "r3 = c1(3) = " << r3 << " (expected: 6), c1.count = " << c1.count << "\n";
}

void test_initial_value() {
    std::cout << "\n=== TEST 2: Initial Value 10 ===\n";
    // Worksheet lines 007-020
    counter myCounter{10};
    std::cout << "&myCounter = " << static_cast<const void*>(&myCounter) << "\n";
    std::cout << "Initial count = " << myCounter.count << " (expected: 10)\n";
    
    int tick = myCounter(1);
    std::cout << "tick = myCounter(1) = " << tick << " (expected: 11)\n";
    std::cout << "myCounter.count = " << myCounter.count << " (expected: 11)\n";
    
    // Second call (lines 021-026)
    int r2 = myCounter(1);
    std::cout << "r2 = myCounter(1) = " << r2 << " (expected: 12)\n";
    
    // More calls (lines 027-030)
    myCounter(3); // count = 15
    myCounter(5); // count = 20
    myCounter(2); // count = 22
    std::cout << "After calls (1,3,5,2): count = " << myCounter.count << " (expected: 22)\n";
    std::cout << "Sum check: 10 + (1+1+3+5+2) = 10 + 12 = 22 ✓\n";
}

void test_copy_semantics() {
    std::cout << "\n=== TEST 3: Copy Semantics ===\n";
    // Worksheet lines 036-037
    counter myCounter{22};
    counter copy = myCounter;
    
    std::cout << "&myCounter = " << static_cast<const void*>(&myCounter) << "\n";
    std::cout << "&copy = " << static_cast<const void*>(&copy) << "\n";
    std::cout << "copy.count = " << copy.count << " (expected: 22)\n";
    
    copy(1);
    std::cout << "After copy(1): copy.count = " << copy.count << " (expected: 23)\n";
    std::cout << "myCounter.count = " << myCounter.count << " (expected: 22, unchanged)\n";
}

void test_lambda_equivalent() {
    std::cout << "\n=== TEST 4: Lambda Equivalent ===\n";
    // Worksheet lines 046-048
    auto lambda = [count = 10](int inc) mutable { return count += inc; };
    
    std::cout << "sizeof(lambda) = " << sizeof(lambda) << " (expected: 4)\n";
    std::cout << "&lambda = " << static_cast<const void*>(&lambda) << "\n";
    
    int l1 = lambda(1);
    std::cout << "lambda(1) = " << l1 << " (expected: 11)\n";
    
    int l2 = lambda(1);
    std::cout << "lambda(1) = " << l2 << " (expected: 12)\n";
    
    auto lambda2 = lambda;
    int l3 = lambda2(1);
    std::cout << "lambda2(1) = " << l3 << " (expected: 13, independent copy)\n";
    std::cout << "lambda(0) = " << lambda(0) << " (expected: 12, original unchanged by copy)\n";
}

void test_edge_cases() {
    std::cout << "\n=== TEST 5: Edge Cases ===\n";
    // Line 033: N=0 calls
    counter c0{10};
    std::cout << "N=0 calls: c0.count = " << c0.count << " (expected: 10)\n";
    
    // Line 034: N=1 call with increment=100
    counter c1{10};
    c1(100);
    std::cout << "N=1, inc=100: c1.count = " << c1.count << " (expected: 110)\n";
    
    // Line 065: Operator precedence
    counter c2{22};
    int result = c2(1) + 2;
    std::cout << "c2(1) + 2 = " << result << " (expected: 25, since c2(1)=23, 23+2=25)\n";
    
    // Line 066: Chaining
    counter c3{22};
    int chained = c3(c3(1));
    std::cout << "c3(c3(1)) = " << chained << " (expected: 46, inner=23, outer=23+23=46)\n";
}

void test_memory_layout() {
    std::cout << "\n=== TEST 6: Memory Layout ===\n";
    counter c{10};
    
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&c);
    std::cout << "Memory at &c: ";
    for (size_t i = 0; i < sizeof(counter); ++i) {
        printf("%02x ", bytes[i]);
    }
    std::cout << "(expected: 0a 00 00 00)\n";
    
    c(1); // count = 11
    std::cout << "After c(1): ";
    for (size_t i = 0; i < sizeof(counter); ++i) {
        printf("%02x ", bytes[i]);
    }
    std::cout << "(expected: 0b 00 00 00)\n";
}

int main() {
    std::cout << "=== 38_functor_vs_lambda ===\n\n";
    
    test_basic_calls();
    test_initial_value();
    test_copy_semantics();
    test_lambda_equivalent();
    test_edge_cases();
    test_memory_layout();
    
    std::cout << "\n=== PREDICTED FAILURES ===\n";
    std::cout << "F1: Race condition on concurrent calls → lost updates ✗\n";
    std::cout << "F2: Overflow with INT_MAX+1 → wraparound to -2147483648 ✗\n";
    std::cout << "F3: Narrowing conversion from float 1.9f → truncated to 1 ✗\n";
    std::cout << "F5: Lambda without 'mutable' → cannot modify capture ✗\n";
    std::cout << "F6: std::function overhead → 10× slowdown ✗\n";
    
    return 0;
}
