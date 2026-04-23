#include "GolfClub.h"

GolfClub::GolfClub()
{
    clubName = "Unknown Club";
}

GolfClub::GolfClub(string name)
{
    clubName = name;
}

void GolfClub::setClubName(string name)
{
    clubName = name;
}

string GolfClub::getClubName()
{
    return clubName;
}

void GolfClub::addGolfer(Golfer* g)
{
    golfers.push_back(g);
}

void GolfClub::addTeeTime(TeeTime* t)
{
    teeTimes.push_back(t);
}

void GolfClub::displayGolfers()
{
    cout << "Golfers in " << clubName << ":" << endl;

    for (int i = 0; i < golfers.size(); i++)
    {
        golfers[i]->display();
    }
}

void GolfClub::displayTeeTimes()
{
    cout << "Tee times in " << clubName << ":" << endl;

    for (int i = 0; i < teeTimes.size(); i++)
    {
        teeTimes[i]->display();
    }
}