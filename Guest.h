#ifndef GUEST_H
#define GUEST_H

#include "Golfer.h"

class Guest : public Golfer
{
public:
    Guest();
    Guest(string n, int h);
    ~Guest();

    string getLoginKey();
    void display();
};

#endif