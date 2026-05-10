/**
 * @file user.cpp
 * @brief Implementation of User model serialization and logic.
 */

#include "user.hpp"

User::User() : balance(0.0), loginAttempts(0), isBlocked(false) {}

User::User(std::string acc, std::string hashedPwd, double initialBalance)
    : accountNumber(std::move(acc)), hashedPassword(std::move(hashedPwd)),
      balance(initialBalance), loginAttempts(0), isBlocked(false) {}

nlohmann::json User::to_json() const {
    nlohmann::json j;
    j["accountNumber"] = accountNumber;
    j["hashedPassword"] = hashedPassword;
    j["balance"] = balance;
    j["loginAttempts"] = loginAttempts;
    j["isBlocked"] = isBlocked;
    
    nlohmann::json hist = nlohmann::json::array();
    for (const auto& t : history) {
        hist.push_back({{"type", t.type}, {"amount", t.amount}});
    }
    j["history"] = hist;
    
    return j;
}

User User::from_json(const nlohmann::json& j) {
    User u;
    u.accountNumber = j.at("accountNumber").get<std::string>();
    u.hashedPassword = j.at("hashedPassword").get<std::string>();
    u.balance = j.at("balance").get<double>();
    u.loginAttempts = j.at("loginAttempts").get<int>();
    u.isBlocked = j.at("isBlocked").get<bool>();
    
    if (j.contains("history")) {
        for (const auto& item : j["history"]) {
            u.history.push_back({item.at("type").get<std::string>(), item.at("amount").get<double>()});
        }
    }
    return u;
}
