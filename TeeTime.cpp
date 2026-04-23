#include "TeeTime.h"

TeeTime::TeeTime()
{
    day = "Unknown";
    time = "00:00";
    maxPlayers = 4; // max 4 players per tee time (project requirement)
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

vector<Golfer*> TeeTime::getGolfers()
{
    return golfers; // used when writing bookings to file
}

bool TeeTime::isFull()
{
    return golfers.size() >= maxPlayers;
}

bool TeeTime::isGolferAlreadyBooked(string name)
{
    for (int i = 0; i < golfers.size(); i++)
    {
        if (golfers[i]->getName() == name)
        {
            return true;
        }
    }
    return false;
}

bool TeeTime::addGolfer(Golfer* g)
{
    // check duplicate booking first
    if (isGolferAlreadyBooked(g->getName()))
    {
        cout << g->getName() << " already booked" << endl;
        return false;
    }

    // check capacity (important edge case for testing)
    if (isFull())
    {
        cout << "Sorry, tee time is full. Please select another." << endl;
        return false;
    }

    golfers.push_back(g);
    return true;
}

bool TeeTime::removeGolfer(string name)
{
    for (int i = 0; i < golfers.size(); i++)
    {
        if (golfers[i]->getName() == name)
        {
            golfers.erase(golfers.begin() + i);
            return true;
        }
    }
    return false;
}

void TeeTime::display()
{
    cout << "TeeTime: " << day << " at " << time
         << " (" << golfers.size() << "/" << maxPlayers << ")" << endl;

    // display all booked golfers
    for (int i = 0; i < golfers.size(); i++)
    {
        golfers[i]->display();
    }
}