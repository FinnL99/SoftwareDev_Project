#ifndef GUEST_H
#define GUEST_H

#include "Golfer.h"

class Guest : public Golfer
{
public:
    Guest();
    Guest(string name, int handicap);

    string getLoginKey(); // guests login with name
    void display();
};

#endif