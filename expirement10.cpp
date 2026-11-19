#include <iostream>
#include <stdexcept>
#include <string>

// 1. Base Custom Exception
class BankException : public std::runtime_error {
public:
    BankException(const std::string& msg) : std::runtime_error(msg) {}
};

// 2. Specific Derived Exceptions
class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException() : BankException("Error: Insufficient balance for withdrawal.") {}
};

class InvalidAmountException : public BankException {
public:
    InvalidAmountException() : BankException("Error: Transaction amount must be positive.") {}
};

// Banking Class
class Account {
    double balance = 500.0;
public:
    void withdraw(double amount) {
        if (amount <= 0) 
            throw InvalidAmountException();
        if (amount > balance) 
            throw InsufficientFundsException();
        
        balance -= amount;
        std::cout << "Withdrawn: ₹" << amount << " | Remaining: ₹" << balance << "\n";
    }
};

int main() {
    Account acc;
    double testAmounts[] = {-50.0, 1000.0, 200.0};

    for (double amt : testAmounts) {
        try {
            acc.withdraw(amt);
        } 
        // Catch specific exceptions first
        catch (const InsufficientFundsException& e) {
            std::cerr << "[Funds Alert] " << e.what() << "\n";
        } 
        catch (const InvalidAmountException& e) {
            std::cerr << "[Input Alert] " << e.what() << "\n";
        } 
        // Catch-all for any other BankException
        catch (const BankException& e) {
            std::cerr << "[Bank Error] " << e.what() << "\n";
        }
    }

    return 0;
}