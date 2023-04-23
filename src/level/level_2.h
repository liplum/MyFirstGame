//
// Created by Liplum on 4/24/2023.
//

#ifndef LEVEL_2_H
#define LEVEL_2_H

#include "../game.h"

const PlayerType playerLv2 = {
  .maxHp = 190.0f,
  .attack = 12.5f,
  .armor = 10.0f,
  .attackPower = 130,
  .level = 2,
};

EnemyType enemyRat = {
  .name = "Rat",
  .maxHp = 240.0f,
  .attack = 18.0f,
  .armor = 5.0f,
  .level = 2,
  .attackPower = 150,
};

BattleResult giantRatBattle();

#endif //LEVEL_2_H
