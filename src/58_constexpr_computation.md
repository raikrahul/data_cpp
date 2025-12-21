```
REASONING DIAGRAM: CONSTANT vs LITERAL vs RUNTIME CONSTANT 
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ CODE:                 MEMORY (Assembly .rodata or Stack)              CPU EXECUTION (Runtime)                   │
│ 1. 24 (Literal)    →  .text: movl $24, %eax (Immediate)            →  CPU loads 24 directly. No memory read.    │
│ 2. const int a=24  →  .text: movl $24, %eax (Optimized out)        →  Compiler replaces 'a' with '24'.          │
│ 3. cin >> k;       →  Stack: [ k ] (Address 0x7FFF...)             →  User types 24. CPU stores 24 at address.  │
│ 4. const int b=k   →  Stack: [ b ] (Address 0x7FFF...)             →  CPU copies k to b. READ ONLY FLAG set.    │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
WHY: Distinct concepts often confused:
1. LITERAL is raw data in source code. Compiler knows it INSTANTLY.
2. CONST AT COMPILE TIME (constexpr) is calculated by COMPILER. CPU sees only result.
3. CONST AT RUNTIME (const) is calculated by CPU, then CPU promises not to change it.
```
01. LITERAL: 24. It is data typed in source. Compiler sees "24".
02. COMPILER: "I know 24 is 24. I don't need CPU to figure that out."
03. ASSEMBLER: `mov $24, %eax`. 24 is EMBEDDED in instruction.
04. ■ LITERAL = KNOWN BY COMPILER INSTANTLY ■
05. const int a = 24; Compiler sees `a` is 24.
06. USAGE: `int b = a + 1;` Compiler computes 24+1=25. Emits `mov $25, %ebx`.
07. `a` memory storage? OPTIMIZED OUT. exists only in compiler's mind.
08. ■ COMPILE TIME CONSTANT = REPLACED BY VALUE ■
09. cin >> k; User input. Compiler DOES NOT KNOW `k`.
10. const int b = k; Compiler knows `b` will imply `k`. But `k` unknown.
11. RUNTIME: CPU pauses. User types 42. CPU writes 42 to `k`.
12. CPU copies `k` to `b`. `b` is 42.
13. `const` on `b` means: "Programmer promises not to write `b = 0` later".
14. MEMORY: `b` LIVES on stack. `b` occupies RAM. `b` is FETCHED.
15. ■ RUNTIME CONSTANT = READ-ONLY VARIABLE IN RAM ■
16. CONFUSION: `const` means "Run-Time Read-Only". `constexpr` means "Compile-Time Known".
17. `const int x = 5;` is implicitly `constexpr`.
18. `const int y = cin_input;` is NOT `constexpr`.
19. ■ constexpr = MUST be known by compiler. const = CAN be known by CPU only. ■

```
REASONING DIAGRAM: CONSTEXPR FUNCTION DUALITY
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ SOURCE: constexpr int f(int x) { return x * 2; }                                                                │
│ CALL 1: constexpr int A = f(10);           CALL 2: int v; cin >> v; int B = f(v);                               │
│ ├─ Compiler: Input 10 is known.            ├─ Compiler: Input 'v' is unknown.                                   │
│ ├─ Compiler: Execs f(10) internally.       ├─ Compiler: Emits CALL instruction to f.                            │
│ ├─ Compiler: Result 20 replaces call.      ├─ CPU: Jumps to f, computes v*2, Returns.                           │
│ └─ ASM: movl $20, memory_of_A            └─ ASM: call _Z1fi                                                   │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
WHY: One function, two lives.
1. IF args are known (literals) AND result assigned to constexpr -> COMPILER EXECUTES.
2. IF args are unknown (user input) OR result assigned to runtime var -> CPU EXECUTES.
```
20. `constexpr int f(int x) { return x * 2; }`
21. CALL 1: `constexpr int val = f(5);`
22. ARG: 5 (Literal). Context: `constexpr` variable.
23. ACTION: Compiler runs `f(5)`. Returns 10. Code becomes `int val = 10;`.
24. CALL 2: `int runtime_val; cin >> runtime_val; int val2 = f(runtime_val);`
25. ARG: `runtime_val`. UNKNOWN at compile time.
26. ACTION: Compiler generates assembly `call f`. CPU runs it later.
27. SURPRISE: `constexpr` function is a NORMAL function that CAN run at compile time.
28. ■ constexpr function = "Compile-time CAPABLE" ■
29. TRAP: `constexpr int k = f(runtime_val);`
30. FAIL: Variable `k` MUST be compile-time. Function `f` forced to runtime. CONTRADICTION.
31. COMPILER ERROR: "expression must have a constant value". ✗
32. ■ constexpr variable forces compile-time. If inputs runtime -> ERROR ■

```
REASONING DIAGRAM: FLOATING POINT CONSTEXPR
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ FORMULA: (x*x + y)*1.0/3.0    Input: x=3.0, y=3.0                                                               │
│ MATH: (9+3)/3 = 4.0 EXACTLY.                                                                                    │
│ IEEE754: 1.0/3.0 = 0.3333333333333333 (Infinite series truncated)                                               │
│ CALC: 12 * 0.3333333333333333 = 3.9999999999999996                                                              │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ IF (x==y) return 0.0; CONDITION CHECK                                                                           │
│ COMPILER: Checks 3.0 == 3.0? TRUE.                                                                              │
│ COMPILER: Returns 0.0 (Exact).                                                                                  │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
WHY: Compile-time float match mimics Runtime float math.
1. Compiler uses SAME float logic as CPU (usually).
2. Round-off errors happen inside compiler too!
3. Conditions can bypass round-off by returning literals.
```
33. `coeff(3.0, 3.0)` formula: `(3*3+3)*(1.0/3.0)`
34. 1.0/3.0 is NOT 1/3. It is `0x3FD5555555555555`.
35. 12.0 * `0x3FD5555555555555` = `3.9999...96`.
36. Result is `3.9999...96`. NOT 4.0.
37. This is "Round-Off Error".
38. TRICK: `if (x == y) return 0.0;`
39. Compiler evaluates `if (3.0 == 3.0)`. True.
40. Compiler returns 0.0.
41. 0.0 is EXACT. No round-off.
42. ■ Optimizing conditions allow skipping unstable math ■
43. Compile-time math is NOT infinitely precise. It is IEEE754.
44. Round-off errors happen AT COMPILE TIME just like runtime.
45. ■ Compiler simulation matches CPU execution bit-for-bit ■

```
REASONING DIAGRAM: PRE-COMPUTE WORKFLOW
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ OLD WAY (2-Step):                                                                                               │
│ 1. Engineer opens Excel. Types formula. Drag-fills range.                                                       │
│ 2. Engineer acts as "Compiler". Copies Excel table. Pastes `const double table[] = { ... }` into C++.           │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ NEW WAY (constexpr):                                                                                            │
│ 1. Engineer types formula into `constexpr` C++ function.                                                        │
│ 2. Engineer writes `constexpr double table[] = { f(0), f(1)... };`                                              │
│ 3. C++ Compiler acts as "Excel". Computes values. Writes table into binary.                                     │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
WHY: Removes human "Copy-Paste" step.
1. No stale data (Source of truth is code, not lost Excel file).
2. Compiler verification (Type checking on formula).
```
46. 2-Step procedure: Calculate offline (Excel/Python) → Paste to C++.
47. DANGER: Update formula in Excel? Forget to update C++. Result: BUG.
48. `constexpr`: Formula is IN CODE.
49. `constexpr double val = f(inputs);`
50. Compiler compiles → Calculates val.
51. User changes formula? Re-compile. Value updates AUTOMATICALLY.
52. ■ constexpr eliminates "Stale Data" bugs ■
53. SEPARATION:
54. `main` runs at runtime.
55. `constexpr` vars run at compile-time.
56. Code is MIXED in file, but SEPARATED in time.
57. ■ Same Syntax, Different Time Dimension ■

---FAILURES---
F1. `const int k = cin >> val;` → Expect compile-time? NO. `const` is just "Do Not Touch". Runtime read-only. ✗
F2. `constexpr int f(int x) { ... }` → `constexpr` function MUST result in constant? NO. Only if args are constant. ✗
F3. `if (3.0 * (1.0/3.0) == 1.0)` → Expect true? NO. Float logic applies. ✗
F4. `constexpr void f() {}` → Void constexpr useful? Only C++20. Pre-C++14 `constexpr` very limited (one return). ✗
F5. `call f(runtime)` where f is `constexpr` → Expect compile error? NO. Degrades to runtime call silently. ⚠
