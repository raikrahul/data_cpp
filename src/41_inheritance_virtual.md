```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ Base object at 0x7FFF0000: |vptr=0x4000|                    vtable at 0x4000: |&Base::speak|                    │
│ Derived object at 0xA000:  |vptr=0x4100|                    vtable at 0x4100: |&Derived::speak|                 │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ b->speak(): load b=0xA000 → load vptr=0x4100 → load vtable[0]=&Derived::speak → call → "Derived"               │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. struct Base { virtual void speak(); } → sizeof=8 (vptr only)
02. Base at 0x7FFF0000 = |vptr=0x4000|, vtable at 0x4000 = |&Base::speak|
03. struct Derived : Base { void speak() override; } → sizeof=8
04. Derived at 0xA000 = |vptr=0x4100|, vtable at 0x4100 = |&Derived::speak|
05. ■ each class has own vtable, object stores vptr to that vtable ■
06. Base* b = new Derived() → b=0xA000, *b = |vptr=0x4100|
07. b->speak() → load vptr=0x4100 → load *(0x4100+0)=&Derived::speak → call → "Derived"
08. ■ virtual dispatch = 2 loads + indirect call ■
09. Base base; base.speak() → direct call to Base::speak, no vtable lookup
10. ■ non-virtual = 1 direct call, virtual = 2 loads + indirect, overhead 5-10× ■
11. struct Animal { virtual void eat(); virtual void sleep(); virtual void move(); }
12. vtable at 0x5000 = |&Animal::eat|&Animal::sleep|&Animal::move|, 3×8=24 bytes
13. struct Dog : Animal { void eat() override; void move() override; }
14. vtable at 0x5100 = |&Dog::eat|&Animal::sleep|&Dog::move|
15. ■ override replaces vtable entry, inherit keeps base pointer ■
16. struct Base { ~Base(){} } → non-virtual destructor
17. Base* b = new Derived(); delete b → calls ~Base() only → ~Derived() not called → LEAK ✗
18. struct Base { virtual ~Base(){} } → delete b → ~Derived() then ~Base() ✓
19. ■ RULE: any virtual method → destructor MUST be virtual ■
20. struct Shape { virtual double area()=0; } → pure virtual → Shape is abstract
21. Shape s; → compile error, cannot instantiate abstract class
22. struct Circle : Shape { double area() override {return 3.14*r*r;} } → concrete
23. Shape* s = new Circle{5}; s->area() = 78.54 ✓
24. ■ pure virtual (=0) → abstract, derived must override all pure virtuals ■
---FAILURES---
F1. delete base_ptr with non-virtual dtor → derived dtor not called → leak → ✗
F2. dynamic_cast without virtual → compile error → ✗
F3. call pure virtual from constructor → UB → ✗
F4. sizeof(Derived)==sizeof(Base) assumed → wrong if Derived adds members → ✗
F5. vector<Base> storing Derived → slicing → ✗
