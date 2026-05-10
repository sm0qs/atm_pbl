/**
 * @file main.cpp
 * @brief Entry point for the secure ATM simulator application.
 */

#include "auth/auth.hpp"
#include "logic/atm.hpp"
#include <iostream>

/**
 * @brief Main function.
 * @return 0 on success, 1 on critical error.
 */
int main() {
    try {
        auth::init();
    } catch (const std::exception& e) {
        std::cerr << "Critical error: " << e.what() << std::endl;
        return 1;
    }

    ATMSystem atm("users_data.json");
    atm.run();

    return 0;
}
