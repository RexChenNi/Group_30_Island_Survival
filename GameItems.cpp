// GameItems.cpp
#include "GameItems.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Prints the contents of the player's bag
void print_bag(const map<string, int>& bag) {
    cout << "+--------------------+----------------+" << endl;
    cout << "|       Item         |     Quantity   |" << endl;
    cout << "+--------------------+----------------+" << endl;

    for (const auto& pair : bag) {
        if (pair.second == 0) continue;
        cout << "| " << setw(19) << left << pair.first
            << "| " << setw(15) << left << pair.second << "|" << endl;
    }

    cout << "+--------------------+----------------+" << endl;
}

// Lists available blueprints
void blueprint_list(GameSetting& game) {
    cout << "+------------------------------+" << endl;
    cout << "| Available Blueprints         |" << endl;
    cout << "+------------------------------+" << endl;

    for (const auto& blueprint : game.blueprints) {
        cout << "| " << setw(35) << left << blueprint << "|" << endl;
    }

    if (game.blueprints.empty()) {
        cout << "| No blueprints available.       |" << endl;
    }

    cout << "+------------------------------+" << endl;
}