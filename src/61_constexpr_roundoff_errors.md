01. MEMORY LAYOUT [Stack/Registers] ----------------------------------------------------
02. | Addr   | Var  | Value (Dec)      | Value (Hex) | Meaning                        |
03. |--------|------|------------------|-------------|--------------------------------|
04. | 0x1000 | sum  | 1.0000000        | 0x3F800000  | Accumulator for e^x            |
05. | 0x1004 | term | 1.0000000        | 0x3F800000  | Current term (x^n / n!)        |
06. | 0x1008 | n    | 0                | 0x00000000  | Loop counter                   |
07. | 0x100C | fact | 1.0              | 0x3F800000  | Factorial accumulator          |
08. ------------------------------------------------------------------------------------
09. 0x1000=1.0000000, 0x1004=0.0000000, 0x1008=1, 0x100C=1 // Init vars: sum, term, n, fact ✓
10. iter₀: n=0 → term=1.0/1=1.0 → sum=0.0+1.0=1.0 → 0x1000=1.0 ✓
11. iter₁: n=1 → fact=1*1=1 → term=1.0/1=1.0 → sum=1.0+1.0=2.0 → 0x1000=2.0 ✓
12. iter₂: n=2 → fact=1*2=2 → term=1.0/2=0.5 → sum=2.0+0.5=2.5 → 0x1000=2.5 ✓
13. iter₃: n=3 → fact=2*3=6 → term=1.0/6≈0.1666667 → sum=2.5+0.1666667=2.6666667 → 0x1000=2.6666667 ✓
14. iter₄: n=4 → fact=6*4=24 → term=1.0/24≈0.0416667 → sum=2.6666667+0.0416667=2.7083334 → 0x1000=2.7083334 ✓
15. iter₅: n=5 → fact=24*5=120 → term=1.0/120≈0.0083333 → sum=2.7083334+0.0083333=2.7166667 → 0x1000=2.7166667 ✓
16. iter₆: n=6 → fact=120*6=720 → term=1.0/720≈0.0013889 → sum=2.7166667+0.0013889=2.7180556 → 0x1000=2.7180556 ✓
17. iter₇: n=7 → fact=720*7=5040 → term=1.0/5040≈0.0001984 → sum=2.7180556+0.0001984=2.7182540 → 0x1000=2.7182540 ✓
18. iter₈: n=8 → fact=5040*8=40320 → term≈2.4801e-5 → sum=2.7182540+0.0000248=2.7182788 → 0x1000=2.7182788 ✗ Precision limits start e-5
19. iter₉: n=9 → fact=40320*9=362880 → term≈2.7557e-6 → sum=2.7182788+0.0000028=2.7182816 → 0x1000=2.7182816 ✗ mantissa crunch
20. iter₁₀: n=10 → fact=3628800 → term≈2.7557e-7 → sum=2.7182816+0.0000003=2.7182819 → 0x1000=2.7182819 ✓
21. iter₁₁: n=11 → fact=39916800 → term≈2.5052e-8 → sum=2.7182819+0.00000002... → float(0x1000) absorbs small term?
22. CHECK: 2.7182819 has 23 mantissa bits → resolution approx 1e-7. Term 2.5e-8 is smaller than resolution?
23. 2.7182819 ≈ 2^1 * 1.359... → exp=1 → ulp = 2^(1-23) = 2^-22 = 2.38e-7.
24. CRITICAL: Term 2.5e-8 < ULP(2.38e-7) → Addition MIGHT be ignored or rounded purely to parity?
25. 2.5e-8 is approx 0.1 * ULP. Round to nearest → No change.
26. ∴ iter₁₁ adds NOTHING to sum in float32? verify manual logic ✗
27. Wait, 2.5e-8 is 0.1 ULP? 2.38e-7 is ULP. 0.5 ULP is 1.19e-7.
28. term < 0.5 ULP → Round to nearest → 0 increment.
29. ∴ sum STOPS changing at n=11 for float32?
30. e_actual = 2.718281828...
31. sum_at_10 = 2.7182819 (slightly high/low?)
32. Run code to verify if loop accumulates noise or stalls.
33. 0x2000: CONSTEXPR_EVALUATION_CONTEXT → Compiler uses MPFR/GMP (high precision)?
34. If compiler uses high precision, it sums exactly then rounds ONCE at end?
35. If compiler mimics float32 steps, it stalls at n=11.
36. QUESTION: Does constexpr mandate "as if executed on target machine" or "mathematically correct"?
37. C++ Standard: Floating point operations in constexpr are implementation-defined but usually IEEE 754.
38. FAIL_PREDICTION: You will think simple summing works, but float absorbs small terms.
39. FAIL_PREDICTION: You will think compiler does perfect math, but it might do float math.
40. DO THIS: Implement `my_e_pow_x` in cpp. Run.
41. DO THIS: Compare `e_runtime` (CPU float add) vs `e_compiletime` (Compiler evaluation).
42. HYPOTHESIS: `e_runtime` stalls at n=11. `e_compiletime` might stalling too OR be more precise.
43. 0x3000: FAILURES → infinite loop if term never zero? No, term becomes denormal then zero.
44. 0x3004: Overflow if fact(n) > FLT_MAX? fact(34) > 3.4e38.
45. n=34 → 34! ≈ 2.95e38. 35! overflow.
46. ∴ Loop must stop before n=35 or handle infinity.
47. 0x4000: Write `my_pow` → strict multiplications.
48. 0x4004: Write `my_fact` → strict multiplications.
49. 0x4008: Loop n=0 to 15. Check `term` magnitude vs `sum` ULP.

---

50. ERROR REPORT -------------------------------------------------------------------------
51. Machine Output: std::e = 0x402DF854, Taylor(15) = 0x402DF855, Matches ✓
52. --------------------------------------------------------------------------------------

53. ERROR E1: Loop index off-by-one confusion ───────────────────────────────────────────
54. LINE: `for (int i = 1; i < terms + 1; i++)` vs `for (int i = 1; i <= terms; i++)`
55. WHAT: Both produce 15 iterations, but brain confused by `< terms + 1` vs `<= terms`
56. WHY SLOPPY: Mixing 0-based and 1-based indexing mental models
57. PREVENTION: Pick one style, stick to it. `i < n` for n iterations starting at 0. `i <= n` for n iterations starting at 1.
58. MISSED: Trace loop manually: i=1,2,...,15 → 15 values → TERMS=15 → correct.

59. ERROR E2: Factorial of 0 edge case ──────────────────────────────────────────────────
60. LINE: `for (int i = 1; i < n + 1; i++)` when n=0
61. WHAT: Loop condition 1 < 1 is false → 0 iterations → returns res=1.0 → 0! = 1 ✓
62. WHY SLOPPY: Did not trace n=0 case before running
63. PREVENTION: Always trace edge cases: n=0, n=1, n=max before coding
64. MISSED: Could have written `if (n == 0) return 1.0f;` for clarity

65. ERROR E3: Float vs int return type for factorial ────────────────────────────────────
66. LINE: `constexpr float my_fact(int n)`
67. WHAT: Returns float, not int. 13! = 6227020800 > INT_MAX = 2147483647.
68. WHY SLOPPY: Assumed int would work, forgot factorial grows fast
69. PREVENTION: Calculate max: 12! = 479001600 < 2^31, 13! overflow. For n>12, need float or long long.
70. MISSED: Could have used uint64_t for exact values up to 20!

71. ERROR E4: NaN generation for n<0 ────────────────────────────────────────────────────
72. LINE: `return 0.0f/0.0f;`
73. WHAT: Generates NaN (0x7FC00000) for invalid input
74. WHY SLOPPY: Did not consider constexpr behavior with NaN
75. PREVENTION: Check if constexpr evaluation allows NaN. GCC allows it.
76. MISSED: Could use std::numeric_limits<float>::quiet_NaN() for clarity

77. ERROR E5: ULP calculation confusion ─────────────────────────────────────────────────
78. LINE: markdown line 23-28
79. WHAT: Calculated ULP = 2^-22 = 2.38e-7, then confused about 0.5 ULP threshold
80. WHY SLOPPY: Forgot that round-to-nearest rounds to NEAREST, not truncates
81. PREVENTION: ULP = 2^(exp-23). For sum=2.718, exp=1 (since 2 ≤ 2.718 < 4). ULP = 2^-22.
82.             Term < 0.5*ULP = 1.19e-7 → rounds to 0 increment.
83.             Term ≥ 0.5*ULP → rounds to 1 ULP increment.
84. MISSED: term at n=10 is 2.76e-7 > ULP, so DOES add. term at n=11 is 2.5e-8 < 0.5*ULP, so ABSORBED.

85. ERROR E6: Assembly loop counter off-by-2 ────────────────────────────────────────────
86. LINE: `cmpl $17, %edx` in .L5
87. WHAT: Loop compares to 17, not 16 or 15
88. WHY SLOPPY: Did not trace assembly loop counter initialization
89. PREVENTION: Trace register values: edx starts at 2, increments to 17, 15 iterations = terms=15 ✓
90. MISSED: edx = 2 initially (not 1), loops while edx < 17, so edx = 2,3,...,16 = 15 values

91. ERROR E7: Assuming pow(1.0, n) optimized away ───────────────────────────────────────
92. LINE: `my_pow(x, i)` in my_e_pow_x
93. WHAT: For x=1.0, my_pow(1.0, n) = 1.0 always, but assembly shows NO separate pow loop
94. WHY SLOPPY: Assumed compiler inlines and optimizes
95. PREVENTION: Check -O2 output. GCC at -O2 knows x=1.0 → x^n = 1.0 → eliminates pow call.
96. MISSED: At -O0, pow loop would exist. At -O2, only factorial loop remains.

97. MACHINE VERIFICATION ─────────────────────────────────────────────────────────────────
98. std::numbers::e_v<float> = 0x402DF854 = 2.7182817459
99. my_e_pow_x(1.0f, 15) = 0x402DF855 = 2.7182819843
100. Difference = 1 ULP = 2.38e-7
101. CONSTEXPR = RUNTIME = 0x402DF855 → Compiler used IEEE float32 semantics ✓
102. Assembly .LC7 = 1076754517 = 0x402DF855 → Constexpr result pre-computed in .rodata ✓
