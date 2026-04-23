// file containing interface for Golfer class
#ifndef _GOLFER_
#define _GOLFER_

#include <string>
#include <iostream>
using namespace std;

class Golfer
{
protected:
    // protected because Member and Guest both need access
    string name;
    int handicap;

public:
    Golfer(); // default constructor
    Golfer(string name, int handicap); // user-defined constructor
    virtual ~Golfer(); // virtual destructor needed because we use base class pointers

    string getName();
    void setName(string);

    int getHandicap();
    void setHandicap(int);

    // pure virtual functions make Golfer abstract
    // this means Member and Guest must provide their own versions
    virtual string getLoginKey() = 0;
    virtual void display() = 0;
};

#endif /* _GOLFER_ */