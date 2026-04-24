#include <gtest/gtest.h>
#include "Golfer.h"
#include "Member.h"
#include "Guest.h"

// Test 1: Constructor Chaining & Initialization Path
// Covers: Golfer, Member, Guest constructors and inheritance

TEST(ConstructorTest, GolferParameterizedConstructor) {
    Golfer g("Test", 10);
    EXPECT_EQ(g.getName(), "Test");
    EXPECT_EQ(g.getHandicap(), 10);
}

TEST(ConstructorTest, GolferDefaultConstructor) {
    Golfer g;
    EXPECT_EQ(g.getName(), "Unknown");
    EXPECT_EQ(g.getHandicap(), 0);
}

TEST(ConstructorTest, MemberParameterizedConstructor) {
    Member m("Alice", 5, "M001");
    EXPECT_EQ(m.getName(), "Alice");
    EXPECT_EQ(m.getHandicap(), 5);
    EXPECT_EQ(m.getMemberID(), "M001");
}

TEST(ConstructorTest, MemberDefaultConstructor) {
    Member m;
    EXPECT_EQ(m.getName(), "Unknown");
    EXPECT_EQ(m.getHandicap(), 0);
    EXPECT_EQ(m.getMemberID(), "");
}

TEST(ConstructorTest, GuestParameterizedConstructor) {
    Guest g("Bob", 8);
    EXPECT_EQ(g.getName(), "Bob");
    EXPECT_EQ(g.getHandicap(), 8);
}

TEST(ConstructorTest, GuestDefaultConstructor) {
    Guest g;
    EXPECT_EQ(g.getName(), "Unknown");
    EXPECT_EQ(g.getHandicap(), 0);
}

// Test 2: getLoginKey() Branch Coverage
// Covers: Member returns memberID, Guest returns name

TEST(LoginKeyTest, MemberGetLoginKeyReturnsMemberID) {
    Member m("Alice", 5, "M001");
    EXPECT_EQ(m.getLoginKey(), "M001");
}

TEST(LoginKeyTest, GuestGetLoginKeyReturnsName) {
    Guest g("Bob", 8);
    EXPECT_EQ(g.getLoginKey(), "Bob");
}

TEST(LoginKeyTest, MemberGetLoginKeyDiffersFromName) {
    Member m("Alice", 5, "ID123");
    // Member login uses ID, not name
    EXPECT_NE(m.getLoginKey(), m.getName());
    EXPECT_EQ(m.getLoginKey(), "ID123");
}

// Test 3: Setter/Getter Pair Coverage
// Covers: Golfer setters/getters, Member memberID setter/getter

TEST(SetterGetterTest, GolferSetName) {
    Golfer g;
    g.setName("New");
    EXPECT_EQ(g.getName(), "New");
}

TEST(SetterGetterTest, GolferSetHandicap) {
    Golfer g;
    g.setHandicap(20);
    EXPECT_EQ(g.getHandicap(), 20);
}

TEST(SetterGetterTest, MemberSetMemberID) {
    Member m;
    m.setMemberID("NEWID");
    EXPECT_EQ(m.getMemberID(), "NEWID");
}

TEST(SetterGetterTest, MemberSetNameAndHandicap) {
    Member m;
    m.setName("UpdatedName");
    m.setHandicap(15);
    EXPECT_EQ(m.getName(), "UpdatedName");
    EXPECT_EQ(m.getHandicap(), 15);
}

TEST(SetterGetterTest, GuestSetNameAndHandicap) {
    Guest g;
    g.setName("GuestName");
    g.setHandicap(12);
    EXPECT_EQ(g.getName(), "GuestName");
    EXPECT_EQ(g.getHandicap(), 12);
}

// Additional edge case tests

TEST(EdgeCaseTest, EmptyNameStrings) {
    Golfer g("", 0);
    EXPECT_EQ(g.getName(), "");
    EXPECT_EQ(g.getHandicap(), 0);
}

TEST(EdgeCaseTest, NegativeHandicap) {
    Golfer g("Test", -5);
    EXPECT_EQ(g.getHandicap(), -5);
}

TEST(EdgeCaseTest, MemberEmptyMemberID) {
    Member m("Name", 10, "");
    EXPECT_EQ(m.getMemberID(), "");
    EXPECT_EQ(m.getLoginKey(), "");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}