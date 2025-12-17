# Problem 25: Transform Even/Odd - Error Report

## Errors Found

### Error 1: Orphaned code blocks (lines 88-94)
Line: 88-94
Wrong: Wrote `{ // return 1 }` and `{ // return -1 }` as standalone blocks outside any function
Should be: Delete these lines, they are not part of lambda syntax
Why sloppy: Confused comment syntax with actual code structure
What missed: Comments in TODO block are instructions, not code to write
How to prevent: Read TODO blocks as instructions, write actual code in designated section

### Error 2: Wrong lambda parameter type (line 83)
Line: 83 (comment)
Wrong: Wrote `int & x` (reference)
Should be: `int x` (value) or `const int& x` (const reference)
Why sloppy: Added `&` without understanding when references needed
What missed: Lambda receives temporary from iterator dereference, value parameter sufficient
How to prevent: Use value for small types (int), const reference for large types (string, vector)

### Error 3: Wrong return type in comment (line 75)
Line: 75 (comment)
Wrong: Wrote "returns a bool (true if even, false if odd)"
Should be: Returns int (1 if even, -1 if odd)
Why sloppy: Confused condition check with return value
What missed: Problem requires 1/-1, not true/false
How to prevent: Read problem statement: "w[i]=1 if even, -1 if odd"

### Error 4: Corrected self on line 77
Line: 77 (comment)
Wrong: Initially thought bool return
Should be: "actually has to return a 1 or -1"
Why sloppy: Did not read problem carefully first time
What missed: Problem explicitly states 1 and -1
How to prevent: Read problem twice before writing anything

### Error 5: Derivation file incomplete (docs/25_transform_even_odd_derivation.md line 13)
Line: 13
Wrong: Wrote "1 0 1 0 1 0 1 0" as answer
Should be: w = {-1, 1, -1, 1, -1, 1, -1, 1}
Why sloppy: Wrote remainders (1%2=1, 2%2=0) instead of final values
What missed: Remainder is intermediate step, must convert to 1/-1
How to prevent: Follow through calculation: 1%2=1 → odd → -1, not just stop at remainder

## Correct Implementation

### What user wrote (line 126):
```cpp
std::transform(v.begin(), v.end(), w.begin(), [](int x) { return x % 2 == 0 ? 1 : -1; });
```

**Analysis:**
```
✓ Correct: v.begin() (start reading from v[0])
✓ Correct: v.end() (stop at past-the-end)
✓ Correct: w.begin() (start writing to w[0])
✓ Correct: [](int x) (lambda takes int by value)
✓ Correct: x % 2 == 0 (checks if even)
✓ Correct: ? 1 : -1 (returns 1 if even, -1 if odd)
```

**Execution trace:**
```
Iteration 0: x=1, 1%2=1, 1==0? NO, return -1, w[0]=-1
Iteration 1: x=2, 2%2=0, 0==0? YES, return 1, w[1]=1
Iteration 2: x=3, 3%2=1, 1==0? NO, return -1, w[2]=-1
Iteration 3: x=4, 4%2=0, 0==0? YES, return 1, w[3]=1
Iteration 4: x=5, 5%2=1, 1==0? NO, return -1, w[4]=-1
Iteration 5: x=6, 6%2=0, 0==0? YES, return 1, w[5]=1
Iteration 6: x=7, 7%2=1, 1==0? NO, return -1, w[6]=-1
Iteration 7: x=8, 8%2=0, 0==0? YES, return 1, w[7]=1
```

**Result:**
```
v = {1, 2, 3, 4, 5, 6, 7, 8}
w = {-1, 1, -1, 1, -1, 1, -1, 1}
Expected: {-1, 1, -1, 1, -1, 1, -1, 1}
Match: YES ✓
```

## Conceptual Errors

### Conceptual Error 1: Remainder vs Final Value
Wrong: Thought 1%2=1 is final answer
Should be: 1%2=1 → odd → apply rule → -1
Why sloppy: Stopped calculation halfway
What missed: Problem has 2-step process: compute remainder, then apply rule
How to prevent: Always complete full calculation chain

### Conceptual Error 2: Bool vs Int Return
Wrong: Thought lambda returns bool
Should be: Lambda returns int (1 or -1)
Why sloppy: Assumed even/odd check means bool
What missed: Problem specifies exact values 1 and -1, not true/false
How to prevent: Read output specification, not just input condition

### Conceptual Error 3: Reference Parameter
Wrong: Wrote `int & x` in comment
Should be: `int x` sufficient for small types
Why sloppy: Overused references without understanding cost/benefit
What missed: Reference adds indirection, value copy is 4 bytes (cheap for int)
How to prevent: Use value for primitives, const reference for objects

## Summary Statistics

Total errors: 5
Syntax errors: 1 (orphaned blocks)
Type errors: 2 (reference parameter, bool return)
Logic errors: 1 (remainder vs final value)
Incomplete work: 1 (derivation file)

Carelessness level: MEDIUM
Root cause: Rushed through TODO blocks, did not complete derivation worksheet
Solution: Fill derivation worksheet completely before writing code

## What Went Right

✓ Final code correct (line 126)
✓ Understood std::transform signature
✓ Understood lambda syntax
✓ Understood ternary operator
✓ Code compiles and runs
✓ Output matches expected
