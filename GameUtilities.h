// GameUtilities.h
#ifndef GAME_UTILITIES_H
#define GAME_UTILITIES_H

#include <string>
#include <map>
#include <utility>

using namespace std;

string weather_ran();
pair<int, int> deduction();
int check_health();
bool check_gun_bullet_blueprint(const map<string, int>& bag);
bool check_signal_flare_blueprint(const map<string, int>& bag);
bool check_armor_blueprint(const map<string, int>& bag);

#endif // GAME_UTILITIES_H
