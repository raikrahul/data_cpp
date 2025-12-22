// 73_variant_animal_visitor.cpp
// VARIANT VERSION: Animal (Horse, Cat, Dog) with makeSound()
// NO VIRTUAL, NO VPTR, NO VTABLE → uses std::variant + std::visit

#include <iostream>
#include <variant>

// ═══════════════════════════════════════════════════════════════════════════
// AXIOM 1: Each animal is a separate struct (no inheritance)
// ═══════════════════════════════════════════════════════════════════════════

struct Horse {
    int speed;      // = 60 km/h
    int weight;     // = 500 kg
    // sizeof(Horse) = 8 bytes (4 + 4)
};

struct Cat {
    int lives;      // = 9
    int weight;     // = 5 kg
    // sizeof(Cat) = 8 bytes (4 + 4)
};

struct Dog {
    int loyalty;    // = 100
    int weight;     // = 30 kg
    // sizeof(Dog) = 8 bytes (4 + 4)
};

// ═══════════════════════════════════════════════════════════════════════════
// AXIOM 2: Variant holds ONE of the types at a time
// ═══════════════════════════════════════════════════════════════════════════
//
// sizeof(std::variant<Horse, Cat, Dog>) = max(sizeof(Horse), sizeof(Cat), sizeof(Dog)) + index
//                                       = max(8, 8, 8) + 8 (alignment padding + index)
//                                       = 16 bytes (typically)
//
// Memory layout of variant:
// ┌────────────────────────────────────────────────────────────────────────┐
// │ Offset │ Size │ Content                                                │
// ├────────┼──────┼────────────────────────────────────────────────────────┤
// │ 0      │ 8    │ Data storage (Horse OR Cat OR Dog)                     │
// │ 8      │ 8    │ Index: 0=Horse, 1=Cat, 2=Dog (+ padding)               │
// └────────────────────────────────────────────────────────────────────────┘

using Animal = std::variant<Horse, Cat, Dog>;

// ═══════════════════════════════════════════════════════════════════════════
// AXIOM 3: Free function makeSound() with overloads (not member function)
// ═══════════════════════════════════════════════════════════════════════════
//
// Overload resolution at COMPILE TIME (not runtime vtable lookup)
// Compiler sees: makeSound(const Horse&) → picks first overload
// Compiler sees: makeSound(const Cat&) → picks second overload
// Compiler sees: makeSound(const Dog&) → picks third overload

void makeSound(const Horse& h) {
    // h.speed = 60, h.weight = 500
    std::cout << "Horse (speed=" << h.speed << ", weight=" << h.weight 
              << ") says: NEIGH!\n";
}

void makeSound(const Cat& c) {
    // c.lives = 9, c.weight = 5
    std::cout << "Cat (lives=" << c.lives << ", weight=" << c.weight 
              << ") says: MEOW!\n";
}

void makeSound(const Dog& d) {
    // d.loyalty = 100, d.weight = 30
    std::cout << "Dog (loyalty=" << d.loyalty << ", weight=" << d.weight 
              << ") says: WOOF!\n";
}

// ═══════════════════════════════════════════════════════════════════════════
// AXIOM 4: Visitor struct with operator() overloads
// ═══════════════════════════════════════════════════════════════════════════
//
// std::visit calls visitor.operator()(actual_type)
// Compiler generates jump table (or if-else chain) based on variant index

struct SoundVisitor {
    // operator() for Horse
    void operator()(const Horse& h) const {
        makeSound(h);
    }
    
    // operator() for Cat
    void operator()(const Cat& c) const {
        makeSound(c);
    }
    
    // operator() for Dog
    void operator()(const Dog& d) const {
        makeSound(d);
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// AXIOM 5: Generic lambda as visitor (C++14+)
// ═══════════════════════════════════════════════════════════════════════════
//
// [](auto&& animal) { makeSound(animal); }
// 
// Compiler instantiates 3 versions:
//   [](const Horse& animal) { makeSound(animal); }  → calls makeSound(Horse&)
//   [](const Cat& animal) { makeSound(animal); }    → calls makeSound(Cat&)
//   [](const Dog& animal) { makeSound(animal); }    → calls makeSound(Dog&)

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // ═══════════════════════════════════════════════════════════════════════
    // STEP 1: Check sizes (no vptr!)
    // ═══════════════════════════════════════════════════════════════════════
    std::cout << "sizeof(Horse) = " << sizeof(Horse) << "\n";
    std::cout << "sizeof(Cat) = " << sizeof(Cat) << "\n";
    std::cout << "sizeof(Dog) = " << sizeof(Dog) << "\n";
    std::cout << "sizeof(Animal) = " << sizeof(Animal) << "\n";
    // Expected: Horse=8, Cat=8, Dog=8, Animal=16 (or 12)
    // NO vptr → structs are pure data
    
    std::cout << "\n";
    
    // ═══════════════════════════════════════════════════════════════════════
    // STEP 2: Create variant holding Horse
    // ═══════════════════════════════════════════════════════════════════════
    //
    // Memory at &a1:
    // ┌────────────────────────────────────────────┐
    // │ Offset 0: speed=60, weight=500 (8 bytes)   │
    // │ Offset 8: index=0 (Horse)                  │
    // └────────────────────────────────────────────┘
    //
    Animal a1 = Horse{60, 500};
    std::cout << "a1 index = " << a1.index() << " (0=Horse)\n";
    
    // ═══════════════════════════════════════════════════════════════════════
    // STEP 3: Create variant holding Cat
    // ═══════════════════════════════════════════════════════════════════════
    //
    // Memory at &a2:
    // ┌────────────────────────────────────────────┐
    // │ Offset 0: lives=9, weight=5 (8 bytes)      │
    // │ Offset 8: index=1 (Cat)                    │
    // └────────────────────────────────────────────┘
    //
    Animal a2 = Cat{9, 5};
    std::cout << "a2 index = " << a2.index() << " (1=Cat)\n";
    
    // ═══════════════════════════════════════════════════════════════════════
    // STEP 4: Create variant holding Dog
    // ═══════════════════════════════════════════════════════════════════════
    //
    // Memory at &a3:
    // ┌────────────────────────────────────────────┐
    // │ Offset 0: loyalty=100, weight=30 (8 bytes) │
    // │ Offset 8: index=2 (Dog)                    │
    // └────────────────────────────────────────────┘
    //
    Animal a3 = Dog{100, 30};
    std::cout << "a3 index = " << a3.index() << " (2=Dog)\n";
    
    std::cout << "\n=== Using SoundVisitor struct ===\n";
    
    // ═══════════════════════════════════════════════════════════════════════
    // STEP 5: std::visit with visitor struct
    // ═══════════════════════════════════════════════════════════════════════
    //
    // std::visit(SoundVisitor{}, a1):
    //   1. Read a1.index() = 0
    //   2. Switch on index:
    //      case 0: call SoundVisitor::operator()(std::get<0>(a1))
    //              = call SoundVisitor::operator()(Horse{60,500})
    //              = call makeSound(Horse{60,500})
    //              = print "Horse... NEIGH!"
    //
    std::visit(SoundVisitor{}, a1);
    std::visit(SoundVisitor{}, a2);
    std::visit(SoundVisitor{}, a3);
    
    std::cout << "\n=== Using generic lambda ===\n";
    
    // ═══════════════════════════════════════════════════════════════════════
    // STEP 6: std::visit with generic lambda
    // ═══════════════════════════════════════════════════════════════════════
    //
    // Lambda type: struct __lambda_1 {
    //     template<typename T>
    //     void operator()(T&& animal) const { makeSound(animal); }
    // };
    //
    // Compiler instantiates:
    //   __lambda_1::operator()<Horse>(Horse&)
    //   __lambda_1::operator()<Cat>(Cat&)
    //   __lambda_1::operator()<Dog>(Dog&)
    //
    auto soundLambda = [](auto&& animal) { makeSound(animal); };
    
    std::visit(soundLambda, a1);   // index=0 → calls makeSound(Horse)
    std::visit(soundLambda, a2);   // index=1 → calls makeSound(Cat)
    std::visit(soundLambda, a3);   // index=2 → calls makeSound(Dog)
    
    std::cout << "\n=== Array of Animals ===\n";
    
    // ═══════════════════════════════════════════════════════════════════════
    // STEP 7: Array of variants
    // ═══════════════════════════════════════════════════════════════════════
    //
    // Memory layout:
    // ┌─────────────────────────────────────────────────────────────────────┐
    // │ animals[0]: Horse{60,500}, index=0   │ 16 bytes at offset 0        │
    // │ animals[1]: Cat{9,5}, index=1        │ 16 bytes at offset 16       │
    // │ animals[2]: Dog{100,30}, index=2     │ 16 bytes at offset 32       │
    // │ animals[3]: Horse{80,450}, index=0   │ 16 bytes at offset 48       │
    // │ animals[4]: Cat{7,6}, index=1        │ 16 bytes at offset 64       │
    // └─────────────────────────────────────────────────────────────────────┘
    // Total: 5 × 16 = 80 bytes, contiguous, cache-friendly
    //
    Animal animals[5] = {
        Horse{60, 500},
        Cat{9, 5},
        Dog{100, 30},
        Horse{80, 450},
        Cat{7, 6}
    };
    
    for (int i = 0; i < 5; ++i) {
        std::cout << "animals[" << i << "]: ";
        std::visit(soundLambda, animals[i]);
    }
    
    return 0;
}

// ═══════════════════════════════════════════════════════════════════════════
// COMPARISON: VIRTUAL vs VARIANT
// ═══════════════════════════════════════════════════════════════════════════
//
// ┌─────────────────────────┬─────────────────────────┬──────────────────────┐
// │ Aspect                  │ Virtual (vptr)          │ Variant (visitor)    │
// ├─────────────────────────┼─────────────────────────┼──────────────────────┤
// │ sizeof(Animal base)     │ 8 (vptr) + members      │ 0 (no base class)    │
// │ sizeof(each derived)    │ 8 + derived members     │ just members         │
// │ Polymorphism mechanism  │ vptr → vtable → slot    │ index → switch/jump  │
// │ Runtime dispatch        │ 2 memory loads          │ 1 memory load        │
// │ New type addition       │ add derived class       │ modify variant<>     │
// │ Open/Closed             │ open (can add derived)  │ closed (fixed types) │
// │ Memory layout           │ scattered (heap ptrs)   │ contiguous (inline)  │
// │ Cache friendliness      │ poor (pointer chasing)  │ good (contiguous)    │
// └─────────────────────────┴─────────────────────────┴──────────────────────┘
//
// Virtual: call *(*(this+0) + slot_offset)  → 2 dereferences
// Variant: switch(index) { case 0: ... }    → 1 index read + jump
// ═══════════════════════════════════════════════════════════════════════════
