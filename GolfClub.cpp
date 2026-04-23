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

string GolfClub::generateMemberID()
{
    int highest = 0;

    // generate next member ID based on current members in vector
    for (int i = 0; i < golfers.size(); i++)
    {
        Member* m = dynamic_cast<Member*>(golfers[i]);

        if (m != nullptr)
        {
            string id = m->getMemberID();

            if (id.length() > 1 && id[0] == 'M')
            {
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
    ofstream outFile("golfclub.txt");

    if (!outFile)
    {
        cout << "Error opening file" << endl;
        return;
    }

    outFile << clubName << endl;

    outFile << golfers.size() << endl;

    for (int i = 0; i < golfers.size(); i++)
    {
        Member* m = dynamic_cast<Member*>(golfers[i]);
        Guest* g = dynamic_cast<Guest*>(golfers[i]);

        if (m != nullptr)
        {
            outFile << "MEMBER," << m->getName()
                    << "," << m->getHandicap()
                    << "," << m->getMemberID() << endl;
        }
        else if (g != nullptr)
        {
            outFile << "GUEST," << g->getName()
                    << "," << g->getHandicap() << endl;
        }
    }

    outFile << teeTimes.size() << endl;

    for (int i = 0; i < teeTimes.size(); i++)
    {
        outFile << teeTimes[i]->getDay() << ","
                << teeTimes[i]->getTime() << ",";

        vector<Golfer*> booked = teeTimes[i]->getGolfers();

        // save booked golfer names after the day/time
        for (int j = 0; j < booked.size(); j++)
        {
            outFile << booked[j]->getName();

            if (j < booked.size() - 1)
            {
                outFile << "|";
            }
        }

        outFile << endl;
    }

    outFile.close();
    cout << "Data saved (with bookings)" << endl;
}

void GolfClub::loadFromFile()
{
    ifstream inFile("golfclub.txt");

    if (!inFile)
    {
        cout << "No file found to load" << endl;
        return;
    }

    string line;
    getline(inFile, clubName);

    int golferCount;
    inFile >> golferCount;
    inFile.ignore();

    for (int i = 0; i < golferCount; i++)
    {
        getline(inFile, line);
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

    int teeTimeCount;
    inFile >> teeTimeCount;
    inFile.ignore();

    for (int i = 0; i < teeTimeCount; i++)
    {
        getline(inFile, line);
        stringstream ss(line);

        string day, time, bookedNames;
        getline(ss, day, ',');
        getline(ss, time, ',');
        getline(ss, bookedNames);

        TeeTime* t = new TeeTime(day, time);
        teeTimes.push_back(t);

        // load golfer bookings back into the tee time
        if (bookedNames != "")
        {
            stringstream bookedStream(bookedNames);
            string golferName;

            while (getline(bookedStream, golferName, '|'))
            {
                Golfer* foundGolfer = getGuestByName(golferName);

                if (foundGolfer == nullptr)
                {
                    // if not guest, search members by name
                    for (int j = 0; j < golfers.size(); j++)
                    {
                        if (golfers[j]->getName() == golferName)
                        {
                            foundGolfer = golfers[j];
                            break;
                        }
                    }
                }

                if (foundGolfer != nullptr)
                {
                    t->addGolfer(foundGolfer);
                }
            }
        }
    }

    inFile.close();
    cout << "Data loaded from file" << endl;
}