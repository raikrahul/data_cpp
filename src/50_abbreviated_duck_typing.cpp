// 50_abbreviated_duck_typing.cpp
// PROOF: abbreviated template uses compile-time duck typing
// auto param requires type with .size() and operator[] → caller must provide

#include <cstdio>
#include <vector>
#include <array>
#include <string>

// =============================================================================
// ABBREVIATED TEMPLATE: countSmallerThan
// =============================================================================
// CONVERSION FROM:
//   template<typename T1, typename T2>
//   int countSmallerThan(const vector<T1>& items, T2 toCompare)
// TO:
//   int countSmallerThan(const auto& items, auto toCompare)
//
// STEP 1: deleted "template<typename T1, typename T2>" line
// STEP 2: replaced "const vector<T1>&" → "const auto&"
// STEP 3: replaced "T2" → "auto"
// STEP 4: body has no T1/T2 references → no changes needed
//
// DUCK TYPING CHECK:
// items.size() → requires size() method
// items[i] → requires operator[]
// items[i] < toCompare → requires operator< between element and toCompare
//
// WHICH TYPES WORK:
// vector<int>        → size() ✓, operator[] ✓, int < int ✓
// array<float,5>     → size() ✓, operator[] ✓, float < float ✓
// string             → size() ✓, operator[] ✓, char < char ✓
// int                → size() ✗ → COMPILE ERROR
// float*             → size() ✗ → COMPILE ERROR

int countSmallerThan(const auto& items, auto toCompare) {
    // items at 0x7FFF0000 (stack reference, 8 bytes = pointer to actual container)
    // toCompare at 0x7FFF0008 (stack copy, 4 bytes for int, 8 bytes for double)
    //
    // MEMORY LAYOUT for vector<int>{10,20,30,40,50}:
    // 0x7FFF0000: items (reference) → points to 0x7FFF0020
    // 0x7FFF0020: vector object (24 bytes on stack):
    //   0x7FFF0020: begin ptr → 0xA000 (heap)
    //   0x7FFF0028: end ptr   → 0xA014 (5 ints × 4 = 20 bytes from begin)
    //   0x7FFF0030: capacity  → 0xA014 (capacity = size = 5)
    // 0xA000: heap array [10, 20, 30, 40, 50]
    //   0xA000: 10 (4 bytes)
    //   0xA004: 20 (4 bytes)
    //   0xA008: 30 (4 bytes)
    //   0xA00C: 40 (4 bytes)
    //   0xA010: 50 (4 bytes)
    
    int count = 0;  // count at -4(%rbp) = 0
    
    // items.size() = 5
    // LOOP: i ∈ {0, 1, 2, 3, 4}
    // TRACE for items={10,20,30,40,50}, toCompare=35:
    //   i=0: items[0]=10 < 35 ✓ → count=0+1=1
    //   i=1: items[1]=20 < 35 ✓ → count=1+1=2
    //   i=2: items[2]=30 < 35 ✓ → count=2+1=3
    //   i=3: items[3]=40 < 35 ✗ → count=3
    //   i=4: items[4]=50 < 35 ✗ → count=3
    // return 3
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i] < toCompare) {
            count++;
        }
    }
    return count;  // movl -4(%rbp), %eax → return count in %eax
}

int main() {
    // ==========================================================================
    // TEST 1: vector<int> - 5 elements, toCompare=35
    // ==========================================================================
    // MEMORY at 0x7FFF1000:
    // v1 = vector<int> at stack 0x7FFF1000 (24 bytes)
    //   0x7FFF1000: begin = 0xB000
    //   0x7FFF1008: end   = 0xB014 (5 × 4 = 20 bytes)
    //   0x7FFF1010: cap   = 0xB014
    // HEAP at 0xB000: [10, 20, 30, 40, 50]
    //   0xB000=10, 0xB004=20, 0xB008=30, 0xB00C=40, 0xB010=50
    //
    // countSmallerThan(v1, 35):
    // auto = vector<int> (deduced)
    // items.size() = 5 ✓
    // items[i] = int ✓
    // int < int ✓
    // TRACE: 10<35✓, 20<35✓, 30<35✓, 40<35✗, 50<35✗ → count=3
    std::vector<int> v1 = {10, 20, 30, 40, 50};
    int r1 = countSmallerThan(v1, 35);
    printf("vector<int>{10,20,30,40,50}, 35 → count=%d (expected 3)\n", r1);
    
    // ==========================================================================
    // TEST 2: array<float,6> - 6 elements, toCompare=2.5f
    // ==========================================================================
    // MEMORY at 0x7FFF1020:
    // a1 = array<float,6> at stack 0x7FFF1020 (24 bytes = 6 × 4)
    //   0x7FFF1020: 1.0f
    //   0x7FFF1024: 1.5f
    //   0x7FFF1028: 2.0f
    //   0x7FFF102C: 2.5f
    //   0x7FFF1030: 3.0f
    //   0x7FFF1034: 3.5f
    //
    // countSmallerThan(a1, 2.5f):
    // auto = array<float,6> (deduced)
    // items.size() = 6 ✓
    // items[i] = float ✓
    // float < float ✓
    // TRACE: 1.0<2.5✓, 1.5<2.5✓, 2.0<2.5✓, 2.5<2.5✗, 3.0<2.5✗, 3.5<2.5✗ → count=3
    std::array<float, 6> a1 = {1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f};
    int r2 = countSmallerThan(a1, 2.5f);
    printf("array<float,6>{1.0,1.5,2.0,2.5,3.0,3.5}, 2.5f → count=%d (expected 3)\n", r2);
    
    // ==========================================================================
    // TEST 3: string - 5 chars, toCompare='m'
    // ==========================================================================
    // MEMORY at 0x7FFF1040:
    // s1 = string at stack 0x7FFF1040 (32 bytes SSO)
    //   0x7FFF1040: SSO buffer "hello\0" (6 bytes used, 16 capacity)
    //   chars: 'h'=104, 'e'=101, 'l'=108, 'l'=108, 'o'=111
    //
    // countSmallerThan(s1, 'm'):
    // auto = string (deduced)
    // items.size() = 5 ✓
    // items[i] = char ✓
    // char < char ✓ (ASCII comparison)
    // 'm' = 109 (ASCII)
    // TRACE: 'h'=104<109✓, 'e'=101<109✓, 'l'=108<109✓, 'l'=108<109✓, 'o'=111<109✗
    // count = 4
    std::string s1 = "hello";
    int r3 = countSmallerThan(s1, 'm');
    printf("string{\"hello\"}, 'm'(109) → count=%d (expected 4: h=104,e=101,l=108,l=108 all <109)\n", r3);
    
    // ==========================================================================
    // TEST 4: EDGE CASE - empty vector
    // ==========================================================================
    // MEMORY at 0x7FFF1060:
    // v2 = vector<int> at stack 0x7FFF1060 (24 bytes)
    //   0x7FFF1060: begin = nullptr (or same as end)
    //   0x7FFF1068: end   = nullptr
    //   0x7FFF1070: cap   = nullptr
    //
    // countSmallerThan(v2, 100):
    // items.size() = 0
    // LOOP: i < 0 → never enters loop
    // return 0 immediately
    std::vector<int> v2 = {};
    int r4 = countSmallerThan(v2, 100);
    printf("vector<int>{}, 100 → count=%d (expected 0)\n", r4);
    
    // ==========================================================================
    // TEST 5: ALL elements smaller
    // ==========================================================================
    // v3 = {1,2,3,4,5}, toCompare = 100
    // TRACE: 1<100✓, 2<100✓, 3<100✓, 4<100✓, 5<100✓ → count=5
    std::vector<int> v3 = {1, 2, 3, 4, 5};
    int r5 = countSmallerThan(v3, 100);
    printf("vector<int>{1,2,3,4,5}, 100 → count=%d (expected 5)\n", r5);
    
    // ==========================================================================
    // TEST 6: NO elements smaller
    // ==========================================================================
    // v4 = {100,200,300}, toCompare = 50
    // TRACE: 100<50✗, 200<50✗, 300<50✗ → count=0
    std::vector<int> v4 = {100, 200, 300};
    int r6 = countSmallerThan(v4, 50);
    printf("vector<int>{100,200,300}, 50 → count=%d (expected 0)\n", r6);
    
    // ==========================================================================
    // TEST 7: LARGE SCALE - 1000 elements
    // ==========================================================================
    // v5 = {0,1,2,...,999}, toCompare = 500
    // Elements 0-499 are < 500 → count = 500
    // Loop iterations = 1000
    // Memory = 1000 × 4 = 4000 bytes
    // Cache lines = 4000 / 64 = 62.5 → 63 cache line touches
    std::vector<int> v5(1000);
    for (size_t i = 0; i < 1000; ++i) v5[i] = static_cast<int>(i);  // {0,1,2,...,999}
    int r7 = countSmallerThan(v5, 500);
    printf("vector<int>{0..999}, 500 → count=%d (expected 500)\n", r7);
    
    // ==========================================================================
    // COMPILE ERROR TEST (commented out):
    // ==========================================================================
    // int x = 42;
    // countSmallerThan(x, 10);  // ERROR: 'int' has no member 'size'
    //
    // float* ptr = nullptr;
    // countSmallerThan(ptr, 1.0f);  // ERROR: no 'size' member
    
    return 0;
}
