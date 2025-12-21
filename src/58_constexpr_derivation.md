```
REASONING DIAGRAM: CONSTEXPR DERIVATION
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
01. 0x7FFF0000: int x = 24; // 4*3*2*1 → 4*3=12 (0xC); 12*2=24 (0x18); 24*1=24 (0x18); mov [rbp-4], 0x18; 3 multiplications saved per execution
02. What:24; Why:0; Where:0x7FFF0000; Who:x; When:CompileTime; Without:3_000_000; Which:constexpr
03. Annoying1:TranscriptDiscrepancy: coeff(3.0, Pi) → (3.0+3.141592653589793)=6.141592653589793; (3.0-3.141592653589793)=-0.141592653589793; product=-0.869604401089358; poly(1.0,2.0,3.0,3.0)=1.0*9.0+2.0*3.0+3.0=9.0+6.0+3.0=18.0; potential=17.130395598910642; transcript:-0.62743; error=17.757825598910642 ✗
04. Annoying2:FloatingPointEquality: x=3.0, y=3.0 → coeff=0.0; bits:0x0000000000000000; transcript claims "close to zero but not exactly zero"; contradiction ✗
05. Annoying3:ConstVsConstexpr: const int a=24 → compile-time:true; const int c=scanf() → compile-time:false; constexpr int b=24 → compile-time:forced; difference:diagnostic at line-of-error
06. Annoying4:OverflowScale: product(65536,65535,65534,65533) → 65536*65535=4294901760*65534=281470681784640*65533=18446744073709551615=ULL_MAX; next increment wraps to 0; detection:__builtin_mul_overflow ✗
07. Annoying5:MemoryLayout: constexpr double Pi@0x7FFF0010 → 8 bytes:40 09 21 fb 54 44 2d 18; constexpr double x@0x7FFF0018 → 8 bytes:00 00 00 00 00 00 08 40; constexpr double y@0x7FFF0020 → copy-of-Pi; total:24 bytes; alignment:8; padding:0
08. Annoying6:CallOverhead: constexpr product(4,3,2,1) → inline:0 cycles; runtime version:push rbp+mov rbp+rsp+call+3 imul+mov rax+leave+ret=10 cycles; saved:100%
09. ScaleSmall: N=1 → product=1; ops=0; memory=4 bytes; time=0ns
10. ScaleMid: N=100 → 100*99*98*97=94,109,400; ops=3; memory=4 bytes; time=3ns
11. ScaleLarge: N=1,000,000 → 1e6*999999*999998*999997=9.99994e23; ops=3; memory=8 bytes; time=3ns; result=overflow
12. EdgeCase1: N=0 → empty product=1; mathematical convention; code returns 1 ✓
13. EdgeCase2: N=-1 → factorial undefined; domain error; exception:std::domain_error ✗
14. EdgeCase3: MixedTypes: constexpr int a=24; constexpr double b=a*2.5; 24*2.5=60.0; promotion:static_cast<double>(24)=24.0; result:60.0; size:8 bytes ✓
15. EdgeCase4: RuntimeFallback: product(std::cin(),2,3,4) → constexpr:false; runtime:call instruction; overhead:10 cycles ✓
16. LITERALS: 24. Tokenized by lexer. Value in AST. No computation
17. mov dword [rbp-4], 0x18 → 24 is immediate operand. 0 memory loads
18. SAVINGS: 4*3*2*1=24. 3 multiplications avoided. 12 bytes code saved. 9 cycles saved
19. ■ LITERAL = ZERO COST, BAKED INTO INSTRUCTION ■
20. const int a = 24; → Symbol a in symbol table. Value 24
21. .rodata: Read-only. Physical address 0x401000
22. const int b = std::cin.get(); → Runtime initialization
23. .bss: Zero initialized initially
24. _ZSt3cin called at startup (main+0x1A5). Result stored in b
25. Page marked R/O after initialization (if supported)
26. ■ CONST = READ-ONLY AFTER INIT. INIT CAN BE RUNTIME ■
27. constexpr int c = product(4,3,2,1);
28. Compiler runs interpreter. 4*3=12 → 12*2=24 → 24*1=24
29. Result 24 stored as immediate
30. NO assembly for product. NO stack frame. NO callq
31. SAVINGS: 10 cycles call overhead + function body cycles PER CALL
32. ■ CONSTEXPR FUNCTION = INTERPRETER RUNS AT COMPILE TIME ■
33. const int d = product(x,y,z,w); where vars are runtime
34. Compiler emits callq 0x401030. Runtime execution
35. push rbp... ret. Registers saved/restored. Stack moved
36. ■ CONSTEXPR FUNCTION DEGRADES TO RUNTIME IF ARGS UNKNOWN ■
37. COEFF(3.0, 3.14159...):
38. Formula: (x+y)*(x-y) = x^2 - y^2 (Difference of squares)
39. x=3.0, y=3.14159...
40. (3.0+3.14...)*(3.0-3.14...) = 6.14... * -0.14... = -0.8696...
41. Transcript said -0.62743? Check inputs
42. Maybe (x*x + y)*factor? Or transcript used different numbers
43. Doesn't matter. Point is: Compiler computed -0.8696... offline
44. Binary contains -0.8696... literal. NOT instructions to compute it
45. ■ COMPLEX MATH AT COMPILE TIME = 1 MOV INSTRUCTION AT RUNTIME ■
46. ROUND-OFF ERROR: 1/3 = 0.3333... (Infinite)
47. Double (53 bits) truncates. Error ~ 1.85e-17
48. (3.0*3.0 - 3.14159*3.14159) = 9.0 - 9.8696 = -0.8696
49. (x+y)*(x-y) when x==y should be 0.0
50. (3.0+3.0)*(3.0-3.0) = 6.0 * 0.0 = 0.0
51. BUT if order changed: x*x + x*y - y*x - y*y
52. Intermediate rounding can make result non-zero
53. if (x==y) return 0.0; forces EXACT zero
54. Compiler can execute logical checks
55. ■ LOGIC AT COMPILE TIME AVOIDS MATH INSTABILITY ■
---FAILURES---
F1. StackExhaustion: available=0xFFFF bytes; recursion depth=16383; overflow at depth=16384 ✗
F2. RecursionLimit: GCC=1024; Clang=512; MSVC=2048; exceeding=compiler error: "depth exceeds limit" ✗
F3. FPNondeterminism: constexpr double on x86 vs ARM → different rounding; portable:false; result varies ✗
F4. ODRViolation: constexpr int x=24; in header.hpp without inline → multiple .cpp files → LNK2005; solution: inline constexpr ✗
F5. InitCycle: constexpr int a=b; constexpr int b=a; → compile error: "constant expression contains unreadable variable" ✗
F6. const int r = rand(); → Expect compile-time? NO. rand() is runtime. r is runtime const ✗
F7. constexpr double d = 1.0/0.0; → Expect infinity? NO. Compile error (UB) ✗
F8. constexpr int val = f(cin_input); → Error. Args must be constant ✗
F9. Confuse literal "24" with computed 24. Literal parsed as token ✗
F10. Assume constexpr function ALWAYS runs at compile time. NO. Dual nature ✗

---SESSION ERRORS (2025-12-21)---

E1. movapd misread
What you said: "move a parity decimal"
Reality: MOV Aligned Packed Double
Cause: Guessing acronym instead of reading Intel manual
Prevention: Look up instruction in Intel SDM before guessing

E2. % prefix confusion
What you said: "% means dereference"
Reality: % = AT&T register prefix (not dereference)
Cause: Mixing AT&T and Intel syntax
Prevention: %reg = register, (%reg) = memory dereference

E3. XMM register size confusion
What you said: "64 bits wide"
Reality: 128 bits wide, but scalar double uses 64 bits (lower half)
Cause: Confusing data size with register size
Prevention: Register = container size, Data = content size

E4. constexpr = compile-time ONLY (WRONG)
What you thought: constexpr forbids runtime usage
Reality: constexpr VARIABLE = compile-time only; constexpr FUNCTION = dual mode
Cause: Partial reading of definition
Prevention: Read FULL definition: "constexpr function CAN be evaluated at compile time"

E5. pxor purpose confusion
What you asked: "why XOR after compare"
Reality: XOR prepares 0.0 for x==y case BEFORE branch decision
Cause: Expecting sequential logic, compiler uses speculative preparation
Prevention: Trace instruction flow, not logical flow

E6. Backup confusion
What you asked: "why backup x if compare already done"
Reality: Compare sets FLAGS, backup protects DATA before pxor destroys it
Cause: Confusing flags (metadata) with registers (data)
Prevention: FLAGS = separate from XMM registers

E7. "why so complex" frustration
What you said: "can't you just return if non-zero"
Reality: Compiler optimizes for branch misprediction avoidance
Cause: Not understanding CPU pipeline and speculative execution
Prevention: Learn: conditional prep (3 cycles) < misprediction penalty (15 cycles)

E8. Compiler over-optimization
What emerged: Simple approach often same speed
Reality: Compiler applied generic pattern; may not help this specific case
Lesson: Compilers are not always optimal; measure, don't assume

---ORTHOGONAL QUESTIONS---

Q1. You asked about constexpr after seeing assembly → WHY did you not ask about constexpr BEFORE writing assembly-level code?

Q2. You confused movapd meaning → WHY did you not look up the instruction when first seeing it?

Q3. You thought constexpr = compile-only → WHY did you not test with cin values earlier to discover dual nature?

Q4. You asked "why backup" → WHY did you not trace register contents line-by-line to see pxor destroys %xmm0?

Q5. You got frustrated with complexity → WHY did you not ask "what is the compiler optimizing FOR" before asking "why so complex"?

---ROOT CAUSES---

RC1. Guessing instead of reading documentation
RC2. Partial definitions instead of complete definitions
RC3. Expecting logic flow instead of tracing data flow
RC4. Not tracing register state step-by-step
RC5. Asking "why" before understanding "what"

---PREVENTION CHECKLIST---

[ ] Before guessing acronym → Search Intel SDM
[ ] Before assuming keyword meaning → Read cppreference FULL definition
[ ] Before asking "why" → Trace register state line-by-line
[ ] Before calling something "confusing" → Draw data flow diagram
[ ] Before frustration → Ask "what is the optimization target"
