#ifndef _GOLFCLUB_
#define _GOLFCLUB_

#include <string>
#include <iostream>
#include <vector>
#include "Golfer.h"
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
    void addTeeTime(TeeTime*);

    void displayGolfers();
    void displayTeeTimes();
};

#endif