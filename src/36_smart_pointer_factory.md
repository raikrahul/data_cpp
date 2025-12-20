# Problem 36::01. DRAW MEMORY LAYOUT [0x7FF0]. Control Block for `shared_ptr<int>`. [0x7FF0]=StrongRef(1) [4 bytes]. [0x7FF4]=WeakRef(0) [4 bytes]. [0x7FF8]=DeleterPtr [8 bytes]. [0x8000]=AllocatorPtr [8 bytes]. Total Control Block = 24 bytes. DRAW Data [0x9000] = 42 [4 bytes]. POINTER GRAPH: `shared_ptr` Object [Stack] -> [0x7FF0] (Control) -> [0x9000] (Data). **Why**: Indirect ownership. The `shared_ptr` does not own the data directly; it owns the *Control Block* which owns the data. **Overhead Calculation**: Data=4 bytes. Metadata=24 bytes. Overhead Ratio = 24/4 = 600%. **Cache Miss Probability**: High. Control Block and Data are separate allocations if using `new`. **Optimization**: `std::make_shared` fuses them. DRAW Fused Layout: [0x7FF0] Control .. [0x8008] Data. Contiguous. **Action**: Write code to print `sizeof` header overhead. `struct Control { atomic<int> s; atomic<int> w; void* d; void* a; };`.
# Problem 36: Smart Pointer Factory & Observer

01. 1. **Axiomatic Worksheet & Memory Traces**
02. 2. `auto p = make_shared<int>(42);` → Stack `p` at `0x1000` (8B) → Heap `0x2000` (32B block) → CtrlBlock `0x2000` (8B vptr + 4B strong=1 + 4B weak=0) → Data `0x2020` (4 bytes = 42). Total `32B`. `sizeof(p)=8`. `*p=42`. `p.use_count()=1`. ✓
03. 3. `int x=7; auto p = make_shared<int>(x);` → `x` at `0x1000` (4B) → `p` at `0x1008` → Heap `0x3000` → `*p` is copy of `x` at `0x3010`. `x=7`, `*p=7`. `p.get()=0x3010`. Independent lifetimes. ✓
04. 4. `auto p1 = make_shared<vector<int>>(4, 100);` → `p1` at `0x1000` → Heap CtrlBlock `0x4000` → Vector Object `0x4010` (24B: size=4, cap=4, ptr=`0x5000`) → Heap Array `0x5000` (16B: 4x4B ints). Total managed `48+16` (allocator dependent). `(*p1)[0]=100`. ✓
05. 5. `auto p2 = p1;` → `p2` at `0x1008` copies `p1` (which is `0x4000` or `0x4010` depends on impl, conceptual `0x4000` managed ptr). Strong ref `0x4008` increments 1→2 (atomic). `p1.use_count()=2`. Aliasing same object. ✓
06. 6. `(*p2)[0] = 200;` → Deref `p2` to vector `0x4010` → Deref vector ptr `0x5000` → Write `200` at `0x5000`. `(*p1)[0]` sees `200`. ✓
07. 7. `p1.reset();` → `p1` becomes `nullptr`. Strong ref `0x4008` decrements 2→1. Object stays. `p2` valid. ✓
08. 8. `p2.reset();` → `p2` becomes `nullptr`. Strong ref 1→0. `0x4000` (Ctrl) calls destructor of vector `0x4010`. Vector frees `0x5000`. Ctrl block freed. All memory reclaimed. ✓
09. 9. `{ auto p = make_shared<int>(42); }` → Scope entry: alloc `0x6000`. Scope exit: `p` dtor → ref dec → 0 → free `0x6000`. Stack pop. ✓
10. 10. `auto p3 = make_unique<int>(42);` → `p3` at `0x1000` (8B) holds `0x7000`. `0x7000` holds `42` (4B). No ctrl block. Overhead 0. `*p3=42`. ✓
11. 11. `unique_ptr<int> p4;` → `p4` is `nullptr` (`0x0`). `(bool)p4` is false. ✓
12. 12. `p4 = p3;` → **COMPILE ERROR**. Copy deleted. `unique_ptr` owns uniquely. Must move. ✗
13. 13. `p4 = std::move(p3);` → `p4` takes `0x7000`. `p3` becomes `nullptr`. Ownership transfer. `*p4=42`. `p3` is empty. ✓
14. 14. `vector<unique_ptr<int>> v(10);` → `v` at `0x1000`. Heap array `0x8000` (80B: 10x8B ptrs). All `nullptr`. Total `24 (vec) + 80 (arr) = 104B`. ✓
15. 15. `loop i=0..9 v[i]=make_unique<int>(i);` → `v[0]` allocs `0x9000` (4B). `v[1]` allocs `0x9010`. ... 10 separate heap allocs. ✓
16. 16. `for(const auto& ptr : v) cout << *ptr;` → Iterates references to unique_ptrs. No copies. Prints 0..9. ✓
17. 17. `vector<unique_ptr<array<float,2>>> p; p.resize(5);` → `p` `0x1000` → `ptr` `0xa000` (40B: 5x8B). Init nulls. ✓
18. 18. `p[i] = make_unique...` → `0xa000` points to `0xc000` (8B: 2x4B floats). `x[i], y[i]` copied in. ✓
19. 19. `rotate` function copies `(*a)[0]` to temp. Negates one. Swaps. In-place modification of heap data `0xc000`. ✓
20. 20. `for_each(p.begin(), p.end(), rotate);` → Iterates. Applies rotation to each `unique_ptr` target. Correctly transforms (x,y) → (-y, x). ✓
21. 21. **Failures Prediction**
22. 22. `shared_ptr<int> p = &x;` → Bad. `p` thinks it owns stack `x`. Double free on exit. ✗
23. 23. `unique_ptr` copy attempt `p2 = p1` → Compiler error C2280. Must use `move`. ✗
24. 24. `make_shared` vs `new`. `new` creates 2 blocks (ctrl + obj). `make_shared` creates 1 block (fused). Cache locality diff. ✓
25. 25. Cyclic Ref: `A` holds `shared_ptr<B>`, `B` holds `shared_ptr<A>`. Ref counts never 0. Leak. Sol: `weak_ptr`. ✓
26. 26. **Factory & Observer Logic**
27. 27. `ShapeFactory` returns `unique_ptr<Shape>`. Reasoning: Factory produces new object. Caller should own it. `unique_ptr` is perfect (movable, exclusive).
28. 28. `Subject` holds `vector<weak_ptr<Observer>>`. Reasoning: Observers exist independently. Subject shouldn't keep Observer alive (cycle risk if Obs owns Shape). `weak_ptr` allows checking `expired()` before notify.
29. 29. **Step-by-Step Execution Plan**
30. 30. `main` creates `shared_ptr<Observer> obs1` (Ref=1).
31. 31. Factory creates `unique_ptr<Shape> s`.
32. 32. `s->attach(obs1)`. `s` input takes `shared_ptr`, stores `weak_ptr`.
33. 33. `s->area()`. Calculates `28.27...`. Calls `notify()`.
34. 34. `notify` loops weak_ptrs. `lock()` → checks not null → calls `update()`.
35. 35. Output: "Obs 101 received...".
36. 36. `obs1.reset()` (Ref 1→0). Observer dies.
37. 37. `s->area()` again. `lock()` returns null. No output. Auto-cleanup of expired weak_ptrs (lazy or explicit).
