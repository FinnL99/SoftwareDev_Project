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

    vector<Golfer*> getGolfers(); // used for saving to file

    bool addGolfer(Golfer*);
    bool removeGolfer(string name);

    bool isFull();
    bool isGolferAlreadyBooked(string name);

    void display();
};

#endif