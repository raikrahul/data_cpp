01. DRAW struct S1 { char a; int b; char c; }. CALCULATE: a at offset 0 (1 byte), PADDING 3 bytes (align b to 4), b at offset 4 (4 bytes), c at offset 8 (1 byte), PADDING 3 bytes (align struct to 4). TOTAL sizeof(S1) = 12 bytes. VERIFY 1+3+4+1+3 = 12 ✓
02. DRAW MEMORY: |0x00: a|0x01: pad|0x02: pad|0x03: pad|0x04: b[0]|0x05: b[1]|0x06: b[2]|0x07: b[3]|0x08: c|0x09: pad|0x0A: pad|0x0B: pad|. WASTED = 6 bytes = 50% ✓
03. REORDER struct S2 { int b; char a; char c; }. CALCULATE: b at offset 0 (4 bytes), a at offset 4 (1 byte), c at offset 5 (1 byte), PADDING 2 bytes (align struct to 4). TOTAL sizeof(S2) = 8 bytes. SAVINGS = 12-8 = 4 bytes = 33% ✓
04. DRAW MEMORY: |0x00-0x03: b|0x04: a|0x05: c|0x06: pad|0x07: pad|. WASTED = 2 bytes = 25%. COMPARE S1 waste = 50% → S2 waste = 25% ✓
05. ■ GROUND: RULE = order members by size descending (largest first). int(4) → char(1) → char(1). Minimizes padding ■ NEXT: alignment rules ■
06. DRAW struct S3 { char a; double b; char c; }. CALCULATE: a at offset 0 (1 byte), PADDING 7 bytes (align b to 8), b at offset 8 (8 bytes), c at offset 16 (1 byte), PADDING 7 bytes (align struct to 8). TOTAL sizeof(S3) = 24 bytes. WASTED = 14 bytes = 58% ✓
07. REORDER struct S4 { double b; char a; char c; }. CALCULATE: b at offset 0 (8 bytes), a at offset 8 (1 byte), c at offset 9 (1 byte), PADDING 6 bytes (align struct to 8). TOTAL sizeof(S4) = 16 bytes. SAVINGS = 24-16 = 8 bytes = 33% ✓
08. RULE: alignof(T) = max(alignof(member)) for each member. alignof(S3) = alignof(double) = 8. alignof(S1) = alignof(int) = 4. VERIFY with alignof() operator ✓
09. ■ GROUND: struct alignment = largest member alignment. padding at end ensures array element alignment ■ NEXT: class vs struct ■
10. COMPARE struct S { int x; } vs class C { int x; }. ONLY difference: struct default = public, class default = private. sizeof(S) = sizeof(C) = 4. MEMORY LAYOUT identical ✓
11. DRAW class D { public: int x; private: int y; }. LAYOUT: x at offset 0, y at offset 4. ACCESS specifiers do NOT affect memory layout. sizeof(D) = 8 ✓
12. DRAW class V { virtual void f(); int x; }. LAYOUT: vptr at offset 0 (8 bytes on 64-bit), x at offset 8 (4 bytes), PADDING 4 bytes. sizeof(V) = 16. OVERHEAD = 8 bytes for virtual ✓
13. ■ GROUND: virtual adds 8-byte vptr at offset 0. Non-virtual class = same as struct ■ NEXT: initialization ■
14. WRITE struct P { int a; int b; }. DEFAULT INIT: P p; → a and b UNINITIALIZED (garbage). VALUE INIT: P p{}; → a=0, b=0. VERIFY difference ✓
15. WRITE struct Q { int a = 5; int b; }. DEFAULT INIT: Q q; → a=5 (default member initializer), b=GARBAGE. VALUE INIT: Q q{}; → a=5, b=0. TRAP: default member init != value init ✓
16. WRITE struct R { int a; int b; R() : a(10), b(20) {} }. CONSTRUCTOR INIT: R r; → a=10, b=20. Member initializer list runs BEFORE constructor body ✓
17. INITIALIZER LIST ORDER: struct T { int a; int b; T() : b(1), a(b) {} }. WARNING: a initialized before b (declaration order), but initializer references b. a = uninitialized b = GARBAGE. TRAP: init order follows declaration, not constructor list ✓
18. ■ GROUND: initialization order = declaration order in class. Initializer list order in constructor is ignored ■ NEXT: aggregate init ■
19. WRITE struct A { int x; int y; }. AGGREGATE INIT: A a = {1, 2}; → x=1, y=2. A a = {1}; → x=1, y=0 (remaining members zero-initialized). A a = {}; → x=0, y=0 ✓
20. WRITE struct B { int x; int y = 5; }. AGGREGATE INIT: B b = {1}; → x=1, y=5 (default member initializer used). B b = {1, 2}; → x=1, y=2 (explicit overrides default). VERIFY ✓

---FAILURES---
F1. struct { char a; int b; } on 32-bit vs 64-bit → sizeof(int) same, but pointer sizes differ → struct size may vary → ✗ (actually int is 4 on both)
F2. #pragma pack(1) struct { char a; int b; } → sizeof = 5 (no padding) → unaligned access → performance penalty or crash on some architectures → ⚠
F3. struct { int a; } s; printf("%d", s.a); → uninitialized read → undefined behavior → ✗
F4. struct { const int x; } s; → default constructor deleted → must provide initializer → compile error → ✗
F5. struct { int& r; } s; → reference member requires initialization → no default constructor → compile error → ✗

---AXIOMATIC CHECK---
Line 01: Introduced struct S1 → primitive types char(1), int(4) with known sizes
Line 03: Introduced reordering → derived from observing 50% waste in line 02
Line 06: Introduced double → 8-byte alignment forces larger padding
Line 10: Introduced class → derived from observing struct limitation (no access control by default)
Line 12: Introduced virtual → derived from need for polymorphism, adds vptr overhead
Line 14: Introduced initialization → derived from observing uninitialized members
NO JUMPING AHEAD: Each concept derived from limitation observed in previous lines.
