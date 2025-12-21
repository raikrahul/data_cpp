01. WRITE auto a = 5. DEDUCE: 5 = int literal → a : int. VERIFY sizeof(a) = 4 ✓. WRITE auto b = 5.0. DEDUCE: 5.0 = double literal → b : double. VERIFY sizeof(b) = 8 ✓
02. WRITE auto c = 5.0f. DEDUCE: 5.0f = float literal → c : float. VERIFY sizeof(c) = 4 ✓. WRITE auto d = 5L. DEDUCE: 5L = long literal → d : long. VERIFY sizeof(d) = 8 ✓
03. WRITE auto e = 5ULL. DEDUCE: 5ULL = unsigned long long → e : unsigned long long. VERIFY sizeof(e) = 8 ✓. WRITE auto f = 'x'. DEDUCE: 'x' = char literal → f : char. sizeof(f) = 1 ✓
04. TRAP: auto g = {1, 2, 3}. DEDUCE: {1,2,3} = std::initializer_list<int> → g : initializer_list<int>. NOT std::vector, NOT std::array. sizeof(g) = 16 (2 pointers) ✓
05. ■ GROUND: auto deduces from literal suffix: (none)=int, .0=double, f=float, L=long, ULL=unsigned long long, {}=initializer_list ■ NEXT: reference deduction ■
06. WRITE int x = 5; auto a = x. DEDUCE: a = copy of x → a : int (not int&). MODIFY x = 10. CHECK a. a = 5 (unchanged). COPY semantics ✓
07. WRITE int x = 5; auto& a = x. DEDUCE: a = reference to x → a : int&. MODIFY x = 10. CHECK a. a = 10 (follows x). REFERENCE semantics ✓
08. WRITE int x = 5; const auto& a = x. DEDUCE: a : const int&. ATTEMPT a = 10. COMPILE ERROR: cannot modify const reference ✓
09. TRAP: auto strips top-level const and reference. const int c = 5; auto a = c. a : int (not const int). a = 10 valid ✓
10. ■ GROUND: auto = T (copies), auto& = T&, auto&& = forwarding reference. const/volatile stripped unless explicit ■ NEXT: auto&& ■
11. WRITE int x = 5; auto&& a = x. DEDUCE: x is lvalue → auto = int& → int& && → int& (reference collapsing). a : int&. VERIFY a modifies x ✓
12. WRITE auto&& b = 5. DEDUCE: 5 is rvalue → auto = int → int && → int&&. b : int&&. b bound to temporary ✓
13. REFERENCE COLLAPSING TABLE: T& & → T&, T& && → T&, T&& & → T&, T&& && → T&&. ONLY rval+rval = rvalue reference. All others = lvalue reference ✓
14. ■ GROUND: auto&& = forwarding/universal reference. Binds to lvalue as T&, binds to rvalue as T&& ■ NEXT: function return type ■
15. WRITE auto foo() { return 5; }. DEDUCE return type: 5 = int → foo returns int. VERIFY with decltype(foo()) = int ✓
16. WRITE auto bar() { int x = 5; return x; }. DEDUCE: x = int → return int. NOT int& (return by value, not reference to local) ✓
17. TRAP: auto& baz() { int x = 5; return x; }. DEDUCE: return int&. WARNING: returning reference to local variable. UNDEFINED BEHAVIOR after return ✓
18. WRITE decltype(auto) qux() { int x = 5; return x; }. DEDUCE: decltype(x) = int → return int. return (x) would be int& (expression in parens) ✓
19. ■ GROUND: auto return = deduced value type. decltype(auto) = exact type including references. TRAP: return (x) vs return x ■ NEXT: structured binding ■
20. WRITE std::pair<int, double> p = {1, 2.5}; auto [a, b] = p. DEDUCE: a from p.first : int, b from p.second : double. VERIFY a=1, b=2.5 ✓
21. WRITE std::tuple<int, double, char> t = {1, 2.5, 'x'}; auto [x, y, z] = t. DEDUCE: x:int, y:double, z:char. COUNT bindings = 3 = tuple_size ✓
22. WRITE int arr[3] = {10, 20, 30}; auto [a, b, c] = arr. DEDUCE: a=arr[0]:int, b=arr[1]:int, c=arr[2]:int. ARRAY decomposition ✓
23. WRITE struct S { int x; double y; }; S s = {1, 2.5}; auto [a, b] = s. DEDUCE: a=s.x:int, b=s.y:double. STRUCT decomposition ✓
24. ■ GROUND: structured binding works with pair, tuple, array, aggregate struct. Binding count must match element count ■ NEXT: range-based for ■
25. WRITE std::vector<int> v = {1, 2, 3}; for (auto x : v) { x = 10; }. AFTER loop: v = {1, 2, 3} (unchanged). x is COPY of each element ✓
26. WRITE for (auto& x : v) { x = 10; }. AFTER loop: v = {10, 10, 10}. x is REFERENCE to each element, modifications affect v ✓
27. WRITE for (const auto& x : v) { }. x is const reference. NO copy made, NO modification allowed. BEST for read-only iteration ✓
28. WRITE for (auto&& x : v). x binds as lvalue reference (v is lvalue container). SAME as auto& for lvalue containers. DIFFERENT for rvalue containers (temporaries) ✓

---FAILURES---
F1. auto x; → auto requires initializer → compile error → ✗
F2. auto arr[5]; → auto not allowed for C arrays → compile error → ✗
F3. auto f(int x, auto y); → pre-C++20: auto parameter only in lambda, not regular function → compile error → ✗
F4. auto [a, b] = std::tuple<int, double, char>{1, 2.5, 'x'}; → 2 bindings for 3 elements → compile error → ✗
F5. auto& x = 5; → cannot bind lvalue reference to rvalue → compile error → ✗
F6. const int c = 5; auto d = c; d = 10; → valid, auto stripped const → d modifiable → ⚠ (intentional or bug?)

---AXIOMATIC CHECK---
Line 01: Introduced auto with literals → fundamental deduction rules from literal type
Line 06: Introduced auto vs auto& → derived from need to choose copy vs reference
Line 11: Introduced auto&& → derived from universal reference/forwarding pattern
Line 15: Introduced auto return → derived from avoiding redundant return type declaration
Line 20: Introduced structured binding → derived from need to decompose aggregates
Line 25: Introduced range-for auto → derived from iteration patterns
NO JUMPING AHEAD: Each deduction scenario builds on previous.
