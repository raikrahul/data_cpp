# 68_stencil_variant_error_report.md

## Session Errors

### E1. Boundary Value
```
Line 211: Dirichlet{0.0}
Expected: Dirichlet{1.0}
Result: new_U[9] = 0 instead of 1
```
Why wrong: Copied line 202 without changing value.
Pattern: Copy-paste without edit.
Prevention: Read problem statement first. Left=0, Right=1.

### E2. Delayed O2 Implementation
```
apply(O2) returned 0.0 for 10+ minutes.
Output showed new_U[1..8] = 0.
```
Why wrong: TODO block not filled.
Pattern: Reading code, not executing it.
Prevention: Fill TODO, compile, run, check output immediately.

### E3. Delayed O4 Implementation
```
Same as E2. 
new_U[3..5] = 0 until O4 formula added.
```
Pattern: Same as E2.
Prevention: After E2, should have immediately done O4.

## Orthogonal Questions

Q1. You set both boundaries to 0.0. Did you read problem statement?
```
Problem: u(0)=0, u(L)=1
Your code: u(0)=0, u(L)=0
```
Answer: No. You copied.

Q2. You implemented O2 but not O4. Why wait?
```
O4 is 5-point. O2 is 3-point.
Both need same steps: pointer arithmetic + weights + sum.
```
Answer: Task switching cost. Should batch similar work.

Q3. Why return 0.0 instead of compile error?
```
Your TODOs returned 0.0.
Code compiled. Ran. Output = zeros.
You saw zeros but didn't fix immediately.
```
Answer: Output not checked. Run-and-check loop broken.

## Numerical Trace of E1

```
nodes[9] = Dirichlet{0.0}
apply(Dirichlet{0.0}, U, 9, dt) → return 0.0
new_U[9] = 0.0

Expected:
nodes[9] = Dirichlet{1.0}
apply(Dirichlet{1.0}, U, 9, dt) → return 1.0
new_U[9] = 1.0
```

## Time Wasted

| Error | Minutes Lost | Fix Time |
|-------|--------------|----------|
| E1    | 5            | 10 sec   |
| E2    | 10           | 2 min    |
| E3    | 5            | 2 min    |
| Total | 20           | 4.5 min  |

Ratio: 20/4.5 = 4.4× more time debugging than fixing.

## Pattern Summary

1. Copy-paste without verification → E1
2. Read without doing → E2, E3
3. Run without checking → All errors

## Prevention Protocol

1. Before copy: State what changes needed.
2. After TODO: Compile immediately.
3. After run: Compare output to expected.
4. Never leave TODO returning 0.0.
