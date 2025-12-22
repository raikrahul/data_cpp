01. INPUT_DATA → Vector u = {0.0, 1.0, 4.0, 9.0, 16.0} (u(x)=x²) ; N=5 ; grid_spacing(h)=1.0.
02. GOAL → Calculate d²u/dx² at i=2 (u=4.0) using 3-point stencil.
03. STENCIL_DEF → Weights W = {1.0, -2.0, 1.0} ; Offsets O = {-1, 0, +1}.
04. DERIV_CHECK → d²(x²)/dx² = 2.0. Expected Result = 2.0.
05. RUNTIME_LOOP_TRACE →
06.   iter₀: k=0 → offset=O[0]=-1 → idx=2+(-1)=1 → val=u[1]=1.0 → term=1.0*W[0]=1.0*1.0=1.0 → sum=1.0.
07.   iter₁: k=1 → offset=O[1]=0  → idx=2+(0)=2  → val=u[2]=4.0 → term=4.0*W[1]=4.0*-2.0=-8.0 → sum=1.0-8.0=-7.0.
08.   iter₂: k=2 → offset=O[2]=+1 → idx=2+(1)=3  → val=u[3]=9.0 → term=9.0*W[2]=9.0*1.0=9.0 → sum=-7.0+9.0=2.0.
09.   RESULT_RUNTIME → 2.0 ✓. Matches analytical derivative.
10. MEMORY_ACCESS_PATTERN → Read W[0]→Read O[0]→Read u[1] → Read W[1]→Read O[1]→Read u[2] → Read W[2]→Read O[2]→Read u[3].
11. FAILURE_PREDICTION_RUNTIME → Indirect addressing (u[i+O[k]]) causes cache misses if O[k] is large stride. Branch misprediction in loop condition if N varies.
12. RECURSIVE_TEMPLATE_TRACE (N=2) → Goal: Unroll loop for k=2 down to 0.
13.   CALL₀: unroll<2>(func)
14.     → func(2) → executes logic for k=2 (offset=+1, weight=1.0).
15.     → RECURSE: unroll<1>(func).
16.   CALL₁: unroll<1>(func)
17.     → func(1) → executes logic for k=1 (offset=0, weight=-2.0).
18.     → RECURSE: unroll<0>(func).
19.   CALL₂: unroll<0>(func)
20.     → func(0) → executes logic for k=0 (offset=-1, weight=1.0).
21.     → RECURSE: unroll<-1> ??? NO. STOP Condition Needed.
22. TEMPLATE_INSTANTIATION_DEPTH → 3 levels (2, 1, 0). Compiler generates 3 distinct functions? No, typically inlined.
23. INLINED_ASSEMBLY_PREDICTION →
24.   LOAD u[i-1] (direct offset mechanism if O known at compile time? No, O is runtime array here).
25.   FMUL term0
26.   LOAD u[i]
27.   FMUL term1
28.   LOAD u[i+1]
29.   FMUL term2
30.   FADD sum_accum
31.   RET
32. COMPARISON_RUNTIME_VS_COMPILE →
33.   Runtime:  Loop overhead (inc, cmp, jne) + Array lookup overhead (W[k], O[k]).
34.   Unrolled: Straight-line code. Immediate operands if W/O are constexpr? (Not in this task yet).
35.   If W/O are runtime arrays: Compiler removes loop structure but still does array lookups.
36.   Optimization: If O/W were template params, instructions would be `MOV result, [ptr - 8] * 1.0 + [ptr] * -2.0 ...`.
37. EXERCISE_USER_1 → Calculate 5-point stencil on u(x)=x³ at i=3?
38.   u={0,1,8,27,64,125,216}. i=3 (27). Weights={-1,16,-30,16,-1}/12.
39.   Offsets={-2,-1,0,1,2}.
40.   Terms needed: u[1], u[2], u[3], u[4], u[5] → 1, 8, 27, 64, 125.
41.   Calculate by hand in code comments.
42. PREDICT_FAILURE_FLOATING_POINT →
43.   Is (1.0 + 1e-16) - 1.0 == 1e-16? Maybe 0.
44.   Stencil sums involve subtracting large numbers (cancellation error).
45.   Example: (-2.0*u[i]) + (u[i-1]+u[i+1]).  If u is large, variance is small, precision loss occurs.
46.   CHECK: u=10^9, result=2.  (10^9 - 2*10^9 + 10^9) = 0?
47.   Double precision has 53 bits sig (~15 digits). 10^9 is safe. 10^16 is dangerous.
