#include <iostream>
#include <cmath>

// 01. Define a compile-time constant for Pi using std::numbers if C++20, or manual
// TODO: Use constexpr for this.
// constexpr double PI = 3.14159265358979323846;

constexpr double PI = std::numbers::pi;


// 02. Implement 'coeff' function
// REQUIREMENTS:
// - constexpr
// - Returns 0.0 exactly if x == y (handled explicitly)
// - Otherwise returns a complex formula involving x, y, and PI. e.g. (x*x - y) * PI
// TODO: Write this function
constexpr double coeff(double x, double y) {
    if (x == y) {
        return 0.0;
    }
    // Arbitrary interaction formula based on transcript description
    // "distribute multiplication by x over parenthesis" -> maybe x*(x-y)?
    return (x * x - y * x) * 0.3333333333; 
}

// 03. Implement 'poly' function for order 3 using 3 coefficients?
// Transcript says "three coefficients... and variable x".
// Let's assume a*x^2 + b*x + c (Order 2) purely based on arg count, 
// or x^3 + a*x^2 + b*x + c?
// Let's do generic ax^2 + bx + c for consistency with "3 coefficients".
constexpr double poly(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

int main() {
    // 04. Compile-time constant instantiation
    constexpr double particle_mass = 1.0;
    constexpr double particle_charge = 1.602e-19;
    constexpr double y = PI; // Initialized from another constexpr

    // 05. Call constexpr functions with literals
    constexpr double interaction = coeff(3.0, 3.0);
    // VERIFY: static_assert checks condition AT COMPILE TIME
    static_assert(interaction == 0.0, "coeff(3,3) must be 0.0");

    constexpr double p_val = poly(1.0, 2.0, 1.0, 2.0); 
    // Manual Calc: 1*4 + 2*2 + 1 = 4 + 4 + 1 = 9.0
    static_assert(p_val == 9.0, "poly(1,2,1,2) must be 9.0");

    // 06. Output result
    std::cout << "Interaction (compile-time): " << interaction << "\n";
    std::cout << "Poly (compile-time): " << p_val << "\n";

    // 07. FAILURES (Uncomment to see errors)
    // int runtime_in;
    // std::cin >> runtime_in;
    // constexpr int k = runtime_in; // ERROR: Not a constant expression

    // 08. Runtime usage of constexpr function
    // double dyn_x;
    // std::cin >> dyn_x;
    // std::cout << "Runtime Poly: " << poly(1.0, 2.0, 1.0, dyn_x) << "\n"; // Valid!

    return 0;
}
