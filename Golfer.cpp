// This file contains the implementation code for the Golfer class
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

Golfer::~Golfer()
{
}

string Golfer::getName()
{
    return name;
}

void Golfer::setName(string n)
{
    name = n;
}

int Golfer::getHandicap()
{
    return handicap;
}

void Golfer::setHandicap(int h)
{
    handicap = h;
}