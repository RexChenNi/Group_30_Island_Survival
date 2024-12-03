#include "GameSetting.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm> // For std::max and std::min

using namespace std;

// Initializes the game with default settings
void GameSetting::initialize_game() {
    day = 1;               // Set the day counter to 1
    setHP(100);            // Set health points to 100
    setHunger(100);        // Set hunger level to 100
    setMental(100);        // Set mental health to 100
    weather = "sunny";     // Set default weather to sunny
    cout << "Game initialized!" << endl;
}

// Starts a new day in the game
void GameSetting::start_of_day() {
    step_remains = 4;      // Reset the number of actions available for the day
    cout << "Good morning! It's your " << day << " day on the island. The weather today is " << weather << "." << endl;
    cout << "You have " << step_remains << " actions available today.\n";
}

// Performs the action selected by the player
void GameSetting::perform_action() {
    while (step_remains > 0) {
        auto selection = selection_menu();
        char choice = selection.first;
        char ready_to_escape = selection.second;

        switch (choice) {
        case '1':
            exploreIsland();
            step_remains--;
            if (weather == "extreme rainfall") {
                setHP(getHP() - 20);
                setHP(getHP() - check_health() * 20);
                setHunger(getHunger() - 30);
                setMental(getMental() - 5);
                setHunger(max(0, getHunger()));
                setMental(max(0, getMental()));
            }
            else {
                setHP(getHP() - check_health() * 20);
                setHunger(getHunger() - deduction().first);
                setMental(getMental() - deduction().second);
                setHunger(max(0, getHunger()));
                setMental(max(0, getMental()));
            }
            break;
        case '2':
            print_bag();
            eatFood();
            break;
        case '3':
            print_bag();
            craftItem();
            step_remains--;
            setHP(getHP() - check_health() * 20);
            setHunger(getHunger() - deduction().first);
            setMental(getMental() - deduction().second);
            setHunger(max(0, min(getHunger(), 100)));
            setMental(max(0, min(getMental(), 100)));
            break;
        case '4':
            rest();
            step_remains--;
            break;
        case '5':
            hunting();
            step_remains--;
            setHP(getHP() - check_health() * 20);
            setHunger(getHunger() - deduction().first);
            setMental(getMental() - deduction().second);
            setHunger(max(0, min(getHunger(), 100)));
            setMental(max(0, min(getMental(), 100)));
            break;
        case '6':
            print_bag();
            if (getBagItem("campfire") > 0) {
                cookFood();
                step_remains--;
            }
            else {
                cout << "Cooking is not available without a campfire!" << endl;
            }
            setHP(getHP() - check_health() * 20);
            setHunger(getHunger() - deduction().first);
            setMental(getMental() - deduction().second);
            setHunger(max(0, min(getHunger(), 100)));
            setMental(max(0, min(getMental(), 100)));
            break;
        case '7':
            if (ready_to_escape == 'Y') {
                attempt_escape();
                setHP(getHP() - check_health() * 20);
                setHunger(getHunger() - deduction().first);
                setMental(getMental() - deduction().second);
                step_remains--;
            }
            else {
                cout << "You are not ready to escape yet!" << endl;
            }
            break;
        default:
            cout << "Invalid input! Please select a valid option." << endl;
            break;
        }

        cout << "+-------------------------------+" << endl;
        cout << "|   Current Stats               |" << endl;
        cout << "+-------------------------------+" << endl;
        cout << "| HP:     " << setw(3) << getHP() << " / 100             |" << endl;
        cout << "| Hunger: " << setw(3) << getHunger() << " / 100             |" << endl;
        cout << "| Mental: " << setw(3) << getMental() << " / 100             |" << endl;
        cout << "+-------------------------------+" << endl;
        cout << "" << endl;
        print_bag();
        if (getHP() <= 0) {
            cout << "You have succumbed to your injuries. Game Over!" << endl;
            exit(0); // End the game
        }
        if (step_remains > 0) {
            cout << "You have " << step_remains << " steps remaining today.\n";
        }
        else {
            cout << "You have no steps remaining for today.\n";
        }
    }
    day++;
    cout << "The day has ended. Preparing for the next day...\n";
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << '\n';
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << '\n';
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << '\n';
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << '\n';
    nightEvent();
    cout << "+-------------------------------+" << endl;
    cout << "|   Current Stats               |" << endl;
    cout << "+-------------------------------+" << endl;
    cout << "| HP:     " << setw(3) << getHP() << " / 100             |" << endl;
    cout << "| Hunger: " << setw(3) << getHunger() << " / 100             |" << endl;
    cout << "| Mental: " << setw(3) << getMental() << " / 100             |" << endl;
    cout << "+-------------------------------+" << endl;
    cout << "" << endl;
    if (getHP() <= 0) {
        cout << "You didn't survive the night. Game Over!" << endl;
        exit(0);
    }
    weather = weather_ran();
    start_of_day();
    perform_action(); // Start the next day's actions
}

// Deletes the linked list of blueprints
void GameSetting::delete_list(Node*& head) {
    Node* current = head;
    Node* nextNode;

    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
}