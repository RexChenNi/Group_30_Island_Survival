// GameSetting.h
#ifndef GAME_SETTING_H
#define GAME_SETTING_H

#include <map>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class GameSetting {
public:
    // Existing public methods...
    void initialize_game();
    void start_of_day();
    pair<char, char> selection_menu();
    void perform_action();
    // Other methods...

    // Getter and Setter methods
    int getHP() const;
    void setHP(int value);
    int getHunger() const;
    void setHunger(int value);
    int getMental() const;
    void setMental(int value);
    int getBagItem(const string& item) const;

private:
    int day;
    int HP;
    int Hunger;
    int Mental;
    int step_remains;
    map<string, int> bag;
    vector<string> blueprints;
    string weather;

    // Node struct for managing linked lists, such as blueprints
    struct Node {
        string name;
        Node* next;
    };

    // Existing private methods...
    void delete_list(Node*& head);
};

#endif // GAME_SETTING_H
