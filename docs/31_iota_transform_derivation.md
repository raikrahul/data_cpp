# Problem 31: Iota & Transform Derivation

## Pipeline Trace

01. **Container:** `std::vector<int> v(20)`
02. **Address Space:** 0x1000 start. 20 elements * 4 bytes = 80 bytes.
03. **State 0 (Init):** [0, 0, 0, ..., 0] (Assuming default init).

## Step 1: std::iota(v.begin(), v.end(), 0)

04. **Operation:** Incremental assignment starting from 0.
05. **Loop Trace:**
    - Iter 0: *0x1000 = 0 -> ++val (1)
    - Iter 1: *0x1004 = 1 -> ++val (2)
    - ...
    - Iter 19: *0x104C = 19 -> ++val (20)
06. **State 1:** {0, 1, 2, ..., 19}.

## Step 2: std::ranges::transform(v, v.begin(), n -> n*7)

07. **Input Range:** v (State 1).
08. **Output Iterator:** v.begin() (In-place modification).
09. **Projection:** None.
10. **Transformation:** Lambda `[](int n){ return n * 7; }`
11. **Loop Trace:**
    - Read 0x1000 (0) -> Calc 0*7=0 -> Write 0x1000 (0).
    - Read 0x1004 (1) -> Calc 1*7=7 -> Write 0x1004 (7).
    - Read 0x1008 (2) -> Calc 2*7=14 -> Write 0x1008 (14).
    - ...
    - Read 0x104C (19) -> Calc 19*7=133 -> Write 0x104C (133).
12. **State 2:** {0, 7, 14, ..., 133}.

## Failure Prediction

F1. **Forget Resize:**
    `vector<int> v; iota(...)` -> Segfault / UB (writing to non-existent memory).
    Iota does NOT resize. It expects valid range.

F2. **Transform Return:**
    `transform` returns output iterator to end.
    If ignored, fine. If assigned to `v`, error (type mismatch).

F3. **Wrong Output Iterator:**
    `transform(v, std::back_inserter(v), ...)` -> Infinite Loop??
    Reading from v, pushing to v -> Reallocation -> Iterator invalidation -> Crash.
    (Note: transform reads InputIterator, writes OutputIterator. If `v` grows, iterators die).
