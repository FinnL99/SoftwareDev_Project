#include <iostream>
#include <string>
#include <vector>
#include "GolfClub.h"
#include "Member.h"
#include "Guest.h"
#include "TeeTime.h"

using namespace std;

// simple helper for menu choices
int readChoice()
{
    int choice;
    cin >> choice;
    cin.ignore();
    return choice;
}

// helper to show tee times with numbers beside them
void displayTeeTimesWithNumbers(GolfClub& club)
{
    cout << "\nAvailable Tee Times:" << endl;

    vector<string> days = {"Monday", "Monday", "Tuesday", "Wednesday"};
    vector<string> times = {"09:00", "10:00", "11:00", "12:00"};

    for (int i = 0; i < days.size(); i++)
    {
        TeeTime* t = club.getTeeTime(days[i], times[i]);

        if (t != nullptr)
        {
            cout << i + 1 << ". ";
            t->display();
        }
    }
}

// helper to return tee time based on number selected
TeeTime* getTeeTimeFromChoice(GolfClub& club, int choice)
{
    if (choice == 1) return club.getTeeTime("Monday", "09:00");
    if (choice == 2) return club.getTeeTime("Monday", "10:00");
    if (choice == 3) return club.getTeeTime("Tuesday", "11:00");
    if (choice == 4) return club.getTeeTime("Wednesday", "12:00");

    return nullptr;
}

int main()
{
    GolfClub club("Skerries Golf Club");

    // load saved data if there is already a file there
    club.loadFromFile();

    // starter tee times only added if they do not already exist
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
                cout << "4. Edit your booking" << endl;
                cout << "5. Logout" << endl;
                cout << "Enter choice: ";
                userChoice = readChoice();

                if (userChoice == 1)
                {
                    displayTeeTimesWithNumbers(club);
                }
                else if (userChoice == 2)
                {
                    int teeChoice;

                    // easier for the user than typing day/time every time
                    displayTeeTimesWithNumbers(club);
                    cout << "Select tee time number: ";
                    teeChoice = readChoice();

                    TeeTime* t = getTeeTimeFromChoice(club, teeChoice);

                    if (t != nullptr)
                    {
                        t->addGolfer(currentUser);
                    }
                    else
                    {
                        cout << "Invalid tee time selection." << endl;
                    }
                }
                else if (userChoice == 3)
                {
                    int teeChoice;

                    displayTeeTimesWithNumbers(club);
                    cout << "Select tee time number to remove yourself from: ";
                    teeChoice = readChoice();

                    TeeTime* t = getTeeTimeFromChoice(club, teeChoice);

                    if (t != nullptr)
                    {
                        t->removeGolfer(currentUser->getName());
                    }
                    else
                    {
                        cout << "Invalid tee time selection." << endl;
                    }
                }
                else if (userChoice == 4)
                {
                    int oldChoice, newChoice;

                    // simple edit = remove from old slot then add to new slot
                    displayTeeTimesWithNumbers(club);
                    cout << "Select your current tee time number: ";
                    oldChoice = readChoice();

                    cout << "Select your new tee time number: ";
                    newChoice = readChoice();

                    TeeTime* oldTeeTime = getTeeTimeFromChoice(club, oldChoice);
                    TeeTime* newTeeTime = getTeeTimeFromChoice(club, newChoice);

                    if (oldTeeTime != nullptr && newTeeTime != nullptr)
                    {
                        if (oldTeeTime->removeGolfer(currentUser->getName()))
                        {
                            if (!newTeeTime->addGolfer(currentUser))
                            {
                                // if new booking fails, add them back to original slot
                                oldTeeTime->addGolfer(currentUser);
                                cout << "Could not update booking." << endl;
                            }
                        }
                        else
                        {
                            cout << "You were not booked into that tee time." << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid tee time selection." << endl;
                    }
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
            cout << "Enter choice: ";
            regChoice = readChoice();

            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter handicap: ";
            handicap = readChoice();

            if (regChoice == 1)
            {
                // still simple ID generation at this stage
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
            displayTeeTimesWithNumbers(club);
        }

    } while (startChoice != 4);

    // save everything before closing
    club.saveToFile();

    cout << "Goodbye." << endl;
    return 0;
}