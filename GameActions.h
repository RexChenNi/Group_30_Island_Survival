// GameActions.h
#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "GameSetting.h"

using namespace std;

void exploreIsland(GameSetting& game);
void cookFood(GameSetting& game);
void eatFood(GameSetting& game);
void craftItem(GameSetting& game);
void rest(GameSetting& game);
void hunting(GameSetting& game);
void attempt_escape(GameSetting& game);
void nightEvent(GameSetting& game);
void wildAnimalAttack(GameSetting& game);
void poor_sleeping_quality(GameSetting& game);

#endif // GAME_ACTIONS_H
