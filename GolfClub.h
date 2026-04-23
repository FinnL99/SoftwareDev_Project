#ifndef GOLFCLUB_H
#define GOLFCLUB_H

#include <string>
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

    string getClubName();
    void setClubName(string name);

    bool addGolfer(Golfer*);
    bool addTeeTime(TeeTime*);

    Golfer* getGolferById(string id);
    Golfer* getGuestByName(string name);

    TeeTime* getTeeTime(string day, string time);
    bool removeTeeTime(string day, string time);
    bool editTeeTime(string oldDay, string oldTime, string newDay, string newTime);

    void displayTeeTimes();
    void displayTeeTimesWithIndex();
    TeeTime* getTeeTimeByIndex(int index);

    string generateNewMemberID();

    void saveToFile();
    void loadFromFile();
};

#endif