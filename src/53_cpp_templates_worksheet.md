:01. DRAW INSTANTIATION. `ipow<double>(2.0,3)` → Code at 0x4000. iter₀: result=1.0. iter₁: 1.0×2.0=2.0. iter₂: 2.0×2.0=4.0. iter₃: 4.0×2.0=8.0. Return 8.0. Verify 2³=8 ✓. :02. DRAW INSTANTIATION. `ipow<int>(2,3)` → Code at 0x4030. iter₀: result=1. iter₁: 1×2=2. iter₂: 2×2=4. iter₃: 4×2=8. Return 8. :03. TRAP. `ipow("text",3)` → T=const char*. No operator*=. Compile error. :04. FIX. `template<> string ipow<string>(string x, int n)` → Specialization. Returns concatenated string. :05. DRAW FixedArray<3>. [0x7000]=1.0. [0x7008]=2.0. [0x7010]=3.0. sizeof=24. :06. TRAP RECURSION. `return N + f<N-1>()` → 3→2→1→0→-1→... No base case. Compiler crash. :07. FIX. `if constexpr (N==0) return 0;` → Base case at N=0. :08. F1. Typo `veclovity`. Fix: `velocity`. :09. F2. Typo `sisz_t`. Fix: `size_t`. :10. CONSTANT FOLDING. `f<3>()` → Compiler calculates 3+2+1+0=6 → Assembly: `movl $6, %eax`. No function in binary.
# Templates Worksheet

- Failure 1: Mistaking `auto` deduction for template substitution (Exercise 1/5). You will assume `auto` behaves like `template<T>` but forget implicit conversions or pointer decay logic.
- Failure 2: Incorrect pointer arithmetic (Exercise 1/5). You will forget that `pos[0]` on a pointer `double*` works but `integrated(pos, vel)` decay changes semantics from array reference to pointer copy.
- Failure 3: Ignoring vptr/padding (Exercise 1/3). You will miscalculate struct sizes by forgetting alignment and virtual table pointers if applicable (though not used here directly, implicitly in vectors).
- Failure 4: Overlooking instantiation counts (Exercise 4). You will count source lines instead of unique type combinations.
- Failure 5: String literal type mismatch (Exercise 2). You will expect `"test"` to match `std::string` specialization but it is `const char[5]`.

01. Exercise 1: Syntax Comparison & Memory Layout. Draw memory 0x4000 for `ipow_full<double>(2.0,3)`. [0x4000]=2.0 (8 bytes). [0x4008]=3 (4 bytes). Code size=24 bytes. Write `ipow_full`. Calculate `ipow_abbr<int>(2,3)` at 0x4020. [0x4020]=2 (4 bytes). [0x4024]=3 (4 bytes). Calculate size difference. 0x20 bytes offset. No solution here.
02. Exercise 2: Specialization. Draw `ipow<string>`. Template generic `ipow` fails for string. `s *= s` invalid. Write specialized `template<> ipow<std::string>(string x, int n)`. Return "repeated string". Address 0x6000. Specialization size=20 bytes. Generic size=48 bytes. Reduction=58%. Predict failure `ipow("text", 3)`. "text" is `const char*`. Fail. Fix: `ipow<string>("text", 3)`.
03. Exercise 3: Non-Type Parameters. Draw FixedArray<3,double> at 0x7000. [0x7000]=1.0. [0x7008]=2.0. [0x7010]=3.0. Total 24 bytes. Write `FixedArray` template. Draw `FixedArray<4,int>` stack at 0x7020. Size=16 bytes. Draw `std::vector<int>` heap at 0x8000. Size=24(control)+16(data)=40 bytes. Calculate Stack/Heap size ratio. 16/40=0.4. Calculate cycles. Stack=1. Heap=100. Ratio=100x.
04. Exercise 4: Lambda Template Syntax. Draw lambda at 0x9000. Size=1 byte. Write abbreviated lambda `[](auto x, auto y)`. Write explicit `[]<class T>(T x, U y)`. Calculate instantiations for `lambda(1, 2.0)`. Instantiations=1. Draw memory layout 0x9000. [0x9000]=0x00. Padding=1 byte.
05. Exercise 5: Multiple Parameters Deduction. Draw `integrate(pos, vel)`. `pos` array at 0xA000. `vel` array at 0xA010. Deduction: `pos`=double*, `vel`=float*. Error 0xC0000011. Pointer arithmetic fail. Write `integrate_fixed`. Use `requires std::is_array_v`. Calculate incorrect byte offset if pointer used. 0xA000+0=0xA000.
06. Exercise 6: Compile vs Runtime. Draw `cpp_power(2.0, 3)`. Code at 0xB000. 5 cycles. Draw Python `py_power`. Loop+TypeCheck. 20 cycles. Calculate 1M calls. C++: 1M*5=5M cycles=1.25μs. Python: 1M*20=20M cycles=5μs. Difference=3.75μs.
07. Exercise 7: Error Detection. Draw `process<T>(42)`. Compile error 0xC0000005. Draw Python `process(42)`. Runtime error. Calculate cost savings. Runtime=300(write)+10(run)+600(debug)=910s. Compile=0s. Savings=910s.
08. Exercise 8: Integration Size. List sizes: ipow_full=144, ipow_abbr=144, string=56, FixedArray=24+16, lambda=2. Total=386 bytes. Linker merge duplicates. Remove 144. Final=242 bytes. Calculate 100 libraries footprint. 242*100=24,200 bytes=23.6KB.
// ... (previous content)

# Session Error Report

## Error 1: Infinite Template Recursion
- **Code**: `return N + numIntegers<N-1>();`
- **Result**: Infinite descent 3→2→1→0→-1... Compiler crash (Instantiation Depth Exceeded).
- **Sloppy Brain**: Ignored termination condition. Assumed magic stop.
- **Orthogonal Analysis**: Recursion without base case is essentially `while(true)`. In templates, this is valid code until instantiation, then catastrophic.
- **Fix**: `if constexpr (N==0) return 0;`.
- **Prevention**: ALWAYS write Base Case FIRST.

## Error 2: Dimensional Paralysis
- **Thought**: "impossible to extend a struct... no idea bout array of dimensions".
- **Result**: User gave up before trying. Wasted keystrokes on despair.
- **Sloppy Brain**: Confused "Type Definition" with "Instance Layout".
- **Orthogonal Analysis**: `struct { float x,y,z; }` is rigid. `float v[N]` is fluid. User mental model stuck on rigid named fields.
- **Fix**: `std::array<float, N>`.
- **Prevention**: When "Dimensions" changes, think "Array Size".

## Error 3: Typo Blindness
- **Code**: `veclovity`, `accelration`, `template<sisz_t>`.
- **Result**: Syntax errors. Compiler noise.
- **Sloppy Brain**: Typed faster than thought. Eyes skipped verification.
- **Orthogonal Analysis**: English typos in code = compilation failure. C++ is strict.
- **Fix**: `velocity`, `acceleration`, `size_t`.
- **Prevention**: Read code BACKWARDS to catch typos.

## Error 4: Assembly Misconception
- **Question**: "where is that 6 and where is the numIntegers function"
- **Result**: Confusion why function was empty.
- **Sloppy Brain**: Expected 1:1 mapping of C++ source to Assembly.
- **Orthogonal Analysis**: Templates + Constexpr = Compile Time Execution. Runtime Assembly = Result only.
- **Fix**: Understand "Constant Folding".
- **Prevention**: If inputs are constant, expect NO code, only Immediate Values.
