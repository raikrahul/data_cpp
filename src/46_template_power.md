01. WRITE ON PAPER: x=2, n=3, result=1, i=0, DRAW TABLE with columns |i|result|computation|, row 0: |0|1|initial|, now CALCULATE i<n → 0<3 → ✓ → enter loop, WRITE result = result × x = 1 × 2 = 2, INCREMENT i = 0+1 = 1, UPDATE TABLE row 1: |1|2|1×2=2|
02. STATE CHECK: i=1, result=2, n=3, CALCULATE i<n → 1<3 → ✓ → continue loop, WRITE result = result × x = 2 × 2 = 4, INCREMENT i = 1+1 = 2, UPDATE TABLE row 2: |2|4|2×2=4|
03. STATE CHECK: i=2, result=4, n=3, CALCULATE i<n → 2<3 → ✓ → continue loop, WRITE result = result × x = 4 × 2 = 8, INCREMENT i = 2+1 = 3, UPDATE TABLE row 3: |3|8|4×2=8|
04. STATE CHECK: i=3, result=8, n=3, CALCULATE i<n → 3<3 → ✗ → exit loop, WRITE return result = 8, VERIFY 2³ = 2×2×2 = 8 ✓, COUNT iterations = 3, VERIFY iterations = n ✓
05. ■ GROUND: x=2, n=3, result=8, i=3, iterations=3, 2³=8 ✓ ■ NEXT: trace pow(2.5, 2) ■
06. WRITE ON PAPER: x=2.5, n=2, result=1.0, i=0, DRAW NEW TABLE |i|result|computation|, row 0: |0|1.0|initial|, CALCULATE i<n → 0<2 → ✓ → enter loop, WRITE result = 1.0 × 2.5 = 2.5, INCREMENT i = 0+1 = 1, UPDATE TABLE row 1: |1|2.5|1.0×2.5=2.5|
07. STATE CHECK: i=1, result=2.5, n=2, CALCULATE i<n → 1<2 → ✓ → continue loop, WRITE result = 2.5 × 2.5 = 6.25, INCREMENT i = 1+1 = 2, UPDATE TABLE row 2: |2|6.25|2.5×2.5=6.25|
08. STATE CHECK: i=2, result=6.25, n=2, CALCULATE i<n → 2<2 → ✗ → exit loop, WRITE return result = 6.25, VERIFY 2.5² = 2.5×2.5 = 6.25 ✓, COUNT iterations = 2, VERIFY iterations = n ✓
09. ■ GROUND: x=2.5, n=2, result=6.25, i=2, iterations=2, 2.5²=6.25 ✓ ■ NEXT: trace negative base ■
10. WRITE ON PAPER: x=-3, n=3, result=1, i=0, DRAW NEW TABLE |i|result|computation|, row 0: |0|1|initial|, iter₁: result = 1 × (-3) = -3, iter₂: result = (-3) × (-3) = +9, iter₃: result = 9 × (-3) = -27, VERIFY: negative × negative = positive, positive × negative = negative, COUNT sign flips: 3 (odd) → final sign = negative ✓
11. COMPARE: pow(-3,3) = -27 (odd n → negative), pow(-3,2) = 9 (even n → positive), WRITE RULE: sign(result) = sign(x)^n = (-1)^n, n=odd → -1, n=even → +1 ✓
12. ■ GROUND: odd exponent preserves sign, even exponent loses sign ■ NEXT: edge cases ■
13. WRITE ON PAPER: x=5, n=0, result=1, i=0, CALCULATE i<n → 0<0 → ✗ → loop NEVER executes, return result = 1 unchanged, VERIFY x⁰ = 1 by definition ✓, TRAP: loop body never runs, result stays at initial value
14. WRITE ON PAPER: x=0, n=5, result=1, i=0, iter₁: result = 1 × 0 = 0, iter₂: result = 0 × 0 = 0, iter₃: 0, iter₄: 0, iter₅: 0, return 0, TRAP: once result=0, all subsequent multiplications = 0, VERIFY 0⁵ = 0 ✓
15. WRITE ON PAPER: x=0, n=0, CALCULATE: n=0 → loop never runs → result=1, BUT mathematically 0⁰ is undefined ⚠, CODE returns 1, MATH returns undefined, MISMATCH between code behavior and mathematical definition
16. ■ GROUND: x⁰=1, 0ⁿ=0 (n>0), 0⁰=1 (code) but undefined (math) ■ NEXT: template syntax ■
17. DRAW DIAGRAM: pow_int at 0x1000 (48 bytes), pow_float at 0x1030 (48 bytes), pow_double at 0x1060 (48 bytes), TOTAL = 144 bytes, THREE separate functions with IDENTICAL logic, ONLY difference = type of result and x, PROBLEM: code duplication, maintenance nightmare
18. WRITE TEMPLATE SYNTAX: `template<typename T> T pow(T x, int n) { T result = 1; for(int i=0; i<n; ++i) result *= x; return result; }`, VERIFY: T appears 4 times (return type, parameter x, variable result, literal 1 converts to T), COMPILER generates pow<int>, pow<float>, pow<double> ON DEMAND at compile-time
19. TRACE INSTANTIATION: pow<int>(2,3) → compiler reads template → substitutes T=int EVERYWHERE → generates `int pow(int x, int n) { int result = 1; ... }` → stores at 0x1000, pow<double>(2.5,3) → substitutes T=double → generates `double pow(double x, int n) { double result = 1; ... }` → stores at 0x1030, SAME source code → DIFFERENT binary functions
20. ■ GROUND: template = single source, multiple binaries, T substituted at compile-time ■ NEXT: calculate large scale ■
21. DRAW TABLE FOR pow(2,10): |i|result|, |0|1|, |1|2|, |2|4|, |3|8|, |4|16|, |5|32|, |6|64|, |7|128|, |8|256|, |9|512|, |10|1024|, VERIFY: 2¹⁰ = 1024 ✓, COUNT multiplications = 10 = n, TIME COMPLEXITY = O(n)
22. DRAW TABLE FOR pow(1.1,10): |i|result|, |0|1.0|, |1|1.1|, |2|1.21|, |3|1.331|, |4|1.4641|, |5|1.61051|, |6|1.771561|, |7|1.9487171|, |8|2.14358881|, |9|2.357947691|, |10|2.5937424601|, VERIFY: compound growth, 1.1¹⁰ ≈ 2.5937 ✓
23. OPTIMIZATION: pow(2,8) by squaring, STEP 1: 2² = 4, STEP 2: 4² = 16, STEP 3: 16² = 256, ONLY 3 multiplications vs 8, FORMULA: x^(2^k) computed in k steps, TIME COMPLEXITY = O(log n), COMPARE: O(n)=8 vs O(log n)=3
24. ■ GROUND: naive O(n), optimized O(log n) via repeated squaring ■ NEXT: instructions to write code ■
25. WRITE CODE: `template<typename T> T pow(T x, int n) { T result = 1; for(int i = 0; i < n; ++i) { result *= x; } return result; }`, TEST: `pow(2, 3)` → expect 8, `pow(2.5, 2)` → expect 6.25, `pow(-3, 3)` → expect -27, `pow(5, 0)` → expect 1, `pow(0, 5)` → expect 0

---FAILURES---
F1. pow(2, -3) → n=-3 → loop condition i<-3 → 0<-3 → ✗ → loop never runs → result=1 → WRONG, expected 2⁻³ = 0.125 → ✗
F2. pow<int>(2.5, 3) → x=2.5 converted to int=2 → pow(2,3)=8 → expected 15.625 → ✗
F3. result=1 (int) for T=float → int × float → float but stored in int → truncation at each step → ✗
F4. pow(2, 100) → 2¹⁰⁰ = 1.27×10³⁰ → int max = 2.1×10⁹ → OVERFLOW → undefined behavior → ✗
F5. pow(0.5, 4) → 0.0625 → works ✓, pow(0.5, 1000) → underflow to 0.0 → precision loss → ⚠

---AXIOMATIC CHECK---
Line 01: Introduced x,n,result,i → derived from function signature `pow(T x, int n)` with T=int
Line 06: Introduced x=2.5 → new example, derived from changing T=double
Line 10: Introduced negative base → new case, derived from sign rules of multiplication
Line 13: Introduced n=0 → edge case, derived from loop condition i<0 being false
Line 17: Introduced memory addresses → derived from compiler placing functions in .text section
Line 18: Introduced template syntax → derived from need to eliminate code duplication in line 17
Line 23: Introduced squaring optimization → derived from observing O(n) is slow for large n in line 21
NO JUMPING AHEAD: Each line builds on previous. Each new concept derived from prior observation.
