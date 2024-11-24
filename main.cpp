#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility> // For std::pair
using namespace std;

class Game_setting {
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

private:
    int day;
    int HP;
    int Hunger;
    int Mental;
    int step_remains;
    map<string, int> bag;
    vector<string> material;
    vector<string> ingredient;
    vector<string> food;
    vector<string> craft;
    vector<string> blueprint;
    vector<string> hunt;
    string weather; // Added to store weather info
};

void Game_setting::initialize_game() {
    day = 1;               // Correctly initializing member variables
    HP = 100;
    Hunger = 100;
    Mental = 100;

    material = {"metal", "wood", "leather"};
    ingredient = {"fruits", "fish", "meat", "beef", "bear meat", "wolf meat"};
    food = {"roast fish", "roast meat", "roast beef", "roast bear meat", "roast wolf meat"};
    craft = {"knife", "upgraded knife", "shelter", "upgraded shelter", "camp fire", "fur clothing", "boat"};
    blueprint = {"gun&bullet blueprint", "signal flare blueprint", "armor blueprint"};
    hunt = {"beef", "leather", "bear meat", "wolf meat"};
    weather = "sunny"; // Default weather
    cout << "Game initialized!" << endl;
}

void Game_setting::start_of_day() {
    step_remains = 4;
    cout << "Good morning! It's your " << day << " day on the island. The weather today is " << weather << "." << endl;
    cout << "You have " << step_remains << " actions available today.\n";
}

pair<char, char> Game_setting::selection_menu() {
    char choice;
    char ready_for_escape = 'N'; // Will be moved to main function later if needed

    // Print selection menu
    cout << "********************************" << endl;
    cout << "What do you want to do next:" << endl;
    cout << "********************************" << endl;
    cout << "[1] exploring the island" << endl;
    cout << "[2] cooking" << endl;
    cout << "[3] eating" << endl;
    cout << "[4] crafting" << endl;
    cout << "[5] resting" << endl;
    cout << "[6] hunting" << endl;
    cout << "[7] showing the bag" << endl;
    if ((bag.find("signal flare") != bag.end()) || (bag.find("boat") != bag.end())) {
        cout << "[8] attempt to escape" << endl;
        ready_for_escape = 'Y';
    }
    cout << "Please enter your choice: ";
    cin >> choice;
    cout << endl;

    return {choice, ready_for_escape}; // Return both choice and escape readiness
}

void Game_setting::perform_action() {
    while (step_remains > 0) {
        auto selection = selection_menu();
        char choice = selection.first;
        char ready_for_escape = selection.second;

        switch (choice) {
        case '1':
            exploreIsland();
            step_remains--;
            break;
        case '2':
            cookFood();
            step_remains--;
            break;
        case '3':
            eatFood();
            step_remains--;
            break;
        case '4':
            craftItem();
            step_remains--;
            break;
        case '5':
            rest();
            step_remains--;
            break;
        case '6':
            hunting();
            step_remains--;
            break;
        case '7':
            print_bag();
            break;
        case '8':
            if (ready_for_escape == 'Y') {
                attempt_escape();
                step_remains--;
            } else {
                cout << "You are not ready to escape yet!" << endl;
            }
            break;
        default:
            cout << "Invalid input!" << endl;
            break;
        }

        if (step_remains > 0) {
            cout << "You have " << step_remains << " steps remaining today.\n";
        } else {
            cout << "You have no steps remaining for today.\n";
        }
    }

    // Transition to the next day
    day++;
    cout << "The day has ended. Preparing for the next day...\n";
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"<<'\n';
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"<<'\n';
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"<<'\n';
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"<<'\n';

    start_of_day();
    perform_action(); // Start the next day's actions
}

void Game_setting::exploreIsland() {
    srand(time(0)); // Seed random number generator

    // Step 1: Random event occurs
    int event = rand() % 100 + 1; // Random number between 1 and 100
    if (event <= 20) { // Animal attack: 20% probability
        cout << "You were attacked by a wild animal and lost 40 HP!" << endl;
        HP -= 40;
    } else if (event <= 40) { // Discover cave: 20% probability
        cout << "***You discovered a cave that might house wild humans!***"<<'\n';
        cout << "Discovering the cave will cost you 140 HP (-140 HP), you have a 60% probability to find blueprints" << endl;
        cout << "Do you want to enter the cave? (Y/N): ";
        char choice1;
        cin >> choice1;

        if (choice1 == 'Y' || choice1 == 'y') {
            // Wild humans attack: -140 HP
            HP -= 140;
            cout << "You encountered wild humans and lost 140 HP!" << endl;

            // 60% chance of finding a blueprint
            if (rand() % 100 + 1 <= 60) {
                int blueprintIndex = rand() % blueprint.size();
                string foundBlueprint = blueprint[blueprintIndex];
                cout << "You found a blueprint: " << foundBlueprint << endl;
                bag[foundBlueprint]++; // Add blueprint to bag
            }
            else{cout << "There is nothing in the cave. Unlucky"<<endl;}
        } else {
            cout << "You decided to avoid the cave." << endl;
        }
    }
    cout << "Your current HP: " << HP << endl;
    if (HP <= 0) {
        cout << "You have succumbed to your injuries. Game Over!" << endl;
        exit(0); // End the game
    }
    // Step 2: Collect materials
    cout << "You can only look for either MATERIALS or INGREDIENTS each time." <<endl;
    cout << "Which one would you choose?"<<endl;
    cout << "**********************************" <<endl;
    cout << "[M] MATERIALS"<<endl;
    cout << "[I] INGREDIENTS" << endl;
    cout << "**********************************" <<endl;
    char choice2;
    cin >> choice2;
    cout << "<<< You have found ";
    if (choice2 == 'M'){


    int materialSet = rand() % 4; // Random set of materials
    switch (materialSet) {
    case 0:
        bag["metal"] += 2;
        bag["wood"] += 3;
        cout << "+2 metal, +3 wood" ;
        break;
    case 1:
        bag["wood"] += 4;
        bag["herb"] += 1;
        cout << "+4 wood, +1 herb" ;
        break;
    case 2:
        bag["metal"] += 5;
        cout << "+5 metal" ;
        break;
    case 3:
        bag["metal"] += 3;
        bag["wood"] += 3;
        bag["herb"] += 1;
        cout << "+3 metal, +3 wood, +1 herb" ;
        break;
    
    }}
    
    if (choice2 == 'I'){
    // Step 3: Collect ingredients
    
    int ingredientSet = rand() % 4; // Random set of ingredients
    switch (ingredientSet) {
    case 0:
        bag["fruit"] += 1;
        bag["fish"] += 1;
        cout << "+1 fruit, +1 fish" << endl;
        break;
    case 1:
        bag["fruit"] += 1;
        bag["meat"] += 1;
        cout << "+1 fruit, +1 meat" << endl;
        break;
    case 2:
        bag["fish"] += 1;
        bag["meat"] += 1;
        cout << "+1 fish, +1 meat" << endl;
        break;
    case 3:
        bag["fruit"] += 1;
        bag["fish"] += 1;
        bag["meat"] += 1;
        cout << "+1 fruit, +1 fish, +1 meat" << endl;
        break;
    }
    }  
    cout << ">>> during your exploration!" << endl;
}

void Game_setting::print_bag(){
    for (const auto& pair :bag){
        cout<< pair.first << ": "<< pair.second<<endl;
    }
}
void Game_setting::cookFood() {
    cout << "You cook some delicious food." << endl;
    // Add functionality for cooking
}

void Game_setting::eatFood() {
    cout << "You eat some food to regain strength." << endl;
    // Add functionality for eating
}

void Game_setting::craftItem() {
    cout << "You craft a new item using materials." << endl;
    // Add functionality for crafting
}

void Game_setting::rest() {
    cout << "You take a rest and regain energy." << endl;
    // Add functionality for resting
}

void Game_setting::hunting() {
    cout << "You go hunting and gather resources." << endl;
    // Add functionality for hunting
}

void Game_setting::attempt_escape() {
    cout << "You attempt to escape the island!" << endl;
    // Add functionality for escape attempts
}

int main() {
    Game_setting game;
    game.initialize_game();
    game.start_of_day();
    game.perform_action();

    return 0;
}