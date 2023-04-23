//
// Created by Liplum on 4/24/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "level_3.h"
#include "../console.h"
#include "level_2.h"

const PlayerType playerLv3 = {
  .maxHp = 280.0f,
  .attack = 18.0f,
  .armor = 18.0f,
  .attackPower = 150,
  .level = 3,
};

const EnemyType enemyGoblinMage = {
  .name = "Goblin Mage",
  .maxHp = 320.0f,
  .attack = 24.0f,
  .armor = 8.0f,
  .level = 3,
  .attackPower = 180,
};

BattleResult goblinMageBattle() {
  Player *player = createPlayer(&playerLv3);
  Enemy *enemy = createEnemy(&enemyGoblinMage);
  int turn = 0;
  clearScreen();
  printf("Upgraded! You are level %d now!\n", player->type->level);
  printf("You learnt a new skill \"Offense To Defense\"!\n");
  printf("Description: Attack three times in a row will charge your next Parry to reduce 90%% damage.\n");
  getchar();
  printf("You continue to explore forward.");
  getchar();
  alert();
  printf("A goblin mage with a staff suddenly jumped out.");
  getchar();
  printf("You have no choice but keep fighting!");
  getchar();

  printf("Your Hp is %d. Goblin Mage Hp is %d.", (int) player->curHp, (int) enemy->curHp);
  getchar();
  // Skill 1:
  // Each round has a 20% chance to charge for two turns (it won't trigger itself during the charge),
  // and release a spell barrier that can resist 50% of oncoming Attack,
  // deal 220% damage and break 50% of armor on the next Attack.

  // Skill 2: TODO: Finish this skill
  // After being attacked for three times in a row,
  // the next time goblin are attacked,
  // 50% of the damage caused is reflected to the attacker,
  // and goblin will only take 50% of the damage.
  int shieldBashCounter = 0;
  int o2dCounter = 0;
  int goblinSkillCounter = 0;
  const int goblinSkillTriggerChance = 4;
  const float goblinSkillDmgFactor = 3.5f;
  while (true) {
    int GRand;
    turn++;
    displayNewTurnBanner(player, enemy, turn);
    ActionType choice = getActionChoice();
    printf("\n");
    const int _goblinSkillCounter = goblinSkillCounter;
    const int _shieldBashCounter = shieldBashCounter;
    switch (choice) {
      case Attack: {
        float goblinCaused = 0.0f;
        float playerCaused;
        // Check the skill "Shield Bash"
        if (_shieldBashCounter >= 2) { // if trigger
          enemy->armor *= 1.0f - shieldBashPenetrate;
          playerCaused = calcDamageFor(player, enemy, player->type->attackPower * shieldBashMul);
          enemy->armor = enemy->type->armor;
        } else { // if not trigger
          playerCaused = calcDamageFor(player, enemy, player->type->attackPower);
        }
        // Reset shield bash
        shieldBashCounter = 0;
        // Check goblin charging
        switch (_goblinSkillCounter) {
          case 0: { // Goblin is not charging. roll to start charging
            GRand = rand() % goblinSkillTriggerChance;
            if (GRand == 0) { // Goblin starts charging
              goblinSkillCounter = 1;
              playerCaused *= 0.5f;
            } else { // Goblin won't charge
              goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower);
            }
          }
            break;
          case 1: { // Goblin is charging, already spent 1 turns
            playerCaused *= 0.5f;
            goblinSkillCounter = 2;
          }
            break;
          case 2: { // Goblin has charged up
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * goblinSkillDmgFactor);
            goblinSkillCounter = 0;
          }
            break;
        }
        player->curHp -= goblinCaused;
        enemy->curHp -= playerCaused;
        shieldBashCounter = 0;
        if (enemy->curHp > 0 && player->curHp > 0) { // Not yet killed
          // count the offense to defense
          o2dCounter += 1;
          if (_shieldBashCounter >= 2) {
            printf("Your skill \"Shield Bash\" is triggered.\n");
          }
          switch (_goblinSkillCounter) {
            case 0: {
              printf("You attacked the goblin mage and caused %d damage.\n",
                     (int) playerCaused);
              printf("The goblin mage cast a fireball on you, dealing %d damage.\n", (int) goblinCaused);
            }
              break;
            case 1: {
              printf("The goblin mage is charging, and a magic barrier appears in front of them.\n");
              printf("You attacked the goblin mage, but the effect is weak, only caused %d damage.\n",
                     (int) playerCaused);
            }
              break;
            case 2: {
              printf("The goblin mage is still charging, and the magic barrier is about to burst.\n");
              printf("You attacked the goblin mage, but the effect is weak, only caused %d damage.\n",
                     (int) playerCaused);
              printf(
                "The goblin mage has charged up and released pyroblast on you, inflicting a huge damage up to %d!\n",
                (int) goblinCaused);
            }
              break;
          }
          getchar();
          getchar();
          continue;
        } else if (enemy->curHp <= 0) { // Killed
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          printf("You mustered up your courage and stabbed the goblin mage with a fatal blow\n");
          printf("Congratulations! You won the fight.\n");
          getchar();
          return BattleWin;
        } else { // Failed
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          printf("You hit the goblin and cause %d damage.\n",
                 (int) playerCaused);
          if (_goblinSkillCounter == 1) {
            printf(
              "After the goblin mage has charged up, they released the pyroblast, dealing %d damage.\n",
              (int) goblinCaused);
            printf("You exploded in this havoc!\n");
          } else {
            printf(
              "The goblin released the dragon flame.\n");
            printf("You can't resist such terrifying power at all and evaporated in the flame...\n");
          }
          getchar();
          return BattleLoss;
        }
      }
      case Parry: {
        player->armor *= 2;
        float goblinCaused;
        int _o2dCounter = o2dCounter;
        // Check goblin charging
        switch (_goblinSkillCounter) {
          case 0: { // Goblin is not charging. roll to start charging
            GRand = rand() % goblinSkillTriggerChance;
            if (GRand == 0) {// Goblin starts charging
              goblinSkillCounter = 1;
            } else { // Goblin won't charge
              // Check player skill "Offense To Defense"
              if (_o2dCounter >= 3 && player->type->level >= 3) { // if trigger
                goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower) * 0.1f;
              } else { // if not trigger
                goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower);
              }
              player->curHp -= goblinCaused;
            }
          }
            break;
          case 1: { // Goblin is charging, already spent 1 turn
            goblinSkillCounter = 2;
          }
            break;
          case 2: { // Goblin has charged and prepare to release.
            // Check player skill "Offense To Defense"
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * goblinSkillDmgFactor);
            if (_o2dCounter >= 3) {
              goblinCaused *= 0.1f; // -90% damage
            }
            player->curHp -= goblinCaused;
            goblinSkillCounter = 0;
          }
            break;
        }
        o2dCounter = 0;
        if (player->curHp > 0) { //Not failed
          shieldBashCounter += 1;
          if (_o2dCounter >= 3) {
            printf("Your skill \"Offense To Defense\" is triggered.\n");
          }
          printf("You raised the shield and defended.\n");
          switch (_goblinSkillCounter) {
            case 1:
              printf("The goblin mage is charging, and a magic barrier appears in front of them.\n");
              break;
            case 2:
              printf("The goblin mage is still charging, and the magic barrier is about to burst.\n");
              break;
            case 0:
              printf("Goblin mage cast fireball on you, dealing %d damage.\n",
                     (int) goblinCaused);
              break;
          }
          if (_goblinSkillCounter == 2) {
            if (_o2dCounter >= 3) {
              printf("The goblin released released the pyroblast on you, but blocked by your tough shield.\n");
            } else {
              printf("After the goblin mage has charged up, they released the pyroblast, dealing %d damage.\n",
                     (int) goblinCaused);
            }
          }
          player->armor = player->type->armor;
          getchar();
          getchar();
          continue;
        } else { // Failed
          printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          if (_o2dCounter >= 3) {
            printf("Your skill \"Offense To Defense\" is triggered.\n");
          }
          printf("You raised the shield and defended.\n");
          if (_goblinSkillCounter == 2 && _o2dCounter >= 3) {
            printf("The goblin mage has charged up and released pyroblast on you, dealing %d damage.\n",
                   (int) goblinCaused);
            printf("Your shield was burned and melted, and you were also wiped out in the flames...\n");
          } else {
            printf("The goblin mage cast dragon flames on you, dealing %d damage.\n",
                   (int) goblinCaused);
            printf("You couldn't resist such a powerful spell at all. You were wiped out in the flames...\n");
          }
          getchar();
          return BattleLoss;
        }
      }
      case Withdraw: {
        float goblinCaused;
        printf(
          "The goblin mage chanted a series of incantations, released a magic circle under your feet, and you were imprisoned!\n");

        // Check goblin charging
        switch (_goblinSkillCounter) {
          case 0: {  // Goblin is not charging. roll to start charging
            GRand = rand() % goblinSkillTriggerChance;
            if (GRand == 0) { // Goblin starts charging
              goblinSkillCounter = 1;
            } else { // Goblin won't charge
              goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * 1.5f);
              player->curHp -= goblinCaused;
            }
            break;
          }
          case 1: { // Goblin is charging, already spent 1 turn
            goblinSkillCounter = 2;
            break;
          }
          case 2: { // Goblin has charged and prepare to release.
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * goblinSkillDmgFactor * 1.5f);
            player->curHp -= goblinCaused;
            goblinSkillCounter = 0;
            break;
          }
        }
        if (player->curHp > 0) {
          switch (_goblinSkillCounter) {
            case 1:
              printf("The goblin mage is charging, and a magic barrier appears in front of them.\n");
              break;
            case 2:
              printf("The goblin mage is still charging, and the magic barrier is about to burst.\n");
              break;
            case 0:
              printf("Goblin mage cast fireball on you, dealing %d damage.\n",
                     (int) goblinCaused);
              break;
          }
          if (_goblinSkillCounter == 2) {
            printf("The goblin mage has charged up and cast pyroblast on you, dealing %d damage.\n",
                   (int) goblinCaused);
          } else {
            printf("It's an opportunity for goblin to cast fireball on you, dealing %d damage.\n",
                   (int) goblinCaused);
          }
          getchar();
          getchar();
          continue;
        }
        if (player->curHp <= 0) {
          printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          if (_goblinSkillCounter == 2) {
            printf("After the goblin mage has charged up, they cast the pyroblast, dealing %d damage.\n",
                   (int) goblinCaused);
            printf("You exploded in this havoc!\n");
          } else {
            printf("The goblin released the dragon flame, dealing %d damage.\n",
                   (int) goblinCaused);
            printf("You can't resist such terrifying power at all and evaporated in the flame...\n");
          }
          getchar();
          return BattleLoss;
        }
      }
    }
  }
}
