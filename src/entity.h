//
// Created by Liplum on 4/23/2023.
//

#ifndef ENTITY_H
#define ENTITY_H

typedef struct {
  float curHp;
  float maxHp;
  float attack;
  float armor;
  int exp;
  int level;
} Player;

typedef struct {
  float hp;
  float attack;
  float armor;
} Upgrade;

typedef struct {
  char *name;
  float curHp;
  float attack;
  float armor;
  int level;
  int exp;
} Enemy;

#endif //ENTITY_H
