#ifndef SURVIVAL_LOG_H
#define SURVIVAL_LOG_H

#include <fstream>
#include <string>

using namespace std;

class Game_setting;

class Survival_log {
public:
    static void openFile(Game_setting& game);
    static void writeFile(Game_setting& game, string data);
    static void appendToFile(Game_setting& game, string text);
    static void closeFile(Game_setting& game);
    static void readFile(Game_setting& game);
};

#endif
