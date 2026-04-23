#include "Guest.h"

Guest::Guest() : Golfer() {}

Guest::Guest(string n, int h) : Golfer(n, h) {}

string Guest::getLoginKey()
{
    return name;
}

void Guest::display()
{
    cout << "Guest: " << name
         << " | Handicap: " << handicap << endl;
}