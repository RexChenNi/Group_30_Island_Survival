#ifndef GAME_SETTING_H
#define GAME_SETTING_H

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
using namespace std;

class Game_setting {
public:
    void initialize_game();
    void start_of_day();
    void perform_action();
    void exploreIsland();
    void cookFood();
    void eatFood();
    void craftItem();
    void rest();
    void hunting();
    void attempt_escape();
    void print_bag();
    string weather_ran();
    pair<int, int> deduction();
    pair<char, char> selection_menu();
    int check_health();
    bool check_gun_bullet_blueprint();
    bool check_signal_flare_blueprint();
    bool check_armor_blueprint();
    void blueprint_list();
    void wildAnimalAttack();
    void poor_sleeping_quality();
    void night_event();
    void openFile();
    void writeFile(string data);
    void appendToFile(string text);
    void readFile();
    void closeFile();
    ofstream outFile;

private:
    int day;
    int HP;
    int Hunger;
    int Mental;
    int step_remains;
    map<string, int> bag;
    vector<string> blueprints;
    string weather;
    struct Node{
        string name;
        Node* next;
};

    void delete_list(Node*& head);
  


};

#endif
