// ═══════════════════════════════════════════════════════════════════════════
// FILE: 79_geometry_intersect_solution.cpp
// TOPIC: Implement intersect function for 2D geometry objects
// APPROACH: std::variant + std::visit + generic lambda
// ═══════════════════════════════════════════════════════════════════════════

#include <cmath>
#include <iostream>
#include <variant>
#include <vector>

// ═══════════════════════════════════════════════════════════════════════════
// QUESTION 1 SPECIFICATION:
// ═══════════════════════════════════════════════════════════════════════════
//
// INPUT:  vector of 2D geometry objects + line (y = a*x + b)
// OUTPUT: vector<double> containing x-coordinates of ALL intersection points
//
// EACH geometry object must define:
//   std::vector<double> intersect(double a, double b) const;
//   returns 0, 1, or 2 x-coordinates
//
// ═══════════════════════════════════════════════════════════════════════════
// DESIGN DERIVATION:
// ═══════════════════════════════════════════════════════════════════════════
//
// 01. "vector of arbitrary geometry objects" → heterogeneous container needed
//     → SOLUTION: std::variant<Circle, Rectangle, Ellipse, ...>
//
// 02. "arbitrary, user-defined" → types known at library compile time
//     → SOLUTION: template parameter pack or fixed variant
//
// 03. "call intersect on each" → polymorphic dispatch needed
//     → SOLUTION: std::visit with generic lambda
//
// 04. "accumulate all x-coordinates" → collect results from all objects
//     → SOLUTION: loop over vector, append each object's results
//
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// STEP 1: DEFINE GEOMETRY TYPES (user-defined)
// ═══════════════════════════════════════════════════════════════════════════

struct Circle {
    double cx;      // center x
    double cy;      // center y
    double radius;  // radius

    // INTERFACE: intersect with line y = a*x + b
    // RETURNS: x-coordinates of intersection points (0, 1, or 2)
    //
    // DERIVATION:
    // Circle: (x - cx)² + (y - cy)² = r²
    // Line:   y = a*x + b
    // Substitute: (x - cx)² + (a*x + b - cy)² = r²
    // Expand:     (x - cx)² + (a*x + (b - cy))² = r²
    // Let d = b - cy
    //           (x - cx)² + (a*x + d)² = r²
    //           x² - 2*cx*x + cx² + a²x² + 2*a*d*x + d² = r²
    //           (1 + a²)x² + (-2*cx + 2*a*d)x + (cx² + d² - r²) = 0
    //           A*x² + B*x + C = 0
    // WHERE:
    //   A = 1 + a²
    //   B = -2*cx + 2*a*d = -2*cx + 2*a*(b - cy) = 2*(a*b - a*cy - cx)
    //   C = cx² + d² - r² = cx² + (b - cy)² - r²
    //
    // Discriminant D = B² - 4*A*C
    // D < 0: 0 intersections
    // D = 0: 1 intersection (tangent)
    // D > 0: 2 intersections
    //
    // x = (-B ± √D) / (2*A)
    //
    [[nodiscard]] std::vector<double> intersect(double a, double b) const {
        // TODO: IMPLEMENT - derive A, B, C coefficients
        // TODO: IMPLEMENT - calculate discriminant
        // TODO: IMPLEMENT - return x-coordinates based on D

        (void)a;
        (void)b;    // suppress unused warnings
        return {};  // STUB - replace with implementation
    }
};

struct Rectangle {
    double x_min;  // left edge
    double y_min;  // bottom edge
    double x_max;  // right edge
    double y_max;  // top edge

    // INTERFACE: intersect with line y = a*x + b
    // RETURNS: x-coordinates of intersection points (0, 1, or 2)
    //
    // DERIVATION:
    // Rectangle has 4 edges:
    //   top:    y = y_max, x ∈ [x_min, x_max]
    //   bottom: y = y_min, x ∈ [x_min, x_max]
    //   left:   x = x_min, y ∈ [y_min, y_max]
    //   right:  x = x_max, y ∈ [y_min, y_max]
    //
    // Line y = a*x + b intersects:
    //   top:    y_max = a*x + b → x = (y_max - b) / a  (if x ∈ [x_min, x_max])
    //   bottom: y_min = a*x + b → x = (y_min - b) / a  (if x ∈ [x_min, x_max])
    //   left:   y = a*x_min + b                        (if y ∈ [y_min, y_max])
    //   right:  y = a*x_max + b                        (if y ∈ [y_min, y_max])
    //
    // TRAP: a = 0 → horizontal line → special case
    // TRAP: may have 0, 1, 2, 3, or 4 intersections with edges
    //       but only return unique x-values in [x_min, x_max]
    //
    [[nodiscard]] std::vector<double> intersect(double a, double b) const {
        // TODO: IMPLEMENT - check intersection with each edge
        // TODO: IMPLEMENT - handle a = 0 (horizontal line)
        // TODO: IMPLEMENT - deduplicate and return

        (void)a;
        (void)b;    // suppress unused warnings
        return {};  // STUB - replace with implementation
    }
};

struct Ellipse {
    double cx;  // center x
    double cy;  // center y
    double rx;  // semi-axis x (horizontal radius)
    double ry;  // semi-axis y (vertical radius)

    // INTERFACE: intersect with line y = a*x + b
    // RETURNS: x-coordinates of intersection points (0, 1, or 2)
    //
    // DERIVATION:
    // Ellipse: ((x - cx)/rx)² + ((y - cy)/ry)² = 1
    // Substitute y = a*x + b:
    // ((x - cx)/rx)² + ((a*x + b - cy)/ry)² = 1
    //
    // Let u = x - cx, v = a*x + b - cy = a*(u + cx) + b - cy = a*u + (a*cx + b - cy)
    // Let k = a*cx + b - cy
    // v = a*u + k
    //
    // (u/rx)² + ((a*u + k)/ry)² = 1
    // u²/rx² + (a*u + k)²/ry² = 1
    // u²/rx² + (a²u² + 2*a*k*u + k²)/ry² = 1
    // Multiply by rx² * ry²:
    // ry²*u² + rx²*(a²u² + 2*a*k*u + k²) = rx²*ry²
    // (ry² + rx²*a²)*u² + (2*rx²*a*k)*u + (rx²*k² - rx²*ry²) = 0
    //
    // A = ry² + rx²*a²
    // B = 2*rx²*a*k
    // C = rx²*k² - rx²*ry² = rx²*(k² - ry²)
    //
    // Solve for u, then x = u + cx
    //
    [[nodiscard]] std::vector<double> intersect(double a, double b) const {
        // TODO: IMPLEMENT - derive A, B, C coefficients
        // TODO: IMPLEMENT - calculate discriminant
        // TODO: IMPLEMENT - convert u back to x

        (void)a;
        (void)b;    // suppress unused warnings
        return {};  // STUB - replace with implementation
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// STEP 2: DEFINE VARIANT TYPE ALIAS
// ═══════════════════════════════════════════════════════════════════════════

// USER specifies which geometry types are supported
template <typename... Shapes>
using ShapeVariant = std::variant<Shapes...>;

// EXAMPLE: library supports Circle, Rectangle, Ellipse
using Shape = ShapeVariant<Circle, Rectangle, Ellipse>;

// ═══════════════════════════════════════════════════════════════════════════
// STEP 3: FUNCTION SIGNATURE
// ═══════════════════════════════════════════════════════════════════════════
//
// SIGNATURE DERIVATION:
//
// INPUT:  vector of shapes     → const std::vector<Shape>&
// INPUT:  line parameters      → double a, double b
// OUTPUT: all x-coordinates    → std::vector<double>
//
// template version for arbitrary shape collections:
// template<typename ShapeCollection>
// std::vector<double> intersect(const ShapeCollection& shapes, double a, double b);
//
// concrete version for our Shape type:
// std::vector<double> intersect(const std::vector<Shape>& shapes, double a, double b);
//
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════════
// STEP 4: IMPLEMENT THE intersect FUNCTION
// ═══════════════════════════════════════════════════════════════════════════

[[nodiscard]] std::vector<double> intersect(const std::vector<Shape>& shapes, double a, double b) {
    std::vector<double> result;

    // DERIVATION:
    // for each shape in shapes:
    //   call shape.intersect(a, b) → returns vector<double>
    //   append all x-coordinates to result
    //
    // PROBLEM: shapes[i] is std::variant, not Circle/Rectangle/Ellipse
    // SOLUTION: std::visit with generic lambda
    //
    // MEMORY ANALYSIS:
    // shapes.size() = N
    // Each intersect() call returns 0, 1, or 2 values
    // Worst case: 2*N x-coordinates → result.reserve(2 * shapes.size())

    result.reserve(2 * shapes.size());  // avoid reallocations

    for (const auto& shape : shapes) {
        // std::visit: dispatch to correct operator() based on shape.index()
        // generic lambda: auto& s deduces to Circle&, Rectangle&, or Ellipse&
        // each type has .intersect(a, b) method → duck typing

        auto points = std::visit(
            [a, b](const auto& s) -> std::vector<double> { return s.intersect(a, b); }, shape);

        // append all intersection points to result
        for (double x : points) {
            result.push_back(x);
        }

        // OR: result.insert(result.end(), points.begin(), points.end());
    }

    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// STEP 5: TEMPLATE VERSION (for arbitrary shape collections)
// ═══════════════════════════════════════════════════════════════════════════

template <typename ShapeCollection>
[[nodiscard]] std::vector<double> intersect_generic(const ShapeCollection& shapes, double a,
                                                    double b) {
    std::vector<double> result;

    for (const auto& shape : shapes) {
        auto points = std::visit(
            [a, b](const auto& s) -> std::vector<double> { return s.intersect(a, b); }, shape);

        result.insert(result.end(), points.begin(), points.end());
    }

    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN: TEST HARNESS
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    std::cout << "=== GEOMETRY INTERSECTION TEST ===" << std::endl;

    // Create test shapes
    std::vector<Shape> shapes;
    shapes.emplace_back(Circle{0.0, 0.0, 1.0});            // unit circle at origin
    shapes.emplace_back(Rectangle{-2.0, -1.0, 2.0, 1.0});  // rectangle
    shapes.emplace_back(Ellipse{0.0, 0.0, 2.0, 1.0});      // ellipse

    // Define line: y = 0.5x + 0 (passes through origin, slope 0.5)
    double a = 0.5;
    double b = 0.0;

    std::cout << "Line: y = " << a << "*x + " << b << std::endl;
    std::cout << "Shapes: " << shapes.size() << std::endl;

    // Compute intersections
    std::vector<double> x_coords = intersect(shapes, a, b);

    std::cout << "Intersection x-coordinates: " << x_coords.size() << " points" << std::endl;
    for (std::size_t i = 0; i < x_coords.size(); ++i) {
        std::cout << "  x[" << i << "] = " << x_coords[i] << std::endl;
    }

    // MEMORY ANALYSIS:
    std::cout << "\n=== MEMORY ANALYSIS ===" << std::endl;
    std::cout << "sizeof(Circle) = " << sizeof(Circle) << " bytes" << std::endl;
    std::cout << "sizeof(Rectangle) = " << sizeof(Rectangle) << " bytes" << std::endl;
    std::cout << "sizeof(Ellipse) = " << sizeof(Ellipse) << " bytes" << std::endl;
    std::cout << "sizeof(Shape) = " << sizeof(Shape) << " bytes" << std::endl;
    std::cout << "shapes.index(0) = " << shapes[0].index() << " (Circle)" << std::endl;
    std::cout << "shapes.index(1) = " << shapes[1].index() << " (Rectangle)" << std::endl;
    std::cout << "shapes.index(2) = " << shapes[2].index() << " (Ellipse)" << std::endl;

    return 0;
}

// ═══════════════════════════════════════════════════════════════════════════
// FAILURE PREDICTIONS:
// ═══════════════════════════════════════════════════════════════════════════
//
// F1. Shape type missing intersect(double, double) → compile error ✓
// F2. intersect returns wrong type (not vector<double>) → compile error ✓
// F3. Quadratic formula with D < 0 and sqrt(D) → NaN → must check D first
// F4. Division by zero when a = 0 (horizontal line for rectangle)
// F5. Forgetting to reserve() → many reallocations for large N
// F6. Vertical line (infinite slope) → not representable with y = ax + b
//
// ═══════════════════════════════════════════════════════════════════════════
// TRIP-UP POINTS:
// ═══════════════════════════════════════════════════════════════════════════
//
// T1. const auto& s in lambda → s is reference, not copy → efficient
// T2. [a, b] capture by value → lambda closure is 16 bytes
// T3. -> std::vector<double> explicit return type → all branches must match
// T4. std::visit returns what visitor returns → auto points = std::visit(...)
// T5. variant.index() is 0, 1, 2 for 3 types → matches order in variant<...>
//
// ═══════════════════════════════════════════════════════════════════════════
