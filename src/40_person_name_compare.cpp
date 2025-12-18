#include <iostream>
#include <string>
#include <cstring>
#include <functional>

// 40_person_name_compare.cpp
// Problem: Compare two Person objects by name
// Traps: pointer comparison, c_str() comparison, memcmp without size check

struct Person {
    std::string name;   // offset 0, size 32 (libstdc++), SSO threshold = 15 chars
    int age;            // offset 32, size 4
    // Total: 32 + 4 + 4(padding) = 40 bytes
};

// ┌────────────────────────────────────────────────────────────────────────────────────────┐
// │ TRAP #1: Comparing addresses of name members (ALWAYS FALSE for different objects)     │
// │ &p1.name = 0x7ffc_a000, &p2.name = 0x7ffc_a028 → different addresses → false          │
// │ This compares WHERE the strings are stored, not WHAT they contain                     │
// └────────────────────────────────────────────────────────────────────────────────────────┘
bool sameNameWRONG_AddressCompare(const Person& a, const Person& b) {
    // WRONG: compares string object addresses (ALWAYS different for different objects)
    return &a.name == &b.name;
}

// ┌────────────────────────────────────────────────────────────────────────────────────────┐
// │ TRAP #2: Comparing c_str() pointers (ALWAYS FALSE for different objects)              │
// │ SSO: a.name.c_str() = 0x7ffc_a010 (internal buffer)                                   │
// │      b.name.c_str() = 0x7ffc_a038 (internal buffer)                                   │
// │ Heap: a.name.c_str() = 0x5555_a000, b.name.c_str() = 0x5555_b000                     │
// │ Both cases: different pointers → false                                                │
// └────────────────────────────────────────────────────────────────────────────────────────┘
bool sameNameWRONG_CStrPointer(const Person& a, const Person& b) {
    // WRONG: compares buffer pointers (ALWAYS different for different objects)
    return a.name.c_str() == b.name.c_str();
}

// ┌────────────────────────────────────────────────────────────────────────────────────────┐
// │ TRAP #3: memcmp without size check (WRONG for different-length strings)               │
// │ a.name = "Alice" (5), b.name = "AliceX" (6)                                           │
// │ memcmp(a, b, 5) = 0 → WRONG! They're not equal                                        │
// │ Must check: a.name.size() == b.name.size() FIRST                                      │
// └────────────────────────────────────────────────────────────────────────────────────────┘
bool sameNameWRONG_MemcmpNoSize(const Person& a, const Person& b) {
    // WRONG: ignores length difference
    size_t len = std::min(a.name.size(), b.name.size());
    return std::memcmp(a.name.data(), b.name.data(), len) == 0;
}

// ┌────────────────────────────────────────────────────────────────────────────────────────┐
// │ CORRECT #1: Using operator== (BEST)                                                   │
// │ std::string::operator== checks size first (O(1)), then content (O(n))                │
// │ Early exit if sizes differ → efficient for different-length strings                  │
// └────────────────────────────────────────────────────────────────────────────────────────┘
bool sameNameCorrect_OperatorEq(const Person& a, const Person& b) {
    return a.name == b.name;
}

// ┌────────────────────────────────────────────────────────────────────────────────────────┐
// │ CORRECT #2: Using compare() method                                                    │
// │ a.name.compare(b.name) returns: 0 if equal, <0 if a<b, >0 if a>b                     │
// │ Equivalent to operator== for equality check                                          │
// └────────────────────────────────────────────────────────────────────────────────────────┘
bool sameNameCorrect_Compare(const Person& a, const Person& b) {
    return a.name.compare(b.name) == 0;
}

// ┌────────────────────────────────────────────────────────────────────────────────────────┐
// │ CORRECT #3: Using strcmp (C-style)                                                    │
// │ strcmp compares null-terminated strings byte by byte                                  │
// │ Returns 0 if equal, <0 if a<b, >0 if a>b                                             │
// │ Works for std::string via .c_str()                                                   │
// └────────────────────────────────────────────────────────────────────────────────────────┘
bool sameNameCorrect_Strcmp(const Person& a, const Person& b) {
    return std::strcmp(a.name.c_str(), b.name.c_str()) == 0;
}

// ┌────────────────────────────────────────────────────────────────────────────────────────┐
// │ CORRECT #4: memcmp WITH size check                                                    │
// │ Step 1: Check sizes equal                                                             │
// │ Step 2: memcmp the raw bytes                                                          │
// └────────────────────────────────────────────────────────────────────────────────────────┘
bool sameNameCorrect_MemcmpWithSize(const Person& a, const Person& b) {
    if (a.name.size() != b.name.size()) return false;
    return std::memcmp(a.name.data(), b.name.data(), a.name.size()) == 0;
}

// ┌────────────────────────────────────────────────────────────────────────────────────────┐
// │ ALTERNATIVE: Hash pre-filter (faster for mostly-different names)                      │
// │ Compute hash of each name, compare hashes first                                       │
// │ If hashes differ → definitely different (early exit)                                 │
// │ If hashes equal → might be same OR collision → verify with full compare             │
// │ Trade-off: O(n) hash compute + O(1) hash compare + possible O(n) verify              │
// └────────────────────────────────────────────────────────────────────────────────────────┘
bool sameNameAlt_HashPrefilter(const Person& a, const Person& b) {
    std::hash<std::string> hasher;
    if (hasher(a.name) != hasher(b.name)) return false;  // Definitely different
    return a.name == b.name;  // Verify (handles hash collisions)
}

void test_wrong_approaches() {
    std::cout << "=== WRONG APPROACHES (should all return false even for same names) ===\n";
    Person p1{"Alice", 30};
    Person p2{"Alice", 25};
    
    // TODO: Test wrong approaches and show WHY they fail
    // Print addresses to prove they're different
    std::cout << "&p1.name = " << static_cast<const void*>(&p1.name) << "\n";
    std::cout << "&p2.name = " << static_cast<const void*>(&p2.name) << "\n";
    std::cout << "p1.name.c_str() = " << static_cast<const void*>(p1.name.c_str()) << "\n";
    std::cout << "p2.name.c_str() = " << static_cast<const void*>(p2.name.c_str()) << "\n";
    
    // Prove they contain same content but different addresses
    std::cout << "Content p1.name = \"" << p1.name << "\"\n";
    std::cout << "Content p2.name = \"" << p2.name << "\"\n";
}

void test_correct_approaches() {
    std::cout << "\n=== CORRECT APPROACHES (should all return true for same names) ===\n";
    Person p1{"Alice", 30};
    Person p2{"Alice", 25};
    
    // TODO: Test each correct approach
    std::cout << "operator==: " << (p1.name == p2.name ? "true" : "false") << " (expected: true)\n";
    std::cout << "compare(): " << (p1.name.compare(p2.name) == 0 ? "true" : "false") << " (expected: true)\n";
    std::cout << "strcmp(): " << (std::strcmp(p1.name.c_str(), p2.name.c_str()) == 0 ? "true" : "false") << " (expected: true)\n";
}

void test_edge_cases() {
    std::cout << "\n=== EDGE CASES ===\n";
    
    // Empty names
    Person empty1{"", 0};
    Person empty2{"", 0};
    std::cout << "Empty names: " << (empty1.name == empty2.name ? "true" : "false") << " (expected: true)\n";
    
    // One empty
    Person alice{"Alice", 30};
    std::cout << "Alice vs empty: " << (alice.name == empty1.name ? "true" : "false") << " (expected: false)\n";
    
    // Long names (heap allocated, > 15 chars)
    Person long1{"VeryLongNameThatExceedsSSO", 30};
    Person long2{"VeryLongNameThatExceedsSSO", 25};
    std::cout << "Long names (heap): " << (long1.name == long2.name ? "true" : "false") << " (expected: true)\n";
    std::cout << "long1.c_str() = " << static_cast<const void*>(long1.name.c_str()) << "\n";
    std::cout << "long2.c_str() = " << static_cast<const void*>(long2.name.c_str()) << "\n";
    
    // Case sensitivity
    Person alice_upper{"ALICE", 30};
    std::cout << "Alice vs ALICE (case): " << (alice.name == alice_upper.name ? "true" : "false") << " (expected: false)\n";
}

void test_memcmp_trap() {
    std::cout << "\n=== MEMCMP TRAP (different lengths) ===\n";
    
    Person p1{"Alice", 30};
    Person p2{"AliceX", 25};
    
    size_t minLen = std::min(p1.name.size(), p2.name.size());
    int memcmpResult = std::memcmp(p1.name.data(), p2.name.data(), minLen);
    
    std::cout << "p1.name = \"" << p1.name << "\" (len=" << p1.name.size() << ")\n";
    std::cout << "p2.name = \"" << p2.name << "\" (len=" << p2.name.size() << ")\n";
    std::cout << "memcmp(p1,p2," << minLen << ") = " << memcmpResult << " (WRONG comparison!)\n";
    std::cout << "Correct: p1.name == p2.name = " << (p1.name == p2.name ? "true" : "false") << " (expected: false)\n";
}

int main() {
    std::cout << "=== 40_person_name_compare ===\n\n";
    
    std::cout << "sizeof(Person) = " << sizeof(Person) << " (expected: 40)\n";
    std::cout << "sizeof(std::string) = " << sizeof(std::string) << " (expected: 32)\n\n";
    
    test_wrong_approaches();
    test_correct_approaches();
    test_edge_cases();
    test_memcmp_trap();
    
    std::cout << "\n=== PREDICTED FAILURES ===\n";
    std::cout << "F1: &a.name == &b.name → compares object addresses, ALWAYS false ✗\n";
    std::cout << "F2: a.c_str() == b.c_str() → compares buffer pointers, ALWAYS false ✗\n";
    std::cout << "F3: memcmp without size check → \"Alice\" vs \"AliceX\" → WRONG equal ✗\n";
    std::cout << "F4: Hash only (no verify) → false positives on collisions ✗\n";
    std::cout << "F5: strcasecmp not available on all platforms → use tolower loop ✓\n";
    
    return 0;
}
