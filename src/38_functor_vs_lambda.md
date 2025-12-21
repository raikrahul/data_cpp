01. DRAW functor struct Adder { int value; int operator()(int x) { return x + value; } }. MEMORY: Adder at 0x7FFF0000 = |value=10| (4 bytes). CALCULATE sizeof(Adder) = 4 = sizeof(int) ✓
02. CALL Adder a{10}; int result = a(5). STEP 1: a.operator()(5) called. STEP 2: return 5 + a.value = 5 + 10 = 15. VERIFY result = 15 ✓
03. DRAW lambda auto add = [value=10](int x) { return x + value; }. MEMORY: lambda at 0x7FFF0010 = |value=10| (4 bytes). CALCULATE sizeof(lambda) = 4 = sizeof(int). SAME as functor ✓
04. CALL int result = add(5). STEP 1: lambda::operator()(5) called. STEP 2: return 5 + captures.value = 5 + 10 = 15. VERIFY result = 15, IDENTICAL to functor ✓
05. ■ GROUND: lambda = anonymous functor. Captures become member variables. operator() body = lambda body. sizeof(lambda) = sizeof(captures) ■ NEXT: capture modes ■
06. DRAW int x = 5; auto byVal = [x]() { return x; }. MEMORY: byVal = |x_copy=5| (4 bytes). MODIFY original: x = 10. CALL byVal(). RETURN 5 (captured copy unchanged). VERIFY capture-by-value copies at creation time ✓
07. DRAW int x = 5; auto byRef = [&x]() { return x; }. MEMORY: byRef = |x_ptr=0x7FFF0020| (8 bytes). MODIFY original: x = 10. CALL byRef(). RETURN 10 (reference follows original). VERIFY capture-by-reference stores pointer ✓
08. COMPARE sizeof: byVal = 4 (int copy), byRef = 8 (pointer). TRAP: byRef larger than byVal for small types. byVal larger for large types (e.g., vector) ✓
09. ■ GROUND: [x] = copy (sizeof(T)), [&x] = reference (sizeof(T*)=8). Choose based on modify-after-capture needs ■ NEXT: std::function overhead ■
10. DRAW std::function<int(int)> fn = add. MEMORY: fn at 0x7FFF0040 = |vtable_ptr|buffer[24]|allocator| ≈ 32 bytes. COMPARE to lambda = 4 bytes. OVERHEAD = 32-4 = 28 bytes = 700% ✓
11. CALL fn(5). STEP 1: vtable lookup → operator() entry. STEP 2: type erase unwrap → call underlying lambda. STEP 3: return 15. INDIRECT CALL = 2-3 extra instructions vs direct lambda call ✓
12. BENCHMARK: direct lambda call = 1 cycle. std::function call = 5-10 cycles. SLOWDOWN = 5-10×. TRAP: std::function hides this cost behind clean syntax ✓
13. ■ GROUND: std::function = type erasure container, ~32 bytes, indirect call overhead. Lambda = zero overhead when called directly ■ NEXT: mutable lambda ■
14. DRAW auto counter = [n=0]() mutable { return ++n; }. MEMORY: counter = |n=0| (4 bytes). CALL counter(). n = 0+1 = 1. RETURN 1. CALL counter(). n = 1+1 = 2. RETURN 2. STATE preserved between calls ✓
15. WITHOUT mutable: auto counter = [n=0]() { return ++n; }. COMPILE ERROR: cannot modify captured variable in non-mutable lambda. operator() const by default ✓
16. COMPARE to functor: struct Counter { int n=0; int operator()() { return ++n; } }. operator() is non-const by default in functor. Lambda = opposite default ✓
17. ■ GROUND: lambda operator() const by default. mutable removes const. Functor operator() non-const by default ■ NEXT: generic lambda ■
18. DRAW auto square = [](auto x) { return x * x; }. TEMPLATE EXPANSION: call square(3) → generates operator()<int>. call square(2.5) → generates operator()<double>. TWO operator() instantiations in same lambda object ✓
19. DRAW MEMORY: square = |<empty>| (1 byte). sizeof(square) = 1 (empty class optimization). No captures → 1 byte placeholder ✓
20. CALL square(3). STEP 1: operator()<int>(3). STEP 2: 3 * 3 = 9. CALL square(2.5). STEP 1: operator()<double>(2.5). STEP 2: 2.5 * 2.5 = 6.25. VERIFY type deduction per call ✓

---FAILURES---
F1. auto fn = [&x]() { return x; }; x goes out of scope; fn(); → dangling reference → undefined behavior → ✗
F2. std::function<void()> fn; fn(); → calling empty function → std::bad_function_call exception → ✗
F3. [=]() { x = 10; } → modify captured-by-value → compile error (const operator()) → ✗
F4. [this]() { member = 5; } → this pointer captured, object destroyed → dangling this → ✗
F5. [](auto x) { return x * x; }("hello") → const char* × const char* → no operator* → compile error → ✗

---AXIOMATIC CHECK---
Line 01: Introduced functor → primitive callable object with operator()
Line 03: Introduced lambda → derived from observing functor boilerplate
Line 06: Introduced capture-by-value → derived from need to store state in lambda
Line 07: Introduced capture-by-reference → derived from need to modify external state
Line 10: Introduced std::function → derived from need to store heterogeneous callables
Line 14: Introduced mutable → derived from observing const operator() limitation
Line 18: Introduced generic lambda → derived from need for template-like behavior
NO JUMPING AHEAD: Each concept derived from limitation of previous.
