// Demonstrates data types, constants, variables, operators and I/O
#include <iostream>
#include <string>
using namespace std;

int main() {
    const double PI = 3.14159;      // constant
    int a, b;                       // variables
    float height = 5.8f;
    char grade = 'A';
    string name = "Student";

    cout << "Enter two integers: ";  // output
    cin >> a >> b;                   // input

    cout << "Sum: " << a + b << endl;
    cout << "Difference: " << a - b << endl;
    cout << "Product: " << a * b << endl;
    cout << "Quotient: " << a / b << endl;
    cout << "Remainder: " << a % b << endl;
    cout << "Is a > b? " << (a > b) << endl;
    cout << "Both positive? " << (a > 0 && b > 0) << endl;
    cout << "Bigger: " << (a > b ? a : b) << endl;

    a++;
    cout << "a after a++: " << a << endl;
    cout << "Circle area (r=2): " << PI * 2 * 2 << endl;
    cout << name << " " << grade << " " << height << endl;

    return 0;
}