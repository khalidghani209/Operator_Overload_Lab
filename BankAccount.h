#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <iostream>

/**
 * @class BankAccount
 * @brief Represents a bank account with dynamic memory management,
 *        overloaded operators, and static utility methods.
 */
class BankAccount {
private:
    std::string accountNumber;
    char* accountHolderName; // Dynamically allocated to demonstrate the Rule of Three
    double balance;

public:
    // --- Constructors ---
    /**
     * @brief Default constructor initializing an empty account.
     */
    BankAccount();

    /**
     * @brief Parameterized constructor to initialize account details.
     * @param accNum The unique account number.
     * @param holderName The name of the account holder.
     * @param initialBalance The starting balance of the account.
     */
    BankAccount(const std::string& accNum, const std::string& holderName, double initialBalance);

    // --- The Rule of Three ---
    /**
     * @brief Copy constructor performing a deep copy of dynamic memory.
     * @param other The BankAccount object to copy from.
     */
    BankAccount(const BankAccount& other);

    /**
     * @brief Copy assignment operator performing a deep copy and handling self-assignment.
     * @param other The BankAccount object to assign from.
     * @return Reference to the updated BankAccount object.
     */
    BankAccount& operator=(const BankAccount& other);

    /**
     * @brief Destructor that frees dynamically allocated memory.
     */
    ~BankAccount();

    // --- Accessors (Getters) ---
    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    double getBalance() const;

    // --- Mutators (Setters) ---
    void setAccountHolderName(const std::string& holderName);

    // --- Standard Deposit/Withdraw (kept for backward compatibility) ---
    void deposit(double amount);
    bool withdraw(double amount);

    // --- Overloaded Arithmetic Assignment Operators ---
    /**
     * @brief Adds a positive amount to the account balance in-place.
     * @param amount The amount to deposit.
     * @return Reference to the modified BankAccount.
     */
    BankAccount& operator+=(double amount);

    /**
     * @brief Subtracts a positive amount from the balance in-place if funds permit.
     * @param amount The amount to withdraw.
     * @return Reference to the modified BankAccount.
     */
    BankAccount& operator-=(double amount);

    // --- Overloaded Comparison Operators ---
    /**
     * @brief Compares two accounts for equality based on account number.
     */
    bool operator==(const BankAccount& other) const;

    /**
     * @brief Checks if this account's balance is less than another's.
     */
    bool operator<(const BankAccount& other) const;

    /**
     * @brief Checks if this account's balance is greater than another's.
     */
    bool operator>(const BankAccount& other) const;

    // --- Static Utility Functions ---
    /**
     * @brief Prints the formatted details of a BankAccount object to std::cout.
     * @param account The BankAccount to display.
     */
    static void printAccount(const BankAccount& account);

    /**
     * @brief Prompts the user for input and returns a newly created BankAccount object.
     * @return A new BankAccount initialized with user-provided data.
     */
    static BankAccount createAccountFromInput();
};

#endif // BANKACCOUNT_H
