//
// Created by Liplum on 4/24/2023.
//

#include "../game.h"

#ifndef LEVEL_3_H
#define LEVEL_3_H

const PlayerType playerLv3 = {
  .maxHp = 280.0f,
  .attack = 18.0f,
  .armor = 18.0f,
  .attackPower = 150,
  .level = 3,
};

const EnemyType enemyGoblinMage = {
  .name = "Goblin Mage",
  .maxHp = 320.0f,
  .attack = 24.0f,
  .armor = 8.0f,
  .level = 3,
  .attackPower = 180,
};

BattleResult goblinMageBattle();
#endif //LEVEL_3_H
