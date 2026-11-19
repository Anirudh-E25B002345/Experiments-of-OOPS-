CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = employee_pay_system

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe employees.csv
