// file containing interface for Member class
#ifndef _MEMBER_
#define _MEMBER_

#include "Golfer.h"
#include <string>
#include <iostream>
using namespace std;

class Member : public Golfer
{
private:
    // unique field for Member only
    string memberID;

public:
    Member(); // default parameterless constructor
    Member(string name, int handicap, string memberID); // user-defined overloaded constructor

    string getMemberID();
    void setMemberID(string);

    string getLoginKey() override;
    void display() override;
};

#endif /* _MEMBER_ */