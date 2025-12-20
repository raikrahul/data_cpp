#include <iostream>

// FAILURE PREDICTION: Your code `return N + numIntegers<N-1>()` has NO BASE CASE.
// Compile-time recursion will subtract forever: 3 -> 2 -> 1 -> 0 -> -1 -> -2 ... -> CRASH.
// You MUST stop at 0. Sloppy reading of recursion rules.

// Fixed version:
template<int N>
int numIntegers() {
    if constexpr (N == 0) {
        return 0;
    } else {
        return N + numIntegers<N-1>();
    }
}

// Alternative purely distinct template specialization approach (more "classic"):
/*
template<int N>
int numIntegersOld() {
    return N + numIntegersOld<N-1>();
}
template<>
int numIntegersOld<0>() {
    return 0;
}
*/

int main() {
    // We want to see the assembly for N=3
    // volatile to prevent total elimination of the call site if we want to see the call, 
    // but the function itself will likely be constant-folded.
    int result = numIntegers<3>();
    return result;
}
