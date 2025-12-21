```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ FUNCTOR: struct Adder { int v; int operator()(int x){return x+v;} }; sizeof=4                                   │
│ LAMBDA:  auto add = [v=10](int x){return x+v;};                      sizeof=4 (same)                            │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ std::function<int(int)> fn = add;  sizeof=32  OVERHEAD=28 bytes, indirect call=5-10× slower                    │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. struct Adder { int value; int operator()(int x){return x+value;} }; → sizeof=4
02. Adder a{10}; a(5) → a.operator()(5) → 5+10=15 ✓
03. auto add = [value=10](int x){return x+value;} → sizeof=4, identical to functor
04. add(5) → lambda::operator()(5) → 5+10=15 ✓
05. ■ lambda = anonymous functor, captures = members, sizeof = sizeof(captures) ■
06. int x=5; auto byVal=[x](){return x;} → sizeof=4 (copy), modify x=10, byVal()=5 (unchanged)
07. auto byRef=[&x](){return x;} → sizeof=8 (pointer), modify x=10, byRef()=10 (follows)
08. ■ [x]=copy sizeof(T), [&x]=reference sizeof(T*)=8 ■
09. std::function<int(int)> fn=add → sizeof=32, overhead=28 bytes
10. fn(5) → vtable lookup → type erase → call lambda → 5-10× slower than direct
11. ■ std::function: type erasure, 32 bytes, indirect call overhead ■
12. auto counter=[n=0]()mutable{return ++n;} → counter()=1, counter()=2, state preserved
13. without mutable → operator() const → cannot modify n → compile error
14. ■ lambda operator() const by default, mutable removes const ■
15. auto square=[](auto x){return x*x;} → sizeof=1 (empty capture)
16. square(3) → operator()<int> → 9; square(2.5) → operator()<double> → 6.25
17. ■ generic lambda: auto param = template, generates N operator() instantiations ■
---FAILURES---
F1. [&x](){return x;} after x out of scope → dangling reference → ✗
F2. std::function<void()> fn; fn(); → empty function → bad_function_call → ✗
F3. [=](){x=10;} → modify by-value capture → const error → ✗
F4. [this](){member=5;} after object destroyed → dangling this → ✗
F5. [](auto x){return x*x;}("hi") → const char* × const char* → no operator* → ✗
