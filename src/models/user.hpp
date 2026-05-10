/**
 * @file user.hpp
 * @brief Header file for User and Transaction models.
 */

#ifndef ATM_USER_HPP
#define ATM_USER_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

/**
 * @struct Transaction
 * @brief Represents a single financial transaction record.
 */
struct Transaction {
    std::string type;   ///< Type of transaction (e.g., "Deposit", "Withdrawal")
    double amount;      ///< Transaction amount
};

/**
 * @class User
 * @brief Represents a bank user account with security and balance information.
 */
class User {
public:
    std::string accountNumber;      ///< Unique account identifier
    std::string hashedPassword;     ///< Argon2id hash of the user's PIN
    double balance;                 ///< Current account balance
    int loginAttempts;              ///< Failed login attempt counter
    bool isBlocked;                 ///< Account lockout status
    std::vector<Transaction> history; ///< List of user's transactions

    /**
     * @brief Default constructor.
     */
    User();

    /**
     * @brief Parameterized constructor.
     * @param acc Account identifier.
     * @param hashedPwd Already hashed PIN.
     * @param initialBalance Starting account balance.
     */
    User(std::string acc, std::string hashedPwd, double initialBalance);

    /**
     * @brief Serializes User object to JSON format.
     * @return nlohmann::json object.
     */
    nlohmann::json to_json() const;

    /**
     * @brief Deserializes User object from JSON format.
     * @param j JSON object containing user data.
     * @return User object.
     */
    static User from_json(const nlohmann::json& j);
};

#endif
