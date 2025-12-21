```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ struct S1 { char a; int b; char c; }                                                                            │
│ MEMORY: |a:1|pad:3|b:4|c:1|pad:3| = 12 bytes, waste=6 (50%)                                                     │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ struct S2 { int b; char a; char c; }  REORDERED                                                                 │
│ MEMORY: |b:4|a:1|c:1|pad:2| = 8 bytes, waste=2 (25%), savings=33%                                               │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. struct S1 { char a; int b; char c; } → a at 0 (1), pad 3 (align b to 4), b at 4 (4), c at 8 (1), pad 3 → sizeof=12
02. waste = 6/12 = 50% ✗
03. struct S2 { int b; char a; char c; } → b at 0 (4), a at 4 (1), c at 5 (1), pad 2 → sizeof=8
04. waste = 2/8 = 25%, savings = 12-8 = 4 bytes = 33% ✓
05. ■ RULE: order by size descending → minimize padding ■
06. struct S3 { char a; double b; char c; } → a at 0 (1), pad 7, b at 8 (8), c at 16 (1), pad 7 → sizeof=24, waste=14 (58%)
07. struct S4 { double b; char a; char c; } → b at 0 (8), a at 8 (1), c at 9 (1), pad 6 → sizeof=16, savings=8 (33%)
08. ■ alignof(struct) = max(alignof(members)) ■
09. struct vs class: ONLY default access differs (public vs private), sizeof identical
10. class D { public: int x; private: int y; } → layout: x at 0, y at 4, sizeof=8, access specifiers don't affect layout
11. ■ access specifiers = compile-time only, no runtime cost ■
12. class V { virtual void f(); int x; } → vptr at 0 (8), x at 8 (4), pad 4 → sizeof=16, overhead=8 for virtual
13. ■ virtual adds 8-byte vptr at offset 0 ■
14. struct P { int a; int b; }; P p; → a,b UNINITIALIZED (garbage)
15. P p{}; → a=0, b=0 (value init)
16. struct Q { int a=5; int b; }; Q q; → a=5 (default), b=garbage
17. Q q{}; → a=5, b=0
18. ■ {} = value init (zeros), no {} = default init (maybe garbage) ■
19. struct R { int a; int b; R():a(10),b(20){} }; R r; → a=10, b=20
20. struct T { int a; int b; T():b(1),a(b){} }; → WARNING: a initialized before b (declaration order), a=garbage
21. ■ init order = declaration order, NOT constructor list order ■
22. struct A { int x; int y; }; A a={1,2} → x=1, y=2; A a={1} → x=1, y=0; A a={} → x=0, y=0
23. ■ aggregate init: missing members zero-initialized ■
---FAILURES---
F1. #pragma pack(1) → unaligned access → performance penalty or crash → ⚠
F2. struct { int a; } s; printf(s.a); → uninitialized read → UB → ✗
F3. struct { const int x; } → no default constructor → compile error → ✗
F4. struct { int& r; } → reference needs init → compile error → ✗
F5. assume sizeof(Derived)==sizeof(Base) → wrong if Derived adds members → ✗
