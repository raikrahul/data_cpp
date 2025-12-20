#include <array>
#include <iostream>
#include <cstddef>

// ROAST: You hardcoded '3' in your brain. 
// You typed 'veclovity' (typo). You typed 'accelration' (typo).
// You fear "array of dimensions". Stop fearing. `std::array<T, N>` IS the array of dimensions.
// You do not "extend" a struct. You tell the compiler to COPY-PASTE it for you with a new number.

// TEMPLATE DEFINITION
// Input N → Compiler generates code where every '3' is replaced by 'N'.
template<std::size_t N>
struct SpaceObject {
    std::array<float, N> position{};     // Size = N * 4 bytes
    std::array<float, N> velocity{};     // Size = N * 4 bytes
    std::array<float, N> acceleration{}; // Size = N * 4 bytes
};

// PREDICTED SIZES:
// SpaceObject<1>: 1*4 + 1*4 + 1*4 = 12 bytes
// SpaceObject<2>: 2*4 + 2*4 + 2*4 = 24 bytes
// SpaceObject<3>: 3*4 + 3*4 + 3*4 = 36 bytes

int main() {
    // 1. 2D Instantiation
    SpaceObject<2> asteroid; 
    asteroid.position[0] = 100.0f; // x
    asteroid.position[1] = 200.0f; // y
    // Offset of velocity? 2*4 = 8 bytes from start.
    asteroid.velocity[0] = 5.0f;

    // 2. 3D Instantiation
    SpaceObject<3> satellite;
    satellite.position[0] = 10.0f;
    satellite.position[1] = 20.0f;
    satellite.position[2] = 30.0f; // z
    // Offset of velocity? 3*4 = 12 bytes from start.
    satellite.velocity[0] = 1.0f;

    std::cout << "Size of SpaceObject<2>: " << sizeof(SpaceObject<2>) << " bytes" << std::endl;
    std::cout << "Size of SpaceObject<3>: " << sizeof(SpaceObject<3>) << " bytes" << std::endl;

    return 0;
}
