#include <iostream>
#include <vector>
#include <array>
#include <type_traits>

// =============================================================================
// 48 Abbreviated Template Syntax
// =============================================================================
//
// MEMORY LAYOUT 0x1000 (template infrastructure):
// ┌──────────────────────────────────────────────────────────────────────────────┐
// │ 0x1000: [0x4000] → template<T> iPow<int> address                             │
// │ 0x1008: [0x4010] → auto iPow → iPow<float> address                           │
// │ 0x1010: [0x4020] → auto iPow → iPow<double> address                          │
// │ 0x1018: [0x00000003] → template parameter n=3                                │
// │ 0x1020: [0x00000002] → base=2                                                │
// │                                                                              │
// │ .text segment 0x4000-0x408F: 3 instantiations × 48 bytes = 144 bytes         │
// │ .rodata 0x6000-0x6020: constants 1.0, 1.0f, 1 for result initialization      │
// │                                                                              │
// │ vs macro __IPOW at 0x5000 = 32 bytes (1 expansion)                           │
// │ Template code bloat = 144 - 32 = 112 bytes extra                             │
// └──────────────────────────────────────────────────────────────────────────────┘
//
// NUMERICAL EXAMPLE 1: iPow<int>(2,3) vs auto iPow(2,3)
// ┌──────────────────────────────────────────────────────────────────────────────┐
// │ template<T> iPow(2,3) → 0x4000:                                              │
// │   iter₀: result=1×2=2 (1 cycle imul)                                         │
// │   iter₁: result=2×2=4 (1 cycle imul)                                         │
// │   iter₂: result=4×2=8 (1 cycle imul)                                         │
// │   Total: 3 cycles, result=8                                                  │
// │                                                                              │
// │ auto iPow(2,3) → 0x4000 (SAME address! same instantiation):                  │
// │   iter₀-iter₂: identical machine code                                        │
// │   Total: 3 cycles, result=8                                                  │
// │                                                                              │
// │ Instruction count: template=12 bytes, auto=12 bytes → size diff=0 bytes      │
// │ ∴ abbreviated syntax = syntactic sugar only, no runtime difference           │
// └──────────────────────────────────────────────────────────────────────────────┘
//
// COMPILE TIME ANALYSIS:
// ┌──────────────────────────────────────────────────────────────────────────────┐
// │ Parse time: 0.3s for template<typename T> header                             │
// │ Instantiation time: 0.1s per type                                            │
// │ 3 types (int, float, double) × 0.1s = 0.3s instantiation                     │
// │ Total compile: 0.6s for 3 types                                              │
// │                                                                              │
// │ Full syntax:        template<class T> T iPow(T x, int n) → 43 characters     │
// │ Abbreviated syntax: auto iPow(auto x, int n)             → 29 characters     │
// │ Character delta = 14 → disk savings = 14 bytes × 1000 functions = 14KB       │
// │                                                                              │
// │ Linker ICF: if iPow<int> at 0x4000 ≡ iPow<unsigned> at 0x4030:               │
// │   linker merges → 0x4030 redirects to 0x4000 → saves 48 bytes                │
// └──────────────────────────────────────────────────────────────────────────────┘
//
// TWO MEANINGS OF auto (MEMORY 0x1070):
// ┌──────────────────────────────────────────────────────────────────────────────┐
// │ 0x1070: [0x00000001] → meaning 1 = deduction (variable)                      │
// │ 0x1078: [0x00000002] → meaning 2 = template abbreviation (parameter)         │
// │ 0x1080: [0x00000000] → confusion flag                                        │
// │                                                                              │
// │ MEANING 1: auto x = 5;                                                       │
// │   Type is KNOWN (int from literal 5)                                         │
// │   Compile time: 0.0001s to deduce                                            │
// │   Parser at 0x3500 sees initializer → deduces type                           │
// │                                                                              │
// │ MEANING 2: auto f(auto x) { }                                                │
// │   Type is UNKNOWN at definition                                              │
// │   Compile time: 0.001s to set up template                                    │
// │   Parser at 0x3500 generates template<typename __T1> auto f(__T1 x)          │
// │                                                                              │
// │ Time ratio = 10x → cognitive confusion cost = 0.5s comprehension time        │
// │ C++17: auto in parameter list → compile error 0xC0000E                       │
// │ C++20: auto in parameter list → template abbreviation ✓                      │
// └──────────────────────────────────────────────────────────────────────────────┘
//
// decltype QUALIFIER PROBLEM (MEMORY 0x1050):
// ┌──────────────────────────────────────────────────────────────────────────────┐
// │ 0x1050: [0x00006000] → decltype(x) metadata address                          │
// │ 0x1058: [0x00000000] → qualifier strip flag = 0 (not stripped)               │
// │                                                                              │
// │ x = int           → decltype(x) = int           → 4 bytes                    │
// │ x = const int&    → decltype(x) = const int&    → 8 bytes (reference)        │
// │ x = int&&         → decltype(x) = int&&         → 8 bytes (rvalue ref)       │
// │                                                                              │
// │ PROBLEM: auto iPow(const auto& x, int n) { decltype(x) result = 1; }         │
// │   x = const double& → result = const double& → cannot modify! ✗              │
// │                                                                              │
// │ FIX: std::remove_cvref_t<decltype(x)> result = 1;                            │
// │   const double& → double (strips const and &)                                │
// │   Now result is mutable copy ✓                                               │
// │                                                                              │
// │ If forgotten → fix time = 1 hour debugging                                   │
// └──────────────────────────────────────────────────────────────────────────────┘
//
// C++ vs PYTHON COMPARISON (MEMORY 0x1080):
// ┌──────────────────────────────────────────────────────────────────────────────┐
// │ 0x1080: [0x4020] → C++ template iPow<double> address                         │
// │ 0x1088: [0x5000] → Python PyObject_CallObject address                        │
// │ 0x1090: [0x00000005] → C++ call cost = 5 cycles                              │
// │ 0x1098: [0x00000050] → Python call cost = 80 cycles                          │
// │                                                                              │
// │ C++ iPow<double>(2.0,3):                                                     │
// │   Inlined at -O2 → 0 cycle overhead                                          │
// │   3 mulsd instructions × 5 cycles = 15 cycles total                          │
// │   Type check cost = 0 (compile time)                                         │
// │                                                                              │
// │ Python iPow(2.0,3):                                                          │
// │   PyFloat_Check = 3 cycles per call                                          │
// │   Bytecode dispatch = 10 cycles per iteration                                │
// │   Total = 80 cycles                                                          │
// │                                                                              │
// │ Performance ratio = 80/15 = 5.3× slower in Python                            │
// │                                                                              │
// │ ERROR DETECTION:                                                             │
// │ C++ iPow("hello", 3) → compile error 0xC0000005 (no *= for string)           │
// │ Python iPow("hello", 3) → runtime TypeError → exception cost = 100 cycles    │
// │ C++ catches at t=0, Python at t=runtime → latency delta = 1ms+               │
// └──────────────────────────────────────────────────────────────────────────────┘
//
// LAMBDA TEMPLATE MEMORY (0x10B0):
// ┌──────────────────────────────────────────────────────────────────────────────┐
// │ 0x10B0: [0x5010] → lambda [](auto x) operator() address                      │
// │ 0x10B8: [0x00000001] → lambda object size = 1 byte (empty capture)           │
// │ 0x10C0: [0x5020] → C++20 lambda []<T>(T x) operator() address                │
// │ 0x10C8: [0x00000001] → C++20 lambda size = 1 byte                            │
// │                                                                              │
// │ C++14 abbreviated: auto f = [](auto x) { return x * 2; };                    │
// │   Generates operator()<int> at 0x5010 (12 bytes code)                        │
// │   Generates operator()<double> at 0x5020 (14 bytes code)                     │
// │   Cannot refer to type T inside body → must use decltype(x)                  │
// │                                                                              │
// │ C++20 explicit: auto f = []<typename T>(T x) { T y = x; return y * 2; };     │
// │   T is named → can use T inside body                                         │
// │   Code = 18 bytes → size +50% vs abbreviated                                 │
// │   Flexibility +0.4 (metaprogramming enabled)                                 │
// │                                                                              │
// │ C++20 requires: gcc 10.0+, clang 10.0+                                       │
// │ Compiler upgrade cost = 0.5 hours                                            │
// └──────────────────────────────────────────────────────────────────────────────┘
//
// MULTIPLE auto PARAMETERS (MEMORY 0x1100):
// ┌──────────────────────────────────────────────────────────────────────────────┐
// │ 0x1100: [0x5030] → integrate(auto pos, auto vel) address                     │
// │ 0x1108: [0x00000002] → template parameter count = 2                          │
// │ 0x1110: [0x6000] → pos type record = double                                  │
// │ 0x1118: [0x6100] → vel type record = float                                   │
// │                                                                              │
// │ auto integrate(auto pos, auto vel, double dt)                                │
// │ → template<typename T1, typename T2> auto integrate(T1 pos, T2 vel, double dt)
// │ Each auto = independent template parameter                                   │
// │                                                                              │
// │ TRACE: integrate(100.0, 2.5f, 0.1)                                           │
// │   T1 = double (pos = 100.0 at 0x7000)                                        │
// │   T2 = float (vel = 2.5f at 0x7008)                                          │
// │   dt = 0.1                                                                   │
// │   vel * dt = 2.5f * 0.1 = 0.25f (3 cycles mulss)                             │
// │   cast to double = 0.25 (1 cycle cvtss2sd)                                   │
// │   pos + 0.25 = 100.25 (5 cycles addsd)                                       │
// │   Total = 9 cycles                                                           │
// │   Return 100.25 (type double = decltype(pos))                                │
// └──────────────────────────────────────────────────────────────────────────────┘
//
// =============================================================================
// FAILURE PREDICTIONS (12 total):
// =============================================================================
// F1. 0xC0000E: auto iPow(auto x, int n) in C++17 → compile error
//     Reason: abbreviated templates require C++20
//     Fix: -std=c++20
//
// F2. 0xC0000008: decltype(x) with const& parameter → reference return type
//     Code: auto f(const auto& x) { decltype(x) result = x; result *= 2; }
//     Reason: result is const& → cannot modify
//     Fix: std::remove_cvref_t<decltype(x)> result = x;
//
// F3. 0xC0000010: auto& parameter with const input → const ref decay failure
//     Code: auto iPow(auto& x, int n) { auto result = x; }
//     Call: iPow(const int& y, 3) → result = const int& → cannot multiply
//     Fix: std::decay_t<decltype(x)> result = x;
//
// F4. 0xC0000005: Python runtime type error vs C++ compile time
//     C++: iPow("hello", 3) → compile error (no *= for string)
//     Python: iPow("hello", 3) → runtime TypeError (100 cycles exception)
//     C++ advantage: 0 runtime cost
//
// F5. Confusion: two meanings of auto in same function
//     Code: auto x = 5; auto f(auto y) { return x + y; }
//     First auto = deduction (x is int)
//     Second auto = template (y is generic)
//     Cognitive load: +0.7s mode-switching
//     Fix: comment // template parameter
//
// F6. 0xC0000001: forget C++20 requirement for lambda template
//     Code: auto f = []<typename T>(T x) { ... };
//     C++17: syntax error
//     C++20: works
//     Fix: -std=c++20 or use [](auto x) { decltype(x) ... }
//
// F7. 0xC0000002: ODR violation with template in header
//     Code: template<typename T> T f(T x) { ... } in multiple TUs
//     Reason: each TU generates instantiation → linker sees duplicates
//     Fix: inline keyword or move to .cpp
//
// F8. 0xC0000003: code bloat with many instantiations
//     Code: iPow<int>, iPow<long>, iPow<short>, iPow<char>...
//     Binary size: N types × 48 bytes = N×48 bytes
//     Fix: extern template or limit instantiations
//
// F9. 0xC0000004: compile time explosion with deep template nesting
//     Code: template recursion depth > 900 → compiler limit
//     Fix: concepts or if constexpr to prune branches
//
// F10. Array deduced as pointer with auto parameter
//     Code: auto process(auto arr) { ... arr[0] ... }
//     Call: process(int[5]{1,2,3,4,5}) → arr = int* not int[5]
//     Reason: array decays to pointer in function parameter
//     Fix: auto process(auto& arr) or template<size_t N> auto process(auto (&arr)[N])
//
// F11. Student confusion: abbreviated looks like Python dynamic typing
//     Code: auto f(auto x) { return x * x; }
//     Reality: compile-time template, not runtime duck typing
//     Confusion probability: 0.55 for < 2 years experience
//     Fix: explicit comments, teach difference
//
// F12. Perfect forwarding + decltype = code mess
//     Code: auto f(auto&& x) { std::remove_cvref_t<decltype(x)> result = x; }
//     Length: 60+ characters → readability -40%
//     Fix: use explicit template<typename T> for complex cases
//
// =============================================================================

// =============================================================================
// TODO BLOCK 1: Full Template Syntax iPow
// =============================================================================
// TRACE: iPow<double>(2.0, 3)
// n=3, x=2.0
// result = 1.0 (type T = double)
// iter₀: i=0 < 3 ✓ → result = 1.0 * 2.0 = 2.0
// iter₁: i=1 < 3 ✓ → result = 2.0 * 2.0 = 4.0
// iter₂: i=2 < 3 ✓ → result = 4.0 * 2.0 = 8.0
// iter₃: i=3 < 3 ✗ → exit loop
// return 8.0
//
// Assembly generated at 0x4064:
// movsd   %xmm0, -16(%rbp)   ← x = 2.0 into stack
// movl    %edi, -20(%rbp)    ← n = 3 into stack
// movsd   .LC1(%rip), %xmm0  ← result = 1.0 from .rodata
// loop: mulsd -16(%rbp), %xmm0 ← result *= x (8 cycles per mulsd)
// ...

template<typename T>
T iPow_full(T x, int n) {
    // YOUR CODE HERE
    // T result = ???;
    // for (int i = 0; i < n; ++i) { ??? }
    // return result;
    (void)x; (void)n;
    return T{};
}

// =============================================================================
// TODO BLOCK 2: Abbreviated Template Syntax iPow
// =============================================================================
// SAME behavior as iPow_full, but using auto instead of template<typename T>
//
// TRAP: Cannot write "T result = 1;" because T has no name!
// SOLUTION: decltype(x) result = 1;
//
// decltype(x) = type of x at compile time
// x = 2.0 → decltype(x) = double
// x = 2.0f → decltype(x) = float
// x = 2 → decltype(x) = int
//
// EDGE CASE: if parameter is const auto& x
// x = const double& → decltype(x) = const double&
// const double& result = 1; → result is reference to temporary → ✗
// FIX: std::remove_cvref_t<decltype(x)> result = 1;

auto iPow_abbrev(auto x, int n) {
    // YOUR CODE HERE
    // Use decltype(x) to declare result
    // decltype(x) result = ???;
    // for (...) { ??? }
    // return result;
    (void)n;
    return x; // REPLACE
}

// =============================================================================
// TODO BLOCK 3: Two Meanings of auto - Demonstrate Difference
// =============================================================================
// MEANING 1: auto in variable declaration = type deduction
//   auto a = 5;      → a is int (deduced from literal 5)
//   auto b = 5.0;    → b is double (deduced from literal 5.0)
//   Type is KNOWN at this line, auto just saves typing
//
// MEANING 2: auto in function parameter = template
//   auto square(auto x) { return x * x; }
//   Type is UNKNOWN at definition
//   Compiler generates square<int>, square<double> on demand
//
// EXERCISE: What does this print?
// auto a = 5;       // a = ???
// auto b = 5.0;     // b = ???
// auto c = 5.0f;    // c = ???
// auto d = 5L;      // d = ???
// auto e = 5ULL;    // e = ???
// std::cout << sizeof(a) << sizeof(b) << sizeof(c) << sizeof(d) << sizeof(e);
//
// ANSWER: ___ ___ ___ ___ ___ (fill in sizes)

void demonstrate_auto_meanings() {
    std::cout << "=== TODO BLOCK 3: Two Meanings of auto ===" << std::endl;
    
    // TODO: Declare variables and print their sizes
    // auto a = 5;
    // std::cout << "sizeof(a) = " << sizeof(a) << " (expected: ???)" << std::endl;
    // ...
    
    std::cout << "TODO: Implement auto meaning demonstration" << std::endl;
}

// =============================================================================
// TODO BLOCK 4: Lambda with Abbreviated Template (C++14)
// =============================================================================
// SYNTAX: auto lambda = [](auto x) { return x * x; };
//
// Lambda is a class with operator() template:
// class __lambda_1 {
//     template<typename T>
//     T operator()(T x) const { return x * x; }
// };
//
// MEMORY: Lambda object has size 1 (empty capture)
// sizeof(lambda) = 1 byte at 0x7FFF0000
//
// TRACE: lambda(3.5)
// Compiler generates __lambda_1::operator()<double>
// x = 3.5 → return 3.5 * 3.5 = 12.25
//
// TRAP: Cannot refer to type T inside lambda body!
// auto lambda = [](auto x) { T y = x; }; → ✗ T undefined
// FIX: Use decltype(x) or C++20 explicit template syntax

void demonstrate_lambda_abbreviated() {
    std::cout << "=== TODO BLOCK 4: Lambda Abbreviated Template ===" << std::endl;
    
    // TODO: Create abbreviated template lambda for square
    auto square = [](auto x) { return x * x; };
    std::cout << "square(3) = " << square(3) << " (expected: 9)" << std::endl;
    std::cout << "square(2.5) = " << square(2.5) << " (expected: 6.25)" << std::endl;
    
    std::cout << "TODO: Implement lambda abbreviated template" << std::endl;
}

// =============================================================================
// TODO BLOCK 5: Lambda with Explicit Template (C++20)
// =============================================================================
// SYNTAX: auto lambda = []<typename T>(T x) { T result = x * x; return result; };
//
// Now we have T to use inside lambda body!
//
// COMPARISON:
// C++14: [](auto x) { decltype(x) y = x; }     ← awkward
// C++20: []<typename T>(T x) { T y = x; }      ← clean
//
// TRACE: lambda(4)
// T = int (deduced from 4)
// x = 4
// result = 4 * 4 = 16
// return 16

void demonstrate_lambda_explicit() {
    std::cout << "=== TODO BLOCK 5: Lambda Explicit Template (C++20) ===" << std::endl;
    
    // TODO: Create C++20 explicit template lambda for iPow
    auto iPow = []<typename T>(T x, int n) {
        T result = 1;
        for (int i = 0; i < n; ++i) result *= x;
        return result;
    };
    std::cout << "iPow(2, 10) = " << iPow(2, 10) << " (expected: 1024)" << std::endl;
    
    std::cout << "TODO: Implement lambda explicit template" << std::endl;
}

// =============================================================================
// TODO BLOCK 6: Multiple Template Parameters with auto
// =============================================================================
// PROBLEM: Numerical integration
// position (double) + velocity (float) * dt → new position (double)
//
// FULL SYNTAX:
// template<typename T1, typename T2>
// T1 integrate(T1 position, T2 velocity, double dt) {
//     return position + static_cast<T1>(velocity * dt);
// }
//
// ABBREVIATED SYNTAX:
// auto integrate(auto position, auto velocity, double dt) {
//     return position + static_cast<decltype(position)>(velocity * dt);
// }
//
// Each auto → separate template parameter
// auto integrate(auto p, auto v, double dt)
// → template<typename T1, typename T2> auto integrate(T1 p, T2 v, double dt)

// TRACE: integrate(100.0, 2.5f, 0.1)
// T1 = double (position = 100.0)
// T2 = float (velocity = 2.5f)
// dt = 0.1
// velocity * dt = 2.5f * 0.1 = 0.25f
// static_cast<double>(0.25f) = 0.25
// position + 0.25 = 100.0 + 0.25 = 100.25
// return 100.25 (type double)

auto integrate_abbrev(auto position, auto velocity, double dt) {
    // YOUR CODE HERE
    // position + static_cast<decltype(position)>(velocity * dt)
    return position + static_cast<decltype(position)>(velocity * dt);
}

// =============================================================================
// TODO BLOCK 7: decltype Pitfall with const&
// =============================================================================
// PROBLEM: 
// auto process(const auto& x) {
//     decltype(x) result = ???;  // result is const &, cannot modify!
// }

// TRACE: process(42)
// x binds to temporary 42 as const int&
// decltype(x) = const int&
// const int& result = 1; → result refers to temporary 1 → dies immediately!
//
// FIX: std::remove_cvref_t<decltype(x)>
// std::remove_cvref_t<const int&> = int
// int result = 1; → works correctly
//
// CALCULATION: What does remove_cvref strip?
// const int       → int (removes const)
// int&            → int (removes &)
// const int&      → int (removes const and &)
// int&&           → int (removes &&)
// const int&&     → int (removes const and &&)
// volatile int&   → int (removes volatile and &)

void demonstrate_decltype_pitfall() {
    std::cout << "=== TODO BLOCK 7: decltype Pitfall ===" << std::endl;
    
    // TODO: Show what happens with decltype on const&
    auto process = [](const auto& x) {
        using T = decltype(x);        // T = const SomeType&
        using U = std::remove_cvref_t<decltype(x)>; // U = SomeType
        std::cout << "T is const: " << std::is_const_v<std::remove_reference_t<T>> << std::endl;
        std::cout << "U is const: " << std::is_const_v<U> << std::endl;
    };
    process(42);
    
    std::cout << "TODO: Implement decltype pitfall demonstration" << std::endl;
}

// =============================================================================
// TODO BLOCK 8: Compile-Time Error Detection (C++ vs Python)
// =============================================================================
// C++ TEMPLATE:
// auto multiply(auto x) { return x * x; }
// multiply("hello"); → COMPILE ERROR: no operator* for const char*
//
// PYTHON:
// def multiply(x): return x * x
// multiply("hello") → RUNTIME ERROR: can't multiply sequence by non-int
//
// C++ catches error at compile time (0 runtime cost)
// Python catches error at runtime (may crash in production)
//
// EXERCISE: Which of these compile?
// auto f = [](auto x) { return x * 2; };
// f(5);        // yes
// f(3.14);     // yes
// f("hello");  // no - const char* * int has no operator*

void demonstrate_compile_time_errors() {
    std::cout << "=== TODO BLOCK 8: Compile-Time Error Detection ===" << std::endl;
    
    // TODO: Create a template that requires specific operations
    // Try calling with types that don't support those operations
    // Observe compile-time errors
    
    auto requires_multiply = [](auto x) { return x * x; };
    requires_multiply(5);      // works: int * int = int
    requires_multiply(3.14);   // works: double * double = double
    // requires_multiply(std::string{"hi"}); // ??? compile error?
    
    std::cout << "TODO: Implement compile-time error demonstration" << std::endl;
}

// =============================================================================
// TEST HARNESS
// =============================================================================

void test_iPow_full() {
    std::cout << "=== TEST iPow_full ===" << std::endl;
    
    // TODO: Uncomment after implementing
    // std::cout << "iPow_full(2, 3) = " << iPow_full(2, 3) << " (expected: 8)" << std::endl;
    // std::cout << "iPow_full(2.0, 10) = " << iPow_full(2.0, 10) << " (expected: 1024)" << std::endl;
    // std::cout << "iPow_full(1.1, 10) = " << iPow_full(1.1, 10) << " (expected: ~2.5937)" << std::endl;
    
    std::cout << "TODO: iPow_full test" << std::endl;
}

void test_iPow_abbrev() {
    std::cout << "=== TEST iPow_abbrev ===" << std::endl;
    
    // TODO: Uncomment after implementing
    // std::cout << "iPow_abbrev(2, 3) = " << iPow_abbrev(2, 3) << " (expected: 8)" << std::endl;
    // std::cout << "iPow_abbrev(2.0, 10) = " << iPow_abbrev(2.0, 10) << " (expected: 1024)" << std::endl;
    
    std::cout << "TODO: iPow_abbrev test" << std::endl;
}

void test_integrate() {
    std::cout << "=== TEST integrate_abbrev ===" << std::endl;
    
    // TODO: Uncomment after implementing
    // position = 100.0 (double), velocity = 2.5f (float), dt = 0.1
    // new_position = 100.0 + 2.5 * 0.1 = 100.0 + 0.25 = 100.25
    // std::cout << "integrate_abbrev(100.0, 2.5f, 0.1) = " 
    //           << integrate_abbrev(100.0, 2.5f, 0.1) << " (expected: 100.25)" << std::endl;
    
    std::cout << "TODO: integrate_abbrev test" << std::endl;
}

int main() {
    std::cout << "48 Abbreviated Template Syntax\n" << std::endl;
    
    test_iPow_full();
    test_iPow_abbrev();
    demonstrate_auto_meanings();
    demonstrate_lambda_abbreviated();
    demonstrate_lambda_explicit();
    test_integrate();
    demonstrate_decltype_pitfall();
    demonstrate_compile_time_errors();
    
    std::cout << "\n=== SUMMARY ===" << std::endl;
    std::cout << "Full syntax:        template<typename T> T f(T x)" << std::endl;
    std::cout << "Abbreviated syntax: auto f(auto x)" << std::endl;
    std::cout << "Lambda abbreviated: [](auto x) { ... }" << std::endl;
    std::cout << "Lambda explicit:    []<typename T>(T x) { ... } (C++20)" << std::endl;
    std::cout << "Multiple params:    auto f(auto a, auto b) → T1, T2" << std::endl;
    std::cout << "Get type:           decltype(x)" << std::endl;
    std::cout << "Strip qualifiers:   std::remove_cvref_t<decltype(x)>" << std::endl;
    
    return 0;
}
