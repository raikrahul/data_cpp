// 40_person_name_compare_worksheet.cpp
// ROAST: You typed == and hoped. You never instrumented. You don't know where bytes live.
// This file has boilerplate. YOU fill in the blanks. YOU calculate. YOU trace memory.

#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iterator>

struct Person {
    std::string name;  // offset 0, size 32 (libstdc++)
    int id;            // offset 32, size 4
    // padding 4 bytes to align struct to 8
    // Total: 40 bytes
};

// ┌──────────────────────────────────────────────────────────────────────────────────────────┐
// │ DIAGRAM 1: Person object memory layout (SSO active, name="Alice")                        │
// │ Stack Address: 0x7ffc_c000                                                               │
// │                                                                                          │
// │ ┌─────────┬──────────────────────┬─────────────────┬───────────────────────────────────┐ │
// │ │ Offset  │ Bytes (hex)          │ Field           │ YOUR CALCULATION                  │ │
// │ ├─────────┼──────────────────────┼─────────────────┼───────────────────────────────────┤ │
// │ │ 0x00    │ ?? ?? ?? ?? ?? ?? ?? │ name._M_string  │ TODO: What is string length?      │ │
// │ │ 0x08    │ ?? ?? ?? ?? ?? ?? ?? │ name._M_data ptr│ TODO: Where does this point?      │ │
// │ │ 0x10    │ ?? ?? ?? ?? ??       │ SSO buffer[0:4] │ TODO: What chars are here?        │ │
// │ │ 0x15    │ ?? ??                │ SSO buffer[5:6] │ TODO: Is there a null terminator? │ │
// │ │ 0x20    │ ?? ?? ?? ??          │ id              │ TODO: What is id value in hex?    │ │
// │ │ 0x24    │ ?? ?? ?? ??          │ padding         │ TODO: Why 4 bytes padding?        │ │
// │ └─────────┴──────────────────────┴─────────────────┴───────────────────────────────────┘ │
// │                                                                                          │
// │ WHY SSO: "Alice" has length = ___. SSO threshold = 15. ___ < 15 → fits in SSO buffer.   │
// │ WHY _M_data: When SSO active, _M_data points to offset ___ within same object.          │
// └──────────────────────────────────────────────────────────────────────────────────────────┘

void dump_person_memory(const Person& p, const char* label) {
    std::cout << "=== " << label << " ===\n";
    std::cout << "Address of Person: " << static_cast<const void*>(&p) << "\n";
    std::cout << "Address of name:   " << static_cast<const void*>(&p.name) << "\n";
    std::cout << "Address of id:     " << static_cast<const void*>(&p.id) << "\n";
    std::cout << "name.c_str():      " << static_cast<const void*>(p.name.c_str()) << "\n";
    std::cout << "name.size():       " << p.name.size() << "\n";
    std::cout << "name.capacity():   " << p.name.capacity() << "\n";
    
    // Raw memory dump - 40 bytes
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&p);
    std::cout << "Raw bytes (40): ";
    for (size_t i = 0; i < sizeof(Person); ++i) {
        printf("%02x ", bytes[i]);
        if ((i + 1) % 8 == 0) std::cout << "| ";
    }
    std::cout << "\n\n";
}

// ┌──────────────────────────────────────────────────────────────────────────────────────────┐
// │ DIAGRAM 2: Two Person objects on stack                                                   │
// │                                                                                          │
// │ Stack grows DOWN. p1 allocated first, p2 allocated second.                               │
// │                                                                                          │
// │    Higher addresses                                                                      │
// │    ┌────────────────────────────────────────────────────────────────────────┐            │
// │    │ 0x7ffc_c050: [p2.name SSO buffer] [p2.id] [pad]                        │            │
// │    │              "Alice\0"             42      ????                         │            │
// │    ├────────────────────────────────────────────────────────────────────────┤            │
// │    │ 0x7ffc_c028: &p2.name.c_str() → points to 0x7ffc_c0??                  │            │
// │    │              TODO: Calculate exact offset from p2 base                  │            │
// │    ├────────────────────────────────────────────────────────────────────────┤            │
// │    │ 0x7ffc_c000: [p1.name SSO buffer] [p1.id] [pad]                        │            │
// │    │              "Alice\0"             30      ????                         │            │
// │    ├────────────────────────────────────────────────────────────────────────┤            │
// │    │ 0x7ffc_bfd8: &p1.name.c_str() → points to 0x7ffc_c0??                  │            │
// │    │              TODO: Calculate exact offset from p1 base                  │            │
// │    └────────────────────────────────────────────────────────────────────────┘            │
// │    Lower addresses                                                                       │
// │                                                                                          │
// │ QUESTION: If &p1 = 0x7ffc_c000 and &p2 = 0x7ffc_c028, what is the distance?             │
// │ YOUR CALCULATION: 0x7ffc_c028 - 0x7ffc_c000 = 0x___ = ___ bytes                         │
// │ EXPECTED: sizeof(Person) = ___ bytes                                                    │
// │                                                                                          │
// │ TRAP CHECK: If you compare &p1.name with &p2.name, what do you get?                     │
// │ YOUR CALCULATION: 0x7ffc_c000 == 0x7ffc_c028 → ___ (true/false)                         │
// │                                                                                          │
// │ TRAP CHECK: If you compare p1.name.c_str() with p2.name.c_str(), what do you get?       │
// │ YOUR CALCULATION: 0x7ffc_c0?? == 0x7ffc_c0?? → ___ (true/false)                         │
// │                                                                                          │
// │ CORRECT CHECK: If you compare p1.name content with p2.name content, what do you get?    │
// │ YOUR CALCULATION: "Alice"[0..4] vs "Alice"[0..4] → ___                                  │
// └──────────────────────────────────────────────────────────────────────────────────────────┘

int main() {
    std::cout << "sizeof(Person) = " << sizeof(Person) << "\n";
    std::cout << "sizeof(std::string) = " << sizeof(std::string) << "\n";
    std::cout << "alignof(Person) = " << alignof(Person) << "\n\n";
    
    // ════════════════════════════════════════════════════════════════════════════════════════
    // STEP 1: Create p1
    // YOU CALCULATE: What bytes get written where?
    // ════════════════════════════════════════════════════════════════════════════════════════
    Person p1{"Alice", 30};
    dump_person_memory(p1, "p1: Alice, 30");
    
    // TODO: After seeing the dump, fill in:
    // p1 is at address: 0x________________
    // p1.name.c_str() is at: 0x________________
    // Distance from &p1 to p1.name.c_str(): ___ bytes
    // Is c_str() inside p1? (SSO check): ___
    
    // ════════════════════════════════════════════════════════════════════════════════════════
    // STEP 2: Create p2 with SAME name content
    // YOU CALCULATE: Are the addresses same or different?
    // ════════════════════════════════════════════════════════════════════════════════════════
    Person p2{"Alice", 42};
    dump_person_memory(p2, "p2: Alice, 42");
    
    // TODO: After seeing the dump, fill in:
    // p2 is at address: 0x________________
    // p2.name.c_str() is at: 0x________________
    // &p1.name == &p2.name: 0x________ == 0x________ → ___
    // p1.name.c_str() == p2.name.c_str(): 0x________ == 0x________ → ___
    
    // ════════════════════════════════════════════════════════════════════════════════════════
    // STEP 3: YOUR COMPARISON IMPLEMENTATIONS
    // Write the comparison. Run. See if it matches your prediction.
    // ════════════════════════════════════════════════════════════════════════════════════════
    
    std::cout << "\n=== YOUR COMPARISONS ===\n";
    
    // WRONG APPROACH 1: Address of name member
    // YOUR PREDICTION before running: ___ (true/false)
    // YOUR CODE HERE:
    bool wrong1 = false;  // TODO: Replace with &p1.name == &p2.name
    std::cout << "&p1.name == &p2.name: " << (wrong1 ? "true" : "false") 
              << " [YOUR PREDICTION: ___]\n";
    
    // WRONG APPROACH 2: c_str() pointer comparison
    // YOUR PREDICTION before running: ___ (true/false)
    // YOUR CODE HERE:
    bool wrong2 = false;  // TODO: Replace with p1.name.c_str() == p2.name.c_str()
    std::cout << "p1.c_str() == p2.c_str(): " << (wrong2 ? "true" : "false") 
              << " [YOUR PREDICTION: ___]\n";
    
    // CORRECT APPROACH: Content comparison
    // YOUR PREDICTION before running: ___ (true/false)
    // YOUR CODE HERE:
    bool correct = false;  // TODO: Replace with p1.name == p2.name
    std::cout << "p1.name == p2.name: " << (correct ? "true" : "false") 
              << " [YOUR PREDICTION: ___]\n";
    
    // ════════════════════════════════════════════════════════════════════════════════════════
    // STEP 4: LONG NAME (forces heap allocation)
    // YOU CALCULATE: Where does c_str() point now? Inside struct or heap?
    // ════════════════════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== LONG NAME (HEAP) ===\n";
    Person p3{"ThisNameIsLongerThanFifteenChars", 50};
    dump_person_memory(p3, "p3: Long name");
    
    // TODO: After seeing the dump, fill in:
    // p3.name.c_str() is at: 0x________________
    // &p3 is at: 0x________________
    // Is c_str() inside p3 range [&p3 .. &p3+40]? ___
    // If NO → heap allocated. WHY? name.length = ___ > 15 (SSO threshold)
    
    Person p4{"ThisNameIsLongerThanFifteenChars", 60};
    dump_person_memory(p4, "p4: Same long name");
    
    // TODO: Fill in:
    // p3.name.c_str(): 0x________________ (heap address starts with 0x5...)
    // p4.name.c_str(): 0x________________ (DIFFERENT heap address!)
    // p3.name.c_str() == p4.name.c_str(): 0x________ == 0x________ → ___ (true/false)
    // p3.name == p4.name (content): ___
    
    // ════════════════════════════════════════════════════════════════════════════════════════
    // STEP 5: MEMCMP TRAP
    // YOU CALCULATE: What happens with different-length strings?
    // ════════════════════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== MEMCMP TRAP ===\n";
    Person pShort{"Alice", 1};
    Person pLong{"AliceX", 2};
    
    std::cout << "pShort.name = \"" << pShort.name << "\" (len=" << pShort.name.size() << ")\n";
    std::cout << "pLong.name = \"" << pLong.name << "\" (len=" << pLong.name.size() << ")\n";
    
    // YOUR CALCULATION:
    // min(pShort.name.size(), pLong.name.size()) = min(___, ___) = ___
    // memcmp compares first ___ bytes: "Alice" vs "Alice" → equal? ___
    // But strings are actually equal? ___ (NO! different lengths!)
    
    size_t minLen = 0;  // TODO: Calculate min length
    int memcmpResult = 0;  // TODO: Call memcmp with minLen
    
    std::cout << "memcmp(pShort, pLong, " << minLen << ") = " << memcmpResult << "\n";
    std::cout << "TRAP: memcmp says 0 (equal) but strings are DIFFERENT!\n";
    std::cout << "Correct: pShort.name == pLong.name = " 
              << (pShort.name == pLong.name ? "true" : "false") << "\n";
    
    // ════════════════════════════════════════════════════════════════════════════════════════
    // STEP 6: COPY_IF DEMONSTRATION
    // YOU SEE: Does copy_if copy bytes or just reference?
    // ════════════════════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== COPY_IF DEMONSTRATION ===\n";
    
    // Source data
    struct PersonAge { std::string name; int age; };
    std::vector<PersonAge> source = {
        {"Alice", 15},
        {"Bob", 25},
        {"Carol", 18},
        {"Dave", 30},
        {"Eve", 12}
    };
    
    std::cout << "SOURCE (before copy_if):\n";
    for (size_t i = 0; i < source.size(); ++i) {
        std::cout << "  source[" << i << "] @ " << static_cast<const void*>(&source[i])
                  << " name.c_str()=" << static_cast<const void*>(source[i].name.c_str())
                  << " age=" << source[i].age << "\n";
    }
    
    // Destination - will receive copies
    std::vector<PersonAge> result;
    
    // copy_if: copies elements where age < 20
    std::copy_if(source.begin(), source.end(), std::back_inserter(result),
        [](const PersonAge& p) { return p.age < 20; });
    
    std::cout << "\nRESULT (after copy_if with predicate age < 20):\n";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "  result[" << i << "] @ " << static_cast<const void*>(&result[i])
                  << " name.c_str()=" << static_cast<const void*>(result[i].name.c_str())
                  << " age=" << result[i].age << "\n";
    }
    
    std::cout << "\nADDRESS COMPARISON (proves COPY happened):\n";
    std::cout << "  &source[0] = " << static_cast<const void*>(&source[0]) << "\n";
    std::cout << "  &result[0] = " << static_cast<const void*>(&result[0]) << "\n";
    std::cout << "  &source[0] == &result[0]? " 
              << (&source[0] == &result[0] ? "YES (same)" : "NO (DIFFERENT → COPY)") << "\n";
    
    std::cout << "\nBYTE COUNT:\n";
    std::cout << "  sizeof(PersonAge) = " << sizeof(PersonAge) << " bytes\n";
    std::cout << "  Elements copied = " << result.size() << "\n";
    std::cout << "  Total bytes copied = " << result.size() << " × " << sizeof(PersonAge) 
              << " = " << result.size() * sizeof(PersonAge) << " bytes\n";
    
    // Modify source - does result change?
    std::cout << "\nMODIFY SOURCE: source[0].age = 99\n";
    source[0].age = 99;
    std::cout << "  source[0].age = " << source[0].age << "\n";
    std::cout << "  result[0].age = " << result[0].age << " (UNCHANGED → proves independent copy)\n";
    
    return 0;
}

// ┌──────────────────────────────────────────────────────────────────────────────────────────┐
// │ AFTER RUNNING: Fill in your answers                                                      │
// │                                                                                          │
// │ Q1: What is sizeof(Person)?           Answer: ___ bytes                                  │
// │ Q2: What is sizeof(std::string)?      Answer: ___ bytes                                  │
// │ Q3: For "Alice", is SSO active?       Answer: ___ (yes/no), because length = ___ < 15   │
// │ Q4: For "ThisNameIs...", is SSO active? Answer: ___ (yes/no), because length = ___ > 15 │
// │ Q5: Why does &p1.name == &p2.name return false?                                         │
// │     Answer: Compares __________ addresses, not __________                                │
// │ Q6: Why does p1.name.c_str() == p2.name.c_str() return false?                           │
// │     Answer: SSO buffers are at __________ locations inside different __________         │
// │ Q7: Why does p1.name == p2.name return true?                                            │
// │     Answer: Compares __________, byte by byte, 'A'=='A', 'l'=='l', etc.                 │
// │ Q8: Why is memcmp dangerous without size check?                                         │
// │     Answer: "Alice" (len=5) vs "AliceX" (len=6), memcmp(5) = 0 but ___ are different    │
// └──────────────────────────────────────────────────────────────────────────────────────────┘
