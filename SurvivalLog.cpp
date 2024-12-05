#include "SurvivalLog.h"
#include "GameSetting.h"
#include <iostream>
#include <fstream>

using namespace std;

//Opens a file named "Survival Log" for writing output.
//Inputs: Game_setting& game - A reference to a Game_setting object that contains an ofstream member named outFile.
void SurvivalLog::openFile(Game_setting& game) {
    game.outFile.open("Survival Log");
    if (!game.outFile) { //Checks if the file was successfully opened and prints an error message if it was not.
        cerr << "Error opening file!" << endl;
    }
} //No return value. Prints an error message to cerr if the file cannot be opened.

void SurvivalLog::writeFile(Game_setting& game, string data) {
    // input new data sting into the survival log
    if (game.outFile.is_open()) {
        game.outFile << data << endl;
    }
    else {
        cerr << "File is not open!" << endl;
    }
}

void SurvivalLog::appendToFile(Game_setting& game, string text) {
    //Input new text string into the survival log
    ofstream outFile("Survival Log", ios::app);
    if (!outFile) {
        cerr << "Error opening file for appending!" << endl;
        return;
    }
    outFile << text;
    outFile.close();
}

void SurvivalLog::closeFile(Game_setting& game) {
    // Close the file after all sting inputs
    if (game.outFile.is_open()) {
        game.outFile.close();
    }
}

void SurvivalLog::readFile(Game_setting& game) {
    //Print all the steps pthe layer did in the survival log
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
