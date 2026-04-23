#include "GolfClub.h"
#include <fstream>
#include <sstream>

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
    for (auto g : golfers)
    {
        delete g;
    }

    for (auto t : teeTimes)
    {
        delete t;
    }
}

string GolfClub::getClubName()
{
    return clubName;
}

void GolfClub::setClubName(string name)
{
    clubName = name;
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
        // golfers vector stores base class pointers so dynamic_cast is used here
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

    cout << "Tee time not found" << endl;
    return false;
}

bool GolfClub::editTeeTime(string oldDay, string oldTime, string newDay, string newTime)
{
    TeeTime* t = getTeeTime(oldDay, oldTime);

    if (t == nullptr)
    {
        cout << "Tee time not found" << endl;
        return false;
    }

    // stops duplicate tee times being created after edit
    if ((oldDay != newDay || oldTime != newTime) && getTeeTime(newDay, newTime) != nullptr)
    {
        cout << "Another tee time already exists with these details" << endl;
        return false;
    }

    t->setDay(newDay);
    t->setTime(newTime);
    return true;
}

void GolfClub::displayTeeTimes()
{
    for (int i = 0; i < teeTimes.size(); i++)
    {
        teeTimes[i]->display();
    }
}

void GolfClub::displayTeeTimesWithIndex()
{
    cout << "\nAvailable Tee Times:" << endl;

    for (int i = 0; i < teeTimes.size(); i++)
    {
        cout << i + 1 << ". ";
        teeTimes[i]->display();
    }
}

TeeTime* GolfClub::getTeeTimeByIndex(int index)
{
    // user will see list from 1, but vector still works from 0
    if (index >= 0 && index < teeTimes.size())
    {
        return teeTimes[index];
    }

    return nullptr;
}

string GolfClub::generateNewMemberID()
{
    int highest = 0;

    for (int i = 0; i < golfers.size(); i++)
    {
        Member* m = dynamic_cast<Member*>(golfers[i]);

        if (m != nullptr)
        {
            string id = m->getMemberID();

            if (id.length() > 1 && id[0] == 'M')
            {
                // remove the M and convert the rest to a number
                int number = stoi(id.substr(1));

                if (number > highest)
                {
                    highest = number;
                }
            }
        }
    }

    highest++;

    if (highest < 10)
    {
        return "M00" + to_string(highest);
    }
    else if (highest < 100)
    {
        return "M0" + to_string(highest);
    }
    else
    {
        return "M" + to_string(highest);
    }
}

void GolfClub::saveToFile()
{
    ofstream out("golfclub.txt");

    for (auto g : golfers)
    {
        Member* m = dynamic_cast<Member*>(g);
        Guest* guest = dynamic_cast<Guest*>(g);

        if (m != nullptr)
        {
            out << "MEMBER," << m->getName() << "," << m->getHandicap()
                << "," << m->getMemberID() << endl;
        }
        else if (guest != nullptr)
        {
            out << "GUEST," << guest->getName() << "," << guest->getHandicap() << endl;
        }
    }

    out.close();
}

void GolfClub::loadFromFile()
{
    ifstream in("golfclub.txt");

    if (!in)
    {
        return;
    }

    string line;

    while (getline(in, line))
    {
        // stringstream used to split text read from file
        stringstream ss(line);

        string type, name, handicapStr, id;

        getline(ss, type, ',');
        getline(ss, name, ',');
        getline(ss, handicapStr, ',');

        int handicap = stoi(handicapStr);

        if (type == "MEMBER")
        {
            getline(ss, id, ',');
            golfers.push_back(new Member(name, handicap, id));
        }
        else if (type == "GUEST")
        {
            golfers.push_back(new Guest(name, handicap));
        }
    }

    in.close();
}