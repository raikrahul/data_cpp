#include <iostream>
#include <numeric>
#include <vector>

// ============================================================================
// my_plus: Custom implementation of std::plus
// ============================================================================

// Primary template: forward declaration with default parameter = void
template <typename T = void>
struct my_plus;

// Partial specialization for non-void types: works for single type T
template <typename T>
struct my_plus {
    // T = int → operator()(const int&, const int&) → return int
    // T = double → operator()(const double&, const double&) → return double
    // Both parameters must be same type T
    //
    // MEMORY LAYOUT (for T=int):
    // sizeof(my_plus<int>) = 1 byte (empty struct)
    // Stack at 0x7fff0000: my_plus<int> p (1 byte)
    //
    // CALL: p(5, 10)
    // Stack frame:
    // ┌─────────────────────────────────────────────────────────────┐
    // │ 0x7fff0000: p (1 byte)                                      │
    // │ 0x7fff0001: temporary 5 (4 bytes)                           │
    // │ 0x7fff0005: temporary 10 (4 bytes)                          │
    // │ 0x7fff0009: a = const int& → 0x7fff0001                     │
    // │ 0x7fff0011: b = const int& → 0x7fff0005                     │
    // │ 0x7fff0019: return value = 15 (4 bytes)                     │
    // └─────────────────────────────────────────────────────────────┘
    //
    // What: adds two values of same type T
    // Why: type-safe addition, both args must match
    // Where: stack 0x7fff0000
    // Who: user instantiates with T=int, T=double, etc.
    // When: T=int → 5+10=15, T=double → 5.5+10.5=16.0
    // Without: would need separate function for each type
    // Which: uses primary template, not specialization

    T operator()(const T& a, const T& b) const { return a + b; }
};

// Full specialization: my_plus<void> with type deduction
template <>
struct my_plus<void> {
    // operator() is a template → deduces _Tp and _Up from arguments
    // _Tp = type of first argument (deduced at call site)
    // _Up = type of second argument (deduced at call site)
    //
    // EXAMPLE 1: my_plus<>()(5, 10)
    // _Tp = int (from 5)
    // _Up = int (from 10)
    // Instantiated: auto operator()(int&& a, int&& b) const → int
    // Execution: return 5 + 10 = 15
    //
    // EXAMPLE 2: my_plus<>()(5, 10.5)
    // _Tp = int (from 5)
    // _Up = double (from 10.5)
    // Instantiated: auto operator()(int&& a, double&& b) const → double
    // Execution: return 5 + 10.5 = 15.5
    // Type promotion: int + double → double
    //
    // EXAMPLE 3: my_plus<>()(3.14, 2.86)
    // _Tp = double (from 3.14)
    // _Up = double (from 2.86)
    // Instantiated: auto operator()(double&& a, double&& b) const → double
    // Execution: return 3.14 + 2.86 = 6.0
    //
    // MEMORY LAYOUT (call site):
    // sizeof(my_plus<void>) = 1 byte (empty struct)
    // Stack at 0x7fff0100:
    // ┌─────────────────────────────────────────────────────────────┐
    // │ 0x7fff0100: my_plus<void> p (1 byte)                        │
    // │ 0x7fff0101: arg1 = 5 (4 bytes, int)                         │
    // │ 0x7fff0105: arg2 = 10.5 (8 bytes, double)                   │
    // │ 0x7fff010d: a = int&& → rvalue ref to 0x7fff0101            │
    // │ 0x7fff0115: b = double&& → rvalue ref to 0x7fff0105         │
    // │ 0x7fff011d: return value = 15.5 (8 bytes, double)           │
    // └─────────────────────────────────────────────────────────────┘
    //
    // FORWARDING REFERENCE (_Tp&&):
    // int x = 5; my_plus<>()(x, 10) → _Tp = int& (lvalue)
    //                                → _Tp&& = int& && → int& (collapse)
    // my_plus<>()(5, 10) → _Tp = int (rvalue)
    //                    → _Tp&& = int&& (rvalue reference)
    //
    // TYPE DEDUCTION EXAMPLES:
    // Call                    | _Tp      | _Up      | Return Type
    // ----------------------- | -------- | -------- | -----------
    // my_plus<>()(1, 2)       | int      | int      | int
    // my_plus<>()(1, 2.0)     | int      | double   | double
    // my_plus<>()(1.5, 2.5)   | double   | double   | double
    // my_plus<>()(1L, 2)      | long     | int      | long
    // my_plus<>()(1, 2L)      | int      | long     | long
    //
    // COMPILE-TIME vs RUNTIME:
    // Template deduction → compile-time (_Tp, _Up determined)
    // Addition operation → runtime (5 + 10.5 computed)
    // Return type deduction → compile-time (decltype(int + double) = double)
    //
    // What: adds two values of potentially different types
    // Why: flexible addition, no type restriction, auto type deduction
    // Where: stack 0x7fff0100
    // Who: compiler deduces _Tp and _Up from call arguments
    // When: (5, 10.5) → _Tp=int, _Up=double → 15.5
    // Without: would need my_plus<int> and explicit type conversion
    // Which: uses void specialization, not primary template

    template <typename _Tp, typename _Up>
    auto operator()(_Tp&& a, _Up&& b) const
        -> decltype(static_cast<_Tp&&>(a) + static_cast<_Up&&>(b)) {
        return static_cast<_Tp&&>(a) + static_cast<_Up&&>(b);
    }
};

// ============================================================================
// my_reduce: Custom implementation of std::reduce
// ============================================================================

// Step 1: Implement my_reduce with all parameters
template <typename InputIt, typename T, typename BinaryOp>
T my_reduce(InputIt first, InputIt last, T init, BinaryOp binary_op) {
    // InputIt = vector<int>::iterator → 8 bytes ptr at stack 0x7fff0000
    // T = int → 4 bytes at stack 0x7fff0008
    // BinaryOp = std::plus<> → empty functor, sizeof=1, at stack 0x7fff000c
    // first = 0x600000 → points to v[0]=1
    // last = 0x600010 → points to v[4]=5 (NOT included, end()-1)
    // init = 0 → accumulator starts at 0
    //
    // MID SCALE: N=4 elements {1,2,3,4}
    // Iteration 0: first=0x600000 → *first=1 → init=binary_op(0,1)=0+1=1 → ++first=0x600004
    // Iteration 1: first=0x600004 → *first=2 → init=binary_op(1,2)=1+2=3 → ++first=0x600008
    // Iteration 2: first=0x600008 → *first=3 → init=binary_op(3,3)=3+3=6 → ++first=0x60000c
    // Iteration 3: first=0x60000c → *first=4 → init=binary_op(6,4)=6+4=10 → ++first=0x600010
    // Iteration 4: first=0x600010 == last → exit loop → return 10
    //
    // LARGE SCALE: N=1000000 elements, each int=4 bytes → 4MB array
    // Iterations = 1000000 → each: 1 deref + 1 add + 1 assign + 1 increment = 4 ops
    // Total ops = 1000000×4 = 4000000 ops → at 1ns/op = 4ms
    // Memory accesses = 1000000 reads → cache line = 64 bytes = 16 ints
    // Cache misses = 1000000/16 = 62500 misses → at 100ns/miss = 6.25ms
    // Total time ≈ 4ms + 6.25ms = 10.25ms
    //
    // SMALL SCALE: N=1 element {5}
    // Iteration 0: first=0x600000 → *first=5 → init=binary_op(0,5)=0+5=5 → ++first=0x600004
    // Iteration 1: first=0x600004 == last → exit → return 5
    //
    // EDGE CASE: N=0 (empty range)
    // first == last immediately → loop body never executes → return init=0
    //
    // FRACTIONAL: N=7 elements {1,2,3,4,5,6,7}, init=10
    // Iteration 0: init=10+1=11
    // Iteration 1: init=11+2=13
    // Iteration 2: init=13+3=16
    // Iteration 3: init=16+4=20 → middle calculation (N/2=3.5, round down=3)
    // Iteration 4: init=20+5=25
    // Iteration 5: init=25+6=31
    // Iteration 6: init=31+7=38 → return 38
    //
    // MEMORY LAYOUT (stack frame at 0x7fff0000):
    // ┌─────────────────────────────────────────────────────────────┐
    // │ 0x7fff0000: first (8 bytes) = 0x600000 → heap array        │
    // │ 0x7fff0008: last (8 bytes) = 0x600010                      │
    // │ 0x7fff0010: init (4 bytes) = 0 → 1 → 3 → 6 → 10 (mutates) │
    // │ 0x7fff0014: binary_op (1 byte) = std::plus<> (empty)       │
    // │ 0x7fff0015: (3 bytes padding for alignment)                │
    // └─────────────────────────────────────────────────────────────┘
    // Total stack frame = 24 bytes (8+8+4+1+3)
    //
    // HEAP LAYOUT (vector data at 0x600000):
    // ┌─────────────────────────────────────────────────────────────┐
    // │ 0x600000: v[0] = 1 (4 bytes)                                │
    // │ 0x600004: v[1] = 2 (4 bytes)                                │
    // │ 0x600008: v[2] = 3 (4 bytes)                                │
    // │ 0x60000c: v[3] = 4 (4 bytes)                                │
    // │ 0x600010: v[4] = 5 (4 bytes) ← last points here (excluded) │
    // └─────────────────────────────────────────────────────────────┘
    //
    // What: accumulates elements using binary_op, N=4 → 4 iterations → result=10
    // Why: reduce N elements to 1 value, O(N) time, O(1) space
    // Where: stack frame 0x7fff0000, heap array 0x600000
    // Who: caller provides first=0x600000, last=0x600010, init=0, binary_op=std::plus<>
    // When: each iteration: t=0→init=1, t=1→init=3, t=2→init=6, t=3→init=10
    // Without: if N=0 → return init=0 unchanged, no iterations
    // Which: processes elements at indices {0,1,2,3}, skips index 4

    for (; first != last; ++first) {
        init = binary_op(init, *first);
    }
    return init;
}

// Step 2: Overload with default binary_op = std::plus<>
template <typename InputIt, typename T>
T my_reduce(InputIt first, InputIt last, T init) {
    // InputIt = vector<int>::iterator → 8 bytes at stack 0x7fff0100
    // T = int → 4 bytes at stack 0x7fff0108
    // init = 0 → passed by value, copied to stack
    // first = 0x600000, last = 0x600010
    //
    // DELEGATION: calls my_reduce(first, last, init, std::plus<>())
    // std::plus<> = empty functor → sizeof=1 → created on stack at 0x7fff010c
    // Compiler inlines this call → no actual function call overhead
    // Stack frame before delegation:
    // ┌─────────────────────────────────────────────────────────────┐
    // │ 0x7fff0100: first (8 bytes) = 0x600000                      │
    // │ 0x7fff0108: last (8 bytes) = 0x600010                       │
    // │ 0x7fff0110: init (4 bytes) = 0                              │
    // │ 0x7fff0114: (4 bytes padding)                               │
    // └─────────────────────────────────────────────────────────────┘
    // Total = 24 bytes
    //
    // After delegation (tail call optimization):
    // Stack frame reused → no additional 24 bytes allocated
    // std::plus<>() constructed in-place → 1 byte at 0x7fff0118
    //
    // MID SCALE: N=4 → delegates to overload 1 → 4 iterations → result=10
    // LARGE SCALE: N=1000000 → delegates → 1000000 iterations → 10.25ms
    // SMALL SCALE: N=1 → delegates → 1 iteration → result=5
    // EDGE CASE: N=0 → delegates → 0 iterations → return init=0
    //
    // What: delegates to 4-parameter overload, N=4 → result=10
    // Why: provides default binary_op=std::plus<>, reduces caller burden
    // Where: stack 0x7fff0100, delegates to stack 0x7fff0000
    // Who: caller provides first, last, init → this function adds std::plus<>
    // When: delegation happens immediately, no computation here
    // Without: caller would need to write std::plus<>() explicitly
    // Which: uses overload 1 for actual computation

    return my_reduce(first, last, init, std::plus<>());
}

// Step 3: Overload with default init = T{}
template <typename InputIt>
typename std::iterator_traits<InputIt>::value_type my_reduce(InputIt first, InputIt last) {
    // InputIt = vector<int>::iterator → 8 bytes at stack 0x7fff0200
    // first = 0x600000, last = 0x600010
    //
    // TYPE DEDUCTION via std::iterator_traits:
    // std::iterator_traits<vector<int>::iterator>::value_type = int
    // Return type = int (deduced at compile time, not runtime)
    //
    // using T = typename std::iterator_traits<InputIt>::value_type;
    // T = int → sizeof(int) = 4 bytes
    // T{} = int{} = 0 → default initialization → value = 0
    //
    // DELEGATION CHAIN:
    // my_reduce(first, last)
    //     ↓ calls
    // my_reduce(first, last, T{}, std::plus<>())
    //     ↓ T{} = int{} = 0
    // my_reduce(first, last, 0, std::plus<>())
    //     ↓ delegates to overload 1
    // for loop with 4 iterations → result = 10
    //
    // STACK LAYOUT (before delegation):
    // ┌─────────────────────────────────────────────────────────────┐
    // │ 0x7fff0200: first (8 bytes) = 0x600000                      │
    // │ 0x7fff0208: last (8 bytes) = 0x600010                       │
    // │ 0x7fff0210: T{} temporary (4 bytes) = 0                     │
    // │ 0x7fff0214: std::plus<> temporary (1 byte)                  │
    // │ 0x7fff0215: (3 bytes padding)                               │
    // └─────────────────────────────────────────────────────────────┘
    // Total = 24 bytes
    //
    // MID SCALE: N=4 elements {1,2,3,4}
    // T{} = 0 → delegates with init=0 → result = 0+1+2+3+4 = 10
    //
    // LARGE SCALE: N=1048576 (2^20) elements
    // T{} = 0 → delegates → 1048576 iterations
    // Each iteration: 4 ops → total = 1048576×4 = 4194304 ops
    // At 1ns/op → 4.194ms
    // Cache: 1048576 ints × 4 bytes = 4MB
    // Cache lines = 4MB / 64 bytes = 65536 lines
    // L3 cache = 8MB → fits in cache → minimal misses
    // Total time ≈ 4.194ms + (65536×10ns) = 4.85ms
    //
    // SMALL SCALE: N=1 element {42}
    // T{} = 0 → delegates → 1 iteration → result = 0+42 = 42
    //
    // EDGE CASE: N=0 (empty)
    // T{} = 0 → delegates → 0 iterations → return 0
    //
    // FRACTIONAL: N=3 elements {10,20,30}
    // Middle index = 3/2 = 1 (integer division)
    // Iteration 0: init=0+10=10
    // Iteration 1: init=10+20=30 ← middle
    // Iteration 2: init=30+30=60 → return 60
    //
    // TYPE DEDUCTION EXAMPLES:
    // vector<int>::iterator → value_type = int → T{} = 0
    // vector<double>::iterator → value_type = double → T{} = 0.0
    // list<string>::iterator → value_type = string → T{} = "" (empty string)
    // array<float,5>::iterator → value_type = float → T{} = 0.0f
    //
    // COMPILE-TIME COMPUTATION:
    // sizeof(std::iterator_traits<InputIt>) = 1 (empty struct)
    // sizeof(std::iterator_traits<InputIt>::value_type) = 4 (int)
    // alignof(T) = 4 → stack alignment requirement
    //
    // What: deduces T from iterator, creates T{}=0, delegates → N=4 → result=10
    // Why: caller provides only iterators, no init value needed
    // Where: stack 0x7fff0200, T{} at 0x7fff0210
    // Who: std::iterator_traits extracts value_type=int from InputIt
    // When: T{} constructed at line 123, passed to overload at line 124
    // Without: caller would need to write my_reduce(first, last, 0)
    // Which: uses iterator_traits for type deduction, delegates to overload 2

    using T = typename std::iterator_traits<InputIt>::value_type;
    return my_reduce(first, last, T{}, std::plus<>());
}

int main() {
    auto v = std::vector<int>{1, 2, 3, 4, 5};

    std::cout << "=== Testing my_plus ===\n\n";

    // Test 1: Primary template my_plus<int>
    my_plus<int> p1;
    std::cout << "Test 1: my_plus<int>()(5, 10) = " << p1(5, 10) << "\n";

    // Test 2: Primary template my_plus<double>
    my_plus<double> p2;
    std::cout << "Test 2: my_plus<double>()(3.14, 2.86) = " << p2(3.14, 2.86) << "\n";

    // Test 3: Specialization my_plus<void> with same types
    my_plus<> p3;  // <> = <void>
    std::cout << "Test 3: my_plus<>()(5, 10) = " << p3(5, 10) << "\n";

    // Test 4: Specialization my_plus<void> with different types
    std::cout << "Test 4: my_plus<>()(5, 10.5) = " << p3(5, 10.5) << "\n";

    // Test 5: Specialization my_plus<void> with doubles
    std::cout << "Test 5: my_plus<>()(3.14, 2.86) = " << p3(3.14, 2.86) << "\n";

    std::cout << "\n=== Testing my_reduce ===\n\n";

    // Test 6: my_reduce with my_plus<>
    auto s1 = my_reduce(v.begin(), v.end() - 1, 0, my_plus<>());
    std::cout << "Test 6: my_reduce(begin, end-1, 0, my_plus<>()) = " << s1 << "\n";

    // Test 7: my_reduce with std::plus<>
    auto s2 = my_reduce(v.begin(), v.end() - 1, 0, std::plus<>());
    std::cout << "Test 7: my_reduce(begin, end-1, 0, std::plus<>()) = " << s2 << "\n";

    // Test 8: my_reduce with default binary_op
    auto s3 = my_reduce(v.begin(), v.end() - 1, 0);
    std::cout << "Test 8: my_reduce(begin, end-1, 0) = " << s3 << "\n";

    // Test 9: my_reduce with default init and binary_op
    auto s4 = my_reduce(v.begin(), v.end() - 1);
    std::cout << "Test 9: my_reduce(begin, end-1) = " << s4 << "\n";

    // Test 10: Compare with std::reduce
    auto s5 = std::reduce(v.begin(), v.end() - 1);
    std::cout << "Test 10: std::reduce(begin, end-1) = " << s5 << "\n";

    std::cout << "\nExpected: 1 + 2 + 3 + 4 = 10\n";

    return 0;
}
