//
// Created by Liplum on 4/23/2023.
//

#ifndef ENTITY_H
#define ENTITY_H

typedef struct {
  float maxHp;
  float attack;
  float armor;
  float attackPower;
  int level;
} PlayerType;

typedef struct {
  const PlayerType *info;
  float curHp;
  float attack;
  float armor;
} Player;

Player createPlayer(const PlayerType *type);

typedef struct {
  char *name;
  float maxHp;
  float attack;
  float armor;
  float attackPower;
  int level;
} EnemyType;

typedef struct {
  const EnemyType *info;
  float curHp;
  float attack;
  float armor;
} Enemy;

Enemy createEnemy(const EnemyType *type);

#endif //ENTITY_H
