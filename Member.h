#ifndef _MEMBER_
#define _MEMBER_

#include <string>
#include <iostream>
using namespace std;

class Member
{
private:
    string name;
    int handicap;
    string memberID;
    double balance;   // will be removed later

public:
    Member();
    Member(string name, int handicap, string memberID);

    void setName(string);
    string getName();

    void setHandicap(int);
    int getHandicap();

    void setMemberID(string);
    string getMemberID();

    void setBalance(double);
    double getBalance();

    void display();
};

#endif