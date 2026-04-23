#ifndef MEMBER_H
#define MEMBER_H

#include "Golfer.h"

class Member : public Golfer
{
private:
    string memberID;

public:
    Member();
    Member(string name, int handicap, string id);

    string getMemberID();
    void setMemberID(string);

    string getLoginKey(); // used for login
    void display();
};

#endif