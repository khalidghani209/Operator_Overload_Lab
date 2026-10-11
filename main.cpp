#include "BankAccount.h"
#include <iostream>
#include <vector>
#include <limits>

int findAccountIndex(const std::vector<BankAccount>& accounts, const std::string& accNum) {
    // Uses temporary object and overloaded == operator to match account number
    BankAccount temp(accNum, "", 0.0);
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i] == temp) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int main() {
    std::vector<BankAccount> accounts;
    int choice = 0;

    do {
        std::cout << "\n=== Bank Account Management System ===\n"
                  << "1. Create New Account (Static Function)\n"
                  << "2. Deposit Funds (Operator +=)\n"
                  << "3. Withdraw Funds (Operator -=)\n"
                  << "4. Display All Accounts (Static Function)\n"
                  << "5. Compare Two Accounts (Operators ==, <, >)\n"
                  << "6. Demonstrate Rule of Three (Deep Copy Test)\n"
                  << "7. Exit\n"
                  << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                BankAccount newAcc = BankAccount::createAccountFromInput();
                if (findAccountIndex(accounts, newAcc.getAccountNumber()) != -1) {
                    std::cout << "Error: An account with that number already exists.\n";
                } else {
                    accounts.push_back(newAcc);
                    std::cout << "Account created successfully!\n";
                }
                break;
            }
            case 2: {
                std::string accNum;
                double amount;
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                int idx = findAccountIndex(accounts, accNum);
                if (idx != -1) {
                    std::cout << "Enter Deposit Amount: $";
                    std::cin >> amount;
                    accounts[idx] += amount; // Using overloaded +=
                } else {
                    std::cout << "Account not found.\n";
                }
                break;
            }
            case 3: {
                std::string accNum;
                double amount;
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                int idx = findAccountIndex(accounts, accNum);
                if (idx != -1) {
                    std::cout << "Enter Withdrawal Amount: $";
                    std::cin >> amount;
                    accounts[idx] -= amount; // Using overloaded -=
                } else {
                    std::cout << "Account not found.\n";
                }
                break;
            }
            case 4: {
                if (accounts.empty()) {
                    std::cout << "No accounts available to display.\n";
                } else {
                    for (const auto& acc : accounts) {
                        BankAccount::printAccount(acc); // Using static printAccount
                    }
                }
                break;
            }
            case 5: {
                if (accounts.size() < 2) {
                    std::cout << "Need at least 2 accounts to compare.\n";
                    break;
                }
                std::string acc1, acc2;
                std::cout << "Enter First Account Number: ";
                std::cin >> acc1;
                std::cout << "Enter Second Account Number: ";
                std::cin >> acc2;

                int idx1 = findAccountIndex(accounts, acc1);
                int idx2 = findAccountIndex(accounts, acc2);

                if (idx1 != -1 && idx2 != -1) {
                    std::cout << "\n--- Comparison Results ---\n";
                    if (accounts[idx1] == accounts[idx2]) {
                        std::cout << "Accounts have the SAME account number (== is true).\n";
                    } else {
                        std::cout << "Accounts have DIFFERENT account numbers (== is false).\n";
                    }

                    if (accounts[idx1] < accounts[idx2]) {
                        std::cout << "Account " << acc1 << " has a SMALLER balance than Account " << acc2 << " (< is true).\n";
                    } else if (accounts[idx1] > accounts[idx2]) {
                        std::cout << "Account " << acc1 << " has a LARGER balance than Account " << acc2 << " (> is true).\n";
                    } else {
                        std::cout << "Both accounts have an EQUAL balance.\n";
                    }
                } else {
                    std::cout << "One or both accounts not found.\n";
                }
                break;
            }
            case 6: {
                std::cout << "\n--- Testing Rule of Three (Deep Copy) ---\n";
                BankAccount original("999", "Original Holder", 500.00);
                BankAccount copyConstructed(original); // Calls Copy Constructor
                BankAccount assigned;
                assigned = original; // Calls Copy Assignment Operator

                // Modify the copies to prove deep copy (original remains unchanged)
                copyConstructed.setAccountHolderName("Copy Constructed Holder");
                copyConstructed += 250.00;

                assigned.setAccountHolderName("Assigned Holder");
                assigned -= 100.00;

                std::cout << "Original Account:\n";
                BankAccount::printAccount(original);
                std::cout << "Copy Constructed Account (Modified):\n";
                BankAccount::printAccount(copyConstructed);
                std::cout << "Copy Assigned Account (Modified):\n";
                BankAccount::printAccount(assigned);
                break;
            }
            case 7:
                std::cout << "Exiting program. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please select 1-7.\n";
        }
    } while (choice != 7);

    return 0;
}
