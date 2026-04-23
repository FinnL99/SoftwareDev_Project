// This file contains the implementation code for the Guest class
#include "Guest.h"

Guest::Guest() : Golfer()
{
    cout << "calling default constructor for Guest" << endl;
}

Guest::Guest(string n, int h) : Golfer(n, h)
{
    cout << "calling parameter constructor for Guest" << endl;
}

string Guest::getLoginKey()
{
    // guests do not have IDs, so name is used as login key
    return getName();
}

void Guest::display()
{
    cout << "Guest: " << getName()
         << " has handicap " << getHandicap() << endl;
}