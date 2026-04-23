#ifndef _TEETIME_
#define _TEETIME_

#include <string>
#include <iostream>
#include <vector>
#include "Golfer.h"
using namespace std;

class TeeTime
{
private:
    string day;
    string time;
    vector<Golfer*> golfers;
    int maxPlayers;

public:
    TeeTime();
    TeeTime(string day, string time);

    void setDay(string);
    string getDay();

    void setTime(string);
    string getTime();

    int getMaxPlayers();
    int getNumberOfGolfers();

    bool addGolfer(Golfer*);
    bool isFull();

    void display();
};

#endif