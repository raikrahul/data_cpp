```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ FULL SYNTAX:        template<typename T> T f(T x) { T result=x*x; return result; }                              │
│ ABBREVIATED SYNTAX: auto f(auto x) { decltype(x) result=x*x; return result; }        ← C++20 ONLY              │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ f(2.0) → T=double → double f(double x){...} at 0x4000                                                           │
│ f(3)   → T=int    → int f(int x){...} at 0x4030                                                                 │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. template<typename T> T pow(T x, int n){T result=1; for(int i=0;i<n;++i)result*=x; return result;}
02. pow<int>(2,3) → T=int substituted → int pow(int x,int n){int result=1;...}
03. pow<double>(2.5,2) → T=double substituted → double pow(double x,int n){double result=1;...}
04. ■ template = compile-time type substitution ■
05. auto pow(auto x, int n){decltype(x) result=1; for(int i=0;i<n;++i)result*=x; return result;}
06. pow(2,3) → auto=int → int pow(int x,int n){int result=1;...}
07. pow(2.5,2) → auto=double → double pow(double x,int n){double result=1;...}
08. ■ abbreviated auto = implicit template, SAME binary ■
09. auto f(auto a, auto b) → template<T1,T2> auto f(T1 a, T2 b)
10. f(1, 2.0) → T1=int, T2=double
11. ■ each auto = separate type parameter ■
12. process(const auto& x){decltype(x) result=x;} → x:const int& → decltype(x)=const int& → result is const ref
13. process(const auto& x){std::remove_cvref_t<decltype(x)> result=x;} → result is int (stripped)
14. ■ decltype preserves const&, remove_cvref_t strips both ■
15. auto lambda=[](auto x){return x*x;} → sizeof=1 (empty capture)
16. lambda(3) → operator()<int> generated, lambda(2.5) → operator()<double> generated
17. lambda("hi") → const char* × const char* → no operator* → compile error ✓ (caught at compile-time)
18. ■ generic lambda = abbreviated template at lambda level ■
19. [](auto x){return x*x;} → Python def f(x):return x*x
20. C++: f("hi") → compile error (0 cost); Python: f("hi") → runtime error (user cost)
21. ■ C++ catches type errors at compile-time, Python at runtime ■
---FAILURES---
F1. decltype(x) with const auto& → result is const& → cannot modify → ✗
F2. forget each auto = separate param → expect same type for a,b → ✗
F3. use T inside abbreviated lambda → T undefined → ✗
F4. call template with type lacking operator* → compile error → ✓
F5. []<typename T>(T x) in pre-C++20 → syntax error → ✗
