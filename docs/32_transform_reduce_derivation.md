# Problem 32: Transform Reduce Derivation (Mean & StdDev)

## Small Scale Trace (N=5)

01. **Input Data:** {10, 20, 30, 40, 50}
02. **Objective:** Compute Mean and StdDev in one pass.

## Step 1: Map (Transformation) -> int to Stats
03. **Formula:** `x -> {sum: x, sum_sq: x*x}`
04. **Trace:**
    - 10 -> {10, 100}
    - 20 -> {20, 400}
    - 30 -> {30, 900}
    - 40 -> {40, 1600}
    - 50 -> {50, 2500}

## Step 2: Reduce (Aggregation) -> Stats + Stats
05. **Formula:** `a + b -> {a.sum + b.sum, a.sum_sq + b.sum_sq}`
06. **Trace (Accumulation):**
    - Acc: {0, 0} (Init)
    - + {10, 100} -> Acc: {10, 100}
    - + {20, 400} -> Acc: {30, 500}
    - + {30, 900} -> Acc: {60, 1400}
    - + {40, 1600} -> Acc: {100, 3000}
    - + {50, 2500} -> Acc: {150, 5500}

## Step 3: Final Calculation
07. **Sums:** Sum = 150. SumSq = 5500. N = 5.
08. **Mean:** 150 / 5 = 30.
09. **Variance Formula:** (SumSq / N) - Mean^2.
    - Term 1: 5500 / 5 = 1100.
    - Term 2: 30^2 = 900.
    - Var: 1100 - 900 = 200.
10. **StdDev:** sqrt(200) ≈ 14.1421356.

## Failure Prediction

F1. **Integer Overflow:**
    `sum_sq` for 100,000 numbers up to 99.
    Max `x*x` = 99*99 ≈ 10,000.
    Max `SumSq` = 100,000 * 10,000 = 1,000,000,000.
    `int` max ≈ 2,000,000,000. It *should* fit in `int`, but `double` is safer for variance.

F2. **Initial Value Type:**
    If `transform_reduce` init is `0` (int), result is `int`, truncation occurs.
    Must use `Stats{0, 0}` to propagate struct type.

F3. **Variance Precision:**
    N large -> SumSq very large. Mean^2 very large.
    Subtraction of two large numbers -> Catastrophic Cancellation (Floating Point Issue)?
    (For 1-99 range, unlikely to be catastrophic, but possible).

---

## MY MISTAKES

### Error 1: Narrowing Conversion

| Field | Value |
|-------|-------|
| Line | 52 |
| Code | `Stats{x, x * x}` |
| Wrong | `int` passed to `double` field via brace-init |
| Fix | `Stats{(double)x, (double)(x * x)}` |

| Analysis | Answer |
|----------|--------|
| Why Sloppy | Did not read struct definition |
| What Missed | `struct Stats { double sum; double sum_sq; }` |
| How Prevent | Read struct fields before constructing |

### Error 2: Unused Variable Warning

| Field | Value |
|-------|-------|
| Line | 49 |
| Code | `Stats result = ...` |
| Wrong | `result` declared but not used |
| Fix | Print `result.sum` and `result.sum_sq` |

| Analysis | Answer |
|----------|--------|
| Why Sloppy | Incomplete implementation |
| What Missed | Verification section still commented |
| How Prevent | Uncomment verification after implementing logic |

---

## ORTHOGONAL THOUGHT PROCESS

1. Brace-init `{}` stricter than paren-init `()`.
2. `int` → `double` is widening but brace-init rejects implicit conversions.
3. Compiler error message contained exact fix: "insert explicit cast".
4. Time wasted asking AI > time reading error message.

---

## SESSION 2 REPORT

### TODO Block 3: ranges::transform (Squaring)

| Field | Value |
|-------|-------|
| Code | `ranges::transform(w, w.begin(), [](int x) { return x * x; })` |
| Input | `{2, 3, 4, 5}` |
| Output | `{4, 9, 16, 25}` |
| Status | ✓ Correct |

### TODO Block 4: ranges::for_each (Neighbor Average)

| Field | Value |
|-------|-------|
| Code | `ranges::for_each(indices, [&](size_t i) { dst[i] = 0.5 * (src[i-1] + src[i+1]); })` |
| Input | src=`{10,20,30,40,50}`, indices=`{1,2,3}` |
| Output | dst=`{0, 20, 30, 40, 0}` |
| Status | ✓ Correct |

### Errors This Session

None. Implementation correct on first attempt.

### ORTHOGONAL OBSERVATIONS

1. `for_each` iterates indices, not values → lambda captures vectors by reference.
2. Index range `[1, n-1)` excludes endpoints → `iota(begin, end, 1)` generates `{1, 2, ..., n-2}`.
3. `0.5 * (a + b)` requires `double` vectors to avoid integer truncation.
