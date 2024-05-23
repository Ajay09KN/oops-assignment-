/* 10.Design a C++ Class ‘Complex’ with data members for real and imaginary part. Provide default and
parameterized constructors. Write a program to perform arithmetic operations of two complex numbers
using operator overloading (using either member functions or friend functions).*/

#include <iostream>

class Complex {
private:
    double real;
    double imaginary;

public:
    // Default constructor
    Complex() : real(0.0), imaginary(0.0) {}

    // Parameterized constructor
    Complex(double r, double i) : real(r), imaginary(i) {}

    // Overload the + operator to add two complex numbers
    Complex operator+(const Complex &other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    // Overload the - operator to subtract two complex numbers
    Complex operator-(const Complex &other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }

    // Overload the * operator to multiply two complex numbers
    Complex operator*(const Complex &other) const {
        return Complex(real * other.real - imaginary * other.imaginary, real * other.imaginary + imaginary * other.real);
    }

    // Overload the / operator to divide two complex numbers
    Complex operator/(const Complex &other) const {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        return Complex((real * other.real + imaginary * other.imaginary) / denominator, (imaginary * other.real - real * other.imaginary) / denominator);
    }

    // Friend function to overload the << operator for output
    friend std::ostream& operator<<(std::ostream &out, const Complex &c);

    // Friend function to overload the >> operator for input
    friend std::istream& operator>>(std::istream &in, Complex &c);
};

// Overload the << operator for output
std::ostream& operator<<(std::ostream &out, const Complex &c) {
    out << c.real;
    if (c.imaginary >= 0) {
        out << " + " << c.imaginary << "i";
    } else {
        out << " - " << -c.imaginary << "i";
    }
    return out;
}

// Overload the >> operator for input
std::istream& operator>>(std::istream &in, Complex &c) {
    std::cout << "Enter real part: ";
    in >> c.real;
    std::cout << "Enter imaginary part: ";
    in >> c.imaginary;
    return in;
}

int main() {
    Complex c1, c2, result;
    
    std::cout << "Enter the first complex number:\n";
    std::cin >> c1;
    
    std::cout << "Enter the second complex number:\n";
    std::cin >> c2;
    
    // Perform arithmetic operations
    result = c1 + c2;
    std::cout << "\nSum: " << result << std::endl;
    
    result = c1 - c2;
    std::cout << "Difference: " << result << std::endl;
    
    result = c1 * c2;
    std::cout << "Product: " << result << std::endl;
    
    result = c1 / c2;
    std::cout << "Quotient: " << result << std::endl;

    return 0;
}
