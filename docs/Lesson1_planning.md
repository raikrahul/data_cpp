# LESSON 1: C++ Memory, Types, and Dispatch - Master Planning Document

---

## DOCUMENT PURPOSE

This is NOT a tutorial. This is a TASK BREAKDOWN for teaching C++ from inside out.
NO SOLUTIONS. Only QUESTIONS, SUB-TASKS, and COUNTER-QUESTIONS.
Each section GRILLS the topic until atomic tasks emerge.

---

## LOGICAL SEQUENCE: What Must Be Learned First?

```
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ DEPENDENCY CHAIN (cannot learn B without A):                                                                     │
│                                                                                                                  │
│ LEVEL 0: Memory Model                                                                                            │
│ ├── What is a byte? What is an address?                                                                         │
│ ├── What is stack vs heap?                                                                                      │
│ └── What is alignment and padding?                                                                              │
│                                                                                                                  │
│ LEVEL 1: Type System (requires Level 0)                                                                         │
│ ├── What is sizeof()?                                                                                           │
│ ├── What is a pointer?                                                                                          │
│ └── What is a reference?                                                                                        │
│                                                                                                                  │
│ LEVEL 2: Object Model (requires Level 1)                                                                        │
│ ├── What is struct layout?                                                                                      │
│ ├── What is class vs struct?                                                                                    │
│ └── What is initialization order?                                                                               │
│                                                                                                                  │
│ LEVEL 3: Polymorphism (requires Level 2)                                                                        │
│ ├── What is a vtable?                                                                                           │
│ ├── What is virtual dispatch?                                                                                   │
│ └── What is object slicing?                                                                                     │
│                                                                                                                  │
│ LEVEL 4: Ownership (requires Level 3)                                                                           │
│ ├── What is RAII?                                                                                               │
│ ├── What is unique_ptr?                                                                                         │
│ ├── What is shared_ptr?                                                                                         │
│ └── What is weak_ptr?                                                                                           │
│                                                                                                                  │
│ LEVEL 5: Templates (requires Level 4)                                                                           │
│ ├── What is compile-time substitution?                                                                          │
│ ├── What is auto deduction?                                                                                     │
│ └── What is abbreviated syntax?                                                                                 │
│                                                                                                                  │
│ LEVEL 6: Callables (requires Level 5)                                                                           │
│ ├── What is a functor?                                                                                          │
│ ├── What is a lambda?                                                                                           │
│ └── What is std::function?                                                                                      │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```

---

## LEVEL 0: MEMORY MODEL

### TASK 0.1: What is a byte?

**QUESTIONS TO GRILL:**
- Q1: How many bits in a byte?
- Q2: What is the range of values a byte can hold?
- Q3: What is the difference between signed and unsigned byte?
- Q4: Can a byte hold a character? Which characters?
- Q5: Can a byte hold a number larger than 255?

**COUNTER-QUESTIONS:**
- CQ1: If 8 bits, why not 10 bits? Who decided?
- CQ2: If range 0-255, what happens when you add 1 to 255?
- CQ3: If signed -128 to 127, why not -127 to 128?

**SUB-TASKS:**
- ST1: Draw 8 boxes representing 8 bits. Fill with 0s and 1s for value 42.
- ST2: Calculate 42 in binary by hand. Verify with 32+8+2.
- ST3: Calculate the binary representation of -42 using two's complement.

**TRAP PREDICTIONS:**
- User will confuse bit position (0-indexed from right) with bit number.
- User will forget two's complement for negative numbers.

---

### TASK 0.2: What is an address?

**QUESTIONS TO GRILL:**
- Q1: What is the size of an address on 32-bit vs 64-bit?
- Q2: What is the range of addressable memory?
- Q3: Why do addresses look like 0x7FFF0000?
- Q4: What is hexadecimal? Why use it?
- Q5: What is the difference between address and value at address?

**COUNTER-QUESTIONS:**
- CQ1: If address is 64-bit, why can't we address 2^64 bytes? (virtual vs physical)
- CQ2: If 0x7FFF0000 is an address, what is at that address?
- CQ3: Can two variables have the same address?

**SUB-TASKS:**
- ST1: Convert 0x7FFF0000 to decimal by hand.
- ST2: Draw a memory diagram with addresses 0x1000, 0x1004, 0x1008.
- ST3: Place value 42 at address 0x1000. Draw the bytes in little-endian.

**TRAP PREDICTIONS:**
- User will confuse address (where) with value (what).
- User will forget little-endian byte ordering.

---

### TASK 0.3: Stack vs Heap

**QUESTIONS TO GRILL:**
- Q1: Where does stack start? (high address)
- Q2: Where does heap start? (low address)
- Q3: Which direction does stack grow? (downward)
- Q4: Which direction does heap grow? (upward)
- Q5: What is the typical distance between stack and heap?

**COUNTER-QUESTIONS:**
- CQ1: If stack grows down, what happens at stack overflow?
- CQ2: If heap grows up, what happens when heap meets stack?
- CQ3: Who decides stack size? Can it be changed?
- CQ4: Can you allocate heap memory on stack? (alloca?)
- CQ5: Can you allocate stack memory on heap? (placement new?)

**SUB-TASKS:**
- ST1: Write `int x = 5;` and print &x. Is it 0x7FFF...? (stack)
- ST2: Write `int* p = new int(5);` and print p. Is it 0x5B19...? (heap)
- ST3: Calculate difference: stack_addr - heap_addr. Is it ~40TB?

**TRAP PREDICTIONS:**
- User will think stack is "faster" without understanding cache locality.
- User will forget that `new` returns heap, automatic variables are stack.

---

### TASK 0.4: Alignment and Padding

**QUESTIONS TO GRILL:**
- Q1: What does "aligned to 4-byte boundary" mean?
- Q2: What is the alignment of int? double? char?
- Q3: Why does compiler add padding?
- Q4: What is the alignment of a struct?
- Q5: How does alignment affect array element spacing?

**COUNTER-QUESTIONS:**
- CQ1: If alignment is for performance, what is the performance cost of unaligned access?
- CQ2: If padding wastes memory, why not pack everything?
- CQ3: Can #pragma pack break things? How?
- CQ4: What is natural alignment vs forced alignment?

**SUB-TASKS:**
- ST1: Draw struct { char a; int b; } with padding. Calculate sizeof.
- ST2: Reorder to { int b; char a; }. Calculate sizeof. Compare.
- ST3: Calculate alignof(struct). Is it max(alignof(members))?

**TRAP PREDICTIONS:**
- User will forget end-of-struct padding for array alignment.
- User will assume sizeof = sum of member sizes.

---

## LEVEL 1: TYPE SYSTEM

### TASK 1.1: sizeof() Operator

**QUESTIONS TO GRILL:**
- Q1: Is sizeof evaluated at compile-time or runtime?
- Q2: What is sizeof(char)? Always 1?
- Q3: What is sizeof(int)? Is it always 4?
- Q4: What is sizeof(pointer)? Is it 4 or 8?
- Q5: What is sizeof(array) vs sizeof(pointer to array)?

**COUNTER-QUESTIONS:**
- CQ1: If sizeof(int) can vary, how do you write portable code?
- CQ2: If sizeof(char) is always 1, what is sizeof(wchar_t)?
- CQ3: What is sizeof(void)? Is it valid?
- CQ4: What is sizeof(empty struct)? Is it 0?

**SUB-TASKS:**
- ST1: Print sizeof for int, double, char, int*, double*, void*.
- ST2: Compare sizeof on 32-bit vs 64-bit (or check documentation).
- ST3: Create struct with known layout. Predict sizeof. Verify.

**TRAP PREDICTIONS:**
- User will assume int is 32-bit everywhere.
- User will confuse sizeof(array) with sizeof(pointer).

---

### TASK 1.2: Pointers

**QUESTIONS TO GRILL:**
- Q1: What is stored in a pointer variable?
- Q2: What is the difference between `int*` and `int**`?
- Q3: What does `*p` mean? (dereference)
- Q4: What does `&x` mean? (address-of)
- Q5: What is pointer arithmetic? p+1 means what?

**COUNTER-QUESTIONS:**
- CQ1: If p is int*, what is p+1? Is it +1 byte or +4 bytes?
- CQ2: If p=0x1000 and sizeof(int)=4, what is p+2?
- CQ3: Can you have pointer to pointer to pointer? When useful?
- CQ4: What is nullptr? How different from 0 or NULL?
- CQ5: What is void*? Can you dereference it?

**SUB-TASKS:**
- ST1: Draw: int x=5; int* p=&x; int** pp=&p; Calculate addresses.
- ST2: Calculate: p=0x1000, p+3=? for int*. For char*. For double*.
- ST3: Trace: *pp → *p → x. Write the dereference chain.

**TRAP PREDICTIONS:**
- User will forget pointer arithmetic scales by sizeof(*p).
- User will confuse &(*p) with *(&p).

---

### TASK 1.3: References

**QUESTIONS TO GRILL:**
- Q1: What is a reference? Is it a pointer in disguise?
- Q2: Can you have uninitialized reference? Why not?
- Q3: Can you rebind a reference to another variable?
- Q4: What is sizeof(reference)? Is it 0?
- Q5: What happens when you assign to a reference?

**COUNTER-QUESTIONS:**
- CQ1: If reference cannot be null, how does compiler guarantee this?
- CQ2: If reference cannot rebind, how is it different from const pointer?
- CQ3: If sizeof(T&) == sizeof(T), does reference occupy memory?
- CQ4: Can function return reference? What are the dangers?

**SUB-TASKS:**
- ST1: Write: int x=5; int& r=x; r=10; Print x. Explain.
- ST2: Write: int x=5, y=7; int& r=x; r=y; Print x. Why is x now 7?
- ST3: Draw memory: where is r? Does it have its own address?

**TRAP PREDICTIONS:**
- User will think r=y rebinds r to y. It assigns y's value to x.
- User will try to return reference to local variable.

---

## LEVEL 2: OBJECT MODEL

### TASK 2.1: Struct Layout

**QUESTIONS TO GRILL:**
- Q1: What determines member order in struct?
- Q2: Can compiler reorder members to save memory?
- Q3: What is offsetof()? How to use it?
- Q4: What is the difference between struct padding and member padding?
- Q5: How does inheritance affect layout?

**COUNTER-QUESTIONS:**
- CQ1: If C++ cannot reorder, why can't it? (ABI compatibility)
- CQ2: If offsetof() gives offset, can you access member via pointer arithmetic?
- CQ3: What is standard layout struct? What is trivial struct?

**SUB-TASKS:**
- ST1: Draw { char a; int b; char c; } with offsets. Count bytes.
- ST2: Use offsetof(S, b) to verify offset. Is it 4?
- ST3: Reorder members. Predict new sizeof. Verify.

**TRAP PREDICTIONS:**
- User will expect compiler to optimize layout automatically.
- User will forget trailing padding.

---

### TASK 2.2: Class vs Struct

**QUESTIONS TO GRILL:**
- Q1: What is the ONLY difference between class and struct?
- Q2: Does default access affect memory layout?
- Q3: Can struct have member functions? Constructors?
- Q4: Can struct inherit? Can it be polymorphic?
- Q5: When to use struct vs class by convention?

**COUNTER-QUESTIONS:**
- CQ1: If only default access differs, why have both keywords?
- CQ2: If struct can have virtual functions, does it have vptr?
- CQ3: Can class have all public members? Is it idiomatic?

**SUB-TASKS:**
- ST1: Write struct S { int x; }; class C { int x; }; Compare sizeof.
- ST2: Write struct S { virtual void f(); }; Does it have vptr?
- ST3: Access S::x from outside. Access C::x from outside. Which fails?

**TRAP PREDICTIONS:**
- User will think struct cannot have methods or inheritance.
- User will think struct is "C-style" and class is "C++-style".

---

### TASK 2.3: Initialization Order

**QUESTIONS TO GRILL:**
- Q1: In what order are members initialized?
- Q2: Does constructor initializer list order matter?
- Q3: What is default initialization vs value initialization?
- Q4: What is aggregate initialization?
- Q5: When is default constructor implicitly deleted?

**COUNTER-QUESTIONS:**
- CQ1: If member init order is declaration order, why allow different initializer list order?
- CQ2: If T x; is default init, what is T x{}; ?
- CQ3: What happens if you initialize base class after members in initializer list?

**SUB-TASKS:**
- ST1: Write: struct T { int a; int b; T():b(1),a(b){} }; What is a?
- ST2: Write: struct P { int a; int b; }; P p; What is p.a?
- ST3: Write: struct Q { int a=5; int b; }; Q q{}; What is q.b?

**TRAP PREDICTIONS:**
- User will expect initializer list order to be initialization order.
- User will forget that P p; leaves members uninitialized.

---

## LEVEL 3: POLYMORPHISM

### TASK 3.1: Virtual Function Mechanism

**QUESTIONS TO GRILL:**
- Q1: What is a vptr? Where is it in the object?
- Q2: What is a vtable? Who creates it?
- Q3: How does virtual call differ from non-virtual call?
- Q4: What is the cost of virtual dispatch?
- Q5: Can virtual function be inlined?

**COUNTER-QUESTIONS:**
- CQ1: If vptr is at offset 0, how does multiple inheritance work?
- CQ2: If vtable is per-class, where is it stored? (.rodata?)
- CQ3: If virtual is "slow", how slow exactly? Cycles?
- CQ4: Can compiler devirtualize? When?

**SUB-TASKS:**
- ST1: Draw: Base at 0x1000 with vptr. Derived at 0x2000 with vptr. Different vtables.
- ST2: Trace: b->speak() when b points to Derived. What addresses are loaded?
- ST3: Count: How many memory loads for virtual call? For non-virtual call?

**TRAP PREDICTIONS:**
- User will assume virtual is "free" abstraction.
- User will forget that static type determines non-virtual call.

---

### TASK 3.2: Virtual Destructor

**QUESTIONS TO GRILL:**
- Q1: What happens if destructor is not virtual?
- Q2: When MUST destructor be virtual?
- Q3: What happens if only base destructor runs?
- Q4: What is the destruction order in inheritance?
- Q5: Can constructor be virtual? Why not?

**COUNTER-QUESTIONS:**
- CQ1: If destructor must be virtual for polymorphism, should all destructors be virtual?
- CQ2: If virtual destructor adds vptr, what if I don't want vptr overhead?
- CQ3: What is pure virtual destructor? How to define it?

**SUB-TASKS:**
- ST1: Write: Base* b = new Derived(); delete b; with non-virtual ~Base. What leaks?
- ST2: Fix with virtual ~Base(). Trace destruction order.
- ST3: What is sizeof(Base) with vs without virtual destructor?

**TRAP PREDICTIONS:**
- User will forget virtual destructor in base class.
- User will think pure virtual = no definition needed. (false for destructor)

---

### TASK 3.3: Object Slicing

**QUESTIONS TO GRILL:**
- Q1: What happens when Derived is assigned to Base by value?
- Q2: Is the vptr sliced?
- Q3: Can sliced object call Derived's virtual functions?
- Q4: How to prevent slicing?
- Q5: Does slicing happen with references?

**COUNTER-QUESTIONS:**
- CQ1: If slicing copies only Base portion, is it valid Base object?
- CQ2: If vector<Base> stores Derived, is it sliced?
- CQ3: How does vector<unique_ptr<Base>> prevent slicing?

**SUB-TASKS:**
- ST1: Write: Derived d; Base b = d; What is sizeof(b)?
- ST2: Call b.virtualMethod(). Which version runs?
- ST3: Write: Derived d; Base& r = d; r.virtualMethod(); Which runs?

**TRAP PREDICTIONS:**
- User will store polymorphic objects by value in containers.
- User will confuse slicing with pointer/reference semantics.

---

## LEVEL 4: OWNERSHIP

### TASK 4.1: unique_ptr

**QUESTIONS TO GRILL:**
- Q1: What does unique_ptr guarantee?
- Q2: Can unique_ptr be copied? Why not?
- Q3: What is std::move on unique_ptr?
- Q4: What is sizeof(unique_ptr)? Overhead?
- Q5: What is get() vs release()?

**COUNTER-QUESTIONS:**
- CQ1: If unique_ptr cannot be copied, how to pass to function?
- CQ2: If sizeof(unique_ptr) == sizeof(T*), where is the deleter?
- CQ3: Can unique_ptr have custom deleter? What then is sizeof?
- CQ4: What is unique_ptr<T[]>?

**SUB-TASKS:**
- ST1: Write: unique_ptr<int> p(new int(5)); unique_ptr<int> q = p; Does it compile?
- ST2: Write: unique_ptr<int> q = std::move(p); What is p after?
- ST3: Draw memory: where is unique_ptr? Where is the int?

**TRAP PREDICTIONS:**
- User will try to copy unique_ptr.
- User will access moved-from unique_ptr.

---

### TASK 4.2: shared_ptr

**QUESTIONS TO GRILL:**
- Q1: What is the control block?
- Q2: What is strong_count? weak_count?
- Q3: When is the object deleted?
- Q4: When is the control block deleted?
- Q5: What is sizeof(shared_ptr)? Why 16 bytes?

**COUNTER-QUESTIONS:**
- CQ1: If two shared_ptr created from same raw pointer, what happens?
- CQ2: If circular reference, what is strong_count? Does it reach 0?
- CQ3: What is make_shared? Why better than shared_ptr(new T)?
- CQ4: Can shared_ptr be thread-safe? Is strong_count atomic?

**SUB-TASKS:**
- ST1: Draw: shared_ptr sp1, sp2 sharing object. Draw control block.
- ST2: Trace: sp2 = sp1; What happens to strong_count?
- ST3: Trace: sp1.reset(); sp2.reset(); When is object deleted? Control block?

**TRAP PREDICTIONS:**
- User will create multiple control blocks for same object.
- User will create circular reference.

---

### TASK 4.3: weak_ptr

**QUESTIONS TO GRILL:**
- Q1: Does weak_ptr affect object lifetime?
- Q2: What is lock()? What does it return?
- Q3: What is expired()?
- Q4: Why does control block survive when weak_ptr exists?
- Q5: What is the use case for weak_ptr?

**COUNTER-QUESTIONS:**
- CQ1: If weak_ptr doesn't prevent deletion, how does lock() know if object exists?
- CQ2: If control block survives for weak_count, is this memory overhead?
- CQ3: Can you create weak_ptr from unique_ptr?

**SUB-TASKS:**
- ST1: Draw: shared_ptr sp, weak_ptr wp. Show strong_count, weak_count.
- ST2: Trace: sp.reset(); wp.lock(); What is returned?
- ST3: Trace: Break circular reference with weak_ptr.

**TRAP PREDICTIONS:**
- User will assume weak_ptr prevents deletion.
- User will dereference wp.lock() without checking.

---

## LEVEL 5: TEMPLATES

### TASK 5.1: Template Instantiation

**QUESTIONS TO GRILL:**
- Q1: When is template code generated? Compile-time?
- Q2: What is instantiation? What triggers it?
- Q3: Does template create runtime overhead?
- Q4: What is code bloat?
- Q5: Can template instantiation fail? When?

**COUNTER-QUESTIONS:**
- CQ1: If compile-time, why are some errors deferred until instantiation?
- CQ2: If no runtime overhead, why is binary larger?
- CQ3: Can you instantiate template with type that lacks required operations?

**SUB-TASKS:**
- ST1: Write: template<typename T> T add(T a, T b) { return a+b; } Call with int, double.
- ST2: How many functions are generated? What are their addresses?
- ST3: Call add("hello", "world"). What error?

**TRAP PREDICTIONS:**
- User will expect runtime polymorphism from templates.
- User will call template with incompatible type.

---

### TASK 5.2: auto Deduction

**QUESTIONS TO GRILL:**
- Q1: When is auto deduced?
- Q2: What is the difference between auto, auto&, auto&&?
- Q3: Does auto strip const? reference?
- Q4: What is decltype? decltype(auto)?
- Q5: What is structured binding?

**COUNTER-QUESTIONS:**
- CQ1: If auto strips reference, how to preserve reference?
- CQ2: If auto&& is forwarding reference, what is the deduced type for lvalue?
- CQ3: What is reference collapsing?

**SUB-TASKS:**
- ST1: Write: int x=5; auto a=x; auto& b=x; x=10; What is a? b?
- ST2: Write: auto&& r = 5; What is decltype(r)?
- ST3: Write: auto [a,b] = std::pair{1,2.5}; What are types of a, b?

**TRAP PREDICTIONS:**
- User will expect auto& to copy.
- User will misunderstand auto&& as rvalue reference.

---

### TASK 5.3: Abbreviated Syntax (C++20)

**QUESTIONS TO GRILL:**
- Q1: What is `auto f(auto x)`?
- Q2: Is abbreviated syntax equivalent to template?
- Q3: Can you access the type T inside abbreviated function?
- Q4: What is decltype(x) in abbreviated function?
- Q5: Can lambda have auto parameters?

**COUNTER-QUESTIONS:**
- CQ1: If abbreviated = template, why have abbreviated syntax?
- CQ2: If no T visible, how to create variable of same type as x?
- CQ3: What is `[]<typename T>(T x)` in C++20?

**SUB-TASKS:**
- ST1: Write: auto square(auto x) { return x*x; } Call with int, double.
- ST2: Write: auto process(const auto& x) { decltype(x) result = x; } What is type of result?
- ST3: Fix with std::remove_cvref_t. What is type now?

**TRAP PREDICTIONS:**
- User will use decltype(x) expecting non-const non-ref type.
- User will try to use T inside abbreviated function.

---

## LEVEL 6: CALLABLES

### TASK 6.1: Functors

**QUESTIONS TO GRILL:**
- Q1: What is a functor?
- Q2: What is operator()?
- Q3: What is sizeof(functor)?
- Q4: Can functor have state?
- Q5: Is functor call inlinable?

**COUNTER-QUESTIONS:**
- CQ1: If functor is struct with operator(), how is it different from function?
- CQ2: If functor has state, how is state initialized?
- CQ3: Can functor be stateless? What is sizeof then?

**SUB-TASKS:**
- ST1: Write: struct Adder { int n; int operator()(int x){return x+n;} };
- ST2: Create Adder{10}. Call with 5. Result?
- ST3: What is sizeof(Adder)?

**TRAP PREDICTIONS:**
- User will forget operator() syntax.
- User will confuse functor instance with functor type.

---

### TASK 6.2: Lambdas

**QUESTIONS TO GRILL:**
- Q1: What is capture?
- Q2: What is [x] vs [&x] vs [=] vs [&]?
- Q3: What is sizeof(lambda)?
- Q4: What is mutable lambda?
- Q5: Is lambda operator() const by default?

**COUNTER-QUESTIONS:**
- CQ1: If lambda is anonymous functor, what is its type name?
- CQ2: If [x] copies, when is the copy made?
- CQ3: If [&x] references, what if x goes out of scope?
- CQ4: What is generic lambda with auto parameter?

**SUB-TASKS:**
- ST1: Write: int x=5; auto f=[x](){return x;}; x=10; f()=?
- ST2: Write: int x=5; auto g=[&x](){return x;}; x=10; g()=?
- ST3: Write: auto h=[n=0]()mutable{return ++n;}; h(); h()=?

**TRAP PREDICTIONS:**
- User will capture by reference and have dangling reference.
- User will try to modify by-value capture without mutable.

---

### TASK 6.3: std::function

**QUESTIONS TO GRILL:**
- Q1: What is type erasure?
- Q2: What is sizeof(std::function)?
- Q3: What is the overhead of std::function call?
- Q4: When is heap allocation needed?
- Q5: Can std::function be empty?

**COUNTER-QUESTIONS:**
- CQ1: If std::function erases type, how does it call the right function?
- CQ2: If sizeof ~ 32 bytes, where does the callable go?
- CQ3: What is small buffer optimization?
- CQ4: What exception is thrown when calling empty std::function?

**SUB-TASKS:**
- ST1: Write: std::function<int(int)> f = [](int x){return x*2;};
- ST2: What is sizeof(f)?
- ST3: Benchmark: direct lambda call vs std::function call. Ratio?

**TRAP PREDICTIONS:**
- User will use std::function when lambda or template suffices.
- User will call empty std::function.

---

## CROSS-CUTTING CONCERNS

### CC1: Swap Operation (Uses: Level 0, 1, 4)

**QUESTIONS:**
- Why does swap need temp variable?
- Can swap be done without temp? (XOR)
- Why is XOR swap slower?
- What is std::swap?
- What is move-based swap?

**SUB-TASKS:**
- Trace pointer-based swap step by step.
- Trace reference-based swap. Compare stack usage.
- Trace std::swap. Count instructions.

---

### CC2: String Comparison (Uses: Level 0, 1)

**QUESTIONS:**
- What is SSO?
- When is string on stack vs heap?
- What is c_str()?
- Why can't you compare c_str() pointers?
- What is compare() vs operator==?

**SUB-TASKS:**
- Draw string memory layout with SSO.
- Compare &str with str.c_str() with str==str.
- Trap: memcmp without size check.

---

### CC3: Container Polymorphism (Uses: Level 3, 4)

**QUESTIONS:**
- Why can't vector<Base> hold Derived?
- What is vector<unique_ptr<Base>>?
- What is vector<shared_ptr<Base>>?
- When is pointer appropriate?

**SUB-TASKS:**
- Write code that slices. Observe behavior.
- Fix with unique_ptr. Verify virtual dispatch.
- Compare performance of value vs pointer containers.

---

## ESTIMATED TIME FOR EACH LEVEL

| Level | Topics | Sub-tasks | Estimated Time |
|:------|:-------|:----------|:---------------|
| 0 | Memory Model | 4 × 3 = 12 | 2 hours |
| 1 | Type System | 3 × 3 = 9 | 1.5 hours |
| 2 | Object Model | 3 × 3 = 9 | 1.5 hours |
| 3 | Polymorphism | 3 × 3 = 9 | 1.5 hours |
| 4 | Ownership | 3 × 3 = 9 | 1.5 hours |
| 5 | Templates | 3 × 3 = 9 | 1.5 hours |
| 6 | Callables | 3 × 3 = 9 | 1.5 hours |
| CC | Cross-cutting | 3 × 3 = 9 | 1.5 hours |
| **Total** | | 75 sub-tasks | **13 hours** |

---

## VERIFICATION QUESTIONS (End of Lesson)

After completing Lesson 1, user should answer:

1. What is sizeof(struct { char a; int b; char c; })? Why?
2. What is the difference between pointer and reference at assembly level?
3. What happens when you delete Base* pointing to Derived without virtual destructor?
4. What is the difference between shared_ptr(new T) and make_shared<T>()?
5. What is the type of x in `auto x = 5.0;`?
6. What is sizeof(lambda) with no captures?
7. What is the overhead of std::function vs direct lambda call?

---

## FAILURE PREDICTIONS (Global)

| ID | Failure Pattern | Affected Levels |
|:---|:----------------|:----------------|
| F1 | Confuse address with value | 0, 1 |
| F2 | Forget padding in sizeof calculation | 0, 2 |
| F3 | Expect reference to rebind | 1 |
| F4 | Forget virtual destructor | 3 |
| F5 | Create circular shared_ptr | 4 |
| F6 | Use decltype(x) with const auto& expecting non-const | 5 |
| F7 | Capture by reference after scope ends | 6 |
| F8 | Compare strings by pointer instead of content | CC2 |
| F9 | Store polymorphic objects by value | CC3 |
| F10 | Assume template = runtime polymorphism | 5 |

---

## NEXT STEPS

1. **Select starting level** based on user's current knowledge
2. **Begin with sub-task ST1** of that level
3. **User performs calculation by hand** before seeing answer
4. **User predicts failure** before seeing trap
5. **Ground every 5 tasks** with state summary
6. **Verify understanding** with cross-cutting concerns
7. **End with verification questions** to confirm mastery
