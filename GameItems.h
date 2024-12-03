#ifndef GAME_ITEMS_H
#define GAME_ITEMS_H

#include "GameSetting.h" // Include GameSetting.h to access GameSetting class

#include <map>
#include <string>
#include <iostream>

using namespace std;

// Function to print the contents of the player's bag
void print_bag(const map<string, int>& bag);

// Function to list available blueprints using the GameSetting object
void blueprint_list(const GameSetting& game); // Changed parameter type to const GameSetting&

#endif // GAME_ITEMS_H