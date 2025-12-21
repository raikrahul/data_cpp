**01. EXERCISE 1: RUNTIME INSECT MEMORY LAYOUT CALCULATION**

**02. DRAW SocialInsect object at 0x582043e599f0 with these concrete field values: x=37.454f, y=79.6543f, vx=vel_dist(gen), vy=vel_dist(gen), radius=5.0f. Calculate total size including vptr (8 bytes on 64-bit). Show byte offset of each member. Draw vptr arrow to vtable. ✓✗∴→**

**03. VTABLE: Contains function pointers: &update, &draw, &~dtor. Draw memory map. ✓✗∴→**

**04. EXERCISE 2: VIRTUAL CALL CYCLE COUNT**

**05. INSTRUCTION TRACE FROM ASSEMBLY (line 340): movq (%rdi), %rax → load vptr. call *8(%rax) → indirect call to update via vtable offset 8. Total per call = 7 cycles. For 100 insects × 10 frames = 1,000 calls. Calculate total cycles = 7,000. ✓✗∴→**

**06. BRANCH PREDICTOR PENALTY: Indirect call mispredict rate = 15%. Calculate penalty = 0.15 × 1,000 calls × 10 cycle penalty = 1,500 cycles. ✓✗∴→**

**07. EXERCISE 3: NEIGHBOR SEARCH CALCULATION**

**08. INSECT #0 at (37.454,79.654) checks INSECT #1 at (73.199,77.969). dx = 73.199 - 37.454 = 35.745. dy = 77.969 - 79.654 = -1.685. dist² = 35.745² + (-1.685)² = 1277.71 + 2.839 = 1280.549. dist = √1280.549 ≈ 35.78. Compare to radius=5.0 → 35.78 > 5.0 ∴ ✗ not neighbor. ✓✗∴→**

**09. COMPLEXITY: 100 insects each check 99 neighbors = 9,900 distance calculations per frame. Memory reads = 9,900 × 24 bytes = 237,600 bytes. Cache lines = 237,600 / 64 = 3,712.5 → 3,713 lines. ✓✗∴→**

**10. EXERCISE 4: COMPILE-TIME MEMORY LAYOUT**

**11. DRAW Insect<SocialPolicy> at 0x582043e5a990 without vptr: x at offset 0, y at offset 4, vx at offset 8, vy at offset 12. Total size = 16 bytes. Stride = 16 bytes (verified: 0x582043e5a9a0 - 0x582043e5a990 = 0x10 = 16). ✓✗∴→**

**12. EXERCISE 5: STATIC DISPATCH CYCLE COUNT**

**13. DIRECT CALL: No indirect call in compile-time branch (inlined at -O2). Savings = 7 cycles per call. Total saved = 1,000 calls × 7 = 7,000 cycles. ✓✗∴→**

**14. EXERCISE 6: BENCHMARK RESULTS (REAL DATA)**

**15. Runtime Polymorphism: 4315 μs. Compile-time Polymorphism: 567 μs. Speedup: 7.61×. ✓✗∴→**

**16. EXERCISE 7: CACHE EFFICIENCY**

**17. COMPILE-TIME ARRAY: 50 objects × 16 bytes = 800 bytes. Cache lines = 800 / 64 = 12.5 → 13 lines. Contiguous → prefetch works. ✓✗∴→**

**18. RUNTIME ARRAY: 100 scattered heap allocations. Each unique_ptr dereference → cache miss. Total misses ≈ 100 per frame. ✓✗∴→**

---

## ERROR REPORT

**E01. Line 52-54: Syntax error**
- What: `dx = other->x - this->x` missing semicolon
- Should: `float dx = other->x - this->x;`
- Why sloppy: copy-paste from comment without adding float type and semicolon
- Missed: C++ statement terminator
- Prevent: compile before save

**E02. Line 60: Invalid Unicode**
- What: `radius² = 5.0 × 5.0 = 25.0`
- Should: `// radius² = 5.0 × 5.0 = 25.0` (comment) or `float radius_sq = radius * radius;`
- Why sloppy: treated comment as code
- Missed: × and ² are not valid C++ operators
- Prevent: syntax highlight shows error immediately

**E03. Line 55-57: Redundant declarations**
- What: `[[maybe_unused]] float dx = 0.0f;` after actual `dx = ...`
- Should: remove duplicate declarations
- Why sloppy: half-edited TODO block
- Missed: variable shadowing
- Prevent: compile with -Wshadow

**E04. Function signature mismatch**
- What: update(float dt) had no access to other insects
- Should: update(float dt, const std::vector<...>& all)
- Why sloppy: boilerplate incomplete
- Missed: problem requires O(N²) neighbor check → needs container access
- Prevent: read exercise 09 first

**E05. Line 128-133: Template logic incomplete**
- What: `if constexpr` branches had TODO comments only
- Should: implement actual neighbor logic
- Why sloppy: left as stub
- Missed: benchmark comparison invalid without implementation
- Prevent: write both branches before benchmark

**E06. sizeof mismatch in comments**
- What: comments said "32 bytes" but measured sizeof(SocialInsect)=32, sizeof(SolitaryInsect)=24
- Should: match actual sizeof values
- Why sloppy: assumed same size
- Missed: SolitaryInsect has no radius field → 8 bytes smaller
- Prevent: use sizeof() in code, not hardcoded comments

---

## ASSEMBLY ANALYSIS (REAL)

**Virtual call path (line 340):**
```
movq    (%rdi), %rax     ; load vptr from object at rdi
call    *8(%rax)         ; indirect call to vtable[1] = update
```
- rdi = 0x582043e599f0 (insect #0)
- [rdi] = vptr → vtable address
- [vptr+8] = &SocialInsect::update

**Compile-time path:**
- No `call *` instruction found in template code
- Entire update() inlined → only arithmetic ops remain
