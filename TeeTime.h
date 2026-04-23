#ifndef _TEETIME_
#define _TEETIME_

#include <string>
#include <iostream>
using namespace std;

class TeeTime
{
private:
    string day;
    string time;

public:
    TeeTime();
    TeeTime(string day, string time);

    void setDay(string);
    string getDay();

    void setTime(string);
    string getTime();

    void display();
};

#endif