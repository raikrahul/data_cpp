#include <iostream>
#include <array>
#include <cmath>

// ROAST: You wrote `template<sisz_t> N`. 
// Correction: `template<std::size_t N> struct SpaceObject`.
// You said "infinite dimensions". 
// N is a placeholder. If you write loop i=0..N, you handle ALL dimensions.

template<std::size_t N>
struct SpaceObject {
    // 1. DATA: The dimensions themselves.
    // This valid for N=1, N=3, N=1000.
    std::array<float, N> position{}; 
    
    // 2. LOGIC: How to calculate length in ANY dimension?
    // You use a loop up to N.
    float lengthSquared() const {
        float sum = 0.0f;
        // The compiler knows N. It will unroll this loop.
        for(std::size_t i = 0; i < N; ++i) {
            sum += position[i] * position[i];
        }
        return sum;
    }
    
    void print() const {
        std::cout << N << "-D Object: [ ";
        for(auto v : position) std::cout << v << " ";
        std::cout << "]\n";
    }
};

int main() {
    // 3. INSTANTIATION: "Infinite" choice.
    // 3 dimensions
    SpaceObject<3> point3D;
    point3D.position = {3.0f, 4.0f, 0.0f};
    
    // 10 dimensions (Higher dimensional)
    SpaceObject<10> point10D;
    point10D.position.fill(1.0f); // Set all 10 dims to 1.0

    std::cout << "3D LenSq: " << point3D.lengthSquared() << " (Expected 25)\n";
    std::cout << "10D LenSq: " << point10D.lengthSquared() << " (Expected 10)\n";
    
    point3D.print();
    point10D.print();

    return 0;
}
