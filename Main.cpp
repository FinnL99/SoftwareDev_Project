#include <iostream>
#include <string>
#include <stdexcept>
#include "GolfClub.h"
#include "Member.h"
#include "Guest.h"
#include "TeeTime.h"

using namespace std;

// safer input for menu choices
int readChoice()
{
    int choice;

    while (true)
    {
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number: ";
        }
        else
        {
            cin.ignore();
            return choice;
        }
    }
}

int main()
{
    GolfClub club("Skerries Golf Club");

    // load saved data if file exists
    club.loadFromFile();

    // create starter tee times if none exist yet
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

        try
        {
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
                    throw invalid_argument("Login option must be 1 or 2");
                }

                if (currentUser == nullptr)
                {
                    throw runtime_error("Login failed. User not found.");
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
                        club.displayTeeTimesWithIndex();
                    }

                    else if (userChoice == 2)
                    {
                        int choice;

                        club.displayTeeTimesWithIndex();
                        cout << "Select tee time number: ";
                        choice = readChoice();

                        // user sees 1,2,3 but vector starts at 0
                        TeeTime* t = club.getTeeTimeByIndex(choice - 1);

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
                        int choice;

                        club.displayTeeTimesWithIndex();
                        cout << "Select tee time number to remove yourself from: ";
                        choice = readChoice();

                        // converting menu choice into vector index
                        TeeTime* t = club.getTeeTimeByIndex(choice - 1);

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

                        club.displayTeeTimesWithIndex();
                        cout << "Select your current tee time number: ";
                        oldChoice = readChoice();

                        cout << "Select your new tee time number: ";
                        newChoice = readChoice();

                        TeeTime* oldT = club.getTeeTimeByIndex(oldChoice - 1);
                        TeeTime* newT = club.getTeeTimeByIndex(newChoice - 1);

                        if (oldT != nullptr && newT != nullptr)
                        {
                            if (oldT->removeGolfer(currentUser->getName()))
                            {
                                if (!newT->addGolfer(currentUser))
                                {
                                    // put golfer back if new booking fails
                                    oldT->addGolfer(currentUser);
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

                if (handicap < 0)
                {
                    throw invalid_argument("Handicap cannot be negative");
                }

                if (regChoice == 1)
                {
                    string newID = club.generateNewMemberID();

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
                    throw invalid_argument("Invalid registration option");
                }
            }

            else if (startChoice == 3)
            {
                club.displayTeeTimesWithIndex();
            }

            else if (startChoice != 4)
            {
                throw invalid_argument("Invalid menu option");
            }
        }
        catch (exception& e)
        {
            cout << "Error: " << e.what() << endl;
        }

    } while (startChoice != 4);

    // save before exiting
    club.saveToFile();

    cout << "Goodbye." << endl;
    return 0;
}