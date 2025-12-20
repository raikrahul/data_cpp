#include <iostream>
#include <typeinfo>
#include <vector>
#include <memory>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void whoAmI() const = 0;
};

class Circle;
class Rectangle;

class Circle : public Shape {
public:
    void whoAmI() const override;
};

class Rectangle : public Shape {
public:
    void whoAmI() const override;
};

void Circle::whoAmI() const {
    const std::type_info& ti = typeid(*this);
    const std::type_info& ti_circle = typeid(Circle);
    const std::type_info& ti_rect = typeid(Rectangle);
    
    if (&ti == &ti_circle) {
        std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
    } else if (&ti == &ti_rect) {
        std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
    }
}

void Rectangle::whoAmI() const {
    const std::type_info& ti = typeid(*this);
    const std::type_info& ti_circle = typeid(Circle);
    const std::type_info& ti_rect = typeid(Rectangle);
    
    if (&ti == &ti_circle) {
        std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
    } else if (&ti == &ti_rect) {
        std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Rectangle>());

    std::cout << "=== RTTI via typeid and Address Comparison ===\n";
    for (const auto& shape : shapes) {
        shape->whoAmI();
    }

    return 0;
}
