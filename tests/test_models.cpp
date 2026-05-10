#include <gtest/gtest.h>
#include "models/user.hpp"

TEST(ModelsTest, UserSerialization) {
    User u("12345", "hashed_stuff", 1000.50);
    u.history.push_back({"Deposit", 500.0});
    u.isBlocked = true;

    nlohmann::json j = u.to_json();
    
    EXPECT_EQ(j["accountNumber"], "12345");
    EXPECT_EQ(j["balance"], 1000.50);
    EXPECT_TRUE(j["isBlocked"]);
    EXPECT_EQ(j["history"].size(), 1);
}

TEST(ModelsTest, UserDeserialization) {
    nlohmann::json j = {
        {"accountNumber", "999"},
        {"hashedPassword", "some_hash"},
        {"balance", 50.0},
        {"loginAttempts", 2},
        {"isBlocked", false},
        {"history", nlohmann::json::array({
            {{"type", "Withdrawal"}, {"amount", 10.0}}
        })}
    };

    User u = User::from_json(j);
    
    EXPECT_EQ(u.accountNumber, "999");
    EXPECT_EQ(u.balance, 50.0);
    EXPECT_EQ(u.loginAttempts, 2);
    EXPECT_FALSE(u.isBlocked);
    ASSERT_EQ(u.history.size(), 1);
    EXPECT_EQ(u.history[0].type, "Withdrawal");
}
