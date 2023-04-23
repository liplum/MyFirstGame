//
// Created by Liplum on 4/24/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include "../game.h"
#include "../console.h"
#include "level_1.h"

const PlayerType playerLv1 = {
  .maxHp = 130.0f,
  .attack = 10.0f,
  .armor = 4.0f,
  .attackPower = 100,
  .level = 1,
};

const EnemyType enemySlime = {
  .name = "Slime",
  .maxHp = 120.0f,
  .attack = 12.0f,
  .armor = 2.0f,
  .level = 1,
  .attackPower = 100,
};

BattleResult slimeBattle() {
  Player *player = createPlayer(&playerLv1);
  Enemy *enemy = createEnemy(&enemySlime);
  int turn = 0;
  printf("Press Enter to start.");
  getchar();
  printf("You were found in a forest.");
  getchar();
  alert();
  printf("A slime is coming here...");
  getchar();
  printf("Start fighting!");
  getchar();

  printf("Your Hp is %d. Slime's is %d.", (int) player->curHp, (int) enemy->curHp);
  getchar();

  while (true) {
    turn++;
    displayNewTurnBanner(player, enemy, turn);
    ActionType choice = getActionChoice();
    printf("\n");
    switch (choice) {
      case Attack: {
        float playerCaused = calcDamageFor(player, enemy, player->type->attackPower);
        enemy->curHp -= playerCaused;
        float slimeCaused = calcDamageFor(enemy, player, enemy->type->attackPower);
        player->curHp -= slimeCaused;
        if (enemy->curHp > 0 && player->curHp > 0) { //Not yet killed
          printf("You slashed the enemy and cause %d damage!\n", (int) playerCaused);
          printf("Slime hit you and caused %d damage!\n", (int) slimeCaused);
          getchar();
          getchar();
          continue;
        } else if (enemy->curHp <= 0) { //Killed
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          printf("A critical strike is performed!\n");
          printf("Congratulations! You won the fight.\n");
          return BattleWin;
        } else { //Failed
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          printf("You slashed the enemy and cause %d damage!\n", (int) playerCaused);
          printf("Slime rushed swiftly and consumed you!\n");
          getchar();
          getchar();
          return BattleLoss;
        }
      }
      case Parry: {
        player->armor *= 2;
        float slimeCaused = calcDamageFor(enemy, player, enemy->type->attackPower);
        player->curHp -= slimeCaused;
        if (player->curHp > 0) {
          printf("You raised the shield and defended.\n");
          printf("Slime hit you and cause %d!\n", (int) slimeCaused);
          getchar();
          getchar();
          player->armor = player->type->armor;
          continue;
        } else {
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          printf("You raised the shield and tried to defend.\n");
          printf("But enemy countered your defense...\n");
          getchar();
          return BattleLoss;
        }
      }
      case Withdraw: {
        printf("Slime stuck your legs.\n");
        float slimeCaused = calcDamageFor(enemy, player, enemy->type->attackPower * 1.5f);
        player->curHp -= enemy->attack;
        if (player->curHp > 0) {
          printf("You were distracted and caught by slimes. You lost %d damage.\n", (int) slimeCaused);
          getchar();
          getchar();
          continue;
        } else {
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          printf("Slime caught you and consumed your body. How poor you are!\n");
          getchar();
          return BattleLoss;
        }
      }
    }
  }
}
