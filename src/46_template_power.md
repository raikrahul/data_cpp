```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ INPUT: x=2, n=3                                                                                                  │
│ ├─→ result=1 (initial)                                                                                          │
│ ├─→ i=0: result=1×2=2                                                                                           │
│ ├─→ i=1: result=2×2=4                                                                                           │
│ ├─→ i=2: result=4×2=8                                                                                           │
│ ├─→ i=3: 3<3=✗ exit                                                                                             │
│ └─→ OUTPUT: 8 = 2³ ✓                                                                                            │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ MEMORY: pow<int> at 0x1000 (48 bytes), pow<double> at 0x1030 (48 bytes), pow<float> at 0x1060 (48 bytes)        │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. x=2, n=3, result=1, i=0 → i<n → 0<3 → ✓ → result=1×2=2, i=1
02. i=1, result=2 → i<n → 1<3 → ✓ → result=2×2=4, i=2
03. i=2, result=4 → i<n → 2<3 → ✓ → result=4×2=8, i=3
04. i=3, result=8 → i<n → 3<3 → ✗ → exit → return 8 → 2³=8 ✓
05. ■ x=2 n=3 result=8 iterations=3 ■
06. x=2.5, n=2, result=1.0, i=0 → 0<2 → ✓ → result=1.0×2.5=2.5, i=1
07. i=1, result=2.5 → 1<2 → ✓ → result=2.5×2.5=6.25, i=2
08. i=2 → 2<2 → ✗ → exit → return 6.25 → 2.5²=6.25 ✓
09. ■ x=2.5 n=2 result=6.25 ■
10. x=-3, n=3 → iter₁: 1×(-3)=-3, iter₂: (-3)×(-3)=9, iter₃: 9×(-3)=-27 → (-3)³=-27 ✓
11. x=-3, n=2 → iter₁: -3, iter₂: (-3)×(-3)=9 → (-3)²=9 ✓ → odd n → negative, even n → positive
12. ■ sign(xⁿ) = sign(x)^n ■
13. x=5, n=0 → 0<0 → ✗ → loop never runs → result=1 → 5⁰=1 ✓
14. x=0, n=5 → iter₁: 1×0=0 → iter₂-₅: 0×0=0 → 0⁵=0 ✓
15. x=0, n=0 → n=0 → loop never runs → result=1 → 0⁰=1 (code) but undefined (math) ⚠
16. ■ x⁰=1 ∀x, 0ⁿ=0 ∀n>0, 0⁰=⚠ ■
17. pow_int at 0x1000 (48 bytes) + pow_float at 0x1030 (48 bytes) + pow_double at 0x1060 (48 bytes) = 144 bytes, 3 functions, SAME logic, DIFFERENT types
18. template<typename T> T pow(T x, int n) { T result=1; for(int i=0;i<n;++i) result*=x; return result; } → compiler generates pow<int>, pow<float>, pow<double> on demand
19. pow<int>(2,3) → T=int substituted → int pow(int x, int n){int result=1;...} at 0x1000
20. ■ template = 1 source → N binaries at compile-time ■
21. pow(2,10): 1→2→4→8→16→32→64→128→256→512→1024, 10 iterations, O(n)
22. pow(1.1,10): 1.0→1.1→1.21→1.331→1.4641→1.61051→1.771561→1.9487171→2.14358881→2.357947691→2.5937424601 ✓
23. pow(2,8) by squaring: 2²=4, 4²=16, 16²=256, 3 multiplications vs 8, O(log n)
24. ■ O(n) naive, O(log n) squaring ■
---FAILURES---
F1. pow(2,-3) → n=-3 → 0<-3 → ✗ → result=1 → expected 0.125 → ✗
F2. pow<int>(2.5,3) → 2.5→2 → 2³=8 → expected 15.625 → ✗
F3. pow(2,100) → 2¹⁰⁰ > INT_MAX → overflow → ✗
F4. result=1(int) for T=float → truncation → ✗
F5. pow(0.5,1000) → underflow → 0.0 → ⚠
