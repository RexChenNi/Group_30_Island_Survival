#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <fstream>
#include <string>

class Game_setting;

class FileHandling {
public:
    static void openFile(Game_setting& game);
    static void writeFile(Game_setting& game, std::string data);
    static void appendToFile(Game_setting& game, std::string text);
    static void closeFile(Game_setting& game);
    static void readFile(Game_setting& game);
};

#endif
