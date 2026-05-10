#include <gtest/gtest.h>
#include "logic/atm.hpp"
#include "auth/auth.hpp"
#include <fstream>
#include <cstdio>

class LogicTest : public ::testing::Test {
protected:
    const std::string testDb = "test_users.json";

    void SetUp() override {
        auth::init();
        std::remove(testDb.c_str()); // Ensure clean state
    }

    void TearDown() override {
        std::remove(testDb.c_str());
    }
};

TEST_F(LogicTest, InitialSetupAddsAdmin) {
    ATMSystem atm(testDb);
    atm.addUser("admin", "9999", 0.0);
    
    User u = atm.getUser("admin");
    EXPECT_EQ(u.accountNumber, "admin");
    EXPECT_TRUE(auth::verifyPassword(u.hashedPassword, "9999"));
}

TEST_F(LogicTest, LoginAndOperations) {
    ATMSystem atm(testDb);
    atm.addUser("123", "1111", 1000.0);
    
    // Successful login
    EXPECT_TRUE(atm.verifyLogin("123", "1111"));
    
    // Deposit
    EXPECT_TRUE(atm.performDeposit("123", 500.0));
    EXPECT_EQ(atm.getUser("123").balance, 1500.0);
    
    // Withdrawal
    EXPECT_TRUE(atm.performWithdrawal("123", 200.0));
    EXPECT_EQ(atm.getUser("123").balance, 1300.0);
    
    // Insufficient funds
    EXPECT_FALSE(atm.performWithdrawal("123", 2000.0));
    EXPECT_EQ(atm.getUser("123").balance, 1300.0); // Balance unchanged
}

TEST_F(LogicTest, AccountLockoutAfterThreeAttempts) {
    ATMSystem atm(testDb);
    atm.addUser("lockme", "0000", 100.0);
    
    // 3 failed attempts
    EXPECT_FALSE(atm.verifyLogin("lockme", "1111"));
    EXPECT_FALSE(atm.verifyLogin("lockme", "2222"));
    EXPECT_FALSE(atm.verifyLogin("lockme", "3333"));
    
    // Should be blocked now
    User u = atm.getUser("lockme");
    EXPECT_TRUE(u.isBlocked);
    
    // Even correct PIN should fail when blocked
    EXPECT_FALSE(atm.verifyLogin("lockme", "0000"));
}
