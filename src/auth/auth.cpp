/**
 * @file auth.cpp
 * @brief Implementation of sodium-based authentication.
 */

#include "auth.hpp"
#include <sodium.h>
#include <stdexcept>

namespace auth {

void init() {
    if (sodium_init() < 0) {
        throw std::runtime_error("Failed to initialize libsodium");
    }
}

std::string hashPassword(const std::string& password) {
    char hashedPassword[crypto_pwhash_STRBYTES];
    if (crypto_pwhash_str(hashedPassword, password.c_str(), password.length(),
                          crypto_pwhash_OPSLIMIT_INTERACTIVE,
                          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
        throw std::runtime_error("Password hashing failed");
    }
    return std::string(hashedPassword);
}

bool verifyPassword(const std::string& hashedPassword, const std::string& password) {
    return crypto_pwhash_str_verify(hashedPassword.c_str(), password.c_str(), password.length()) == 0;
}

} // namespace auth
