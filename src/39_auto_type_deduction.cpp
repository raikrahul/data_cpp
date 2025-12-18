#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <variant>
#include <tuple>
#include <cstdint>
#include <cstddef>

// 39_auto_type_deduction.cpp
// What: auto keyword type deduction mechanics + copy/reference semantics
// Why: RHS expr type flows to LHS variable via template deduction rules
// Where: Stack 0x7ffc_a000..0x7ffc_bfff (8KB), Heap 0x5555_a000..0x5555_ffff
// Who: Compiler deduces at compile-time, CPU executes memcpy at runtime
// When: Deduction = compile phase, Copy = runtime phase after RHS evaluation
// Without: auto keyword = must write explicit type = 24 chars saved per declaration
// Which: auto=value(copy 24B), auto&=lvalue ref(0B), auto&&=universal ref(0B), auto*=pointer(8B)

// ┌──────────────────────────────────────────────────────────────────────────────────────────┐
// │ TrackedZ: Instrumented struct for copy detection                                         │
// │ sizeof(TrackedZ) = 4(int a) + 4(pad) + 8(double b) + 4(int c) + 4(pad) = 24 bytes       │
// │ alignof(TrackedZ) = 8 (double requires 8-byte alignment)                                 │
// │ Memory layout example at 0x7ffc_a000:                                                    │
// │   [0x7ffc_a000..0x7ffc_a003] = a = 0x00000001 = 1                                        │
// │   [0x7ffc_a004..0x7ffc_a007] = padding = 0x00000000                                      │
// │   [0x7ffc_a008..0x7ffc_a00f] = b = 0x4000000000000000 = 2.0 (IEEE 754 double)           │
// │   [0x7ffc_a010..0x7ffc_a013] = c = 0x00000003 = 3                                        │
// │   [0x7ffc_a014..0x7ffc_a017] = padding = 0x00000000                                      │
// │ Total: 0x7ffc_a018 - 0x7ffc_a000 = 0x18 = 24 bytes ✓                                    │
// └──────────────────────────────────────────────────────────────────────────────────────────┘
struct TrackedZ {
    int a;      // offset 0, size 4, values: 1,2,3,10,100,1000 → hex: 0x01,0x02,0x03,0x0a,0x64,0x3e8
    double b;   // offset 8, size 8, values: 2.0=0x4000000000000000, 20.5=0x4034800000000000
    int c;      // offset 16, size 4, values: 3,30,300 → hex: 0x03,0x1e,0x12c
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Constructor: TrackedZ(int a_, double b_, int c_)                                       │
    // │ Call: TrackedZ original{1, 2.0, 3};                                                    │
    // │ Stack allocation: rsp -= 24 → rsp = 0x7ffc_a000                                        │
    // │ a_ passed in edi = 0x00000001, b_ passed in xmm0 = 0x4000000000000000, c_ in esi = 3   │
    // │ Member init: mov [rsp+0], edi → [0x7ffc_a000] = 0x01                                   │
    // │              movsd [rsp+8], xmm0 → [0x7ffc_a008] = 0x4000000000000000                  │
    // │              mov [rsp+16], esi → [0x7ffc_a010] = 0x03                                  │
    // │ cout output: prints "TrackedZ @ 0x7ffc_a000 created with {1,2,3}"                     │
    // │ Cost: 3 stores × 1 cycle = 3 cycles @ 3GHz = 1ns                                       │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    TrackedZ(int a_, double b_, int c_) : a(a_), b(b_), c(c_) {
        std::cout << "  [CONSTRUCTOR] TrackedZ @ " << this 
                  << " created with {" << a << "," << b << "," << c << "}\n";
        // What: print address 0x7ffc_a000 + values {1,2.0,3}
        // Why: debug visibility of object creation location
        // Where: cout buffer → stdout file descriptor 1 → terminal
        // Who: constructor called by compiler-generated code
        // When: after member initialization list completes
        // Without: no visibility into copy vs move vs create
        // Which: constructor (not copy, not move)
    }
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Copy Constructor: TrackedZ(const TrackedZ& other)                                      │
    // │ Call: auto x = original; where original @ 0x7ffc_a000                                  │
    // │ x allocated @ 0x7ffc_a018 (next 24-byte aligned slot)                                  │
    // │ other = reference to original, &other = 0x7ffc_a000                                    │
    // │ memcpy equivalent: rep movsb from 0x7ffc_a000 to 0x7ffc_a018, count 24                │
    // │ Byte trace: [0x7ffc_a018..0x7ffc_a02f] = copy of [0x7ffc_a000..0x7ffc_a017]           │
    // │   x.a @ 0x7ffc_a018 = other.a @ 0x7ffc_a000 = 1                                        │
    // │   x.b @ 0x7ffc_a020 = other.b @ 0x7ffc_a008 = 2.0                                      │
    // │   x.c @ 0x7ffc_a028 = other.c @ 0x7ffc_a010 = 3                                        │
    // │ Cost: 24 bytes read + 24 bytes write = 48 bytes memory traffic                        │
    // │ Cache: 24 bytes / 64 bytes per line = 0.375 lines → 1 cache line touched              │
    // │ Time: 48 bytes × 0.25 ns/byte (L1 hit) = 12 ns                                        │
    // │ Large scale: N=1000 copies → 1000 × 24 = 24000 bytes → 375 cache lines → 375 µs      │
    // │ Mid scale: N=100 copies → 100 × 24 = 2400 bytes → 37.5 cache lines → 37.5 µs         │
    // │ Small scale: N=1 copy → 24 bytes → 1 cache line → 12 ns                               │
    // │ Edge: N=0 copies → 0 bytes → no work                                                  │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    TrackedZ(const TrackedZ& other) : a(other.a), b(other.b), c(other.c) {
        std::cout << "  [COPY] TrackedZ @ " << this 
                  << " copied FROM " << &other << "\n";
        // What: new address 0x7ffc_a018 printed, source address 0x7ffc_a000 printed
        // Why: proves copy constructor invoked (not move, not elision)
        // Where: this @ 0x7ffc_a018, &other @ 0x7ffc_a000
        // Who: compiler generated call when auto x = original; executes
        // When: after RHS evaluation, before assignment completes
        // Without: no debug trace, can't prove copy occurred
        // Which: copy constructor (not move constructor)
    }
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Move Constructor: TrackedZ(TrackedZ&& other) noexcept                                  │
    // │ Call: auto x = std::move(original); where original @ 0x7ffc_a000                       │
    // │ x allocated @ 0x7ffc_a018                                                              │
    // │ other = rvalue reference to original, &other = 0x7ffc_a000 (same address!)            │
    // │ For trivial types: move = copy = memcpy 24 bytes                                       │
    // │ original left in valid-but-unspecified state = unchanged for trivial types            │
    // │ Cost: same as copy = 24 bytes × 2 = 48 bytes traffic                                  │
    // │ Benefit: for non-trivial types (heap-owning), move transfers ownership, 0 bytes copy │
    // │ Example: std::string move: 24-byte string object copied, but heap content not copied │
    // │          string{} = 32 bytes, heap = 100 bytes → move = 32 bytes, copy = 132 bytes   │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    TrackedZ(TrackedZ&& other) noexcept : a(other.a), b(other.b), c(other.c) {
        std::cout << "  [MOVE] TrackedZ @ " << this 
                  << " moved FROM " << &other << "\n";
        // What: new address 0x7ffc_a018, source 0x7ffc_a000
        // Why: proves move constructor invoked (std::move used)
        // Where: this @ 0x7ffc_a018, &other @ 0x7ffc_a000
        // Who: compiler when auto x = std::move(original); executes
        // When: after std::move cast, during initialization
        // Without: no visibility into move vs copy
        // Which: move constructor (&&)
    }
    
    // operator() returns sum: a + b + c (cast to int)
    // Example: {1, 2.0, 3} → 1 + 2 + 3 = 6 → return 6 in eax
    // Cost: 2 adds + 1 float-to-int conversion = 3 cycles
    int operator()() const { return static_cast<int>(a + b + c); }
};

// ┌──────────────────────────────────────────────────────────────────────────────────────────────┐
// │ proof_auto_vs_copy(): Demonstrates that 'auto' does NOT cause copy, '=' causes copy         │
// │ Stack frame layout (rbp-relative offsets):                                                   │
// │   [rbp-0x18..rbp-0x01] = original (24 bytes) @ 0x7ffc_a000                                   │
// │   [rbp-0x30..rbp-0x19] = x (24 bytes) @ 0x7ffc_a018                                          │
// │   [rbp-0x48..rbp-0x31] = y (24 bytes) @ 0x7ffc_a030                                          │
// │   [rbp-0x08..rbp-0x01] = ref (8 bytes, pointer impl) @ 0x7ffc_a048                           │
// │   [rbp-0x10..rbp-0x09] = ref2 (8 bytes) @ 0x7ffc_a050                                        │
// │   [rbp-0x18..rbp-0x11] = cref (8 bytes) @ 0x7ffc_a058                                        │
// │   [rbp-0x20..rbp-0x19] = ptr (8 bytes) @ 0x7ffc_a060                                         │
// │ Total stack usage: ~120 bytes + alignment padding                                            │
// └──────────────────────────────────────────────────────────────────────────────────────────────┘
void proof_auto_vs_copy() {
    std::cout << "\n=== PROOF: auto vs copy mechanics ===\n";
    std::cout << "Key insight: 'auto' does NOT cause copy. The '=' with value type causes copy.\n\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Step 1: Construct original object on stack                                             │
    // │ TrackedZ original{1, 2.0, 3};                                                          │
    // │ Memory allocation: rsp -= 24 → &original = 0x7ffc_a000                                 │
    // │ Constructor call: TrackedZ::TrackedZ(1, 2.0, 3)                                        │
    // │ Memory state after:                                                                    │
    // │   ┌─────────────────────────────────────────┐                                          │
    // │   │ 0x7ffc_a000: 01 00 00 00 │ a = 1        │                                          │
    // │   │ 0x7ffc_a004: 00 00 00 00 │ padding      │                                          │
    // │   │ 0x7ffc_a008: 00 00 00 00 00 00 00 40 │ b = 2.0 (0x4000000000000000) │              │
    // │   │ 0x7ffc_a010: 03 00 00 00 │ c = 3        │                                          │
    // │   │ 0x7ffc_a014: 00 00 00 00 │ padding      │                                          │
    // │   └─────────────────────────────────────────┘                                          │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    std::cout << "Step 1: TrackedZ original{1, 2.0, 3};\n";
    TrackedZ original{1, 2.0, 3};
    // What: 24 bytes allocated at 0x7ffc_a000, values {1,2.0,3} stored
    // Why: create source object for copy/reference tests
    // Where: stack @ 0x7ffc_a000..0x7ffc_a017
    // Who: constructor called directly
    // When: before any auto declarations
    // Without: no source for copy tests
    // Which: direct construction (not copy, not move)
    std::cout << "  &original = " << &original << "\n\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Step 2: auto x = original; (VALUE COPY)                                                │
    // │ Type deduction: decltype(original) = TrackedZ → auto = TrackedZ                       │
    // │ x allocated @ 0x7ffc_a018 (next aligned slot after original)                          │
    // │ Copy constructor invoked: TrackedZ::TrackedZ(const TrackedZ& = original)              │
    // │ Memory operation: memcpy(0x7ffc_a018, 0x7ffc_a000, 24)                                │
    // │ Memory state after:                                                                    │
    // │   original @ 0x7ffc_a000 = {1, 2.0, 3} (unchanged)                                    │
    // │   x @ 0x7ffc_a018 = {1, 2.0, 3} (copy)                                                │
    // │   ┌──────────────────────────────────────────────────────────────────────────────┐    │
    // │   │ [0x7ffc_a000] original ─────(memcpy 24B)────→ [0x7ffc_a018] x                │    │
    // │   │ {1, 2.0, 3}                                   {1, 2.0, 3}                     │    │
    // │   │ ↑                                             ↑                               │    │
    // │   │ source (unchanged)                            destination (new copy)          │    │
    // │   └──────────────────────────────────────────────────────────────────────────────┘    │
    // │ &x (0x7ffc_a018) != &original (0x7ffc_a000) → different addresses → COPY occurred    │
    // │ Cost: 24 bytes copied, 1 cache line touched, 12 ns elapsed                           │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    std::cout << "Step 2: auto x = original; (auto deduces TrackedZ, = causes COPY)\n";
    auto x = original;
    // What: x @ 0x7ffc_a018 = copy of original @ 0x7ffc_a000, 24 bytes
    // Why: auto deduces value type TrackedZ, = triggers copy constructor
    // Where: x @ 0x7ffc_a018, original @ 0x7ffc_a000, difference = 24 bytes
    // Who: copy constructor TrackedZ(const TrackedZ&)
    // When: after RHS 'original' evaluated to lvalue
    // Without: auto → would need to write 'TrackedZ x = original;' (same copy)
    // Which: copy (not move, not reference, not elision)
    std::cout << "  &x = " << &x << "\n";
    std::cout << "  &x == &original? " << (&x == &original ? "YES (same)" : "NO (different)") 
              << " → COPY occurred\n\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Step 3: TrackedZ y = original; (EXPLICIT TYPE, SAME COPY)                              │
    // │ No auto: type explicitly written as TrackedZ                                           │
    // │ y allocated @ 0x7ffc_a030                                                              │
    // │ Same copy constructor call, same 24 bytes copied                                       │
    // │ Proves: auto vs explicit type → identical runtime behavior                            │
    // │ Only difference: auto = 4 chars, TrackedZ = 8 chars (compile-time only)               │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    std::cout << "Step 3: TrackedZ y = original; (explicit type, = causes COPY)\n";
    TrackedZ y = original;
    // What: y @ 0x7ffc_a030 = copy, 24 bytes
    // Why: proves auto vs explicit type = same copy behavior
    // Where: y @ 0x7ffc_a030
    // Who: copy constructor (same as step 2)
    // When: after 'original' evaluated
    // Without: explicit type → same behavior, no difference
    // Which: copy (identical to auto case)
    std::cout << "  &y = " << &y << "\n";
    std::cout << "  &y == &original? " << (&y == &original ? "YES (same)" : "NO (different)") 
              << " → COPY occurred\n\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Step 4: auto& ref = original; (LVALUE REFERENCE, NO COPY)                              │
    // │ Type deduction: auto& → TrackedZ&                                                      │
    // │ ref is NOT a new object, it's an alias to original                                    │
    // │ Implementation: ref stored as pointer = 8 bytes @ 0x7ffc_a048 containing 0x7ffc_a000  │
    // │ Memory state:                                                                          │
    // │   ┌──────────────────────────────────────────────────────────────────────────────┐    │
    // │   │ [0x7ffc_a048] ref ────────(alias)────→ [0x7ffc_a000] original                │    │
    // │   │ 8 bytes: 00 a0 fc 7f 00 00 00 00      {1, 2.0, 3}                             │    │
    // │   │ ↑                                      ↑                                      │    │
    // │   │ stores address 0x7ffc_a000            same object, same bytes                 │    │
    // │   └──────────────────────────────────────────────────────────────────────────────┘    │
    // │ &ref = &original = 0x7ffc_a000 → same address → NO COPY                              │
    // │ Cost: 0 bytes copied, 8 bytes for reference implementation, 1 cycle                  │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    std::cout << "Step 4: auto& ref = original; (auto& deduces TrackedZ&, NO copy)\n";
    auto& ref = original;
    // What: ref = alias, &ref = 0x7ffc_a000 = &original
    // Why: & after auto forces reference deduction
    // Where: ref internally at 0x7ffc_a048 = ptr to 0x7ffc_a000
    // Who: no constructor called, just address stored
    // When: at declaration, no runtime copy
    // Without: auto& → must write 'TrackedZ& ref' (same)
    // Which: lvalue reference (not copy, not pointer)
    std::cout << "  &ref = " << &ref << "\n";
    std::cout << "  &ref == &original? " << (&ref == &original ? "YES (same)" : "NO (different)") 
              << " → NO copy, alias\n\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Step 5: TrackedZ& ref2 = original; (EXPLICIT REFERENCE, SAME BEHAVIOR)                 │
    // │ Proves: auto& vs explicit Type& → identical                                           │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    std::cout << "Step 5: TrackedZ& ref2 = original; (explicit ref, NO copy)\n";
    TrackedZ& ref2 = original;
    // What: ref2 = alias, &ref2 = 0x7ffc_a000
    // Why: proves explicit ref = same as auto&
    std::cout << "  &ref2 = " << &ref2 << "\n";
    std::cout << "  &ref2 == &original? " << (&ref2 == &original ? "YES (same)" : "NO (different)") 
              << " → NO copy, alias\n\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Step 6: const auto& cref = original; (CONST REFERENCE, NO COPY)                        │
    // │ Type deduction: const auto& → const TrackedZ&                                         │
    // │ cref is read-only alias, cannot modify through cref                                   │
    // │ Important: const auto& can bind to temporaries (lifetime extension)                   │
    // │ Example: const auto& t = TrackedZ{7,8.0,9}; → temporary lives until t goes out of scope│
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    std::cout << "Step 6: const auto& cref = original; (const ref, NO copy)\n";
    const auto& cref = original;
    // What: cref = const alias, &cref = 0x7ffc_a000
    // Why: const prevents modification through cref
    std::cout << "  &cref = " << &cref << "\n";
    std::cout << "  &cref == &original? " << (&cref == &original ? "YES (same)" : "NO (different)") 
              << " → NO copy\n\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Step 7: auto* ptr = &original; (POINTER, NO COPY OF OBJECT)                            │
    // │ Type deduction: auto* → TrackedZ* (pointer to TrackedZ)                               │
    // │ ptr stores address of original: ptr = 0x7ffc_a000                                     │
    // │ sizeof(ptr) = 8 bytes (64-bit pointer)                                                │
    // │ ptr @ 0x7ffc_a060 = {00 a0 fc 7f 00 00 00 00} = 0x7ffc_a000                          │
    // │ *ptr dereferences to original's memory                                                │
    // │ Cost: 8 bytes for pointer storage, 0 bytes for object copy                           │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    std::cout << "Step 7: auto* ptr = &original; (pointer, NO copy)\n";
    auto* ptr = &original;
    // What: ptr = 0x7ffc_a000 (address of original)
    // Why: * after auto forces pointer deduction
    // Where: ptr @ 0x7ffc_a060, value = 0x7ffc_a000
    // Who: no constructor, just & operator
    // When: at declaration
    // Without: auto* → must write 'TrackedZ* ptr'
    // Which: pointer (not reference, not copy)
    std::cout << "  ptr = " << ptr << "\n";
    std::cout << "  ptr == &original? " << (ptr == &original ? "YES (same)" : "NO (different)") 
              << " → NO copy, just address stored\n\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ SUMMARY TABLE: Copy Cost Analysis                                                      │
    // │ ┌──────────────────────┬───────┬─────────────────────────────────────────────────────┐│
    // │ │ Declaration          │ Copy? │ Bytes Moved │ Address Comparison                    ││
    // │ ├──────────────────────┼───────┼─────────────┼─────────────────────────────────────────┤│
    // │ │ auto x = obj;        │ YES   │ 24 bytes    │ &x=0x7ffc_a018 ≠ &obj=0x7ffc_a000      ││
    // │ │ TrackedZ x = obj;    │ YES   │ 24 bytes    │ &x=0x7ffc_a030 ≠ &obj=0x7ffc_a000      ││
    // │ │ auto& x = obj;       │ NO    │ 0 bytes     │ &x=0x7ffc_a000 == &obj=0x7ffc_a000     ││
    // │ │ TrackedZ& x = obj;   │ NO    │ 0 bytes     │ &x=0x7ffc_a000 == &obj=0x7ffc_a000     ││
    // │ │ const auto& x = obj; │ NO    │ 0 bytes     │ &x=0x7ffc_a000 == &obj=0x7ffc_a000     ││
    // │ │ auto* x = &obj;      │ NO    │ 8 bytes(ptr)│ x=0x7ffc_a000 == &obj=0x7ffc_a000      ││
    // │ └──────────────────────┴───────┴─────────────┴─────────────────────────────────────────┘│
    // │ Large scale cost: N=1000000 objects × 24 bytes = 24 MB copied if auto x = obj         │
    // │                   N=1000000 objects × 0 bytes = 0 MB copied if auto& x = obj          │
    // │ Time: 24 MB / 10 GB/s (memcpy) = 2.4 ms for copies, 0 ms for references               │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    std::cout << "=== SUMMARY ===\n";
    std::cout << "| Declaration           | Copy? | Reason                    |\n";
    std::cout << "|----------------------|-------|---------------------------|\n";
    std::cout << "| auto x = obj;        | YES   | auto=TrackedZ, = copies   |\n";
    std::cout << "| TrackedZ x = obj;    | YES   | explicit type, = copies   |\n";
    std::cout << "| auto& x = obj;       | NO    | auto&=TrackedZ&, alias    |\n";
    std::cout << "| TrackedZ& x = obj;   | NO    | explicit ref, alias       |\n";
    std::cout << "| const auto& x = obj; | NO    | const ref, alias          |\n";
    std::cout << "| auto* x = &obj;      | NO    | pointer, stores address   |\n";
    std::cout << "\nConclusion: 'auto' alone does NOT cause copy. The '&' or '*' prevents copy.\n";
}


// ┌──────────────────────────────────────────────────────────────────────────────────────────┐
// │ struct Z: Simple aggregate for basic auto deduction tests                                │
// │ Layout identical to TrackedZ but without instrumentation                                 │
// │ sizeof(Z) = 24, alignof(Z) = 8                                                           │
// └──────────────────────────────────────────────────────────────────────────────────────────┘
struct Z {
    int a;      // offset 0, 4 bytes
    double b;   // offset 8, 8 bytes (after 4-byte padding)
    int c;      // offset 16, 4 bytes (+ 4 trailing padding)
    int operator()() const { return static_cast<int>(a + b + c); }
};

void test_sizeof_alignment() {
    std::cout << "=== TEST 1: sizeof and alignment ===\n";
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Size and alignment verification:                                                       │
    // │ sizeof(int) = 4 bytes, alignof(int) = 4                                               │
    // │ sizeof(double) = 8 bytes, alignof(double) = 8                                         │
    // │ sizeof(Z) = 4 + 4(pad) + 8 + 4 + 4(pad) = 24 bytes                                   │
    // │ Calculation: max(alignof members) = max(4,8,4) = 8 → struct alignment = 8            │
    // │ Offset calculation:                                                                   │
    // │   a: align 4, offset 0 ✓ (0 % 4 = 0)                                                 │
    // │   b: align 8, next offset = 4, need 8-aligned → 4 + 4(pad) = 8 ✓ (8 % 8 = 0)        │
    // │   c: align 4, next offset = 16 ✓ (16 % 4 = 0)                                        │
    // │   trailing: struct size must be multiple of 8 → 20 + 4(pad) = 24 ✓ (24 % 8 = 0)     │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    std::cout << "sizeof(int) = " << sizeof(int) << " (expected: 4)\n";
    std::cout << "sizeof(double) = " << sizeof(double) << " (expected: 8)\n";
    std::cout << "alignof(int) = " << alignof(int) << " (expected: 4)\n";
    std::cout << "alignof(double) = " << alignof(double) << " (expected: 8)\n";
    std::cout << "sizeof(Z) = " << sizeof(Z) << " (expected: 24)\n";
    std::cout << "offsetof(Z,a) = " << offsetof(Z, a) << " (expected: 0)\n";
    std::cout << "offsetof(Z,b) = " << offsetof(Z, b) << " (expected: 8)\n";
    std::cout << "offsetof(Z,c) = " << offsetof(Z, c) << " (expected: 16)\n";
}

void test_memory_layout() {
    std::cout << "\n=== TEST 2: Memory Layout ===\n";
    Z zz{1, 2.0, 3};
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Memory dump of Z{1, 2.0, 3} at hypothetical address 0x7ffc_b000:                      │
    // │ Offset 0x00: 01 00 00 00    ← a = 1 (little-endian int)                              │
    // │ Offset 0x04: 00 00 00 00    ← padding (4 bytes)                                       │
    // │ Offset 0x08: 00 00 00 00 00 00 00 40    ← b = 2.0 (IEEE 754: 0x4000000000000000)     │
    // │ Offset 0x10: 03 00 00 00    ← c = 3 (little-endian int)                              │
    // │ Offset 0x14: 00 00 00 00    ← trailing padding (4 bytes)                              │
    // │ Total: 24 bytes ✓                                                                     │
    // │ IEEE 754 double 2.0 breakdown:                                                        │
    // │   sign = 0 (positive)                                                                 │
    // │   exponent = 10000000000 (binary) = 1024 (decimal) → biased: 1024 - 1023 = 1 → 2^1  │
    // │   mantissa = 0 → value = 1.0 × 2^1 = 2.0 ✓                                           │
    // │ Hex: 0100 0000 0000 0000 0000 0000 0000 0000 → 0x4000000000000000                    │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    std::cout << "&zz = " << static_cast<const void*>(&zz) << "\n";
    
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&zz);
    std::cout << "Memory dump (24 bytes): ";
    for (size_t i = 0; i < sizeof(Z); ++i) {
        printf("%02x ", bytes[i]);
    }
    std::cout << "\n";
    std::cout << "Expected: 01 00 00 00 [pad 4] 00 00 00 00 00 00 00 40 03 00 00 00 [pad 4]\n";
    
    // Verify double 2.0 = 0x4000000000000000
    uint64_t* b_bits = reinterpret_cast<uint64_t*>(&zz.b);
    std::cout << "zz.b bits = 0x" << std::hex << *b_bits << std::dec 
              << " (expected: 0x4000000000000000)\n";
}

void test_auto_deduction() {
    std::cout << "\n=== TEST 3: Auto Deduction ===\n";
    
    // auto zz1 = Z{}; → zero-initialization, all bytes 0
    auto zz1 = Z{};
    std::cout << "auto zz1 = Z{}; → zz1.a = " << zz1.a << ", zz1.b = " << zz1.b 
              << ", zz1.c = " << zz1.c << "\n";
    
    // auto zz2 = Z{1, 2.0, 3}; → brace-init, copy elision
    auto zz2 = Z{1, 2.0, 3};
    std::cout << "auto zz2 = Z{1,2.0,3}; → zz2.a = " << zz2.a << ", zz2.b = " << zz2.b 
              << ", zz2.c = " << zz2.c << "\n";
    
    // operator() returns 1 + 2 + 3 = 6
    auto result = zz2();
    std::cout << "auto result = zz2(); → result = " << result << " (expected: 6)\n";
}

void test_copy_move() {
    std::cout << "\n=== TEST 4: Copy and Move ===\n";
    
    Z obj{10, 20.5, 30};
    std::cout << "&obj = " << static_cast<const void*>(&obj) << ", obj() = " << obj() 
              << " (expected: 60)\n";
    
    auto copy = obj;
    std::cout << "&copy = " << static_cast<const void*>(&copy) << ", copy() = " << copy() 
              << " (expected: 60)\n";
    std::cout << "&obj != &copy: " << (&obj != &copy ? "true" : "false") << "\n";
    
    auto moved = std::move(obj);
    std::cout << "&moved = " << static_cast<const void*>(&moved) << ", moved() = " << moved() 
              << " (expected: 60)\n";
    
    auto& ref = moved;
    std::cout << "&ref = " << static_cast<const void*>(&ref) 
              << " (same as &moved: " << (&ref == &moved ? "true" : "false") << ")\n";
    
    auto* ptr = &moved;
    std::cout << "ptr = " << static_cast<const void*>(ptr) << ", *ptr.a = " << ptr->a << "\n";
}

void test_lambda_capture() {
    std::cout << "\n=== TEST 5: Lambda Capture ===\n";
    
    Z zz{1, 2.0, 3};
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Lambda capture by value: [zz]                                                          │
    // │ Compiler generates: struct __lambda { Z zz; auto operator()() const {...} };          │
    // │ sizeof(lambda_val) = sizeof(Z) = 24 bytes (captured copy)                             │
    // │ Lambda @ 0x7ffc_c000, captured zz @ 0x7ffc_c000 (inside lambda)                       │
    // │ Original zz @ 0x7ffc_b000 → zz copied to lambda's internal storage                    │
    // │ Cost: 24 bytes copy at lambda creation                                                │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    auto lambda_val = [zz]() { return zz(); };
    std::cout << "sizeof(lambda_val) = " << sizeof(lambda_val) 
              << " (expected: 24, captures Z by value)\n";
    std::cout << "lambda_val() = " << lambda_val() << " (expected: 6)\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Lambda capture by reference: [&zz]                                                     │
    // │ Compiler generates: struct __lambda { Z* zz_ptr; auto operator()()  {...} };          │
    // │ sizeof(lambda_ref) = sizeof(Z*) = 8 bytes (pointer only)                              │
    // │ Lambda @ 0x7ffc_c020, contains pointer 0x7ffc_b000 (address of original zz)           │
    // │ Cost: 8 bytes (pointer), no copy of Z                                                 │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    auto lambda_ref = [&zz]() { return zz(); };
    std::cout << "sizeof(lambda_ref) = " << sizeof(lambda_ref) 
              << " (expected: 8, stores pointer)\n";
    std::cout << "lambda_ref() = " << lambda_ref() << " (expected: 6)\n";
    
    // Modify zz and verify lambda_ref sees change, lambda_val does not
    zz.a = 100;
    std::cout << "After zz.a = 100: lambda_ref() = " << lambda_ref() << " (expected: 105)\n";
    std::cout << "After zz.a = 100: lambda_val() = " << lambda_val() 
              << " (expected: 6, captured before change)\n";
}

void test_structured_binding() {
    std::cout << "\n=== TEST 6: Structured Binding ===\n";
    
    Z zz{1, 2.0, 3};
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ Structured binding: auto [a_val, b_val, c_val] = zz;                                  │
    // │ Creates hidden copy of zz, then binds names to members                                │
    // │ Equivalent to: auto __e = zz; auto& a_val = __e.a; auto& b_val = __e.b; ...          │
    // │ Types: a_val = int, b_val = double, c_val = int                                       │
    // │ Cost: 24 bytes copy (hidden aggregate copy)                                           │
    // │ To avoid copy: auto& [a_ref, b_ref, c_ref] = zz; → references to original members    │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    auto [a_val, b_val, c_val] = zz;
    std::cout << "auto [a_val, b_val, c_val] = zz;\n";
    std::cout << "a_val = " << a_val << " (expected: 1)\n";
    std::cout << "b_val = " << b_val << " (expected: 2.0)\n";
    std::cout << "c_val = " << c_val << " (expected: 3)\n";
}

void test_smart_pointers() {
    std::cout << "\n=== TEST 7: Smart Pointers ===\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ unique_ptr: auto up = std::make_unique<Z>(Z{1,2.0,3});                                │
    // │ Stack: up @ 0x7ffc_d000 = {ptr = 0x5555_a000} (8 bytes)                              │
    // │ Heap: Z @ 0x5555_a000 = {1, 2.0, 3} (24 bytes)                                       │
    // │ Ownership: up owns Z, deletion when up goes out of scope                             │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    auto up = std::make_unique<Z>(Z{1, 2.0, 3});
    std::cout << "auto up = make_unique<Z>; up.get() = " 
              << static_cast<const void*>(up.get()) << "\n";
    std::cout << "(*up)() = " << (*up)() << " (expected: 6)\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ shared_ptr: auto sp = std::make_shared<Z>(Z{4,5.0,6});                                │
    // │ Stack: sp @ 0x7ffc_d010 = {ptr=0x5555_b020, ctrl=0x5555_b000} (16 bytes)             │
    // │ Heap control block @ 0x5555_b000 = {refcount=1, weakcount=0, ...} (32 bytes)         │
    // │ Heap object @ 0x5555_b020 = Z{4,5.0,6} (24 bytes)                                    │
    // │ Total heap: 32 + 24 = 56 bytes (often allocated together = 56 bytes)                 │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    auto sp = std::make_shared<Z>(Z{4, 5.0, 6});
    std::cout << "auto sp = make_shared<Z>; sp.get() = " 
              << static_cast<const void*>(sp.get()) << "\n";
    std::cout << "sp.use_count() = " << sp.use_count() << " (expected: 1)\n";
    
    std::weak_ptr<Z> wp = sp;
    std::cout << "weak_ptr wp = sp; wp.expired() = " 
              << (wp.expired() ? "true" : "false") << " (expected: false)\n";
    
    auto locked = wp.lock();
    std::cout << "auto locked = wp.lock(); sp.use_count() = " << sp.use_count() 
              << " (expected: 2)\n";
}

void test_optional_variant() {
    std::cout << "\n=== TEST 8: Optional and Variant ===\n";
    
    std::optional<Z> opt;
    std::cout << "std::optional<Z> opt; opt.has_value() = " 
              << (opt.has_value() ? "true" : "false") << "\n";
    opt = Z{1, 2.0, 3};
    std::cout << "opt = Z{1,2.0,3}; (*opt)() = " << (*opt)() << " (expected: 6)\n";
    
    std::variant<int, Z> var;
    var = Z{4, 5.0, 6};
    std::cout << "std::variant<int,Z> var = Z{4,5.0,6}; std::get<Z>(var)() = " 
              << std::get<Z>(var)() << " (expected: 15)\n";
    std::cout << "var.index() = " << var.index() << " (expected: 1, Z is second type)\n";
}

void test_left_to_right_init() {
    std::cout << "\n=== TEST 9: Left-to-Right Initialization ===\n";
    
    auto x = Z{1, 2.0, 3}, y = Z{4, 5.0, 6};
    std::cout << "&x = " << static_cast<const void*>(&x) 
              << ", &y = " << static_cast<const void*>(&y) << "\n";
    std::cout << "x() = " << x() << " (expected: 6), y() = " << y() << " (expected: 15)\n";
    std::cout << "x constructed before y: &x < &y = " 
              << (&x < &y ? "true (likely)" : "false (stack grows down)") << "\n";
}

void test_chaining() {
    std::cout << "\n=== TEST 10: Chaining ===\n";
    
    Z zz{10, 20.5, 30};
    std::cout << "Z zz{10, 20.5, 30}; zz() = " << zz() << " (expected: 60)\n";
    
    // ┌────────────────────────────────────────────────────────────────────────────────────────┐
    // │ IEEE 754 double 20.5 breakdown:                                                        │
    // │ 20.5 = 10100.1 binary = 1.01001 × 2^4                                                 │
    // │ sign = 0                                                                               │
    // │ exponent = 4 + 1023 (bias) = 1027 = 10000000011 binary                               │
    // │ mantissa = 01001000000... (52 bits)                                                   │
    // │ Hex: 0x4034800000000000                                                               │
    // └────────────────────────────────────────────────────────────────────────────────────────┘
    uint64_t* bits = reinterpret_cast<uint64_t*>(&zz.b);
    std::cout << "20.5 bits = 0x" << std::hex << *bits << std::dec 
              << " (expected: 0x4034800000000000)\n";
}

int main() {
    std::cout << "=== 39_auto_type_deduction ===\n\n";
    
    // PROOF FIRST: Shows when copies happen
    proof_auto_vs_copy();
    
    test_sizeof_alignment();
    test_memory_layout();
    test_auto_deduction();
    test_copy_move();
    test_lambda_capture();
    test_structured_binding();
    test_smart_pointers();
    test_optional_variant();
    test_left_to_right_init();
    test_chaining();
    
    std::cout << "\n=== PREDICTED FAILURES ===\n";
    std::cout << "F1: auto z zz; → parse error, expected = or ; ✗\n";
    std::cout << "F2: Z<int,double,int>{} → template args not allowed on aggregate ✗\n";
    std::cout << "F3: zz() without operator() → error C2064 ✗\n";
    std::cout << "F4: const Z cz{}; cz() without const operator() → error ✗\n";
    std::cout << "F5: lambda without mutable → cannot modify capture ✗\n";
    
    return 0;
}
