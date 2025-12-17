# Problem 25: Transform Even/Odd Derivation

## Input Data (Given)

```
v = {1, 2, 3, 4, 5, 6, 7, 8}
```

## Output Data (To Derive)

```
w = {?, ?, ?, ?, ?, ?, ?, ?}
```
1 0 1 0 1 0 1 0 
## Rule

```
v[i] % 2 == 0 → w[i] = 1
v[i] % 2 == 1 → w[i] = -1
```

---

## Step 1: Calculate v[0] % 2

```
v[0] = 1
1 ÷ 2 = 0 remainder ???
1 % 2 = ???
```

**Question:** 1 % 2 = 0 or 1?

**Calculation by hand:**
```
1 = 2 × ??? + ???
```

**Result:** v[0] % 2 = ___

**Therefore:** v[0] is even? YES/NO: ___

**Therefore:** w[0] = ___

---

## Step 2: Calculate v[1] % 2

```
v[1] = 2
2 ÷ 2 = ??? remainder ???
2 % 2 = ???
```

**Calculation by hand:**
```
2 = 2 × ??? + ???
```

**Result:** v[1] % 2 = ___

**Therefore:** v[1] is even? YES/NO: ___

**Therefore:** w[1] = ___

---

## Step 3: Calculate v[2] % 2

```
v[2] = 3
3 ÷ 2 = ??? remainder ???
3 % 2 = ???
```

**Calculation by hand:**
```
3 = 2 × ??? + ???
```

**Result:** v[2] % 2 = ___

**Therefore:** w[2] is even? YES/NO: ___

**Therefore:** w[2] = ___

---

## Step 4: Calculate v[3] % 2

```
v[3] = 4
4 ÷ 2 = ??? remainder ???
4 % 2 = ???
```

**Result:** v[3] % 2 = ___

**Therefore:** w[3] = ___

---

## Step 5: Calculate v[4] % 2

```
v[4] = 5
5 % 2 = ???
```

**Result:** w[4] = ___

---

## Step 6: Calculate v[5] % 2

```
v[5] = 6
6 % 2 = ???
```

**Result:** w[5] = ___

---

## Step 7: Calculate v[6] % 2

```
v[6] = 7
7 % 2 = ???
```

**Result:** w[6] = ___

---

## Step 8: Calculate v[7] % 2

```
v[7] = 8
8 % 2 = ???
```

**Result:** w[7] = ___

---

## Step 9: Write Complete w Vector

```
w = {___, ___, ___, ___, ___, ___, ___, ___}
```

---

## Step 10: Pattern Recognition

```
Index | v[i] | v[i]%2 | even? | w[i]
------|------|--------|-------|------
  0   |  1   |  ???   |  ???  | ???
  1   |  2   |  ???   |  ???  | ???
  2   |  3   |  ???   |  ???  | ???
  3   |  4   |  ???   |  ???  | ???
  4   |  5   |  ???   |  ???  | ???
  5   |  6   |  ???   |  ???  | ???
  6   |  7   |  ???   |  ???  | ???
  7   |  8   |  ???   |  ???  | ???
```

---

## Step 11: Lambda Function - What Input?

```
Lambda receives: v[0], then v[1], then v[2], ...
Type of input: ???
Parameter name: choose any name (example: x, n, val, num)
```

**Write parameter:**
```
[](??? ???) {
```

---

## Step 12: Lambda Function - What Computation?

```
Input: 1 → compute ??? → output ???
Input: 2 → compute ??? → output ???
Input: 3 → compute ??? → output ???
```

**Pattern:**
```
Input % 2 == 0 → return ???
Input % 2 == 1 → return ???
```

---

## Step 13: Lambda Function - What Output Type?

```
Returns: 1 or -1
Type: ???
```

---

## Step 14: Lambda Function - Complete Syntax

```
auto lambda = [](??? ???) {
    if (??? % 2 == 0) {
        return ???;
    } else {
        return ???;
    }
};
```

**Alternative (ternary):**
```
auto lambda = [](??? ???) {
    return (??? % 2 == 0) ? ??? : ???;
};
```

---

## Step 15: std::transform - What Are The 4 Arguments?

```
From signature:
transform(_InputIterator __first, _InputIterator __last,
          _OutputIterator __result, _UnaryOperation __unary_op)
```

**Argument 1 (__first):**
```
Start reading from: v[???]
Iterator: v.begin() or v.end() or w.begin()?
Answer: ???
```

**Argument 2 (__last):**
```
Stop reading at: v[???]
Iterator: ???
```

**Argument 3 (__result):**
```
Start writing to: w[???]
Iterator: ???
```

**Argument 4 (__unary_op):**
```
Function to apply: ???
```

---

## Step 16: std::transform - Complete Call

```
std::transform(
    ???,  // first
    ???,  // last
    ???,  // result
    ???   // operation
);
```

---

## Step 17: Trace Execution By Hand

```
Iteration 0:
  __first points to v[0] = 1
  *__first = 1
  __unary_op(1) = lambda(1) = ???
  *__result = ???
  w[0] = ???
  ++__first → points to v[1]
  ++__result → points to w[1]

Iteration 1:
  __first points to v[1] = 2
  *__first = 2
  __unary_op(2) = lambda(2) = ???
  *__result = ???
  w[1] = ???
  ++__first → points to v[2]
  ++__result → points to w[2]

Iteration 2:
  __first points to v[2] = 3
  *__first = 3
  __unary_op(3) = ???
  w[2] = ???

Continue for remaining iterations...
```

---

## Step 18: Memory Addresses During Execution

```
v allocated at: 0x600000
v[0] at 0x600000 = 1
v[1] at 0x600004 = 2
v[2] at 0x600008 = 3
v[3] at 0x60000c = 4
v[4] at 0x600010 = 5
v[5] at 0x600014 = 6
v[6] at 0x600018 = 7
v[7] at 0x60001c = 8

w allocated at: 0x600020
w[0] at 0x600020 = ??? (to be filled)
w[1] at 0x600024 = ??? (to be filled)
w[2] at 0x600028 = ??? (to be filled)
...
```

---

## Step 19: Verify Result

```
Expected: w = {-1, 1, -1, 1, -1, 1, -1, 1}
Actual:   w = {___, ___, ___, ___, ___, ___, ___, ___}
Match? YES/NO: ___
```

---

## Mistakes to Avoid

1. **Writing to v instead of w**
   - Wrong: `std::transform(v.begin(), v.end(), v.begin(), lambda);`
   - Why wrong: Overwrites input data
   - Correct: `std::transform(v.begin(), v.end(), w.begin(), lambda);`

2. **Forgetting to allocate w**
   - Wrong: `std::vector<int> w;`
   - Why wrong: w.size() = 0, no space to write
   - Correct: `std::vector<int> w(v.size());`

3. **Lambda returns void**
   - Wrong: `[](int x) { x % 2 == 0 ? 1 : -1; }`
   - Why wrong: No return statement
   - Correct: `[](int x) { return x % 2 == 0 ? 1 : -1; }`

4. **Wrong condition**
   - Wrong: `x % 2 == 1 ? 1 : -1`
   - Why wrong: Returns 1 for odd, -1 for even (reversed)
   - Correct: `x % 2 == 0 ? 1 : -1`

---

## Implementation Checklist

- [ ] Calculated v[0] % 2 by hand
- [ ] Calculated v[1] % 2 by hand
- [ ] Calculated all 8 values by hand
- [ ] Filled w vector with expected values
- [ ] Wrote lambda parameter type
- [ ] Wrote lambda condition (% 2 == 0)
- [ ] Wrote lambda return values (1 and -1)
- [ ] Wrote std::transform first argument (v.begin())
- [ ] Wrote std::transform second argument (v.end())
- [ ] Wrote std::transform third argument (w.begin())
- [ ] Wrote std::transform fourth argument (lambda)
- [ ] Compiled code
- [ ] Ran code
- [ ] Verified output matches expected
