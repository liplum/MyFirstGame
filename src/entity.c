//
// Created by Liplum on 4/23/2023.
//

#include "entity.h"

Player createPlayer(const PlayerType *type) {
  return (Player) {
    .type = type,
    .curHp = type->maxHp,
    .attack = type->attack,
    .armor = type->armor,
  };
}


Enemy createEnemy(const EnemyType *type) {
  return (Enemy) {
    .type = type,
    .curHp = type->maxHp,
    .attack = type->attack,
    .armor = type->armor,
  };
}