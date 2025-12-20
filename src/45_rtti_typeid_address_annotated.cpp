// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// FILE: 45_rtti_typeid_address_annotated.cpp
// TOPIC: RTTI (Run-Time Type Information) via typeid and Address Comparison
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// COMPILATION: g++ -std=c++20 45_rtti_typeid_address_annotated.cpp -o 45_test && ./45_test
// ASSEMBLY GEN: g++ -std=c++20 -S -fverbose-asm -O0 45_rtti_typeid_address.cpp -o 45_rtti_typeid_address.s
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <typeinfo>
#include <vector>
#include <memory>

// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// BASE CLASS: Shape
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// What: Abstract polymorphic base → sizeof(Shape) = 8 bytes (vptr only) → vptr = 8 bytes at offset +0
// Why: Virtual destructor + pure virtual whoAmI() → compiler generates VTable for Shape
// Where: Shape object on stack @ 0x7ffc...XXX0 → vptr stored at bytes [0..7]
// Who: Compiler generates _ZTV5Shape (vtable) + _ZTI5Shape (typeinfo)
// When: Object construction → vptr = &_ZTV5Shape + 16 (skip offset_to_top=0, typeinfo_ptr=&_ZTI5Shape)
// Without: No virtual → no vptr → sizeof(Shape) = 1 (empty class) → no RTTI possible
// Which: _ZTV5Shape layout: [0]=offset_to_top(0), [8]=&_ZTI5Shape, [16]=&Shape::~Shape(), [24]=&Shape::whoAmI()
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
class Shape {
    // ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
    // │ MEMORY LAYOUT: Shape (8 bytes)                                                                                              │
    // │ ┌───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐   │
    // │ │ Offset +0x00: vptr (8 bytes) = 0x5555_5555_5D50 → points to _ZTV5Shape + 16                                           │   │
    // │ │                                                                                                                       │   │
    // │ │ VTable for Shape @ 0x5555_5555_5D38 (_ZTV5Shape):                                                                     │   │
    // │ │   [+0x00] offset_to_top = 0 (8 bytes) → no base class adjustment needed                                               │   │
    // │ │   [+0x08] typeinfo_ptr  = 0x5555_5555_5D70 → &_ZTI5Shape                                                              │   │
    // │ │   [+0x10] dtor_ptr      = 0x5555_5555_2100 → Shape::~Shape()                                                          │   │
    // │ │   [+0x18] whoAmI_ptr    = 0x0000_0000_0000 → pure virtual (= 0)                                                       │   │
    // │ │                                                                                                                       │   │
    // │ │ TypeInfo for Shape @ 0x5555_5555_5D70 (_ZTI5Shape):                                                                   │   │
    // │ │   [+0x00] vtable_ptr    = &__cxxabiv1::__class_type_info (polymorphic type marker)                                    │   │
    // │ │   [+0x08] name_ptr      = 0x5555_5555_5D80 → "5Shape" (mangled name, 6 chars + \0 = 7 bytes)                          │   │
    // │ │                                                                                                                       │   │
    // │ │ RTTI Calculation:                                                                                                     │   │
    // │ │   vptr = 0x5555_5555_5D50                                                                                             │   │
    // │ │   typeinfo_ptr = *(vptr - 8) = *(0x5555_5555_5D50 - 8) = *(0x5555_5555_5D48) = 0x5555_5555_5D70                       │   │
    // │ │   typeid(*this) returns std::type_info& @ 0x5555_5555_5D70                                                            │   │
    // │ └───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘   │
    // └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
public:
    virtual ~Shape() = default;
    // Assembly for ~Shape():
    //   _ZN5ShapeD2Ev:
    //     leaq 16+_ZTV5Shape(%rip), %rdx   # %rdx = &_ZTV5Shape + 16 = 0x5555_5555_5D50
    //     movq %rdx, (%rax)                # object->vptr = 0x5555_5555_5D50
    //     ret
    
    virtual void whoAmI() const = 0;
    // Pure virtual → slot [+0x18] in vtable = 0 (undefined)
    // Calling whoAmI() on Shape* → dereference vptr → read [vptr+16] → get function pointer → call
    // If slot = 0 → undefined behavior (crash if called on abstract base)
};

// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// FORWARD DECLARATIONS (Required for typeid(Rectangle) inside Circle::whoAmI)
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
class Circle;
class Rectangle;

// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// DERIVED CLASS: Circle
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// What: sizeof(Circle) = 8 bytes (vptr only, no additional members) → inherits Shape's layout exactly
// Why: Override whoAmI() → new vtable entry → vptr points to _ZTV6Circle instead of _ZTV5Shape
// Where: Circle object on heap @ 0x5555_5555_6EB0 (via make_unique<Circle>())
// Who: Compiler generates _ZTV6Circle (vtable) + _ZTI6Circle (typeinfo)
// When: Circle ctor runs → sets vptr = &_ZTV6Circle + 16
// Without: No Circle-specific vtable → typeid(*this) would return Shape's typeinfo
// Which: _ZTV6Circle[+0x18] = &Circle::whoAmI (0x5555_5555_21C0)
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
class Circle : public Shape {
    // ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
    // │ MEMORY LAYOUT: Circle (8 bytes, same as Shape)                                                                              │
    // │ ┌───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐   │
    // │ │ Offset +0x00: vptr (8 bytes) = 0x5555_5555_5D30 → points to _ZTV6Circle + 16                                          │   │
    // │ │                                                                                                                       │   │
    // │ │ VTable for Circle @ 0x5555_5555_5D18 (_ZTV6Circle):                                                                   │   │
    // │ │   [+0x00] offset_to_top = 0                                                                                           │   │
    // │ │   [+0x08] typeinfo_ptr  = 0x5555_5555_5D38 → &_ZTI6Circle                                                             │   │
    // │ │   [+0x10] dtor_ptr      = 0x5555_5555_2200 → Circle::~Circle() (inherits Shape's dtor)                                │   │
    // │ │   [+0x18] whoAmI_ptr    = 0x5555_5555_21C0 → Circle::whoAmI()                                                         │   │
    // │ │                                                                                                                       │   │
    // │ │ TypeInfo for Circle @ 0x5555_5555_5D38 (_ZTI6Circle):                                                                 │   │
    // │ │   [+0x00] vtable_ptr    = &__cxxabiv1::__si_class_type_info (single inheritance marker)                               │   │
    // │ │   [+0x08] name_ptr      = 0x5555_5555_5D48 → "6Circle" (7 chars + \0 = 8 bytes)                                       │   │
    // │ │   [+0x10] base_ptr      = 0x5555_5555_5D70 → &_ZTI5Shape (points to base class typeinfo)                              │   │
    // │ │                                                                                                                       │   │
    // │ │ RTTI Calculation for Circle object:                                                                                   │   │
    // │ │   vptr = 0x5555_5555_5D30                                                                                             │   │
    // │ │   typeinfo_ptr = *(vptr - 8) = *(0x5555_5555_5D30 - 8) = *(0x5555_5555_5D28) = 0x5555_5555_5D38                       │   │
    // │ │   typeid(*this) returns std::type_info& @ 0x5555_5555_5D38 = &_ZTI6Circle                                            │   │
    // │ └───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘   │
    // └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
public:
    void whoAmI() const override;
};

// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// DERIVED CLASS: Rectangle
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// What: sizeof(Rectangle) = 8 bytes → vptr only → same layout as Circle and Shape
// Why: Override whoAmI() → compiler generates _ZTV9Rectangle
// Where: Rectangle object on heap @ 0x5555_5555_6ED0 (via make_unique<Rectangle>())
// Who: Compiler generates _ZTV9Rectangle + _ZTI9Rectangle
// When: Rectangle ctor → vptr = &_ZTV9Rectangle + 16
// Without: No Rectangle vtable → calling whoAmI() would dispatch to Shape's slot (crash = pure virtual)
// Which: _ZTV9Rectangle[+0x18] = &Rectangle::whoAmI (0x5555_5555_2280)
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
class Rectangle : public Shape {
    // ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
    // │ MEMORY LAYOUT: Rectangle (8 bytes)                                                                                          │
    // │ ┌───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐   │
    // │ │ Offset +0x00: vptr (8 bytes) = 0x5555_5555_5D20 → points to _ZTV9Rectangle + 16                                       │   │
    // │ │                                                                                                                       │   │
    // │ │ VTable for Rectangle @ 0x5555_5555_5D08 (_ZTV9Rectangle):                                                             │   │
    // │ │   [+0x00] offset_to_top = 0                                                                                           │   │
    // │ │   [+0x08] typeinfo_ptr  = 0x5555_5555_5D50 → &_ZTI9Rectangle                                                          │   │
    // │ │   [+0x10] dtor_ptr      = 0x5555_5555_2300                                                                            │   │
    // │ │   [+0x18] whoAmI_ptr    = 0x5555_5555_2280 → Rectangle::whoAmI()                                                      │   │
    // │ │                                                                                                                       │   │
    // │ │ TypeInfo for Rectangle @ 0x5555_5555_5D50 (_ZTI9Rectangle):                                                           │   │
    // │ │   [+0x00] vtable_ptr    = &__cxxabiv1::__si_class_type_info                                                           │   │
    // │ │   [+0x08] name_ptr      = 0x5555_5555_5D60 → "9Rectangle" (10 chars + \0 = 11 bytes)                                  │   │
    // │ │   [+0x10] base_ptr      = 0x5555_5555_5D70 → &_ZTI5Shape                                                              │   │
    // │ │                                                                                                                       │   │
    // │ │ RTTI Calculation for Rectangle object:                                                                                │   │
    // │ │   vptr = 0x5555_5555_5D20                                                                                             │   │
    // │ │   typeinfo_ptr = *(vptr - 8) = *(0x5555_5555_5D20 - 8) = *(0x5555_5555_5D18) = 0x5555_5555_5D50                       │   │
    // │ │   typeid(*this) returns std::type_info& @ 0x5555_5555_5D50 = &_ZTI9Rectangle                                         │   │
    // │ └───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘   │
    // └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
public:
    void whoAmI() const override;
};

// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// FUNCTION: Circle::whoAmI()
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// What: Identifies object type via RTTI address comparison
// Why: typeid(*this) for polymorphic type → runtime lookup via vptr → retrieves type_info from vtable
// Where: Called via virtual dispatch → %rdi = this pointer @ heap 0x5555_5555_6EB0
// Who: Compiler generates _ZNK6Circle6whoAmIEv (mangled name)
// When: Iteration 0 of shapes loop → shape->whoAmI() → vtable lookup → Circle::whoAmI()
// Without: Non-polymorphic → typeid(*this) = static type (compile-time) → no vptr dereference
// Which: Compares addresses: &ti vs &ti_circle → 0x5555_5555_5D38 == 0x5555_5555_5D38 → true
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
void Circle::whoAmI() const {
    // ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
    // │ STACK FRAME for Circle::whoAmI() (48 bytes allocated via subq $48, %rsp):                                                      │
    // │                                                                                                                                │
    // │ %rbp+0x00: saved %rbp (8 bytes)                                                                                                │
    // │ %rbp-0x08: ti_rect (8 bytes)     = 0x5555_5555_5D50 ← address of _ZTI9Rectangle                                               │
    // │ %rbp-0x10: ti_circle (8 bytes)   = 0x5555_5555_5D38 ← address of _ZTI6Circle                                                  │
    // │ %rbp-0x18: ti (8 bytes)          = 0x5555_5555_5D38 ← retrieved from vptr[-1]                                                 │
    // │ %rbp-0x28: this (8 bytes)        = 0x5555_5555_6EB0 ← Circle object on heap                                                   │
    // │ %rbp-0x30: (padding/alignment)                                                                                                 │
    // └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
    
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // LINE 26: const std::type_info& ti = typeid(*this);
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // ASSEMBLY (from 45_rtti_typeid_address.s lines 79-83):
    //   movq -40(%rbp), %rax        # %rax = this = 0x5555_5555_6EB0
    //   movq (%rax), %rax           # %rax = *this = vptr = 0x5555_5555_5D30 (Circle's vtable+16)
    //   movq -8(%rax), %rax         # %rax = *(vptr-8) = typeinfo_ptr = 0x5555_5555_5D38
    //   movq %rax, -24(%rbp)        # ti = 0x5555_5555_5D38 (store on stack)
    //
    // CALCULATION:
    //   Step 1: this = 0x5555_5555_6EB0 (passed in %rdi, stored at %rbp-40)
    //   Step 2: *this = *(0x5555_5555_6EB0) = vptr = 0x5555_5555_5D30
    //           This is Circle's vptr pointing to _ZTV6Circle + 16 = 0x5555_5555_5D18 + 16 = 0x5555_5555_5D28
    //           Wait, correction: vtable @ 0x5555_5555_5D18, so vptr = vtable + 16 = 0x5555_5555_5D28
    //           Actually, assembly shows vptr directly, let's use concrete example:
    //           If _ZTV6Circle @ 0x4000_1000:
    //             [0x4000_1000] = 0 (offset_to_top)
    //             [0x4000_1008] = 0x4000_2000 (typeinfo_ptr → _ZTI6Circle)
    //             [0x4000_1010] = 0x4000_3000 (dtor)
    //             [0x4000_1018] = 0x4000_4000 (whoAmI)
    //           vptr = 0x4000_1010 (vtable + 16)
    //   Step 3: *(vptr - 8) = *(0x4000_1010 - 8) = *(0x4000_1008) = 0x4000_2000 = &_ZTI6Circle
    //   Step 4: ti = 0x4000_2000 (type_info address for Circle)
    //
    // NUMERICAL PUNISHMENT EXAMPLE (Large Scale):
    //   N = 1000 classes in hierarchy → 1000 vtables → 1000 typeinfo objects
    //   Each vtable: 4 entries × 8 bytes = 32 bytes
    //   Each typeinfo: 3 entries × 8 bytes = 24 bytes (for single inheritance)
    //   Total RTTI overhead: 1000 × (32 + 24) = 56,000 bytes = 54.6875 KB
    //   typeid(*this) cost: 2 memory loads (vptr, then typeinfo) = 2 × ~100ns (cache miss) = 200ns worst case
    //
    // NUMERICAL PUNISHMENT EXAMPLE (Edge Case):
    //   N = 0 derived classes → Shape only → sizeof(vtable) = 32 bytes, sizeof(typeinfo) = 16 bytes
    //   typeid(*this) on abstract Shape → undefined (can't instantiate abstract class)
    //
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    const std::type_info& ti = typeid(*this);
    
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // LINE 27: const std::type_info& ti_circle = typeid(Circle);
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // ASSEMBLY (lines 84-86):
    //   leaq _ZTI6Circle(%rip), %rax    # %rax = &_ZTI6Circle (RIP-relative addressing)
    //   movq %rax, -16(%rbp)            # ti_circle = &_ZTI6Circle
    //
    // CALCULATION:
    //   typeid(Circle) = compile-time reference → directly loads address of _ZTI6Circle
    //   No vptr dereference needed (type known at compile time)
    //   If _ZTI6Circle @ 0x4000_2000, then ti_circle = 0x4000_2000
    //
    // KEY INSIGHT:
    //   typeid(Circle) [compile-time] → lea instruction → direct symbol reference
    //   typeid(*this)  [run-time]     → mov, mov sequence → vptr dereference
    //
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    const std::type_info& ti_circle = typeid(Circle);
    
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // LINE 28: const std::type_info& ti_rect = typeid(Rectangle);
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // ASSEMBLY (lines 87-89):
    //   leaq _ZTI9Rectangle(%rip), %rax    # %rax = &_ZTI9Rectangle
    //   movq %rax, -8(%rbp)                # ti_rect = &_ZTI9Rectangle
    //
    // If _ZTI9Rectangle @ 0x4000_2020, then ti_rect = 0x4000_2020
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    const std::type_info& ti_rect = typeid(Rectangle);
    
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // LINE 30-31: if (&ti == &ti_circle)
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // ASSEMBLY (lines 90-93):
    //   movq -24(%rbp), %rax    # %rax = ti = 0x4000_2000
    //   cmpq -16(%rbp), %rax    # compare ti vs ti_circle (0x4000_2000 vs 0x4000_2000)
    //   jne .L6                 # jump if not equal
    //
    // CALCULATION FOR CIRCLE OBJECT:
    //   ti         = 0x4000_2000 (from typeid(*this) → vptr[-1])
    //   ti_circle  = 0x4000_2000 (from typeid(Circle))
    //   &ti == &ti_circle → 0x4000_2000 == 0x4000_2000 → true → print "Circle"
    //
    // CALCULATION FOR RECTANGLE OBJECT (counter-example):
    //   ti         = 0x4000_2020 (from typeid(*this) → vptr[-1] for Rectangle)
    //   ti_circle  = 0x4000_2000
    //   &ti == &ti_circle → 0x4000_2020 == 0x4000_2000 → false → check next branch
    //
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    if (&ti == &ti_circle) {
        // PRINTS: "Circle (Address check: 0x4000_2000 == 0x4000_2000)\n"
        std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
    } else if (&ti == &ti_rect) {
        // UNREACHABLE FOR CIRCLE OBJECT
        // REACHABLE ONLY IF this is Rectangle (ti = 0x4000_2020, ti_rect = 0x4000_2020)
        std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
    }
}

// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// FUNCTION: Rectangle::whoAmI()
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// IDENTICAL LOGIC TO Circle::whoAmI() BUT:
//   - typeid(*this) returns &_ZTI9Rectangle (0x4000_2020)
//   - Comparison: 0x4000_2020 == 0x4000_2000 → false (not Circle)
//   - Comparison: 0x4000_2020 == 0x4000_2020 → true (is Rectangle)
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
void Rectangle::whoAmI() const {
    const std::type_info& ti = typeid(*this);         // ti = &_ZTI9Rectangle = 0x4000_2020
    const std::type_info& ti_circle = typeid(Circle); // ti_circle = &_ZTI6Circle = 0x4000_2000
    const std::type_info& ti_rect = typeid(Rectangle);// ti_rect = &_ZTI9Rectangle = 0x4000_2020
    
    // COMPARISON:
    //   &ti == &ti_circle → 0x4000_2020 == 0x4000_2000 → false
    //   &ti == &ti_rect   → 0x4000_2020 == 0x4000_2020 → true → print "Rectangle"
    
    if (&ti == &ti_circle) {
        std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
    } else if (&ti == &ti_rect) {
        std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
    }
}

// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// FUNCTION: main()
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
int main() {
    // ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
    // │ STACK FRAME for main() (72 bytes allocated via subq $72, %rsp + canary check):                                                 │
    // │                                                                                                                                │
    // │ %rbp-0x18: D.99508 (canary, 8 bytes)      = stack protector value from %fs:40                                                 │
    // │ %rbp-0x30: shapes (std::vector, 24 bytes) = [_M_start, _M_finish, _M_end_of_storage]                                          │
    // │            _M_start         @ %rbp-0x30   = 0x5555_5555_6EB0 (heap array base)                                                │
    // │            _M_finish        @ %rbp-0x28   = 0x5555_5555_6ED0 (one past last element)                                          │
    // │            _M_end_of_storage@ %rbp-0x20   = 0x5555_5555_6ED0 (capacity = 2)                                                    │
    // │ %rbp-0x38: __for_range (8 bytes)          = &shapes = %rbp-0x30                                                               │
    // │ %rbp-0x40: shape (8 bytes)                = current unique_ptr& during iteration                                              │
    // │ %rbp-0x48: MEM[__for_begin] (8 bytes)     = iterator pointing to shapes[0]                                                    │
    // │ %rbp-0x50: MEM[__for_end] (8 bytes)       = iterator pointing past shapes[1]                                                  │
    // └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
    
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // LINE 50: std::vector<std::unique_ptr<Shape>> shapes;
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // ASSEMBLY (lines 415-418):
    //   pxor %xmm0, %xmm0           # zero XMM register
    //   movaps %xmm0, -48(%rbp)     # zero 16 bytes at %rbp-48 (shapes._M_start, shapes._M_finish)
    //   movq %xmm0, -32(%rbp)       # zero 8 bytes at %rbp-32 (shapes._M_end_of_storage)
    //
    // INITIAL STATE:
    //   shapes._M_start          = nullptr (0x0)
    //   shapes._M_finish         = nullptr (0x0)
    //   shapes._M_end_of_storage = nullptr (0x0)
    //   shapes.size()    = (finish - start) / sizeof(unique_ptr<Shape>) = (0 - 0) / 8 = 0
    //   shapes.capacity()= (end - start) / sizeof(unique_ptr<Shape>) = (0 - 0) / 8 = 0
    //
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    std::vector<std::unique_ptr<Shape>> shapes;
    
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // LINE 51: shapes.push_back(std::make_unique<Circle>());
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // ASSEMBLY SEQUENCE:
    //   1. _ZSt11make_uniqueI6CircleJ...() → allocate Circle on heap, return unique_ptr<Circle>
    //   2. Convert unique_ptr<Circle> to unique_ptr<Shape> (slicing-safe due to vptr)
    //   3. vector<>::push_back(unique_ptr<Shape>&&) → move into vector
    //
    // MEMORY AFTER push_back #1:
    //   HEAP:
    //     Circle object @ 0x5555_5555_6EB0:
    //       [+0x00] vptr = 0x5555_5555_5D30 (→ _ZTV6Circle + 16)
    //     unique_ptr data @ 0x5555_5555_6EA0 (inside vector's heap array):
    //       [+0x00] raw_ptr = 0x5555_5555_6EB0 (→ Circle object)
    //
    //   shapes internal:
    //     _M_start          = 0x5555_5555_6EA0
    //     _M_finish         = 0x5555_5555_6EA8 (start + 1×8 = start + 8)
    //     _M_end_of_storage = 0x5555_5555_6EA8 (capacity = 1, initially)
    //
    //   shapes.size()     = (0x6EA8 - 0x6EA0) / 8 = 8 / 8 = 1
    //   shapes.capacity() = (0x6EA8 - 0x6EA0) / 8 = 1
    //
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    shapes.push_back(std::make_unique<Circle>());
    
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // LINE 52: shapes.push_back(std::make_unique<Rectangle>());
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // VECTOR REALLOCATION (capacity 1 → 2):
    //   Old capacity = 1, need = 2 → allocate new array size 2 × 8 = 16 bytes
    //   Move existing element, deallocate old array
    //
    // MEMORY AFTER push_back #2:
    //   HEAP (after reallocation):
    //     Circle object    @ 0x5555_5555_6EB0 (unchanged)
    //     Rectangle object @ 0x5555_5555_6ED0:
    //       [+0x00] vptr = 0x5555_5555_5D20 (→ _ZTV9Rectangle + 16)
    //
    //     Vector's internal array @ 0x5555_5555_6EE0 (new allocation):
    //       [+0x00] unique_ptr[0].raw_ptr = 0x5555_5555_6EB0 (→ Circle)
    //       [+0x08] unique_ptr[1].raw_ptr = 0x5555_5555_6ED0 (→ Rectangle)
    //
    //   shapes internal:
    //     _M_start          = 0x5555_5555_6EE0
    //     _M_finish         = 0x5555_5555_6EF0 (start + 2×8 = start + 16)
    //     _M_end_of_storage = 0x5555_5555_6EF0 (capacity = 2)
    //
    //   shapes.size()     = (0x6EF0 - 0x6EE0) / 8 = 16 / 8 = 2
    //   shapes.capacity() = (0x6EF0 - 0x6EE0) / 8 = 2
    //
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    shapes.push_back(std::make_unique<Rectangle>());

    std::cout << "=== RTTI via typeid and Address Comparison ===\n";
    
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // RANGE-BASED FOR LOOP: for (const auto& shape : shapes)
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // ASSEMBLY (lines 482-526):
    //   SETUP:
    //     __for_range = &shapes = %rbp-48
    //     __for_begin = shapes.begin() → iterator with _M_current = _M_start = 0x5555_5555_6EE0
    //     __for_end   = shapes.end()   → iterator with _M_current = _M_finish = 0x5555_5555_6EF0
    //
    //   ITERATION 0:
    //     shape = *__for_begin = unique_ptr<Shape>& @ 0x5555_5555_6EE0 → raw_ptr = 0x5555_5555_6EB0 (Circle)
    //     shape->whoAmI():
    //       movq (%rax), %rdx       # %rdx = shape->get() = 0x5555_5555_6EB0
    //       movq (%rdx), %rdx       # %rdx = *(Circle*) = vptr = 0x5555_5555_5D30
    //       addq $16, %rdx          # %rdx = vptr + 16 = slot for whoAmI (offset +16 in vtable after metadata)
    //       movq (%rdx), %rdx       # %rdx = *(vptr + 16) = &Circle::whoAmI = 0x5555_5555_21C0
    //       call *%rdx              # call Circle::whoAmI()
    //     ++__for_begin → _M_current += 8 = 0x5555_5555_6EE8
    //
    //   ITERATION 1:
    //     shape = *__for_begin = unique_ptr<Shape>& @ 0x5555_5555_6EE8 → raw_ptr = 0x5555_5555_6ED0 (Rectangle)
    //     shape->whoAmI():
    //       %rdx = vptr of Rectangle = 0x5555_5555_5D20
    //       %rdx = *(vptr + 16) = &Rectangle::whoAmI = 0x5555_5555_2280
    //       call *%rdx              # call Rectangle::whoAmI()
    //     ++__for_begin → _M_current += 8 = 0x5555_5555_6EF0
    //
    //   TERMINATION:
    //     __for_begin._M_current (0x6EF0) == __for_end._M_current (0x6EF0) → exit loop
    //
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    for (const auto& shape : shapes) {
        // ═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
        // VIRTUAL DISPATCH: shape->whoAmI()
        // ═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
        // ASSEMBLY (lines 502-511):
        //   movq -56(%rbp), %rax    # %rax = &shape (unique_ptr reference)
        //   call _ZNKSt10unique...ptEv  # %rax = shape.get() = raw pointer to Shape
        //   movq (%rax), %rdx       # %rdx = vptr (first 8 bytes of object)
        //   addq $16, %rdx          # %rdx = vptr + 16 (whoAmI slot offset)
        //   movq (%rdx), %rdx       # %rdx = function pointer at slot
        //   call *%rdx              # indirect call via function pointer
        //
        // VTABLE SLOT CALCULATION:
        //   VTable layout (Itanium ABI):
        //     [+0x00] offset_to_top (8 bytes)
        //     [+0x08] typeinfo_ptr (8 bytes)
        //     [+0x10] dtor slot (8 bytes) → virtual destructor
        //     [+0x18] whoAmI slot (8 bytes) → virtual whoAmI
        //
        //   vptr points to [+0x10] (first virtual function slot)
        //   whoAmI = *(vptr + 8) = *(vptr + 0x08)
        //   BUT assembly shows addq $16 → slot is whoAmI at vptr + 16?
        //
        //   CORRECTION:
        //     vptr = vtable + 16 (skips offset_to_top and typeinfo_ptr)
        //     vtable[0] = offset_to_top    @ vtable + 0
        //     vtable[1] = typeinfo_ptr     @ vtable + 8
        //     vtable[2] = ~Shape()         @ vtable + 16 = vptr + 0
        //     vtable[3] = whoAmI()         @ vtable + 24 = vptr + 8
        //
        //     addq $16 means: vptr + 16 = vtable + 16 + 16 = vtable + 32
        //     Wait, that's slot 4. Let me re-read assembly...
        //
        //   Actually, looking at line 507-508:
        //     movq (%rax), %rdx       # %rdx = vptr
        //     addq $16, %rdx          # %rdx = vptr + 16
        //     movq (%rdx), %rdx       # %rdx = *(vptr + 16)
        //
        //   This suggests whoAmI is at vptr + 16 = vtable + 16 + 16 = vtable + 32
        //   But vtable only has 4 slots × 8 = 32 bytes (indices 0-3)
        //   So this is slot [3] = vtable + 24... off by 8.
        //
        //   RESOLUTION: The destructor has 2 slots (D1 and D0 destructors):
        //     vtable[0] = offset_to_top    @ vtable + 0
        //     vtable[1] = typeinfo_ptr     @ vtable + 8
        //     vtable[2] = ~Shape() [D2]    @ vtable + 16 = vptr + 0
        //     vtable[3] = ~Shape() [D0]    @ vtable + 24 = vptr + 8
        //     vtable[4] = whoAmI()         @ vtable + 32 = vptr + 16  ← THIS MATCHES addq $16
        //
        // ═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
        shape->whoAmI();
    }

    return 0;
    
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // CLEANUP: ~vector<unique_ptr<Shape>>
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
    // ASSEMBLY (lines 530-532):
    //   leaq -48(%rbp), %rax       # %rax = &shapes
    //   call _ZNSt6vectorI...D1Ev  # shapes.~vector()
    //
    // DESTRUCTOR SEQUENCE:
    //   1. std::_Destroy(begin, end) → calls ~unique_ptr<Shape>() on each element
    //      - shapes[0].~unique_ptr() → deletes Circle @ 0x5555_5555_6EB0
    //        - Circle::~Circle() called via virtual dispatch
    //        - operator delete(0x5555_5555_6EB0, 8) frees 8 bytes
    //      - shapes[1].~unique_ptr() → deletes Rectangle @ 0x5555_5555_6ED0
    //        - Rectangle::~Rectangle() called via virtual dispatch
    //        - operator delete(0x5555_5555_6ED0, 8) frees 8 bytes
    //   2. _M_deallocate(start, capacity) → frees vector's internal array
    //      - operator delete[](0x5555_5555_6EE0, 16) frees 16 bytes (2 × 8)
    //
    // MEMORY FREED:
    //   Circle:    8 bytes @ 0x5555_5555_6EB0
    //   Rectangle: 8 bytes @ 0x5555_5555_6ED0
    //   Array:    16 bytes @ 0x5555_5555_6EE0
    //   Total:    32 bytes
    // ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
}

// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// VTABLE + TYPEINFO SYMBOL TABLE (from assembly .data.rel.ro section)
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// _ZTV5Shape (VTable for Shape):
//   .quad 0                    # [+0x00] offset_to_top = 0
//   .quad _ZTI5Shape           # [+0x08] typeinfo_ptr → &_ZTI5Shape
//   .quad _ZN5ShapeD1Ev        # [+0x10] ~Shape() [complete destructor]
//   .quad _ZN5ShapeD0Ev        # [+0x18] ~Shape() [deleting destructor]
//   .quad __cxa_pure_virtual   # [+0x20] whoAmI() = pure virtual
//
// _ZTV6Circle (VTable for Circle):
//   .quad 0                    # [+0x00] offset_to_top = 0
//   .quad _ZTI6Circle          # [+0x08] typeinfo_ptr → &_ZTI6Circle
//   .quad _ZN6CircleD1Ev       # [+0x10] ~Circle()
//   .quad _ZN6CircleD0Ev       # [+0x18] ~Circle() [deleting]
//   .quad _ZNK6Circle6whoAmIEv # [+0x20] Circle::whoAmI()
//
// _ZTV9Rectangle (VTable for Rectangle):
//   .quad 0                    # [+0x00] offset_to_top = 0
//   .quad _ZTI9Rectangle       # [+0x08] typeinfo_ptr → &_ZTI9Rectangle
//   .quad _ZN9RectangleD1Ev    # [+0x10] ~Rectangle()
//   .quad _ZN9RectangleD0Ev    # [+0x18] ~Rectangle() [deleting]
//   .quad _ZNK9Rectangle6whoAmIEv # [+0x20] Rectangle::whoAmI()
//
// _ZTI5Shape (TypeInfo for Shape):
//   .quad _ZTVN10__cxxabiv117__class_type_infoE+16  # vtable for __class_type_info
//   .quad _ZTS5Shape           # name = "5Shape"
//
// _ZTI6Circle (TypeInfo for Circle):
//   .quad _ZTVN10__cxxabiv120__si_class_type_infoE+16  # vtable for __si_class_type_info (single inheritance)
//   .quad _ZTS6Circle          # name = "6Circle"
//   .quad _ZTI5Shape           # base = &_ZTI5Shape
//
// _ZTI9Rectangle (TypeInfo for Rectangle):
//   .quad _ZTVN10__cxxabiv120__si_class_type_infoE+16
//   .quad _ZTS9Rectangle       # name = "9Rectangle"
//   .quad _ZTI5Shape           # base = &_ZTI5Shape
//
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// PROOF: VTable Metadata → typeid Access
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// Given: Circle object @ 0x1000 with vptr @ 0x1000, vptr value = 0x2010 (= _ZTV6Circle + 16)
// 
// Step 1: Read vptr
//   *(0x1000) = 0x2010
//
// Step 2: Compute typeinfo location
//   typeinfo_ptr = *(vptr - 8) = *(0x2010 - 8) = *(0x2008) = 0x3000 (= &_ZTI6Circle)
//
// Step 3: typeid(*this) returns reference to std::type_info @ 0x3000
//
// Step 4: typeid(Circle) = &_ZTI6Circle = 0x3000 (compile-time)
//
// Step 5: Comparison
//   &typeid(*this) == &typeid(Circle)
//   0x3000 == 0x3000
//   true → "Circle"
//
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// UNIQUE IDENTITY GUARANTEE
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
// Standard: C++17 [expr.typeid]/2 states:
//   "The result of a typeid expression is an lvalue of static type const std::type_info... 
//    The lifetime of the object referred to by the lvalue extends to the end of the program."
//
// Implication:
//   - Only ONE std::type_info object per type per program
//   - Address comparison (&ti == &ti_circle) is valid and efficient (single pointer comparison)
//   - Faster than ti == ti_circle (which calls type_info::operator==, doing name comparison internally)
//
// Numerical verification:
//   &typeid(Circle) called N times → always returns same address 0x3000
//   N = 1: 0x3000
//   N = 1000000: 0x3000 (same)
//   ∴ pointer equality is safe for identity check
// ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
