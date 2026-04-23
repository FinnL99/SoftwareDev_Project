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
    if (isGolferAlreadyBooked(g->getName()))
    {
        cout << g->getName() << " is already booked into this tee time" << endl;
        return false;
    }

    if (isFull())
    {
        cout << "Tee time is full" << endl;
        return false;
    }

    golfers.push_back(g);
    cout << g->getName() << " added to tee time" << endl;
    return true;
}

bool TeeTime::removeGolfer(string name)
{
    for (int i = 0; i < golfers.size(); i++)
    {
        if (golfers[i]->getName() == name)
        {
            golfers.erase(golfers.begin() + i);
            cout << name << " removed from tee time" << endl;
            return true;
        }
    }

    cout << "Golfer not found in tee time" << endl;
    return false;
}

void TeeTime::display()
{
    cout << "TeeTime: " << day << " at " << time
         << " | Booked: " << golfers.size()
         << "/" << maxPlayers << endl;

    for (int i = 0; i < golfers.size(); i++)
    {
        golfers[i]->display();
    }
}