#include "Golfer.h"

Golfer::Golfer()
{
    name = "Unknown";
    handicap = 0;
}

Golfer::Golfer(string n, int h)
{
    name = n;
    handicap = h;
}

void Golfer::setName(string n)
{
    name = n;
}

string Golfer::getName()
{
    return name;
}

void Golfer::setHandicap(int h)
{
    handicap = h;
}

int Golfer::getHandicap()
{
    return handicap;
}

void Golfer::display()
{
    cout << "Golfer: " << name
         << " | Handicap: " << handicap << endl;
}