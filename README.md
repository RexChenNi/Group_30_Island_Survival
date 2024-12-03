#COMP2113 Group Project - Island Survival

Member Identifications
#1 Chen Ni
#2 Liang Wanqing
#3 Wang Keni 3036267745
#4 Ian
#5 Vincent

Application description

#Overview: The application is an interactive survival game where players navigate the challenges of being stranded on a deserted island. Players manage health points (HP), hunger, and mental status while engaging in various activities to gather resources, craft items, and ultimately escape the island.

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

  2. Cooking: Players can prepare food to replenish the hunger bar. (The player cannot cook without campfire, player can cook 2 dishes in this step)

  3. Eating:  Players can consume cooked food to recover the hunger bar or mental bar. (do not consume hunger bar, do not count as a move) P.S. Eating directly from gathered ingredients may have negative effects on HP and mental status.

  4. Crafting: Players can create tools, upgrade their shelter, and build a boat using collected materials. Crafting blueprints enhances gameplay strategy (Adding to HP)

  5. Resting: Players can gradually recover HP and mental health points.

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

Coding features and Requirement:

