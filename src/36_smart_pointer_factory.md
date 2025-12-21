01. DRAW shared_ptr<Widget> sp at 0x7FFF0000. sp contains: ptr = 0xA000 (Widget*), ctrl = 0xB000 (control block*). CALCULATE sizeof(shared_ptr) = 16 bytes = 2 pointers × 8 bytes ✓
02. DRAW control block at 0xB000: |strong_count=1|weak_count=1|deleter|allocator|. CALCULATE sizeof(control_block) ≥ 16 bytes (2 atomics + vtable). strong_count=1 → 1 shared_ptr owns Widget. weak_count=1 → includes "self" reference ✓
03. DRAW Widget at 0xA000: |data=42|. CALCULATE total memory = sizeof(sp) + sizeof(ctrl) + sizeof(Widget) = 16 + 16 + 4 = 36 bytes minimum. COMPARE to raw pointer: sizeof(Widget*) = 8 bytes. OVERHEAD = 36-8 = 28 bytes ✓
04. COPY shared_ptr: sp2 = sp. STEP 1: sp2.ptr ← sp.ptr = 0xA000. STEP 2: sp2.ctrl ← sp.ctrl = 0xB000. STEP 3: ++ctrl->strong_count. DRAW control block: strong_count = 1+1 = 2. VERIFY both sp and sp2 point to same Widget ✓
05. ■ GROUND: sp@0x7FFF0000, sp2@0x7FFF0010, both→Widget@0xA000, ctrl@0xB000 has strong=2, weak=1 ■ NEXT: destroy one shared_ptr ■
06. DESTROY sp2 (goes out of scope). STEP 1: --ctrl->strong_count. strong_count = 2-1 = 1. STEP 2: strong_count > 0 → Widget NOT deleted. VERIFY Widget still exists at 0xA000 ✓
07. DESTROY sp (goes out of scope). STEP 1: --ctrl->strong_count. strong_count = 1-1 = 0. STEP 2: strong_count == 0 → delete Widget at 0xA000. STEP 3: --ctrl->weak_count. weak_count = 1-1 = 0. STEP 4: weak_count == 0 → delete control block at 0xB000. VERIFY all memory freed ✓
08. ■ GROUND: last shared_ptr destruction triggers Widget delete when strong=0, control block delete when weak=0 ■ NEXT: weak_ptr ■
09. DRAW weak_ptr<Widget> wp at 0x7FFF0020. wp contains: ptr = 0xA000, ctrl = 0xB000 (same as sp). COPY wp = sp. STEP 1: wp.ptr ← sp.ptr. STEP 2: wp.ctrl ← sp.ctrl. STEP 3: ++ctrl->weak_count. DRAW: weak_count = 1+1 = 2. strong_count unchanged = 1 ✓
10. CALL wp.lock(). CHECK strong_count > 0? 1 > 0 → ✓. CREATE shared_ptr<Widget> sp3 from wp. ++strong_count = 2. RETURN sp3. VERIFY Widget accessible via sp3 ✓
11. DESTROY sp (last shared_ptr). strong_count = 2-1 = 1. DESTROY sp3. strong_count = 1-1 = 0. Widget DELETED at 0xA000. weak_count = 2. control block STILL EXISTS because weak_count > 0 ✓
12. CALL wp.lock() AFTER Widget deleted. CHECK strong_count > 0? 0 > 0 → ✗. RETURN nullptr (empty shared_ptr). VERIFY wp.expired() == true ✓
13. ■ GROUND: weak_ptr does NOT prevent Widget destruction, only keeps control block alive for lock() check ■ NEXT: unique_ptr ■
14. DRAW unique_ptr<Widget> up at 0x7FFF0040. up contains: ptr = 0xC000 (Widget*). CALCULATE sizeof(unique_ptr) = 8 bytes = 1 pointer. NO control block. OVERHEAD vs raw pointer = 0 bytes ✓
15. MOVE unique_ptr: up2 = std::move(up). STEP 1: up2.ptr ← up.ptr = 0xC000. STEP 2: up.ptr ← nullptr. VERIFY up == nullptr, up2 owns Widget ✓
16. COPY unique_ptr: up3 = up2. COMPILE ERROR: unique_ptr copy constructor deleted. VERIFY single ownership enforced at compile time ✓
17. ■ GROUND: unique_ptr = single owner, zero overhead, move-only. shared_ptr = multiple owners, 28+ bytes overhead, copyable. weak_ptr = observer, no ownership ■ NEXT: make_shared optimization ■
18. CALL make_shared<Widget>(42). SINGLE allocation: ctrl+Widget together at 0xD000. DRAW: |ctrl|Widget| contiguous. SIZE = 16+4 = 20 bytes (no separate allocations). COMPARE to new Widget + new control_block = 2 allocations ✓
19. CACHE PERFORMANCE: make_shared → ctrl and Widget in same cache line. new Widget → 2 cache lines. SPEEDUP = 50% fewer cache misses for access pattern ctrl→Widget ✓
20. ■ GROUND: make_shared combines allocations, better cache locality, exception-safe ■

---FAILURES---
F1. shared_ptr<Widget> sp(new Widget); shared_ptr<Widget> sp2(new Widget); sp = sp2; → original Widget leaked if no other owner → ✗ (actually safe, sp's Widget deleted first)
F2. Widget* raw = new Widget; shared_ptr<Widget> sp1(raw); shared_ptr<Widget> sp2(raw); → TWO control blocks for SAME Widget → double-free → ✗
F3. weak_ptr<Widget> wp; auto sp = wp.lock(); → wp never initialized → lock() returns nullptr → dereference causes crash → ✗
F4. shared_ptr<Widget[]> arr(new Widget[10]); → pre-C++17: uses delete instead of delete[] → undefined behavior → ✗
F5. circular reference: A→shared_ptr<B>, B→shared_ptr<A> → strong_count never reaches 0 → memory leak → ✗

---AXIOMATIC CHECK---
Line 01: Introduced shared_ptr layout → derived from observing ptr+ctrl structure in <memory> header
Line 02: Introduced control block → derived from need to track ownership count for multiple shared_ptrs
Line 09: Introduced weak_ptr → derived from need to observe without owning (break circular refs)
Line 14: Introduced unique_ptr → derived from observing shared_ptr overhead when single ownership sufficient
Line 18: Introduced make_shared → derived from observing 2 separate allocations in line 03
NO JUMPING AHEAD: Each smart pointer type derived from limitation of previous.
