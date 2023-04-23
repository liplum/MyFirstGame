//
// Created by Liplum on 4/24/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include "../game.h"
#include "level_2.h"
#include "../console.h"

BattleResult giantRatBattle() {
  Player *player = createPlayer(&playerLv2);
  Enemy *enemy = createEnemy(&enemyRat);
  int turn = 0;
  clearScreen();
  printf("Upgraded! Your level is %d now!\n", player->type->level);
  printf("You learnt a new skill \"Shield Bash\"!\n");
  printf(
    "Description: Parry twice in a row will charge your next Attack with 200%% damage and penetrate 50%% armor.\n");
  clearScreen();
  getchar();
  getchar();
  alert();
  printf("A giant rat followed closely.");
  getchar();
  printf("You have to fight again!");
  getchar();

  printf("Your Hp is %d. Rat's is %d.", (int) player->curHp, (int) enemy->curHp);
  getchar();
  // Skill: Whenever rat attacks twice in a row,
  // the third Attack will be a critical strike (this Attack does not count as two consecutive attacks),
  // causing double Attack.
  int playerSkill1Counter = 0;
  int ratSkillCounter = 0;
  while (true) {
    turn++;
    displayNewTurnBanner(player, enemy, turn);
    ActionType choice = getActionChoice();
    printf("\n");
    switch (choice) {
      case Attack: {
        float ratCaused;
        float playerCaused;
        int thisTurnRatSkill;
        int thisTurnPlayerSkill1;
        // Check the skill "Shield Bash"
        if (playerSkill1Counter >= 2) {// if trigger
          enemy->armor *= 1.0f - shieldBashPenetrate;
          playerCaused = calcDamageFor(player, enemy, player->type->attackPower * shieldBashMul);
          enemy->armor = enemy->type->armor;
          playerSkill1Counter = 0;
          thisTurnPlayerSkill1 = 1;
        } else { // if not trigger
          playerCaused = calcDamageFor(player, enemy, player->type->attackPower);
          playerSkill1Counter = 0;
          thisTurnPlayerSkill1 = 0;
        }
        enemy->curHp -= playerCaused;
        // Check rat's skill
        if (ratSkillCounter >= 2) { // if trigger
          ratCaused = calcDamageFor(enemy, player, enemy->type->attackPower * 2);
          ratSkillCounter = 0;
          thisTurnRatSkill = 1;
        } else { // if not trigger
          ratCaused = calcDamageFor(enemy, player, enemy->type->attackPower);
          ratSkillCounter += 1;
          thisTurnRatSkill = 0;
        }
        player->curHp -= ratCaused;
        if (enemy->curHp > 0 && player->curHp > 0) { //Not yet killed
          if (thisTurnPlayerSkill1 == 1) {
            printf("Your skill \"Shield Bash\" is triggered.\n");
          }
          printf("You hit the rat and cause %d damage.\n\n", (int) playerCaused);
          if (thisTurnRatSkill == 1) {
            printf("The Giant rat has attacked twice in a row, and this time it is full of energy!\n");
          }
          printf("The Giant rat bit you heavily and caused %d damage.\n", (int) ratCaused);
          getchar();
          getchar();
          continue;
        } else if (enemy->curHp <= 0) {  //Killed
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          if (thisTurnPlayerSkill1 == 1) {
            printf("Your skill \"Shield Bash\" is triggered.\n");
          }
          printf("You made a critical strike on the rat!\n");
          printf("Congratulations! You won the fight.\n");
          getchar();
          return BattleWin;
        } else { //Failed
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          if (thisTurnPlayerSkill1 == 1) {
            printf("Your skill \"Shield Bash\" is triggered.\n");
          }
          printf("You hit the rat and cause %d damage.\n", (int) playerCaused);
          if (thisTurnRatSkill == 1) {
            printf("The giant rat has attacked twice in a row, and this time it is full of energy!\n");
          }
          printf("The giant rat suddenly hit you with a fatal blow!\n");
          getchar();
          return BattleLoss;
        }
      }
      case Parry: {
        float ratCaused;
        player->armor *= 2;
        bool thisTurnRatSkill;
        // Check rat's skill
        if (ratSkillCounter >= 2) { // if trigger
          ratCaused = calcDamageFor(enemy, player, enemy->type->attackPower * 2);
          ratSkillCounter = 0;
          thisTurnRatSkill = true;
        } else { // if not trigger
          ratCaused = calcDamageFor(enemy, player, enemy->type->attackPower);
          ratSkillCounter += 1;
          thisTurnRatSkill = false;
        }
        player->curHp -= ratCaused;
        if (player->curHp > 0) {
          if (player->type->level == 2) {
            playerSkill1Counter += 1;
          }
          printf("You raised the shield and defended.\n");
          if (thisTurnRatSkill == 1) {
            printf("The giant rat has attacked twice in a row, and this time it is full of energy!\n");
          }
          printf("The giant Rat bit you heavily and caused %d damage.\n", (int) ratCaused);
          player->armor = player->type->armor;
          getchar();
          getchar();
          continue;
        } else {
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          printf("You raised the shield and tried to defend.\n");
          if (thisTurnRatSkill == 1) {
            printf("The giant rat has attacked twice in a row, and this time it is full of energy!\n");
          }
          printf("But giant rat countered your defense...\n");
          getchar();
          return BattleLoss;
        }
      }
      case Withdraw: {
        printf("The giant rat bit your shoulder. You can't not move!\n");
        float ratCaused = calcDamageFor(enemy, player, enemy->type->attackPower * 1.5f);
        player->curHp -= ratCaused;
        if (player->curHp > 0) {
          printf("You were controlled by a giant rat, and it bit at your neck causing %d damage!\n",
                 (int) ratCaused);
          getchar();
          getchar();
          continue;
        } else {
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          printf("You were held by the giant rat, and it bit off your neck!\n");
          getchar();
          return BattleLoss;
        }
      }
    }
  }
}