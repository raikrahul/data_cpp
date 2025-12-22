#include <iostream>
#include <array>

// =============================================================================
// PROBLEM: DOT PRODUCT OF TWO VECTORS
// =============================================================================
// a = {2.0, 3.0, 5.0, 7.0}   (4 elements, primes)
// b = {11.0, 13.0, 17.0, 19.0}  (4 elements, primes)
//
// dot(a, b) = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3]
//           = 2*11 + 3*13 + 5*17 + 7*19
//           = 22 + 39 + 85 + 133
//           = 279
//
// =============================================================================
// MEMORY LAYOUT (a starts at 0x1000, b at 0x1020)
// =============================================================================
// 0x1000: a[0] = 2.0
// 0x1008: a[1] = 3.0
// 0x1010: a[2] = 5.0
// 0x1018: a[3] = 7.0
// 0x1020: b[0] = 11.0
// 0x1028: b[1] = 13.0
// 0x1030: b[2] = 17.0
// 0x1038: b[3] = 19.0
//
// =============================================================================
// EXERCISE 1: TRACE THE RUNTIME LOOP (fill table)
// =============================================================================
// Code: for(int k=0; k<4; ++k) sum += a[k] * b[k];
//
// | k | a[k] | b[k] | product | sum_after |
// |---|------|------|---------|-----------|
// | 0 | ____ | ____ | _______ | _________ |
// | 1 | ____ | ____ | _______ | _________ |
// | 2 | ____ | ____ | _______ | _________ |
// | 3 | ____ | ____ | _______ | _________ |
//
// Final sum = _________
//
// =============================================================================
// EXERCISE 2: COUNT OVERHEAD INSTRUCTIONS
// =============================================================================
// Per iteration: INC k (1) + CMP k,4 (1) + JMP (1) = 3 overhead
// Per iteration: LOAD a[k] (1) + LOAD b[k] (1) + MUL (1) + ADD (1) = 4 useful
//
// Total iterations = 4
// Total overhead   = 3 * __3__ = __9__
// Total useful     = 4 * __4__ = __16__
// Overhead %       = __9__ / __20__ = __45__%
//
// =============================================================================

// -----------------------------------------------------------------------------
// PART A: RUNTIME DOT PRODUCT (BOILERPLATE - DONE FOR YOU)
// -----------------------------------------------------------------------------
double dot_runtime(const double* a, const double* b, int n) {
    double sum = 0.0;
    for (int k = 0; k < n; ++k) {
        sum += a[k] * b[k];
    }
    return sum;
}

// -----------------------------------------------------------------------------
// PART B: COMPILE-TIME UNROLLER (YOU WRITE THIS)
// -----------------------------------------------------------------------------
// GOAL: Create template struct that "explodes" a loop at compile time.
//
// Unroller<3>::run(f) should:
//   1. Call f(3)
//   2. Call Unroller<2>::run(f)
//
// Unroller<0>::run(f) should:
//   1. Call f(0)
//   2. Call Unroller<-1>::run(f) → STOP
//
// EXERCISE 3: TRACE THE TEMPLATE INSTANTIATION
// unrolled_loop<4>(myFunc) starts at index 4-1=3.
//
// Call 1: Unroller<___>::run → myFunc(___)
// Call 2: Unroller<___>::run → myFunc(___)
// Call 3: Unroller<___>::run → myFunc(___)
// Call 4: Unroller<___>::run → myFunc(___)
// Call 5: Unroller<___>::run → _________ (terminate)
//
// Total instantiations: _____

template <int N, typename F>
struct UnrollerCtor {
   UnrollerCtor(F f) {
    f(N);
    UnrollerCtor<N-1, F>{f};
   } 
};
template <typename F>
struct UnrollerCtor<-1, F>{
    UnrollerCtor(F f){}
};


// TODO: Write the base case specialization for N = -1
// Hint: It should do nothing (empty function body).
// template <typename F>
// struct Unroller<-1, F> {
//     static void run(F /*f*/) {
//         // STOP
//     }
// };

// template <int Count, typename F>
// void unrolled_loop(F f) {
//     // Start recursion at Count-1 using constructor-based unroller
//     UnrollerCtor<Count - 1, F>{f};
// }

// -----------------------------------------------------------------------------
// PART C: UNROLLED DOT PRODUCT (YOU WRITE THIS)
// -----------------------------------------------------------------------------
// SIZE must be compile-time constant (template parameter).
template <int SIZE>
double dot_unrolled(const double* a, const double* b, double* pairwise) {
    double sum = 0.0;
    
    auto work = [&](int k) {
        pairwise[k] = a[k] * b[k];  // STORE EACH PRODUCT
        sum += pairwise[k];
    };
    
    UnrollerCtor<SIZE -1 , decltype(work)>{work};
    
    return sum;
}

template<typename T, int N>
T sumOfPositive(const std::array<T, N>& v)
{
    T sum = T{0};
    auto work = [&](int k) {
        if (v[k] > T{0})
        {
            sum += v[k];
        }
    };

    UnrollerCtor<N-1, decltype(work)>{work};
    
    return sum;
}

// =============================================================================
// EXERCISE 4: PREDICT ASSEMBLY OUTPUT
// =============================================================================
// For dot_unrolled<4>(a, b), compiler should generate:
//
// MOVSD (%rdi), %xmm0          ; load a[___]
// MULSD (%rsi), %xmm0          ; multiply by b[___]
// MOVSD 8(%rdi), %xmm1         ; load a[___]
// MULSD 8(%rsi), %xmm1         ; multiply by b[___]
// ADDSD %xmm1, %xmm0           ; accumulate
// MOVSD 16(%rdi), %xmm1        ; load a[___]
// MULSD 16(%rsi), %xmm1        ; multiply by b[___]
// ADDSD %xmm1, %xmm0           ; accumulate
// MOVSD 24(%rdi), %xmm1        ; load a[___]
// MULSD 24(%rsi), %xmm1        ; multiply by b[___]
// ADDSD %xmm1, %xmm0           ; accumulate
// RET
//
// COUNT: How many INC/CMP/JMP instructions? _____
// WHY? _________________________________

// =============================================================================
// EXERCISE 5: EDGE CASE - WHAT IF SIZE = 0?
// =============================================================================
// dot_unrolled<0>(a, b):
// unrolled_loop<0>(lambda) calls Unroller<-1>::run(lambda)
// Unroller<-1> does nothing.
// sum = 0.0 (unchanged).
// Result = 0.0
//
// Is this correct? (yes/no): _____
// dot product of zero-length vectors = _____

// =============================================================================
// EXERCISE 6: WHAT IF SIZE MISMATCHES ARRAY LENGTH?
// =============================================================================
// a has 4 elements. b has 4 elements.
// Code: dot_unrolled<6>(a, b)
//
// Unroller calls: lambda(5), lambda(4), lambda(3), lambda(2), lambda(1), lambda(0)
// lambda(5) accesses a[5] and b[5].
// a[5] is at address: 0x1000 + 5*8 = _________
// But a only has 4 elements (indices 0-3).
// a[5] is _________ (valid/invalid).
// Result: _________

int main() {
    // Data setup (same primes as above)
    std::array<double, 4> a = {2.0, 3.0, 5.0, 7.0};
    std::array<double, 4> b = {11.0, 13.0, 17.0, 19.0};
    
    // TEST 1: Runtime version
    double runtime_result = dot_runtime(a.data(), b.data(), 4);
    std::cout << "Runtime dot product: " << runtime_result 
              << " (Expected: 279)" << std::endl;
    
    // TEST 2: Unrolled version with pairwise products
    std::array<double, 4> pairwise = {0, 0, 0, 0};
    double unrolled_result = dot_unrolled<4>(a.data(), b.data(), pairwise.data());
    std::cout << "Unrolled dot product: " << unrolled_result 
              << " (Expected: 279)" << std::endl;
    std::cout << "Pairwise products: ";
    for(int i = 0; i < 4; ++i) std::cout << pairwise[i] << " ";
    std::cout << "(Expected: 22 39 85 133)" << std::endl;
    
    // ==========================================================================
    // EXERCISE 7: LARGER EXAMPLE (fill by hand)
    // ==========================================================================
    // c = {1, 2, 3, 4, 5, 6, 7, 8}   (8 elements)
    // d = {8, 7, 6, 5, 4, 3, 2, 1}   (8 elements, reversed)
    //
    // dot(c, d) = 1*8 + 2*7 + 3*6 + 4*5 + 5*4 + 6*3 + 7*2 + 8*1
    //           = ___ + ___ + ___ + ___ + ___ + ___ + ___ + ___
    //           = _____
    //
    // Runtime overhead for N=8:
    //   INC+CMP+JMP = 3 instructions × 8 iterations = _____ overhead
    //   LOAD+LOAD+MUL+ADD = 4 instructions × 8 = _____ useful
    //   Overhead % = _____ / _____ = _____%
    //
    // Unrolled overhead: _____
    
    // ==========================================================================
    // EXERCISE 8: ASSEMBLY TRACE (fill addresses)
    // ==========================================================================
    // a at 0x2000, b at 0x2040
    // sizeof(double) = 8
    //
    // a[0] at 0x2000 + 0*8 = _________
    // a[1] at 0x2000 + 1*8 = _________
    // a[2] at 0x2000 + 2*8 = _________
    // a[3] at 0x2000 + 3*8 = _________
    //
    // b[0] at 0x2040 + 0*8 = _________
    // b[1] at 0x2040 + 1*8 = _________
    // b[2] at 0x2040 + 2*8 = _________
    // b[3] at 0x2040 + 3*8 = _________
    //
    // MOVSD instruction for a[2]: MOVSD (__________), %xmm0
    // MULSD instruction for b[2]: MULSD (__________), %xmm0
    
    return 0;
}
