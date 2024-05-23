/* 12.Create a base class shape. Use this class to store two double type values that could be used to compute
area of figures. Derive two specific classes called triangle and rectangle from the base shape. Add to the base a
member function getdata() to initialize base class data member and another member function display_area() to
compute and display the area of figures. Make display_area() as a virtual function and redefine it the derived
class to suit their requirements*/

#include <iostream>

class Shape {
protected:
    double dimension1;
    double dimension2;

public:
    // Function to initialize base class data members
    void getdata(double d1, double d2) {
        dimension1 = d1;
        dimension2 = d2;
    }

    // Virtual function to compute and display area
    virtual void display_area() const = 0; // Pure virtual function
};

class Triangle : public Shape {
public:
    // Override display_area to compute the area of a triangle
    void display_area() const override {
        double area = 0.5 * dimension1 * dimension2;
        std::cout << "Area of the triangle: " << area << std::endl;
    }
};

class Rectangle : public Shape {
public:
    // Override display_area to compute the area of a rectangle
    void display_area() const override {
        double area = dimension1 * dimension2;
        std::cout << "Area of the rectangle: " << area << std::endl;
    }
};

int main() {
    Triangle tri;
    Rectangle rect;

    double base, height, length, width;

    std::cout << "Enter the base and height of the triangle: ";
    std::cin >> base >> height;
    tri.getdata(base, height);

    std::cout << "Enter the length and width of the rectangle: ";
    std::cin >> length >> width;
    rect.getdata(length, width);

    std::cout << "\n";
    tri.display_area();
    rect.display_area();

    return 0;
}
