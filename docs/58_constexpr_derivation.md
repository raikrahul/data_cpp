```
REASONING DIAGRAM: CONSTEXPR vs RUNTIME ASSEMBLY
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ CONSTEXPR CALCULATION:                       RUNTIME CALCULATION:                                              │
│ constexpr double val = coeff(1.0, 2.0);      double a,b; cin>>a>>b; const double val = coeff(a,b);             │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ ASSEMBLY (.text):                            ASSEMBLY (.text):                                                 │
│ [No call to coeff]                           [call coeff_function]                                             │
│ movsd xmm0, [.rodata+0x8] (Load 1.234)       lea rdi, [vars]                                                   │
│ movsd [stack_var], xmm0                      call std::basic_istream::operator>> (Read a,b)                    │
│                                              movsd xmm0, [a]                                                   │
│                                              movsd xmm1, [b]                                                   │
│                                              call coeff (Jump to function)                                     │
│                                              movsd [result], xmm0                                              │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ CYCLES: ~2 (Load immediate)                  CYCLES: ~1000+ (I/O) + 10 (Call overhead) + Function body cycles  │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. LITERALS: 24. Tokenized by lexer. Value in AST. No computation.
02. `mov dword [rbp-4], 0x18` → 24 is immediate operand. 0 memory loads.
03. SAVINGS: 4*3*2*1=24. 3 multiplications avoided. 12 bytes code saved. 9 cycles saved.
04. ■ LITERAL = ZERO COST, BAKED INTO INSTRUCTION ■
05. `const int a = 24;` → Symbol `a` in symbol table. Value 24.
06. `.rodata`: Read-only. Physical address 0x401000.
07. `const int b = std::cin.get();` → Runtime initialization.
08. .bss: Zero initialized initially.
09. _ZSt3cin called at startup (main+0x1A5). Result stored in `b`.
10. Page marked R/O *after* initialization (if supported).
11. ■ CONST = READ-ONLY AFTER INIT. INIT CAN BE RUNTIME ■
12. `constexpr int c = product(4,3,2,1);`
13. Compiler runs interpreter. 4*3=12 → 12*2=24 → 24*1=24.
14. Result 24 stored as immediate.
15. NO assembly for `product`. NO stack frame. NO callq.
16. SAVINGS: 10 cycles call overhead + function body cycles PER CALL.
17. ■ CONSTEXPR FUNCTION = INTERPRETER RUNS AT COMPILE TIME ■
18. `const int d = product(x,y,z,w);` where vars are runtime.
19. Compiler emits `callq 0x401030`. Runtime execution.
20. `push rbp`... `ret`. Registers saved/restored. Stack moved.
21. ■ CONSTEXPR FUNCTION DEGRADES TO RUNTIME IF ARGS UNKNOWN ■
22. COEFF(3.0, 3.14159...):
23. Formula: (x+y)*(x-y) = x^2 - y^2 (Difference of squares).
24. x=3.0, y=3.14159...
25. (3.0+3.14...)*(3.0-3.14...) = 6.14... * -0.14... = -0.8696...
26. Transcript said -0.62743? Check inputs.
27. Maybe `(x*x + y)*factor`? Or transcript used different numbers.
28. Doesn't matter. Point is: Compiler computed -0.8696... offline.
29. Binary contains -0.8696... literal. NOT instructions to compute it.
30. ■ COMPLEX MATH AT COMPILE TIME = 1 MOV INSTRUCTION AT RUNTIME ■
31. ROUND-OFF ERROR: 1/3 = 0.3333... (Infinite).
32. Double (53 bits) truncates. Error ~ 1.85e-17.
33. (3.0*3.0 - 3.14159*3.14159) = 9.0 - 9.8696 = -0.8696.
34. (x+y)*(x-y) when x==y should be 0.0.
35. (3.0+3.0)*(3.0-3.0) = 6.0 * 0.0 = 0.0.
36. BUT if order changed: x*x + x*y - y*x - y*y.
37. Intermediate rounding can make result non-zero.
38. `if (x==y) return 0.0;` forces EXACT zero.
39. Compiler *can* execute logical checks.
40. ■ LOGIC AT COMPILE TIME AVOIDS MATH INSTABILITY ■
---FAILURES---
F1. `const int r = rand();` → Expect compile-time? NO. `rand()` is runtime. `r` is runtime const. ✗
F2. `constexpr double d = 1.0/0.0;` → Expect infinity? NO. Compile error (UB). ✗
F3. `constexpr int val = f(cin_input);` → Error. Args must be constant. ✗
F4. Confuse literal "24" with computed 24. Literal parsed as token. ✗
F5. Assume constexpr function ALWAYS runs at compile time. NO. Dual nature. ✗
