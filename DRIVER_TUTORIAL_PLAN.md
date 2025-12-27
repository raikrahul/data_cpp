# DRIVER TUTORIAL PLAN: TASK GRILLING DOCUMENT
## NO SOLUTIONS. ONLY TASK DECOMPOSITION. ONLY QUESTIONS.

═══════════════════════════════════════════════════════════════════════════════
MACHINE DATA (REAL VALUES - SOURCE OF ALL DERIVATIONS)
═══════════════════════════════════════════════════════════════════════════════

```
CPU: AMD Ryzen 5 4600H
Physical Address Bits: 44
Virtual Address Bits: 48
RAM Total: 15776276 kB = 15406 MB = 15.04 GB
RAM Pages: 15776276 / 4 = 3944069 pages
Swap File: /swap.img = 4194300 kB = 4095 MB
Swap Used: 1412936 kB = 1380 MB
Kernel: 6.14.0-37-generic
```

═══════════════════════════════════════════════════════════════════════════════
TASK GRILLING: WHAT MUST BE DERIVED FOR EACH DRIVER?
═══════════════════════════════════════════════════════════════════════════════

## DRIVER 01: cr3_driver.c - READ CR3 REGISTER

### QUESTIONS TO GRILL:
01. CR3 is 64 bits. Which bits hold address? Which bits hold flags?
02. If physical address is 44 bits, and page-aligned, how many bits actually used?
03. 44 bits - 12 bits (page offset) = 32 bits for PFN. Correct?
04. CR3 mask = 0x000FFFFFFFFFF000. Derive this mask bit-by-bit.
05. Why bits [63:52] zeroed? Why bits [11:0] zeroed?
06. If CR3 = 0x1337A3000, what is PCID? What is PML4 address?
07. 0x1337A3000 & 0xFFF = ? (PCID extraction)
08. 0x1337A3000 & 0x000FFFFFFFFFF000 = ? (Address extraction)
09. __va(0x1337A3000) = page_offset_base + 0x1337A3000 = ?
10. If page_offset_base = 0xFFFF89DF00000000, calculate virtual address.

### CALCULATIONS TO FORCE:
```
TRAP 1: User might forget PCID is in low 12 bits
TRAP 2: User might confuse physical vs virtual
TRAP 3: User might not know fls64() finds highest set bit
```

### DATA STRUCTURES TO DRAW:
```
CR3 Register (64 bits):
┌────────────┬────────────────────────────────────┬────────────┐
│ bits 63-52 │           bits 51-12              │ bits 11-0  │
│  Reserved  │     PML4 Physical Address         │    PCID    │
│  (zeroed)  │        (40 bits)                  │  (12 bits) │
└────────────┴────────────────────────────────────┴────────────┘
```

### FAILURE PREDICTIONS:
F1. Reading CR3 in userspace → General Protection Fault
F2. Using raw CR3 as pointer → crash (physical vs virtual confusion)
F3. PCID not masked out → wrong address calculation

---

## DRIVER 02: indices_driver.c - EXTRACT PAGE TABLE INDICES

### QUESTIONS TO GRILL:
01. VA = 0x7FFE5E4ED123. How many bits? Count them.
02. 0x7FFE5E4ED123 in binary = ?
03. Why 9 bits per index? 2^9 = 512 entries per table.
04. PML4 index = bits [47:39]. How to extract? (VA >> 39) & 0x1FF
05. 0x1FF = 511 = 0b111111111 = 9 bits mask. Derive this.
06. Calculate: (0x7FFE5E4ED123 >> 39) = ?
07. Calculate: result & 0x1FF = ?
08. Repeat for PDPT: (VA >> 30) & 0x1FF = ?
09. Repeat for PD: (VA >> 21) & 0x1FF = ?
10. Repeat for PT: (VA >> 12) & 0x1FF = ?
11. Calculate offset: VA & 0xFFF = ?

### CALCULATIONS TO FORCE:
```
VA = 0x7FFE5E4ED123
Binary = 0111_1111_1111_1110_0101_1110_0100_1110_1101_0001_0010_0011

Bit positions (from 0):
[47:39] = bits 39-47 = 9 bits for PML4
[38:30] = bits 30-38 = 9 bits for PDPT
[29:21] = bits 21-29 = 9 bits for PD
[20:12] = bits 12-20 = 9 bits for PT
[11:0]  = bits 0-11  = 12 bits for Offset

STEP: 0x7FFE5E4ED123 >> 39
0x7FFE5E4ED123 = 140,730,825,814,307 (decimal)
>> 39 = divide by 2^39 = divide by 549,755,813,888
= 256.something → need exact calculation

TRAP: User might calculate wrong shift result
```

### DATA STRUCTURES TO DRAW:
```
VA: 0x7FFE5E4ED123 (48 bits used)
┌─────────┬─────────┬─────────┬─────────┬─────────────┐
│  PML4   │  PDPT   │   PD    │   PT    │   Offset    │
│ [47:39] │ [38:30] │ [29:21] │ [20:12] │   [11:0]    │
│  9 bits │  9 bits │  9 bits │  9 bits │   12 bits   │
│  = ???  │  = ???  │  = ???  │  = ???  │   = ???     │
└─────────┴─────────┴─────────┴─────────┴─────────────┘
```

### FAILURE PREDICTIONS:
F1. Wrong shift amount → wrong index
F2. Forgetting 0x1FF mask → garbage high bits
F3. Sign extension on negative VAs (kernel addresses)

---

## DRIVER 03: entry_driver.c - READ PAGE TABLE ENTRY

### QUESTIONS TO GRILL:
01. If PML4 base = 0x1337A3000 and index = 255, what is entry address?
02. Each entry is 8 bytes. Offset = index × 8 = 255 × 8 = ?
03. 255 × 8 = 2040 bytes = 0x7F8
04. Entry physical address = 0x1337A3000 + 0x7F8 = ?
05. 0x1337A3000 + 0x7F8 = 0x1337A37F8
06. To read this in kernel, need __va(). Calculate __va(0x1337A37F8).
07. page_offset_base + 0x1337A37F8 = ?
08. If page_offset_base = 0xFFFF89DF00000000: 0xFFFF89DF00000000 + 0x1337A37F8 = ?
09. Result = 0xFFFF89E0337A37F8
10. Now dereference: *(unsigned long *)0xFFFF89E0337A37F8 = ?

### CALCULATIONS TO FORCE:
```
HARD EXAMPLE: index = 511 (max)
511 × 8 = 4088 bytes = 0xFF8
0x1337A3000 + 0xFF8 = 0x1337A3FF8

EDGE CASE: index = 0
0 × 8 = 0
0x1337A3000 + 0 = 0x1337A3000

TRAP: index = 512 → OUT OF BOUNDS (only 0-511 valid)
```

### DATA STRUCTURES TO DRAW:
```
PML4 Table in RAM (Physical 0x1337A3000):
┌──────────────────────────────────────────────────────────────┐
│ 0x1337A3000: Entry[0]   = 0x???????????????? (8 bytes)       │
│ 0x1337A3008: Entry[1]   = 0x???????????????? (8 bytes)       │
│ ...                                                          │
│ 0x1337A37F8: Entry[255] = 0x???????????????? (8 bytes) ← HERE│
│ ...                                                          │
│ 0x1337A3FF8: Entry[511] = 0x???????????????? (8 bytes)       │
└──────────────────────────────────────────────────────────────┘
Total size = 512 × 8 = 4096 bytes = 1 page
```

### FAILURE PREDICTIONS:
F1. Forgetting ×8 multiplication → reading wrong entry
F2. Using physical address directly → page fault
F3. Index out of range [0,511] → memory corruption

---

## DRIVER 04: present_driver.c - CHECK PRESENT BIT

### QUESTIONS TO GRILL:
01. Entry = 0x80000002FAE00067. Is bit 0 set?
02. 0x67 in binary = 0110_0111. Bit 0 = 1. ∴ Present = ✓
03. If bit 0 = 0, what happens on access? → Page Fault
04. Entry & 1 = 0x80000002FAE00067 & 1 = ?
05. 0x67 & 0x01 = 0x01 = 1 = True
06. Decode all other flags from 0x67:
07. Bit 1 (R/W): (0x67 >> 1) & 1 = (0x33) & 1 = 1 → Writable
08. Bit 2 (U/S): (0x67 >> 2) & 1 = (0x19) & 1 = 1 → User accessible
09. Bit 5 (A): (0x67 >> 5) & 1 = (0x03) & 1 = 1 → Accessed
10. Bit 6 (D): (0x67 >> 6) & 1 = (0x01) & 1 = 1 → Dirty
11. Bit 7 (PS): (0x67 >> 7) & 1 = (0x00) & 1 = 0 → Not huge
12. Bit 63 (NX): (0x8000... >> 63) & 1 = 1 → No Execute

### CALCULATIONS TO FORCE:
```
EXAMPLE 2: Entry = 0x0000000000000000
Bit 0 = 0 → Not Present
All other bits meaningless (MMU ignores them)

EXAMPLE 3: Entry = 0x80000002FAE00080
0x80 = 1000_0000
Bit 0 = 0 → Not Present (TRAP: bit 7 is set but P=0!)
Bit 7 = 1 → This would be huge page IF present

TRAP: Checking PS bit when P=0 is meaningless
```

### DATA STRUCTURES TO DRAW:
```
PTE Format (64 bits):
┌────┬───────────────────────────────────────┬──────────────┐
│ 63 │              51:12                    │    11:0      │
│ NX │     Physical Address (40 bits)        │    Flags     │
└────┴───────────────────────────────────────┴──────────────┘

Flags Detail (bits 11:0):
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
│11 │10 │ 9 │ 8 │ 7 │ 6 │ 5 │ 4 │ 3 │ 2 │ 1 │ 0 │
│   │   │   │ G │PS │ D │ A │PCD│PWT│U/S│R/W│ P │
└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
```

### FAILURE PREDICTIONS:
F1. Checking flags when P=0 → invalid interpretation
F2. Forgetting NX is bit 63, not in low 12 bits
F3. Confusing PS bit at different levels (L3 vs L2)

---

## DRIVER 05: huge_driver.c - CHECK HUGE PAGE BIT

### QUESTIONS TO GRILL:
01. At which levels can PS=1 appear? L3 (PDPT) and L2 (PD) only.
02. PS=1 at L3 → 1GB page. PS=1 at L2 → 2MB page.
03. PS=1 at L4 → Reserved/Invalid. PS=1 at L1 → Reserved/Invalid.
04. Entry = 0x80000002FAE001A1. Extract PS bit.
05. 0xA1 = 1010_0001. Bit 7 = (0xA1 >> 7) & 1 = 1. PS = 1.
06. If at L2, this is 2MB huge page.
07. Physical base extraction for 2MB: Entry & 0x000FFFFFFFE00000
08. 0x80000002FAE001A1 & 0x000FFFFFFFE00000 = ?
09. Need to zero bits [20:0] and [63:52].
10. If at L3 (1GB): Entry & 0x000FFFFFC0000000

### CALCULATIONS TO FORCE:
```
2MB MASK DERIVATION:
Bits [51:21] = address (31 bits)
Bits [20:0] = offset within 2MB = 21 bits
2^21 = 2,097,152 = 2MB ✓

1GB MASK DERIVATION:
Bits [51:30] = address (22 bits)
Bits [29:0] = offset within 1GB = 30 bits
2^30 = 1,073,741,824 = 1GB ✓

TRAP: Using wrong mask for wrong page size
TRAP: Forgetting to check P bit before checking PS bit
```

### DATA STRUCTURES TO DRAW:
```
4KB Page Walk:  L4 → L3 → L2 → L1 → Page (4 levels)
2MB Huge Walk:  L4 → L3 → L2 → Page (3 levels, PS=1 at L2)
1GB Huge Walk:  L4 → L3 → Page (2 levels, PS=1 at L3)

Address Bits Used:
┌─────────────────────────────────────────────────────────────┐
│ 4KB:  [51:12] = 40 bits address, [11:0] = 12 bits offset    │
│ 2MB:  [51:21] = 31 bits address, [20:0] = 21 bits offset    │
│ 1GB:  [51:30] = 22 bits address, [29:0] = 30 bits offset    │
└─────────────────────────────────────────────────────────────┘
```

### FAILURE PREDICTIONS:
F1. Checking PS at L4 or L1 → invalid
F2. Using 4KB mask for 2MB page → wrong address
F3. CPU without pdpe1gb flag → 1GB pages unsupported

---

## DRIVER 06: addr_driver.c - EXTRACT PHYSICAL ADDRESS

### QUESTIONS TO GRILL:
01. Entry = 0x80000002FAE00067. What is physical address?
02. Assuming 4KB page: Mask = 0x000FFFFFFFFFF000
03. 0x80000002FAE00067 & 0x000FFFFFFFFFF000 = ?
04. Step: 0x8000... has bit 63 set. That gets masked out.
05. 0x...00067 has low 12 bits. Those get masked out.
06. Result = 0x00000002FAE00000
07. Verify: Is this 4KB aligned? 0x...000 ends in 3 zeros = 12 bits = ✓
08. If this were 2MB entry: Mask = 0x000FFFFFFFE00000
09. 0x80000002FAE00067 & 0x000FFFFFFFE00000 = 0x00000002FAE00000
10. Same result because FAE00 already ends in 00000 (2MB aligned)

### CALCULATIONS TO FORCE:
```
HARD EXAMPLE: Entry = 0x00000003FFFFF067
4KB mask: 0x00000003FFFFF067 & 0x000FFFFFFFFFF000 = 0x00000003FFFFF000
2MB mask: 0x00000003FFFFF067 & 0x000FFFFFFFE00000 = 0x00000003FFE00000

DIFFERENCE: 
4KB gives 0x3FFFFF000
2MB gives 0x3FFE00000
                ↑↑↑↑↑
These bits differ! WRONG address if using wrong mask.

TRAP: Using 4KB mask for 2MB page loses 9 bits of offset
```

### DATA STRUCTURES TO DRAW:
```
MASK COMPARISON:
4KB: 0x000FFFFFFFFFF000
     0000 0000 0000 1111 1111 1111 1111 1111 1111 1111 1111 1111 0000 0000 0000
                    ↑bits 51                              bit 12↑    ↑bit 0

2MB: 0x000FFFFFFFE00000
     0000 0000 0000 1111 1111 1111 1111 1111 1111 1111 1110 0000 0000 0000 0000
                    ↑bits 51                        bit 21↑         ↑bit 0

1GB: 0x000FFFFFC0000000
     0000 0000 0000 1111 1111 1111 1111 1111 1100 0000 0000 0000 0000 0000 0000
                    ↑bits 51              bit 30↑                   ↑bit 0
```

### FAILURE PREDICTIONS:
F1. Wrong mask for page size → wrong physical address
F2. Not clearing NX bit (63) → garbage in high bits
F3. Using masked address directly as pointer → crash

---

## DRIVER 07: walk4kb_driver.c - FULL 4KB PAGE WALK

### QUESTIONS TO GRILL:
01. Starting point: CR3 = 0x1337A3000. VA = 0xFFFFFFFF81000000.
02. Extract PML4 index from VA.
03. 0xFFFFFFFF81000000 >> 39 = ? (careful: sign extension!)
04. Kernel VA is negative (bit 47 = 1). Result after shift has leading 1s.
05. & 0x1FF to mask: gets index correctly.
06. Read PML4[index]. Get entry. Mask to get PDPT base.
07. Repeat for PDPT[pdpt_idx]. Check PS bit.
08. If PS=0, continue. Get PD base.
09. Repeat for PD[pd_idx]. Check PS bit.
10. If PS=0, continue. Get PT base.
11. Read PT[pt_idx]. Get page base.
12. Final physical = page_base | (VA & 0xFFF)

### CALCULATIONS TO FORCE:
```
VA = 0xFFFFFFFF81000000 (Kernel text)

PML4 index:
0xFFFFFFFF81000000 >> 39 = 0x1FFFFFF03 (with sign extension)
0x1FFFFFF03 & 0x1FF = 0x103 & 0x1FF = 259

Wait, 0x103 = 259. But 0x1FF = 511. 259 & 511 = 259. ✓
Actually: 0x1FFFFFF03 & 0x1FF = 0x103 = 259. ✗
Check: 0x1FF = 0b111111111. 0x103 = 0b100000011.
0x103 & 0x1FF = 0x103 = 259. 

TRAP: Is 259 valid? Valid range [256,511] for kernel.
259 > 256. ✓ This is in kernel half.

PDPT index:
0xFFFFFFFF81000000 >> 30 = 0x3FFFFFFFE04
& 0x1FF = 0x004 = 4

PD index:
0xFFFFFFFF81000000 >> 21 = 0x7FFFFFFFC08
& 0x1FF = 0x008 = 8

PT index:
0xFFFFFFFF81000000 >> 12 = 0xFFFFFFFF81000
& 0x1FF = 0x000 = 0

Offset:
0xFFFFFFFF81000000 & 0xFFF = 0x000

∴ Walk path: PML4[259] → PDPT[4] → PD[8] → PT[0] → Page + 0
```

### DATA STRUCTURES TO DRAW:
```
PAGE WALK TRACE:
                                                              
CR3=0x1337A3000 ──→ PML4 @ 0x1337A3000                       
                      │                                       
                      ├─[259]─→ entry=0x???????? ─mask→ PDPT_base
                      │                                       
                      └─→ PDPT @ PDPT_base                    
                            │                                 
                            ├─[4]─→ entry=0x???????? ─mask→ PD_base
                            │                                 
                            └─→ PD @ PD_base                  
                                  │                           
                                  ├─[8]─→ entry=0x???????? ─mask→ PT_base
                                  │                           
                                  └─→ PT @ PT_base            
                                        │                     
                                        ├─[0]─→ entry=0x???????? ─mask→ Page_base
                                        │                     
                                        └─→ Physical = Page_base | 0x000
```

### FAILURE PREDICTIONS:
F1. Not checking P bit at each level → dereferencing garbage
F2. Hitting PS=1 unexpectedly → should stop walk early
F3. Sign extension confusion on kernel addresses
F4. Using wrong mask for non-4KB pages

---

## DRIVER 08: walk2mb_driver.c - 2MB HUGE PAGE WALK

### QUESTIONS TO GRILL:
01. Direct map region starts at page_offset_base.
02. page_offset_base = 0xFFFF89DF00000000 (from kernel).
03. Walk this address. Expect PS=1 at L2.
04. Calculate indices for 0xFFFF89DF00000000.
05. PML4: (0xFFFF89DF00000000 >> 39) & 0x1FF = ?
06. PDPT: (0xFFFF89DF00000000 >> 30) & 0x1FF = ?
07. PD:   (0xFFFF89DF00000000 >> 21) & 0x1FF = ?
08. At PD level, check PS bit. If PS=1, stop walking.
09. Physical = (PD_entry & 0x000FFFFFFFE00000) | (VA & 0x1FFFFF)
10. 0x1FFFFF = 2^21 - 1 = 2,097,151 bytes offset range

### CALCULATIONS TO FORCE:
```
VA = 0xFFFF89DF00000000

0xFFFF89DF00000000 >> 39:
0xFFFF89DF00000000 = -114,706,598,346,883,072 (signed)
>> 39 (arithmetic) = sign extends
Unsigned: 0xFFFF89DF00000000 / 2^39 = ?

Let's compute:
0xFFFF89DF00000000 = 18,446,027,475,362,668,544 (unsigned)
2^39 = 549,755,813,888
18,446,027,475,362,668,544 / 549,755,813,888 = 33,554,179.99...

Hmm, let's do hex:
0xFFFF89DF00000000 >> 39
= 0x1FFFF13BE (approximately)
& 0x1FF = 0x1BE = 446

TRAP: Must verify this calculation by hand
```

### FAILURE PREDICTIONS:
F1. Not recognizing PS=1 → continuing past L2 → crash
F2. Using 4KB offset mask (0xFFF) instead of 2MB (0x1FFFFF)
F3. Kernel direct map might use 1GB pages on some systems

---

## DRIVER 09: walk1gb_driver.c - 1GB HUGE PAGE SEARCH

### QUESTIONS TO GRILL:
01. 1GB pages: PS=1 at L3 (PDPT level).
02. Check CPU flag: pdpe1gb. If missing, 1GB unsupported.
03. cat /proc/cpuinfo | grep pdpe1gb → present?
04. To find 1GB pages: scan all PDPT entries for PS=1.
05. Each PML4 entry covers 512GB.
06. Each PDPT entry covers 1GB.
07. Total entries to scan: up to 512 × 512 = 262,144
08. Mask for 1GB physical base: 0x000FFFFFC0000000
09. Offset within 1GB: 30 bits = 0x3FFFFFFF = 1,073,741,823

### CALCULATIONS TO FORCE:
```
COVERAGE MATH:
PML4[256:511] = kernel half = 256 PML4 entries
Each PML4 → 512 PDPT entries
256 × 512 = 131,072 PDPT entries to scan (worst case)

If 1GB page found at PML4[273] PDPT[100]:
Virtual base = ?
PML4 index 273 → bits [47:39] = 273 = 0x111 (9 bits)
Wait, 273 > 255. Need sign extension for kernel.
VA = 0xFFFF... prefix + (273 << 39) + (100 << 30)

This is getting complex. Need step by step.

TRAP: Reconstructing VA from indices requires understanding canonical addresses
```

### FAILURE PREDICTIONS:
F1. CPU without pdpe1gb → no 1GB pages exist
F2. Scanning all entries takes time (O(262144) reads)
F3. Wrong offset mask (30 bits vs 21 bits)

---

## DRIVER 10: va_driver.c - COMPARE __VA MACRO

### QUESTIONS TO GRILL:
01. __va(phys) = phys + page_offset_base
02. Verify: __va(0) = page_offset_base = 0xFFFF89DF00000000
03. __va(0x1000) = 0xFFFF89DF00000000 + 0x1000 = 0xFFFF89DF00001000
04. virt_to_phys(virt) = virt - page_offset_base
05. Verify inverse: virt_to_phys(__va(X)) = X
06. When does this fail? Addresses outside direct map.
07. Direct map size = Total physical RAM = ~16GB on this machine.
08. Max valid physical for __va: 0x3EA0A8000 (16GB boundary)

### CALCULATIONS TO FORCE:
```
RAM = 15776276 kB = 15,776,276 × 1024 bytes = 16,154,906,624 bytes
= 0x3C3753000 bytes? Let's verify:
15,776,276 × 1024 = 16,154,906,624
16,154,906,624 / (1024^3) = 15.046 GB ✓

Max physical address = 0x3C3753000 (approximately)
__va(0x3C3753000) = 0xFFFF89DF00000000 + 0x3C3753000 = 0xFFFF89E2C3753000

TRAP: page_offset_base is KASLR randomized. Different each boot.
TRAP: Addresses beyond RAM are holes (memory-mapped I/O, etc.)
```

### FAILURE PREDICTIONS:
F1. Using __va on physical address > RAM size → undefined
F2. Using __va for MMIO addresses → wrong result
F3. Different kernel → different page_offset_base

---

## DRIVERS 11-20: SUMMARY OF GRILLING NEEDED

### DRIVER 11: pml4_driver.c
- Dump all 512 entries
- Calculate virtual range covered by each present entry
- TRAP: Canonical address reconstruction

### DRIVER 12: pid_driver.c
- Compare CR3 across processes
- Each process has different PML4
- TRAP: Kernel threads have mm=NULL

### DRIVER 13: zone_driver.c
- DMA: 0-16MB, DMA32: 16MB-4GB, Normal: 4GB+
- Calculate zone sizes from real RAM
- TRAP: Zone boundaries are fixed regardless of RAM size

### DRIVER 14: flags_driver.c
- struct page flags: 64 bits of state
- pfn_to_page(pfn) → struct page*
- TRAP: PageReferenced(), PageActive() may not exist in newer kernels

### DRIVER 15: vma_driver.c
- Walk mm->mmap (now requires VMA_ITERATOR)
- Each VMA: [start, end), permissions
- TRAP: Locking (mmap_read_lock) required

### DRIVER 16: slab_driver.c
- kmem_cache_create(name, size, align, flags, ctor)
- Object size must match cache size
- TRAP: Cache name appears in /proc/slabinfo

### DRIVER 17: buddy_driver.c
- alloc_pages(GFP_KERNEL, order)
- order 0 = 1 page, order 1 = 2 pages, ...
- TRAP: Max order = 10 or 11 depending on config

### DRIVER 18: tlb_driver.c
- TLB flush: write CR3, or invlpg
- Flush penalty: 100+ cycles per miss after
- TRAP: Global pages not flushed by CR3 write

### DRIVER 19: cow_driver.c
- fork() sets RW=0 on shared pages
- Write triggers fault → copy
- TRAP: Can't observe COW directly from /proc

### DRIVER 20: swap_driver.c
- Swap entry format when P=0
- Type (5 bits) + Offset (58 bits)
- TRAP: si_swapinfo() not exported, use si_meminfo()

═══════════════════════════════════════════════════════════════════════════════
META-QUESTIONS: WHAT IS NOT BEING ASKED?
═══════════════════════════════════════════════════════════════════════════════

01. How do we know page_offset_base if it's randomized?
02. How do we verify our calculations match real hardware?
03. What if the kernel data structures changed in 6.14?
04. How do we handle failures gracefully?
05. How do we test without crashing the system?
06. What order should we teach these concepts?
07. How do we debug when module crashes?
08. How do we correlate /proc output with dmesg?

═══════════════════════════════════════════════════════════════════════════════
FAILURE CATALOG: ALL PREDICTED FAILURES
═══════════════════════════════════════════════════════════════════════════════

```
CATEGORY A: WRONG CALCULATION
A1. Wrong shift amount → wrong index
A2. Wrong mask → wrong address
A3. Sign extension on kernel addresses
A4. Integer overflow on large values
A5. Off-by-one in array bounds [0,511]

CATEGORY B: WRONG ASSUMPTION
B1. Assuming all entries are present (P=1)
B2. Assuming all pages are 4KB (no huge pages)
B3. Assuming direct map uses 2MB (might be 1GB or 4KB)
B4. Assuming exported symbols exist

CATEGORY C: KERNEL API CHANGES
C1. PageReferenced() removed in newer kernels
C2. for_each_process() needs RCU lock
C3. VMA iteration changed from mmap to VMA_ITERATOR
C4. struct sysinfo field names

CATEGORY D: SECURITY/PERMISSIONS
D1. Reading CR3 requires ring 0
D2. Accessing other process mm requires capabilities
D3. /proc files need correct permissions

CATEGORY E: HARDWARE LIMITATIONS
E1. 44-bit physical vs 48-bit virtual (this CPU)
E2. pdpe1gb flag for 1GB pages
E3. PCID support flag
```

═══════════════════════════════════════════════════════════════════════════════
NEXT STEPS: WHAT TO DO WITH THIS PLAN
═══════════════════════════════════════════════════════════════════════════════

1. For each driver, create a companion .md file
2. Each .md file contains:
   - Pre-filled calculations to verify
   - Diagrams with real addresses
   - Failure cases to test
   - Questions to answer by hand
3. User must work through calculations before looking at code
4. Code contains NO solutions, only measurement
5. User compares their calculation with module output
