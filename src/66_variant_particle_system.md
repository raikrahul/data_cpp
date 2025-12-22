
01. Definition: Particle System → 3 Types: Fire, Smoke, Water.
02. Data Constraints: Fire{temp:float, life:float}, Smoke{density:float, life:float}, Water{viscosity:float, life:float}.
03. Struct Fire: [ temp(4) | life(4) ] → 8 bytes. Align: 4.
04. Struct Smoke: [ density(4) | life(4) ] → 8 bytes. Align: 4.
05. Struct Water: [ viscosity(4) | life(4) ] → 8 bytes. Align: 4.
06. Max Size = 8. Max Align = 4.
07. Variant<Fire, Smoke, Water>: Union(8) + Index(1 or 4?) + Padding.
08. Check Index Type: usually `unsigned char` if types < 256. Align of Index = 1.
09. Layout: [ Union (8) ] [ Index (1) ] [ Pad (3) → to align 4 ] → Total 12 bytes.
10. Wait! Align of Variant is MaxAlign(Fire, Smoke, Water) = 4.
11. Size = 12 bytes.
12. Verify: 8 (data) + 1 (tag) + 3 (pad) = 12. ✓

13. Virtual Inheritance Alternative.
14. Base `IParticle` { vptr(8) }.
15. Derived `VirtFire` : IParticle { vptr(8) | temp(4) | life(4) }.
16. Size: 16 bytes. Align: 8 (ptr).
17. Storage: `std::vector<IParticle*>`.
18. Vector Content: 8 bytes per pointer.
19. Real Memory: 8 (ptr) + 16 (object) + MallocOverhead(16 header) = 40 bytes/particle.
20. Indirection: Vector[i] → 0xHeap → Object.

21. Cache Line Density (64 bytes).
22. Variant Method: 64 / 12 = 5.33 → 5 particles/line.
23. linear access: 0x1000, 0x100C, 0x1018... → Prefetcher Happy ✓.
24. Virtual Method: 64 / 8 = 8 pointers/line.
25. Pointers point to random heap addresses (0x9000, 0x2000, 0xF000).
26. Access: Load Ptr (Cache Hit) → Dereference (Cache Miss ✗) → Vptr Load (Cache Hit/Miss) → Func Call.
27. Miss Rate: High.

28. YOUR JOB: CALCULATE SPECIFIC LOSS.
29. Count = 1,000,000 particles.
30. Variant Memory: 1,000,000 × 12 = 12 MB.
31. Virtual Memory: 1,000,000 × (8 ptr + 16 obj + 16 malloc_meta) = 40 MB.
32. Ratio: 3.33x memory overhead.

33. INSTRUCTION: Implement the benchmark in `66_variant_particle_system.cpp`.
34. Construct `std::vector<std::variant<...>>` size 1M.
35. Construct `std::vector<IParticle*>` size 1M.
36. Fill randomly (Fire/Smoke/Water).
37. Measure `update()` loop time for both.
38. EXPECTATION: Variant should be 2-3x faster due to cache locality and no virtual dispatch.
39. PREDICTION F1: If you store `Variant` in `vector<Variant*>`, you lose all benefits. Store by value `vector<Variant>`.
40. PREDICTION F2: Virtual destructors needed for `IParticle`.
41. PREDICTION F3: `std::visit` might be slower if compiler doesn't optimize jump table. compile with `-O3` or `-O2`.

42. HANDS-ON TASK 1: Calculate exact byte offset of `Water::viscosity` in a `vector<variant>` at index 5.
43. Base = 0x1000.
44. Stride = 12.
45. Index 5 → Offset 5 × 12 = 60.
46. Address = 0x103C.
47. Local offset inside variant: 0 (it's the first member of union).
48. Total Addr = 0x103C.

49. HANDS-ON TASK 2: Calculate exact addresses for Virtual method.
50. Vector Base = 0x2000.
51. Index 5 → Offset 5 × 8 = 40.
52. Addr of Ptr = 0x2028.
53. Value at 0x2028 = 0xHeapAddr (unknown).
54. ∴ Cannot predict address → Cannot prefetch → CPU Stalls.

55. EXERCISE: Draw the Jump Table for `update()` visitor.
56. Tags: 0=Fire, 1=Smoke, 2=Water.
57. Funcs: `updateFire`, `updateSmoke`, `updateWater`.
58. Table: [ &updateFire, &updateSmoke, &updateWater ].
59. ASM: `jmp [Table + tag * 8]`.
60. Show this in debugger mentally.
