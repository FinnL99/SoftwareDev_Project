#ifndef _GOLFCLUB_
#define _GOLFCLUB_

#include <string>
#include <iostream>
#include <vector>
#include "Golfer.h"
#include "Member.h"
#include "Guest.h"
#include "TeeTime.h"
using namespace std;

class GolfClub
{
private:
    string clubName;
    vector<Golfer*> golfers;
    vector<TeeTime*> teeTimes;

public:
    GolfClub();
    GolfClub(string name);

    void setClubName(string);
    string getClubName();

    void addGolfer(Golfer*);
    bool addTeeTime(TeeTime*);

    Golfer* getGolferById(string);
    Golfer* getGuestByName(string);
    TeeTime* getTeeTime(string, string);

    bool removeTeeTime(string, string);

    void displayGolfers();
    void displayTeeTimes();
};

#endif