//
// Created by Liplum on 4/24/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "console.h"
#include "calculate.h"

const float escapeChance = 0.01f;

void displaySeparatorLine() {
  printf("*------*------*------*------*------*-------*\n");
}

ActionType getActionChoice() {
  ActionType choice = 0;
  printf("Attack=1, Parry=2, Withdraw=3\n");
  while (choice != Attack && choice != Parry && choice != Withdraw) {
    printf("Your choice:");
    scanf("%d", &choice);
  }
  return choice;
}

// Create a health bar string based on the current and maximum health points
char *createHealthBar(float curHp, float maxHp, int barWidth) {
  // Calculate the percentage of remaining health points
  float percent = curHp / maxHp;

  // Calculate the number of characters to fill in the bar
  int numFilledChars = (int) (percent * (float) barWidth);
  numFilledChars = numFilledChars < 1 ? 1 : numFilledChars;

  // Allocate memory for the health bar string
  char *healthBar = (char *) malloc(sizeof(char) * (barWidth + 1));

  // Fill the health bar string with spaces
  memset(healthBar, ' ', barWidth);

  // Fill in the filled characters with '='
  for (int i = 0; i < numFilledChars; i++) {
    healthBar[i] = '=';
  }
  healthBar[numFilledChars - 1] = '>';
  // Add null terminator at the end
  healthBar[barWidth] = '\0';

  return healthBar;
}

const int healthBarWidth = 18;

void displayNewTurnBanner(Player *player, Enemy *enemy, int turn) {
#ifndef __CLION__
  clearScreen();
#endif
  displaySeparatorLine();
  printf("[Turn %d]\n", turn);
  printf("Your HP:\n");
  printf("\t|%s| %d.\n", createHealthBar(player->curHp, player->type->maxHp, healthBarWidth), (int) player->curHp);
  printf("%s HP:\n", enemy->type->name);
  printf("\t|%s| %d.\n", createHealthBar(enemy->curHp, enemy->type->maxHp, healthBarWidth), (int) enemy->curHp);
}

float calcDamage(int aLv, float aAttack, float aPower, float bArmor) {
  float randomFactor = randfIn(0.85f, 1.0f);
  bArmor = bArmor > 1 ? bArmor : 1;
  float damageFactor = aAttack / bArmor;
  float attackerLvFactor = 2 * (float) aLv / 5 + 2;
  float damage = attackerLvFactor * aPower * damageFactor / 50;
  return damage * randomFactor;
}
