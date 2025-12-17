#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // INPUT DATA (given):
    // v = {1, 2, 3, 4, 5, 6, 7, 8}
    //      ↓  ↓  ↓  ↓  ↓  ↓  ↓  ↓
    //    odd even odd even odd even odd even
    //
    // EXPECTED OUTPUT (to fill):
    // w = {-1, 1, -1, 1, -1, 1, -1, 1}
    //
    // RULE:
    // v[i] even → w[i] = 1
    // v[i] odd  → w[i] = -1

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> w(v.size());  // Allocate w with same size as v

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 1: Trace by hand what happens at each index
    // ════════════════════════════════════════════════════════════════════════
    //
    // INDEX 0:
    // v[0] = 1
    // 1 % 2 = ???
    // 1 is even? YES/NO: ___
    // w[0] should be: ___
    //
    // INDEX 1:
    // v[1] = 2
    // 2 % 2 = ???
    // 2 is even? YES/NO: ___
    // w[1] should be: ___
    //
    // INDEX 2:
    // v[2] = 3
    // 3 % 2 = ???
    // 3 is even? YES/NO: ___
    // w[2] should be: ___
    //
    // INDEX 3:
    // v[3] = 4
    // 4 % 2 = ???
    // 4 is even? YES/NO: ___
    // w[3] should be: ___
    //
    // Continue for indices 4, 5, 6, 7...
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 2: What does std::transform need?
    // ════════════════════════════════════════════════════════════════════════
    //
    // From /usr/include/c++/13/bits/stl_algo.h line 4298:
    // template<typename _InputIterator, typename _OutputIterator, typename _UnaryOperation>
    // _OutputIterator transform(_InputIterator __first, _InputIterator __last,
    //                           _OutputIterator __result, _UnaryOperation __unary_op)
    //
    // PARAMETERS:
    // __first  = ??? (what iterator?)
    // from v.begin() to v.end()
    // __last   = ??? (what iterator?)
    // to v.end()
    // __result = ??? (what iterator?)
    // w.begin()
    // __unary_op = ??? (what function?)
    // lambda
    //
    // WHAT __unary_op MUST DO:
    // Input: int (element from v)
    // Output: ??? (what type? what value?)
    //  takes an int returns a bool (true if even, false if odd)
    // ════════════════════════════════════════════════════════════════════════
    // actually has to return a 1 or -1
    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 3: Write lambda step by step
    // ════════════════════════════════════════════════════════════════════════
    //
    // STEP 1: Lambda takes what parameter?
    // auto lambda = []( int & x  ) {
    //
    // STEP 2: Lambda checks what condition?
    // Check if parameter is even using: ??? % 2 == ???
    //                  if (x %2 ) == 0
    {
        // return 1
    }
    // else
    {
        // return -1
    }
    // STEP 3: Lambda returns what?
    // If even: return ???
    // If odd: return ???
    //
    // STEP 4: Complete lambda syntax
    // auto lambda = [](???) { ??? };
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // TODO BLOCK 4: Call std::transform
    // ════════════════════════════════════════════════════════════════════════
    //
    // std::transform(
    //     ???,  // first iterator (v.begin()? v.end()? w.begin()?)
    //     ???,  // last iterator
    //     ???,  // result iterator (where to write output?)
    //     ???   // lambda function
    // );
    //
    // ════════════════════════════════════════════════════════════════════════

    // ════════════════════════════════════════════════════════════════════════
    // WRITE YOUR CODE HERE
    // ════════════════════════════════════════════════════════════════════════

    // TODO: Write std::transform call with lambda

    // ════════════════════════════════════════════════════════════════════════
    // VERIFICATION: Print results
    // ════════════════════════════════════════════════════════════════════════
    std::transform(v.begin(), v.end(), w.begin(), [](int x) { return x % 2 == 0 ? 1 : -1; });
    std::cout << "v = {";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i < v.size() - 1) std::cout << ", ";
    }
    std::cout << "}\n";

    std::cout << "w = {";
    for (size_t i = 0; i < w.size(); ++i) {
        std::cout << w[i];
        if (i < w.size() - 1) std::cout << ", ";
    }
    std::cout << "}\n";

    std::cout << "\nExpected: w = {-1, 1, -1, 1, -1, 1, -1, 1}\n";

    return 0;
}
