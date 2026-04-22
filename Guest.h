#ifndef _GUEST_
#define _GUEST_

#include "Golfer.h"

class Guest : public Golfer
{
public:
    Guest();
    Guest(string name, int handicap);

    void display();
};

#endif