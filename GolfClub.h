// file containing interface for GolfClub class
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
    GolfClub(string);
    ~GolfClub();

    string getClubName();
    void setClubName(string);

    bool addGolfer(Golfer*);
    Golfer* getGolferById(string);
    Golfer* getGuestByName(string);

    bool addTeeTime(TeeTime*);
    bool removeTeeTime(string, string);
    bool editTeeTime(string, string, string, string);
    TeeTime* getTeeTime(string, string);
    void displayTeeTimes();

    void displayTeeTimesWithIndex();
    TeeTime* getTeeTimeByIndex(int);
    string generateNewMemberID();

    void saveToFile();
    void loadFromFile();
};

#endif /* _GOLFCLUB_ */