#include <iostream>
#include <string>

using namespace std;

// Base Class
class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}

    void displayPerson() {
        cout << "Name: " << name << "\nAge: " << age << endl;
    }
};

// (Single Inheritance: Person -> Student)
class Student : public Person {
protected:
    int rollNo;

public:
    Student(string n, int a, int r) : Person(n, a), rollNo(r) {}

    void displayStudent() {
        displayPerson();
        cout << "Roll No: " << rollNo << endl;
    }
};

//  (Multilevel Inheritance: Person -> Student -> GraduateStudent)
class GraduateStudent : public Student {
private:
    string thesisTopic;

public:
    GraduateStudent(string n, int a, int r, string topic)
        : Student(n, a, r), thesisTopic(topic) {}

    void displayGradStudent() {
        displayStudent();
        cout << "Thesis Topic: " << thesisTopic << endl;
    }
};

int main() {
    // Demonstrating Single Inheritance
    cout << "--- Single Inheritance (Student) ---" << endl;
    Student s1("Rohan", 19, 101);
    s1.displayStudent();

    // Multilevel Inheritance
    cout << "\n Multilevel Inheritance (Graduate Student) " << endl;
    GraduateStudent g1("Priya", 23, 205, "AI in Healthcare");
    g1.displayGradStudent();

    return 0;
}