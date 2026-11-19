# Employee Pay Rule Management System (C++17)

A console-based mini project using concepts from the uploaded Object Oriented Principles syllabus.

## Features
- Add Full-Time and Part-Time employees
- View/list all employees
- Search by employee ID
- Update employee pay rules
- Delete employee records
- Generate a payroll report and total payroll
- Persist records in `employees.csv` (automatically loaded on startup and saved after changes)

## Salary calculation rules
- **Full-Time:** Monthly Basic Pay + Monthly Allowance - Monthly Deduction
- **Part-Time:** Hourly Rate × Hours Worked - Monthly Deduction

All inputs are checked for non-negative values. Employee IDs must be positive and unique. Part-time hours are limited to 0–744 (maximum hours in a 31-day month).

## OOP concepts demonstrated
- **Encapsulation:** employee/pay values are private or protected; updates use validated setters.
- **Abstraction:** `Employee` is abstract and exposes `calculateSalary()` as a pure virtual method.
- **Inheritance:** `FullTimeEmployee` and `PartTimeEmployee` inherit from `Employee`.
- **Runtime polymorphism:** virtual functions display employee details and calculate salary through base-class pointers.
- **Constructors / destructor:** constructors initialize objects; base destructor is virtual.
- **RAII / smart pointers:** employees are owned by `vector<unique_ptr<Employee>>`.
- **STL:** `vector`, `find_if`, `algorithm`, and range-based loops.
- **Exception handling:** invalid data and file errors use exceptions.
- **File I/O:** employee records are saved to and loaded from CSV.

## Compile and run
### Linux / macOS / MinGW with g++
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o employee_pay_system
./employee_pay_system
```
### Windows (MinGW)
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o employee_pay_system.exe
employee_pay_system.exe
```

The `employees.csv` file is created in the program's current working directory. Keep it with the executable if you want to retain records between runs.

## Menu
1. Add Employee
2. List Employees
3. Search Employee
4. Update Pay Rule
5. Delete Employee
6. Payroll Report
7. Exit

## Example calculation
A full-time employee with basic pay 30,000, allowance 5,000, and deduction 2,000 has net pay 33,000.
A part-time employee working 80 hours at 250/hour with a deduction of 1,000 has net pay 19,000.
