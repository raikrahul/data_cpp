// 77_variant_alias_step2.cpp
// STEP 2: Template Alias with FIXED Parameter Count.
// GOAL: Introduce parameterization. See the NEW limitation.
// NO SOLUTIONS YET. JUST THE PROBLEM.

#include <iostream>
#include <variant>

// ═══════════════════════════════════════════════════════════════════════════
// STRUCT DEFINITIONS (Same as Step 0)
// ═══════════════════════════════════════════════════════════════════════════

struct Circle {
    // Size: 3 × 8 = 24 bytes. Align: 8.
    double x{}, y{}, r{};
};

struct Rectangle {
    // Size: 4 × 8 = 32 bytes. Align: 8.
    double x1{}, y1{}, x2{}, y2{};
};

struct Ellipse {
    // Size: 4 × 8 = 32 bytes. Align: 8.
    double cx{}, cy{}, a{}, b{};
};

struct Triangle {
    // Size: 6 × 8 = 48 bytes. Align: 8.
    // 3 vertices: (x1,y1), (x2,y2), (x3,y3).
    double x1{}, y1{}, x2{}, y2{}, x3{}, y3{};
};

struct Line {
    // Size: 4 × 8 = 32 bytes. Align: 8.
    // 2 endpoints: (x1,y1), (x2,y2).
    double x1{}, y1{}, x2{}, y2{};
};

// ═══════════════════════════════════════════════════════════════════════════
// STEP 2: TEMPLATE ALIAS WITH FIXED PARAMETER COUNT
// ═══════════════════════════════════════════════════════════════════════════
//
// OBSERVATION FROM STEP 0:
// Typing `std::variant<Circle, Rectangle, Ellipse>` = 42 characters repeated.
// SOLUTION ATTEMPT: Use `template` to parameterize.
//
// SYNTAX:
// template<typename A, typename B, typename C>
// using MyShape = std::variant<A, B, C>;
//
// WHAT THIS DOES:
// 1. `template<typename A, typename B, typename C>` declares 3 type parameters.
// 2. `using MyShape =` creates a new name.
// 3. `std::variant<A, B, C>` is the target type, using those parameters.
//
// SUBSTITUTION TRACE:
// MyShape<Circle, Rectangle, Ellipse>
//     ↓
// A = Circle, B = Rectangle, C = Ellipse (pattern match)
//     ↓
// std::variant<Circle, Rectangle, Ellipse> (substitution)
//
// ═══════════════════════════════════════════════════════════════════════════

// ───────────────────────────────────────────────────────────────────────────
// FIXED 3-TYPE ALIAS (Works for EXACTLY 3 types)
// What: Template alias accepting 3 type parameters.
// Why: Reduces repetition for 3-type variants.
// Where: Compile-time. No runtime cost. No memory for alias itself.
// Who: Compiler's symbol table.
// When: During template instantiation.
// Without: Would need separate alias for 2 types, 4 types, etc.
// Which: Works for ANY 3 types, not just shapes.
// ───────────────────────────────────────────────────────────────────────────
template <typename A, typename B, typename C>
using Shape3 = std::variant<A, B, C>;

// ───────────────────────────────────────────────────────────────────────────
// FIXED 2-TYPE ALIAS (Works for EXACTLY 2 types)
// What: Template alias accepting 2 type parameters.
// Why: Different arity = different template needed.
// ANNOYANCE: Must write ANOTHER template for different count.
// ───────────────────────────────────────────────────────────────────────────
template <typename A, typename B>
using Shape2 = std::variant<A, B>;

// ───────────────────────────────────────────────────────────────────────────
// FIXED 4-TYPE ALIAS (Works for EXACTLY 4 types)
// What: Template alias accepting 4 type parameters.
// ANNOYANCE GROWS: 10 shapes = need Shape10 definition.
// ───────────────────────────────────────────────────────────────────────────
template <typename A, typename B, typename C, typename D>
using Shape4 = std::variant<A, B, C, D>;

// ═══════════════════════════════════════════════════════════════════════════
// THE PROBLEM:
// N different type counts = N different template alias definitions.
// If you need 2,3,4,5 types → 4 templates needed.
// If you need 2..20 types → 19 templates needed.
// Combinatorial explosion.
// ERROR if wrong template used: Shape3<A,B> = compile error (expected 3, got 2).
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// ALTERNATIVE APPROACHES (Why `using` is needed)
// ═══════════════════════════════════════════════════════════════════════════

// ───────────────────────────────────────────────────────────────────────────
// APPROACH A: STRUCT WRAPPER (Works, but UGLY)
// What: Wrap variant in a struct.
// Why: Struct can be templated. This works in C++03.
// Problem: NOT a direct alias. Need to access `.value` member.
// Memory: sizeof(ShapeWrapper3<A,B,C>) = sizeof(variant<A,B,C>) = same bytes.
//         BUT usage is different.
// ───────────────────────────────────────────────────────────────────────────
template <typename A, typename B, typename C>
struct ShapeWrapper3 {
    std::variant<A, B, C> value;  // The actual variant buried inside.
    // Size = sizeof(variant<A,B,C>) = 8 + max(sizeof(A), sizeof(B), sizeof(C)).
};

// USAGE COMPARISON:
// With `using Shape3`:
//   Shape3<Circle, Rectangle, Ellipse> s = Circle{1.0, 2.0, 0.5};
//   s.index();  ← Direct access. Clean.
//
// With `struct ShapeWrapper3`:
//   ShapeWrapper3<Circle, Rectangle, Ellipse> w;
//   w.value = Circle{1.0, 2.0, 0.5};  ← Must access `.value`. Ugly.
//   w.value.index();  ← Must access `.value`. Ugly.

// ───────────────────────────────────────────────────────────────────────────
// APPROACH B: typedef (DOES NOT WORK with templates!)
// What: Old C-style type alias.
// Why: Cannot be templated. Historical limitation.
// ───────────────────────────────────────────────────────────────────────────
// ✗ INVALID:
// template<typename A, typename B, typename C>
// typedef std::variant<A, B, C> ShapeTypedef3;
// ERROR: "typedef cannot follow template"

// ✓ VALID (but non-templated):
typedef std::variant<Circle, Rectangle, Ellipse> FixedShapeTypedef;
// This works but is FIXED to exactly Circle, Rectangle, Ellipse.
// Cannot change types. Same problem as Step 0.

// ═══════════════════════════════════════════════════════════════════════════
// STEP 3: VARIADIC TEMPLATES (The Solution!)
// ═══════════════════════════════════════════════════════════════════════════
//
// PROBLEM FROM STEP 2:
// Shape2<A,B> = 2 types only.
// Shape3<A,B,C> = 3 types only.
// Shape4<A,B,C,D> = 4 types only.
// Need N templates for N different arities. BAD.
//
// SOLUTION: Use `typename...` to accept ANY number of types.
//
// SYNTAX:
// template<typename... Types>
// using ShapeAny = std::variant<Types...>;
//
// SUBSTITUTION TRACE:
// ShapeAny<Circle>                       → std::variant<Circle>
// ShapeAny<Circle, Rectangle>            → std::variant<Circle, Rectangle>
// ShapeAny<Circle, Rectangle, Ellipse>   → std::variant<Circle, Rectangle, Ellipse>
// ShapeAny<A,B,C,D,E,F,G,H,I,J>          → std::variant<A,B,C,D,E,F,G,H,I,J>
//
// ONE TEMPLATE handles ALL cases!
// ═══════════════════════════════════════════════════════════════════════════

// ───────────────────────────────────────────────────────────────────────────
// VARIADIC TEMPLATE ALIAS (using)
// What: Template alias accepting ANY number of type parameters.
// Why: Single definition handles 2, 3, 4, 5, 10, 100 types.
// Where: Compile-time. No runtime cost.
// Who: Compiler expands `Types...` into type list.
// When: During template instantiation.
// Without: Would need Shape2, Shape3, Shape4... (explosion).
// Which: Works for ANY types, ANY count.
// ───────────────────────────────────────────────────────────────────────────
template <typename... Types>
using ShapeAny = std::variant<Types...>;
//
// MEMORY: 0 bytes for alias itself.
// USAGE: ShapeAny<A,B,C> = std::variant<A,B,C>. Direct substitution.

// ───────────────────────────────────────────────────────────────────────────
// VARIADIC STRUCT WRAPPER (for comparison)
// What: Struct wrapper accepting ANY number of types.
// Why: Works, but UGLY (same .value issue as non-variadic wrapper).
// ───────────────────────────────────────────────────────────────────────────
template <typename... Types>
struct ShapeWrapperAny {
    std::variant<Types...> value;  // Still need .value access.
    // Size = sizeof(variant<Types...>) = 8 + max(sizeof(Types)...).
};
//
// COMPARISON:
// ShapeAny<X,Y,Z> s = X{};
//   s.index();  ← Clean.
//
// ShapeWrapperAny<X,Y,Z> w;
// w.value = X{};
//   w.value.index();  ← Ugly.

int main() {
    // ───────────────────────────────────────────────────────────────────────
    // USAGE OF Shape3 (3 types):
    // What: Use 3-type alias.
    // Memory: sizeof(variant) = 8 (header) + max(24,32,32) = 40 bytes.
    // Substitution: Shape3<Circle, Rectangle, Ellipse>
    //                 ↓
    //               std::variant<Circle, Rectangle, Ellipse>
    // ───────────────────────────────────────────────────────────────────────
    Shape3<Circle, Rectangle, Ellipse> s3 = Circle{1.0, 2.0, 0.5};
    // CHARACTER COUNT: 33 characters (was 42 for raw variant).
    // SAVINGS: 42 - 33 = 9 characters per use.
    // At 1000 uses: 9 × 1000 = 9,000 characters saved.

    // ───────────────────────────────────────────────────────────────────────
    // USAGE OF Shape2 (2 types):
    // Memory: sizeof(variant) = 8 + max(24,32) = 40 bytes.
    // Substitution: Shape2<Circle, Rectangle>
    //                 ↓
    //               std::variant<Circle, Rectangle>
    // ───────────────────────────────────────────────────────────────────────
    Shape2<Circle, Rectangle> s2 = Rectangle{0.0, 0.0, 5.0, 3.0};
    // Works. But needed SEPARATE template definition.

    // ───────────────────────────────────────────────────────────────────────
    // USAGE OF Shape4 (4 types):
    // Memory: sizeof(variant) = 8 + max(24,32,32,48) = 56 bytes.
    //   48 = sizeof(Triangle) = largest.
    //   8 header → 8 + 48 = 56 bytes.
    // Substitution: Shape4<Circle, Rectangle, Ellipse, Triangle>
    //                 ↓
    //               std::variant<Circle, Rectangle, Ellipse, Triangle>
    // ───────────────────────────────────────────────────────────────────────
    Shape4<Circle, Rectangle, Ellipse, Triangle> s4 = Triangle{0, 0, 1, 0, 0.5, 1};
    // Works. But needed ANOTHER SEPARATE template definition.

    // ───────────────────────────────────────────────────────────────────────
    // THE PAIN POINT:
    // What if we need 5 types?
    //   Shape5<A,B,C,D,E> = need to DEFINE Shape5.
    // What if we need 10 types?
    //   Shape10<A,B,C,D,E,F,G,H,I,J> = need to DEFINE Shape10.
    // Explosion of definitions.
    // ───────────────────────────────────────────────────────────────────────

    // ───────────────────────────────────────────────────────────────────────
    // COMPILE ERROR DEMO (Uncomment to see):
    // Shape3<Circle, Rectangle> error_var;
    //   ERROR: "wrong number of template arguments (2, should be 3)"
    //   Shape3 expects EXACTLY 3 types. We gave 2.
    // ───────────────────────────────────────────────────────────────────────

    // ═══════════════════════════════════════════════════════════════════════
    // VERIFICATION
    // ═══════════════════════════════════════════════════════════════════════
    std::cout << "sizeof(Circle)    = " << sizeof(Circle) << " bytes\n";
    std::cout << "sizeof(Rectangle) = " << sizeof(Rectangle) << " bytes\n";
    std::cout << "sizeof(Ellipse)   = " << sizeof(Ellipse) << " bytes\n";
    std::cout << "sizeof(Triangle)  = " << sizeof(Triangle) << " bytes\n";
    std::cout << "\n";
    std::cout << "sizeof(s3) [Shape3<C,R,E>]     = " << sizeof(s3) << " bytes (expected 40)\n";
    std::cout << "sizeof(s2) [Shape2<C,R>]       = " << sizeof(s2) << " bytes (expected 40)\n";
    std::cout << "sizeof(s4) [Shape4<C,R,E,T>]   = " << sizeof(s4) << " bytes (expected 56)\n";
    std::cout << "\n";
    std::cout << "s3.index() = " << s3.index() << " (expected 0 = Circle)\n";
    std::cout << "s2.index() = " << s2.index() << " (expected 1 = Rectangle)\n";
    std::cout << "s4.index() = " << s4.index() << " (expected 3 = Triangle)\n";

    // ═══════════════════════════════════════════════════════════════════════
    // DEMO: STRUCT WRAPPER APPROACH (Approach A)
    // ═══════════════════════════════════════════════════════════════════════
    std::cout << "\n=== STRUCT WRAPPER DEMO ===\n";

    // ───────────────────────────────────────────────────────────────────────
    // Using struct wrapper (UGLY):
    // Memory: sizeof(ShapeWrapper3<C,R,E>) = 40 bytes (same as variant inside).
    // BUT: Must access .value to do anything.
    // ───────────────────────────────────────────────────────────────────────
    ShapeWrapper3<Circle, Rectangle, Ellipse> wrapper;
    wrapper.value = Circle{3.0, 4.0, 1.5};  // UGLY: .value required.

    std::cout << "sizeof(wrapper)       = " << sizeof(wrapper) << " bytes (same as s3)\n";
    std::cout << "wrapper.value.index() = " << wrapper.value.index() << " (must use .value!)\n";

    // COMPARISON:
    // Clean (using alias):     s3.index()           ← 10 characters
    // Ugly (struct wrapper):   wrapper.value.index() ← 21 characters
    // Extra typing: 21 - 10 = 11 characters per access.
    // At 1000 accesses: 11 × 1000 = 11,000 extra characters.

    // ═══════════════════════════════════════════════════════════════════════
    // DEMO: TYPEDEF APPROACH (Approach B - Fixed, Non-Template)
    // ═══════════════════════════════════════════════════════════════════════
    std::cout << "\n=== TYPEDEF DEMO ===\n";

    // ───────────────────────────────────────────────────────────────────────
    // Using typedef (FIXED to Circle, Rectangle, Ellipse):
    // Cannot change types. Same limitation as Step 0.
    // ───────────────────────────────────────────────────────────────────────
    FixedShapeTypedef td = Ellipse{5.0, 6.0, 2.0, 1.0};

    std::cout << "sizeof(FixedShapeTypedef) = " << sizeof(td) << " bytes\n";
    std::cout << "td.index()                = " << td.index() << " (expected 2 = Ellipse)\n";
    std::cout << "Problem: FixedShapeTypedef cannot be reused for different types!\n";

    // ═══════════════════════════════════════════════════════════════════════
    // DEMO: VARIADIC TEMPLATE ALIAS (STEP 3 - The Solution!)
    // ═══════════════════════════════════════════════════════════════════════
    std::cout << "\n=== VARIADIC TEMPLATE DEMO (ShapeAny<...>) ===\n";

    // ───────────────────────────────────────────────────────────────────────
    // SAME template works for 2, 3, 4, 5 types!
    // No need for Shape2, Shape3, Shape4, Shape5 separate definitions.
    // ───────────────────────────────────────────────────────────────────────

    // 2 types:
    ShapeAny<Circle, Rectangle> v2 = Circle{1.0, 1.0, 1.0};
    // Substitution: ShapeAny<Circle, Rectangle> → std::variant<Circle, Rectangle>
    // sizeof = 8 + max(24, 32) = 40 bytes.

    // 3 types:
    ShapeAny<Circle, Rectangle, Ellipse> v3 = Rectangle{0.0, 0.0, 2.0, 2.0};
    // Substitution: ShapeAny<C, R, E> → std::variant<C, R, E>
    // sizeof = 8 + max(24, 32, 32) = 40 bytes.

    // 4 types:
    ShapeAny<Circle, Rectangle, Ellipse, Triangle> v4 = Ellipse{3.0, 3.0, 1.0, 0.5};
    // sizeof = 8 + max(24, 32, 32, 48) = 56 bytes.

    // 5 types:
    ShapeAny<Circle, Rectangle, Ellipse, Triangle, Line> v5 = Triangle{0, 0, 1, 0, 0.5, 0.8};
    // sizeof = 8 + max(24, 32, 32, 48, 32) = 56 bytes.

    std::cout << "sizeof(v2) [2 types] = " << sizeof(v2) << " bytes\n";
    std::cout << "sizeof(v3) [3 types] = " << sizeof(v3) << " bytes\n";
    std::cout << "sizeof(v4) [4 types] = " << sizeof(v4) << " bytes\n";
    std::cout << "sizeof(v5) [5 types] = " << sizeof(v5) << " bytes\n";
    std::cout << "v2.index() = " << v2.index() << " (expected 0 = Circle)\n";
    std::cout << "v3.index() = " << v3.index() << " (expected 1 = Rectangle)\n";
    std::cout << "v4.index() = " << v4.index() << " (expected 2 = Ellipse)\n";
    std::cout << "v5.index() = " << v5.index() << " (expected 3 = Triangle)\n";

    // ═══════════════════════════════════════════════════════════════════════
    // DEMO: VARIADIC STRUCT WRAPPER (Comparison)
    // ═══════════════════════════════════════════════════════════════════════
    std::cout << "\n=== VARIADIC STRUCT WRAPPER DEMO ===\n";

    ShapeWrapperAny<Circle, Rectangle, Ellipse> wrapperV;
    wrapperV.value = Circle{7.0, 8.0, 2.0};  // Must use .value to assign!
    // Note: Line{} would be compile error here (Line not in variant).

    ShapeWrapperAny<Circle, Rectangle, Ellipse, Triangle, Line> wrapperV5;
    wrapperV5.value = Line{0.0, 0.0, 10.0, 10.0};

    std::cout << "sizeof(wrapperV5)       = " << sizeof(wrapperV5) << " bytes\n";
    std::cout << "wrapperV5.value.index() = " << wrapperV5.value.index() << " (must use .value!)\n";
    std::cout << "Same 5 types, but UGLY access pattern!\n";

    // ═══════════════════════════════════════════════════════════════════════
    // MEMORY LAYOUT OF s4 @ Stack (Largest example):
    //
    // sizeof(s4) = 56 bytes.
    // Breakdown:
    //   [0x00]: index (1B) = 0x03 (Triangle = 4th type, index 3).
    //   [0x01..0x07]: padding (7B).
    //   [0x08]: x1 (8B) = 0.0.
    //   [0x10]: y1 (8B) = 0.0.
    //   [0x18]: x2 (8B) = 1.0.
    //   [0x20]: y2 (8B) = 0.0.
    //   [0x28]: x3 (8B) = 0.5.
    //   [0x30]: y3 (8B) = 1.0.
    //
    // Total: 8 (header) + 48 (Triangle data) = 56 bytes.
    //
    // ┌──────────────┬────────┬──────────────────────────────────────────────┐
    // │ Address      │ Size   │ Content                                      │
    // ├──────────────┼────────┼──────────────────────────────────────────────┤
    // │ RSP+0x00     │ 1B     │ 0x03 (index = Triangle)                      │
    // ├──────────────┼────────┼──────────────────────────────────────────────┤
    // │ RSP+0x01     │ 7B     │ padding                                      │
    // ├──────────────┼────────┼──────────────────────────────────────────────┤
    // │ RSP+0x08     │ 48B    │ Triangle{0,0, 1,0, 0.5,1} data               │
    // └──────────────┴────────┴──────────────────────────────────────────────┘
    // ═══════════════════════════════════════════════════════════════════════

    // ═══════════════════════════════════════════════════════════════════════
    // SUMMARY OF STEP 2:
    // SOLVED: Repetition reduced for FIXED type counts.
    // NEW PROBLEM: Need separate template for each arity (2,3,4,5...).
    // NEXT STEP: Use variadic templates `typename...` to handle ANY count.
    // ═══════════════════════════════════════════════════════════════════════

    return 0;
}
