#include <iostream>
#include <string>
#include "GolfClub.h"
#include "Member.h"
#include "Guest.h"
#include "TeeTime.h"

using namespace std;

void showLoggedInMenu()
{
    cout << "\n--- User Menu ---" << endl;
    cout << "1. View tee times" << endl;
    cout << "2. Book a tee time" << endl;
    cout << "3. Remove yourself from a tee time" << endl;
    cout << "4. Edit your tee time" << endl;
    cout << "5. Logout" << endl;
    cout << "Enter choice: ";
}

int main()
{
    GolfClub club("Skerries Golf Club");
    club.loadFromFile();

    // only create starter tee times if they are not already loaded from file
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
        cin >> startChoice;
        cin.ignore();

        if (startChoice == 1)
        {
            int loginChoice;
            string input;
            Golfer* currentUser = nullptr;

            cout << "\n1. Member login by ID" << endl;
            cout << "2. Guest login by Name" << endl;
            cout << "Enter choice: ";
            cin >> loginChoice;
            cin.ignore();

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
                cin >> userChoice;
                cin.ignore();

                if (userChoice == 1)
                {
                    club.displayTeeTimesWithIndex();
                }
                else if (userChoice == 2)
                {
                    club.displayTeeTimesWithIndex();

                    int slot;
                    cout << "Pick a tee time number: ";
                    cin >> slot;
                    cin.ignore();

                    // user sees 1,2,3 but vector index still starts at 0
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

                    int slot;
                    cout << "Pick a tee time number to remove yourself from: ";
                    cin >> slot;
                    cin.ignore();

                    TeeTime* t = club.getTeeTimeByIndex(slot - 1);

                    if (t != nullptr)
                    {
                        // using login key here works for both Member and Guest
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

                    int oldSlot, newSlot;
                    cout << "Pick your current tee time number: ";
                    cin >> oldSlot;
                    cout << "Pick your new tee time number: ";
                    cin >> newSlot;
                    cin.ignore();

                    TeeTime* oldT = club.getTeeTimeByIndex(oldSlot - 1);
                    TeeTime* newT = club.getTeeTimeByIndex(newSlot - 1);

                    if (oldT != nullptr && newT != nullptr)
                    {
                        if (oldT->removeGolferFromTeeTime(currentUser->getLoginKey()))
                        {
                            if (!newT->addGolferToTeeTime(currentUser))
                            {
                                // put golfer back into original slot if the move fails
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
            cin >> regChoice;
            cin.ignore();

            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter handicap: ";
            cin >> handicap;
            cin.ignore();

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
        }
        else if (startChoice == 3)
        {
            club.displayTeeTimesWithIndex();
        }

    } while (startChoice != 4);

    // save club data and bookings before closing the program
    club.saveToFile();

    cout << "Goodbye." << endl;
    return 0;
}