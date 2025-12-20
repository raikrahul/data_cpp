#include <iostream>
#include <vector>

// =============================================================================
// 47 countEqualItems Template
// Problem: Count items in vector equal to toCompare
// =============================================================================
//
// MEMORY LAYOUT:
// v = {1.0f, 2.0f, 3.0f, 2.0f} at 0x7000
// +--------+--------+--------+--------+
// | 0x7000 | 0x7004 | 0x7008 | 0x700C |
// | 1.0f   | 2.0f   | 3.0f   | 2.0f   |
// +--------+--------+--------+--------+
// sizeof(float)=4, 4 elements × 4 bytes = 16 bytes
//
// secondItem = v[1] = 2.0f (copy, not reference)
// toCompare = 2.0f
//
// COMPARISON TRACE (T=float):
// i=0: items[0]=1.0f == 2.0f? 1.0f != 2.0f → ✗ count stays 0
// i=1: items[1]=2.0f == 2.0f? 2.0f == 2.0f → ✓ count=0+1=1
// i=2: items[2]=3.0f == 2.0f? 3.0f != 2.0f → ✗ count stays 1
// i=3: items[3]=2.0f == 2.0f? 2.0f == 2.0f → ✓ count=1+1=2
// return 2
//
// TYPE DEDUCTION:
// countEqualItems(v, secondItem)
// v = vector<float> → T=float
// secondItem = float → T=float ✓ (both match)
//
// TRAP: countEqualItems(v, 2) → v=vector<float>, 2=int → T=float vs T=int → error
// FIX: countEqualItems(v, 2.0f) or countEqualItems<float>(v, 2)
//
// =============================================================================

template<typename T>
int countEqualItems(const std::vector<T>& items, T toCompare) {
    int count = 0;
    for (size_t i = 0; i < items.size(); ++i) {
        // items[i] == toCompare uses T::operator==
        // for float: bitwise compare (ignoring NaN edge cases)
        if (items[i] == toCompare) {
            ++count;
        }
    }
    return count;
}

int main() {
    std::cout << "47 countEqualItems Template\n" << std::endl;

    // v = {1.0f, 2.0f, 3.0f, 2.0f}
    // Memory: 0x7000=1.0f, 0x7004=2.0f, 0x7008=3.0f, 0x700C=2.0f
    auto v = std::vector{1.0f, 2.0f, 3.0f, 2.0f};
    
    std::cout << "v = {";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i < v.size() - 1) std::cout << ", ";
    }
    std::cout << "}" << std::endl;
    std::cout << "v.size() = " << v.size() << std::endl;
    std::cout << "sizeof(float) = " << sizeof(float) << std::endl;
    std::cout << "total bytes = " << v.size() * sizeof(float) << std::endl;
    std::cout << std::endl;

    // secondItem = v[1] = 2.0f
    auto secondItem = v[1];
    std::cout << "secondItem = v[1] = " << secondItem << std::endl;
    std::cout << std::endl;

    // countEqualItems(v, secondItem)
    // T=float deduced from both v (vector<float>) and secondItem (float)
    auto numItems = countEqualItems(v, secondItem);
    
    std::cout << "=== TRACE ===" << std::endl;
    std::cout << "i=0: v[0]=" << v[0] << " == " << secondItem << "? " 
              << (v[0] == secondItem ? "✓" : "✗") << std::endl;
    std::cout << "i=1: v[1]=" << v[1] << " == " << secondItem << "? " 
              << (v[1] == secondItem ? "✓" : "✗") << std::endl;
    std::cout << "i=2: v[2]=" << v[2] << " == " << secondItem << "? " 
              << (v[2] == secondItem ? "✓" : "✗") << std::endl;
    std::cout << "i=3: v[3]=" << v[3] << " == " << secondItem << "? " 
              << (v[3] == secondItem ? "✓" : "✗") << std::endl;
    std::cout << std::endl;

    std::cout << "numItems = " << numItems << std::endl;
    std::cout << "expected = 2 (v[1]=2.0f and v[3]=2.0f)" << std::endl;
    std::cout << (numItems == 2 ? "✓ PASS" : "✗ FAIL") << std::endl;
    std::cout << std::endl;

    // Additional test: count 3.0f
    auto count3 = countEqualItems(v, 3.0f);
    std::cout << "countEqualItems(v, 3.0f) = " << count3 << " (expected 1)" << std::endl;
    std::cout << (count3 == 1 ? "✓ PASS" : "✗ FAIL") << std::endl;

    // Additional test: count 5.0f (not in vector)
    auto count5 = countEqualItems(v, 5.0f);
    std::cout << "countEqualItems(v, 5.0f) = " << count5 << " (expected 0)" << std::endl;
    std::cout << (count5 == 0 ? "✓ PASS" : "✗ FAIL") << std::endl;

    // Test with int vector
    std::cout << "\n=== INT VECTOR ===" << std::endl;
    auto vi = std::vector{10, 20, 30, 20, 20, 40};
    std::cout << "vi = {10, 20, 30, 20, 20, 40}" << std::endl;
    auto countTwenty = countEqualItems(vi, 20);
    std::cout << "countEqualItems(vi, 20) = " << countTwenty << " (expected 3)" << std::endl;
    std::cout << (countTwenty == 3 ? "✓ PASS" : "✗ FAIL") << std::endl;

    return 0;
}
