01. DRAW struct Base { virtual void speak() { print("Base"); } }. MEMORY: Base object at 0x7FFF0000 = |vptr=0x4000| (8 bytes). DRAW vtable at 0x4000 = |&Base::speak|. sizeof(Base) = 8 (vptr only, no data members) ✓
02. DRAW struct Derived : Base { void speak() override { print("Derived"); } }. MEMORY: Derived at 0x7FFF0010 = |vptr=0x4100|. DIFFERENT vtable at 0x4100 = |&Derived::speak|. Derived overrides Base::speak ✓
03. WRITE Base* b = new Derived(). MEMORY: b at 0x7FFF0020 = 0xA000 (heap pointer). Derived object at 0xA000 = |vptr=0x4100|. vptr points to Derived's vtable, not Base's ✓
04. CALL b->speak(). STEP 1: load b = 0xA000. STEP 2: load vptr = *0xA000 = 0x4100 (Derived vtable). STEP 3: load speak = *(0x4100 + 0) = &Derived::speak. STEP 4: call &Derived::speak. OUTPUT: "Derived" ✓
05. ■ GROUND: virtual dispatch = load vptr → load vtable[index] → call. Runtime resolution via pointer indirection. Derived object through Base* calls Derived's method ■ NEXT: non-virtual call ■
06. WRITE Base base; base.speak(). NO virtual dispatch. Compiler knows static type = Base. DIRECT call to Base::speak at compile time. OUTPUT: "Base" ✓
07. COMPARE: b->speak() = 2 loads + indirect call (5-10 cycles). base.speak() = 1 direct call (1 cycle). VIRTUAL OVERHEAD = 5-10× slower ✓
08. ■ GROUND: virtual = runtime dispatch via vptr. Non-virtual = compile-time dispatch, no overhead ■ NEXT: vtable layout ■
09. DRAW struct Animal { virtual void eat(); virtual void sleep(); virtual void move(); }. VTABLE at 0x5000 = |&Animal::eat|&Animal::sleep|&Animal::move|. THREE entries, each 8 bytes. sizeof(vtable) = 24 bytes ✓
10. DRAW struct Dog : Animal { void eat() override; void move() override; }. VTABLE at 0x5100 = |&Dog::eat|&Animal::sleep|&Dog::move|. eat at index 0 overridden, sleep at index 1 inherited, move at index 2 overridden ✓
11. CALL Animal* a = new Dog(); a->sleep(). STEP 1: load vptr = 0x5100 (Dog's vtable). STEP 2: sleep is index 1. Load *(0x5100 + 8) = &Animal::sleep. STEP 3: call Animal::sleep. INHERITED method via Dog's vtable ✓
12. ■ GROUND: vtable index fixed at compile time. Overridden methods replace entries. Inherited methods keep base class pointers ■ NEXT: virtual destructor ■
13. WRITE struct Base { ~Base() { print("~Base"); } }. NO virtual destructor. WRITE struct Derived : Base { int* data; ~Derived() { delete data; print("~Derived"); } }. Derived has resource to clean up ✓
14. WRITE Base* b = new Derived(); delete b. STEP 1: destructor called. STEP 2: ~Base() called (static type = Base). STEP 3: ~Derived() NOT called. data NOT deleted. MEMORY LEAK ✗
15. FIX: struct Base { virtual ~Base() { print("~Base"); } }. NOW delete b calls: ~Derived() first (cleans data), then ~Base(). CORRECT destruction order ✓
16. ■ GROUND: RULE = if class has any virtual method, destructor MUST be virtual. Otherwise derived resources leak when deleted through base pointer ■ NEXT: pure virtual ■
17. WRITE struct Shape { virtual double area() = 0; }. PURE virtual = no definition. Shape is ABSTRACT. Shape s; → compile error, cannot instantiate abstract class ✓
18. WRITE struct Circle : Shape { double r; double area() override { return 3.14159 * r * r; } }. Circle provides definition → Circle is CONCRETE. Circle c; → valid ✓
19. CALL Shape* s = new Circle{5}; s->area(). area() = 3.14159 × 5 × 5 = 78.54. DISPATCH via vtable to Circle::area ✓
20. ■ GROUND: pure virtual (=0) makes class abstract. Derived must override all pure virtuals to be instantiable ■ NEXT: multiple inheritance ■
21. DRAW struct A { virtual void f(); int a; }. sizeof(A) = 16 (vptr + a + padding). DRAW struct B { virtual void g(); int b; }. sizeof(B) = 16. DRAW struct C : A, B { int c; }. sizeof(C) = 16 + 16 + 4 + 4 = 40 (two vptrs) ✓
22. MEMORY C object at 0x7FFF0100: |vptr_A=0x6000|a|vptr_B=0x6100|b|c|. TWO vtables. A* and B* point to different offsets within C ✓
23. CAST: C c; A* pa = &c → pa = 0x7FFF0100. B* pb = &c → pb = 0x7FFF0100 + 16 = 0x7FFF0110. DIFFERENT addresses for same object ✓
24. ■ GROUND: multiple inheritance = multiple vptrs. Pointer adjustment on cast. Diamond problem requires virtual inheritance ■

---FAILURES---
F1. delete base_ptr when destructor not virtual → derived destructor not called → resource leak → ✗
F2. dynamic_cast<Derived*>(base_ptr) when base has no virtual → compile error, RTTI needs vtable → ✗
F3. calling pure virtual from constructor → undefined behavior → ✗
F4. sizeof(Derived) assumed = sizeof(Base) → wrong if Derived adds members → ✗
F5. storing polymorphic objects by value in vector<Base> → slicing, vptr of Derived replaced with Base's → ✗
F6. virtual function marked final in Derived, further derived tries override → compile error → ✓ (intended)

---AXIOMATIC CHECK---
Line 01: Introduced virtual method → need for runtime polymorphism
Line 03: Introduced Base* pointing to Derived → polymorphic usage pattern
Line 04: Introduced vtable dispatch → mechanism for virtual call resolution
Line 13: Introduced non-virtual destructor problem → derived from delete through base pointer
Line 17: Introduced pure virtual → derived from need for abstract interfaces
Line 21: Introduced multiple inheritance → derived from need to combine behaviors
NO JUMPING AHEAD: Each virtual concept derived from observed need or problem.
