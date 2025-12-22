01. String object on stack: 3 members → ptr (8 bytes) + size (8 bytes) + capacity (8 bytes) = ____ bytes total.
02. Stack address: MyString s at 0x7FFF0000 → s.ptr at 0x7FFF0000, s.size at 0x7FFF0008, s.capacity at 0x7FFF0010.
03. Heap allocation: "hello" = 5 chars + 1 null = 6 bytes minimum → allocate 8 bytes (power of 2).
04. Heap address: new char[8] returns 0xA000 → bytes 0xA000-0xA007.
05. After construction: s.ptr=0xA000, s.size=5, s.capacity=8.
06. Memory at heap: 0xA000='h', 0xA001='e', 0xA002='l', 0xA003='l', 0xA004='o', 0xA005='\0', 0xA006=?, 0xA007=?.
07. Copy constructor: MyString s2 = s1 → s2.ptr = new char[8] = 0xB000 → copy 6 bytes from 0xA000 to 0xB000.
08. After copy: s1.ptr=0xA000, s2.ptr=0xB000 → independent buffers → deep copy ✓.
09. Move constructor: MyString s3 = std::move(s1) → s3.ptr = s1.ptr = 0xA000 → s1.ptr = nullptr → no allocation.
10. After move: s3.ptr=0xA000, s1.ptr=0x0, s1.size=0, s1.capacity=0 → s1 is empty shell.
11. Destructor: delete[] ptr → if ptr=0xA000 → frees 0xA000-0xA007 → if ptr=nullptr → no-op.
12. operator[]: s[2] → *(s.ptr + 2) → *(0xA000 + 2) → *0xA002 → 'l'.
13. size(): return m_size → 5.
14. capacity(): return m_capacity → 8.
15. c_str(): return m_ptr → 0xA000 → null-terminated.
16. append("!"): current size=5, new size=6, capacity=8 → 6 ≤ 8 → no realloc.
17. append("!"): copy '!' to 0xA005, write '\0' to 0xA006, m_size=6.
18. append(" world"): current size=6, add 6 chars, new size=12 → 12 > 8 → realloc needed.
19. realloc: new capacity = old × 2 = 16 → new char[16] = 0xC000.
20. realloc: copy 7 bytes (including '\0') from 0xA000 to 0xC000.
21. realloc: delete[] 0xA000 → free old buffer.
22. realloc: m_ptr = 0xC000, m_capacity = 16.
23. append: copy " world" (6 chars) to 0xC000+6 = 0xC006.
24. append: write '\0' at 0xC00C, m_size = 12.
25. reserve(100): if 100 > m_capacity → realloc to 100 → new char[100].
26. reserve(5): if 5 ≤ m_capacity → no-op.
27. clear(): m_size = 0, m_ptr[0] = '\0' → does NOT deallocate.
28. shrink_to_fit(): realloc to m_size+1 → delete old, alloc new, copy.
29. operator+: MyString operator+(const MyString& a, const MyString& b) → new string, size = a.size + b.size.
30. operator+=: same as append.
31. operator==: compare size first (fast path), then memcmp.
32. operator<: lexicographic → memcmp, then size tiebreaker.
33. Rule of 5: destructor, copy ctor, copy assign, move ctor, move assign.
34. Copy assignment: if (this != &other) → delete[] m_ptr → alloc new → copy.
35. Move assignment: if (this != &other) → delete[] m_ptr → steal → set other to null.
36. Self-assignment check: s = s → without check → delete[] ptr → use deleted memory → UB ✗.
37. Small String Optimization (SSO): if size ≤ 15 → store in stack buffer, no heap.
38. SSO layout: union { char* ptr; char buf[16]; } → 16 bytes inline.
39. SSO flag: use high bit of capacity or separate bool.
40. SSO benefit: "hello" (5 chars) → no malloc, no free, cache-friendly.
41. TRAP: forget null terminator → c_str() returns garbage after string → UB.
42. TRAP: off-by-one in capacity → size=8, capacity=8, append 1 char → overflow.
43. TRAP: double free → copy without deep copy → both delete same ptr.
44. TRAP: use after move → s1 moved to s3, then s1[0] → nullptr dereference.
45. TRAP: iterator invalidation → append causes realloc → old pointers invalid.
