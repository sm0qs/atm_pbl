/**
 * @file storage.cpp
 * @brief Implementation of file-based user data persistence.
 */

#include "storage.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace storage {

std::map<std::string, User> loadUsers(const std::string& filename) {
    std::map<std::string, User> users;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        return users;
    }

    nlohmann::json j;
    try {
        file >> j;
        for (const auto& item : j) {
            User u = User::from_json(item);
            users[u.accountNumber] = u;
        }
    } catch (...) {}

    return users;
}

void saveUsers(const std::map<std::string, User>& users, const std::string& filename) {
    nlohmann::json j = nlohmann::json::array();
    for (const auto& pair : users) {
        j.push_back(pair.second.to_json());
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
    }
}

} // namespace storage
