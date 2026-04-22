#ifndef _GOLFER_
#define _GOLFER_

#include <string>
#include <iostream>
using namespace std;

class Golfer
{
private:
    string name;
    int handicap;

public:
    Golfer();
    Golfer(string name, int handicap);

    void setName(string);
    string getName();

    void setHandicap(int);
    int getHandicap();

    void display();
};

#endif