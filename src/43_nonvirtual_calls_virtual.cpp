// 43_nonvirtual_calls_virtual.cpp
// PROOF: non-virtual function calling virtual function → virtual dispatch inside

#include <cstdio>
#include <cstdint>

class Base {
public:
    virtual void bar() { std::printf("Base::bar\n"); }
    virtual ~Base() = default;
};

class D : public Base {
public:
    // foo is NON-VIRTUAL
    void foo() {
        std::printf("D::foo calling bar()...\n");
        bar();  // <-- THIS IS VIRTUAL DISPATCH (uses vptr)
    }
    
    // bar OVERRIDES Base::bar
    void bar() override { std::printf("D::bar\n"); }
};

void dump_vptr(const void* obj, const char* label) {
    const void* vptr = *reinterpret_cast<void* const*>(obj);
    std::printf("[%s] vptr = %p\n", label, vptr);
}

int main() {
    D d;
    
    std::printf("=== Object layout ===\n");
    std::printf("&d = %p\n", static_cast<void*>(&d));
    dump_vptr(&d, "D");
    std::printf("sizeof(D) = %zu\n\n", sizeof(D));
    
    // CASE 1: D* calls foo (non-virtual)
    std::printf("=== D* pd = &d; pd->foo(); ===\n");
    D* pd = &d;
    pd->foo();
    // EXPECTED OUTPUT:
    //   D::foo calling bar()...
    //   D::bar  <-- virtual dispatch worked!
    
    std::printf("\n");
    
    // CASE 2: Base* calls bar (virtual)
    std::printf("=== Base* pb = &d; pb->bar(); ===\n");
    Base* pb = &d;
    pb->bar();
    // EXPECTED OUTPUT:
    //   D::bar  <-- virtual dispatch
    
    // CASE 3: Prove foo is NOT in Base
    // pb->foo();  // COMPILE ERROR: 'foo' is not a member of 'Base'
    
    return 0;
}

// COMPILE:
// g++ -std=c++17 -O0 -g 43_nonvirtual_calls_virtual.cpp -o 43_test
//
// GENERATE ASSEMBLY:
// g++ -std=c++17 -O0 -S -fno-exceptions 43_nonvirtual_calls_virtual.cpp -o 43_nonvirtual_calls_virtual.s
//
// EXPECTED ASSEMBLY FOR D::foo:
//   D::foo is direct call (no vptr lookup to CALL foo)
//   BUT inside foo(), call to bar() has vptr lookup:
//     mov rax, [rdi]       ; rax = vptr from this
//     mov rax, [rax + 0]   ; rax = vtable[0] = &bar
//     call rax             ; virtual dispatch to bar()
