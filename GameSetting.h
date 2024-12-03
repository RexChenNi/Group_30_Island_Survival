#ifndef GAME_SETTING_H
#define GAME_SETTING_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class GameSetting {
public:
    void initialize_game();
    void start_of_day();
    pair<char, char> selection_menu();
    void perform_action();
    void exploreIsland();
    void cookFood();
    void eatFood();
    void craftItem();
    void rest();
    void hunting();
    void attempt_escape();
    void print_bag();
    void nightEvent();
    string weather_ran();
    pair<int, int> deduction();
    int check_health();
    bool check_gun_bullet_blueprint();
    bool check_signal_flare_blueprint();
    bool check_armor_blueprint();
    void blueprint_list();
    void wildAnimalAttack();
    void poor_sleeping_quality();

    int getHP() const { return HP; }
    void setHP(int value) { HP = value; }

    int getHunger() const { return Hunger; }
    void setHunger(int value) { Hunger = value; }

    int getMental() const { return Mental; }
    void setMental(int value) { Mental = value; }

    const map<string, int>& getBag() const { return bag; }
    int getBagItem(const string& item) const { return bag.at(item); }
    void addToBag(const string& item, int amount) { bag[item] += amount; }
    void setBagItem(const string& item, int amount) { bag[item] = amount; }

private:
    int day;
    int HP;
    int Hunger;
    int Mental;
    int step_remains;
    map<string, int> bag;
    vector<string> blueprints;
    string weather;

};

#endif // GAME_SETTING_H