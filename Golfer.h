#ifndef GOLFER_H
#define GOLFER_H

#include <string>
#include <iostream>
using namespace std;

// base class (abstract) for Member and Guest
class Golfer
{
protected:
    string name;
    int handicap;

public:
    Golfer();
    Golfer(string name, int handicap);
    virtual ~Golfer();

    string getName();
    void setName(string);

    int getHandicap();
    void setHandicap(int);

    // pure virtual functions (forces subclasses to implement these)
    virtual string getLoginKey() = 0;
    virtual void display() = 0;
};

#endif