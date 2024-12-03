#COMP2113 Group Project - Island Survival

Member Identification
  1. Chen Ni 3036267800
  2. Lai Wing Shing 3036233615
  3. Liang Wan Qing 3036260383
  4. Ngai Pui Chun 3036235924
  5. Wang Keni 3036267745

Application description

#Overview: The application is a text-based interactive survival game where players navigate the challenges of being stranded on a deserted island. Players manage health points (HP), hunger, and mental status while engaging in various activities to gather resources, craft items, and ultimately escape the island.

#Gameplaye Mechanics:
  1. Player Stats: Players start with 100 HP, 100 Hunger, and 100 Mental status. Engaging in actions impacts these stats.
  2. Daily Actions: Players can perform up to four actions each day, with options including exploring the island, cooking, crafting, resting, hunting, and attempting escape.
  3. Resource Management: Players collect resources such as wood, metal, and food through exploration and hunting. These resources are essential for crafting tools, preparing food, and constructing a boat for escape.
  4. Health Management: Players must monitor HP, hunger, and mental health. If the hunger or mental status drops below critical levels (20), HP will decrease each step teken. The game ends if HP reaches zero or drops below zero.

#Key Actions & Features:
  1. Exploration: Random evetns, such as animal attacks or discovering valuable blueprints, add unpredictability. Players can gather materials and ingredients during exploration.

    a. Probability of encountering a cave: 20% chance - given a choice of entering or not (70% chance of losing health; 90% chance of finding a blueprint; 10% chance of nothing happen)

    b. Probability of animal attack: 20% chance - causing 40 HP deduction

    c. Blueprint types: gun_bullet, signal_flare, armor

  2. Cooking: Players can prepare food to replenish the hunger bar. The player cannot cook without campfire and they can cook 2 dishes each time. (P.S. This choice will only appear once the player has crafted a campfire.)

  3. Eating:  Players can consume cooked food to recover the hunger bar or mental bar. This activity does not deduct hunger bar and is not counted as a move. (P.S. Eating directly from gathered ingredients may have negative effects on HP and mental status.)

  4. Crafting: Players can create tools, upgrade their shelter, and build a boat using collected materials. Crafting blueprints enhances gameplay strategy (Adding to HP)

  5. Resting: Players can gradually recover HP and mental health status.

  6. Hunting: Players can obtain ingredients for cooking that can significantly recover the hunger bar, but also carry a high risk of being attacked by wild animals such as bears, wolves (70% chance).

  7. Attempting Escape: Players can attempt to escape the island when a boat is crafted. But there is a probability of failed escape every day (70% chance of successful escape, otherwise 50 HP deduction)

  8. Random Night Events & Extreme Weather Conditions:

    a. Wild animal attack: 20% chance - damage depending on the shielding effect of tools owned

    b. Poor sleeping quality: 20% chance - causing 15 mental deduction

    c. Extreme rainfall: 10% chance - causing 15 Hunger deduction and 5 mental deduction

    d. Extreme Cold: 10% chance - causing 20 Hunger deduction and 5 mental deduction

    e. Extreme Hot: 10% chance - causing 15 Hunger deduction and 10 mental deduction

#Win Conditions:
  To win, players must:
  1. Collect 35 wood and 20 mental to construct a boat
  2. Acquire a blueprint for a signal flare and gather 20 metal to produce it.

Coding features and Requirement

  1. Generation of random events: Random number generator is used to control the probability of random events in the gameplay, including the generation of random night events, extreme weather conditions, the probability of collecting different materials and ingredients, as well as th possibility of finding and exploring a cave and successful island escape. The header files <cstdlib> and <ctime> are included to facilate this feature.
     
  2. Data structures for storing data: A map is used to store the the player's bag and a vector is used to store the blueprints. Everytime the player collect some materials, ingredients or blueprints, the corresponding items will be updated into the map and vector for furthur use. In addition, a pair is used to perform game stats (HP, Hunger & Mental) deduction after each step taken by the player. The corresponding deduction effects on three stats under different weather conditions and random events are stored in the pair. The header files <vector> <map> <utility> are used to facilitate these features.
  
  3. Dynamic memory management: A linked list is used to perform dynamic memory management. A blueprint list is created to store the blueprints that have not been found by the player. Everytime the player finds a blueprint, the blueprint-checking functions will reference to the linked list to check the type of the blueprint and delete from the linked list through linear searching. Besides, vectors are also used in our game for storing the bag items and the blueprints owned. Everytime the player collects some items, the new items will be added to the bag and the existing items will display an increment. The header files <vector> and <string> are used to facilitate these features.

  4. File input/output: A survival log is created from the first day of the game. In each day, the weather and activities will be inputed into the survival log. After each time of game-playing, the player can choose to check the outputed survival log for memory retrieval and achievement records. This can assist the player to improve their game performance and gain better game experience next time. The header file <fstream> and <sstream> are used to facilitate the feature.

  5. Program codes in multiple files: The program codes are stored in Gamesetting.cpp and Survival_log.cpp files separately. The former deals with the basic game setting while utilizing a class to declare all functions and variables to be used consistently throughout the game. It supports the features of random event generation, data structure storage, and dynamic memory management. The latter is in charge of creating, writing and reading the survival log that support the file input/output features. A Survival_log class is also created to declare all functions tobe used in producing the survival log.

Compilation and Execution Instructions

  1. Open a Linux OS in your computer and connect to the Linux server
  2. Enter the command: git clone https://github.com/RexChenNi/Survival-Game.git
  3. Check in SFTP to see if the repository has successfully cloned into your own directory
  4. Enter the command: cd Survival-game (changes the current directory to 2113)
  5. Enter the command: make

    g++ -c Main.cpp
    g++ -c GameSetting.cpp
    g++ -c Survival_log.cpp
    g++ -o main Main.o GameSetting.o Survival_log.o

  6. Compilation succeeds (shown above)
  7. Enter the command: ./main
  8. Once you see "Game initialized!", you can start playing based on the game instructions provided.
  9. Enjoy your game :)
