#include "GameActions.h"
#include "GameSetting.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm> // For std::max and std::min

using namespace std;

// Explore the island for resources or encounters
void exploreIsland(GameSetting& game) {
    srand(time(0)); // Seed the random number generator for exploration events

    cout << "+------------------------------------------------+" << endl;
    cout << "| You can only look for either MATERIALS or       |" << endl;
    cout << "| INGREDIENTS each time.                         |" << endl;
    cout << "| Which one would you choose?                    |" << endl;
    cout << "+------------------------------------------------+" << endl;
    cout << "| [M] MATERIALS                                  |" << endl;
    cout << "| [I] INGREDIENTS                                |" << endl;
    cout << "+------------------------------------------------+" << endl;

    char choice1;
    cin >> choice1;

    // Calculate potential damage reduction from items
    int shield = 0;
    shield += game.getBagItem("knife") * 10;
    shield += game.getBagItem("upgraded knife") * 30;
    shield += game.getBagItem("fur clothing") * 20;
    shield += game.getBagItem("gun&bullet") * 50;
    shield += game.getBagItem("armor") * 50;

    // Random event during exploration
    int event = rand() % 100 + 1;
    if (event <= 20) {
        // Animal attack event
        cout << "You were attacked by a wild animal while exploring the island and lost "
            << max(40 - shield, 0) << " HP! Crafted items like knives or fur clothing have reduced the damage." << endl;
        int damage = max(40 - shield, 0);
        game.setHP(game.getHP() - damage);
    }
    else if (event <= 40) {
        // Discover cave event
        cout << "*** You stumbled upon a mysterious cave that might hold hidden dangers or treasures! ***" << endl;
        cout << "Exploring the cave has a 70% chance of being trapped, costing you "
            << 140 - shield << " HP. Crafted items like knives or fur clothing have reduced the damage." << endl;

        char choice;
        cout << "Do you wish to take the risk and enter the cave? (Y/N): ";
        cin >> choice;

        if (tolower(choice) == 'y') {
            int caveEvent = rand() % 100 + 1;

            if (caveEvent <= 70) {
                // Trapped in the cave event
                int damage = max(140 - shield, 0);
                game.setHP(game.getHP() - damage);
                cout << "You were trapped in the cave and lost " << damage << " HP!" << endl;
            }
            else if (caveEvent <= 90) {
                // Found blueprints event
                string blueprint;
                if (!game.getBag().empty()) {
                    // This is a simplified example; you might want to handle blueprints differently
                    map<string, int>::iterator it = game.getBag().begin();
                    blueprint = it->first;
                    game.addToBag(blueprint, 1);
                }
                cout << "Congrats! You discovered valuable " << blueprint << " inside the cave! These could help you craft powerful items." << endl;
            }
            else {
                // Nothing found event
                cout << "You carefully explored the cave but found nothing unusual. At least you came out unharmed." << endl;
            }
        }
        else {
            cout << "You decided not to take the risk and left the cave untouched." << endl;
        }
    }
    else {
        cout << "You managed to explore the island without any significant events." << endl;
    }

    if (game.getHP() <= 0) {
        cout << "You have succumbed to your injuries. Game Over!" << endl;
        exit(0);
    }

    // Collect materials or ingredients based on the player's choice
    cout << "\nYou found <<< ";
    if (choice1 == 'M' || choice1 == 'm') {
        int materialSet = rand() % 4;
        switch (materialSet) {
        case 0:
            game.addToBag("metal", 2);
            game.addToBag("wood", 3);
            cout << "+2 metal, +3 wood";
            break;
        case 1:
            game.addToBag("wood", 5);
            game.addToBag("herb", 1);
            cout << "+5 wood, +1 herb";
            break;
        case 2:
            game.addToBag("metal", 5);
            cout << "+5 metal";
            break;
        case 3:
            game.addToBag("metal", 3);
            game.addToBag("wood", 3);
            game.addToBag("herb", 1);
            cout << "+3 metal, +3 wood, +1 herb";
            break;
        }
    }
    else if (choice1 == 'I' || choice1 == 'i') {
        int ingredientSet = rand() % 4;
        switch (ingredientSet) {
        case 0:
            game.addToBag("fruit", 1);
            game.addToBag("fish", 1);
            cout << "+1 fruit, +1 fish";
            break;
        case 1:
            game.addToBag("fruit", 1);
            game.addToBag("meat", 1);
            cout << "+1 fruit, +1 meat";
            break;
        case 2:
            game.addToBag("fish", 1);
            game.addToBag("meat", 1);
            cout << "+1 fish, +1 meat";
            break;
        case 3:
            game.addToBag("fruit", 1);
            game.addToBag("fish", 1);
            game.addToBag("meat", 1);
            cout << "+1 fruit, +1 fish, +1 meat";
            break;
        }
    }
    cout << " >>> during your exploration!" << endl;
}

// Cook food using the campfire
void cookFood(GameSetting& game) {
    // Check if the player has a campfire
    if (game.getBagItem("campfire") == 0) {
        cout << "!!! You need a campfire to cook food. Craft one first!!!" << endl;
        return;
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

    int choice;
    cout << "Select a dish to cook (1-6), or enter 0 to stop: ";
    cin >> choice;

    if (choice == 0) {
        cout << "You decided to stop cooking." << endl;
        return;
    }

    if (choice < 1 || choice > 6) {
        cout << "Invalid choice. Please select a valid dish." << endl;
        return;
    }

    // Map of dishes to their ingredients
    map<int, pair<string, string>> dishIngredients = {
        {1, {"fish", "wood"}},
        {2, {"meat", "wood"}},
        {3, {"beef", "wood"}},
        {4, {"mutton", "wood"}},
        {5, {"bear meat", "wood"}},
        {6, {"wolf meat", "wood"}}
    };

    auto ingredients = dishIngredients[choice];

    // Check if the player has enough ingredients
    if (game.getBagItem(ingredients.first) < 1) {
        cout << "You don't have enough "<< ingredients.first << " to cook " << ingredients.second << "." << endl;
            return;
    }
    if (game.getBagItem("wood") < 1) {
        cout << "You don't have enough wood to cook " << ingredients.second << "." << endl;
        return;
    }

    // Cook the food
    game.addToBag(ingredients.first, -1); // Deduct one unit of the main ingredient
    game.addToBag("wood", -1); // Deduct one unit of wood
    game.addToBag("cooked " + ingredients.first, 1); // Add one unit of the cooked dish to the inventory

    cout << "You cooked " << ingredients.second << " using " << ingredients.first << " and wood." << endl;
}

// Eat food to restore hunger and mental health
void eatFood(GameSetting& game) {
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

    if (choice < 1 || choice > 9) {
        cout << "Invalid choice! Please select a valid food option." << endl;
        return;
    }

    switch (choice) {
    case 1: // Fruits
        if (game.getBagItem("fruit") > 0) {
            game.addToBag("fruit", -1);
            game.setHunger(max(0, game.getHunger() + 30));
            cout << "You ate a fruit. Hunger bar recovered by 30." << endl;
        }
        else {
            cout << "You have no fruit!" << endl;
        }
        break;

    case 2: // Fish
        if (game.getBagItem("fish") > 0) {
            game.addToBag("fish", -1);
            game.setHunger(max(0, game.getHunger() + 30));
            game.setHP(max(0, game.getHP() - 20));
            game.setMental(max(0, game.getMental() - 5));
            cout << "You ate a fish directly. Hunger recovered by 30, HP decreased by 20, and Mental decreased by 5." << endl;
        }
        else {
            cout << "You have no fish!" << endl;
        }
        break;

    case 3: // Meat
        if (game.getBagItem("meat") > 0) {
            game.addToBag("meat", -1);
            game.setHunger(max(0, game.getHunger() + 40));
            game.setHP(max(0, game.getHP() - 20));
            game.setMental(max(0, game.getMental() - 15));
            cout << "You ate meat directly. Hunger recovered by 40, HP decreased by 20, and Mental decreased by 15." << endl;
        }
        else {
            cout << "You have no meat!" << endl;
        }
        break;

    case 4: // Roast Fish
        if (game.getBagItem("roast fish") > 0) {
            game.addToBag("roast fish", -1);
            game.setHunger(max(0, game.getHunger() + 50));
            game.setMental(min(100, game.getMental() + 20));
            cout << "You ate roast fish. Hunger recovered by 50, Mental recovered by 20." << endl;
        }
        else {
            cout << "You have no roast fish!" << endl;
        }
        break;

    case 5: // Roast Meat
        if (game.getBagItem("roast meat") > 0) {
            game.addToBag("roast meat", -1);
            game.setHunger(max(0, game.getHunger() + 60));
            game.setMental(min(100, game.getMental() + 10));
            cout << "You ate roast meat. Hunger recovered by 60, Mental recovered by 10." << endl;
        }
        else {
            cout << "You have no roast meat!" << endl;
        }
        break;

    case 6: // Roast Beef
        if (game.getBagItem("roast beef") > 0) {
            game.addToBag("roast beef", -1);
            game.setHunger(max(0, game.getHunger() + 80));
            game.setMental(min(100, game.getMental() + 20));
            cout << "You ate roast beef. Hunger recovered by 80, Mental recovered by 20." << endl;
        }
        else {
            cout << "You have no roast beef!" << endl;
        }
        break;

    case 7: // Roast Bear Meat
        if (game.getBagItem("roast bear meat") > 0) {
            game.addToBag("roast bear meat", -1);
            game.setHunger(max(0, game.getHunger() + 100));
            game.setMental(min(100, game.getMental() + 50));
            cout << "You ate roast bear meat. Hunger recovered by 100, Mental recovered by 50." << endl;
        }
        else {
            cout << "You have no roast bear meat!" << endl;
        }
        break;

    case 8: // Roast Wolf Meat
        if (game.getBagItem("roast wolf meat") > 0) {
            game.addToBag("roast wolf meat", -1);
            game.setHunger(max(0, game.getHunger() + 100));
            game.setMental(min(100, game.getMental() + 50));
            cout << "You ate roast wolf meat. Hunger recovered by 100, Mental recovered by 50." << endl;
        }
        else {
            cout << "You have no roast wolf meat!" << endl;
        }
        break;

    case 9: // Herb
        if (game.getBagItem("herb") > 0) {
            game.addToBag("herb", -1);
            game.setHP(min(100, game.getHP() + 60));
            cout << "You ate herb and recovered 60 HP." << endl;
        }
        else {
            cout << "You don't have any herb!" << endl;
        }
        break;
    }
}

// Craft items from available resources
void craftItem(GameSetting& game) {
    cout << "+--------------------+---------------------+" << endl;
    cout << "| 1. Campfire       | Wood-5               |" << endl;
    cout << "| 2. Knife          | Wood-3 , Metal-3     |" << endl;
    cout << "| 3. Upgrade Knife  | Wood-10, Metal-10    |" << endl;
    cout << "| 4. Build Shelter  | Wood-10, Metal-4     |" << endl;
    cout << "| 5. Upgrade Shelter| Wood-10, Metal-6     |" << endl;
    cout << "| 6. Fur Clothing   | Leather-10           |" << endl;
    cout << "| 7. Boat           | Wood-35, Metal-20    |" << endl;

    // Check for blueprints and add additional craftable items
    if (game.check_gun_bullet_blueprint()) {
        cout << "| 8. Gun&bullet     | Metal-15             |" << endl;
    }
    if (game.check_signal_flare_blueprint()) {
        cout << "| 9. Signal Flare   | Metal-20             |" << endl;
    }
    if (game.check_armor_blueprint()) {
        cout << "| 10.Armor          | Metal-10, Leather-10 |" << endl;
    }
    cout << "+--------------------+---------------------+" << endl;

    cout << "Enter the number of the item you want to craft, or 0 to cancel: ";
    int choice;
    cin >> choice;

    if (choice == 0) {
        cout << "You decided not to craft anything." << endl;
        return;
    }

    // Using the game object to access the bag
    map<string, int>& bag = game.getBag();
    switch (choice) {
    case 1: // Campfire
        if (bag["wood"] >= 5) {
            bag["wood"] -= 5;
            bag["campfire"] += 1;
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
            bag["knife"] += 1;
            cout << "You crafted a knife! It has been added to your inventory." << endl;
        }
        else {
            cout << "You don't have enough resources to craft a knife. You need 3 wood and 3 metal." << endl;
        }
        break;

    case 3: // Upgraded Knife
        if (bag["wood"] >= 10 && bag["metal"] >= 10 && bag["knife"] >= 1) {
            bag["wood"] -= 10;
            bag["metal"] -= 10;
            bag["knife"] -= 1;
            bag["upgraded knife"] += 1;
            cout << "You upgraded your knife! It has been added to your inventory." << endl;
        }
        else {
            cout << "You cannot upgrade your knife. You need a knife, 10 wood and 10 metal." << endl;
        }
        break;

    case 4: // Shelter
        if (bag["wood"] >= 10 && bag["metal"] >= 4 && bag["shelter"] == 0) {
            bag["wood"] -= 10;
            bag["metal"] -= 4;
            bag["shelter"] += 1;
            cout << "You have created a shelter! It has been added to your inventory." << endl;
        }
        else {
            cout << "You already have a shelter or don't have enough resources to craft a shelter. You need 10 wood and 4 metal." << endl;
        }
        break;

    case 5: // Upgraded Shelter
        if (bag["wood"] >= 10 && bag["metal"] >= 6 && bag["shelter"] >= 1 && bag["upgraded shelter"] == 0) {
            bag["wood"] -= 10;
            bag["metal"] -= 6;
            bag["shelter"] -= 1;
            bag["upgraded shelter"] += 1;
            cout << "You have upgraded your shelter! It has been added to your inventory." << endl;
        }
        else {
            cout << "You cannot upgrade your shelter. You need a shelter, 10 wood and 6 metal." << endl;
        }
        break;

    case 6: // Fur Clothing
        if (bag["leather"] >= 10) {
            bag["leather"] -= 10;
            bag["fur clothing"] += 1;
            cout << "You crafted a fur clothing! It has been added to your inventory." << endl;
        }
        else {
            cout << "You don't have enough leather to craft a fur clothing. You need 10 leather." << endl;
        }
        break;

    case 7: // Boat
        if (bag["wood"] >= 35 && bag["metal"] >= 20) {
            bag["wood"] -= 35;
            bag["metal"] -= 20;
            bag["boat"] += 1;
            cout << "You crafted a boat! You can now attempt to escape the island!" << endl;
        }
        else {
            cout << "You don't have enough resources to craft a boat. You need 35 wood and 20 metal." << endl;
        }
        break;

    case 8: // Gun&bullet
        if (bag["metal"] >= 15 && game.check_gun_bullet_blueprint()) {
            bag["metal"] -= 15;
            bag["gun&bullet"] += 1;
            cout << "You crafted a gun&bullet" << endl;
        }
        else {
            cout << "You don't have enough metal to craft a gun&bullet. You need 15 metal and a gun&bullet blueprint." << endl;
        }
        break;

    case 9: // Signal Flare
        if (bag["metal"] >= 20 && game.check_signal_flare_blueprint()) {
            bag["metal"] -= 20;
            bag["signal flare"] += 1;
            cout << "You crafted a signal flare." << endl;
        }
        else {
            cout << "You don't have enough metal to craft a signal flare. You need 20 metal and a signal flare blueprint." << endl;
        }
        break;

    case 10: // Armor
        if (bag["metal"] >= 10 && bag["leather"] >= 10 && bag["fur clothing"] >= 1 && game.check_armor_blueprint()) {
            bag["metal"] -= 10;
            bag["leather"] -= 10;
            bag["fur clothing"] -= 1;
            bag["armor"] += 1;
            cout << "You crafted an armor." << endl;
        }
        else {
            cout << "You cannot craft an armor. You need 10 metal, 10 leather, a fur clothing, and an armor blueprint." << endl;
        }
        break;

    default:
        cout << "Invalid choice. Please select a valid item to craft." << endl;
        break;
    }

    // Display updated bag
    cout << "\nYour updated bag after crafting:\n";
    game.print_bag(); // Use the game object to call print_bag
}

// Rest to recover health and mental health
void rest(GameSetting& game) {
    cout << "You take a rest and regain some energy." << endl;

    // Increase health by 20 points
    game.setHP(min(100, game.getHP() + 20));
    // Increase mental health by 20 points
    game.setMental(min(100, game.getMental() + 20));

    cout << "HP restored by 20. New HP: " << game.getHP() << endl;
    cout << "Mental health restored by 20. New Mental Health: " << game.getMental() << endl;
}

// Hunt for food
void hunting(GameSetting& game) {
    // Seed the random number generator for hunting events
    srand(time(0));
    int hunt_event = rand() % 100; // Random number between 0 and 99

    cout << "You go hunting for food." << endl;

    if (hunt_event < 35) {
        // Bear attack event
        int damage = max(40 - (game.getBagItem("knife") * 10 + game.getBagItem("upgraded knife") * 30 + game.getBagItem("fur clothing") * 20 + game.getBagItem("gun&bullet") * 50 + game.getBagItem("armor") * 50), 0);
        game.setHP(max(0, game.getHP() - damage));
        game.addToBag("bear meat", 1); // Assume the player gets bear meat after the fight
        cout << "You encountered a bear and got into a fight! You lost " << damage << " HP." << endl;
    }
    else if (hunt_event < 70) {
        // Wolf attack event
        int damage = max(40 - (game.getBagItem("knife") * 10 + game.getBagItem("upgraded knife") * 30 + game.getBagItem("fur clothing") * 20 + game.getBagItem("gun&bullet") * 50 + game.getBagItem("armor") * 50), 0);
        game.setHP(max(0, game.getHP() - damage));
        game.addToBag("wolf meat", 1); // Assume the player gets wolf meat after the fight
        cout << "You encountered a wolf and got into a fight! You lost " << damage << " HP." << endl;
    }
    else {
        // No attack, peaceful hunting
        game.addToBag("beef", 1); // Add beef to the inventory
        game.addToBag("leather", 3); // Add leather to the inventory
        cout << "You went hunting and found some beef." << endl;
    }

    // Ensure HP does not drop below 0
    if (game.getHP() < 0) {
        game.setHP(0);
    }

    cout << "Your current HP after hunting: " << game.getHP() << endl;
}

// Attempt to escape the island
void attempt_escape(GameSetting& game) {
    // Check if the player has the necessary items to attempt an escape
    if (game.getBagItem("boat") > 0 || game.getBagItem("signal flare") > 0) {
        cout << "You have the necessary items to attempt an escape!" << endl;

        // Random chance of successful escape
        int escape_chance = rand() % 100; // Generate a random number between 0 and 99

        if (escape_chance < 70) { // 70% chance of successful escape
            cout << "Congratulations! You have successfully escaped the island!" << endl;
            exit(0); // End the game successfully
        }
        else {
            cout << "Your escape attempt failed. You will need to try again later." << endl;
            game.setHP(max(0, game.getHP() - 50)); // Penalize the player for the failed escape attempt
            cout << "You lost 50 HP during the failed escape attempt. Current HP: " << game.getHP() << endl;
        }
    }
    else {
        cout << "You do not have the necessary items to attempt an escape!" << endl;
    }
}

void nightEvent(GameSetting& game) {
    srand(time(0)); // Seed the random number generator for night events
    int night_ran = rand() % 101; // Generate a random number between 0 and 100

    cout << "*** Night is falling... ***" << endl;

    if (game.getBagItem("upgraded shelter") > 0) {
        cout << "Your upgraded shelter kept you safe and comfortable through the night." << endl;
    }
    else if (game.getBagItem("shelter") > 0) {
        if (night_ran >= 0 && night_ran <= 70) {
            cout << "Your shelter kept you safe, but it wasn't very comfortable." << endl;
        }
        else if (night_ran > 70 && night_ran <= 90) {
            game.wildAnimalAttack(); // Call the wild animal attack function
        }
        else if (night_ran > 90 && night_ran <= 100) {
            game.poor_sleeping_quality(); // Call the poor sleeping quality function
        }
    }
    else {
        if (night_ran >= 0 && night_ran <= 60) {
            cout << "You managed to survive the night without a shelter, but it was tough." << endl;
        }
        else if (night_ran > 60 && night_ran <= 80) {
            game.wildAnimalAttack(); // Call the wild animal attack function
        }
        else if (night_ran > 80 && night_ran <= 100) {
            game.poor_sleeping_quality(); // Call the poor sleeping quality function
        }
    }

    cout << "Your current HP: " << game.getHP() << " Hunger: " << game.getHunger() << " Mental: " << game.getMental() << endl;
    if (game.getHP() <= 0) {
        cout << "You didn't survive the night. Game Over!" << endl;
        exit(0);
    }
}

// Simulates a wild animal attack during the night or exploration
void wildAnimalAttack(GameSetting& game) {
    int shield = 0;
    shield += game.getBagItem("knife") * 10;
    shield += game.getBagItem("upgraded knife") * 30;
    shield += game.getBagItem("fur clothing") * 20;
    shield += game.getBagItem("gun&bullet") * 50;
    shield += game.getBagItem("armor") * 50;

    int damage = 40 - shield; // Calculate damage, considering the protective items
    damage = max(0, damage);  // Ensure damage is not negative

    game.setHP(max(0, game.getHP() - damage)); // Subtract damage from health
    cout << "A wild animal attacked you! You lost " << damage << " HP." << endl;
    cout << "Your remaining HP: " << game.getHP() << endl;

    // Check if the player has died from the attack
    if (game.getHP() <= 0) {
        cout << "You didn't survive the animal attack. Game Over!" << endl;
        exit(0);
    }
}

// Simulates the effect of poor sleeping quality on the player's mental health
void poor_sleeping_quality(GameSetting& game) {
    cout << "You had a restless night, and your mental health has suffered." << endl;

    // Decrease mental health by 15 points due to poor sleep
    game.setMental(max(0, game.getMental() - 15));

    cout << "Your mental health decreased by 15 points. Current mental health: " << game.getMental() << endl;

    // Check if the player's mental health has reached a critical level
    if (game.getMental() < 20) {
        cout << "Your mental health is getting dangerously low. You need to find ways to recover or your situation will become dire." << endl;
    }
}

