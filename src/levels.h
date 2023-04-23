//
// Created by Liplum on 4/23/2023.
//

#ifndef LEVELS_H
#define LEVELS_H

#include "entity.h"

const PlayerType playerLv1 = (PlayerType) {
  .maxHp = 150.0f,
  .attack = 10.0f,
  .armor = 4.0f,
  .attackPower = 100,
  .level = 1,
};

const PlayerType playerLv2 = (PlayerType) {
  .maxHp = 150.0f,
  .attack = 10.0f,
  .armor = 4.0f,
  .attackPower = 100,
  .level = 2,
};

const PlayerType playerLv3 = (PlayerType) {
  .maxHp = 150.0f,
  .attack = 10.0f,
  .armor = 4.0f,
  .attackPower = 100,
  .level = 3,
};

const EnemyType enemySlime = (EnemyType) {
  .name = "Slime",
  .maxHp = 60.0f,
  .attack = 12.0f,
  .armor = 2.0f,
  .level = 1,
  .attackPower = 100,
};


EnemyType enemyRat = (EnemyType) {
  .name = "Rat",
  .maxHp = 85.0f,
  .attack = 17.0f,
  .armor = 1.0f,
  .level = 2,
  .attackPower = 150,
};

EnemyType enemyGoblinMage = (EnemyType) {
  .name = "Goblin Mage",
  .maxHp = 180.0f,
  .attack = 20.0f,
  .armor = 8,
  .level = 3,
  .attackPower = 120,
};

#endif //LEVELS_H
