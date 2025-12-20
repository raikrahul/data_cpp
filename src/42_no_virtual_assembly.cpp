// 42_no_virtual_assembly.cpp
// NO virtual functions - analyze assembly to see direct call

#include <cstdio>

struct Base {
    int x;
    int y;
    // NO virtual keyword → NO vptr → NO vtable → direct call
    void someFun() { std::printf("Base::someFun x=%d y=%d\n", x, y); }
};

struct Derived : Base {
    int z;
    void someFun() { std::printf("Derived::someFun x=%d y=%d z=%d\n", x, y, z); }
};

int main() {
    Base baseObj;
    baseObj.x = 10;
    baseObj.y = 20;

    // Case 1: Direct call on Base object
    baseObj.someFun();

    // Case 2: Pointer to Base pointing to Base object
    Base* b = &baseObj;
    b->someFun();

    // Case 3: Derived object
    Derived derivedObj;
    derivedObj.x = 100;
    derivedObj.y = 200;
    derivedObj.z = 300;

    // Case 4: Base pointer pointing to Derived object
    // NO virtual → calls Base::someFun, NOT Derived::someFun
    Base* b2 = &derivedObj;
    b2->someFun();  // <-- THIS CALLS Base::someFun (static binding)

    // Case 5: Derived pointer calls Derived::someFun
    Derived* d = &derivedObj;
    d->someFun();

    return 0;
}

// COMPILE TO ASSEMBLY:
// g++ -O0 -S -fno-exceptions -fno-rtti 42_no_virtual_assembly.cpp -o 42_no_virtual_assembly.s
//
// EXPECTED ASSEMBLY FOR b->someFun():
//   mov rdi, [rbp-8]     ; load b (pointer to object) into rdi
//   call _ZN4Base7someFunEv  ; DIRECT call to Base::someFun (mangled name)
//
// NO vptr load. NO vtable lookup. Address known at compile time.
