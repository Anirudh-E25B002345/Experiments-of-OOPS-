#include <iostream>
#include <vector>
#include <string>

template <typename T>
class Stack {
private:
    std::vector<T> items;

public:
    void push(const T& item) {
        items.push_back(item);
    }

    void pop() {
        if (!items.empty()) {
            items.pop_back();
        }
    }

    T top() const {
        if (!items.empty()) {
            return items.back();
        }
        throw std::out_of_range("Stack is empty");
    }

    bool isEmpty() const {
        return items.empty();
    }
};

int main() {
    //  Test with int
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    std::cout << "Int top: " << intStack.top() << "\n";
    intStack.pop();
    std::cout << "Int top after pop: " << intStack.top() << "\n\n";

    //  Test with float
    Stack<float> floatStack;
    floatStack.push(3.14f);
    floatStack.push(9.81f);
    std::cout << "Float top: " << floatStack.top() << "\n\n";

    // Test with std::string
    Stack<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    std::cout << "String top: " << stringStack.top() << "\n";

    return 0;
}