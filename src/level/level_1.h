//
// Created by Liplum on 4/24/2023.
//

#ifndef LEVEL_1_H
#define LEVEL_1_H

#include "../entity.h"

const PlayerType playerLv1 = {
  .maxHp = 130.0f,
  .attack = 10.0f,
  .armor = 4.0f,
  .attackPower = 100,
  .level = 1,
};

const EnemyType enemySlime = {
  .name = "Slime",
  .maxHp = 120.0f,
  .attack = 12.0f,
  .armor = 2.0f,
  .level = 1,
  .attackPower = 100,
};

BattleResult slimeBattle();

#endif //LEVEL_1_H
