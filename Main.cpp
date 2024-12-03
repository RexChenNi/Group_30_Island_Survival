#include "GameSetting.h"
#include "Survival_log.h"

int main() {
    Game_setting game;
    game.initialize_game();
    game.start_of_day();
    game.perform_action();

    return 0;
}
