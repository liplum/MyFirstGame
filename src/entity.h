//
// Created by Liplum on 4/23/2023.
//

#ifndef ENTITY_H
#define ENTITY_H

typedef struct {
  float maxHp;
  float attack;
  float armor;
  int exp;
  int level;
} PlayerInfo;

typedef struct {
  PlayerInfo *info;
  float curHp;
  float attack;
  float armor;
} Player;

Player createPlayer(PlayerInfo *info);

typedef struct {
  float hp;
  float attack;
  float armor;
} Upgrade;

typedef struct {
  char *name;
  float attack;
  float maxHp;
  float armor;
  int level;
  int expRewards;
} EnemyInfo;

typedef struct {
  EnemyInfo *info;
  float curHp;
  float attack;
  float armor;
} Enemy;

Enemy createEnemy(EnemyInfo *info);

#endif //ENTITY_H
