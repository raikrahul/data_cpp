01. DRAW struct Person { std::string name; }. DRAW p1 at 0x7FFF0000: name.data() → 0x7FFF0010 (SSO buffer). DRAW p2 at 0x7FFF0040: name.data() → 0x7FFF0050 (SSO buffer). BOTH contain "Alice" (5 chars < 15 SSO threshold). VERIFY names stored INSIDE string object ✓
02. COMPARE &p1.name vs &p2.name. &p1.name = 0x7FFF0000. &p2.name = 0x7FFF0040. CALCULATE 0x7FFF0000 ≠ 0x7FFF0040. COMPARE: false. TRAP: comparing ADDRESSES, not CONTENT ✗
03. COMPARE p1.name == p2.name. STEP 1: operator==(string, string) called. STEP 2: compare sizes (5 == 5 ✓). STEP 3: memcmp("Alice", "Alice", 5) = 0. RESULT: true. CORRECT: comparing CONTENT ✓
04. COMPARE p1.name.c_str() == p2.name.c_str(). c_str() returns pointer to internal buffer. p1.name.c_str() = 0x7FFF0010. p2.name.c_str() = 0x7FFF0050. COMPARE pointers: false. TRAP: same content, different addresses ✗
05. ■ GROUND: &str compares string object addresses. str.c_str() compares buffer addresses. str == str compares content. ONLY == is correct for content comparison ■ NEXT: heap strings ■
06. DRAW p3.name = "VeryLongNameThatExceedsSSO" (26 chars > 15). MEMORY: p3 at 0x7FFF0080. name.data() → 0xA000 (heap allocated). SSO threshold exceeded → heap allocation ✓
07. DRAW p4.name = "VeryLongNameThatExceedsSSO". MEMORY: p4 at 0x7FFF00C0. name.data() → 0xB000 (different heap address). COMPARE c_str(): 0xA000 ≠ 0xB000 = false. CONTENT identical but addresses differ ✓
08. TRAP: never compare string content with pointer comparison. Always use operator== or compare() or strcmp() ✓
09. ■ GROUND: SSO = small string optimization (< 15 chars inline). Heap = large strings. Either way, different string objects have different buffer addresses ■ NEXT: memcmp trap ■
10. COMPARE memcmp(p1.name.c_str(), p2.name.c_str(), 5). p1.name = "Alice", p2.name = "Alice". memcmp("Alice", "Alice", 5) = 0. RESULT: strings equal ✓
11. TRAP: memcmp(p1.name.c_str(), p5.name.c_str(), 5) where p5.name = "AliceX". memcmp("Alice", "Alice", 5) = 0. BUT p5.name has 6 chars! memcmp only checks first 5 bytes. FALSE POSITIVE ✗
12. CORRECT: FIRST check p1.name.size() == p5.name.size(). 5 ≠ 6 → not equal. SKIP memcmp. SIZE check must come BEFORE byte comparison ✓
13. ■ GROUND: memcmp(a, b, n) compares n bytes regardless of string length. Always check .size() equality first ■ NEXT: compare() method ■
14. USE p1.name.compare(p2.name). RETURN VALUE: 0 if equal, <0 if p1 < p2, >0 if p1 > p2. compare() handles size and content. PREFERRED over manual memcmp ✓
15. LEXICOGRAPHIC ORDER: "Alice".compare("Bob") = -1 (A < B). "Bob".compare("Alice") = +1 (B > A). "Alice".compare("Alice") = 0 ✓
16. PARTIAL COMPARE: p1.name.compare(0, 3, "Ali") = compare first 3 chars. "Ali".compare("Ali") = 0 ✓
17. ■ GROUND: compare() = safe, handles length. memcmp() = unsafe without size check. strcmp() = C-style, null-terminated only ■ NEXT: sorting ■
18. DRAW vector<Person> v = {p2, p1} where p1.name="Alice", p2.name="Bob". SORT by name: std::sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.name < b.name; }). AFTER: v = {p1, p2} (Alice < Bob) ✓
19. TRAP: sort by pointer: [](auto& a, auto& b) { return &a.name < &b.name; }. SORTS by address order in memory. NOT alphabetical. UNDEFINED order across runs ✗
20. VERIFY sort correctness: use operator< which calls string::compare() internally. NEVER sort by address ✓

---FAILURES---
F1. if (&p1.name == &p2.name) → comparing addresses → always false for different objects → logic error → ✗
F2. if (p1.name.c_str() == p2.name.c_str()) → comparing buffer pointers → always false for different strings → ✗
F3. memcmp(a.c_str(), b.c_str(), a.size()) where b.size() < a.size() → reads beyond b's buffer → undefined behavior → ✗
F4. strcmp(a.c_str(), b.c_str()) on binary data with null bytes → stops at first \0 → incomplete comparison → ✗
F5. std::string s1 = "test"; const char* s2 = "test"; if (s1 == s2) → works (implicit conversion) → ✓, but if (s2 == s1) also works → OK

---AXIOMATIC CHECK---
Line 01: Introduced Person with string member → basic struct layout
Line 02: Introduced address comparison → derived from common mistake &a == &b
Line 03: Introduced operator== → correct way to compare, derived from failure in line 02
Line 06: Introduced heap allocation → derived from SSO threshold exceeded
Line 10: Introduced memcmp → low-level comparison, derived from need for byte-level control
Line 11: Introduced memcmp trap → derived from observing size difference ignored
Line 14: Introduced compare() → safe alternative derived from memcmp pitfalls
NO JUMPING AHEAD: Each comparison method introduced after showing failure of previous.
