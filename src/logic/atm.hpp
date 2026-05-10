/**
 * @file atm.hpp
 * @brief Main ATM system logic and controller.
 */

#ifndef ATM_LOGIC_HPP
#define ATM_LOGIC_HPP

#include "../models/user.hpp"
#include <map>
#include <string>

/**
 * @class ATMSystem
 * @brief Controller class managing the ATM workflow, users, and security.
 */
class ATMSystem {
private:
    std::map<std::string, User> users; ///< In-memory user database
    std::string dataFile;             ///< Path to the JSON data file

    /**
     * @brief Persists the current state of users to the data file.
     */
    void saveState();

    /**
     * @brief Displays the authenticated user menu and handles operations.
     * @param user Reference to the currently logged-in user.
     */
    void userMenu(User& user);

    /**
     * @brief Displays the administrative menu and handles management tasks.
     */
    void adminMenu();

public:
    /**
     * @brief Constructs the ATM system and loads users from file.
     * @param dataFilename Path to the JSON storage.
     */
    ATMSystem(const std::string& dataFilename);
    
    /**
     * @brief Securely adds a new user to the system.
     * @param acc Account number.
     * @param pin Plain text PIN (will be hashed).
     * @param initialBalance Starting balance.
     */
    void addUser(const std::string& acc, const std::string& pin, double initialBalance);
    
    /**
     * @brief Starts the main application execution loop.
     */
    void run();
};

#endif
