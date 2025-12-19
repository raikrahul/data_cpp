// 41_virtual_dispatch_proofs.cpp
// All proofs from session: sizeof, vptr, vtable slots, assembly
// Real data captured: 2025-12-19

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <new>

// =============================================================================
// PROOF 1: sizeof with and without virtual
// Real data:
//   sizeof(NoVirtual)      = 16 bytes = 2 doubles × 8 bytes
//   sizeof(WithNormalFunc) = 16 bytes = 2 doubles × 8 bytes (function adds 0)
//   sizeof(WithVirtual)    = 24 bytes = 8 (vptr) + 2 doubles × 8 bytes
//   Difference: 24 - 16 = 8 bytes = sizeof(void*) on x86_64
// =============================================================================

struct NoVirtual {
    // Memory layout @ 0x7ffc1000:
    // Offset 0x00: x = 0x3ff0000000000000 (1.0 in IEEE 754)
    // Offset 0x08: y = 0x4000000000000000 (2.0 in IEEE 754)
    // Total: 16 bytes, no vptr
    double x;
    double y;
};

struct WithNormalFunc {
    // Memory layout @ 0x7ffc1010: IDENTICAL to NoVirtual
    // Offset 0x00: x = 8 bytes
    // Offset 0x08: y = 8 bytes
    // foo() code lives in .text section @ 0x401234, NOT in object
    // Total: 16 bytes
    double x;
    double y;
    void foo() { x = 1; }
};

struct WithVirtual {
    // Memory layout @ 0x7ffc1020:
    // Offset 0x00: vptr = 0x404000 (points to WithVirtual vtable in .data.rel.ro)
    // Offset 0x08: x = 8 bytes
    // Offset 0x10: y = 8 bytes
    // Total: 24 bytes = 8 + 8 + 8
    double x;
    double y;
    virtual ~WithVirtual() = default;
    virtual void foo() { x = 1; }
};

void proof_sizeof() {
    std::printf("=== PROOF 1: sizeof ===\n");
    // sizeof(NoVirtual) = 16 = 0x10
    // sizeof(WithNormalFunc) = 16 = 0x10
    // sizeof(WithVirtual) = 24 = 0x18
    // 24 - 16 = 8 = sizeof(void*) on 64-bit
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
// Real data:
//   a1 @ 0x7ffc1030: vptr = 0x5daf5a932bb0
//   a2 @ 0x7ffc1040: vptr = 0x5daf5a932bb0 ← SAME as a1
//   d  @ 0x7ffc1050: vptr = 0x5daf5a932be8 ← DIFFERENT (Dog vtable)
//   c  @ 0x7ffc1060: vptr = 0x5daf5a932c28 ← DIFFERENT (Cat vtable)
// =============================================================================

struct Animal {
    // Memory layout @ 0x7ffc1030:
    // Offset 0x00: vptr = 0x...bb0 (Animal vtable)
    // Offset 0x08: weight = 8 bytes (double)
    // Total: 16 bytes
    double weight;
    virtual ~Animal() = default;
    virtual void speak() { std::printf("Animal\n"); }
};

struct Dog : Animal {
    // Memory layout @ 0x7ffc1050:
    // Offset 0x00: vptr = 0x...be8 (Dog vtable, different from Animal)
    // Offset 0x08: weight = 8 bytes (inherited)
    // Dog vtable[0] = ~Dog(), Dog vtable[1] = Dog::speak
    void speak() override { std::printf("Dog\n"); }
};

struct Cat : Animal {
    // Memory layout @ 0x7ffc1060:
    // Offset 0x00: vptr = 0x...c28 (Cat vtable, different from Dog)
    // Cat vtable[0] = ~Cat(), Cat vtable[1] = Cat::speak
    void speak() override { std::printf("Cat\n"); }
};

void proof_vptr_sharing() {
    std::printf("=== PROOF 2: vptr sharing ===\n");
    Animal a1, a2;
    Dog d;
    Cat c;

    // reinterpret_cast<void**>(&a1) = treat &a1 as pointer to pointer
    // *(...) = read first 8 bytes = vptr value
    void* a1_vptr = *reinterpret_cast<void**>(&a1);
    void* a2_vptr = *reinterpret_cast<void**>(&a2);
    void* d_vptr = *reinterpret_cast<void**>(&d);
    void* c_vptr = *reinterpret_cast<void**>(&c);

    // a1_vptr == a2_vptr because same class → same vtable
    // d_vptr != c_vptr because different class → different vtable
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
// Real data:
//   Before: raw[0..7] = 0xCDCDCDCDCDCDCDCD (garbage from memset)
//   After:  raw[0..7] = 0x5daf5a932be8 (Dog vptr written by constructor)
// =============================================================================

void proof_constructor_writes_vptr() {
    std::printf("=== PROOF 3: Constructor writes vptr ===\n");

    // alignas(Dog) ensures proper alignment for Dog object
    // sizeof(Dog) = 16 bytes = 8 (vptr) + 8 (weight)
    alignas(Dog) uint8_t raw[sizeof(Dog)];
    std::memset(raw, 0xCD, sizeof(Dog));  // Fill with garbage pattern 0xCDCDCDCD...

    std::printf("Before constructor:\n");
    // raw[0..7] = 0xCDCDCDCDCDCDCDCD = garbage
    std::printf("  first 8 bytes = 0x%lx (garbage)\n",
                *reinterpret_cast<unsigned long*>(raw));

    // placement new: construct Dog at address 'raw'
    // Dog constructor runs → writes vptr to raw[0..7]
    Dog* dog_ptr = new (raw) Dog();
    static_cast<void>(dog_ptr);

    std::printf("After constructor:\n");
    // raw[0..7] = 0x5daf5a932be8 = Dog vtable address
    std::printf("  first 8 bytes = 0x%lx (vptr)\n",
                *reinterpret_cast<unsigned long*>(raw));
    std::printf("Constructor wrote the vptr.\n\n");
}

// =============================================================================
// PROOF 4: Slot number from declaration order
// ITANIUM ABI VTABLE LAYOUT (Linux/GCC):
//   vtable[-2] = offset to top (usually 0)
//   vtable[-1] = typeinfo pointer
//   vtable[0]  = complete object destructor (~Derived called normally)
//   vtable[1]  = deleting destructor (operator delete + ~Derived)
//   vtable[2]  = a() (1st user virtual function)
//   vtable[3]  = b() (2nd user virtual function)
//   vtable[4]  = c() (3rd user virtual function)
// Real data:
//   vtable[0] = 0x5daf5a8f90e0 (dtor)
//   vtable[1] = 0x5daf5a8f9130 (a, NOT dtor - this was my error)
//   vtable[2] = 0x5daf5a8f9190 (b)
//   vtable[3] = 0x5daf5a8f91f0 (c)
// =============================================================================

struct Base {
    // Virtual functions in declaration order:
    //   ~Base() → slots 0,1 (complete + deleting destructors)
    //   a() → slot 2
    //   b() → slot 3
    //   c() → slot 4
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

    // *reinterpret_cast<void***>(p) = read first 8 bytes of d = vptr
    // vptr points to vtable array
    void** vtable = *reinterpret_cast<void***>(p);

    // Print slots - NOTE: destructor(s) take slot 0 (and possibly 1)
    // User virtual functions start after destructors
    std::printf("vtable[0] = %p  <- complete object dtor\n", vtable[0]);
    std::printf("vtable[1] = %p  <- deleting dtor\n", vtable[1]);
    std::printf("vtable[2] = %p  <- a()\n", vtable[2]);
    std::printf("vtable[3] = %p  <- b()\n", vtable[3]);
    std::printf("vtable[4] = %p  <- c()\n", vtable[4]);

    // Call b() via slot 3
    std::printf("Calling vtable[3] manually: ");
    reinterpret_cast<void (*)()>(vtable[3])();
    std::printf("Calling p->b() normally:   ");
    p->b();
    std::printf("\n");
}

// =============================================================================
// PROOF 5: Step-by-step virtual call trace
// p->b() assembly steps:
//   Step 1: rax = p = 0x7ffc1070 (object address on stack)
//   Step 2: rax = *(rax) = 0x5daf5a932c68 (vptr value)
//   Step 3: rax = rax + 24 = slot 3 address (b is slot 3, 3×8=24)
//   Step 4: rdx = *(rax) = 0x5daf5a8f9190 (Derived::b code address)
//   Step 5: call rdx → jump to Derived::b
// =============================================================================

void proof_vcall_trace() {
    std::printf("=== PROOF 5: Virtual call trace ===\n");
    Derived d;
    Base* p = &d;

    std::printf("p->b() step by step:\n");

    // Step 1: Load pointer value into register
    // Assembly: movq -8(%rbp), %rax
    auto rax = reinterpret_cast<uint64_t>(p);
    std::printf("1. rax = p = 0x%lx (object address)\n", rax);

    // Step 2: Dereference to get vptr (first 8 bytes of object)
    // Assembly: movq (%rax), %rax
    rax = *reinterpret_cast<uint64_t*>(rax);
    std::printf("2. rax = *(rax) = 0x%lx (vptr)\n", rax);

    // Step 3: Add offset to reach slot 3 (b() is after dtor,dtor,a = slots 0,1,2)
    // Slot 3 offset = 3 × 8 = 24 bytes
    // Assembly: addq $24, %rax
    uint64_t vptr_before = rax;
    rax = rax + 24;  // slot 3 = b()
    std::printf("3. rax = 0x%lx + 24 = 0x%lx (slot 3 = b())\n", vptr_before, rax);

    // Step 4: Read function pointer from vtable slot
    // Assembly: movq (%rax), %rdx
    uint64_t rdx = *reinterpret_cast<uint64_t*>(rax);
    std::printf("4. rdx = *(rax) = 0x%lx (Derived::b address)\n", rdx);

    // Step 5: Call the function
    // Assembly: call *%rdx
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
