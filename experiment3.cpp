#include <iostream>
#include <utility> // For std::move

class IntArray {
private:
    int* data;
    size_t size;

public:
    // 1. Default Constructor
    IntArray() : data(nullptr), size(0) {
        std::cout << "[Default Constructor]\n";
    }

    // 2. Parameterized Constructor
    explicit IntArray(size_t s) : data(new int[s]{}), size(s) {
        std::cout << "[Parameterized Constructor] size=" << size << "\n";
    }

    // 3. Destructor 
    ~IntArray() {
        std::cout << "[Destructor] freeing size=" << size << "\n";
        delete[] data;
    }

    // 4. Copy Constructor 
    IntArray(const IntArray& other) : data(other.size ? new int[other.size] : nullptr), size(other.size) {
        std::cout << "[Copy Constructor]\n";
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // 5. Copy Assignment Operator 
    IntArray& operator=(const IntArray& other) {
        std::cout << "[Copy Assignment]\n";
        if (this == &other) return *this; 

        delete[] data; 

        size = other.size;
        data = size ? new int[size] : nullptr;
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    // 6. Move Constructor 
    IntArray(IntArray&& other) noexcept : data(other.data), size(other.size) {
        std::cout << "[Move Constructor]\n";
        other.data = nullptr; // Leave source in a valid, empty state
        other.size = 0;
    }

    // 7. Move Assignment Operator 
    IntArray& operator=(IntArray&& other) noexcept {
        std::cout << "[Move Assignment]\n";
        if (this == &other) return *this; 

        delete[] data; 

        data = other.data; 
        size = other.size;

        other.data = nullptr;
        other.size = 0;
        return *this;
    }
};

int main() {
    IntArray a1;                    // Default
    IntArray a2(5);                 // Parameterized
    IntArray a3 = a2;               // Copy Constructor
    a1 = a2;                        // Copy Assignment
    IntArray a4 = std::move(a2);    // Move Constructor (a2 is now empty)
    a3 = std::move(a4);             // Move Assignment (a4 is now empty)

    return 0;
}