//
// Created by Liplum on 4/23/2023.
//

#ifndef LEVELS_H
#define LEVELS_H

#include "entity.h"

PlayerType playerType = (PlayerType) {
  .maxHp = 150.0f,
  .attack = 10.0f,
  .armor = 4.0f,
  .attackPower = 100,
};

EnemyType enemySlime = (EnemyType) {
  .name = "Slime",
  .maxHp = 60.0f,
  .attack = 12.0f,
  .armor = 2.0f,
  .expRewards = 200,
  .level = 1,
};


EnemyType enemyRat = (EnemyType) {
  .name = "Rat",
  .maxHp = 85.0f,
  .attack = 17.0f,
  .armor = 1.0f,
  .expRewards = 300,
  .level = 2,
};

EnemyType enemyGoblinMage = (EnemyType) {
  .name = "Goblin Mage",
  .maxHp = 180.0f,
  .attack = 20.0f,
  .armor = 8,
  .expRewards = 600,
  .level = 3,
};
#endif //LEVELS_H
