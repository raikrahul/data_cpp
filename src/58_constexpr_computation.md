```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ SOURCE CODE: constexpr int x = fact(4);                                                                          │
│ COMPILER AST: Call(fact, 4) → Body: 4*fact(3) → ... → 4*3*2*1 → 24                                              │
│ ASSEMBLY: movl $24, -4(%rbp)  (Immediate value, NO function call logic preserved)                               │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ RUNTIME: ./program → LOAD 24 → PRINT 24 (Zero CPU cycles spent on multiplication)                               │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. CALC: 4×3×2×1 → 12×2=24×1=24. C++ `int x = 4*3*2*1;` implicitly constant-folded by optimizer.
02. TRAP: `int x` is runtime type. `const int x` is "read-only" not strictly "compile-time".
03. KEYWORD: `constexpr` = "force compile-time evaluation". `constexpr int x = 24;` ✓
04. IN: `int runtime_val; cin >> runtime_val;` → `constexpr int y = runtime_val;` → ERROR.
05. WHY: Compiler cannot know `runtime_val` value at build time. Runtime ≠ Compile-time. ✗
06. FUNCTION: `constexpr int product(int a, int b) { return a * b; }`
07. CALL: `constexpr int z = product(10, 20);` → Compiler execs `product` → returns 200 → `int z = 200;` stored.
08. CALL: `int w = product(runtime_val, 2);` → valid? YES. `constexpr` functions can degrade to runtime.
09. ■ `constexpr` variable = MUST be compile-time. `constexpr` function = CAN be compile-time. ■
10. SIMULATION: `coeff(x,y) = (x*x + y) * 0.333333`.
11. IN: x=3.0, y=3.0. CALC: 3*3=9. 9+3=12. 12*0.333333 = 3.999996.
12. MATH: Expected (9+3)/3 = 4.0. ACTUAL: 3.999996.
13. ZERO CHECK: `if (x == y) return 0.0;` → `coeff(3.0, 3.0)` returns 0.0 exact.
14. COMPILATION: `constexpr double res = coeff(3.0, 3.0);`
15. STEP 1: Check args (3.0, 3.0) are literals? Yes.
16. STEP 2: Exec body. `x==y`? True.
17. STEP 3: Return 0.0.
18. STEP 4: `res` initialized with 0.0 binary representation in `.rodata`.
19. OPTIMIZATION: `poly(a,b,c,x) = a*x^2 + b*x + c`? No, order 3: `a*x^3 + ...`
20. TRACE: `poly` interaction potential.
21. DATA: `a=1.0, b=2.0, c=1.0, x=2.0`.
22. CALC: Term1 = 1.0 * (2.0*2.0*2.0) = 8.0.
23. CALC: Term2 = ... (Wait, transcript says order 3 polynomial).
24. FORCE HAND: Use Horners? `((a*x + b)*x + c)*x + d`? Transcript specific formula unclear, assume standard.
25. FAIL PREDICTION F1: `constexpr` function with `void` return? Pre-C++14 illegal. C++20 OK.
26. FAIL PREDICTION F2: `constexpr` function with uninitialized vars? Undefined Behavior forbidden in constexpr contexts.
27. FAIL PREDICTION F3: `cin >> k; constexpr int val = k;` → Compile Error "value of k is not usable in constant expression".
28. FAIL PREDICTION F4: `constexpr double d = 1.0/3.0; if(d*3.0 == 1.0)` → False due to precision. Run-time or Compile-time same IEEE754 logic.
29. TRICK: `if consteval` (C++20). Detects if running at compile time.
30. TASK: Implement `coeff` and `poly` as `constexpr`.
31. VERIFY: `static_assert(coeff(3,3) == 0.0)` ensures logic correctness at compile time.
32. ■ `static_assert` = unit test that runs during build. Fails build if logic wrong. ■
---FAILURES---
F1. `constexpr int a; cin >> a;` → Compile Error: not initialized constant ✗
F2. `constexpr int f(int x) { return x; }` called with `cin >> v` inside `constexpr int z = f(v);` → Error ✗
F3. `const double PI = 3.14;` (runtime/linktime?) vs `constexpr double PI = 3.14;` (literal substitution)
F4. Comparison of float/double in `constexpr` behaves same as runtime (messy) ⚠
F5. `reinterpret_cast` inside `constexpr` → Forbidden ✗
