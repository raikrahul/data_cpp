# Problem 30: Vector vs Ranges Fill Derivation

## Memory Structure Trace
01. **Variable:** `std::vector<int> v1` (Stack Handle).
02. **Stack Addr:** 0x1000. Size: 24 Bytes (Ptr, Size, Cap).
03. **Heap Addr:** 0x5000 (Managed Block).
04. **Element Size:** 4 Bytes.
05. **N:** 100.
06. **Total Heap Bytes:** 100 × 4 = 400 Bytes. Offsets: 0x5000...0x5190.

## Case 1: `std::vector<int> v1(100, 8);`

07. Step 1: Allocator gets 400 Bytes at 0x5000.
08. Step 2: `uninitialized_fill_n(0x5000, 100, 8)`.
09. Loop:
    - 0x5000 ← 8
    - 0x5004 ← 8
    - ...
    - 0x518C ← 8 (Index 99)
10. **Total Writes:** 100 integers. 400 Bytes.
11. **Complexity:** 1 Pass.

## Case 2: `std::vector<int> v2(100); std::ranges::fill(v2, 8);`

12. Step 1: Allocator gets 400 Bytes at 0x6000.
13. Step 2: `vector(100)` constructor (Default Init).
14. Sub-step: `uninitialized_fill_n(0x6000, 100, 0)`.
15. Loop A (Zeroing):
    - 0x6000 ← 0
    - 0x6004 ← 0
    - ...
    - 0x618C ← 0
16. Step 3: `std::ranges::fill(v2, 8)`.
17. Loop B (Overwriting):
    - 0x6000 ← 8
    - 0x6004 ← 8
    - ...
    - 0x618C ← 8
18. **Total Writes:** 100 (Zero) + 100 (Eight) = 200 integers.
19. **Inefficiency:** 100 redundant writes. 400 Bytes wasted traffic.

## Punishment Calculation: N = 1,048,576 (2^20)

20. **Heap Size:** 1,048,576 × 4 bytes = 4,194,304 bytes = 4 MiB.
21. **Case 1 Logic:**
    - Write 4 MiB once.
    - Total Traffic = 4 MiB.
    - RAM Time @ 20GB/s: 4MB / 20GB/s = 200 µs.
22. **Case 2 Logic:**
    - Pass 1 (Zero): Write 4 MiB.
    - Pass 2 (Fill): Write 4 MiB.
    - Total Traffic = 8 MiB.
    - RAM Time @ 20GB/s: 400 µs.
23. **Cache Implications (L3 = 8MiB??):**
    - Pass 1 loads 4MB into cache (Dirty).
    - If L3 < 4MB (e.g. 2MB slice), Pass 1 evicts data.
    - Pass 2 re-loads lines? Or Write-Allocate?
    - Worst case: Double the cache pollution.

## Edge & Fractional Cases

24. **N=0:** No allocations. Both cases 0 writes. No difference.
25. **N=1:** v1 writes 1 int. v2 writes 0 then 8 (2 writes). 100% overhead.
26. **Small N=7:** v1 writes 7. v2 writes 14.
