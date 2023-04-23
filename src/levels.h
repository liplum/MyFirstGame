//
// Created by Liplum on 4/23/2023.
//

#ifndef LEVELS_H
#define LEVELS_H

#include "entity.h"

PlayerInfo playerInfo = (PlayerInfo) {
  .maxHp = 150.0f,
  .attack = 10.0f,
  .armor = 4.0f,
  .level = 1,
  .exp = 0,
};

EnemyInfo enemySlime = (EnemyInfo) {
  .name = "Slime",
  .maxHp = 60.0f,
  .attack = 12.0f,
  .armor = 2.0f,
  .expRewards = 200,
  .level = 1,
};


EnemyInfo enemyRat = (EnemyInfo) {
  .name = "Rat",
  .maxHp = 85.0f,
  .attack = 17.0f,
  .armor = 1.0f,
  .expRewards = 300,
  .level = 2,
};

EnemyInfo enemyGoblinMage = (EnemyInfo) {
  .name = "Goblin Mage",
  .maxHp = 180.0f,
  .attack = 20.0f,
  .armor = 8,
  .expRewards = 600,
  .level = 3,
};
#endif //LEVELS_H
