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
    ~GolfClub();

    void setClubName(string name);
    string getClubName();

    bool addGolfer(Golfer* g);
    bool addTeeTime(TeeTime* t);

    Golfer* getGolferById(string id);
    Golfer* getGuestByName(string name);
    TeeTime* getTeeTime(string day, string time);

    bool removeTeeTime(string day, string time);
    bool editTeeTime(string oldDay, string oldTime, string newDay, string newTime);

    void displayGolfers();
    void displayTeeTimes();

    void saveToFile();
    void loadFromFile();

    string generateMemberID(); // improved member ID generation
};

#endif