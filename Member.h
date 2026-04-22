#ifndef _MEMBER_
#define _MEMBER_

#include "Golfer.h"
#include <string>
#include <iostream>
using namespace std;

class Member : public Golfer
{
private:
    string memberID;

public:
    Member();
    Member(string name, int handicap, string memberID);

    void setMemberID(string);
    string getMemberID();

    void display();
};

#endif