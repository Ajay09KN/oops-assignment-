/* 11.Assume that a bank maintains two kinds of accounts for customers, one called as savings account and the
other as current account. The savings account provides compound interest and withdrawal facilities but no
cheque book facility. The current account provides cheque book facility but no interest. Current account
holders should also maintain a minimum balance and if the balance falls below this level, a service chargeis imposed. Create a class account that stores customer name, account number and type of account. From
this derive the classes curacct and savacct to make them more specific to their requirements. Include
necessary member functions in order to achieve the following tasks:
a. Accept deposit from a costumer and update the balance.
b. Display the balance
c. Compute and deposit interest.
d. Permit withdrawal and update the balance.
e. Check for the minimum balance, impose penalty, necessary and update balance.*/

#include <iostream>
#include <string>
#include <cmath>

class Account {
protected:
    std::string customerName;
    int accountNumber;
    std::string accountType;
    double balance;

public:
    Account(const std::string &name, int accNum, const std::string &type, double initialBalance) 
        : customerName(name), accountNumber(accNum), accountType(type), balance(initialBalance) {}

    virtual void deposit(double amount) {
        balance += amount;
        std::cout << "Deposit successful. New balance: " << balance << std::endl;
    }

    virtual void displayBalance() const {
        std::cout << "Account balance: " << balance << std::endl;
    }

    virtual void withdraw(double amount) = 0; // Pure virtual function

    virtual ~Account() {}
};

class SavAcct : public Account {
private:
    double interestRate;

public:
    SavAcct(const std::string &name, int accNum, double initialBalance, double interestRate)
        : Account(name, accNum, "Savings", initialBalance), interestRate(interestRate) {}

    void computeAndDepositInterest() {
        double interest = balance * std::pow(1 + interestRate / 100, 1) - balance;
        deposit(interest);
        std::cout << "Interest of " << interest << " added. New balance: " << balance << std::endl;
    }

    void withdraw(double amount) override {
        if (amount <= balance) {
            balance -= amount;
            std::cout << "Withdrawal successful. New balance: " << balance << std::endl;
        } else {
            std::cout << "Insufficient funds for withdrawal." << std::endl;
        }
    }
};

class CurAcct : public Account {
private:
    double minimumBalance;
    double serviceCharge;

public:
    CurAcct(const std::string &name, int accNum, double initialBalance, double minBalance, double serviceCharge)
        : Account(name, accNum, "Current", initialBalance), minimumBalance(minBalance), serviceCharge(serviceCharge) {}

    void checkMinimumBalance() {
        if (balance < minimumBalance) {
            balance -= serviceCharge;
            std::cout << "Balance below minimum. Service charge of " << serviceCharge << " imposed. New balance: " << balance << std::endl;
        }
    }

    void withdraw(double amount) override {
        if (amount <= balance) {
            balance -= amount;
            std::cout << "Withdrawal successful. New balance: " << balance << std::endl;
            checkMinimumBalance();
        } else {
            std::cout << "Insufficient funds for withdrawal." << std::endl;
        }
    }

    void issueChequeBook() {
        std::cout << "Cheque book issued to " << customerName << std::endl;
    }
};

int main() {
    SavAcct savAccount("Alice", 1001, 5000.0, 5.0);  // 5% interest rate
    CurAcct curAccount("Bob", 1002, 3000.0, 1000.0, 50.0);  // Minimum balance 1000, service charge 50

    std::cout << "Savings Account:" << std::endl;
    savAccount.displayBalance();
    savAccount.deposit(1000);
    savAccount.computeAndDepositInterest();
    savAccount.withdraw(2000);
    savAccount.displayBalance();

    std::cout << "\nCurrent Account:" << std::endl;
    curAccount.displayBalance();
    curAccount.deposit(500);
    curAccount.withdraw(2000);
    curAccount.checkMinimumBalance();
    curAccount.displayBalance();
    curAccount.issueChequeBook();

    return 0;
}
