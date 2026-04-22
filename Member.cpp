#include "Member.h"

Member::Member()
{
    name = "Unknown";
    handicap = 0;
    memberID = "M000";
    balance = 0.0;
}

Member::Member(string n, int h, string id)
{
    name = n;
    handicap = h;
    memberID = id;
    balance = 0.0;
}

void Member::setName(string n)
{
    name = n;
}

string Member::getName()
{
    return name;
}

void Member::setHandicap(int h)
{
    handicap = h;
}

int Member::getHandicap()
{
    return handicap;
}

void Member::setMemberID(string id)
{
    memberID = id;
}

string Member::getMemberID()
{
    return memberID;
}

void Member::setBalance(double b)
{
    balance = b;
}

double Member::getBalance()
{
    return balance;
}

void Member::display()
{
    cout << "Member: " << name
         << " | Handicap: " << handicap
         << " | ID: " << memberID
         << " | Balance: " << balance << endl;
}