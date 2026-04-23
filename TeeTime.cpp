#include "TeeTime.h"

TeeTime::TeeTime()
{
    day = "Unknown";
    time = "00:00";
}

TeeTime::TeeTime(string d, string t)
{
    day = d;
    time = t;
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

void TeeTime::display()
{
    cout << "TeeTime: " << day << " at " << time << endl;
}