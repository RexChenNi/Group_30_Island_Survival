#include "GameSetting.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

struct Node {
    string name;
    Node* next;
};

void Game_setting::initialize_game() { // Correctly initializing member variables
    day = 1;//initial number of day
    HP = 100;//initial hp        
    Hunger = 100;//initial hunger level
    Mental = 100;//initial mental level
    weather = "sunny"; // Default weather
    openFile();
    writeFile("This Survival Log records your actions in each day\n");
    cout << "Game initialized!" << endl;
    cout << "Cooking is allowed only when you have crafted campfire and shelter is key to survive the night!!!" << endl;
}

void Game_setting::print_bag() { //printing items in the bag owned by player 
    cout << "+--------------------+----------------+" << endl;
    cout << "|       Item         |     Quantity   |" << endl;
    cout << "+--------------------+----------------+" << endl;

    for (const auto& pair : bag) {
        if (pair.second == 0) continue;
        cout << "| " << setw(19) << left << pair.first
            << "| " << setw(15) << left << pair.second << "|" << endl;
    }

    cout << "+--------------------+----------------+" << endl;
}

void Game_setting::cookFood() {
    // Check if the player has a campfire
    if (bag.find("campfire") == bag.end() || bag["campfire"] < 1) {
        cout << "!!! You need a campfire to cook food. Craft one first!!!" << '\n' << endl;
        // Restore the player's remaining step since cooking is unavailable.
        step_remains++;
      // Call the crafting function to allow the player to create a campfire.
        craftItem();
        return; // Exit the function as cooking cannot proceed without a campfire.
    }

    // Display the cooking menu
    cout << "+-------------------+----------------------+" << endl;
    cout << "| Dish              | Ingredients Needed   |" << endl;
    cout << "+-------------------+----------------------+" << endl;
    cout << "| 1. Roast Fish     | Fish -1, Wood -1     |" << endl;
    cout << "| 2. Roast Meat     | Meat -1, Wood -1     |" << endl;
    cout << "| 3. Roast Beef     | Beef -1, Wood -1     |" << endl;
    cout << "| 4. Roast Mutton   | Mutton -1, Wood -1   |" << endl;
    cout << "| 5. Roast Bear     | Bear Meat -1, Wood -1|" << endl;
    cout << "| 6. Roast Wolf     | Wolf Meat -1, Wood -1|" << endl;
    cout << "+-------------------+----------------------+" << endl;

    int dishesCooked = 0; // Tracks the number of dishes cooked in this session.

    // Allow the player to cook up to two dishes per session.
    while (dishesCooked < 2) {
        cout << "Select a dish to cook (1-6), or enter 0 to stop: ";
        int choice;
        cin >> choice;

        // Stop cooking if the player enters 0
        if (choice == 0) {
            cout << "You decided to stop cooking." << endl;
            appendToFile("You decided to stop cooking.\n");
            break;
        }

        // Validate the choice and update inventory
        string dish;
        string ingredient;
        switch (choice) {
        case 1:
            dish = "roast fish";
            appendToFile("You had made a " + dish + "\n");
            ingredient = "fish";
            break;
        case 2:
            dish = "roast meat";
            appendToFile("You had made a " + dish + "\n");
            ingredient = "meat";
            break;
        case 3:
            dish = "roast beef";
            appendToFile("You had made a " + dish + "\n");
            ingredient = "beef";
            break;
        case 4:
            dish = "roast mutton";
            appendToFile("You had made a " + dish + "\n");
            ingredient = "mutton";
            break;
        case 5:
            dish = "roast bear meat";
            appendToFile("You had made a " + dish + "\n");
            ingredient = "bear meat";
            break;
        case 6:
            dish = "roast wolf meat";
            appendToFile("You had made a " + dish + "\n");
            ingredient = "wolf meat";
            break;
        default:
            // Handle invalid input and allow the player to try again.
            cout << "Invalid choice. Please select a valid dish." << endl;
            continue;
        }

        // Check if enough ingredients and wood are available
        if (bag[ingredient] < 1) {
            cout << "You don't have enough " << ingredient << " to cook " << dish << "." << endl;
        }
        else if (bag["wood"] < 1) {
            cout << "You don't have enough wood to cook " << dish << "." << endl;
        }
        else {
            // Deduct ingredients and wood, and add the cooked dish to the inventory
            bag[ingredient]--;
            bag["wood"]--;
            bag[dish]++;
            dishesCooked++;
            cout << "You cooked " << dish << "! Remaining dishes to cook: " << (2 - dishesCooked) << endl;
        }
    }
    // check if the player has the necessary resources
    if (dishesCooked == 0) {
        cout << "You didn't cook anything today." << endl;
    }
    else {
        cout << "Cooking session complete. You cooked " << dishesCooked << " dish(es)." << endl;
    }


}

void Game_setting::eatFood() {   
    //disaplay a selection menu of the food for players to recover their conditions
    cout << "+-------------------------------+" << endl;
    cout << "|          Eating Menu          |" << endl;
    cout << "+-------------------------------+" << endl;
    cout << "| [1] Fruit: Recover 30 Hunger |" << endl;
    cout << "| [2] Fish: Recover 30 Hunger,  |" << endl;
    cout << "|     -20 HP, -5 Mental         |" << endl;
    cout << "| [3] Meat: Recover 40 Hunger,  |" << endl;
    cout << "|     -20 HP, -15 Mental        |" << endl;
    cout << "| [4] Roast Fish: Recover 50    |" << endl;
    cout << "|     Hunger, +20 Mental        |" << endl;
    cout << "| [5] Roast Meat: Recover 60    |" << endl;
    cout << "|     Hunger, +10 Mental        |" << endl;
    cout << "| [6] Roast Beef: Recover 80    |" << endl;
    cout << "|     Hunger, +20 Mental        |" << endl;
    cout << "| [7] Roast Bear Meat: Recover  |" << endl;
    cout << "|     100 Hunger, +50 Mental    |" << endl;
    cout << "| [8] Roast Wolf Meat: Recover  |" << endl;
    cout << "|     100 Hunger, +50 Mental    |" << endl;
    cout << "| [9] Herb: Recover 60 HP       |" << endl;
    cout << "+-------------------------------+" << endl;

    int choice;
    cout << "What would you like to eat? Enter your choice: ";
    cin >> choice;
    // choice in numerical numbers
    switch (choice) {
    case 1: // Fruits
        if (bag["fruit"] > 0) {
            bag["fruit"]--;
            Hunger = min(100, Hunger + 30);
            cout << "You ate a fruit. Hunger bar recovered by 30." << endl;
        }
        else {
            cout << "You have no fruit!" << endl;
        }
        break;

    case 2: // Fish
        if (bag["fish"] > 0) {
            bag["fish"]--;
            Hunger = min(100, Hunger + 30);
            HP -= 20;
            Mental -= 5;
            cout << "You ate a fish directly. Hunger recovered by 30, HP decreased by 20, and Mental decreased by 5." << endl;
        }
        else {
            cout << "You have no fish!" << endl;
        }
        break;

    case 3: // Meat
        if (bag["meat"] > 0) {
            bag["meat"]--;
            Hunger = min(100, Hunger + 40);
            HP -= 20;
            Mental -= 15;
            cout << "You ate meat directly. Hunger recovered by 40, HP decreased by 20, and Mental decreased by 15." << endl;
        }
        else {
            cout << "You have no meat!" << endl;
        }
        break;

    case 4: // Roast Fish
        if (bag["roast fish"] > 0) {
            bag["roast fish"]--;
            Hunger = min(100, Hunger + 50);
            Mental = min(100, Mental + 20);
            cout << "You ate roast fish. Hunger recovered by 50, Mental recovered by 20." << endl;
        }
        else {
            cout << "You have no roast fish!" << endl;
        }
        break;

    case 5: // Roast Meat
        if (bag["roast meat"] > 0) {
            bag["roast meat"]--;
            Hunger = min(100, Hunger + 60);
            Mental = min(100, Mental + 10);
            cout << "You ate roast meat. Hunger recovered by 60, Mental recovered by 10." << endl;
        }
        else {
            cout << "You have no roast meat!" << endl;
        }
        break;

    case 6: // Roast Beef
        if (bag["roast beef"] > 0) {
            bag["roast beef"]--;
            Hunger = min(100, Hunger + 80);
            Mental = min(100, Mental + 20);
            cout << "You ate roast beef. Hunger recovered by 80, Mental recovered by 20." << endl;
        }
        else {
            cout << "You have no roast beef!" << endl;
        }
        break;

    case 7: // Roast Bear Meat
        if (bag["roast bear meat"] > 0) {
            bag["roast bear meat"]--;
            Hunger = min(100, Hunger + 100);
            Mental = min(100, Mental + 50);
            cout << "You ate roast bear meat. Hunger recovered by 100, Mental recovered by 50." << endl;
        }
        else {
            cout << "You have no roast bear meat!" << endl;
        }
        break;

    case 8: // Roast Wolf Meat
        if (bag["roast wolf meat"] > 0) {
            bag["roast wolf meat"]--;
            Hunger = min(100, Hunger + 100);
            Mental = min(100, Mental + 50);
            cout << "You ate roast wolf meat. Hunger recovered by 100, Mental recovered by 50." << endl;
        }
        else {
            cout << "You have no roast wolf meat!" << endl;
        }
        break;
    case 9:
        if (bag["herb"] > 0) {
            HP += 60;
            bag["herb"]--;
            HP = min(100, HP);
            cout << "You ate herb and recovered 60 HP." << endl;
        }
        else {
            cout << "You don't have any herb!" << endl;
        }
        break;

    default:
        cout << "Invalid choice! Please select a valid food option." << endl;
        break;
    }
}

void Game_setting::craftItem() {  
    // Allowing players to craft items to reduce the deduction of HP, hunger or metal
    // Allowing players to craft campfire and enabling the cookfood option in the selection menu
    // Allowing players to craft boats, Gun&bullet, Signal Flare or Armor, which are crucial items for winning the game
    cout << "+--------------------+---------------------+" << endl;
    cout << "| 1. Campfire       | Wood-5               |" << endl;
    cout << "| 2. Knife          | Wood-3 , Metal-3     |" << endl;
    cout << "| 3. Upgrade Knife  | Wood-10, Metal-10    |" << endl;
    cout << "| 4. Build Shelter  | Wood-10, Metal-4     |" << endl;
    cout << "| 5. Upgrade Shelter| Wood-10, Metal-6     |" << endl;
    cout << "| 6. Fur Clothing   | Leather-10           |" << endl;
    cout << "| 7. Boat           | Wood-35, Metal-20    |" << endl;
    // choice 8 only enables when Gun&bullet was explored in the island and stored in the bag map
    if (check_gun_bullet_blueprint()) {
        cout << "| 8. Gun&bullet     | Metal-15             |" << endl;
    }
    // choice 9 only enables when Signal Flare was explored in the island and stored in the bag map

    if (check_signal_flare_blueprint()) {
        cout << "| 9. Signal Flare   | Metal-20             |" << endl;
    }
    // choice 10 only enables when Armor was explored in the island and stored in the bag map

    if (check_armor_blueprint()) {
        cout << "| 10.Armor          | Metal-10, Leather-10 |" << endl;
    }
    cout << "+--------------------+---------------------+" << endl;

    cout << "Enter the number of the item you want to craft, or 0 to cancel: ";
    int choice;
    cin >> choice;

    if (choice == 0) {
        cout << "You decided not to craft anything." << endl;
        appendToFile("Nothing\n");
        return;
    }

    switch (choice) {
    case 1: // Campfire
        if (bag["campfire"] > 0) {
            appendToFile("Nothing\n");
            cout << "You have already crafted a campfire!" << endl;
        }
        else if (bag["wood"] >= 5) {
            bag["wood"] -= 5;
            bag["campfire"]++;
            appendToFile("campfire\n");
            cout << "You crafted a campfire! It has been added to your inventory." << endl;
        }
        else {
            cout << "You don't have enough wood to craft a campfire. You need 5 wood." << endl;
        }
        break;

    case 2: // Knife
        if (bag["wood"] >= 3 && bag["metal"] >= 3) {
            bag["wood"] -= 3;
            bag["metal"] -= 3;
            appendToFile("knife\n");
            bag["knife"]++;
            cout << "You crafted a knife! It has been added to your inventory." << endl;
        }
        else {
            cout << "You don't have enough resource to craft a knife. You need 3 wood and 3 metal." << endl;
        }
        break;

    case 3: // Upgraded Knife
        if (bag["wood"] >= 10 && bag["metal"] >= 10 && bag["knife"] >= 1) {
            bag["wood"] -= 10;
            bag["metal"] -= 10;
            bag["knife"] -= 1;
            appendToFile("upgraded knife\n");
            bag["upgraded knife"]++;
            cout << "You upgraded your knife! It has been added to your inventory." << endl;
        }
        else {
            cout << "You cannot upgrade your knife. You need a knife, 10 wood and 10 metal." << endl;
        }
        break;

    case 4: // Shelter
        if (bag["shelter"] == 1 || bag["upgraded shelter"] == 1) {
            cout << "You already have a shelter" << endl;
            appendToFile("nothing\n");
        }
        else if (bag["wood"] >= 10 && bag["metal"] >= 4) {
            bag["wood"] -= 10;
            bag["metal"] -= 4;
            bag["shelter"]++;
            appendToFile("shelter\n");
            cout << "You have created a shelter! It has been added to your inventory." << endl;

        }
        else {
            appendToFile("nothing\n");
            cout << "You don't have enough resource to craft a shelter. You need 10 wood and 4 metal." << '\n' << endl;
        }
        break;


    case 5: // Upgraded Shelter
        if (bag["upgraded shelter"] == 1) {
            appendToFile("nothing\n");
            cout << "You already have a upgraded shelter" << endl;
        }
        else if (bag["shelter"] == 1 && bag["wood"] >= 10 && bag["metal"] >= 6) {
            bag["wood"] -= 10;
            bag["metal"] -= 6;
            bag["upgraded shelter"]++;
            appendToFile("upgraded shelter\n");
            bag["shelter"]--;
            cout << "You have upgraded your shelter! It has been added to your inventory." << endl;
        }
        else {
            appendToFile("nothing\n");
            cout << "You cannot upgrade your shelter. You need a shelter, 10 wood and 6 metal" << '\n' << endl;
        }
        break;

    case 6: // Fur Clothing
        if (bag["leather"] >= 10) {
            bag["leather"] -= 10;
            bag["fur clothing"]++;
            appendToFile("fur clothing\n");
            cout << "You crafted a fur clothing! It has been added to your inventory." << endl;
        }
        else {
            cout << "You don't have enough leather to craft a fur clothing. You need 10 leather." << endl;
        }
        break;


    case 7: // Boat
        if (bag["boat"] != 0) {
            appendToFile("Nothing\n");
            cout << "You already have a boat!" << endl;

        }
        else if (bag["wood"] >= 35 && bag["metal"] >= 20) {
            bag["wood"] -= 35;
            bag["metal"] -= 20;
            bag["boat"]++;
            appendToFile("boat\n");
            cout << "You crafted a boat! You can now attempt to escape the island!" << endl;
        }
        else {
            cout << "You don't have enough resource to craft a boat. You need 50 wood and 30 metal." << endl;
        }
        break;


    case 8: // gun&bullet
        if (bag["metal"] >= 15 && bag["gun&bullet blueprint"] > 0) {
            bag["metal"] -= 15;
            appendToFile("gun&bullet\n");
            bag["gun&bullet"]++;
            cout << "You crafted a gun&bullet" << endl;
        }
        else {
            cout << "You don't have enough metal to craft a gun&bullet. You need 15 metal and a gun&bullet blueprint" << endl;
        }
        break;

    case 9: // signal flare blueprint
        if (bag["metal"] >= 20 && bag["signal flare blueprint"] > 0) {
            bag["metal"] -= 20;
            bag["signal flare"]++;
            appendToFile("signal flare\n");
            cout << "You crafted a signal flare" << endl;
        }
        else {
            cout << "You don't have enough metal to craft a signal flare. You need 20 metal and a signal flare blueprint" << endl;
        }
        break;

    case 10: // armor blueprint
        if (bag["metal"] >= 10 && bag["leather"] >= 10 && bag["fur clothing"] >= 1 && bag["armor blueprint"] > 0) {
            bag["metal"] -= 10;
            bag["leather"] -= 10;
            bag["fur clothing"] -= 1;
            bag["armor"]++;
            appendToFile("armor\n");
            cout << "You crafted an armor" << endl;
        }
        else {
            cout << "You cannot craft an armor. You need 10 metal, 10 leather, a fur clothing and an armor blueprint" << endl;
        }
        break;

    default:
        appendToFile("Nothing\n");
        cout << "Invalid choice. Please select a valid item to craft." << endl;
        break;
    }

    // Display updated bag
    cout << "\nYour updated bag after crafting:\n";
    print_bag();
}

void Game_setting::wildAnimalAttack() {
    int shield = 0;
    if (bag["knife"] > 0) shield += bag["knife"] * 10;
    if (bag["upgraded knife"] > 0) shield += bag["upgraded knife"] * 30;
    if (bag["fur clothing"] > 0) shield += bag["fur clothing"] * 20;
    if (bag["gun&bullet"] > 0) shield += bag["gun&bullet"] * 50;
    if (bag["armor"] > 0) shield += bag["armor"] * 50;
    int damage = 40 - shield;
    HP -= (max(40 - shield, 0)); //from crafted items
    cout << "You were attacked by a wild animal during the night and lost " << max(damage, 0) << " HP!" << endl;
}

void Game_setting::poor_sleeping_quality() {
    cout << "You have had a poor sleeping quality at night and your mental bar droped by 15!" << endl;
    Mental -= 15;
}

void Game_setting::night_event() {
    int night_ran;
    srand(time(0));
    night_ran = rand() % 101;
    cout << "*** Night is falling... ***" << endl;
    if (bag["upgraded shelter"] == 1) {
        cout << "Your upgraded shelter kept you safe through the night." << endl;
        return;
    }

    if (bag["shelter"] == 1) {
        cout << "Your shelter kept you safe, but it wasn't very comfortable." << endl;
        if (night_ran >= 0 && night_ran <= 70) {
            return;
        }

        if (night_ran > 70 && night_ran <= 90) {
            wildAnimalAttack();
            return;
        }
        if (night_ran > 90 && night_ran <= 100) {
            poor_sleeping_quality();
            return;
        }
    }

    cout << "You managed to survive the night without a shelter, but it was tough." << endl;
    if (night_ran >= 0 && night_ran <= 60) return;
    if (night_ran > 60 && night_ran <= 80) {
        wildAnimalAttack();
        return;
    }
    if (night_ran > 80 && night_ran <= 100) {
        poor_sleeping_quality();
        return;
    }
}

void Game_setting::rest() {
    cout << "You take a rest and regain energy." << endl;
    // Add functionality for resting
    HP += 20;
    HP -= check_health() * 20;
    Hunger -= deduction().first;
    Mental += 20;
    if (Hunger <= 0)  Hunger = (max(Hunger, 0));
    else Hunger = min(Hunger, 100);
    if (HP <= 0)  HP = (max(HP, 0));
    else HP = min(HP, 100);
    if (Mental <= 0)  Mental = (max(Mental, 0));
    else Mental = min(Mental, 100);
}

void Game_setting::hunting() {
    // Random event generator for hunting
    int hunt_event = rand() % 100;
    int shield = 0;
    if (bag["knife"] > 0) shield += bag["knife"] * 10;
    if (bag["upgraded knife"] > 0) shield += bag["upgraded knife"] * 30;
    if (bag["fur clothing"] > 0) shield += bag["fur clothing"] * 20;
    if (bag["gun&bullet"] > 0) shield += bag["gun&bullet"] * 50;
    if (bag["armor"] > 0) shield += bag["armor"] * 50;
    if (hunt_event < 35) {
        // Bear attack
        HP -= max(40 - shield, 0);
        bag["bear meat"]++;
        cout << " You lost " << max(40 - shield, 0) << " HP  in a bear attack!" << endl;
        appendToFile("You successfully hunted a bear and obtained 1 bear meat, 1 beef and 3 leather!\n");
        cout << "You successfully hunted a bear and obtained 1 bear meat, 1 beef and 3 leather!" << endl;
    }
    else if (hunt_event < 70) {
        // Wolf attack
        HP -= max(40 - shield, 0);
        bag["wolf meat"]++;
        cout << " You lost " << max(40 - shield, 0) << " HP in a wolf attack!" << endl;
        cout << "You successfully hunted a wolf and obtained 1 wolf meat, 1 beef and 3 leather!" << endl;
        appendToFile("You successfully hunted a wolf and obtained 1 wolf meat, 1 beef and 3 leather!\n");
    }
    else {
        //no attack
        cout << "You did not encounter any attack and obtained 1 beef and 3 leather!" << endl;
        appendToFile("You did not encounter any attack and obtained 1 beef and 3 leather!\n");
    }
    bag["beef"] += 1;
    bag["leather"] += 3;

    // Ensure HP does not drop below 0
    if (HP < 0) HP = 0;
}

void Game_setting::attempt_escape() {
    if (bag.find("boat") != bag.end() || bag.find("signal flare") != bag.end()) {
        cout << "You have the necessary items to attempt an escape!" << endl;

        // Random chance of successful escape
        int escape_chance = rand() % 100;
        if (escape_chance < 70) { // 70% chance of successful escape
            appendToFile("Succeed!");
            cout << "Congratulations! You have successfully escaped the island!" << endl;
            exit(0);
        }
        else {
            cout << "Your escape attempt failed." << endl;
            appendToFile("Failed!");
            HP -= 50; //
            if (HP < 0) HP = 0;
            cout << "You lost 50 HP during the failed escape attempt. Current HP: " << HP << endl;
        }
    }
    else {
        appendToFile("Nothing");
        cout << "You do not have the necessary items to attempt an escape!" << endl;
    }
}

string Game_setting::weather_ran() {
    int weather_index;
    string weather;
    srand(time(NULL));
    weather_index = rand() % 101;
    if (weather_index >= 0 && weather_index <= 70) {
        weather = "sunny";
    }
    else if (weather_index >= 71 && weather_index <= 80) {
        weather = "extreme rainfall";
    }
    else if (weather_index >= 81 && weather_index <= 90) {
        weather = "extreme cold";
    }
    else if (weather_index >= 91 && weather_index <= 100) {
        weather = "extreme hot";
    }
    return weather;
}

pair<int, int>Game_setting::deduction() {
    pair<int, int> deduction;
    if (weather == "sunny") {
        deduction.first = 15;
        deduction.second = 5;
    }
    else if (weather == "extreme rainfall") {
        deduction.first = 15;
        deduction.second = 5;
    }
    else if (weather == "extreme cold") {
        deduction.first = 20;
        deduction.second = 5;
    }
    else if (weather == "extreme hot") {
        deduction.first = 15;
        deduction.second = 10;
    }
    return deduction;
}

int Game_setting::check_health() {
    int count = 0;
    if (Hunger < 20 && HP != 0) {
        cout << "You are starving! WARNING!!!" << endl;
        count += 1;
    }
    if (Mental < 20 && HP != 0) {
        cout << "Your mental is breaking down! WARNING!!!" << endl;
        count += 1;
    }
    if (HP <= 0) {
        cout << "You died..." << endl;
        cout << "We have a Survival Log for you.Do you want to read it? [Y/N]" << endl;
        appendToFile("You died");
        char read;
        cin >> read;
        if (tolower(read) == 'y') readFile();
        if (tolower(read) == 'n') exit(0);
        exit(0);
    }
    return count;
}

bool Game_setting::check_gun_bullet_blueprint() {
    bool has_gun_bullet = false;
    if (bag["gun&bullet blueprint"] > 0) {
        has_gun_bullet = true;
    }
    return has_gun_bullet;
}

bool Game_setting::check_signal_flare_blueprint() {
    bool has_signal = false;
    if (bag["signal flare blueprint"] > 0) {
        has_signal = true;
    }
    return has_signal;
}

bool Game_setting::check_armor_blueprint() {
    bool has_armor = false;
    if (bag["armor blueprint"] > 0) {
        has_armor = true;
    }
    return has_armor;
}

void Game_setting::openFile() {
    outFile.open("Survival Log");
    if (!outFile) {
        cerr << "Error opening file!" << endl;
    }
}

void Game_setting::writeFile(string data) {
    if (outFile.is_open()) {
        outFile << data << endl;
    }
    else {
        cerr << "File is not open!" << endl;
    }
}

void Game_setting::appendToFile(string text) {
    // Open the file in append mode
    ofstream outFile("Survival Log", ios::app);

    // Check if the file opened successfully
    if (!outFile) {
        cerr << "Error opening file for appending!" << endl;
        return;
    }

    // Write the text to the file
    outFile << text; // Add a newline after the text

    // Close the file
    outFile.close();
}

void Game_setting::closeFile() {
    if (outFile.is_open()) {
        outFile.close();
    }
}

void Game_setting::readFile() {
    ifstream inFile("Survival Log"); // Open the file

    // Check if the file opened successfully
    if (!inFile) {
        cerr << "Error opening file: " << "Survival Log" << endl;
        return;
    }

    string line;
    // Read the file line by line
    while (getline(inFile, line)) {
        cout << line << endl; // Print each line to the console
    }

    // Close the file
    inFile.close();
}

 void Game_setting::delete_list(Node*& head) {
    Node* current = head;
    Node* nextNode;

    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
}

void Game_setting::blueprint_list() {
    Node* head = nullptr;

    if (check_gun_bullet_blueprint()) {
        Node* P = new Node;
        P->name = "gun bullet blueprint";
        P->next = head;
        head = P;
    }

    if (check_signal_flare_blueprint()) {
        Node* P = new Node;
        P->name = "signal flare blueprint";
        P->next = head;
        head = P;
    }

    if (check_armor_blueprint()) {
        Node* P = new Node;
        P->name = "armor blueprint";
        P->next = head;
        head = P;
    }

    Node* current = head;
    while (current != NULL) {
        cout << current->name << endl;
        current = current->next;
    }

    delete_list(head);
}

