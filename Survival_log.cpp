#include "SurvivalLog.h"
#include "GameSetting.h"
#include <iostream>
#include <fstream>

using namespace std;

void SurvivalLog::openFile(Game_setting& game) {
    game.outFile.open("Survival Log");
    if (!game.outFile) {
        cerr << "Error opening file!" << endl;
    }
}

void SurvivalLog::writeFile(Game_setting& game, std::string data) {
    if (game.outFile.is_open()) {
        game.outFile << data << endl;
    }
    else {
        cerr << "File is not open!" << endl;
    }
}

void SurvivalLog::appendToFile(Game_setting& game, std::string text) {
    ofstream outFile("Survival Log", ios::app);
    if (!outFile) {
        cerr << "Error opening file for appending!" << endl;
        return;
    }
    outFile << text;
    outFile.close();
}

void SurvivalLog::closeFile(Game_setting& game) {
    if (game.outFile.is_open()) {
        game.outFile.close();
    }
}

void SurvivalLog::readFile(Game_setting& game) {
    ifstream inFile("Survival Log");
    if (!inFile) {
        cerr << "Error opening file: " << "Survival Log" << endl;
        return;
    }
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
}
