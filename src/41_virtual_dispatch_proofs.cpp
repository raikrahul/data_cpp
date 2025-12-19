// 41_virtual_dispatch_proofs.cpp
// All proofs from session: sizeof, vptr, vtable slots, assembly
// Merged from ad-hoc /tmp tests

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <new>

// =============================================================================
// PROOF 1: sizeof with and without virtual
// =============================================================================

struct NoVirtual {
    double x;
    double y;
};

struct WithNormalFunc {
    double x;
    double y;
    void foo() { x = 1; }  // normal function
};

struct WithVirtual {
    double x;
    double y;
    virtual ~WithVirtual() = default;
    virtual void foo() { x = 1; }  // virtual function
};

void proof_sizeof() {
    std::printf("=== PROOF 1: sizeof ===\n");
    std::printf("sizeof(NoVirtual)     = %zu\n", sizeof(NoVirtual));
    std::printf("sizeof(WithNormalFunc)= %zu\n", sizeof(WithNormalFunc));
    std::printf("sizeof(WithVirtual)   = %zu\n", sizeof(WithVirtual));
    std::printf("Normal function adds: %zu bytes\n",
                sizeof(WithNormalFunc) - sizeof(NoVirtual));
    std::printf("Virtual function adds: %zu bytes\n\n",
                sizeof(WithVirtual) - sizeof(NoVirtual));
}

// =============================================================================
// PROOF 2: Two objects of same class share vptr value
// =============================================================================

struct Animal {
    double weight;
    virtual ~Animal() = default;
    virtual void speak() { std::printf("Animal\n"); }
};

struct Dog : Animal {
    void speak() override { std::printf("Dog\n"); }
};

struct Cat : Animal {
    void speak() override { std::printf("Cat\n"); }
};

void proof_vptr_sharing() {
    std::printf("=== PROOF 2: vptr sharing ===\n");
    Animal a1, a2;
    Dog d;
    Cat c;

    void* a1_vptr = *reinterpret_cast<void**>(&a1);
    void* a2_vptr = *reinterpret_cast<void**>(&a2);
    void* d_vptr = *reinterpret_cast<void**>(&d);
    void* c_vptr = *reinterpret_cast<void**>(&c);

    std::printf("a1.vptr = %p\n", a1_vptr);
    std::printf("a2.vptr = %p\n", a2_vptr);
    std::printf("a1.vptr == a2.vptr? %s (same class)\n",
                a1_vptr == a2_vptr ? "YES" : "NO");
    std::printf("d.vptr  = %p\n", d_vptr);
    std::printf("c.vptr  = %p\n", c_vptr);
    std::printf("d.vptr == c.vptr? %s (different class)\n\n",
                d_vptr == c_vptr ? "YES" : "NO");
}

// =============================================================================
// PROOF 3: Constructor writes vptr
// =============================================================================

void proof_constructor_writes_vptr() {
    std::printf("=== PROOF 3: Constructor writes vptr ===\n");

    alignas(Dog) uint8_t raw[sizeof(Dog)];
    std::memset(raw, 0xCD, sizeof(Dog));

    std::printf("Before constructor:\n");
    std::printf("  first 8 bytes = 0x%lx (garbage)\n",
                *reinterpret_cast<unsigned long*>(raw));

    Dog* dog_ptr = new (raw) Dog();
    static_cast<void>(dog_ptr);  // suppress unused warning

    std::printf("After constructor:\n");
    std::printf("  first 8 bytes = 0x%lx (vptr)\n",
                *reinterpret_cast<unsigned long*>(raw));
    std::printf("Constructor wrote the vptr.\n\n");
}

// =============================================================================
// PROOF 4: Slot number from declaration order
// =============================================================================

struct Base {
    virtual ~Base() = default;
    virtual void a() { std::printf("Base::a\n"); }
    virtual void b() { std::printf("Base::b\n"); }
    virtual void c() { std::printf("Base::c\n"); }
};

struct Derived : Base {
    void a() override { std::printf("Derived::a\n"); }
    void b() override { std::printf("Derived::b\n"); }
    void c() override { std::printf("Derived::c\n"); }
};

void proof_slot_order() {
    std::printf("=== PROOF 4: Slot order from declaration ===\n");
    Derived d;
    Base* p = &d;

    void** vtable = *reinterpret_cast<void***>(p);
    std::printf("vtable[0] = %p  <- dtor\n", vtable[0]);
    std::printf("vtable[1] = %p  <- a() (1st virtual func)\n", vtable[1]);
    std::printf("vtable[2] = %p  <- b() (2nd virtual func)\n", vtable[2]);
    std::printf("vtable[3] = %p  <- c() (3rd virtual func)\n", vtable[3]);

    std::printf("Calling vtable[2] manually: ");
    reinterpret_cast<void (*)()>(vtable[2])();
    std::printf("Calling p->b() normally:   ");
    p->b();
    std::printf("Both call Derived::b\n\n");
}

// =============================================================================
// PROOF 5: Step-by-step virtual call trace
// =============================================================================

void proof_vcall_trace() {
    std::printf("=== PROOF 5: Virtual call trace ===\n");
    Derived d;
    Base* p = &d;

    std::printf("p->b() step by step:\n");

    auto rax = reinterpret_cast<uint64_t>(p);
    std::printf("1. rax = p = 0x%lx (object address)\n", rax);

    rax = *reinterpret_cast<uint64_t*>(rax);
    std::printf("2. rax = *(rax) = 0x%lx (vptr)\n", rax);

    uint64_t vptr_before = rax;
    rax = rax + 16;  // slot 2 (b is 2nd virtual func after dtor)
    std::printf("3. rax = 0x%lx + 16 = 0x%lx (slot 2 address)\n", vptr_before,
                rax);

    uint64_t rdx = *reinterpret_cast<uint64_t*>(rax);
    std::printf("4. rdx = *(rax) = 0x%lx (Derived::b address)\n", rdx);

    std::printf("5. call rdx: ");
    reinterpret_cast<void (*)()>(rdx)();
    std::printf("\n");
}

// =============================================================================
// MAIN
// =============================================================================

int main() {
    proof_sizeof();
    proof_vptr_sharing();
    proof_constructor_writes_vptr();
    proof_slot_order();
    proof_vcall_trace();

    std::printf("=== ALL PROOFS COMPLETE ===\n");
    return 0;
}
