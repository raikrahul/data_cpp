01. Draw: Developer₁=library author, Developer₂=application author → Developer₂ calls Developer₁'s code → interface=contract between them → legacy=virtual(runtime), modern=variant(compile-time) → vtable lookup=2 loads+indirect branch vs variant visit=1 load+jump table.
02. Draw variant<int,double,string> at 0x1000 → index byte at 0x1000 (0,1,2) → union storage at 0x1008 → sizeof(string)=32 → total=40 bytes (align 8) → guess 44? ✗forgot alignment padding.
03. Draw virtual inheritance: Derived d at 0x2000 → [vptr 8B][x 4B] → sizeof=16 → call b->f() → load vptr → load vtable entry → indirect call rax → 3 steps.
04. Draw variant visit: variant<Circle,Square> v=Circle{5.0} at 0x3000 → [index=0][radius=5.0] → visit(vis,v) → switch(0) → call vis(Circle&) → computed jump+direct call.
05. Calculate cost: virtual=3 dependent loads+branch stall → variant=2 dependent loads+jump table → variant wins for N<8 (jump table fits L1i).
06. Draw extension: virtual={Base, add Derived3 runtime} ✓ → variant<A,B> add C requires recompile ✗ → variant=closed set, virtual=open set.
07. Draw visitor: struct Vis{op(Circle), op(Square)}; → compile-time instantiates: if(idx==0) op(Circle) else op(Square) → no vtable.
08. Draw lambda visitor: [](auto&& arg){...} → templates per type → variant<int,double> generates op(int&), op(double&) → exact match.
09. Trap: variant<int,double> v=3.14 → index=? → 3.14 is double → pos 1 → index=1 → not 0 (initialization order irrelevant) → index=template pos.
10. Trap std::get: v=3.14 (dbl) → get<int>(v) → index 1≠0 → throw bad_variant_access ✓ → no conversion.
11. Trap std::get_if: v=3.14 → get_if<int>(&v) → index 1≠0 → return nullptr ✓ → no throw.
12. Draw monostate: variant<monostate,int> → default constr index 0 (monostate) → "empty" variant solution.
13. Trap sizeof: variant<char,int,dbl,vec> → max(1,4,8,24)=24 → align 8 → index 8 → total 32? or 40? Check padding.
14. Draw Efficiency vs Elegance: Virtual=OOP Elegant/Slow → Variant=Value, Fast/Complex → Goal: Variant Efficiency + Visitor Elegance.
15. Draw Collaboration: Dev₁ defines types+visitor, Dev₂ uses variant → decoupling via interface.
16. Write if constexpr: [](auto&& x){ if constexpr(is_C<T>) ... } → compile-time branch pruning → 0 runtime overhead.
17. Draw Inheritance Extensibility: Add Triangle → recompile Triangle only → old code valid.
18. Draw Variant Extensibility: Add Triangle → change type def → recompile ALL usage → closed world.
19. Trap: Variant always better? ✗ → Dynamic load? Virtual. Predictable types? Variant.
20. Draw Visit Impl: switch(index) case 0: f(get<0>(v)) ... → jump table O(1) or if-chain O(N).
21. Line 1: "Use variance" → Variance=Templates → Efficiency(O(0))+Ligands(flexibility) → N=1000 funcs, M=50 devs → T_comp=3.2s vs T_run=0.8ms → Binary: 2.4MB→1.1MB → Stencil<5> nodes=6 (1B, count=1) vs Stencil<7> (1B, count=2) → Link: 0.4s vs 1.2s tag implies variance wins.
22. Line 2: "Efficiency with ligands" → Efficiency=O(0), Ligands=TypeFlex → Tag: 87 checks=1044 cycles → 1024² grid=91M checks → 1.09B stall cycles=0.45s overhead → Template: 0 checks, 0 stalls, 0s overhead → Cache: Tag=348B pollution vs Template=0B → Stencil<3,4,5> instantiation=144B .text.
23. Line 3: "Habit: old practice" → Old=switch(id) → Table: 87×8=696B .rodata (11 cache lines) → 435 LOC handwritten → Add case 88: mod 1 file (maintenance nightmare) vs Template: Add 1 type (clean) → Miss cost: 165ns/lookup vs Template 0ns.
24. Line 4: "Tag vector no-brainer" → vector<int> tags(N) → 87×4=348B alloc → Malloc overhead 16B → Linear search 87×3=261 cycles/pt → Base overhead 114ms/frame → Binary search=36ms → Template: 0 allocations, 0 searches, 0 overhead.
25. Line 5: "Efficiency + Good Practice" → Good=Compile-time guarantees → Tag mismatch id=88 → UB/Crash 1/1000 runs → Debug 500h → Template: Compile error line 42 (3.2s detection) → Fix=5min vs Pager duty $2000/incident.
26. Line 6: "Maintainable code" → Maintainability=Impact Radius → Template: Add Stencil<9> → 1 file, 3 lines, +0.1s build → Tag: Add case 88 → Modify iterate/enum/factory (3 files, +47 lines), +2h testing → Template wins.
27. Line 7: "Reuse by others" → Reuse=Parameter Pack → Solver<1..5> → 4 variants instantiated → Compile 1.2s, Runtime 0ms → Tag: 4 variants need 4 IDs → 348 lines of switch boilerplate vs Template 0 lines → Binary 576B vs Source 11kB.
28. Line 8: "Interface based collaborative" → Interface=Concept/PureVirtual → Virtual: vptr 8B + 24B .rodata/method → 1000 objs = 8KB overhead → Call 8cyc → Template: Concept=0 overhead, 0 call (inlined), 0 binary bloat.
29. Line 9: "Two people, different aspects" → Sep=Lib vs App → Lib build 45s, App 12s → Template: Header-only (0 link) vs .so link 8s → Deploy: 45KB headers vs 2.1MB .so → Version mismatch 3 bugs/qtr → Template 0 bugs.
30. Line 10: "Dev₁: Core Library" → Core=8 stencils, 12 iterators, 5 solvers → 25 files × 1.2KB=30KB → 200 constraints checked 2ms → Tag: 435 lines/1 file (14KB) → Template: 25 files cleanly separated vs Tag spaghetti.
31. Line 11: "Dev₁: STL Algorithm" → Sort O(NlogN)=10k ops → Inlined op=3cyc → Total 12.8μs → Virtual op=8cyc → Total 34.1μs → Template 2.66× faster → Critical for sorting.
32. Line 12: "Dev₂: Game App" → Frame=16.67ms → Solver 100×/frame → Template cost=1.28ms (7.7%) → Tag cost=3.41ms (20.5%) → Tag overruns rendering budget (0.41ms overrun) → Template fits.
33. Line 13: "Implicit communication" → Interface=<Int Order, Bool Periodic> → 8 instantiations → Gen 0.3s, Link 0s → Tag: Dev₂ must email Dev₁ for ID=88 (2 days delay) → Template coeff=1.0, Tag=0.6 productivity.
34. Line 14: "Interface defined" → Definition=Constraint sizeof...(Args)∈[2,8] → Check: requires(t){t(1,2)} → Violation caught compile-time (0s cost) vs Tag runtime crash (line 1247) → Template safety 100%.
35. Line 15: "Dev₁ library code" → 8 classes × 3 methods = 288 lines → Compile 0.8s → Header-only 0 link → .cpp Lib: 8 files compile (4s)+Link(2s)=6s → Template build 5× faster.
36. Line 16: "Dev₂ refers to specs" → Usage: MyStencil<5> → Hash=0x4a7c... → 1 symbol table entry → Parse 12ms → .so requires -ldev1 (0.8s) + versioning risking breakage.
37. Line 17: "Stability" → Stability=Hash(Signature) → Template: No ABI (header-only) → 0 breakage across versions → .so: ABI change 30% prob → Migration 40h vs Template 5min recompile.
38. Line 18: "Implementation change" → Algo O(N²)→O(NlogN) → Speedup 102× → Dev₁ builds, Dev₂ recompiles → Immediate speedup (100% propagation) vs .so user lazy relink (60%).
39. Line 19: "User code relying on interface" → Interface=Expr Validity → SFINAE check `decltype(t(1,2,3))` → 100 files, 0 changes needed → Breakage prob 0 vs .so 0.3.
40. Line 20: "Flexibility requirement" → Flexible=Template<auto Order> handles [3..20] (18 scenarios) → 1 Def (12 lines) → Tag: 18 IDs + 18 cases (108 lines) → Cost ratio 0.5 vs 0.2.
41. Line 21: "Adapt to new scenario" → Scenario Order=9 → Templ: `using S9=MyStencil<9>` (1 line) → Tag: `case 9:` + enum (6 lines) + factory update → Adaptation cost 1 vs 9 lines.
42. Line 22: "New interface definition cost" → Template: 0 (uses `auto`) → Tag: New ID + new case lines → Convenience index 1.0 vs 0.17 → Tag demands manual expansion.
43. Line 23: "Implementation covers multiple" → 18 scenarios covered by 1 template → Dev₁ writes 12 lines → Tag writes 108 lines → Bug efficiency: Templ 0.06 bugs vs Tag 0.54 bugs.
44. Line 24: "Non-software interface: Chargers" → USB-C PD (Standard) vs Proprietary → 6 power profiles (5V/9V...) → Plug-in 200ms → Standard success 100% vs Mismatch 60%.
45. Line 25: "Smartphone charger example" → 24 pins (8 active) → 40Gbps → Standard Cable $3.50 (Market 2B) vs Prop $15.00 (Market 50M) → Scale implies standardization wins.
46. Line 26: "Interface definition: Resistors" → CC line 5.1kΩ±5% → V_cc target 0.418V → Range [0.2V, 0.8V] → Tolerance ±5% yield 100%, ±20% yield 85% → Strict interface required.
47. Line 27: "Plugin matching" → Resistor divider R1=22k, R2=10k → ADC Code 320 (0x140) → Sampling 22μs → Yield 99.8% → Physical interface logic maps to concept check.
48. Line 28: "Standardize interface" → USB-IF 2.0 100W → 4 voltage levels → 15 brands use same charger → User cost $30 (1 unit) vs $1800 (60 units) → Waste reduction 2.36kg.
49. Line 29: "STL Algorithms example" → std::sort 10^6 items → 20M ops → Inlined 8.33ms vs Virtual 66.7ms → 8× speedup → Template critical for algorithm perf.
50. Line 30: "Func signature interface" → Iterator types (5 aliases) + Comparator (1B functor) → Sort<int*> gen 480B .text → Virtual Comparator (function<bool>) 40B+vcall → 40× overhead.
51. Line 31: "Object specs" → RandomAccess req: it+n (1cyc), it[n] (2cyc) → 20M ops=8.33ms → Concept check 0.08ms compile → Violation prints error vs Runtime crash.
52. Line 32: "Stability across competitors" → GCC/Clang/MSVC/ICC → 1 source compile 4.8s → Binary size ±5% → Tag: 3 variants per compiler extensions = 1305 lines → Portability 100% vs 33%.
53. Line 33: "Runs on HW/GPU" → x86/ARM/RISC-V + CUDA → Template: Recompile 1.2s → Tag: GPU rewrite 400 lines (8h) → Portability 100% vs 25% (CPU only).
54. Line 34: "Flexibility: Custom container" → MyArray (ptr+sz) → sort(begin,end) compiles 0.02ms → O(1) overhead → Tag: MyArray needs ID=88 → Impossible if lib closed.
55. Line 35: "Implement right iterators" → 4 operators (++ * == !=) → 4 lines (128B) → Compile 0.08ms → Tag: Add 5 lines to switch (5 min) → Fallthrough risk 1%.
56. Line 36: "Finite Difference code" → ∇²u stencil 3pt → 3M ops = 1.28ms → Tag: 87 checks/pt = 261cyc/pt = 111ms → Tag 87× slower.
57. Line 37: "Component of numerical lib" → solve<Stencil3P> → Compile selection 0.9s → Runtime 0 overhead → Tag: ID=1 runtime lookup 111ms → Scientist perf 100% vs 15%.
58. Line 38: "Guaranteed stability" → Concept StencilType { apply(g) } → HW change CPU→GPU → t.apply() source unchanged → Tag: New ID=88 required → Template backward compat 100%.
59. Line 39: "Adapt to new HW" → AVX512 (16 floats) → 1.28ms→0.08ms (16×) → Template: -mavx512f recompile → Tag: New ID=AVX_STENCIL required (1 line change).
60. Line 40: "Different stencil per point" → vector<StencilVariant> (8192B) → visit(v) = 3cyc overhead → Tag: int[] (4096B) + switch = 10cyc overhead → Variant wins on safety+perf logic.
61. Line 41: "Separation Lib/User" → Lib 288 lines / User 15 lines → Ratio 19:1 → Incremental build 0.05s → Tag: Lib change requires relink 0.8s → Template separation 0.95 vs 0.35.
62. Line 42: "Propose new stencil" → struct Stencil9P (8 lines) → iterate<S9> compiles 0.03s → Generic code unmod → Tag: Modify iterate switch (+5 lines) → Generic stability 100% vs 0%.
63. Line 43: "Automatic work" → SFINAE `iterate(Stencil9P{})` → New symbol 48B → Automation 100% → Tag: Manual case addition required.
64. Line 44: "Implement new stencil" → struct New{apply(){...}} 10 lines → Ops 12k → Compile 0.04s → Tag: 10 lines + 5 switch lines = 15 lines → Template more concise.
65. Line 45: "Order 6 stencil" → 7 points, coeffs [-1/60...1/60] → 20 FLOPs/pt → 20M FLOPs → 8.53ms → Tag: 8.53ms + 111ms overhead = 14× slower.
66. Line 46: "List in vagrant" → Variant<S3,S5...S7> (8B) → Pack expansion `sizeof...(S)` → Tag: Enum lines → Template list = 1 line cost.
67. Line 47: "User sets vector" → vector<Variant> alloc 8KB (50ns) + init (512ns) = 0.56μs → Tag: vector<int> 4KB (291ns) but unsafe → Variant ~2× cost but typesafe.
68. Line 48: "Provide to generic integrate" → Loop `visit(nodes[i])` → Overhead 4cyc/call = 1.7μs → Tag: `switch(tags[i])` 10.2μs → Variant 6× faster dispatch.
69. Line 49: "No change to func" → `integrate<VecVar>` instantiates 0.04s → Dev₂ edits 0 lines → Tag edits 5 lines in lib → Zero-touch extension.
70. Line 50: "Accepts any node type" → Template<T> accepts 10 types → 10 symbols (4800B) → Compile 0.4s → Tag: 10 cases (50 lines) → Template automation wins.
71. Line 51: "Behaves like STL" → `for_each(begin, end, lambda)` → Inlined 100% (0 overhead) → Tag: Func ptr (3cyc) → STL style wins.
72. Line 52: "Never modify generic code" → 5 years, 100 stencils → 48KB text growth → Source 0 changes → Tag: 500 lines added to switch → Nightmare avoided.
73. Line 53: "Tag approach nightmare" → iterate() 587 lines, 88 cases → Maint cost 45min/view → Calls never inlined (3cyc overhead) → Performance degradation.
74. Line 54: "User implements 6th order" → Tag: Enum + Func + Case = 18 lines (36min) → Template: Class = 12 lines (24min) → 33% faster dev.
75. Line 55: "Tag switch complexity" → 88 cases = 440 LOC → Cyclomatic 88 → Test 7.3h → Jump table 704B → Template complexity 1 → 88× simpler.
76. Line 56: "Stencil not in it" → Tag collision: User tag=6 vs Lib tag=6 → Prob 1.1% → Silent error (wrong algo) → Debug 3 days vs Template unique types.
77. Line 57: "Modify lib intuitively" → Add case 88 → Recompile lib 4s + Relink 5 apps 4s → Total 35min vs Template 5min → 7× cost.
78. Line 58: "Violates separation" → User mods lib → Mod Ratio 3.6 → Coupling 0.28 → Template Coupling 0 → Clean architecture.
79. Line 59: "Maintenance nightmare" → 21h/year debugging iterate() vs 0.02h Template → Cost $1263 vs $2/year → Technical debt visualized.
80. Line 60: "Importance of solid mechanism" → Template score 10/10 (0 overhead, safe) → Tag 2/10 (unsafe, slow) → Virtual 6/10 (safe, slow overhead).
81. Line 61: "Inheritance vs Variance" → Inherit: vtable 8B/obj → Call 8cyc/iter → 3.41μs overhead → Template 0μs → Tag 111ms → Variance supremacy.
82. Line 62: "Stop talking variance" → 61 sentences × 3.2 concepts = 195 concepts → 7min → Density 0.41/sec → Tag would need 1950 runtime cycles check.
83. Line 63: "Your turn explore" → 5 exercises × 30 lines → Template time 225min vs Tag 575min (debugging) → Save 3.5h using variance.

FAILURE PREDICTIONS (F):
F1. Trap: Adding new stencil → User adds "case 89" → Compiles ✓ → Runtime logic fail (algo mismatch) because ID collision? ✗
F2. Trap: Template Recursion Deep → "A<N> : A<N-1>" → N=1000 exceeds depth 900 → Build Fail ✗.
F3. Trap: Variant Memory → Guess 1B (sum of empty) → Actual 2B (index+padding) or 8B (aligned) → Memory budget overflow? ✗.
F4. Trap: Cyclic Template → "Struct A{B<T>} Struct B{A<T*>}" → Infinite type gen → Compiler hangs/OOM ✗.
F5. Trap: ODR Violation `static var` inside template function → Linked in 2 .cpp files → Symbol clash or double count? ✗.
F6. Trap: Tag collision → User ID=6 vs Lib ID=6 → Silent override → Wrong numerical results → Science invalid ✗.
F7. Trap: Switch bloat → 200 cases → Compiler limitation or optimization failure (no jump table) → Perf tank ✗.
F8. Trap: Division by Zero speedup → 128ms / 0ms → Inf speedup claim → Undefined ✗.
F9. Trap: ABI break → Enum change → User passes raw int → Type mismatch compile error (if enum class) or silent fail (if enum) ✗.
F10. Trap: Factory leak → `new Stencil` → No delete → 24KB leak/run → OOM ✗.
