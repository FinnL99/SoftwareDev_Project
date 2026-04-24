#include <gtest/gtest.h>
#include "Member.h"
#include "Guest.h"
#include "TeeTime.h"

// Test 1: successful booking
TEST(TeeTimeTest, AddGolferWhenNotFull)
{
    TeeTime t("Monday", "09:00");
    Member m("Alice", 5, "M001");

    bool result = t.addGolferToTeeTime(&m);

    EXPECT_TRUE(result);
    EXPECT_EQ(t.getBookedCount(), 1);
}

// Test 2: reject duplicate booking
TEST(TeeTimeTest, RejectDuplicateGolfer)
{
    TeeTime t("Tuesday", "10:00");
    Member m("John", 10, "M002");

    bool firstAdd = t.addGolferToTeeTime(&m);
    bool secondAdd = t.addGolferToTeeTime(&m);

    EXPECT_TRUE(firstAdd);
    EXPECT_FALSE(secondAdd);
    EXPECT_EQ(t.getBookedCount(), 1);
}

// Test 3: reject fifth golfer when tee time is full
TEST(TeeTimeTest, RejectFifthGolferWhenFull)
{
    TeeTime t("Wednesday", "11:00");

    Member m1("John", 10, "M001");
    Member m2("Sarah", 8, "M002");
    Guest g1("Tom", 18);
    Guest g2("Emma", 20);
    Guest g3("Extra", 15);

    t.addGolferToTeeTime(&m1);
    t.addGolferToTeeTime(&m2);
    t.addGolferToTeeTime(&g1);
    t.addGolferToTeeTime(&g2);

    bool result = t.addGolferToTeeTime(&g3);

    EXPECT_FALSE(result);
    EXPECT_EQ(t.getBookedCount(), 4);
    EXPECT_TRUE(t.isFull());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}