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
  int goblinSkillCounter = 0;
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
  int playerSkill2Counter = 0;
  const int goblinSkillTriggerChance = 4;
  const float goblinSkillDmgFactor = 3.5f;
  while (true) {
    int GRand;
    turn++;
    displayNewTurnBanner(player, enemy, turn);
    ActionType choice = getActionChoice();
    printf("\n");
    switch (choice) {
      case Attack: {
        bool isShieldBashTriggered;
        float goblinCaused;
        float playerCaused;
        // Check the skill "Shield Bash"
        if (shieldBashCounter >= 2) { // if trigger
          enemy->armor *= 1.0f - shieldBashPenetrate;
          playerCaused = calcDamageFor(player, enemy, player->type->attackPower * shieldBashMul);
          enemy->armor = enemy->type->armor;
          isShieldBashTriggered = true;
        } else { // if not trigger
          playerCaused = calcDamageFor(player, enemy, player->type->attackPower);
          isShieldBashTriggered = false;
        }

        // Check goblin charging
        switch (goblinSkillCounter) {
          case 0: { // Goblin is not charging. roll to start charging
            GRand = rand() % goblinSkillTriggerChance;
            if (GRand == 0) { // Goblin starts charging
              goblinSkillCounter = 1;
              playerCaused *= 0.5f;
              enemy->curHp -= playerCaused;
            } else { // Goblin won't charge
              enemy->curHp -= playerCaused;
              goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower);
              player->curHp -= goblinCaused;
            }
          }
            break;
          case 1: { // Goblin is charging, already spent 1 turns
            playerCaused *= 0.5f;
            enemy->curHp -= playerCaused;
            goblinSkillCounter += 1;
          }
            break;
          case 2: { // Goblin has charged up
            enemy->curHp -= playerCaused;
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * goblinSkillDmgFactor);
            player->curHp -= goblinCaused;
            goblinSkillCounter = 0;
          }
            break;
          default:
            break;
        }
        // Reset skill 1
        shieldBashCounter = 0;
        if (enemy->curHp > 0 && player->curHp > 0) { // Not yet killed
          if (player->type->level >= 3) {
            playerSkill2Counter += 1;
          } // count the skill 2
          if (isShieldBashTriggered) {
            printf("Your skill \"Shield Bash\" is triggered.\n");
          }
          switch (goblinSkillCounter) {
            case 1:
              printf("The goblin mage is charging, and a magic barrier appears in front of them.\n");
              printf("You attacked the goblin mage, but the effect is weak, only caused %d damage.\n",
                     (int) playerCaused);
              break;
            case 2:
              printf("The goblin mage is still charging, and the magic barrier is about to burst.\n");
              printf("You attacked the goblin mage, but the effect is weak, only caused %d damage.\n",
                     (int) playerCaused);
              break;
            case 0:
              printf("You attacked the goblin mage and caused %d damage.\n",
                     (int) playerCaused);
              break;
            default:
              break;
          }
          if (goblinSkillCounter == 1) {
            printf(
              "The goblin mage has charged up and released pyroblast on you, inflicting a huge damage up to %d!\n",
              (int) goblinCaused);
          }
          if (goblinSkillCounter == 0) {
            printf("The goblin mage cast a fireball on you, dealing %d damage.\n", (int) goblinCaused);
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
          if (goblinSkillCounter == 1) {
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
        bool thisTurnPlayerSkill2;
        bool thisTurnGoblinSkill;
        player->armor *= 2;
        float goblinCaused;
        // Check goblin charging
        switch (goblinSkillCounter) {
          case 0: { // Goblin is not charging. roll to start charging
            GRand = rand() % goblinSkillTriggerChance;
            if (GRand == 0) {// Goblin starts charging
              goblinSkillCounter = 1;
              thisTurnGoblinSkill = false;
            } else { // Goblin won't charge
              // Check player skill "Offense To Defense"
              if (playerSkill2Counter >= 3 && player->type->level >= 3) { // if trigger
                goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower) * 0.1f;
                thisTurnPlayerSkill2 = true;
              } else { // if not trigger
                goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower) * 0.1f;
                thisTurnPlayerSkill2 = false;
              }
              player->curHp -= goblinCaused;
              thisTurnGoblinSkill = false;
            }
          }
            break;
          case 1: { // Goblin is charging, already spent 1 turn
            goblinSkillCounter += 1;
            thisTurnGoblinSkill = false;
          }
            break;
          case 2: { // Goblin has charged and prepare to release.
            // Check player skill "Offense To Defense"
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * goblinSkillDmgFactor);
            if (playerSkill2Counter >= 3) {
              goblinCaused *= 0.1f; // -90% damage
              thisTurnPlayerSkill2 = true;
            } else {
              thisTurnPlayerSkill2 = false;
            }
            player->curHp -= goblinCaused;
            goblinSkillCounter = 0;
            thisTurnGoblinSkill = true;
          }
            break;
          default:
            break;
        }
        playerSkill2Counter = 0;
        if (player->curHp > 0) { //Not failed
          shieldBashCounter += 1;
          if (thisTurnPlayerSkill2) {
            printf("Your skill \"Offense To Defense\" is triggered.\n");
          }
          printf("You raised the shield and defended.\n");
          switch (goblinSkillCounter) {
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
            default:
              break;
          }
          if (thisTurnGoblinSkill) {
            if (thisTurnPlayerSkill2) {
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
          if (thisTurnPlayerSkill2) {
            printf("Your skill \"Offense To Defense\" is triggered.\n");
          }
          printf("You raised the shield and defended.\n");
          if (thisTurnGoblinSkill && thisTurnPlayerSkill2) {
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
        bool thisTurnGoblinSkill;
        float goblinCaused;
        printf(
          "The goblin mage chanted a series of incantations, released a magic circle under your feet, and you were imprisoned!\n");

        // Check goblin charging
        switch (goblinSkillCounter) {
          case 0: {  // Goblin is not charging. roll to start charging
            GRand = rand() % goblinSkillTriggerChance;
            if (GRand == 0) { // Goblin starts charging
              goblinSkillCounter = 1;
              thisTurnGoblinSkill = false;
            } else { // Goblin won't charge
              goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * 1.5f);
              player->curHp -= goblinCaused;
              thisTurnGoblinSkill = true;
            }
            break;
          }
          case 1: { // Goblin is charging, already spent 1 turn
            goblinSkillCounter += 1;
            thisTurnGoblinSkill = false;
            break;
          }
          case 2: { // Goblin has charged and prepare to release.
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * goblinSkillDmgFactor * 1.5f);
            player->curHp -= goblinCaused;
            goblinSkillCounter = 0;
            thisTurnGoblinSkill = true;
            break;
          }
          default:
            break;
        }
        if (player->curHp > 0) {
          switch (goblinSkillCounter) {
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
            default:
              break;
          }
          if (thisTurnGoblinSkill) {
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
          if (thisTurnGoblinSkill) {
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
