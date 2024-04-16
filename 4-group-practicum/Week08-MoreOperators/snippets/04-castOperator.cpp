#include <iostream>

class Fraction 
{
private:
    int numerator;
    int denominator;

    static int calculateGCD(int a, int b) 
    {
        if (b == 0) 
        {
            return a;
        }
        return calculateGCD(b, a % b);
    }

    void simplify() 
    {
        int gcd = calculateGCD(numerator, denominator);

        numerator /= gcd;
        denominator /= gcd;

        if (denominator < 0) 
        {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Fraction(int num, int den) 
        : numerator(num), denominator(den) 
    {
        if (denominator == 0) 
        {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        simplify();
    }

    Fraction operator + (const Fraction& other) const 
    {
        int newNumerator = (numerator * other.denominator) + (other.numerator * denominator);
        int newDenominator = denominator * other.denominator;
        
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator - (const Fraction& other) const 
    {
        int newNumerator = (numerator * other.denominator) - (other.numerator * denominator);
        int newDenominator = denominator * other.denominator;
        
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator * (const Fraction& other) const 
    {
        int newNumerator = numerator * other.numerator;
        int newDenominator = denominator * other.denominator;
        
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator / (const Fraction& other) const 
    {
        int newNumerator = numerator * other.denominator;
        int newDenominator = denominator * other.numerator;

        return Fraction(newNumerator, newDenominator);
    }

    friend std::ostream& operator << (std::ostream& os, const Fraction& fraction) 
    {
        os << fraction.numerator << "/" << fraction.denominator;
        
        return os;
    }

    operator double() 
    {
        return static_cast<double>(numerator) / static_cast<double>(denominator);
    }

    operator int()
    {
        return numerator / denominator;
    }

    operator bool()
    {
        return numerator != 0;
    }
};

int main() {
    Fraction f1(1, 2);
    Fraction f2(3, 4);

    Fraction addition = f1 + f2;
    Fraction subtraction = f1 - f2;
    Fraction multiplication = f1 * f2;
    Fraction division = f1 / f2;

    std::cout << "Addition: " << addition << std::endl;  // Output: 5/4
    std::cout << "Subtraction: " << subtraction << std::endl;  // Output: -1/4
    std::cout << "Multiplication: " << multiplication << std::endl;  // Output: 3/8
    std::cout << "Division: " << division << std::endl;  // Output: 2/3

    int f1AsInt = f1;
    double f1AsDouble = f1;
    bool f1AsBool = f1;

    std::cout << "Int: " << f1AsInt << std::endl; // Output: 0
    std::cout << "Double: " << f1AsDouble << std::endl; // Output: 0.5
    std::cout << "Bool: " << std::boolalpha << f1AsBool << std::endl; // Output: true

    return 0;
}
