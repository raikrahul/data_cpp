#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstddef>
#include <iomanip>
#include <cstdint>

// 01. BOILERPLATE: Define Struct
// Task: Confirm layout matches logic in step 01 (Derivation File).
// Expected Size: 4 (int) + 4 (float) + 32 (string) = 40 bytes (GCC).
struct Person {
    int age;
    float height;
    std::string name;
};

// 02. HELPER: Binary Printer
// Input: void* ptr, int size
// Logic: Loop i from 0 to size-1 -> Print byte in Hex -> Print Char if printable.
void dump_raw_memory(const void* ptr, size_t size) {
    const unsigned char* bytes = static_cast<const unsigned char*>(ptr);
    std::cout << "Offset | Hex      | Char | Interpretation\n";
    std::cout << "-------|----------|------|---------------\n";
    
    // Base address for relative calculation display (used in debug if needed, commented out to avoid warning)
    // uintptr_t base_addr = reinterpret_cast<uintptr_t>(ptr);

    for (size_t i = 0; i < size; ++i) {
        // 03. CALCULATION: Determine member overlap
        // 0-3: age
        // 4-7: height
        // 8-39: name (header + buffer)
        std::string label = "";
        if (i == 0) label = "<- age (start)";
        if (i == 4) label = "<- height (start)";
        if (i == 8) label = "<- string ptr/size (start)";
        if (i == 24) label = "<- SSO buffer start (likely GCC)"; // GCC specific offset for SSO buffer

        printf(" +%-2zu   | %02X       |  %c   | %s\n", 
               i, bytes[i], (isprint(bytes[i]) ? bytes[i] : '.'), label.c_str());
    }
    std::cout << "-----------------------------------------\n";
}

int main() {
    std::cout << "=== 37_struct_class_init ===\n\n";

    // 04. DATA POPULATION: Real values
    // Age: 21 (0x15)
    // Height: 1.76 (0x3FE147AE calculated in Step 02 of MD)
    // Name: "Peter" (ASCII: 50 65 74 65 72)
    
    std::cout << "1. INSTANTIATION: Person{21, 1.76, \"Peter\"}\n";
    auto myNeighbor = Person{21, 1.76f, "Peter"};

    // 05. VERIFICATION: Size Check
    // Calculation: If size != 40 (on standard 64-bit GCC), something is different (padding/lib version).
    std::cout << "Sizeof(Person): " << sizeof(Person) << " (Expected: 40 on GCC/Linux)\n";
    std::cout << "Offset(age):    " << offsetof(Person, age) << "\n";
    std::cout << "Offset(height): " << offsetof(Person, height) << "\n";
    std::cout << "Offset(name):   " << offsetof(Person, name) << "\n";

    // 06. INSPECTION: Brute Force Memory Dump
    // Trigger for User: Look at offset +4. Do you see AE 47 E1 3F?
    // Trigger for User: Look at offset +24. Do you see 50 65 74 65 72?
    std::cout << "\nMemory Dump of myNeighbor:\n";
    dump_raw_memory(&myNeighbor, sizeof(Person));

    // 07. TRICK EXPOSURE: Pointer arithmetic
    // If we overwrite the age using raw bytes, does it work?
    // Logic: int* p_age = (int*)&myNeighbor; *p_age = 0x16; (22)
    int* p_age = reinterpret_cast<int*>(&myNeighbor);
    std::cout << "\n2. MODIFICATION: *p_age = 22 (via pointer overwrite)\n";
    *p_age = 22; // Brute force memory write
    
    // Verify modification
    std::cout << "myNeighbor.age: " << myNeighbor.age << " (Expected: 22)\n";
    std::cout << "Raw check at offset 0: " << std::hex << static_cast<int>(*reinterpret_cast<unsigned char*>(p_age)) << std::dec << "\n";

    // 08. SSO vs HEAP Verification
    std::cout << "\n3. STRING MECHANICS (SSO vs HEAP):\n";
    const char* internal_ptr = myNeighbor.name.data();
    uintptr_t struct_start = reinterpret_cast<uintptr_t>(&myNeighbor);
    uintptr_t buffer_addr = reinterpret_cast<uintptr_t>(internal_ptr);
    
    std::cout << "Struct Address: " << static_cast<const void*>(&myNeighbor) << "\n";
    std::cout << "String Buffer:  " << static_cast<const void*>(internal_ptr) << "\n";
    
    if (buffer_addr >= struct_start && buffer_addr < struct_start + sizeof(Person)) {
        std::cout << "-> Buffer is INSIDE struct (SSO Active) [Distance=" << (buffer_addr - struct_start) << " bytes from start]\n";
    } else {
        std::cout << "-> Buffer is OUTSIDE struct (Heap Allocated)\n";
    }

    // 09. FLOAT BIT PATTERN CHECK
    std::cout << "\n4. FLOAT BIT PATTERN (1.76):\n";
    float h = 1.76f;
    uint32_t* h_bits = reinterpret_cast<uint32_t*>(&h);
    std::cout << "1.76f bits: 0x" << std::hex << *h_bits << std::dec << "\n";
    std::cout << "Expected:   0x3FE147AE\n";

    // 10. FAILURE PREDICTION: NARROWING
    // Uncommenting line below causes compile error
    // Person fail = {21.9, 1.76f, "Fail"}; 
    std::cout << "\n[Note: Uncommenting narrowing conversion test would break build]\n";

    return 0;
}
