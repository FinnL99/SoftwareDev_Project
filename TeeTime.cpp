// This file contains the implementation code for the TeeTime class
#include "TeeTime.h"

TeeTime::TeeTime() : maxPlayers(4)
{
    bookingDay = "Unknown";
    bookingTime = "Unknown";
    cout << "calling default constructor for TeeTime" << endl;
}

TeeTime::TeeTime(string day, string time) : maxPlayers(4)
{
    bookingDay = day;
    bookingTime = time;
    cout << "calling two parameter constructor for TeeTime" << endl;
}

string TeeTime::getBookingDay()
{
    return bookingDay;
}

void TeeTime::setBookingDay(string day)
{
    bookingDay = day;
}

string TeeTime::getBookingTime()
{
    return bookingTime;
}

void TeeTime::setBookingTime(string time)
{
    bookingTime = time;
}

int TeeTime::getMaxPlayers()
{
    return maxPlayers;
}

int TeeTime::getBookedCount()
{
    return golfersBooked.size();
}

bool TeeTime::isFull()
{
    // compares current number booked to max capacity of 4
    return golfersBooked.size() >= maxPlayers;
}

bool TeeTime::isGolferAlreadyBooked(string loginKey)
{
    // simple linear search through vector
    // this is basic vector traversal from notes / learncpp examples
    for (int i = 0; i < golfersBooked.size(); i++)
    {
        if (golfersBooked[i]->getLoginKey() == loginKey)
        {
            return true;
        }
    }
    return false;
}

bool TeeTime::addGolferToTeeTime(Golfer* g)
{
    // check duplicate booking first
    if (isGolferAlreadyBooked(g->getLoginKey()))
    {
        cout << g->getName() << " is already booked into this tee time" << endl;
        return false;
    }

    // then check if the slot has reached capacity
    if (isFull())
    {
        cout << "Sorry, tee time is full. Please select another." << endl;
        return false;
    }

    // add base class pointer into vector so both Member and Guest can be stored
    golfersBooked.push_back(g);
    cout << g->getName() << " added to tee time successfully" << endl;
    return true;
}

bool TeeTime::removeGolferFromTeeTime(string loginKey)
{
    for (int i = 0; i < golfersBooked.size(); i++)
    {
        if (golfersBooked[i]->getLoginKey() == loginKey)
        {
            golfersBooked.erase(golfersBooked.begin() + i);
            cout << "Golfer removed from tee time successfully" << endl;
            return true;
        }
    }

    cout << "Golfer not found in this tee time" << endl;
    return false;
}

void TeeTime::display()
{
    cout << "Tee Time: " << getBookingDay() << " at " << getBookingTime() << endl;
    cout << "Booked golfers: " << getBookedCount() << "/" << getMaxPlayers() << endl;

    for (int i = 0; i < golfersBooked.size(); i++)
    {
        golfersBooked[i]->display();
    }
}

vector<Golfer*> TeeTime::getGolfersBooked()
{
    // returning vector here makes saving bookings to file easier later
    return golfersBooked;
}