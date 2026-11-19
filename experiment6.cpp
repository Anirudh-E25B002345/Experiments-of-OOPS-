#include <iostream>
using namespace std;

class Complex {
private:
    int real, imag;

public:
    // 1. Function Overloading 
    Complex() {
        real = 0;
        imag = 0;
    }

    Complex(int r, int i) {
        real = r;
        imag = i;
    }

    // 2. Function Overloading 
    void set(int r) {
        real = r;
        imag = 0;
    }

    void set(int r, int i) {
        real = r;
        imag = i;
    }

    // 3. Operator Overloading 
    Complex operator+(const Complex& obj) {
        Complex temp;
        temp.real = real + obj.real;
        temp.imag = imag + obj.imag;
        return temp;
    }

    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1, c2;

    
    c1.set(5);        
    c2.set(3, 4);     

    
    Complex c3 = c1 + c2;

    cout << "c1 = "; c1.display();
    cout << "c2 = "; c2.display();
    cout << "Sum (c1 + c2) = "; c3.display();

    return 0;
}