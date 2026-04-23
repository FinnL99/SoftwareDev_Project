// This file contains the implementation code for the Member class
#include "Member.h"

Member::Member() : Golfer()
{
    memberID = "";
    cout << "calling default constructor for Member" << endl;
}

Member::Member(string n, int h, string id) : Golfer(n, h)
{
    memberID = id;
    cout << "calling three parameter constructor for Member" << endl;
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
    // members log in using ID rather than name
    return memberID;
}

void Member::display()
{
    cout << "Member: " << getName()
         << " has handicap " << getHandicap()
         << " and member ID: " << getMemberID() << endl;
}