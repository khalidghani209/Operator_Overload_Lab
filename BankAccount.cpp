#include "BankAccount.h"
#include <cstring>
#include <iomanip>
#include <limits>

// Default Constructor
BankAccount::BankAccount() : accountNumber("000000"), balance(0.0) {
    const char* defaultName = "Unknown";
    accountHolderName = new char[std::strlen(defaultName) + 1];
    std::strcpy(accountHolderName, defaultName);
}

// Parameterized Constructor
BankAccount::BankAccount(const std::string& accNum, const std::string& holderName, double initialBalance)
    : accountNumber(accNum), balance(initialBalance >= 0.0 ? initialBalance : 0.0) {
    accountHolderName = new char[holderName.length() + 1];
    std::strcpy(accountHolderName, holderName.c_str());
}

// 1. Copy Constructor (Deep Copy)
BankAccount::BankAccount(const BankAccount& other)
    : accountNumber(other.accountNumber), balance(other.balance) {
    accountHolderName = new char[std::strlen(other.accountHolderName) + 1];
    std::strcpy(accountHolderName, other.accountHolderName);
}

// 2. Copy Assignment Operator (Deep Copy)
BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) { // Prevent self-assignment
        accountNumber = other.accountNumber;
        balance = other.balance;

        // Free existing memory before allocating new memory
        delete[] accountHolderName;
        accountHolderName = new char[std::strlen(other.accountHolderName) + 1];
        std::strcpy(accountHolderName, other.accountHolderName);
    }
    return *this;
}

// 3. Destructor
BankAccount::~BankAccount() {
    delete[] accountHolderName;
}

// Accessors
std::string BankAccount::getAccountNumber() const {
    return accountNumber;
}

std::string BankAccount::getAccountHolderName() const {
    return std::string(accountHolderName);
}

double BankAccount::getBalance() const {
    return balance;
}

// Mutator
void BankAccount::setAccountHolderName(const std::string& holderName) {
    delete[] accountHolderName;
    accountHolderName = new char[holderName.length() + 1];
    std::strcpy(accountHolderName, holderName.c_str());
}

// Standard Methods
void BankAccount::deposit(double amount) {
    *this += amount;
}

bool BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        *this -= amount;
        return true;
    }
    return false;
}

// Overloaded Arithmetic Assignment Operators
BankAccount& BankAccount::operator+=(double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Successfully deposited $" << std::fixed << std::setprecision(2) << amount << ".\n";
    } else {
        std::cout << "Error: Deposit amount must be positive.\n";
    }
    return *this;
}

BankAccount& BankAccount::operator-=(double amount) {
    if (amount <= 0) {
        std::cout << "Error: Withdrawal amount must be positive.\n";
    } else if (amount > balance) {
        std::cout << "Error: Insufficient funds for withdrawal.\n";
    } else {
        balance -= amount;
        std::cout << "Successfully withdrew $" << std::fixed << std::setprecision(2) << amount << ".\n";
    }
    return *this;
}

// Overloaded Comparison Operators
bool BankAccount::operator==(const BankAccount& other) const {
    return this->accountNumber == other.accountNumber;
}

bool BankAccount::operator<(const BankAccount& other) const {
    return this->balance < other.balance;
}

bool BankAccount::operator>(const BankAccount& other) const {
    return this->balance > other.balance;
}

// Static Utility Functions
void BankAccount::printAccount(const BankAccount& account) {
    std::cout << "----------------------------------------\n"
              << "Account Number : " << account.accountNumber << "\n"
              << "Account Holder : " << account.accountHolderName << "\n"
              << "Balance        : $" << std::fixed << std::setprecision(2) << account.balance << "\n"
              << "----------------------------------------\n";
}

BankAccount BankAccount::createAccountFromInput() {
    std::string accNum, holderName;
    double initialBalance;

    std::cout << "Enter Account Number: ";
    std::cin >> accNum;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Account Holder Name: ";
    std::getline(std::cin, holderName);

    std::cout << "Enter Initial Balance: $";
    while (!(std::cin >> initialBalance) || initialBalance < 0) {
        std::cout << "Invalid amount. Enter a non-negative balance: $";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return BankAccount(accNum, holderName, initialBalance);
}
