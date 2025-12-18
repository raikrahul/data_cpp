01. struct Person { std::string name; int age; }; → sizeof(Person) = 32(string) + 4(int) + 4(pad) = 40 bytes ✓
02. Person p1{"Alice", 30}; @ Stack 0x7ffc_a000 → name @ offset 0, age @ offset 32 ✓
03. Person p2{"Alice", 25}; @ Stack 0x7ffc_a028 → different object, same name content ✓
04. SSO check: "Alice" length = 5 < 15 (SSO threshold) → stored inline in string buffer ✓
05. p1.name internal buffer @ 0x7ffc_a000+16 = 0x7ffc_a010 → contains "Alice\0" ✓
06. p2.name internal buffer @ 0x7ffc_a028+16 = 0x7ffc_a038 → contains "Alice\0" ✓
07. Memory comparison: 0x7ffc_a010 vs 0x7ffc_a038 → DIFFERENT ADDRESSES → wrong approach ✗
08. Content comparison: "Alice"[0..4] vs "Alice"[0..4] → 'A'=='A', 'l'=='l', 'i'=='i', 'c'=='c', 'e'=='e' → 5 char compares → true ✓
09. Trap #1: &p1.name == &p2.name → 0x7ffc_a000 == 0x7ffc_a028 → false (compares string object addresses) ✗
10. Trap #2: p1.name.c_str() == p2.name.c_str() → 0x7ffc_a010 == 0x7ffc_a038 → false (compares buffer pointers) ✗
11. Trap #3: p1.name.data() == p2.name.data() → same as c_str() → false ✗
12. Correct #1: p1.name == p2.name → calls std::string::operator==() → compares length then bytes → true ✓
13. Correct #2: p1.name.compare(p2.name) == 0 → returns 0 if equal, <0 if less, >0 if greater → true ✓
14. Correct #3: strcmp(p1.name.c_str(), p2.name.c_str()) == 0 → C-style null-terminated compare → true ✓
15. Heap case: Person p3{"VeryLongNameThatExceedsSSO", 40}; → length = 26 > 15 → heap allocation ✓
16. p3.name @ 0x7ffc_a050, heap buffer @ 0x5555_a000 containing "VeryLong..." ✓
17. Person p4{"VeryLongNameThatExceedsSSO", 45}; → heap buffer @ 0x5555_b000 (DIFFERENT heap) ✓
18. p3.name.c_str() = 0x5555_a000 ≠ p4.name.c_str() = 0x5555_b000 → pointer compare fails ✗
19. p3.name == p4.name → compares 26 bytes of content → true ✓
20. Performance: SSO compare = 5 bytes × 1 cycle = 5 cycles. Heap compare = 26 bytes + cache miss = 200 cycles ✓
21. Large scale: N=1000000 Person pairs, name length L=20 → 1000000 × 20 × 1 cycle = 20M cycles = 6.67ms @ 3GHz ✓
22. Hash approach: std::hash<string>{}(p1.name) → computes 64-bit hash → compare hashes → O(1) but false positives ✗
23. Hash collision: N=1M names, expected collisions = N²/2^64 = 10^12/10^19 ≈ 0.00005 per pair → 5 collisions total ✗
24. Byte-by-byte: for(i=0;i<len;i++) if(a[i]!=b[i]) return false; → same as operator== internally ✓
25. memcmp: memcmp(p1.name.data(), p2.name.data(), p1.name.size()) → requires size check first! ✗
26. Failure F1: memcmp without size check → p1.name="Alice"(5), p2.name="AliceX"(6) → memcmp(5) = equal → WRONG! ✗
27. Failure F2: Using strncmp with wrong length → strncmp(a,b,min(len1,len2)) → "Alice" vs "AliceX" → 0 (equal up to 5) ✗
28. Failure F3: Case sensitivity → "alice" != "Alice" → strcmp returns non-zero → need strcasecmp or tolower loop ✓
29. Edge case: Empty names → p1.name="" (length 0), p2.name="" → "" == "" → true ✓
30. Edge case: One empty → p1.name="Alice", p2.name="" → "Alice" == "" → false ✓
31. Edge case: Unicode → p1.name="日本" (6 bytes UTF-8), p2.name="日本" → byte compare works for exact match ✓
32. Edge case: Null in string → p1.name="A\0B" (3 bytes), p2.name="A\0C" → strcmp stops at \0 → WRONG! ✗
33. std::string handles embedded nulls: "A\0B".size()=3, compare all 3 bytes → correct ✓
34. Alternative: std::string_view → no allocation, just ptr+len → sameName(string_view a, string_view b) { return a==b; } ✓
35. Alternative: Hashing + verify → if(hash(a)==hash(b)) return a==b; else return false; → early exit for different ✓
36. Cost analysis: 
    | Method          | Best Case | Worst Case | Notes                    |
    |-----------------|-----------|------------|--------------------------|
    | operator==      | O(1)      | O(n)       | Early exit on length     |
    | compare()       | O(1)      | O(n)       | Same as ==               |
    | strcmp          | O(n)      | O(n)       | No length pre-check      |
    | memcmp          | O(n)      | O(n)       | Requires size==size      |
    | hash            | O(n)      | O(n)       | False positives possible |
37. Diagram: p1 vs p2 comparison flow
    ┌─────────────────────────────────────────────────────────────────────────┐
    │ Stack 0x7ffc_a000: Person p1                                            │
    │ ├── [0x7ffc_a000..0x7ffc_a01f] name: std::string (32 bytes)            │
    │ │   ├── [0x7ffc_a000..0x7ffc_a007] size = 5                            │
    │ │   ├── [0x7ffc_a008..0x7ffc_a00f] capacity = 15 (SSO)                 │
    │ │   └── [0x7ffc_a010..0x7ffc_a01f] buffer = "Alice\0.........."        │
    │ └── [0x7ffc_a020..0x7ffc_a023] age = 30 = 0x1e                         │
    │                                                                         │
    │ Stack 0x7ffc_a028: Person p2                                            │
    │ ├── [0x7ffc_a028..0x7ffc_a047] name: std::string (32 bytes)            │
    │ │   ├── [0x7ffc_a028..0x7ffc_a02f] size = 5                            │
    │ │   ├── [0x7ffc_a030..0x7ffc_a037] capacity = 15 (SSO)                 │
    │ │   └── [0x7ffc_a038..0x7ffc_a047] buffer = "Alice\0.........."        │
    │ └── [0x7ffc_a048..0x7ffc_a04b] age = 25 = 0x19                         │
    │                                                                         │
    │ Comparison: p1.name == p2.name                                          │
    │ Step 1: p1.name.size() (5) == p2.name.size() (5) ✓                     │
    │ Step 2: memcmp(0x7ffc_a010, 0x7ffc_a038, 5) → 0 (equal) ✓              │
    │ Result: true                                                            │
    └─────────────────────────────────────────────────────────────────────────┘
38. Why diagram: Shows that addresses are DIFFERENT but content is SAME → must compare content, not addresses
39. Why SSO matters: Short names avoid heap → buffer inside string object → &buffer = &string + 16
40. Punishment: Compare 1M pairs of 100-char names → 1M × 100 × 1ns = 100ms. With hash pre-filter: 1M × O(1) hash compare = 1ms + verification = 1.1ms → 100× faster for mostly-different names ✓
