#include <iostream>
#include <string>
#include <limits>
#include "GolfClub.h"
#include "Member.h"
#include "Guest.h"
#include "TeeTime.h"

using namespace std;

int getIntInput(const string& prompt)
{
    int value;

    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail())
        {
            cin.clear(); // clear error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // throw away bad input
            cout << "Invalid input. Please enter a number." << endl;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline
            return value;
        }
    }
}

void showLoggedInMenu()
{
    cout << "\n--- User Menu ---" << endl;
    cout << "1. View tee times" << endl;
    cout << "2. Book a tee time" << endl;
    cout << "3. Remove yourself from a tee time" << endl;
    cout << "4. Edit your tee time" << endl;
    cout << "5. Logout" << endl;
}

int main()
{
    GolfClub club("Skerries Golf Club");
    club.loadFromFile();

    if (club.getTeeTime("Monday", "09:00") == nullptr)
    {
        club.addTeeTime(new TeeTime("Monday", "09:00"));
        club.addTeeTime(new TeeTime("Monday", "10:00"));
        club.addTeeTime(new TeeTime("Tuesday", "11:00"));
        club.addTeeTime(new TeeTime("Wednesday", "12:00"));
    }

    int startChoice = 0;

    do
    {
        cout << "\n=== " << club.getClubName() << " ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. View tee times" << endl;
        cout << "4. Exit" << endl;

        startChoice = getIntInput("Enter choice: ");

        if (startChoice == 1)
        {
            int loginChoice;
            string input;
            Golfer* currentUser = nullptr;

            cout << "\n1. Member login by ID" << endl;
            cout << "2. Guest login by Name" << endl;
            loginChoice = getIntInput("Enter choice: ");

            if (loginChoice == 1)
            {
                cout << "Enter Member ID: ";
                getline(cin, input);
                currentUser = club.getGolferById(input);
            }
            else if (loginChoice == 2)
            {
                cout << "Enter Guest Name: ";
                getline(cin, input);
                currentUser = club.getGuestByName(input);
            }
            else
            {
                cout << "Invalid login option." << endl;
                continue;
            }

            if (currentUser == nullptr)
            {
                cout << "Login failed." << endl;
                continue;
            }

            cout << "\nLogin successful." << endl;
            currentUser->display();

            int userChoice = 0;
            do
            {
                showLoggedInMenu();
                userChoice = getIntInput("Enter choice: ");

                if (userChoice == 1)
                {
                    club.displayTeeTimesWithIndex();
                }
                else if (userChoice == 2)
                {
                    club.displayTeeTimesWithIndex();

                    int slot = getIntInput("Pick a tee time number: ");
                    TeeTime* t = club.getTeeTimeByIndex(slot - 1);

                    if (t != nullptr)
                    {
                        if (!t->addGolferToTeeTime(currentUser))
                        {
                            cout << "Booking failed." << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid tee time selection." << endl;
                    }
                }
                else if (userChoice == 3)
                {
                    club.displayTeeTimesWithIndex();

                    int slot = getIntInput("Pick a tee time number to remove yourself from: ");
                    TeeTime* t = club.getTeeTimeByIndex(slot - 1);

                    if (t != nullptr)
                    {
                        t->removeGolferFromTeeTime(currentUser->getLoginKey());
                    }
                    else
                    {
                        cout << "Invalid tee time selection." << endl;
                    }
                }
                else if (userChoice == 4)
                {
                    club.displayTeeTimesWithIndex();

                    int oldSlot = getIntInput("Pick your current tee time number: ");
                    int newSlot = getIntInput("Pick your new tee time number: ");

                    TeeTime* oldT = club.getTeeTimeByIndex(oldSlot - 1);
                    TeeTime* newT = club.getTeeTimeByIndex(newSlot - 1);

                    if (oldT != nullptr && newT != nullptr)
                    {
                        if (oldT->removeGolferFromTeeTime(currentUser->getLoginKey()))
                        {
                            if (!newT->addGolferToTeeTime(currentUser))
                            {
                                oldT->addGolferToTeeTime(currentUser);
                                cout << "Could not move booking." << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "Invalid tee time selection." << endl;
                    }
                }
                else if (userChoice != 5)
                {
                    cout << "Invalid menu choice." << endl;
                }

            } while (userChoice != 5);
        }
        else if (startChoice == 2)
        {
            int regChoice;
            string name;
            int handicap;

            cout << "\n1. Register as Member" << endl;
            cout << "2. Register as Guest" << endl;
            regChoice = getIntInput("Enter choice: ");

            cout << "Enter name: ";
            getline(cin, name);

            handicap = getIntInput("Enter handicap: ");

            if (regChoice == 1)
            {
                string newID = club.generateNewMemberID();
                club.addGolfer(new Member(name, handicap, newID));
                cout << "Registration successful. Your Member ID is: " << newID << endl;
            }
            else if (regChoice == 2)
            {
                club.addGolfer(new Guest(name, handicap));
                cout << "Guest registration successful. Login with your name." << endl;
            }
            else
            {
                cout << "Invalid registration option." << endl;
            }
        }
        else if (startChoice == 3)
        {
            club.displayTeeTimesWithIndex();
        }
        else if (startChoice != 4)
        {
            cout << "Invalid menu choice." << endl;
        }

    } while (startChoice != 4);

    club.saveToFile();

    cout << "Goodbye." << endl;
    return 0;
}