// 75_geometry_intersection.cpp
//
// TASK: Geometry Intersection Library
// SCENARIO: Compute intersections of a Line (y = ax + b) with various Shapes (Circle, Line, etc.)
// CONSTRAINT: User defines shapes. Library must be generic.
// NO SOLUTIONS - ALL BOILERPLATE - FILL CALCULATIONS BY HAND
//
// 01. STACK START
// [ 0xStack ] points (output vector) → Heap Block
// [ 0xStack ] shapes (input variants) → Heap Block
//
// 02. CONFUSION 1: Return Type
// Problem: User said "vector<double> intersect(...)".
// Reality: Intersection is (x,y) point.
// Why vector<double>?
//   - Maybe only X coordinate is returned?
//   - Y can be computed: y = ax + b
//   - What if line is vertical (x = c)? Formula y = ax+b fails!
//   - HARD PART: The problem spec uses y=ax+b (slope-intercept). Vertical lines have infinite slope
//   `a`.
//   - TRAP: Coordinate system issues. We must stick to spec essentially, or challenge it.
//   - Assumption: Use X-coordinate return, calc Y later. Vector size 0, 1, or 2 = number of
//   intersection pts.
//
// 03. CONFUSION 2: Heterogeneous Vector
// "Vector of 2D geometry objects"
// - vector<Circle>? No, need Circle AND Square AND Line etc.
// - vector<void*>? Unsafe.
// - vector<unique_ptr<Base>>? Virtual dispatch (Legacy).
// - vector<variant<Circle,Square...>>? Variant dispatch (Modern).
//
// ------------------------------------------------------------------------------------------

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

// =========================================================================================
// BLOCK 1: USER DEFINED SHAPES (The "Input")
// =========================================================================================

// 04. struct Circle
// Equation: (x-cx)^2 + (y-cy)^2 = r^2
// Line: y = ax + b
// Substitution: (x-cx)^2 + (ax+b-cy)^2 = r^2
// Expansion: (1+a^2)x^2 + 2(a(b-cy)-cx)x + (cx^2 + (b-cy)^2 - r^2) = 0
// Quadratic: Ax^2 + Bx + C = 0
// Solve for x.
struct Circle {
    double x{};  // Center X
    double y{};  // Center Y
    double r{};  // Radius

    // Return X coordinates of intersection
    std::vector<double> intersect(double a, double b) const {
        (void)a;
        (void)b;       // Suppress unused warning
        return {1.0};  // Dummy return to force assembly generation
    }
};

// 05. struct Rectangle (Axis Aligned for simplicity first?)
// Edges: x=x1, x=x2, y=y1, y=y2
// Intersection with y=ax+b:
// Intersect x=x1: y = a*x1 + b. Check if y in [y1, y2].
// Intersect x=x2: y = a*x2 + b. Check if y in [y1, y2].
// Intersect y=y1: y1 = ax + b → x = (y1-b)/a. Check if x in [x1, x2].
// Intersect y=y2: y2 = ax + b → x = (y2-b)/a. Check if x in [x1, x2].
struct Rectangle {
    double x1, y1;  // Bottom-left
    double x2, y2;  // Top-right

    std::vector<double> intersect(double a, double b) const {
        (void)a;
        (void)b;  // Suppress unused warning
        std::vector<double> results;
        // TODO: IMPLEMENT INTERSECTION LOGIC
        // Trap: What if 'a' (slope) is 0? Div by zero for horizontal edges?
        // Trap: What if line overlaps edge perfectly? (Infinite points?) ignores spec "points"
        return results;
    }
};

// =========================================================================================
// BLOCK 2: VARIANT & VISITOR (The "Interface")
// =========================================================================================

// 06. using GeometryVariant
using Geometry = std::variant<Circle, Rectangle>;

// 07. struct IntersectionVisitor
struct IntersectionVisitor {
    double a;  // Line slope
    double b;  // Line intercept

    // operator() template for duck typing
    template <typename T>
    std::vector<double> operator()(const T& shape) const {
        // Concept Check: Does T have intersect(double, double)?
        // If not, compile error (Good!)
        // Duck Typing: shape.intersect(a, b)
        return shape.intersect(a, b);
    }
};

// =========================================================================================
// BLOCK 3: LIBRARY FUNCTION (The "Core")
// =========================================================================================

// 08. solve_intersections
// Input: Vector of variants, Line (a,b)
// Output: Vector of (x,y) points
struct Point {
    double x, y;
};

std::vector<Point> solve_intersections(const std::vector<Geometry>& shapes, double a, double b) {
    std::vector<Point> all_points;
    IntersectionVisitor visitor{a, b};

    for (const auto& shape_var : shapes) {
        // Visit variant
        std::vector<double> x_coords = std::visit(visitor, shape_var);

        // Convert x to (x,y) using line eq y = ax + b
        for (double x : x_coords) {
            double y = a * x + b;
            all_points.push_back({x, y});
        }
    }
    return all_points;
}

// =========================================================================================
// BLOCK 4: TEST BOILERPLATE (The "Driver")
// =========================================================================================

void run_test(const std::string& name, const std::vector<Geometry>& shapes, double a, double b) {
    std::cout << "TEST: " << name << " (Line y = " << a << "x + " << b << ")\n";
    auto points = solve_intersections(shapes, a, b);

    std::cout << "  Found " << points.size() << " intersections:\n";
    for (const auto& p : points) {
        std::cout << "    (" << p.x << ", " << p.y << ")\n";
    }
    std::cout << "----------------------------------------\n";
}

int main() {
    // 09. TEST CASE 1: Circle at origin, Line y=x (diagonal through origin)
    // Circle: x=0, y=0, r=1
    // Line: y = 1*x + 0
    // Expected: (+0.707, +0.707), (-0.707, -0.707)
    // Math: x^2 + x^2 = 1 → 2x^2 = 1 → x^2 = 0.5 → x = ±sqrt(0.5) ≈ ±0.707
    run_test("Unit Circle vs y=x", {Circle{0, 0, 1}}, 1.0, 0.0);

    // 10. TEST CASE 2: Circle shifted, Line offset
    // Circle: x=2, y=2, r=1
    // Line: y = 1*x + 0 (intersects circle?)
    // Center (2,2) on line y=x.
    // Expected: (2+0.707, 2+0.707), (2-0.707, 2-0.707)
    run_test("Shifted Circle vs y=x", {Circle{2, 2, 1}}, 1.0, 0.0);

    // 11. TEST CASE 3: No Intersection
    // Circle: x=10, y=10, r=1
    // Line: y = -x (opposite quadrant effectively)
    // Expected: 0 points
    run_test("Far Circle vs y=-x", {Circle{10, 10, 1}}, -1.0, 0.0);

    // 12. TEST CASE 4: Tangent
    // Circle: x=0, y=1, r=1
    // Line: y=0 (X-axis)
    // Intersects at (0,0) only? Or float precision issues?
    // D should be 0.
    run_test("Tangent Circle vs y=0", {Circle{0, 1, 1}}, 0.0, 0.0);

    // 13. PROBLEM CONFUSION CHECK
    // You asked: "how can a vec of double be sufficient... need x,y"
    // Answer: We return X from shape.intersect(), then library calculates Y = a*X + b.
    // Trap: Vertical lines cannot be represented by y=ax+b (a=infinity).
    // This interface FAILS for vertical lines.
    // This is a "Part designed to trip you off".

    return 0;
}
