# Problem 22: SIMD Vectorization & Parallel Execution

## PUZZLE 1: Register Width Calculation

**GIVEN:** ymm0 register = 256 bits

```
CALCULATION:
───────────────────────────────────────────────────
256 bits ÷ 8 bits/byte = ___ bytes

sizeof(double) = 8 bytes → ___ doubles per ymm
sizeof(float) = 4 bytes → ___ floats per ymm
sizeof(int) = 4 bytes → ___ ints per ymm
sizeof(char) = 1 byte → ___ chars per ymm
───────────────────────────────────────────────────
```

**TRAP:** xmm0 = 128 bits, zmm0 = 512 bits. Different registers, different widths.

---

## PUZZLE 2: Vectorization Speedup

**GIVEN:** Scalar loop vs SIMD loop for multiply

```
SCALAR ASSEMBLY:
───────────────────────────────────────────────────
.L3:
  movsd xmm0, [rax]      ; load 1 double (8 bytes)
  mulsd xmm0, xmm1       ; multiply 1 double
  movsd [rbx], xmm0      ; store 1 double
  add rax, 8             ; next input
  add rbx, 8             ; next output
  cmp rax, rdx           ; check end
  jne .L3                ; loop
  
Instructions per element: ___
───────────────────────────────────────────────────

SIMD ASSEMBLY (AVX2):
───────────────────────────────────────────────────
.L3:
  vmovupd ymm0, [rax]    ; load 4 doubles (32 bytes)
  vmulpd ymm0, ymm0, ymm1 ; multiply 4 doubles
  vmovupd [rbx], ymm0    ; store 4 doubles
  add rax, 32            ; next 4 inputs
  add rbx, 32            ; next 4 outputs
  cmp rax, rdx           ; check end
  jne .L3                ; loop
  
Instructions per 4 elements: ___
Instructions per element: ___ / 4 = ___
───────────────────────────────────────────────────

SPEEDUP = Scalar instructions / SIMD instructions = ___ / ___ = ___x
```

**TRAP:** Latency ≠ Throughput. vmulpd latency = 4 cycles, throughput = 0.5 cycles.

---

## PUZZLE 3: Memory Bandwidth Crossover

**GIVEN:**
- L1 cache: 32 KB, 64 bytes/cycle bandwidth
- L2 cache: 256 KB, 40 bytes/cycle bandwidth
- SIMD demand: 32 bytes load + 32 bytes store = 64 bytes/iteration

```
CALCULATION:
───────────────────────────────────────────────────
L1 capacity: 32,768 bytes ÷ 8 bytes/double = ___ doubles

For N ≤ ___: Data fits in L1, full SIMD speed
For N > ___: Data spills to L2, bandwidth drops

L2 utilization: 40 bytes/cycle ÷ 64 bytes/iter = ___% efficiency
───────────────────────────────────────────────────

SIMD effective speedup at N=100,000:
  Theoretical: 4x
  Memory limited: 4x × ___% = ___x
───────────────────────────────────────────────────
```

**TRAP:** CPU-bound vs Memory-bound. Large N is memory-bound.

---

## PUZZLE 4: Parallel Break-Even Point

**GIVEN:**
- Thread dispatch overhead: 10,000 cycles
- Per-element work: 10 cycles
- Number of threads: 8

```
CALCULATION:
───────────────────────────────────────────────────
Serial time: N × 10 cycles
Parallel time: (N × 10 ÷ 8) + 10,000 cycles

Break-even: Serial = Parallel
  N × 10 = (N × 10 ÷ 8) + 10,000
  N × 10 - N × 10 ÷ 8 = 10,000
  N × 10 × (1 - 1/8) = 10,000
  N × 10 × 7/8 = 10,000
  N = 10,000 × 8 ÷ 70
  N = ___
───────────────────────────────────────────────────

For N < ___: Serial is faster
For N > ___: Parallel is faster
───────────────────────────────────────────────────
```

**TRAP:** Real overhead includes synchronization barrier (additional ~2,000 cycles).

---

## PUZZLE 5: False Claim Verification

**GIVEN:** Lecture claims "algorithms can parallelize automatically"

```
VERIFICATION:
───────────────────────────────────────────────────
Code A (no policy):
  std::transform(v.begin(), v.end(), w.begin(), [](double x){return x*2;});

Code B (explicit parallel):
  std::transform(std::execution::par, v.begin(), v.end(), w.begin(), [](double x){return x*2;});

COMPILE: g++ -O3 -S -o codeA.s codeA.cpp
COMPILE: g++ -O3 -S -o codeB.s codeB.cpp

SEARCH in codeA.s:
  grep "call.*tbb" codeA.s → Found? ___
  grep "lock" codeA.s → Found? ___
  grep "__parallel" codeA.s → Found? ___

CONCLUSION: If all NO → Code A is SEQUENTIAL → Lecture is WRONG
───────────────────────────────────────────────────
```

**TRAP:** "Optimized" ≠ "Parallelized". -O3 vectorizes, but does NOT parallelize.

---

## PUZZLE 6: Instruction Port Pressure

**GIVEN:** Skylake has 8 execution ports

```
PORT ASSIGNMENT:
───────────────────────────────────────────────────
Port 0: SIMD multiply (vmulpd)
Port 1: SIMD add
Port 2: Load
Port 3: Load
Port 4: Store data
Port 5: Shuffle
Port 6: Branch
Port 7: Store address

SIMD loop uses:
  vmovupd (load): Port ___ or ___
  vmulpd: Port ___
  vmovupd (store): Port ___ + ___
  add: Port ___ or ___
  cmp + jne: Port ___

Total ports per iteration: ___
───────────────────────────────────────────────────

Max throughput = ___ instructions/cycle (limited by port 0)
Actual throughput = ___ doubles/cycle (if not memory bound)
───────────────────────────────────────────────────
```

**TRAP:** Port 0 is shared with other SIMD ops. Conflict = stall.

---

## PUZZLE 7: Cache Line Alignment

**GIVEN:**
- Cache line: 64 bytes
- ymm load: 32 bytes
- Access address: random in [0x1000, 0x2000)

```
CALCULATION:
───────────────────────────────────────────────────
Cache line at 0x1000: covers 0x1000 - 0x103F
Cache line at 0x1040: covers 0x1040 - 0x107F

32-byte load at address A crosses boundary if:
  (A % 64) + 32 > 64
  A % 64 > 32

Addresses that DON'T cross: 0x1000, 0x1020 (offset 0, 32)
Addresses that DO cross: 0x1030, 0x1050 (offset 48, 16+64=80-64=16)

Wait, let me recalculate:
  Offset 0: load 0-31 → OK (within 0-63)
  Offset 16: load 16-47 → OK (within 0-63)
  Offset 32: load 32-63 → OK (within 0-63)
  Offset 48: load 48-79 → SPLIT (48-63 in line 1, 64-79 in line 2)

Split probability = offsets {48, 49, ..., 63} = 16 offsets out of 64
Split probability = 16/64 = ___
───────────────────────────────────────────────────

Extra penalty: 4-8 cycles per split (L1) or 50+ cycles (L2 miss)
───────────────────────────────────────────────────
```

**TRAP:** std::vector does NOT guarantee 32-byte alignment. Only 16-byte.

---

## FILL IN ALL BLANKS BEFORE RUNNING CODE

---

## Error Report: SIMD Puzzle Session Mistakes

### ERROR 1: Register Width Calculation
- **Line:** L27, L37-40
- **Wrong:** 256 bits = 16 bytes, 16/8 = 2 doubles
- **Correct:** 256 bits = 32 bytes, 32/8 = 4 doubles
- **Why sloppy:** Did not compute 256 ÷ 8, guessed 16
- **Missed:** 256 ÷ 8 = 32, not 16
- **Prevention:** Write calculation: 256 ÷ 8 = ___ before typing answer

### ERROR 2: Float/Int Capacity First Attempt
- **Line:** L27
- **Wrong:** 4 floats, 4 ints
- **Correct:** 8 floats, 8 ints (32 bytes ÷ 4 bytes)
- **Why sloppy:** Used wrong base (16 bytes instead of 32)
- **Missed:** 32 ÷ 4 = 8, not 4
- **Prevention:** Start from correct byte count (32), then divide

### ERROR 3: Instruction Per Element Calculation
- **Line:** L87
- **Wrong:** 7 / 4 = 2 instr/elem
- **Correct:** 7 / 4 = 1.75 instr/elem
- **Why sloppy:** Rounded to integer without thinking
- **Missed:** 7 ÷ 4 = 1.75, not 2
- **Prevention:** Use calculator or write: 7.0 / 4.0 = 1.75

### ERROR 4: Assembly Instruction Meaning
- **Line:** Verbal
- **Wrong:** "movsd = move short decimal"
- **Correct:** movsd = Move Scalar Double-precision
- **Why sloppy:** Guessed from letters instead of looking up
- **Missed:** s = scalar, d = double, not "short decimal"
- **Prevention:** Decompose instruction: prefix + operation + size + type

---

### Pattern: Root Causes

1. **Bit vs Byte confusion** → 256 bits ≠ 256 bytes
2. **Integer rounding** → 7/4 = 1.75, not 2
3. **Guessing acronyms** → movsd ≠ "move short decimal"
4. **Cascade errors** → Wrong byte count → wrong element count

### Fix Protocol

1. WRITE bit-to-byte conversion: bits ÷ 8 = bytes
2. USE decimal division for instruction ratios
3. DECOMPOSE instruction names systematically
4. VERIFY base value before computing derived values


---

## Error Report: sbrk/malloc Session Mistakes

### ERROR 1: Size Header Overwrite
- **Line:** L10-11 (original)
- **Wrong:** Store size at ptr1, then for-loop writes ptr1[0..99]
- **Correct:** Store size, then ptr1 += 8, then write user data
- **Why sloppy:** Did not trace memory layout step by step
- **Missed:** ptr1[0] overlaps with *(size_t*)ptr1
- **Prevention:** Draw memory boxes: [header][user data], mark boundaries

### ERROR 2: Missing Pad Storage for Free
- **Line:** L10
- **Wrong:** *(size_t*)ptr1 = 100 (stores only user size)
- **Correct:** Need to store pad OR store total allocation size
- **Why sloppy:** Focused on alloc, forgot free needs reverse info
- **Missed:** At free time, pad value is lost (calculated at alloc time)
- **Prevention:** Ask "what info does free() need?" before designing header

### ERROR 3: Confusion About sbrk Return Value
- **Line:** Verbal
- **Wrong:** Thought sbrk "returns then allocates"
- **Correct:** sbrk saves old, extends heap, returns old (order matters)
- **Why sloppy:** Did not read source code
- **Missed:** Function stores oldbrk BEFORE calling __brk()
- **Prevention:** Read implementation: glibc-2.39/misc/sbrk.c lines 65-77

### ERROR 4: Alignment Math Direction
- **Line:** Verbal
- **Wrong:** Confused ceil vs floor for alignment
- **Correct:** Alloc uses ceil (round up), free uses floor (round down)
- **Why sloppy:** Did not write formula before calculating
- **Missed:** ceil = (addr + 7) & ~7, floor = addr & ~7
- **Prevention:** Write alignment formula, test with example addresses

---

### Pattern: Root Causes

1. **No memory diagram** → overlapping writes
2. **Forward-only thinking** → forgot reverse operation (free) needs info
3. **Not reading source** → invented wrong execution order
4. **Formula skipped** → confused ceil/floor alignment

### Fix Protocol

1. DRAW memory layout before writing any code
2. DESIGN header by asking "what does free() need?"
3. READ source code for system calls
4. WRITE formula before calculating alignments

