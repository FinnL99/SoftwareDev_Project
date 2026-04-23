// This file contains the implementation code for the GolfClub class
#include "GolfClub.h"
#include <fstream>
#include <sstream>

GolfClub::GolfClub()
{
    clubName = "Unknown Club";
    cout << "calling default constructor for GolfClub" << endl;
}

GolfClub::GolfClub(string name)
{
    clubName = name;
    cout << "calling one parameter constructor for GolfClub" << endl;
}

GolfClub::~GolfClub()
{
    // GolfClub owns the golfer and tee time pointers, so they should be deleted here
    for (int i = 0; i < golfers.size(); i++)
    {
        delete golfers[i];
    }

    for (int i = 0; i < teeTimes.size(); i++)
    {
        delete teeTimes[i];
    }

    cout << "calling destructor for GolfClub" << endl;
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
        // using login key here means Member compares by ID and Guest compares by name
        if (golfers[i]->getLoginKey() == g->getLoginKey())
        {
            cout << "Golfer already exists in club" << endl;
            return false;
        }
    }

    golfers.push_back(g);
    cout << g->getName() << " added to club successfully" << endl;
    return true;
}

Golfer* GolfClub::getGolferById(string memberId)
{
    for (int i = 0; i < golfers.size(); i++)
    {
        // dynamic_cast used because golfers vector stores Golfer* base class pointers
        // looked this up from polymorphism examples on learncpp
        Member* memberPtr = dynamic_cast<Member*>(golfers[i]);

        if (memberPtr != nullptr && memberPtr->getMemberID() == memberId)
        {
            return golfers[i];
        }
    }
    return nullptr;
}

Golfer* GolfClub::getGuestByName(string guestName)
{
    for (int i = 0; i < golfers.size(); i++)
    {
        Guest* guestPtr = dynamic_cast<Guest*>(golfers[i]);

        if (guestPtr != nullptr && guestPtr->getName() == guestName)
        {
            return golfers[i];
        }
    }
    return nullptr;
}

bool GolfClub::addTeeTime(TeeTime* t)
{
    if (getTeeTime(t->getBookingDay(), t->getBookingTime()) != nullptr)
    {
        cout << "Tee time already exists" << endl;
        return false;
    }

    teeTimes.push_back(t);
    cout << "Tee time added successfully" << endl;
    return true;
}

bool GolfClub::removeTeeTime(string day, string time)
{
    for (int i = 0; i < teeTimes.size(); i++)
    {
        if (teeTimes[i]->getBookingDay() == day && teeTimes[i]->getBookingTime() == time)
        {
            delete teeTimes[i];
            teeTimes.erase(teeTimes.begin() + i);
            cout << "Tee time removed successfully" << endl;
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

    // this check stops duplicate tee time slots being created after an edit
    if ((oldDay != newDay || oldTime != newTime) && getTeeTime(newDay, newTime) != nullptr)
    {
        cout << "Another tee time already exists with the new details" << endl;
        return false;
    }

    t->setBookingDay(newDay);
    t->setBookingTime(newTime);
    cout << "Tee time updated successfully" << endl;
    return true;
}

TeeTime* GolfClub::getTeeTime(string day, string time)
{
    for (int i = 0; i < teeTimes.size(); i++)
    {
        if (teeTimes[i]->getBookingDay() == day && teeTimes[i]->getBookingTime() == time)
        {
            return teeTimes[i];
        }
    }
    return nullptr;
}

void GolfClub::displayTeeTimes()
{
    cout << "Golf Club: " << getClubName() << endl;
    cout << "Tee times:" << endl;

    for (int i = 0; i < teeTimes.size(); i++)
    {
        teeTimes[i]->display();
        cout << endl;
    }
}

void GolfClub::displayTeeTimesWithIndex()
{
    cout << "\nAvailable Tee Times:" << endl;

    for (int i = 0; i < teeTimes.size(); i++)
    {
        cout << i + 1 << ". "
             << teeTimes[i]->getBookingDay() << " at "
             << teeTimes[i]->getBookingTime()
             << " (" << teeTimes[i]->getBookedCount()
             << "/" << teeTimes[i]->getMaxPlayers() << " booked)";

        if (teeTimes[i]->isFull())
        {
            cout << " [FULL]";
        }

        cout << endl;
    }
}

TeeTime* GolfClub::getTeeTimeByIndex(int index)
{
    // user sees 1,2,3 in menu, but vector still works from 0 internally
    if (index >= 0 && index < teeTimes.size())
    {
        return teeTimes[index];
    }
    return nullptr;
}

string GolfClub::generateNewMemberID()
{
    int maxNum = 0;

    for (int i = 0; i < golfers.size(); i++)
    {
        Member* m = dynamic_cast<Member*>(golfers[i]);
        if (m != nullptr)
        {
            string id = m->getMemberID();

            if (id.length() > 1 && id[0] == 'M')
            {
                // remove the M at the start and convert the rest to an integer
                // substr/stoi examples from cplusplus reference
                int num = stoi(id.substr(1));

                if (num > maxNum)
                {
                    maxNum = num;
                }
            }
        }
    }

    maxNum++;

    if (maxNum < 10) return "M00" + to_string(maxNum);
    if (maxNum < 100) return "M0" + to_string(maxNum);
    return "M" + to_string(maxNum);
}

void GolfClub::saveToFile()
{
    ofstream outFile("golfclub.txt");

    if (!outFile)
    {
        cout << "Error opening file for saving." << endl;
        return;
    }

    // save club name first so it can be restored when the program starts again
    outFile << "CLUB|" << clubName << endl;

    for (int i = 0; i < golfers.size(); i++)
    {
        Member* m = dynamic_cast<Member*>(golfers[i]);
        Guest* g = dynamic_cast<Guest*>(golfers[i]);

        if (m != nullptr)
        {
            outFile << "GOLFER|MEMBER|"
                    << m->getName() << "|"
                    << m->getHandicap() << "|"
                    << m->getMemberID() << endl;
        }
        else if (g != nullptr)
        {
            outFile << "GOLFER|GUEST|"
                    << g->getName() << "|"
                    << g->getHandicap() << endl;
        }
    }

    for (int i = 0; i < teeTimes.size(); i++)
    {
        outFile << "TEETIME|"
                << teeTimes[i]->getBookingDay() << "|"
                << teeTimes[i]->getBookingTime() << "|";

        vector<Golfer*> booked = teeTimes[i]->getGolfersBooked();

        // save login keys for booked golfers so bookings can be restored later
        for (int j = 0; j < booked.size(); j++)
        {
            outFile << booked[j]->getLoginKey();

            if (j < booked.size() - 1)
            {
                outFile << ",";
            }
        }

        outFile << endl;
    }

    outFile.close();
    cout << "Data saved successfully." << endl;
}

void GolfClub::loadFromFile()
{
    ifstream inFile("golfclub.txt");

    if (!inFile)
    {
        cout << "No saved file found. Starting blank." << endl;
        return;
    }

    string line;
    vector<string> teeTimeLines;

    while (getline(inFile, line))
    {
        // stringstream makes it easier to split text line by line
        stringstream ss(line);
        vector<string> parts;
        string part;

        while (getline(ss, part, '|'))
        {
            parts.push_back(part);
        }

        if (parts.size() == 0)
        {
            continue;
        }

        if (parts[0] == "CLUB" && parts.size() >= 2)
        {
            clubName = parts[1];
        }
        else if (parts[0] == "GOLFER")
        {
            if (parts[1] == "MEMBER" && parts.size() >= 5)
            {
                golfers.push_back(new Member(parts[2], stoi(parts[3]), parts[4]));
            }
            else if (parts[1] == "GUEST" && parts.size() >= 4)
            {
                golfers.push_back(new Guest(parts[2], stoi(parts[3])));
            }
        }
        else if (parts[0] == "TEETIME")
        {
            // store tee time lines first so golfers exist before we re-link bookings
            teeTimeLines.push_back(line);
        }
    }

    for (int i = 0; i < teeTimeLines.size(); i++)
    {
        stringstream ss(teeTimeLines[i]);
        vector<string> parts;
        string part;

        while (getline(ss, part, '|'))
        {
            parts.push_back(part);
        }

        if (parts.size() >= 3)
        {
            TeeTime* t = new TeeTime(parts[1], parts[2]);
            teeTimes.push_back(t);

            if (parts.size() >= 4 && parts[3] != "")
            {
                stringstream bookedSS(parts[3]);
                string key;

                while (getline(bookedSS, key, ','))
                {
                    Golfer* found = getGolferById(key);

                    if (found == nullptr)
                    {
                        found = getGuestByName(key);
                    }

                    if (found != nullptr)
                    {
                        t->addGolferToTeeTime(found);
                    }
                }
            }
        }
    }

    inFile.close();
    cout << "Data loaded successfully." << endl;
}