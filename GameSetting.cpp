#include "GameSetting.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Initializes the game with default settings
void GameSetting::initialize_game() {
    day = 1;               // Set the day counter to 1
    HP = 100;              // Set health points to 100
    Hunger = 100;          // Set hunger level to 100
    Mental = 100;          // Set mental health to 100
    weather = "sunny";     // Set default weather to sunny
    cout << "Game initialized!" << endl;
}

// Starts a new day in the game
void GameSetting::start_of_day() {
    step_remains = 4;      // Reset the number of actions available for the day
    cout << "Good morning! It's your " << day << " day on the island. The weather today is " << weather << "." << endl;
    cout << "You have " << step_remains << " actions available today.\n";
}

// Displays the menu for player actions and returns the choice
pair<char, char> GameSetting::selection_menu() {
    char choice;
    char ready_to_escape = 'N'; // Flag to check if the player is ready to attempt an escape

    cout << "+------------------------------+" << endl;
    cout << "| What do you want to do next: |" << endl;
    cout << "+------------------------------+" << endl;
    cout << "| [1] Exploring the island     |" << endl;
    cout << "| [2] Eating                   |" << endl;
    cout << "| [3] Crafting                 |" << endl;
    cout << "| [4] Resting                  |" << endl;
    cout << "| [5] Hunting                  |" << endl;

    // Conditionally add "Cooking" option if the player has a campfire
    if (bag.find("campfire") != bag.end()) {
        cout << "| [6] Cooking                  |" << endl;
    }

    // Conditionally add "Escape" option if the player has a signal flare or a boat
    if (bag.find("signal flare") != bag.end() || bag.find("boat") != bag.end()) {
        cout << "| [7] Attempt to escape        |" << endl;
        ready_to_escape = 'Y'; // Player is ready to attempt an escape
    }

    cout << "+------------------------------+" << endl;
    cout << "Please enter your choice: ";
    cin >> choice;
    cout << endl;

    return { choice, ready_to_escape };
}

// Performs the action selected by the player
void GameSetting::perform_action() {
    while (step_remains > 0) {
        auto selection = selection_menu();
        char choice = selection.first;
        char ready_to_escape = selection.second;

        switch (choice) {
        case '1': exploreIsland(); break;
        case '2': eatFood(); break;
        case '3': craftItem(); break;
        case '4': rest(); break;
        case '5': hunting(); break;
        case '6': cookFood(); break;
        case '7': attempt_escape(); break;
        default: cout << "Invalid input! Please select a valid option." << endl; break;
        }

        cout << "+-------------------------------+" << endl;
        cout << "|   Current Stats               |" << endl;
        cout << "+-------------------------------+" << endl;
        cout << "| HP:     " << setw(3) << HP << " / 100             |" << endl;
        cout << "| Hunger: " << setw(3) << Hunger << " / 100             |" << endl;
        cout << "| Mental: " << setw(3) << Mental << " / 100             |" << endl;
        cout << "+-------------------------------+" << endl;
        cout << "" << endl;
        print_bag(); // Display inventory after each action
        if (HP <= 0) {
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
    night_event(); // Handle night events
    cout << "+-------------------------------+" << endl;
    cout << "|   Current Stats               |" << endl;
    cout << "+-------------------------------+" << endl;
    cout << "| HP:     " << setw(3) << HP << " / 100             |" << endl;
    cout << "| Hunger: " << setw(3) << Hunger << " / 100             |" << endl;
    cout << "| Mental: " << setw(3) << Mental << " / 100             |" << endl;
    cout << "+-------------------------------+" << endl;
    cout << "" << endl;
    if (HP <= 0) {
        cout << "You didn't survive the night. Game Over!" << endl;
        exit(0);
    }
    weather = weather_ran(); // Get new weather for the day
    start_of_day(); // Start a new day
    perform_action(); // Continue with the next day's actions
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