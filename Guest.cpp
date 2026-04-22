#include "Guest.h"

Guest::Guest() : Golfer()
{
}

Guest::Guest(string name, int handicap) : Golfer(name, handicap)
{
}

void Guest::display()
{
    cout << "Guest: " << getName()
         << " | Handicap: " << getHandicap() << endl;
}