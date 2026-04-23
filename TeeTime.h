// file containing interface for TeeTime class
#ifndef _TEETIME_
#define _TEETIME_

#include <string>
#include <iostream>
#include <vector>
#include "Golfer.h"
using namespace std;

class TeeTime
{
private:
    string bookingDay;
    string bookingTime;
    vector<Golfer*> golfersBooked;
    const int maxPlayers;

public:
    TeeTime();
    TeeTime(string bookingDay, string bookingTime);

    string getBookingDay();
    void setBookingDay(string);

    string getBookingTime();
    void setBookingTime(string);

    int getMaxPlayers();
    int getBookedCount();

    bool isFull();
    bool isGolferAlreadyBooked(string);

    bool addGolferToTeeTime(Golfer*);
    bool removeGolferFromTeeTime(string);
    void display();

    vector<Golfer*> getGolfersBooked();
};

#endif /* _TEETIME_ */