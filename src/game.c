//
// Created by Liplum on 4/24/2023.
//

#include <stdio.h>
#include "game.h"
#include "console.h"
#include "calculate.h"

const float escapeChance = 0.01f;

ActionType getActionChoice() {
  ActionType choice = 0;
  printf("Attack=1, Parry=2, Withdraw=3\n");
  while (choice != Attack && choice != Parry && choice != Withdraw) {
    printf("Your choice:");
    scanf("%d", &choice);
  }
  return choice;
}

void displayNewTurnBanner(Player *player, Enemy *enemy, int turn) {
#if !defined(__CLION__)
  clearScreen();
#endif
  printf("------------------------------------------------------------\n");
  printf("[Turn %d]\n\n", turn);
  printf("Your Hp is %d. The %s Hp is %d.\n", (int) player->curHp, enemy->type->name, (int) enemy->curHp);
}

float calcDamage(int aLv, float aAttack, float aPower, float bArmor) {
  float randomFactor = randfIn(0.85f, 1.0f);
  bArmor = bArmor > 1 ? bArmor : 1;
  float damageFactor = aAttack / bArmor;
  float attackerLvFactor = 2 * (float) aLv / 5 + 2;
  float damage = attackerLvFactor * aPower * damageFactor / 50;
  return damage * randomFactor;
}