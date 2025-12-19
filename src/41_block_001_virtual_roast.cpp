// 41_block_001_virtual_roast.cpp
// BLOCK 001: "Virtual does nothing" — prove yourself wrong

#include <cstdint>
#include <cstdio>
#include <iostream>

// =============================================================================
// EXERCISE 001: Measure sizeof with and without virtual
// =============================================================================

// Class A: no virtual
struct NoVirtual {
    double x;  // 8 bytes
    double y;  // 8 bytes
};
// Q: What is sizeof(NoVirtual)? Calculate by hand: 8 + 8 = 16
// why i need padding in this case too? I do not think so
// Class B: one virtual function
struct OneVirtual {
    double x;  // 8 bytes
    double y;  // 8 bytes
    virtual ~OneVirtual() = default;
    virtual void foo() {}
};
// Q: What is sizeof(OneVirtual)? 
// Your guess: 8 + 8 = 24   jj 
// Reality: 8 (vptr) + 8 + 8 = 24
// this is wrong i think becasue this will be far more becasue of the function 

// =============================================================================
// EXERCISE 002: Print the hidden vptr
// =============================================================================

void print_vptr(const void* obj, const char* label) {
    // Object's first 8 bytes = vptr (on x86_64)
    const void* vptr = *reinterpret_cast<void* const*>(obj);
    std::printf("[%s] object addr = %p, vptr = %p\n", label, obj, vptr);
    // // where is this vptr in the elf of the file?{}
}

// =============================================================================
// EXERCISE 003: See two objects with same vptr
// =============================================================================

struct Animal {
    virtual ~Animal() = default;
    virtual void speak() { std::cout << "...\n"; }
};

// Q: If you create two Animal objects a1 and a2, do they share the same vptr?
// Your prediction: _______ (yes/no)
// Why: ____________________________________________no___

// =============================================================================
// EXERCISE 004: See derived class has DIFFERENT vptr
// =============================================================================

struct Dog : Animal {
    void speak() override { std::cout << "Woof\n"; }
};

struct Cat : Animal {
    void speak() override { std::cout << "Meow\n"; }
};

// Q: Does Dog share vptr with Animal?
// Your prediction: _______ (yes/
// Q: Does Dog share vptr with Cat?
// Your prediction: _______ no

// =============================================================================
// MAIN: Verify your predictions
// =============================================================================

int main() {
    std::cout << "=== EXERCISE 001: sizeof measurement ===\n";
    std::cout << "sizeof(NoVirtual) = " << sizeof(NoVirtual) << "\n";
    std::cout << "sizeof(OneVirtual) = " << sizeof(OneVirtual) << "\n";
    std::cout << "Difference = " << sizeof(OneVirtual) - sizeof(NoVirtual) << " bytes\n";
    std::cout << "Q: Where did the extra bytes come from?\n";
    std::cout << "A: _______ hidden vptrt at 0________relocation read only_________________ (you fill)\n\n";

    std::cout << "=== EXERCISE 002: Print vptr ===\n";
    OneVirtual obj1;
    print_vptr(&obj1, "OneVirtual obj1");
    std::cout << "Q: The vptr points to which section of the executable?\n";
    std::cout << "A: relocation read only________________________________ (you fill)\n\n";

    std::cout << "=== EXERCISE 003: Two objects, same class ===\n";
    Animal a1, a2;
    print_vptr(&a1, "Animal a1");
    print_vptr(&a2, "Animal a2");
    std::cout << "Q: Are the vptrs equal?\n";
    std::cout << "A: ________________________________ (you fill)\n";
    std::cout << "Q: Why would the compiler make them share?\n";
    std::cout << "A: ________________________________ (you fill)\n\n";

    std::cout << "=== EXERCISE 004: Different derived classes ===\n";
    Dog d;
    Cat c;
    Animal* ptr_d = &d;
    Animal* ptr_c = &c;
    print_vptr(&d, "Dog d");
    print_vptr(&c, "Cat c");
    std::cout << "Q: Are Dog and Cat vptrs different?\n";
    std::cout << "A: ________________________________ (you fill)\n";
    std::cout << "Q: This is how ptr->speak() knows which function to call.\n";
    std::cout << "   Draw the vtable lookup by hand:\n";
    std::cout << "   ptr_d = " << ptr_d << "\n";
    std::cout << "   Step 1: Load vptr = *(void**)ptr_d = ?\n";
    std::cout << "   Step 2: Load vtable slot 0 = *(vptr + 0) = ?\n";
    std::cout << "   Step 3: CALL that address\n\n";

    std::cout << "=== EXERCISE 005: Call through base pointer ===\n";
    std::cout << "ptr_d->speak(): ";
    ptr_d->speak();
    std::cout << "ptr_c->speak(): ";
    ptr_c->speak();
    std::cout << "Q: How did the CPU know to call Dog::speak vs Cat::speak?\n";
    std::cout << "A: ________________________________ (you fill)\n\n";

    std::cout << "=== ROAST CHECK ===\n";
    std::cout << "Before this exercise, you thought virtual does nothing.\n";
    std::cout << "Now you have measured:\n";
    std::cout << "  - Extra " << sizeof(OneVirtual) - sizeof(NoVirtual) << " bytes per object\n";
    std::cout << "  - Hidden pointer at offset 0\n";
    std::cout << "  - Different vptrs for different derived classes\n";
    std::cout << "  - Runtime lookup before every virtual call\n";
    std::cout << "Virtual is NOT free. Virtual is NOT magic. Virtual is data.\n";

    return 0;
}

// =============================================================================
// YOUR TASK AFTER RUNNING:
// =============================================================================
// 1. Write down the vptr addresses you observed
// 2. Verify: a1.vptr == a2.vptr
// 3. Verify: d.vptr != c.vptr
// 4. Draw the memory layout of Dog object:
//    +--------+-------+
//    | Offset | Value |
//    +--------+-------+
//    | 0x00   | vptr = ________ |
//    +--------+-------+
//    (Dog has no extra members, so size = 8)
//
// 5. Draw the vtable for Dog:
//    +--------+------------------+
//    | Slot 0 | &Dog::speak = __ |
//    +--------+------------------+
//
// 6. Show the CPU instructions for ptr_d->speak():
//    mov rax, [ptr_d]        ; rax = ________
//    mov rcx, [rax]          ; rcx = ________ (vptr)
//    call [rcx + 0]          ; call ________  (Dog::speak address)
