//
// Created by Liplum on 4/24/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../game.h"
#include "level_2.h"
#include "../console.h"
#include "../calculate.h"

const PlayerType playerLv2 = {
  .maxHp = 190.0f,
  .attack = 12.5f,
  .armor = 10.0f,
  .attackPower = 130,
  .level = 2,
};

const EnemyType enemyRat = {
  .name = "Rat",
  .maxHp = 240.0f,
  .attack = 18.0f,
  .armor = 5.0f,
  .level = 2,
  .attackPower = 150,
};

const float shieldBashMul = 2.0f;
const float shieldBashPenetrate = 0.5f;

void displayShieldBashCounter(int counter) {
  printf("[Shield Bash | %d]\n", counter);
}

BattleResult giantRatBattle() {
  Player *player = createPlayer(&playerLv2);
  Enemy *enemy = createEnemy(&enemyRat);
  int turn = 0;
  clearScreen();
  printf("Upgraded! You are level %d now!\n", player->type->level);
  printf("You learnt a new skill \"Shield Bash\"!\n");
  printf(
    "Description: Parry twice in a row will charge your next attack with 200%% damage and penetrate 50%% armor.\n");
  getchar();
  alert();
  printf("A giant rat followed closely.");
  alert();
  getchar();
  printf("You have to fight again!");
  getchar();

  printf("Your HP is %d. Rat's is %d.", (int) player->curHp, (int) enemy->curHp);
  getchar();
  // Skill: Whenever rat attacks twice in a row,
  // the third Attack will be a critical strike (this Attack does not count as two consecutive attacks),
  // causing double Attack.
  int parryCounter = 0;
  int ratAttackCounter = 0;
  while (true) {
    turn++;
    displayNewTurnBanner(player, enemy, turn);
    displayShieldBashCounter(parryCounter);
    printf("\n");
    ActionType choice = getActionChoice();
    printf("\n");
    const int _ratAttackCounter = ratAttackCounter;
    const int _parryCounter = parryCounter;
    switch (choice) {
      case Attack: {
        // update counter
        parryCounter = 0;
        float ratCaused;
        float playerCaused;
        // Check the skill "Shield Bash"
        if (_parryCounter >= 2) {// if trigger
          enemy->armor *= 1.0f - shieldBashPenetrate;
          playerCaused = calcDamageFor(player, enemy, player->type->attackPower * shieldBashMul);
          enemy->armor = enemy->type->armor;
          parryCounter = 0;
        } else { // if not trigger
          playerCaused = calcDamageFor(player, enemy, player->type->attackPower);
          parryCounter = 0;
        }
        enemy->curHp -= playerCaused;
        // Check rat's skill
        if (ratAttackCounter >= 2) { // if trigger
          ratCaused = calcDamageFor(enemy, player, enemy->type->attackPower * 2);
          ratAttackCounter = 0;
        } else { // if not trigger
          ratCaused = calcDamageFor(enemy, player, enemy->type->attackPower);
          ratAttackCounter++;
        }
        player->curHp -= ratCaused;
        if (enemy->curHp <= 0) {  //Killed
          displaySeparatorLine();
          if (_parryCounter >= 2) {
            printf("Your skill \"Shield Bash\" is triggered.\n");
          }
          printf("You made a critical strike on the rat!\n");
          printf("Congratulations! You won the fight.\n");
          getchar();
          free(player);
          free(enemy);
          return BattleWin;
        }
        if (player->curHp <= 0) { //Failed
          displaySeparatorLine();
          if (_parryCounter >= 2) {
            printf("Your skill \"Shield Bash\" is triggered.\n");
          }
          printf("You hit the rat and cause %d damage.\n", (int) playerCaused);
          if (_parryCounter >= 2) {
            printf("The giant rat has attacked twice in a row, and this time it is full of energy!\n");
          }
          printf("The giant rat suddenly hit you with a fatal blow!\n");
          getchar();
          free(player);
          free(enemy);
          return BattleLoss;
        }
        //Not yet killed
        if (_parryCounter >= 2) {
          printf("Your skill \"Shield Bash\" is triggered.\n");
        }
        printf("You hit the rat and cause %d damage.\n", (int) playerCaused);
        if (_ratAttackCounter >= 2) {
          printf("The Giant rat has attacked twice in a row, and this time it is full of energy!\n");
        }
        printf("The Giant rat bit you heavily and caused %d damage.\n", (int) ratCaused);
        getchar();
        getchar();
        continue;
      }
      case Parry: {
        // update counter
        parryCounter += 1;
        float ratCaused;
        player->armor *= 2;
        // Check rat's skill
        if (_ratAttackCounter >= 2) { // if trigger
          ratCaused = calcDamageFor(enemy, player, enemy->type->attackPower * 2);
          ratAttackCounter = 0;
        } else { // if not trigger
          ratCaused = calcDamageFor(enemy, player, enemy->type->attackPower);
          ratAttackCounter++;
        }
        player->curHp -= ratCaused;
        if (player->curHp <= 0) {
          displaySeparatorLine();
          printf("You raised the shield and tried to defend.\n");
          if (_ratAttackCounter >= 2) {
            printf("The giant rat has attacked twice in a row, and this time it is full of energy!\n");
          }
          printf("But giant rat countered your defense...\n");
          getchar();
          free(player);
          free(enemy);
          return BattleLoss;
        }
        printf("You raised the shield and defended.\n");
        if (_ratAttackCounter >= 2) {
          printf("The giant rat has attacked twice in a row, and this time it is full of energy!\n");
        }
        printf("The giant Rat bit you heavily and caused %d damage.\n", (int) ratCaused);
        player->armor = player->type->armor;
        getchar();
        getchar();
        continue;
      }
      case Withdraw: {
        if (randf() <= escapeChance) {
          free(player);
          free(enemy);
          return BattleEscape;
        }
        // update counter
        parryCounter = 0;
        printf("The giant rat bit your shoulder. You can't not move!\n");
        float ratCaused = calcDamageFor(enemy, player, enemy->type->attackPower * 1.5f);
        player->curHp -= ratCaused;
        if (player->curHp <= 0) {
          displaySeparatorLine();
          printf("You were held by the giant rat, and it bit off your neck!\n");
          getchar();
          free(player);
          free(enemy);
          return BattleLoss;
        }
        printf("You were controlled by a giant rat, and it bit at your neck causing %d damage!\n",
               (int) ratCaused);
        getchar();
        getchar();
        continue;
      }
    }
  }
}

