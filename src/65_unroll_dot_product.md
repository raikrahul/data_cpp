01. QUESTION: "for loop is fine" → WRONG. for loop = 3 overhead instructions × N iterations. N=3 → 9 wasted cycles.
02. QUESTION: "compiler will unroll" → WRONG. vec.size() = runtime. Compiler cannot prove size=3 at compile time.
03. QUESTION: "why static?" → You asked after writing code. Should ask BEFORE writing.
04. QUESTION: "can I do without ::" → You do not understand scope resolution. :: = "look inside this class/namespace".

05. ASSEMBLY TRACE (stencil_runtime, -O3):
06.   .L10:
07.     movl (%rsi,%rax,4), %edx      ; load offsets[k]
08.     addl %r8d, %edx               ; idx = i + offset
09.     movslq %edx, %rdx             ; sign extend
10.     movsd (%rdi,%rdx,8), %xmm0    ; load u[idx]
11.     mulsd (%rcx,%rax,8), %xmm0    ; multiply by weights[k]
12.     addq $1, %rax                 ; k++           ← OVERHEAD
13.     addsd %xmm0, %xmm1            ; sum += ...
14.     cmpq %r9, %rax                ; k < size?     ← OVERHEAD
15.     jb .L10                       ; jump back     ← OVERHEAD

16. OVERHEAD COUNT:
17.   addq $1, %rax  = 1 instruction × 3 = 3
18.   cmpq %r9, %rax = 1 instruction × 3 = 3
19.   jb .L10        = 1 instruction × 3 = 3
20.   TOTAL WASTED = 9 instructions

21. WHY STATIC FUNCTION?
22.   static = belongs to class, not object
23.   call: Unroller<3>::run(f)
24.   no object created
25.   no constructor called
26.   no memory allocated
27.   just function call

28. WHY NOT NON-STATIC?
29.   non-static = needs object
30.   call: Unroller<3> obj; obj.run(f);
31.   creates dummy object (0 bytes but still constructor call)
32.   wasteful

33. WHY NOT FREE FUNCTION?
34.   template<int N, typename F> void unroll(F f);
35.   needs base case: template<typename F> void unroll<-1>(F f);
36.   C++ rule: cannot partial-specialize function templates
37.   ∴ free function = ✗

38. CONSTEXPR IF (C++17):
39.   template<int N, typename F>
40.   void unroll(F f) {
41.       if constexpr (N >= 0) {
42.           f(N);
43.           unroll<N-1>(f);
44.       }
45.   }
46.   no struct, no ::, no object
47.   cleanest solution

48. :: OPERATOR:
49.   Unroller<2, F>::run(f)
50.   = enter class Unroller<2, F>
51.   = find member named run
52.   = call it with argument f

53. WITHOUT ::?
54.   Unroller<2, F>.run(f) → needs object instance → error
55.   Unroller<2, F>run(f) → syntax error
56.   run(f) → which run? ambiguous

57. TEMPLATE INSTANTIATION TRACE (N=3):
58.   COMPILE TIME:
59.     Unroller<3,F>::run exists? NO → GENERATE
60.     Unroller<2,F>::run exists? NO → GENERATE
61.     Unroller<1,F>::run exists? NO → GENERATE
62.     Unroller<0,F>::run exists? NO → GENERATE
63.     Unroller<-1,F>::run exists? YES (specialization) → USE
64.   BINARY CONTAINS:
65.     4 distinct functions (inlined to 0)

66. RUNTIME EXECUTION (N=3):
67.   t0: Unroller<3>::run → f(3) → Unroller<2>::run
68.   t1: Unroller<2>::run → f(2) → Unroller<1>::run
69.   t2: Unroller<1>::run → f(1) → Unroller<0>::run
70.   t3: Unroller<0>::run → f(0) → Unroller<-1>::run
71.   t4: Unroller<-1>::run → {} → STOP

72. AFTER INLINING (ACTUAL BINARY):
73.   f(3);
74.   f(2);
75.   f(1);
76.   f(0);
77.   ret;

78. YOUR ERRORS:
79.   E1. Did not trace assembly before making claims about compiler.
80.   E2. Did not understand static vs non-static before writing code.
81.   E3. Asked "why ::" after writing, not before.
82.   E4. Assumed "for loop is ok" without counting instructions.

83. EXERCISES YOU MUST DO:
84.   EX1. Write Unroller using constexpr if (no struct).
85.   EX2. Count instructions in unrolled assembly (compare to loop).
86.   EX3. Trace: What if Unroller<-1> specialization is missing?
87.   EX4. Write non-static version, count constructor calls.

88. NEW ERROR: MISSING TEMPLATE ARGUMENT
89.   WROTE: Unroller<N-1>(f)
90.   NEEDED: Unroller<N-1, F>(f)
91.   Unroller has 2 params: <int N, typename F>
92.   You gave 1, needed 2.
93.   QUESTION: Did you read the template definition before using it?

94. NEW ERROR: MISSING SEMICOLON AFTER STRUCT
95.   WROTE: struct Unroller<-1, F>{ ... }
96.   NEEDED: struct Unroller<-1, F>{ ... };
97.   QUESTION: Did you copy-paste without checking syntax?

98. NEW ERROR: MOST VEXING PARSE
99.   WROTE: UnrollerCtor<N-1, F>(f);
100.  COMPILER: "Declare variable 'f' of type UnrollerCtor<N-1, F>"
101.  EXPECTED: Create temporary object, call constructor with f.
102.  ACTUAL: Variable declaration shadows parameter 'f'.
103.  FIX: UnrollerCtor<N-1, F>{f};  ← braces = unambiguous
104.  QUESTION: Did you know Type(name) can be declaration in C++?

105. PATTERN IN ERRORS:
106.  E1. Missing template arg → Did not count params.
107.  E2. Missing semicolon → Did not proofread.
108.  E3. Most vexing parse → Did not know C++ grammar trap.
109.  ALL 3: Copy-paste without understanding.

110. ORTHOGONAL QUESTION:
111.  You wanted to remove run() for "simplicity".
112.  Constructor version caused 3 bugs.
113.  Static run() version had 0 bugs in original file.
114.  Was removing run() "simpler"?

115. RECURSIVE TEMPLATE INSTANTIATION (HOW COMPILER EXPANDS):
116.   LINE 130 → UnrollerCtor<3, __lambda>{work};
117.   COMPILER: "Need UnrollerCtor<3>. Instantiate it."
118.
119.   STEP 1: Generate UnrollerCtor<3>
120.     struct UnrollerCtor<3, __lambda> {
121.        UnrollerCtor(__lambda f) {
122.           f(3);
123.           UnrollerCtor<2, __lambda>{f};  ← COMPILER SEES THIS
124.        }
125.     };
126.     COMPILER: "Body uses UnrollerCtor<2>. Need that too."
127.
128.   STEP 2: Generate UnrollerCtor<2>
129.     struct UnrollerCtor<2, __lambda> {
130.        UnrollerCtor(__lambda f) {
131.           f(2);
132.           UnrollerCtor<1, __lambda>{f};  ← COMPILER SEES THIS
133.        }
134.     };
135.     COMPILER: "Body uses UnrollerCtor<1>. Need that too."
136.
137.   STEP 3: Generate UnrollerCtor<1>
138.     struct UnrollerCtor<1, __lambda> {
139.        UnrollerCtor(__lambda f) {
140.           f(1);
141.           UnrollerCtor<0, __lambda>{f};  ← COMPILER SEES THIS
142.        }
143.     };
144.
145.   STEP 4: Generate UnrollerCtor<0>
146.     struct UnrollerCtor<0, __lambda> {
147.        UnrollerCtor(__lambda f) {
148.           f(0);
149.           UnrollerCtor<-1, __lambda>{f}; ← COMPILER SEES THIS
150.        }
151.     };
152.
153.   STEP 5: Find UnrollerCtor<-1>
154.     FOUND SPECIALIZATION:
155.     struct UnrollerCtor<-1, __lambda> {
156.        UnrollerCtor(__lambda f) {}  ← EMPTY BODY
157.     };
158.     COMPILER: "Empty body. No more templates. STOP."
159.
160.   CHAIN:
161.     LINE 130 → need <3> → body has <2> → need <2> → body has <1> → ... → <-1> → STOP
162.
163.   INSTANTIATION = COMPILER READS BODY → FINDS TEMPLATE → GENERATES IT
164.   RECURSION = EACH BODY REFERENCES SMALLER N
165.   TERMINATION = SPECIALIZATION <-1> HAS EMPTY BODY
166.
167. FULL DEBUGGER TRACE (26 STEPS):
168.   #01 main() calls dot_unrolled<4>(a,b) @ line 191
169.   #02 sum = 0.0 @ 0x7FF0
170.   #03 work = lambda with &sum=0x7FF0, &a=0x1000, &b=0x1020
171.   #04 UnrollerCtor<3>{work} constructor entered
172.   #05 f(3): a[3]=7.0, b[3]=19.0, 7*19=133, sum=133
173.   #06 UnrollerCtor<2>{work} constructor entered
174.   #07 f(2): a[2]=5.0, b[2]=17.0, 5*17=85, sum=218
175.   #08 UnrollerCtor<1>{work} constructor entered
176.   #09 f(1): a[1]=3.0, b[1]=13.0, 3*13=39, sum=257
177.   #10 UnrollerCtor<0>{work} constructor entered
178.   #11 f(0): a[0]=2.0, b[0]=11.0, 2*11=22, sum=279
179.   #12 UnrollerCtor<-1>{work} constructor entered → EMPTY → return
180.   #13-#17 destructors run (empty, do nothing)
181.   #18 return sum → 279.0 ✓
182.
183. KEY INSIGHT:
184.   sum @ 0x7FF0 NEVER MOVES
185.   lambda.captured_sum_ptr = 0x7FF0 (POINTER TRAVELS)
186.   ALL f(k) CALLS WRITE TO SAME ADDRESS 0x7FF0
187.   ∴ sum accumulates: 0→133→218→257→279

188. NEW ERROR: LAMBDA PARAMETER SYNTAX
189.   WROTE: auto work = [&](<int k>) { ... }
190.   NEEDED: auto work = [&](int k) { ... }
191.   < > = TEMPLATE SYNTAX, NOT FUNCTION PARAMETER
192.   QUESTION: Did you confuse template<int N> with (int k)?

193. NEW ERROR: MISSING std::
194.   WROTE: const array<T, N>& v
195.   NEEDED: const std::array<T, N>& v
196.   QUESTION: Did you assume array is in global namespace?

197. CONFUSION: "SAME LAMBDA IN ALL EXPANSIONS?"
198.   YOU THOUGHT: Different lambda for each template?
199.   REALITY: Same lambda TYPE (F) in all.
200.   F = __lambda_125 = ONE TYPE
201.   N changes (3→2→1→0), F stays same.

202. CONFUSION: "WHO UPDATES sum?"
203.   YOU THOUGHT: sum travels between functions?
204.   REALITY: sum STAYS at 0x7FF0.
205.   POINTER to sum (0x7FF0) travels inside lambda copies.
206.   ALL writes go to *(0x7FF0) = original sum.

207. CONFUSION: "LAMBDA IS COPIED EACH TIME?"
208.   YES. Lambda OBJECT copied (24 bytes).
209.   NO. Pointers INSIDE lambda are same value.
210.   COPY 24 bytes = copy 3 pointers = all point to same sum.

211. CONFUSION: "WHERE ARE EXPANDED FUNCTIONS KEPT?"
212.   YOU THOUGHT: On call stack with constructor?
213.   COMPILE TIME: Functions written to BINARY (.text section).
214.   RUNTIME: Call stack = FRAMES for each function CALL.
215.   BINARY = disk/memory (permanent).
216.   STACK = runtime memory (per call).

217. CONFUSION: "COMPILE-TIME LOOP?"
218.   NO LOOP AT COMPILE TIME.
219.   COMPILER READS constructor body → sees UnrollerCtor<N-1>.
220.   GENERATES that template → reads ITS body → sees UnrollerCtor<N-2>.
221.   RECURSION via template dependency, not loop.

222. CONFUSION: "v IS RUNTIME, HOW CAN UNROLL?"
223.   UNROLL NEEDS: SIZE at compile time.
224.   v VALUES = runtime (can be anything).
225.   v SIZE = N = template param = compile time.
226.   ∴ std::array<T, N> CAN unroll. std::vector CANNOT.

227. PATTERN IN NEW ERRORS:
228.   E1. <int k> vs (int k) → confused template vs function.
229.   E2. array vs std::array → assumed implicit namespace.
230.   E3. "lambda travels" → did not trace pointer arithmetic.
231.   E4. "functions on stack" → confused compile vs runtime.
232.   ALL: Asked AFTER writing code, not BEFORE.

233. ORTHOGONAL QUESTION:
234.   You spent 2 hours on loop unrolling.
235.   Did you verify one single thing by hand BEFORE asking?
236.   Trace = power. Asking = avoidance.
