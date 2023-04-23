//
// Created by Liplum on 4/23/2023.
//

#include "entity.h"

Player createPlayer(PlayerInfo *info) {
  return (Player) {
    .info=info,
    .curHp = info->maxHp,
    .attack = info->attack,
    .armor = info->armor,
  };
}


Enemy createEnemy(EnemyInfo *info) {
  return (Enemy) {
    .info=info,
    .curHp = info->maxHp,
    .attack = info->attack,
    .armor = info->armor,
  };
}