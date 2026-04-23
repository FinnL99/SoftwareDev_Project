#include "GolfClub.h"

GolfClub::GolfClub()
{
    clubName = "Unknown Club";
}

GolfClub::GolfClub(string name)
{
    clubName = name;
}

GolfClub::~GolfClub()
{
    for (int i = 0; i < golfers.size(); i++)
    {
        delete golfers[i];
    }

    for (int i = 0; i < teeTimes.size(); i++)
    {
        delete teeTimes[i];
    }
}

void GolfClub::setClubName(string name)
{
    clubName = name;
}

string GolfClub::getClubName()
{
    return clubName;
}

bool GolfClub::addGolfer(Golfer* g)
{
    for (int i = 0; i < golfers.size(); i++)
    {
        if (golfers[i]->getName() == g->getName())
        {
            cout << "Golfer already exists" << endl;
            return false;
        }
    }

    golfers.push_back(g);
    return true;
}

bool GolfClub::addTeeTime(TeeTime* t)
{
    if (getTeeTime(t->getDay(), t->getTime()) != nullptr)
    {
        cout << "Tee time already exists" << endl;
        return false;
    }

    teeTimes.push_back(t);
    return true;
}

Golfer* GolfClub::getGolferById(string id)
{
    for (int i = 0; i < golfers.size(); i++)
    {
        Member* m = dynamic_cast<Member*>(golfers[i]);
        if (m != nullptr && m->getMemberID() == id)
        {
            return golfers[i];
        }
    }

    return nullptr;
}

Golfer* GolfClub::getGuestByName(string name)
{
    for (int i = 0; i < golfers.size(); i++)
    {
        Guest* g = dynamic_cast<Guest*>(golfers[i]);
        if (g != nullptr && g->getName() == name)
        {
            return golfers[i];
        }
    }

    return nullptr;
}

TeeTime* GolfClub::getTeeTime(string day, string time)
{
    for (int i = 0; i < teeTimes.size(); i++)
    {
        if (teeTimes[i]->getDay() == day && teeTimes[i]->getTime() == time)
        {
            return teeTimes[i];
        }
    }

    return nullptr;
}

bool GolfClub::removeTeeTime(string day, string time)
{
    for (int i = 0; i < teeTimes.size(); i++)
    {
        if (teeTimes[i]->getDay() == day && teeTimes[i]->getTime() == time)
        {
            delete teeTimes[i];
            teeTimes.erase(teeTimes.begin() + i);
            return true;
        }
    }

    return false;
}

bool GolfClub::editTeeTime(string oldDay, string oldTime, string newDay, string newTime)
{
    TeeTime* t = getTeeTime(oldDay, oldTime);

    if (t == nullptr)
    {
        return false;
    }

    if ((oldDay != newDay || oldTime != newTime) && getTeeTime(newDay, newTime) != nullptr)
    {
        cout << "New tee time already exists" << endl;
        return false;
    }

    t->setDay(newDay);
    t->setTime(newTime);
    return true;
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