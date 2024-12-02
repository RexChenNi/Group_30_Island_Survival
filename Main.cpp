// Main.cpp
#include "GameSetting.h"

using namespace std;

int main() {
    GameSetting game;
    game.initialize_game();
    game.start_of_day();
    game.perform_action();

    return 0;
}