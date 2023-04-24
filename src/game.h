//
// Created by Liplum on 4/24/2023.
//

#ifndef GAME_H
#define GAME_H

#include "entity.h"

typedef enum {
  BattleWin,
  BattleLoss,
  BattleEscape,
} BattleResult;

extern const float escapeChance;

typedef BattleResult (*BattleRunner)();

typedef enum {
  Attack = 1,
  Parry = 2,
  Withdraw = 3,
} ActionType;

ActionType getActionChoice();

void displayNewTurnBanner(Player *player, Enemy *enemy, int turn);

float calcDamage(int aLv, float aAttack, float aPower, float bArmor);

#define calcDamageFor(a, b, power) (calcDamage(a->type->level, a->attack, power, b->armor))

#endif //GAME_H
