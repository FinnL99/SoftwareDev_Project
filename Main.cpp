#include <iostream>
#include <string>
#include "GolfClub.h"
#include "Member.h"
#include "Guest.h"
#include "TeeTime.h"

using namespace std;

// small helper to keep menu input simple
int readChoice()
{
    int choice;
    cin >> choice;
    cin.ignore();
    return choice;
}

int main()
{
    GolfClub club("Skerries Golf Club");

    // load previous data if file already exists
    club.loadFromFile();

    // if no tee times exist yet, create starter slots
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
        cout << "Enter choice: ";
        startChoice = readChoice();

        if (startChoice == 1)
        {
            int loginChoice;
            string input;
            Golfer* currentUser = nullptr;

            cout << "\n1. Member login by ID" << endl;
            cout << "2. Guest login by Name" << endl;
            cout << "Enter choice: ";
            loginChoice = readChoice();

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
                cout << "\n--- User Menu ---" << endl;
                cout << "1. View tee times" << endl;
                cout << "2. Book a tee time" << endl;
                cout << "3. Remove yourself from a tee time" << endl;
                cout << "4. Logout" << endl;
                cout << "Enter choice: ";
                userChoice = readChoice();

                if (userChoice == 1)
                {
                    // useful to display current state of bookings
                    club.displayTeeTimes();
                }
                else if (userChoice == 2)
                {
                    string day, time;

                    cout << "Enter day: ";
                    getline(cin, day);

                    cout << "Enter time: ";
                    getline(cin, time);

                    TeeTime* t = club.getTeeTime(day, time);

                    if (t != nullptr)
                    {
                        // TeeTime class handles duplicate/full checks
                        t->addGolfer(currentUser);
                    }
                    else
                    {
                        cout << "Tee time not found." << endl;
                    }
                }
                else if (userChoice == 3)
                {
                    string day, time;

                    cout << "Enter day: ";
                    getline(cin, day);

                    cout << "Enter time: ";
                    getline(cin, time);

                    TeeTime* t = club.getTeeTime(day, time);

                    if (t != nullptr)
                    {
                        t->removeGolfer(currentUser->getName());
                    }
                    else
                    {
                        cout << "Tee time not found." << endl;
                    }
                }

            } while (userChoice != 4);
        }
        else if (startChoice == 2)
        {
            int regChoice;
            string name;
            int handicap;

            cout << "\n1. Register as Member" << endl;
            cout << "2. Register as Guest" << endl;
            cout << "Enter choice: ";
            regChoice = readChoice();

            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter handicap: ";
            handicap = readChoice();

            if (regChoice == 1)
            {
                // simple starter ID generation for now
                string newID = "M00" + to_string(rand() % 100);

                if (club.addGolfer(new Member(name, handicap, newID)))
                {
                    cout << "Member registered successfully." << endl;
                    cout << "Your ID is: " << newID << endl;
                }
            }
            else if (regChoice == 2)
            {
                if (club.addGolfer(new Guest(name, handicap)))
                {
                    cout << "Guest registered successfully." << endl;
                }
            }
            else
            {
                cout << "Invalid registration option." << endl;
            }
        }
        else if (startChoice == 3)
        {
            club.displayTeeTimes();
        }

    } while (startChoice != 4);

    // save data before exiting program
    club.saveToFile();

    cout << "Goodbye." << endl;
    return 0;
}