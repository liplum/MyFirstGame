//
// Created by Liplum on 4/23/2023.
//

#include <malloc.h>
#include "entity.h"

Player *createPlayer(const PlayerType *type) {
  Player *p = malloc(sizeof(Player));
  p->type = type;
  p->curHp = type->maxHp;
  p->attack = type->attack;
  p->armor = type->armor;
  return p;
}

Enemy *createEnemy(const EnemyType *type) {
  Enemy *p = malloc(sizeof(Enemy));
  p->type = type;
  p->curHp = type->maxHp;
  p->attack = type->attack;
  p->armor = type->armor;
  return p;
}
