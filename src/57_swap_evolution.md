```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ BEFORE SWAP:                           AFTER SWAP:                                                               │
│ 0x7FFDFFF8: a=5 ←─pa                   0x7FFDFFF8: a=7 ←─pa                                                     │
│ 0x7FFDFFF4: b=7 ←─pb                   0x7FFDFFF4: b=5 ←─pb                                                     │
│ 0x7FFDFFE0: tmp=?                      0x7FFDFFE0: tmp=5                                                        │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ CHAIN: tmp←*pa(5) → *pa←*pb(7) → *pb←tmp(5)                                                                     │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. a=5 at 0x7FFDFFF8, b=7 at 0x7FFDFFF4, offset=0x7FFDFFF8-0x7FFDFFF4=4=sizeof(int) ✓
02. pa=0x7FFDFFF8 at 0x7FFDFFEC (8 bytes), pb=0x7FFDFFF4 at 0x7FFDFFE4 (8 bytes)
03. *pa = mem[0x7FFDFFF8] = 5, *pb = mem[0x7FFDFFF4] = 7
04. tmp = *pa = 5 at 0x7FFDFFE0
05. ■ a=5 b=7 pa→a pb→b tmp=5 ■
06. *pa = *pb → mem[0x7FFDFFF8] = mem[0x7FFDFFF4] = 7 → a=7
07. *pb = tmp → mem[0x7FFDFFF4] = 5 → b=5
08. ■ a=7 b=5 swap complete ■
09. REFERENCE VERSION: ra→0x7FFDDFA8, rb→0x7FFDDFA4, NO storage for ra/rb, only symbol table entries
10. tmp = ra = mem[0x7FFDDFA8] = 5, ra = rb → mem[0x7FFDDFA8] = 7, rb = tmp → mem[0x7FFDDFA4] = 5
11. ■ pointer: 28 bytes (a+b+pa+pb+tmp), reference: 12 bytes (a+b+tmp), savings=57% ■
12. std::swap(a,b): tmp=a=5, a=b=7, b=tmp=5, 3 mov instructions (register optimized)
13. ■ std::swap = 3 mov vs 6 mov (pointer version), 50% fewer instructions ■
14. auto a=5 → int, auto b=7 → int, sizeof=4 ✓
15. auto c=5.0 → double, sizeof=8 ✓, auto d=5.0f → float, sizeof=4 ✓
16. ■ auto deduces from literal suffix ■
17. auto [x,y] = std::pair{5,7} → x=pair.first=5, y=pair.second=7
18. swap via pair: [x,y] = std::pair{y,x} → temp pair{7,5} → x=7, y=5
19. ■ structured binding decomposes aggregates ■
20. priceA=19.99=0x403C7AE147AE147B, priceB=34.50=0x4041400000000000, IEEE 754 double
21. std::swap uses xmm0 register, 0 stack temp, 3 movsd instructions
22. cache: 0x7FFDDDC0, 0x7FFDDDB8 in same 64-byte line → 1 cache miss loads both
23. ■ register swap: 3 cycles, cache efficient ■
24. XOR: a^=b → 0x05^0x07=0x02, b^=a → 0x07^0x02=0x05, a^=b → 0x02^0x05=0x07 → a=7,b=5 ✓
25. ■ XOR: no tmp, 3 serial deps, SLOWER than std::swap (parallel moves) ■
---FAILURES---
F1. pa=nullptr → *pa → SIGSEGV → ✗
F2. pa==pb → self-swap → no change → ⚠
F3. std::swap(5,7) → rvalue → compile error → ✗
F4. volatile int a,b → std::swap → compile error → ✗
F5. swap C-arrays → swaps pointers not elements → ✗
