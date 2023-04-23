//
// Created by Liplum on 4/23/2023.
//

#include "entity.h"

Player createPlayer(PlayerInfo *info) {
  float lv = (float) info->level;
  return (Player) {
    .info=info,
    .curHp = info->type->maxHp * (lv * 1.5f),
    .attack = info->type->attack * (lv * 1.22f),
    .armor = info->type->armor * (lv * 1.15f),
  };
}


Enemy createEnemy(EnemyType *info) {
  return (Enemy) {
    .info=info,
    .curHp = info->maxHp,
    .attack = info->attack,
    .armor = info->armor,
  };
}