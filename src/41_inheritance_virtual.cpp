// 41_inheritance_virtual.cpp
// ROAST-DRIVEN DEVELOPMENT: You will not write code until you draw bytes.

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <vector>

// =============================================================================
// STEP 001: ROAST YOUR CODE BEFORE YOU WRITE IT
// =============================================================================
// ROAST: You think "virtual does nothing" because you never checked the
// assembly. You never printed raw bytes. You never watched the vptr get loaded
// at runtime. You just wrote `virtual` because the textbook said so. That's
// sloppy. Virtual is a memory layout hack that inserts a hidden function
// pointer table. Without it, you get a compile error. Without it, you cannot
// distinguish Circle from Rectangle at runtime. Period.

// =============================================================================
// STEP 002: DRAW THE BASE CLASS MEMORY LAYOUT (NO DERIVED CLASSES YET)
// =============================================================================
// DIAGRAM: Stack variable `base_ptr` declared as `ShapeBase* base_ptr;`
// Address: 0x7ffc_c000 (stack top, hypothetical)
// Bytes before initialization: cd cd cd cd cd cd cd cd (garbage from debug
// fill) Why: Uninitialized pointer contains garbage → dereference → SEGFAULT
// at 0xcdcdcdcdcdcdcdcd → signal 11 → program death. This is why you must
// initialize.

// =============================================================================
// STEP 003: DRAW THE BASE CLASS VTABLE LAYOUT (READ-ONLY DATA SECTION)
// =============================================================================
// Address: 0x4000_1000 (code segment, .rodata)
// +--------+----------------+------------------+------------------------+
// | Offset | Bytes (hex)    | Symbol           | Why entry exists       |
// +--------+----------------+------------------+------------------------+
// | 0x00   | 00 00 00 00    | top_offset       | For multiple inherit   |
// | 0x08   | xx xx xx xx    | typeinfo ptr     | RTTI for dynamic_cast  |
// | 0x10   | 00 00 00 00    | left_of (slot 0) | Pure virtual = 0       |
// | 0x18   | 00 00 00 00    | whoAmI (slot 1)  | Pure virtual = 0       |
// | 0x20   | xx xx xx xx    | ~ShapeBase       | Destructor address     |
// +--------+----------------+------------------+------------------------+
// Size: 40 bytes. vtable slots 0,1 are NULL because `= 0` → derived must fill.

// =============================================================================
// STEP 004: NOW YOU DEFINE ShapeBase
// =============================================================================
// TODO: Before writing, answer:
// Q1: sizeof(ShapeBase) = ? (only vptr, no data members)
// Q2: How many vtable slots for: left_of, whoAmI, destructor?
// Q3: What is slot index of left_of? (answer: 0)
// Q4: What is slot index of whoAmI? (answer: 1)

struct Point {
    double x;
    double y;
};
// sizeof(Point) = 16, alignof = 8

class ShapeBase {
   public:
    // Pure virtual: slot 0 in vtable
    virtual bool left_of(double x) const = 0;

    // Pure virtual: slot 1 in vtable
    virtual void whoAmI() const = 0;

    // Virtual destructor: slot 2 (or separate dtor vtable)
    // WHY VIRTUAL: Without this, `delete base_ptr` where base_ptr points to
    // Circle will NOT call ~Circle(), only ~ShapeBase(). Memory leak.
    virtual ~ShapeBase() = default;
};
// sizeof(ShapeBase) = 8 (vptr only)

// =============================================================================
// STEP 005: DRAW CIRCLE VTABLE AND OBJECT MEMORY
// =============================================================================
// Circle vtable at 0x4000_1080:
// +--------+----------------+------------------------+
// | Slot 0 | 0x4000_10a0    | &Circle::left_of       |
// | Slot 1 | 0x4000_10b0    | &Circle::whoAmI        |
// | Slot 2 | 0x4000_10c0    | &Circle::~Circle       |
// +--------+----------------+------------------------+
//
// Circle object at heap 0x5555_a020 (32 bytes):
// +--------+------------------+-------------------+-------------------+
// | Offset | Bytes            | Field             | Value             |
// +--------+------------------+-------------------+-------------------+
// | 0x00   | 80 10 00 40 ...  | vptr              | 0x4000_1080       |
// | 0x08   | 00 00 00 00 ...  | center.x          | 2.0 (IEEE754)     |
// | 0x10   | 00 00 00 00 ...  | center.y          | 3.0 (IEEE754)     |
// | 0x18   | 00 00 00 00 ...  | radius            | 1.5 (IEEE754)     |
// +--------+------------------+-------------------+-------------------+

class Circle final : public ShapeBase {
   public:
    Point center;
    double radius;

    Circle(Point c, double r) : center(c), radius(r) {}

    // Slot 0: left_of
    // LOGIC: Circle is "left of x" if its rightmost edge < x
    // rightmost edge = center.x + radius
    // Example: center.x=2.0, radius=1.5 → right edge = 3.5
    // left_of(3.0) → 3.5 < 3.0? → false
    // left_of(4.0) → 3.5 < 4.0? → true
    bool left_of(double x) const override { return center.x + radius < x; }

    // Slot 1: whoAmI
    void whoAmI() const override { std::cout << "Circle\n"; }
};
// sizeof(Circle) = 8 (vptr) + 16 (Point) + 8 (double) = 32

// =============================================================================
// STEP 006: DRAW RECTANGLE VTABLE AND OBJECT MEMORY
// =============================================================================
// Rectangle vtable at 0x4000_1100:
// +--------+----------------+------------------------+
// | Slot 0 | 0x4000_1120    | &Rectangle::left_of    |
// | Slot 1 | 0x4000_1130    | &Rectangle::whoAmI     |
// | Slot 2 | 0x4000_1140    | &Rectangle::~Rectangle |
// +--------+----------------+------------------------+
//
// Rectangle object at heap 0x5555_a050 (40 bytes):
// +--------+------------------+-------------------+-------------------+
// | Offset | Bytes            | Field             | Value             |
// +--------+------------------+-------------------+-------------------+
// | 0x00   | 00 11 00 40 ...  | vptr              | 0x4000_1100       |
// | 0x08   |                  | lower_left.x      | 0.0               |
// | 0x10   |                  | lower_left.y      | 0.0               |
// | 0x18   |                  | upper_right.x     | 4.0               |
// | 0x20   |                  | upper_right.y     | 5.0               |
// +--------+------------------+-------------------+-------------------+

class Rectangle final : public ShapeBase {
   public:
    Point lower_left;
    Point upper_right;

    Rectangle(Point ll, Point ur) : lower_left(ll), upper_right(ur) {}

    // Slot 0: left_of
    // LOGIC: Rectangle is "left of x" if ALL corners are left of x
    // Rightmost corner = upper_right.x
    // Example: ur.x=4.0, left_of(3.0) → 4.0 < 3.0? → false
    // Example: ur.x=4.0, left_of(5.0) → 4.0 < 5.0? → true
    bool left_of(double x) const override { return upper_right.x < x; }

    // Slot 1: whoAmI
    void whoAmI() const override { std::cout << "Rectangle\n"; }
};
// sizeof(Rectangle) = 8 (vptr) + 16 (Point) + 16 (Point) = 40

// =============================================================================
// STEP 007: DUMP RAW MEMORY TO VERIFY YOUR HAND CALCULATION
// =============================================================================
void dump_object(const void* ptr, size_t size, const char* label) {
    std::printf("--- %s at %p (%zu bytes) ---\n", label, ptr, size);
    const auto* bytes = static_cast<const uint8_t*>(ptr);
    for (size_t i = 0; i < size; i += 8) {
        std::printf("  +0x%02zx: ", i);
        for (size_t j = 0; j < 8 && i + j < size; ++j) {
            std::printf("%02x ", bytes[i + j]);
        }
        std::printf("\n");
    }
}

void dump_vptr(const ShapeBase* obj, const char* label) {
    // vptr is at offset 0 of object
    const void* vptr = *reinterpret_cast<void* const*>(obj);
    std::printf("[%s] vptr = %p\n", label, vptr);
}

// =============================================================================
// STEP 008: TRACE THE VIRTUAL CALL BY HAND
// =============================================================================
// Code: `ptr->left_of(3.0);` where ptr = 0x5555_a020 (Circle)
//
// Assembly (pseudo):
//   mov rax, [ptr]           ; rax = 0x5555_a020 (Circle address)
//   mov rcx, [rax]           ; rcx = *(Circle*) = vptr = 0x4000_1080
//   mov rdx, [rcx + 0]       ; left_of is slot 0 → rdx = 0x4000_10a0
//   call rdx                 ; call Circle::left_of with this=rax
//
// Inside Circle::left_of:
//   this = 0x5555_a020
//   center.x = *(double*)(this + 0x08) = 2.0
//   radius   = *(double*)(this + 0x18) = 1.5
//   right_edge = 2.0 + 1.5 = 3.5
//   return 3.5 < 3.0 → false
//
// YOU VERIFY: Run the code, print the result, compare to hand calculation.

// =============================================================================
// STEP 009: MAIN - YOU TRACE EVERY LINE BY HAND FIRST
// =============================================================================
int main() {
    // VERIFY SIZES BEFORE ANYTHING
    std::cout << "sizeof(ShapeBase) = " << sizeof(ShapeBase) << " (expect 8)\n";
    std::cout << "sizeof(Circle) = " << sizeof(Circle) << " (expect 32)\n";
    std::cout << "sizeof(Rectangle) = " << sizeof(Rectangle)
              << " (expect 40)\n\n";

    static_assert(sizeof(ShapeBase) == 8, "ShapeBase must be 8 bytes (vptr)");
    static_assert(sizeof(Circle) == 32, "Circle must be 32 bytes");
    static_assert(sizeof(Rectangle) == 40, "Rectangle must be 40 bytes");

    // TASK 004: Instantiate Circle
    // center = (2.0, 3.0), radius = 1.5
    // Heap address will be printed, compare to your assumed 0x5555_a020
    Circle* c = new Circle({2.0, 3.0}, 1.5);
    std::cout << "Circle allocated at: " << static_cast<void*>(c) << "\n";
    dump_object(c, sizeof(Circle), "Circle");
    dump_vptr(c, "Circle");

    // TASK 004: Instantiate Rectangle
    // lower_left = (0.0, 0.0), upper_right = (4.0, 5.0)
    Rectangle* r = new Rectangle({0.0, 0.0}, {4.0, 5.0});
    std::cout << "\nRectangle allocated at: " << static_cast<void*>(r) << "\n";
    dump_object(r, sizeof(Rectangle), "Rectangle");
    dump_vptr(r, "Rectangle");

    // VERIFY: Circle vptr != Rectangle vptr
    std::cout << "\nVptrs different? "
              << (*reinterpret_cast<void**>(c) != *reinterpret_cast<void**>(r)
                      ? "YES"
                      : "NO")
              << "\n";

    // TASK 005: Vector of base pointers
    std::vector<ShapeBase*> shapes;
    shapes.push_back(c);
    shapes.push_back(r);

    std::cout << "\nVector contents:\n";
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << "  shapes[" << i << "] = " << shapes[i] << "\n";
    }

    // TASK 006: Virtual dispatch left_of(3.0)
    // YOUR HAND CALCULATION:
    // Circle: center.x=2.0, radius=1.5 → right=3.5 → 3.5<3.0? → false
    // Rectangle: ur.x=4.0 → 4.0<3.0? → false
    std::cout << "\n--- left_of(3.0) test ---\n";
    double test_x = 3.0;
    for (size_t i = 0; i < shapes.size(); ++i) {
        ShapeBase* ptr = shapes[i];

        // TRACE: This is where vtable dispatch happens
        // mov rcx, [ptr]       ; load vptr
        // call [rcx + 0]       ; call slot 0 (left_of)
        bool result = ptr->left_of(test_x);

        std::cout << "shapes[" << i << "]->left_of(" << test_x
                  << ") = " << (result ? "true" : "false") << "\n";
    }

    // TASK 006: Virtual dispatch left_of(5.0)
    // YOUR HAND CALCULATION:
    // Circle: 3.5<5.0? → true
    // Rectangle: 4.0<5.0? → true
    std::cout << "\n--- left_of(5.0) test ---\n";
    test_x = 5.0;
    for (size_t i = 0; i < shapes.size(); ++i) {
        bool result = shapes[i]->left_of(test_x);
        std::cout << "shapes[" << i << "]->left_of(" << test_x
                  << ") = " << (result ? "true" : "false") << "\n";
    }

    // TASK: whoAmI dispatch
    std::cout << "\n--- whoAmI() test ---\n";
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << "shapes[" << i << "]->whoAmI() = ";
        shapes[i]->whoAmI();
    }

    // CLEANUP: Virtual destructor test
    // If ~ShapeBase was NOT virtual, this would only call ~ShapeBase
    // and Circle/Rectangle destructors would NOT run → leak if they had
    // resources
    std::cout << "\n--- Deleting via base pointer ---\n";
    for (auto* p : shapes) {
        std::cout << "delete " << p << "\n";
        delete p;
    }

    std::cout << "\nDone.\n";
    return 0;
}

// =============================================================================
// STEP 010: YOUR IMMEDIATE ACTION
// =============================================================================
// 1. Compile: g++ -std=c++17 -g 41_inheritance_virtual.cpp -o test
// 2. Run: ./test
// 3. Compare output to your hand calculations:
//    - sizeof values match?
//    - vptr addresses different for Circle vs Rectangle?
//    - left_of(3.0) returns false for both?
//    - left_of(5.0) returns true for both?
// 4. If ANY mismatch, your hand calculation was wrong. Find the error.
// 5. Run in gdb:
//    (gdb) break main
//    (gdb) run
//    (gdb) x/8xb c        # dump Circle bytes
//    (gdb) x/gx c         # dump vptr as pointer
//    (gdb) disas Circle::left_of  # see the assembly
