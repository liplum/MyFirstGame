//
// Created by Liplum on 4/23/2023.
//

#include "entity.h"

Player createPlayer(const PlayerType *type) {
  return (Player) {
    .info = type,
    .curHp = type->maxHp,
    .attack = type->attack,
    .armor = type->armor,
  };
}


Enemy createEnemy(const EnemyType *type) {
  return (Enemy) {
    .info = type,
    .curHp = type->maxHp,
    .attack = type->attack,
    .armor = type->armor,
  };
}