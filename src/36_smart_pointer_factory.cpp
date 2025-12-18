#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iomanip>

// PUZZLE 36: SMART POINTER FACTORY
// ==========================================
// Your Goal: Implement the memory graph manually.
// STRICT RULE: Do not use raw pointers.
// STRICT RULE: No cyclic references allowed (Subject <-> Observer).

// [AXIOM 1] Memory Layout
// shared_ptr<T> on Stack: 16 bytes (Ptr to Object + Ptr to ControlBlock)
// ControlBlock on Heap:   StrongCount(4B) + WeakCount(4B) + Allocator...
// Object on Heap:         T

class Observer {
    int id_;
public:
    explicit Observer(int id) : id_(id) {
        std::cout << "  [Alloc] Observer@" << this << " (ID " << id_ << ")\n";
    }
    ~Observer() {
        std::cout << "  [Free]  Observer@" << this << " (ID " << id_ << ")\n";
    }
    int id() const { return id_; }
    void update(double area) const {
        std::cout << "  [Msg]   Observer@" << this << " (ID " << id_ << ") received area=" << area << "\n";
    }
};

class Subject {
    // -------------------------------------------------------------
    // TODO A: Define the container for observers.
    // CONSTRAINT: Observer lifecycle is INDEPENDENT of Subject.
    // MEMORY: Subject -> Observer connection.
    // CALCULATION:
    //   If vector<shared_ptr<Observer>>: 
    //      Subject holds StrongRef. 
    //      If Observer also holds StrongRef to Subject (common pattern), RefCount never hits 0. -> LEAK.
    //   If vector<Observer*>:
    //      Dangling pointer risk if Observer dies first.
    //   THEREFORE: Use a smart pointer that "observes" but doesn't "own".
    // -------------------------------------------------------------
    // std::vector<.......> observers_; 

public:
    virtual ~Subject() = default;

    // TODO B: Implement attach
    // INPUT: shared_ptr<Observer> obs
    // MEMORY TRACE:
    //   obs passed by value? -> Copy shared_ptr -> StrongRef++ (Stack)
    //   Stored in vector -> StrongRef?? or WeakRef??
    //   End of function -> Stack shared_ptr dies -> StrongRef--
    void attach(std::shared_ptr<Observer> obs) {
        // Fill this
    }

    // TODO C: Implement detach
    void detach(std::shared_ptr<Observer> obs) {
       // Remove matching observer
    }

protected:
    // TODO D: Implement notify
    // ACTION: Iterate observers.
    // PROBLEM: Weak pointers cannot be dereferenced directly.
    // STEP 1: Check if object exists (expired?).
    // STEP 2: Elevate to shared_ptr (lock).
    // STEP 3: Call update().
    // MEMORY: temp_shared_ptr created -> StrongRef N -> N+1.
    //         update() returns.
    //         temp_shared_ptr dies -> StrongRef N+1 -> N.
    void notify(double value) const {
        // Fill this
    }
};

class Shape : public Subject {
public:
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
    double radius_;
public:
    explicit Circle(double r) : radius_(r) {}
    double area() const override {
        double a = 3.14159 * radius_ * radius_;
        // TODO: Call notify(a) here
        return a;
    }
};

class Rectangle : public Shape {
    double w_, h_;
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area() const override {
        double a = w_ * h_;
        // TODO: Call notify(a) here
        return a;
    }
};

class ShapeFactory {
public:
    // TODO E: Return type?
    // CASE: Factory creates NEW object from scratch.
    // Q: Who owns it? The Caller.
    // Q: Should Factory retain ownership? No.
    // RETURN: shared_ptr? (Overhead 16B). unique_ptr? (Zero overhead, transfer ownership).
    // SELECT: unique_ptr.
    static /*Type*/ void create(int id) {
        // if id=1 return Circle(3.0)
        // if id=2 return Rectangle(4.0, 5.0)
    }
};

int main() {
    std::cout << "--- PUZZLE START ---\n";

    // 1. Create Observers
    // auto obs1 = ... (ID 101)
    
    // 2. Create Shape
    // auto shape = ... (ID 1)
    
    // 3. Attach
    // shape->attach(obs1);
    
    // 4. Calculate Area
    // shape->area();

    // 5. Verify Lifetime
    // obs1.reset();
    // shape->area(); // Should not crash, should not notify dead observer

    return 0;
}
