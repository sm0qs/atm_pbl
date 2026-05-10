/**
 * @file auth.hpp
 * @brief Authentication module using libsodium for secure hashing.
 */

#ifndef ATM_AUTH_HPP
#define ATM_AUTH_HPP

#include <string>

/**
 * @namespace auth
 * @brief Contains cryptographic utility functions.
 */
namespace auth {

/**
 * @brief Initializes the sodium library.
 */
void init();

/**
 * @brief Securely hashes a password.
 * @param password The plain text password.
 * @return String containing the hash.
 */
std::string hashPassword(const std::string& password);

/**
 * @brief Verifies a password against a stored hash.
 * @param hashedPassword The hash to verify against.
 * @param password The plain text password to verify.
 * @return true if matches, false otherwise.
 */
bool verifyPassword(const std::string& hashedPassword, const std::string& password);

} // namespace auth

#endif
