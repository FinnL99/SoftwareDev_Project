#include <gtest/gtest.h>
#include "Golfer.h"
#include "Member.h"
#include "Guest.h"
#include "TeeTime.h"

// Test 1: Constructor and inheritance behaviour
// Covers Member and Guest constructors using Golfer base class data

TEST(ConstructorTest, MemberParameterizedConstructor)
{
    Member m("Alice", 5, "M001");

    EXPECT_EQ(m.getName(), "Alice");
    EXPECT_EQ(m.getHandicap(), 5);
    EXPECT_EQ(m.getMemberID(), "M001");
}

TEST(ConstructorTest, MemberDefaultConstructor)
{
    Member m;

    EXPECT_EQ(m.getName(), "Unknown");
    EXPECT_EQ(m.getHandicap(), 0);
}

TEST(ConstructorTest, GuestParameterizedConstructor)
{
    Guest g("Bob", 8);

    EXPECT_EQ(g.getName(), "Bob");
    EXPECT_EQ(g.getHandicap(), 8);
}

TEST(ConstructorTest, GuestDefaultConstructor)
{
    Guest g;

    EXPECT_EQ(g.getName(), "Unknown");
    EXPECT_EQ(g.getHandicap(), 0);
}


// Test 2: Polymorphism / getLoginKey()
// Covers different behaviour for Member and Guest

TEST(LoginKeyTest, MemberLoginKeyReturnsMemberID)
{
    Member m("Alice", 5, "M001");

    EXPECT_EQ(m.getLoginKey(), "M001");
}

TEST(LoginKeyTest, GuestLoginKeyReturnsName)
{
    Guest g("Bob", 8);

    EXPECT_EQ(g.getLoginKey(), "Bob");
}

TEST(LoginKeyTest, MemberLoginKeyDiffersFromName)
{
    Member m("Alice", 5, "ID123");

    EXPECT_NE(m.getLoginKey(), m.getName());
    EXPECT_EQ(m.getLoginKey(), "ID123");
}


// Test 3: Setter and getter testing
// Covers inherited setters/getters and Member-specific setter/getter

TEST(SetterGetterTest, MemberSetNameAndHandicap)
{
    Member m;

    m.setName("UpdatedName");
    m.setHandicap(15);

    EXPECT_EQ(m.getName(), "UpdatedName");
    EXPECT_EQ(m.getHandicap(), 15);
}

TEST(SetterGetterTest, GuestSetNameAndHandicap)
{
    Guest g;

    g.setName("GuestName");
    g.setHandicap(12);

    EXPECT_EQ(g.getName(), "GuestName");
    EXPECT_EQ(g.getHandicap(), 12);
}

TEST(SetterGetterTest, MemberSetMemberID)
{
    Member m;

    m.setMemberID("NEWID");

    EXPECT_EQ(m.getMemberID(), "NEWID");
}


// Test 4: TeeTime successful booking
// White box path: not duplicate and not full

TEST(TeeTimeTest, AddGolferWhenNotFullAndNotDuplicate)
{
    TeeTime t("Monday", "09:00");
    Member m("John", 10, "M001");

    bool result = t.addGolferToTeeTime(&m);

    EXPECT_TRUE(result);
    EXPECT_EQ(t.getBookedCount(), 1);
}


// Test 5: Duplicate booking rejected
// White box path: isGolferAlreadyBooked() returns true

TEST(TeeTimeTest, RejectDuplicateGolfer)
{
    TeeTime t("Monday", "09:00");
    Member m("John", 10, "M001");

    bool firstAdd = t.addGolferToTeeTime(&m);
    bool secondAdd = t.addGolferToTeeTime(&m);

    EXPECT_TRUE(firstAdd);
    EXPECT_FALSE(secondAdd);
    EXPECT_EQ(t.getBookedCount(), 1);
}


// Test 6: Full tee time rejected
// White box path: isFull() returns true after 4 golfers

TEST(TeeTimeTest, RejectFifthGolferWhenFull)
{
    TeeTime t("Tuesday", "10:00");

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


// Test 7: Remove golfer from tee time
// Covers removeGolferFromTeeTime()

TEST(TeeTimeTest, RemoveBookedGolfer)
{
    TeeTime t("Wednesday", "11:00");
    Member m("John", 10, "M001");

    t.addGolferToTeeTime(&m);

    bool removed = t.removeGolferFromTeeTime("M001");

    EXPECT_TRUE(removed);
    EXPECT_EQ(t.getBookedCount(), 0);
}


// Test 8: Removing golfer not booked should fail

TEST(TeeTimeTest, RemoveGolferNotBooked)
{
    TeeTime t("Wednesday", "11:00");

    bool removed = t.removeGolferFromTeeTime("M999");

    EXPECT_FALSE(removed);
    EXPECT_EQ(t.getBookedCount(), 0);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}