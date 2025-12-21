```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ ERROR PATTERN: action → expected → actual → root cause                                                          │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ E1: &p1.name==&p2.name → true → false → address compare not content → ✗                                        │
│ E2: memcmp(a,b,5) on "AliceX" → not equal → equal(5 bytes) → ignores length → ✗                                │
│ E3: max_element(v.begin(),v.end())->age on empty v → crash → end()==begin() → deref end() → ✗                  │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. E1: &p1.name==&p2.name → 0x7FFC1000≠0x7FFC1020 → false → expected true → comparing addresses not content → ✗
02. E2: SSO "Alice" at +16 → p1.c_str()=0x7FFC1010, p2.c_str()=0x7FFC1030 → pointer compare false → ✗
03. E3: memcmp("Alice","AliceX",5) → 0 (equal) → sizes 5≠6 → false positive → ✗
04. ■ always check .size() before memcmp ■
05. E4: p1.name==p2.name → operator== → size check → byte compare → true ✓
06. E5: max_element on empty v → returns end() → deref end() → UB → ✗
07. ■ check v.empty() before max_element ■
08. E6: missing #include<vector> → used vector<> → compile error → ✗
09. E7: k=i×nx+j vs k=i×ny+j → row-major: skip i rows of nx columns → k=i×nx+j ✓
10. ■ define variable names before formula ■
---PREVENTION---
P1. print addresses before comparing → printf("%p %p", &a, &b)
P2. draw memory diagram before code
P3. test with empty container first
P4. check sizeof() and offsetof()
P5. trace algorithm step by step with addresses
P6. calculate index formula by hand with example
