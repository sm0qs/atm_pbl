#include <gtest/gtest.h>
#include "auth/auth.hpp"

class AuthTest : public ::testing::Test {
protected:
    void SetUp() override {
        auth::init();
    }
};

TEST_F(AuthTest, HashAndVerifyCorrectPassword) {
    std::string password = "secret_pin_1234";
    std::string hash = auth::hashPassword(password);
    
    EXPECT_TRUE(auth::verifyPassword(hash, password));
}

TEST_F(AuthTest, VerifyWrongPasswordFails) {
    std::string password = "correct_password";
    std::string hash = auth::hashPassword(password);
    
    EXPECT_FALSE(auth::verifyPassword(hash, "wrong_password"));
}

TEST_F(AuthTest, DifferentHashesForSamePassword) {
    std::string password = "same_password";
    std::string hash1 = auth::hashPassword(password);
    std::string hash2 = auth::hashPassword(password);
    
    // Sodium uses random salt, so hashes must be different
    EXPECT_NE(hash1, hash2);
    EXPECT_TRUE(auth::verifyPassword(hash1, password));
    EXPECT_TRUE(auth::verifyPassword(hash2, password));
}
