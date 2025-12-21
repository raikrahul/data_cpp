```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ LITERAL → TYPE DEDUCTION:                                                                                        │
│ 5 → int (4)   5.0 → double (8)   5.0f → float (4)   5L → long (8)   5ULL → unsigned long long (8)               │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ auto a = x → copy   auto& a = x → reference   auto&& a = x → forwarding (lvalue→T&, rvalue→T&&)                │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. auto a=5 → int, sizeof=4; auto b=5.0 → double, sizeof=8
02. auto c=5.0f → float, sizeof=4; auto d=5L → long, sizeof=8; auto e=5ULL → unsigned long long, sizeof=8
03. auto f='x' → char, sizeof=1; auto g={1,2,3} → initializer_list<int>, sizeof=16
04. ■ auto deduces from literal suffix ■
05. int x=5; auto a=x → a:int (copy), x=10 → a=5 (unchanged)
06. auto& a=x → a:int&, x=10 → a=10 (follows)
07. const auto& a=x → a:const int&, a=10 → compile error
08. ■ auto=copy, auto&=ref, const auto&=const ref ■
09. const int c=5; auto a=c → a:int (NOT const int), a=10 valid
10. ■ auto strips top-level const/reference ■
11. int x=5; auto&& a=x → x is lvalue → int& && → int& (ref collapse)
12. auto&& b=5 → 5 is rvalue → int && (rvalue ref)
13. ■ T& & → T&, T& && → T&, T&& & → T&, T&& && → T&& ■
14. auto foo(){return 5;} → return int
15. auto bar(){int x=5; return x;} → return int (copy, not ref)
16. auto& baz(){int x=5; return x;} → WARNING: return ref to local → UB
17. ■ auto return deduces value type, auto& return → dangling risk ■
18. auto [a,b]=std::pair{1,2.5} → a:int=1, b:double=2.5
19. auto [x,y,z]=std::tuple{1,2.5,'x'} → x:int, y:double, z:char
20. int arr[3]={10,20,30}; auto [a,b,c]=arr → a=10, b=20, c=30
21. ■ structured binding: pair, tuple, array, aggregate ■
22. vector<int> v={1,2,3}; for(auto x:v){x=10;} → v unchanged (copy)
23. for(auto& x:v){x=10;} → v={10,10,10} (modified)
24. for(const auto& x:v){} → no copy, no modify (read-only)
25. ■ for-range: auto=copy, auto&=modify, const auto&=read ■
---FAILURES---
F1. auto x; → no initializer → compile error → ✗
F2. auto arr[5]; → C array with auto → compile error → ✗
F3. auto f(int x, auto y); → pre-C++20 → compile error → ✗
F4. auto [a,b]=tuple{1,2.5,'x'} → 2 bindings for 3 elements → ✗
F5. auto& x=5 → lvalue ref to rvalue → ✗
