```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ ipow<double>(2.0,3) at 0x4000: iter₀:1.0 → iter₁:2.0 → iter₂:4.0 → iter₃:8.0 → return 8.0                      │
│ ipow<int>(2,3) at 0x4030: iter₀:1 → iter₁:2 → iter₂:4 → iter₃:8 → return 8                                     │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ FixedArray<3> at 0x7000: |1.0|2.0|3.0| = 24 bytes (stack)                                                       │
│ vector<double> at 0x8000: |ptr→heap|size|cap| + heap[1.0,2.0,3.0] = 24+24 = 48 bytes                           │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. ipow<double>(2.0,3): result=1.0, iter₁:1.0×2.0=2.0, iter₂:2.0×2.0=4.0, iter₃:4.0×2.0=8.0 → 2³=8 ✓
02. ipow<int>(2,3): result=1, iter₁:2, iter₂:4, iter₃:8 → 2³=8 ✓
03. ■ template generates separate code per type at compile-time ■
04. ipow("text",3) → T=const char* → no operator*= → compile error ✓
05. template<> string ipow<string>(string x, int n){...} → specialization for string
06. ■ specialization overrides generic template for specific type ■
07. template<size_t N, typename T> struct FixedArray { T data[N]; }
08. FixedArray<3,double> at 0x7000 = |1.0|2.0|3.0|, sizeof=24 (stack)
09. vector<double> at 0x8000 = |ptr|size|cap|, heap at 0x9000 = |1.0|2.0|3.0|, total=48 bytes
10. ratio: stack/heap = 24/48 = 0.5, fixed array 50% smaller
11. ■ non-type template param N → compile-time size → stack allocation ■
12. auto lambda=[](auto x, auto y){return x+y;} → sizeof=1 (empty)
13. lambda(1,2.0) → operator()<int,double> → 1+2.0=3.0
14. ■ lambda with auto = abbreviated template with multiple params ■
15. integrate(pos,vel) where pos:double*, vel:float* → pointer arithmetic error
16. template requires std::is_array_v → reject pointers
17. ■ use requires clauses to constrain template params ■
18. C++ ipow(2.0,3) → 5 cycles → Python → 20 cycles → ratio=4× slower
19. 1M calls: C++ = 5M cycles = 1.25μs, Python = 20M cycles = 5μs
20. ■ template = native speed per type, Python = interpreter overhead ■
---FAILURES---
F1. ipow<int>("text",3) → "text"→int → compile error → ✗
F2. ipow(2,-3) → negative exponent → result=1 (wrong) → ✗
F3. recursive template without base case → infinite instantiation → compiler crash → ✗
F4. forget sizeof(FixedArray<N>) = N×sizeof(T) → miscalculate stack usage → ✗
F5. assume template = runtime polymorphism → wrong, it's compile-time → ✗
