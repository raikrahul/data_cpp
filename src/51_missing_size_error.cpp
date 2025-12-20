// 51_missing_size_error.cpp
// PROOF: abbreviated template requires size() - compile error if missing

#include <cstdio>

// =============================================================================
// CUSTOM CONTAINER WITHOUT size() - WILL CAUSE COMPILE ERROR
// =============================================================================
// MEMORY LAYOUT:
// MyBrokenContainer at 0x7FFF0000 (12 bytes):
//   0x7FFF0000: data[0] = 10 (4 bytes)
//   0x7FFF0004: data[1] = 20 (4 bytes)
//   0x7FFF0008: data[2] = 30 (4 bytes)
//
// HAS: operator[] ✓
// MISSING: size() ✗

struct MyBrokenContainer {
    int data[3] = {10, 20, 30};  // 3 ints × 4 bytes = 12 bytes at offset 0
    
    // operator[] EXISTS - returns reference to element
    // data[0]=10, data[1]=20, data[2]=30
    int& operator[](int i) { return data[i]; }
    const int& operator[](int i) const { return data[i]; }
    
    // size() INTENTIONALLY MISSING
    // NO: size_t size() const { return 3; }
};

// =============================================================================
// CUSTOM CONTAINER WITH size() - WILL COMPILE
// =============================================================================
// MEMORY LAYOUT: same as above but has size() method

struct MyWorkingContainer {
    int data[3] = {100, 200, 300};
    
    int& operator[](size_t i) { return data[i]; }
    const int& operator[](size_t i) const { return data[i]; }
    
    // size() EXISTS
    size_t size() const { return 3; }  // returns 3
};

// =============================================================================
// ABBREVIATED TEMPLATE - requires size() and operator[]
// =============================================================================

int countSmallerThan(const auto& items, auto toCompare) {
    int count = 0;
    for (size_t i = 0; i < items.size(); ++i) {  // ← calls items.size()
        if (items[i] < toCompare) {               // ← calls items.operator[]
            count++;
        }
    }
    return count;
}

int main() {
    // TEST 1: MyWorkingContainer - HAS size()
    // MEMORY at 0x7FFF1000:
    //   0x7FFF1000: data[0] = 100
    //   0x7FFF1004: data[1] = 200
    //   0x7FFF1008: data[2] = 300
    //
    // countSmallerThan(working, 250):
    // auto = MyWorkingContainer (deduced)
    // items.size() = 3 ✓ (method exists)
    // items[i] = int ✓
    // TRACE: 100<250✓, 200<250✓, 300<250✗ → count=2
    MyWorkingContainer working;
    int r1 = countSmallerThan(working, 250);
    printf("MyWorkingContainer{100,200,300}, 250 → count=%d (expected 2)\n", r1);
    
    // TEST 2: MyBrokenContainer - MISSING size()
    // UNCOMMENT TO SEE COMPILE ERROR:
    
    // MyBrokenContainer broken;
    // int r2 = countSmallerThan(broken, 25);
    // ERROR: 'const MyBrokenContainer' has no member named 'size'
    
    printf("\nUncomment lines 71-72 to see compile error for missing size()\n");
    
    return 0;
}
