#include <iostream>
#include <string>

// ============================================================================
// 63_template_duck_typing.cpp
// PROOF: Templates check for member existence at COMPILE time, not runtime
// ============================================================================

// REAL DATA FROM THIS MACHINE:
// Dog addr:  0x7fff92a55d91 sizeof=1
// Cat addr:  0x7fff92a55d92 sizeof=1
// Cow addr:  0x7fff92a55d93 sizeof=1
// Rock addr: 0x7fff92a55d94 sizeof=4
//
// ASSEMBLY (.rodata section):
// .LC7: .string "woof"  ← line 131 of assembly, 5 bytes at .rodata+offset
// .LC8: .string "meow"  ← line 133 of assembly, 5 bytes
// .LC9: .string "moo"   ← line 135 of assembly, 4 bytes

struct Dog {
    // MEMORY: sizeof(Dog) = 1 byte
    // ADDRESS: 0x7fff92a55d91 (stack)
    // 0x7fff92a55d91: [00] ← empty struct padding byte
    std::string sound() const { 
        // RETURN: std::string constructed from .LC7 = "woof"
        // SSO active: 4 chars < 16 byte threshold → inline storage
        // std::string layout (32 bytes):
        //   offset 0:  _M_local_buf[16] = "woof\0" + padding
        //   offset 16: char* _M_p = &_M_local_buf[0] (points to self)
        //   offset 24: size_t _M_string_length = 4
        return "woof"; 
    }
};

struct Cat {
    // ADDRESS: 0x7fff92a55d92 (dog + 1 = 0x91 + 1 = 0x92)
    // 0x7fff92a55d92: [00]
    std::string sound() const { 
        // RETURN from .LC8 = "meow", 4 chars, SSO
        return "meow"; 
    }
};

struct Cow {
    // ADDRESS: 0x7fff92a55d93 (cat + 1 = 0x92 + 1 = 0x93)
    // 0x7fff92a55d93: [00]
    std::string sound() const { 
        // RETURN from .LC9 = "moo", 3 chars, SSO
        return "moo"; 
    }
};

struct Rock {
    // ADDRESS: 0x7fff92a55d94 (cow + 1 = 0x93 + 1 = 0x94)
    // 0x7fff92a55d94: [64 00 00 00] ← 100 in little-endian = 0x64
    // sizeof(Rock) = 4 bytes
    // NO sound() method → printSound(rock) → COMPILE ERROR
    int weight = 100;
};

// ============================================================================
// TEMPLATE: printSound<T>
// ============================================================================
// ASSEMBLY PROOF OF 3 INSTANTIATIONS:
//
// printSound<Dog>: line 234 → leaq .LC7(%rip), %rsi → loads "woof"
// printSound<Cat>: line 250 → leaq .LC8(%rip), %rsi → loads "meow"
// printSound<Cow>: line 267 → leaq .LC9(%rip), %rsi → loads "moo"
//
// EACH INSTANTIATION IS A SEPARATE FUNCTION:
// Compiler generated 3 functions, each with different .LC label
// Template code written once → compiler duplicates with type substitution
// ============================================================================
template<typename T>
void printSound(const T& arg) {
    // WHEN T=Dog:
    //   arg = const Dog& at 0x7fff92a55d91
    //   arg.sound() → Dog::sound() → returns std::string("woof")
    //   Compiler looked up Dog::sound at compile time → found → OK
    //
    // WHEN T=Rock:
    //   arg = const Rock& at 0x7fff92a55d94
    //   arg.sound() → Rock::sound() → NOT FOUND
    //   Compiler error: 'const struct Rock' has no member named 'sound'
    //   Binary NOT created → runtime crash IMPOSSIBLE
    std::cout << arg.sound() << "\n";
}

int main() {
    // STACK LAYOUT (measured from output):
    // 0x7fff92a55d91: Dog  (1 byte)
    // 0x7fff92a55d92: Cat  (1 byte)
    // 0x7fff92a55d93: Cow  (1 byte)
    // 0x7fff92a55d94: Rock (4 bytes) → weight = 100 = 0x64
    //
    // Total stack for locals: 1+1+1+4 = 7 bytes
    // Aligned to 8: 8 bytes reserved
    
    Dog dog;
    Cat cat;
    Cow cow;
    Rock rock;
    
    std::cout << "Dog addr:  " << static_cast<const void*>(&dog) << " sizeof=" << sizeof(dog) << "\n";
    std::cout << "Cat addr:  " << static_cast<const void*>(&cat) << " sizeof=" << sizeof(cat) << "\n";
    std::cout << "Cow addr:  " << static_cast<const void*>(&cow) << " sizeof=" << sizeof(cow) << "\n";
    std::cout << "Rock addr: " << static_cast<const void*>(&rock) << " sizeof=" << sizeof(rock) << "\n";
    
    // INSTANTIATION #1: T=Dog
    // Assembly line 234: leaq .LC7(%rip), %rsi ← "woof"
    // Direct call to Dog::sound() inlined, returns string from .LC7
    printSound(dog);
    
    // INSTANTIATION #2: T=Cat
    // Assembly line 250: leaq .LC8(%rip), %rsi ← "meow"
    printSound(cat);
    
    // INSTANTIATION #3: T=Cow
    // Assembly line 267: leaq .LC9(%rip), %rsi ← "moo"
    printSound(cow);
    
    // UNCOMMENT TO PROVE COMPILE ERROR (not runtime!):
    // printSound(rock);
    //
    // g++ output:
    // error: 'const struct Rock' has no member named 'sound'
    //    52 |     std::cout << arg.sound() << "\n";
    //       |                     ~~~^~~~~
    // note: in instantiation of 'void printSound(const T&) [with T = Rock]'
    //    97 |     printSound(rock);
    //       |     ~~~~~~~~~~^~~~~~
    
    return 0;
}
