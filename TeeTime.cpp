#include "TeeTime.h"

TeeTime::TeeTime()
{
    day = "Unknown";
    time = "00:00";
    maxPlayers = 4;
}

TeeTime::TeeTime(string d, string t)
{
    day = d;
    time = t;
    maxPlayers = 4;
}

void TeeTime::setDay(string d)
{
    day = d;
}

string TeeTime::getDay()
{
    return day;
}

void TeeTime::setTime(string t)
{
    time = t;
}

string TeeTime::getTime()
{
    return time;
}

int TeeTime::getMaxPlayers()
{
    return maxPlayers;
}

int TeeTime::getNumberOfGolfers()
{
    return golfers.size();
}

bool TeeTime::isFull()
{
    return golfers.size() >= maxPlayers;
}

bool TeeTime::addGolfer(Golfer* g)
{
    if (isFull())
    {
        cout << "Tee time is full" << endl;
        return false;
    }

    golfers.push_back(g);
    cout << g->getName() << " added to tee time" << endl;
    return true;
}

void TeeTime::display()
{
    cout << "TeeTime: " << day << " at " << time
         << " | Booked: " << golfers.size()
         << "/" << maxPlayers << endl;
}