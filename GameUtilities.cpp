#include "GameUtilities.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Randomly determines the weather for the day
string weather_ran() {
    srand(time(0)); // Note: srand should ideally be called once at the beginning of the program
    int weather_index = rand() % 101; // Generate a random number between 0 and 100

    if (weather_index <= 70) {
        return "sunny";
    }
    else if (weather_index <= 80) {
        return "extreme rainfall";
    }
    else if (weather_index <= 90) {
        return "extreme cold";
    }
    else {
        return "extreme hot";
    }
}

// Calculates the deduction in hunger and mental health based on weather
pair<int, int> deduction() {
    string weather = weather_ran(); // Get the current weather

    if (weather == "sunny" || weather == "extreme rainfall") {
        return make_pair(15, 5);
    }
    else if (weather == "extreme cold") {
        return make_pair(20, 5);
    }
    else { // Extreme hot
        return make_pair(15, 10);
    }
}

// Checks the player's health and issues warnings if necessary
int check_health(const map<string, int>& bag) { // Using const reference to avoid unnecessary copying
    int count = 0;
    if (bag.at("Hunger") < 20) {
        cout << "You are starving! WARNING!!!" << endl;
        count += 1;
    }
    if (bag.at("Mental") < 20) {
        cout << "Your mental is breaking down! WARNING!!!" << endl;
        count += 1;
    }
    return count;
}

// Checks if the player has a gun and bullet blueprint
bool check_gun_bullet_blueprint(const map<string, int>& bag) {
    return bag.at("gun&bullet blueprint") > 0;
}

// Checks if the player has a signal flare blueprint
bool check_signal_flare_blueprint(const map<string, int>& bag) {
    return bag.at("signal flare blueprint") > 0;
}

// Checks if the player has an armor blueprint
bool check_armor_blueprint(const map<string, int>& bag) {
    return bag.at("armor blueprint") > 0;
}