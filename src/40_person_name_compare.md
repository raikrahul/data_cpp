```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ p1.name = "Alice" at 0x7FFF0010 (SSO buffer inside string object)                                               │
│ p2.name = "Alice" at 0x7FFF0050 (DIFFERENT address, SAME content)                                               │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ &p1.name == &p2.name → 0x7FFF0010 ≠ 0x7FFF0050 → false (ADDRESS compare) ✗                                     │
│ p1.name == p2.name → "Alice" == "Alice" → true (CONTENT compare) ✓                                              │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. p1 at 0x7FFF0000, p1.name.data()=0x7FFF0010 (SSO, "Alice"=5<15)
02. p2 at 0x7FFF0040, p2.name.data()=0x7FFF0050 (SSO, "Alice"=5<15)
03. &p1.name=0x7FFF0000, &p2.name=0x7FFF0040 → 0x7FFF0000≠0x7FFF0040 → false ✗
04. ■ &str compares object addresses, not content ■
05. p1.name==p2.name → operator==(string,string) → size check 5==5 ✓ → memcmp("Alice","Alice",5)=0 → true ✓
06. p1.name.c_str()=0x7FFF0010, p2.name.c_str()=0x7FFF0050 → 0x7FFF0010≠0x7FFF0050 → false ✗
07. ■ c_str() returns buffer pointer, different strings have different buffers ■
08. p3.name="VeryLongNameThatExceedsSSO" (26>15) → heap at 0xA000
09. p4.name="VeryLongNameThatExceedsSSO" → heap at 0xB000 → 0xA000≠0xB000 → false ✗
10. ■ SSO<15 chars inline, ≥15 chars heap, either way different addresses ■
11. memcmp(p1.c_str(),p2.c_str(),5) → memcmp("Alice","Alice",5)=0 ✓
12. memcmp(p1.c_str(),p5.c_str(),5) where p5="AliceX" → memcmp("Alice","Alice",5)=0 → but p5 has 6 chars → FALSE POSITIVE ✗
13. ■ memcmp ignores length, MUST check .size() first ■
14. p1.name.compare(p2.name) → 0 if equal, <0 if less, >0 if greater → handles size correctly ✓
15. "Alice".compare("Bob")=-1, "Bob".compare("Alice")=+1, "Alice".compare("Alice")=0
16. ■ compare() = safe, memcmp() = unsafe without size check ■
17. sort by name: [](auto& a,auto& b){return a.name<b.name;} → alphabetical ✓
18. sort by address: [](auto& a,auto& b){return &a.name<&b.name;} → memory order ✗
19. ■ sort by operator<, NEVER by address ■
---FAILURES---
F1. if(&p1.name==&p2.name) → always false for different objects → ✗
F2. if(p1.name.c_str()==p2.name.c_str()) → always false → ✗
F3. memcmp(a.c_str(),b.c_str(),a.size()) where b.size()<a.size() → reads beyond b → UB → ✗
F4. strcmp with binary data containing \0 → stops at first null → incomplete → ✗
F5. sort by &name → undefined order → ✗
