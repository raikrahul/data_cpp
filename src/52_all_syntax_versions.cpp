// 52_all_syntax_versions.cpp
// DEMONSTRATION: All template/auto syntax variations + C++ version compatibility
// Compile with: g++ -std=c++11/14/17/20 to see what works where

#include <iostream>
#include <type_traits>

// =============================================================================
// SYNTAX 1: Full template (C++11+)
// =============================================================================
template<typename T>
T square_full(T x) {
    T result = x * x;  // T available in body
    return result;
}

// =============================================================================
// SYNTAX 2: Abbreviated function template (C++20 ONLY)
// =============================================================================
#if __cplusplus >= 202002L
auto square_abbrev(auto x) {
    decltype(x) result = x * x;  // must use decltype, no T available
    return result;
}
#endif

// =============================================================================
// SYNTAX 3: Lambda abbreviated (C++14+)
// =============================================================================
auto lambda_abbrev = [](auto x) { return x * x; };

// =============================================================================
// SYNTAX 4: Lambda abbreviated with explicit return type (C++14+)
// =============================================================================
auto lambda_abbrev_explicit = [](auto x) -> decltype(x) { return x * x; };

// =============================================================================
// SYNTAX 5: Lambda explicit template (C++20 ONLY)
// =============================================================================
#if __cplusplus >= 202002L
auto lambda_explicit = []<typename T>(T x) -> T { 
    T result = x * x;  // T available in body
    return result; 
};
#endif

// =============================================================================
// DECLTYPE PITFALL DEMONSTRATION
// =============================================================================
// PROBLEM: const auto& parameter → decltype preserves const&

#if __cplusplus >= 202002L
// BROKEN VERSION - decltype(x) = const int& when x is const&
auto process_broken(const auto& x) {
    // decltype(x) = const int& (for int input)
    // const int& result = 1; → binds to temporary → DANGER
    // Cannot modify result!
    
    std::cout << "  decltype(x) is const: " 
              << std::is_const_v<std::remove_reference_t<decltype(x)>> << std::endl;
    std::cout << "  decltype(x) is reference: " 
              << std::is_reference_v<decltype(x)> << std::endl;
    
    // This would fail to compile if we tried to modify:
    // decltype(x) result = x;
    // result = result * 2;  // ERROR: cannot assign to const
    
    return x * 2;  // works because returns by value
}

// FIXED VERSION - strip const and reference
auto process_fixed(const auto& x) {
    // std::remove_cvref_t<decltype(x)> = int (stripped const and &)
    using CleanType = std::remove_cvref_t<decltype(x)>;
    
    std::cout << "  CleanType is const: " 
              << std::is_const_v<CleanType> << std::endl;
    std::cout << "  CleanType is reference: " 
              << std::is_reference_v<CleanType> << std::endl;
    
    CleanType result = x;  // mutable copy
    result = result * 2;   // CAN modify now
    return result;
}
#endif

// =============================================================================
// MULTIPLE AUTO PARAMETERS (C++20 ONLY)
// =============================================================================
#if __cplusplus >= 202002L
// Each auto = separate template parameter
// integrate(auto pos, auto vel) → template<typename T1, typename T2>
auto integrate(auto position, auto velocity, double dt) {
    // position = double (100.0)
    // velocity = float (2.5f)
    // dt = double (0.1)
    // velocity * dt = 2.5f * 0.1 = 0.25
    // static_cast to position type (double)
    // 100.0 + 0.25 = 100.25
    return position + static_cast<decltype(position)>(velocity * dt);
}
#endif

// =============================================================================
// MAIN - DEMONSTRATE ALL
// =============================================================================
int main() {
    std::cout << "C++ Standard: " << __cplusplus << std::endl;
    std::cout << std::endl;
    
    // =========================================================================
    // SYNTAX 1: Full template (works C++11, 14, 17, 20)
    // =========================================================================
    std::cout << "=== SYNTAX 1: Full template (C++11+) ===" << std::endl;
    std::cout << "square_full(3) = " << square_full(3) << " (expected: 9)" << std::endl;
    std::cout << "square_full(2.5) = " << square_full(2.5) << " (expected: 6.25)" << std::endl;
    std::cout << std::endl;
    
    // =========================================================================
    // SYNTAX 2: Abbreviated function (C++20 only)
    // =========================================================================
#if __cplusplus >= 202002L
    std::cout << "=== SYNTAX 2: Abbreviated function (C++20) ===" << std::endl;
    std::cout << "square_abbrev(3) = " << square_abbrev(3) << " (expected: 9)" << std::endl;
    std::cout << "square_abbrev(2.5) = " << square_abbrev(2.5) << " (expected: 6.25)" << std::endl;
    std::cout << std::endl;
#else
    std::cout << "=== SYNTAX 2: Abbreviated function (SKIPPED - requires C++20) ===" << std::endl;
    std::cout << std::endl;
#endif
    
    // =========================================================================
    // SYNTAX 3: Lambda abbreviated (C++14+)
    // =========================================================================
    std::cout << "=== SYNTAX 3: Lambda abbreviated (C++14+) ===" << std::endl;
#if __cplusplus >= 201402L
    std::cout << "lambda_abbrev(3) = " << lambda_abbrev(3) << " (expected: 9)" << std::endl;
    std::cout << "lambda_abbrev(2.5) = " << lambda_abbrev(2.5) << " (expected: 6.25)" << std::endl;
#else
    std::cout << "SKIPPED - requires C++14" << std::endl;
#endif
    std::cout << std::endl;
    
    // =========================================================================
    // SYNTAX 4: Lambda with explicit return type (C++14+)
    // =========================================================================
    std::cout << "=== SYNTAX 4: Lambda explicit return type (C++14+) ===" << std::endl;
#if __cplusplus >= 201402L
    std::cout << "lambda_abbrev_explicit(3) = " << lambda_abbrev_explicit(3) << " (expected: 9)" << std::endl;
    std::cout << "lambda_abbrev_explicit(2.5) = " << lambda_abbrev_explicit(2.5) << " (expected: 6.25)" << std::endl;
#else
    std::cout << "SKIPPED - requires C++14" << std::endl;
#endif
    std::cout << std::endl;
    
    // =========================================================================
    // SYNTAX 5: Lambda explicit template (C++20 only)
    // =========================================================================
#if __cplusplus >= 202002L
    std::cout << "=== SYNTAX 5: Lambda explicit template (C++20) ===" << std::endl;
    std::cout << "lambda_explicit(3) = " << lambda_explicit(3) << " (expected: 9)" << std::endl;
    std::cout << "lambda_explicit(2.5) = " << lambda_explicit(2.5) << " (expected: 6.25)" << std::endl;
    std::cout << std::endl;
#else
    std::cout << "=== SYNTAX 5: Lambda explicit template (SKIPPED - requires C++20) ===" << std::endl;
    std::cout << std::endl;
#endif

    // =========================================================================
    // DECLTYPE PITFALL DEMO
    // =========================================================================
#if __cplusplus >= 202002L
    std::cout << "=== DECLTYPE PITFALL: const auto& ===" << std::endl;
    std::cout << "process_broken(42):" << std::endl;
    int r1 = process_broken(42);
    std::cout << "  result = " << r1 << " (expected: 84)" << std::endl;
    std::cout << std::endl;
    
    std::cout << "process_fixed(42):" << std::endl;
    int r2 = process_fixed(42);
    std::cout << "  result = " << r2 << " (expected: 84)" << std::endl;
    std::cout << std::endl;
#else
    std::cout << "=== DECLTYPE PITFALL: (SKIPPED - requires C++20) ===" << std::endl;
    std::cout << std::endl;
#endif

    // =========================================================================
    // MULTIPLE AUTO PARAMS
    // =========================================================================
#if __cplusplus >= 202002L
    std::cout << "=== MULTIPLE AUTO PARAMS ===" << std::endl;
    // position = 100.0 (double), velocity = 2.5f (float), dt = 0.1
    // new_pos = 100.0 + 2.5 * 0.1 = 100.0 + 0.25 = 100.25
    double pos = integrate(100.0, 2.5f, 0.1);
    std::cout << "integrate(100.0, 2.5f, 0.1) = " << pos << " (expected: 100.25)" << std::endl;
    std::cout << std::endl;
#else
    std::cout << "=== MULTIPLE AUTO PARAMS: (SKIPPED - requires C++20) ===" << std::endl;
    std::cout << std::endl;
#endif

    // =========================================================================
    // VERSION COMPATIBILITY SUMMARY
    // =========================================================================
    std::cout << "=== VERSION COMPATIBILITY ===" << std::endl;
    std::cout << "| Syntax                      | C++11 | C++14 | C++17 | C++20 |" << std::endl;
    std::cout << "|-----------------------------|-------|-------|-------|-------|" << std::endl;
    std::cout << "| template<T> T f(T x)        |   Y   |   Y   |   Y   |   Y   |" << std::endl;
    std::cout << "| auto f(auto x)              |   N   |   N   |   N   |   Y   |" << std::endl;
    std::cout << "| [](auto x) { }              |   N   |   Y   |   Y   |   Y   |" << std::endl;
    std::cout << "| [](auto x) -> T { }         |   N   |   Y   |   Y   |   Y   |" << std::endl;
    std::cout << "| []<typename T>(T x) { }     |   N   |   N   |   N   |   Y   |" << std::endl;
    std::cout << std::endl;
    
    return 0;
}
