// ============================================================================
// C++ Containers & Memory Worksheet - Boilerplate Code
// NO SOLUTIONS - Fill in the TODO sections
// ============================================================================
// Build: cmake .. -DCMAKE_CXX_COMPILER=g++-14 && make
// Run:   ./containers_worksheet
// ============================================================================

#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

// ============================================================================
// PART 1: Pointer Swap
// ============================================================================
// HARDEST PART: Tracking memory addresses during indirection
// EDGE CASE: nullptr dereference
// ============================================================================

void swap_with_pointers([[maybe_unused]] int* pa, [[maybe_unused]] int* pb) {
    // TODO: Implement swap using pointers
    // 1. int tmp = *pa;
    // 2. *pa = *pb;
    // 3. *pb = tmp;

    // YOUR CODE HERE (3 lines)
}

void test_pointer_swap() {
    std::cout << "=== PART 1: Pointer Swap ===\n";

    int a = 5;
    int b = 7;

    std::cout << "Before: a=" << a << " b=" << b << "\n";
    std::cout << "Address &a=" << &a << " &b=" << &b << "\n";

    swap_with_pointers(&a, &b);

    std::cout << "After:  a=" << a << " b=" << b << "\n";

    // VERIFICATION
    // assert(a == 7 && "a should be 7 after swap");
    // assert(b == 5 && "b should be 5 after swap");

    std::cout << "Result: " << (a == 7 && b == 5 ? "PASS" : "FAIL") << "\n\n";
}

// ============================================================================
// PART 2: Reference Swap
// ============================================================================
// HARDEST PART: Understanding that reference IS the variable (alias)
// EDGE CASE: Cannot have uninitialized reference
// ============================================================================

void swap_with_references([[maybe_unused]] int& ra, [[maybe_unused]] int& rb) {
    // TODO: Implement swap using references
    // 1. int tmp = ra;
    // 2. ra = rb;
    // 3. rb = tmp;

    // YOUR CODE HERE (3 lines)
}

void test_reference_swap() {
    std::cout << "=== PART 2: Reference Swap ===\n";

    int a = 5;
    int b = 7;

    std::cout << "Before: a=" << a << " b=" << b << "\n";

    swap_with_references(a, b);

    std::cout << "After:  a=" << a << " b=" << b << "\n";
    std::cout << "Result: " << (a == 7 && b == 5 ? "PASS" : "FAIL") << "\n\n";
}

// ============================================================================
// PART 3: Vector Capacity Growth
// ============================================================================
// HARDEST PART: Predicting when reallocation occurs
// EDGE CASE: push_back on empty vector (capacity 0 → 1)
// ============================================================================

void test_vector_capacity() {
    std::cout << "=== PART 3: Vector Capacity Growth ===\n";

    std::vector<int> v(3, 0);  // size=3, capacity=3

    std::cout << "Initial: size=" << v.size() << " capacity=" << v.capacity() << "\n";
    std::cout << "v.data()=" << v.data() << "\n";

    // TODO: Predict capacity before each push_back
    // Fill in expected values, then verify

    // Push 1
    void* old_data = v.data();
    v.push_back(10);
    bool reallocated = (v.data() != old_data);
    std::cout << "After push_back(10): size=" << v.size() << " capacity=" << v.capacity()
              << " reallocated=" << (reallocated ? "YES" : "NO") << "\n";

    // Push 2
    old_data = v.data();
    v.push_back(20);
    reallocated = (v.data() != old_data);
    std::cout << "After push_back(20): size=" << v.size() << " capacity=" << v.capacity()
              << " reallocated=" << (reallocated ? "YES" : "NO") << "\n";

    // Push 3
    old_data = v.data();
    v.push_back(30);
    reallocated = (v.data() != old_data);
    std::cout << "After push_back(30): size=" << v.size() << " capacity=" << v.capacity()
              << " reallocated=" << (reallocated ? "YES" : "NO") << "\n";

    // Push 4
    old_data = v.data();
    v.push_back(40);
    reallocated = (v.data() != old_data);
    std::cout << "After push_back(40): size=" << v.size() << " capacity=" << v.capacity()
              << " reallocated=" << (reallocated ? "YES" : "NO") << "\n";

    std::cout << "\n";
}

// ============================================================================
// PART 4: Iterator Invalidation
// ============================================================================
// HARDEST PART: Iterator becomes dangling pointer after reallocation
// EDGE CASE: *v.end() is undefined behavior
// ============================================================================

void test_iterator_invalidation() {
    std::cout << "=== PART 4: Iterator Invalidation ===\n";

    std::vector<int> v = {10, 20, 30};

    auto it = v.begin();
    std::cout << "Before reallocation: it points to " << *it << "\n";
    std::cout << "Iterator address: " << &(*it) << "\n";
    std::cout << "v.data(): " << v.data() << "\n";

    // Force reallocation
    v.reserve(100);

    std::cout << "After reallocation:\n";
    std::cout << "v.data(): " << v.data() << "\n";

    // WARNING: 'it' is now INVALID (dangling pointer)
    // DO NOT uncomment: std::cout << "*it = " << *it << "\n";
    // This would be undefined behavior!

    // SAFE: Get new iterator
    it = v.begin();
    std::cout << "New iterator points to: " << *it << "\n";

    std::cout << "\n";
}

// ============================================================================
// PART 5: List vs Vector Memory
// ============================================================================
// HARDEST PART: List node overhead (prev + next + data + padding)
// EDGE CASE: List iteration = pointer chasing = cache misses
// ============================================================================

void test_list_vs_vector_memory() {
    std::cout << "=== PART 5: List vs Vector Memory ===\n";

    constexpr int N = 100;

    std::vector<int> vec(N);
    std::list<int> lst;
    for (int i = 0; i < N; ++i) lst.push_back(i);

    // Vector memory: N * sizeof(int) = N * 4
    size_t vec_bytes = N * sizeof(int);

    // List memory: N * (sizeof(prev) + sizeof(next) + sizeof(data) + padding)
    // On 64-bit: N * (8 + 8 + 4 + 4) = N * 24
    size_t list_node_size = sizeof(void*) * 2 + sizeof(int);
    // Add alignment padding
    size_t aligned_node_size = ((list_node_size + 7) / 8) * 8;
    size_t lst_bytes = N * aligned_node_size;

    std::cout << "Vector: " << N << " elements × " << sizeof(int) << " bytes = " << vec_bytes
              << " bytes\n";
    std::cout << "List:   " << N << " elements × ~" << aligned_node_size << " bytes = " << lst_bytes
              << " bytes\n";
    std::cout << "List overhead ratio: "
              << static_cast<double>(lst_bytes) / static_cast<double>(vec_bytes) << "x\n";

    // Cache line analysis
    constexpr int CACHE_LINE = 64;
    int vec_per_cache = CACHE_LINE / sizeof(int);
    int list_per_cache = static_cast<int>(CACHE_LINE / aligned_node_size);

    std::cout << "Elements per cache line: vector=" << vec_per_cache << " list=" << list_per_cache
              << "\n";

    // TODO: Calculate cache misses for traversal
    // vector: ceil(N * sizeof(int) / CACHE_LINE)
    // list: worst case = N (each node in different cache line)

    std::cout << "\n";
}

// ============================================================================
// PART 6: Smart Pointer Reference Counting
// ============================================================================
// HARDEST PART: weak_ptr.lock() returns nullptr after all shared_ptr released
// EDGE CASE: Cyclic reference causes memory leak
// ============================================================================

class Observer {
   public:
    int id;
    explicit Observer(int i) : id(i) { std::cout << "  Observer " << id << " created\n"; }
    ~Observer() { std::cout << "  Observer " << id << " destroyed\n"; }
    void notify(double value) {
        std::cout << "  Observer " << id << " received: " << value << "\n";
    }
};

void test_smart_pointer_refcount() {
    std::cout << "=== PART 6: Smart Pointer Reference Counting ===\n";

    // TODO: Track reference counts at each step

    std::cout << "Creating shared_ptr p1:\n";
    std::shared_ptr<Observer> p1 = std::make_shared<Observer>(101);
    std::cout << "  use_count=" << p1.use_count() << "\n";  // Expected: 1

    std::cout << "Creating shared_ptr p2 = p1:\n";
    std::shared_ptr<Observer> p2 = p1;
    std::cout << "  use_count=" << p1.use_count() << "\n";  // Expected: ?

    std::cout << "Creating weak_ptr w = p1:\n";
    std::weak_ptr<Observer> w = p1;
    std::cout << "  use_count=" << p1.use_count() << "\n";  // weak_ptr doesn't change count
    std::cout << "  w.expired()=" << w.expired() << "\n";   // Expected: false (0)

    std::cout << "p1.reset():\n";
    p1.reset();
    std::cout << "  p2.use_count()=" << p2.use_count() << "\n";  // Expected: ?
    std::cout << "  w.expired()=" << w.expired() << "\n";

    std::cout << "p2.reset():\n";
    p2.reset();
    std::cout << "  w.expired()=" << w.expired() << "\n";  // Expected: true (1)

    std::cout << "w.lock() attempt:\n";
    if (auto sp = w.lock()) {
        std::cout << "  Got valid shared_ptr\n";
    } else {
        std::cout << "  Got nullptr (object destroyed)\n";
    }

    std::cout << "\n";
}

// ============================================================================
// PART 7: Factory Pattern
// ============================================================================
// HARDEST PART: Virtual dispatch, heap allocation
// EDGE CASE: Factory returns nullptr for unknown ID
// ============================================================================

class Shape {
   public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual const char* name() const = 0;
};

class Circle : public Shape {
    [[maybe_unused]] double radius_;

   public:
    explicit Circle(double r) : radius_(r) {}
    double area() const override {
        // TODO: return M_PI * radius_ * radius_;
        return 0.0;  // PLACEHOLDER
    }
    const char* name() const override { return "Circle"; }
};

class Rectangle : public Shape {
    [[maybe_unused]] double width_, height_;

   public:
    Rectangle(double w, double h) : width_(w), height_(h) {}
    double area() const override {
        // TODO: return width_ * height_;
        return 0.0;  // PLACEHOLDER
    }
    const char* name() const override { return "Rectangle"; }
};

class ShapeFactory {
   public:
    static std::unique_ptr<Shape> create([[maybe_unused]] int id) {
        // TODO: Implement factory logic
        // id == 1 → Circle(3.0)
        // id == 2 → Rectangle(4.0, 5.0)
        // else    → nullptr

        return nullptr;  // PLACEHOLDER
    }
};

void test_factory_pattern() {
    std::cout << "=== PART 7: Factory Pattern ===\n";

    auto circle = ShapeFactory::create(1);
    auto rect = ShapeFactory::create(2);
    auto unknown = ShapeFactory::create(99);

    if (circle) {
        std::cout << circle->name() << " area=" << circle->area() << "\n";
        // Expected: Circle area=28.274...
    }

    if (rect) {
        std::cout << rect->name() << " area=" << rect->area() << "\n";
        // Expected: Rectangle area=20.0
    }

    if (!unknown) {
        std::cout << "Unknown ID returned nullptr (correct)\n";
    }

    std::cout << "\n";
}

// ============================================================================
// PART 8: Observer Pattern with weak_ptr
// ============================================================================
// HARDEST PART: weak_ptr prevents memory leak in observer list
// EDGE CASE: Observer destroyed while attached → weak_ptr.lock() returns nullptr
// ============================================================================

class Subject {
    std::vector<std::weak_ptr<Observer>> observers_;

   public:
    void attach(const std::weak_ptr<Observer>& obs) { observers_.push_back(obs); }

    void notify_all([[maybe_unused]] double value) {
        // TODO: Iterate observers, lock each weak_ptr, call notify if valid

        for ([[maybe_unused]] auto& weak_obs : observers_) {
            if (auto control_block = weak_obs.lock()) {
                control_block->notify(value);
            }
        }
    }

    [[nodiscard]] size_t observer_count() const { return observers_.size(); }
};

void test_observer_pattern() {
    std::cout << "=== PART 8: Observer Pattern ===\n";

    Subject subject;

    {
        auto obs1 = std::make_shared<Observer>(1);
        auto obs2 = std::make_shared<Observer>(2);

        subject.attach(obs1);
        subject.attach(obs2);

        std::cout << "Notifying " << subject.observer_count() << " observers:\n";
        subject.notify_all(42.0);

        std::cout << "obs1 goes out of scope:\n";
    }  // obs1 and obs2 destroyed here

    std::cout << "Notifying after observers destroyed:\n";
    subject.notify_all(99.0);  // Should send 0 notifications

    std::cout << "\n";
}

// ============================================================================
// EDGE CASE TESTS
// ============================================================================

void test_edge_cases() {
    std::cout << "=== EDGE CASES ===\n";

    // Edge 1: Empty vector
    std::vector<int> empty;
    std::cout << "Empty vector: begin()==end()? " << (empty.begin() == empty.end() ? "YES" : "NO")
              << "\n";

    // Edge 2: Single element
    std::vector<int> single = {42};
    std::cout << "Single element: *begin()=" << *single.begin() << "\n";

    // Edge 3: Capacity vs Size
    std::vector<int> reserved;
    reserved.reserve(100);
    std::cout << "After reserve(100): size=" << reserved.size()
              << " capacity=" << reserved.capacity() << "\n";

    // WARNING: DO NOT UNCOMMENT THESE - UNDEFINED BEHAVIOR
    // *empty.end();           // Dereference past-the-end
    // empty.pop_back();       // Pop from empty
    // int* p; *p = 5;         // Uninitialized pointer

    std::cout << "\n";
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║  C++ Containers & Memory Worksheet                       ║\n";
    std::cout << "║  Fill in TODO sections, run, verify against worksheet    ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    test_pointer_swap();
    test_reference_swap();
    test_vector_capacity();
    test_iterator_invalidation();
    test_list_vs_vector_memory();
    test_smart_pointer_refcount();
    test_factory_pattern();
    test_observer_pattern();
    test_edge_cases();

    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║  END OF WORKSHEET                                        ║\n";
    std::cout << "║  Compare output against expected values in worksheet.md  ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";

    return 0;
}
