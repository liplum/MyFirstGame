//
// Created by Liplum on 4/23/2023.
//

#ifndef LEVELS_H
#define LEVELS_H

#include "entity.h"

const PlayerType playerLv2 = {
  .maxHp = 190.0f,
  .attack = 12.5f,
  .armor = 10.0f,
  .attackPower = 130,
  .level = 2,
};

const PlayerType playerLv3 = {
  .maxHp = 280.0f,
  .attack = 18.0f,
  .armor = 18.0f,
  .attackPower = 150,
  .level = 3,
};



EnemyType enemyRat = {
  .name = "Rat",
  .maxHp = 240.0f,
  .attack = 18.0f,
  .armor = 5.0f,
  .level = 2,
  .attackPower = 150,
};

EnemyType enemyGoblinMage = {
  .name = "Goblin Mage",
  .maxHp = 320.0f,
  .attack = 24.0f,
  .armor = 8.0f,
  .level = 3,
  .attackPower = 180,
};

#endif //LEVELS_H
