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
} PlayerType;

typedef struct {
  const PlayerType *type;
  int exp;
  int level;
} PlayerInfo;

typedef struct {
  PlayerInfo *info;
  float curHp;
  float attack;
  float armor;
} Player;

Player createPlayer(const PlayerInfo *info);

typedef struct {
  char *name;
  float attack;
  float maxHp;
  float armor;
  int level;
  int expRewards;
  float attackPower;
} EnemyType;

typedef struct {
  const EnemyType *info;
  float curHp;
  float attack;
  float armor;
} Enemy;

Enemy createEnemy(const EnemyType *info);

#endif //ENTITY_H
