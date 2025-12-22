#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <iomanip>

// User: Read src/67_finite_difference_stencil.md FIRST.
// i=1 -> 0x1008. i=2 -> 0x1010.

void apply_stencil_3point(const std::vector<double>& u, std::vector<double>& u_new) {
    if (u_new.size() != u.size()) u_new.resize(u.size());
    size_t N = u.size();

    u_new[0] = u[0];       // Line 33: Boundary
    u_new[N-1] = u[N-1];   // Line 34: Boundary

    const double* src_ptr = u.data(); // Line 02
    double* dst_ptr = u_new.data();   // Line 15

    (void)src_ptr; // TODO: remove this when you use src_ptr


    double c_left = 1.0;
    double c_center = -2.0;
    double c_right = 1.0;

    // Line 35: Loop Range 1 to 3
    for (size_t i = 1; i < N - 1; ++i) {
        // MD Line 05: Addr(left) = src + i - 1
        // MD Line 04: Addr(center) = src + i
        // MD Line 06: Addr(right) = src + i + 1

        // TODO: REPLACE 0.0 WITH POINTER ARITHMETIC
        // double val_left   = ...; 
        double val_left   = 0.0; 
        double val_center = 0.0;
        double val_right  = 0.0;

        // Calc: c_left*val_left + c_center*val_center + c_right*val_right
        double result = (c_left * val_left) + (c_center * val_center) + (c_right * val_right);
        
        // Store
        dst_ptr[i] = result;
    }
}

void test_basic_diffusion() {
    std::vector<double> u = { 1.0, 2.0, 5.0, 4.0, 1.0 };
    std::vector<double> u_new;
    apply_stencil_3point(u, u_new);

    // MD Line 14: Result 2.0
    double e1 = 2.0;
    // MD Line 23: Result -4.0
    double e2 = -4.0;
    // MD Line 31: Result -2.0
    double e3 = -2.0;

    std::cout << "i=1: Exp " << e1 << " Got " << u_new[1] << "\n";
    std::cout << "i=2: Exp " << e2 << " Got " << u_new[2] << "\n";
    std::cout << "i=3: Exp " << e3 << " Got " << u_new[3] << "\n";
    
    // Hard check
    if(std::abs(u_new[1] - e1) > 1e-9) exit(1);
    if(std::abs(u_new[2] - e2) > 1e-9) exit(1);
    if(std::abs(u_new[3] - e3) > 1e-9) exit(1);
}

int main() {
    test_basic_diffusion();
    std::cout << "OK\n";
    return 0;
}
