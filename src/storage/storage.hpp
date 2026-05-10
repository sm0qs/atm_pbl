/**
 * @file storage.hpp
 * @brief User data persistence layer.
 */

#ifndef ATM_STORAGE_HPP
#define ATM_STORAGE_HPP

#include "../models/user.hpp"
#include <map>
#include <string>

/**
 * @namespace storage
 * @brief Handles file I/O for user data.
 */
namespace storage {

/**
 * @brief Loads user records from a JSON file.
 * @param filename Path to the storage file.
 * @return Map of account numbers to user objects.
 */
std::map<std::string, User> loadUsers(const std::string& filename);

/**
 * @brief Saves user records to a JSON file.
 * @param users Map of users to persist.
 * @param filename Path to the storage file.
 */
void saveUsers(const std::map<std::string, User>& users, const std::string& filename);

} // namespace storage

#endif
