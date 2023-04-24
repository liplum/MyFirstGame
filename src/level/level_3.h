//
// Created by Liplum on 4/24/2023.
//

#include "../game.h"

#ifndef LEVEL_3_H
#define LEVEL_3_H

extern const PlayerType playerLv3;

extern const EnemyType enemyGoblinMage;

extern const float offense2DefenseResistance;

BattleResult goblinMageBattle();

void displayOffense2DefenseCounter(int counter);

#endif //LEVEL_3_H
