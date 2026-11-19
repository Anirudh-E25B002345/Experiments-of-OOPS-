#include <iostream>
#include <string>

// Base Class
class BankAccount {
private:
    
    std::string accountNumber;

protected:
   double balance;

public:
    
    BankAccount(std::string accNum, double initialBalance) {
        accountNumber = accNum;
        balance = initialBalance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited: $" << amount << "\n";
        }
    }

    void display() const {
        std::cout << "Account: " << accountNumber 
                  << " | Balance: $" << balance << "\n";
    }
};

// Derived Class (Inherits publicly from BankAccount)
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(std::string accNum, double initialBalance, double rate)
        : BankAccount(accNum, initialBalance), interestRate(rate) {}

    void addInterest() {
        
        double interest = balance * (interestRate / 100);
        balance += interest;
        std::cout << "Interest Added: $" << interest << "\n";
        
       
    }
};

int main() {
    SavingsAccount mySavings("SAV-101", 1000.0, 5.0);

    // Calling PUBLIC member functions
    mySavings.display();
    mySavings.deposit(500.0);
    mySavings.addInterest();
    mySavings.display();

   

    return 0;
}