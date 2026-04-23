#include "Member.h"

Member::Member() : Golfer()
{
    memberID = "M000";
}

Member::Member(string n, int h, string id) : Golfer(n, h)
{
    memberID = id;
}

string Member::getMemberID()
{
    return memberID;
}

void Member::setMemberID(string id)
{
    memberID = id;
}

string Member::getLoginKey()
{
    return memberID; // login uses ID
}

void Member::display()
{
    cout << "Member: " << name
         << " | Handicap: " << handicap
         << " | ID: " << memberID << endl;
}