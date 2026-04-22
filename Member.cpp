#include "Member.h"

Member::Member() : Golfer()
{
    memberID = "M000";
}

Member::Member(string name, int handicap, string id) : Golfer(name, handicap)
{
    memberID = id;
}

void Member::setMemberID(string id)
{
    memberID = id;
}

string Member::getMemberID()
{
    return memberID;
}

void Member::display()
{
    cout << "Member: " << getName()
         << " | Handicap: " << getHandicap()
         << " | ID: " << memberID << endl;
}