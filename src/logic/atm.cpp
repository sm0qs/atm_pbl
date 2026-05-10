/**
 * @file atm.cpp
 * @brief Implementation of the main ATM system controller logic.
 */

#include "atm.hpp"
#include "../auth/auth.hpp"
#include "../storage/storage.hpp"
#include "../ui/ui.hpp"
#include <iostream>
#include <iomanip>

ATMSystem::ATMSystem(const std::string& dataFilename) : dataFile(dataFilename) {
    users = storage::loadUsers(dataFile);
}

void ATMSystem::saveState() {
    storage::saveUsers(users, dataFile);
}

void ATMSystem::addUser(const std::string& acc, const std::string& pin, double initialBalance) {
    if (users.find(acc) == users.end()) {
        std::string hashedPin = auth::hashPassword(pin);
        users[acc] = User(acc, hashedPin, initialBalance);
        saveState();
    }
}

void ATMSystem::adminMenu() {
    int choice;
    do {
        ui::printHeader("ADMINISTRATOR PANEL");
        std::cout << "1. Create new user account\n";
        std::cout << "2. Reset user PIN\n";
        std::cout << "3. Unlock account\n";
        std::cout << "4. List all accounts\n";
        std::cout << "5. Return to main menu\n";
        std::cout << "Choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            std::string acc, pin;
            double bal;
            std::cout << "New account number: "; std::cin >> acc;
            if (acc == "admin") {
                std::cout << "[ERROR] Cannot create another 'admin' account.\n";
            } else if (users.find(acc) == users.end()) {
                std::cout << "PIN for account: "; std::cin >> pin;
                std::cout << "Initial balance: "; std::cin >> bal;
                addUser(acc, pin, bal);
                std::cout << "[SUCCESS] User account created.\n";
            } else {
                std::cout << "[ERROR] Account number already exists.\n";
            }
            ui::pauseAndContinue();
            break;
        }
        case 2: {
            std::string acc, newPin;
            std::cout << "Account number to reset PIN: "; std::cin >> acc;
            if (users.find(acc) != users.end()) {
                std::cout << "New PIN: "; std::cin >> newPin;
                users[acc].hashedPassword = auth::hashPassword(newPin);
                saveState();
                std::cout << "[SUCCESS] PIN has been changed.\n";
            } else {
                std::cout << "[ERROR] User not found.\n";
            }
            ui::pauseAndContinue();
            break;
        }
        case 3: {
            std::string acc;
            std::cout << "Account number to unlock: "; std::cin >> acc;
            if (users.find(acc) != users.end()) {
                users[acc].isBlocked = false;
                users[acc].loginAttempts = 0;
                saveState();
                std::cout << "[SUCCESS] Account unlocked.\n";
            } else {
                std::cout << "[ERROR] User not found.\n";
            }
            ui::pauseAndContinue();
            break;
        }
        case 4: {
            std::cout << "\nALL ACCOUNTS LIST:\n";
            std::cout << std::left << std::setw(15) << "ACCOUNT" << std::setw(10) << "BALANCE" << "STATUS" << std::endl;
            for (const auto& pair : users) {
                std::cout << std::left << std::setw(15) << pair.first 
                          << std::setw(10) << pair.second.balance 
                          << (pair.second.isBlocked ? "BLOCKED" : (pair.first == "admin" ? "ADMIN" : "ACTIVE")) << std::endl;
            }
            ui::pauseAndContinue();
            break;
        }
        }
    } while (choice != 5);
}

bool ATMSystem::verifyLogin(const std::string& acc, const std::string& pin) {
    if (users.find(acc) == users.end()) return false;
    User& u = users[acc];
    if (u.isBlocked) return false;

    if (auth::verifyPassword(u.hashedPassword, pin)) {
        u.loginAttempts = 0;
        u.history.push_back({"Login", 0});
        saveState();
        return true;
    } else {
        u.loginAttempts++;
        if (u.loginAttempts >= 3) {
            u.isBlocked = true;
        }
        saveState();
        return false;
    }
}

bool ATMSystem::performDeposit(const std::string& acc, double amount) {
    if (users.find(acc) == users.end() || amount <= 0) return false;
    User& u = users[acc];
    u.balance += amount;
    u.history.push_back({"Deposit", amount});
    saveState();
    return true;
}

bool ATMSystem::performWithdrawal(const std::string& acc, double amount) {
    if (users.find(acc) == users.end() || amount <= 0) return false;
    User& u = users[acc];
    if (u.balance >= amount) {
        u.balance -= amount;
        u.history.push_back({"Withdrawal", amount});
        saveState();
        return true;
    } else {
        u.history.push_back({"Rejected Withdrawal", amount});
        saveState();
        return false;
    }
}

void ATMSystem::userMenu(User& user) {
    int choice;
    do {
        ui::printHeader("ACCOUNT: " + user.accountNumber);
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdrawal\n";
        std::cout << "4. History\n";
        std::cout << "5. Logout\n";
        std::cout << "Choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            std::cout << "Current balance: " << std::fixed << std::setprecision(2) << user.balance << " USD\n";
            ui::pauseAndContinue();
            break;
        case 2: {
            double amt;
            std::cout << "Deposit amount: ";
            if (std::cin >> amt && performDeposit(user.accountNumber, amt)) {
                std::cout << "Successfully deposited.\n";
            } else {
                std::cout << "Deposit failed.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            ui::pauseAndContinue();
            break;
        }
        case 3: {
            double amt;
            std::cout << "Withdrawal amount: ";
            if (std::cin >> amt && performWithdrawal(user.accountNumber, amt)) {
                std::cout << "Successfully withdrawn.\n";
            } else {
                std::cout << "Withdrawal failed (Check balance or amount).\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            ui::pauseAndContinue();
            break;
        }
        case 4:
            std::cout << "\nHISTORY:\n";
            for (auto it = user.history.rbegin(); it != user.history.rend(); ++it) {
                std::cout << it->type << ": " << std::fixed << std::setprecision(2) << it->amount << " USD\n";
            }
            ui::pauseAndContinue();
            break;
        }
    } while (choice != 5);
}

void ATMSystem::run() {
    while (true) {
        bool noAdmin = (users.find("admin") == users.end());

        if (noAdmin) {
            ui::printHeader("INITIAL CONFIGURATION");
            std::cout << "System has no administrator. You must create one.\n";
            std::string pin;
            std::cout << "Set PIN for 'admin' account: ";
            std::cin >> pin;
            addUser("admin", pin, 0.0);
            std::cout << "[SUCCESS] Administrator created. You can now log in.\n";
            ui::pauseAndContinue();
            continue;
        }

        ui::printHeader("ATM - MAIN MENU");
        std::cout << "1. User Login\n";
        std::cout << "2. Administrator Login\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";
        
        int mainChoice;
        if (!(std::cin >> mainChoice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (mainChoice == 3) break;
        
        if (mainChoice == 2) {
            std::string pin;
            std::cout << "Administrator PIN: ";
            std::cin >> pin;
            if (verifyLogin("admin", pin)) {
                adminMenu();
            } else {
                std::cout << "[ERROR] Invalid administrator PIN or blocked.\n";
                ui::pauseAndContinue();
            }
        } else if (mainChoice == 1) {
            std::string acc, pin;
            std::cout << "Account number: "; std::cin >> acc;
            std::cout << "PIN: "; std::cin >> pin;

            if (acc == "admin") {
                std::cout << "[INFO] Use Administrator Login option for this account.\n";
                ui::pauseAndContinue();
                continue;
            }

            if (verifyLogin(acc, pin)) {
                userMenu(users[acc]);
            } else {
                if (users.count(acc) && users[acc].isBlocked) {
                    std::cout << "[ERROR] Account is blocked.\n";
                } else {
                    std::cout << "[ERROR] Invalid account or PIN.\n";
                }
                ui::pauseAndContinue();
            }
        }
    }
}

User ATMSystem::getUser(const std::string& acc) const {
    auto it = users.find(acc);
    if (it == users.end()) {
        throw std::runtime_error("User not found");
    }
    return it->second;
}
