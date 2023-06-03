#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Abstract base class for concrete Shape classes
class Shape
{
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// Concrete Shape classes
class Circle : public Shape
{
public:
    explicit Circle(double radius) : m_Radius(radius) {}

    void draw() const override
    {
        cout << "Drawing a circle with radius " << m_Radius << endl;
    }

private:
    double m_Radius;
};

class Rectangle : public Shape
{
public:
    Rectangle(double width, double height) : m_Width(width), m_Height(height) {}

    void draw() const override
    {
        cout << "Drawing a rectangle with width " << m_Width << " and height " << m_Height << endl;
    }

private:
    double m_Width;
    double m_Height;
};

class Triangle : public Shape
{
public:
    Triangle(double side1, double side2, double side3) : m_Side1(side1), m_Side2(side2), m_Side3(side3) {}

    void draw() const override
    {
        cout << "Drawing a triangle with sides " << m_Side1 << ", " << m_Side2 << ", and " << m_Side3 << endl;
    }

private:
    double m_Side1;
    double m_Side2;
    double m_Side3;
};

class CompositeShape : public Shape {
private:
    std::vector<Shape*> m_Shapes;

public:
    void addShape(Shape &shape) {
        m_Shapes.push_back(&shape);
    }

    void draw() const override
    {
        cout << "Drawing a composite shape" << endl;
        for (const auto &shape : m_Shapes) {
            shape->draw();
        }
    }

    void removeShape(Shape &shape) {
        m_Shapes.erase(std::remove(m_Shapes.begin(), m_Shapes.end(), &shape), m_Shapes.end());
    }
};

int main()
{
    Circle c(5);
    Rectangle r(10, 20);
    Triangle t(3, 4, 5);

    // Create a composite shape
    CompositeShape cs;

    cs.addShape(c);
    cs.addShape(r);
    cs.addShape(t);

    // Draw the composite shape
    cs.draw();

    // Remove a shape from the composite shape
    cs.removeShape(r);

    // Draw the composite shape again
    cs.draw();

    return 0;
}
