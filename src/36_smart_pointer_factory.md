```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ shared_ptr sp at 0x7FFF0000         control_block at 0xB000          Widget at 0xA000                          │
│ ├─ ptr = 0xA000 ─────────────────────────────────────────────────────→ |data=42|                               │
│ └─ ctrl = 0xB000 ───────────────────→ |strong=1|weak=1|deleter|                                                 │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ COPY sp2=sp: strong++ → strong=2 │ DESTROY sp2: strong-- → strong=1 │ DESTROY sp: strong=0 → delete Widget    │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. shared_ptr sp at 0x7FFF0000 = |ptr=0xA000|ctrl=0xB000|, sizeof=16=2×8 ✓
02. control_block at 0xB000 = |strong=1|weak=1|deleter|allocator|, sizeof≥16
03. Widget at 0xA000 = |data=42|, total=16+16+4=36 bytes, raw ptr=8 bytes, overhead=28 bytes
04. ■ shared_ptr overhead = 28 bytes vs raw pointer ■
05. sp2=sp → sp2.ptr=0xA000, sp2.ctrl=0xB000, ++strong → strong=2
06. ~sp2 → --strong → strong=1 → Widget NOT deleted (strong>0)
07. ~sp → --strong → strong=0 → delete Widget → --weak → weak=0 → delete ctrl
08. ■ strong=0 → delete object, weak=0 → delete control_block ■
09. weak_ptr wp=sp → wp.ptr=0xA000, wp.ctrl=0xB000, ++weak → weak=2, strong unchanged=1
10. wp.lock() → strong>0? 1>0 ✓ → create shared_ptr → ++strong → strong=2
11. ~sp, ~sp3 → strong=0 → delete Widget, weak=2 → ctrl survives
12. wp.lock() after delete → strong=0 → return nullptr → wp.expired()=true ✓
13. ■ weak_ptr: observes without owning, ctrl survives while weak>0 ■
14. unique_ptr up at 0x7FFF0040 = |ptr=0xC000|, sizeof=8, NO ctrl, 0 overhead
15. up2=std::move(up) → up2.ptr=0xC000, up.ptr=nullptr
16. up3=up2 → COMPILE ERROR: copy deleted, single ownership enforced
17. ■ unique_ptr: 0 overhead, move-only, single owner ■
18. make_shared<Widget>(42) → single allocation at 0xD000 = |ctrl|Widget| contiguous, sizeof=20
19. cache: ctrl+Widget same line, 1 miss vs 2 separate allocations
20. ■ make_shared: 1 allocation, cache friendly, exception safe ■
---FAILURES---
F1. sp1(raw), sp2(raw) with same raw → 2 control blocks → double-free → ✗
F2. circular: A→shared<B>, B→shared<A> → strong never 0 → leak → ✗
F3. shared_ptr<T[]> pre-C++17 → delete not delete[] → ✗
F4. weak_ptr never initialized → lock() → nullptr → crash on deref → ✗
F5. storing by value vector<Base> with Derived → slicing → ✗
