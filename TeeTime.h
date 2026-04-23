#ifndef TEETIME_H
#define TEETIME_H

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

    // returns list of golfers booked into this slot (needed for file saving later)
    vector<Golfer*> getGolfers();

    bool addGolfer(Golfer*);
    bool removeGolfer(string name);
    bool isFull();
    bool isGolferAlreadyBooked(string name);

    void display();
};

#endif