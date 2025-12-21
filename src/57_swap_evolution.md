01. DRAW STACK at 0x7FFEE000. WRITE a at 0x7FFDFFF8 = 05 00 00 00 (4 bytes, little-endian). WRITE b at 0x7FFDFFF4 = 07 00 00 00 (4 bytes). CALCULATE offset: a_addr - b_addr = 0x7FFDFFF8 - 0x7FFDFFF4 = 4 bytes. VERIFY sizeof(int) = 4 ✓
02. DRAW POINTER pa at 0x7FFDFFEC = F8 FF FD 7F 00 00 00 00 (8 bytes). DECODE: little-endian → 0x7FFDFFF8 → pa points to a. DRAW ARROW pa → a. CALCULATE sizeof(int*) = 8 ✓
03. DRAW POINTER pb at 0x7FFDFFE4 = F4 FF FD 7F 00 00 00 00 (8 bytes). DECODE: 0x7FFDFFF4 → pb points to b. DRAW ARROW pb → b. VERIFY pb_addr - pa_addr = 0x7FFDFFEC - 0x7FFDFFE4 = 8 = sizeof(int*) ✓
04. DEREFERENCE pa: STEP 1 load pa = 0x7FFDFFF8, STEP 2 read mem[0x7FFDFFF8] = 05 00 00 00 = 5. WRITE tmp at 0x7FFDFFE0 = 05 00 00 00. VERIFY tmp = *pa = 5 ✓
05. ■ GROUND: a=5@FFF8, b=7@FFF4, pa→FFF8, pb→FFF4, tmp=5@FFE0 ■ NEXT: overwrite *pa ■
06. DEREFERENCE pb: STEP 1 load pb = 0x7FFDFFF4, STEP 2 read mem[0x7FFDFFF4] = 07 00 00 00 = 7. DEREFERENCE pa: load pa = 0x7FFDFFF8. WRITE mem[0x7FFDFFF8] = 07 00 00 00. VERIFY a = *pa = 7, old value 5 overwritten ✓
07. STATE CHECK: a=7@FFF8, b=7@FFF4, tmp=5@FFE0. BOTH a and b now contain 7. WITHOUT tmp, original a=5 would be lost. tmp PRESERVES original value for next step.
08. DEREFERENCE pb: load pb = 0x7FFDFFF4. WRITE mem[0x7FFDFFF4] = *(int*)0x7FFDFFE0 = 05 00 00 00 = 5. VERIFY b = *pb = 5, original b=7 overwritten ✓
09. FINAL STATE: a=7@FFF8, b=5@FFF4, tmp=5@FFE0 (stale). VERIFY SWAP: original a=5 now in b, original b=7 now in a ✓
10. ■ GROUND: SWAP COMPLETE. a:5→7, b:7→5, tmp=5 (preserves original a). 3-step algorithm: tmp=*pa, *pa=*pb, *pb=tmp ■ NEXT: REFERENCE version ■
11. ERASE POINTERS. DRAW a at 0x7FFDDFA8 = 5. DRAW b at 0x7FFDDFA4 = 7. WRITE ALIAS: ra → 0x7FFDDFA8. rb → 0x7FFDDFA4. CALCULATE sizeof(reference) = 0 bytes in source, 8 bytes if spilled to stack. NO NEW MEMORY allocated for reference itself ✓
12. READ ra: compiler translates ra → mem[0x7FFDDFA8] = 5. WRITE tmp at 0x7FFDDFA0 = 5. VERIFY tmp = ra = *(&a) = 5 ✓
13. WRITE ra = rb: compiler translates → mem[0x7FFDDFA8] = mem[0x7FFDDFA4] = 7. VERIFY a = 7 ✓
14. WRITE rb = tmp: compiler translates → mem[0x7FFDDFA4] = mem[0x7FFDDFA0] = 5. VERIFY b = 5 ✓
15. ■ GROUND: REFERENCE version: SAME memory writes, NO pointer storage. Stack: 12 bytes (a+b+tmp) vs 28 bytes (a+b+pa+pb+tmp). SAVINGS = 16 bytes = 57% ■ NEXT: std::swap ■
16. WRITE a=5 at 0x7FFDDEE8. WRITE b=7 at 0x7FFDDEE4. CALL std::swap(a, b). STEP 1 (inline): tmp ← a = 5. STEP 2: a ← b = 7. STEP 3: b ← tmp = 5. VERIFY a=7, b=5 ✓
17. COUNT INSTRUCTIONS: Version 0 (pointers) = 6 mov (3 load, 3 store). Version 1 (references) = 6 mov (all direct). Version 2 (std::swap) = 3 mov (compiler uses registers). SPEEDUP = 50% instruction reduction ✓
18. ■ GROUND: std::swap abstracts 3-step pattern into 1 call, compiler optimizes to 3 register moves ■ NEXT: auto deduction ■
19. WRITE auto a = 5. DEDUCE: literal 5 → int → a : int. WRITE auto b = 7. DEDUCE: 7 → int → b : int. VERIFY sizeof(a) = sizeof(int) = 4 ✓
20. WRITE auto c = 5.0. DEDUCE: literal 5.0 → double → c : double. VERIFY sizeof(c) = 8 ≠ 4. TRAP: 5 vs 5.0 determines type. WRITE auto d = 5.0f. DEDUCE: 5.0f → float → d : float. sizeof(d) = 4 ✓
21. CALL std::swap(a, b). a : int, b : int → T = int. VERIFY swap works for any T with copy/move semantics ✓
22. ■ GROUND: auto deduces type from literal. int literals: 5, 7. double literals: 5.0. float literals: 5.0f ■ NEXT: structured binding ■
23. WRITE auto [x, y] = std::pair{5, 7}. DECOMPOSE: std::pair<int,int> at 0x7FFDDE00. x → &pair.first = 0x7FFDDE00 = 5. y → &pair.second = 0x7FFDDE04 = 7. VERIFY x=5, y=7, sizeof(pair)=8 ✓
24. SWAP via pair: auto [x, y] = std::pair{y, x}. RHS EVALUATE FIRST: y=7, x=5 → pair{7, 5}. ASSIGN: x←7, y←5. VERIFY swap completed ✓
25. ■ GROUND: structured binding decomposes aggregate into named references. swap via temporary pair creation ■ NEXT: double swap ■
26. WRITE auto priceA = 19.99. DEDUCE: 19.99 → double. IEEE 754: 19.99 = 0x403C7AE147AE147B. WRITE priceB = 34.50 → 0x4041400000000000. CALL std::swap(priceA, priceB). VERIFY priceA=34.50, priceB=19.99 ✓
27. REGISTER USAGE: double swap uses XMM registers. xmm0 ← priceA = 19.99. priceA ← priceB = 34.50. priceB ← xmm0 = 19.99. NO stack temp. CYCLE COUNT = 3 movsd instructions ✓
28. CACHE ANALYSIS: priceA at 0x7FFDDDC0, priceB at 0x7FFDDDB8. DIFFERENCE = 8 bytes. CACHE LINE = 64 bytes. floor(0x7FFDDDC0/64) = floor(0x7FFDDDB8/64) = same line. 1 cache miss loads BOTH values ✓
29. ■ GROUND: COMPLETE EVOLUTION: raw pointers (28 bytes) → references (12 bytes) → std::swap (3 mov) → auto (type deduction) → structured binding (aggregate decomposition) → register swap (0 stack temp) ■
30. XOR SWAP: a ^= b → a = 0x05 ^ 0x07 = 0x02. b ^= a → b = 0x07 ^ 0x02 = 0x05. a ^= b → a = 0x02 ^ 0x05 = 0x07. VERIFY a=7, b=5 ✓. TRAP: 3 serial dependencies → 3 cycles. std::swap = 1 cycle (parallel moves). XOR SLOWER despite no tmp ✓

---FAILURES---
F1. pa = nullptr → *pa = 5 → SIGSEGV at address 0x0 → ✗
F2. pa == pb (alias) → tmp = *pa, *pa = *pb (no-op), *pb = tmp → self-swap, no net change → ✓ but wasteful
F3. std::swap(5, 7) → 5 is rvalue → cannot bind to T& parameter → compile error → ✗
F4. volatile int a = 5, b = 7 → std::swap(a, b) → volatile T& cannot bind to non-volatile ref → compile error → ✗
F5. std::swap(arrA, arrB) where arrA/arrB are C arrays → swaps pointers, not elements → unexpected behavior → ✗
F6. int a = INT_MAX, b = 1 → XOR swap works → no overflow → ✓ (XOR is bitwise, not arithmetic)

---AXIOMATIC CHECK---
Line 01: Introduced a, b, addresses → derived from stack layout starting at 0x7FFEE000
Line 02: Introduced pa → derived from need to store address of a for indirection
Line 04: Introduced tmp → derived from need to preserve a before overwrite in line 06
Line 11: Introduced references → derived from observing pointer storage overhead in line 02-03
Line 16: Introduced std::swap → derived from observing repetitive 3-step pattern in lines 04-08
Line 19: Introduced auto → derived from need to avoid explicit type declaration
Line 23: Introduced structured binding → derived from C++17 aggregate decomposition
Line 30: Introduced XOR swap → derived from observation that tmp uses memory, XOR uses none
NO JUMPING AHEAD: Each concept derived from limitation observed in previous lines.
