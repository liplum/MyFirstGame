//
// Created by Liplum on 4/24/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include "level_3.h"
#include "../console.h"
#include "level_2.h"
#include "../calculate.h"

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
const float offense2DefenseResistance = 0.5f;

void displayOffense2DefenseCounter(int counter) {
  printf("[Offense To Defense | %d]", counter);
}

BattleResult goblinMageBattle() {
  Player *player = createPlayer(&playerLv3);
  Enemy *enemy = createEnemy(&enemyGoblinMage);
  int turn = 0;
  clearScreen();
  printf("Upgraded! You are level %d now!\n", player->type->level);
  printf("You learnt a new skill \"Offense To Defense\"!\n");
  printf("Description: Attack three times in a row will charge your next parry to reduce 50%% damage.\n");
  getchar();
  printf("You continue to explore forward.");
  getchar();
  alert();
  printf("A goblin mage with a staff suddenly jumped out.");
  alert();
  getchar();
  printf("You have no choice but keep fighting!");
  getchar();

  printf("Your Hp is %d. Goblin Mage Hp is %d.", (int) player->curHp, (int) enemy->curHp);
  getchar();
  // Skill 1:
  // Each round has a 50% chance to charge for two turns (it won't trigger itself during the charge),
  // and release a magic barrier that can resist 50% of oncoming damage,
  // cast 500% power spell on the next attack when charging up.

  // Skill 2: TODO: Finish this skill
  // After being attacked for three times in a row,
  // the next time goblin are attacked,
  // 50% of the damage caused is reflected to the attacker,
  // and goblin will only take 50% of the damage.
  int parryCounter = 0;
  int attackCounter = 0;
  int goblinChargeCounter = -1;
  const float goblinSkillTriggerChance = 0.5f;
  const float goblinSkillDmgFactor = 5.0f;
  const float goblinBarrierResistance = 0.5f;
  while (true) {
    turn++;
    displayNewTurnBanner(player, enemy, turn);
    displayShieldBashCounter(parryCounter);
    displayOffense2DefenseCounter(attackCounter);
    printf("\n");
    ActionType choice = getActionChoice();
    printf("\n");
    const int _goblinChargeCounter = goblinChargeCounter;
    const int _parryCounter = parryCounter;
    const int _attackCounter = attackCounter;
    switch (choice) {
      case Attack: {
        // update counter
        parryCounter = 0;
        attackCounter += 1;
        float goblinCaused = 0.0f;
        float playerCaused;
        // Check the skill "Shield Bash"
        if (_parryCounter >= 2) { // if trigger
          enemy->armor *= 1.0f - shieldBashPenetrate;
          playerCaused = calcDamageFor(player, enemy, player->type->attackPower * shieldBashMul);
          enemy->armor = enemy->type->armor;
        } else { // if not trigger
          playerCaused = calcDamageFor(player, enemy, player->type->attackPower);
        }
        // Reset shield bash
        // Check goblin charging
        switch (_goblinChargeCounter) {
          case -1: {  // Goblin is not charging. roll to start charging next turn.
            if (randf() <= goblinSkillTriggerChance) {
              goblinChargeCounter = 0;
            }
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower);
          }
            break;
          case 0: { // Goblin is charging at 1st turn.
            playerCaused *= 1.0f - goblinBarrierResistance;
            goblinChargeCounter = 1;
          }
            break;
          case 1: { // Goblin is still charging at 2nd turn.
            playerCaused *= 1.0f - goblinBarrierResistance;
            goblinChargeCounter = 2;
          }
            break;
          case 2: { // Goblin has charged up
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * goblinSkillDmgFactor);
            goblinChargeCounter = -1;
          }
            break;
        }
        player->curHp -= goblinCaused;
        enemy->curHp -= playerCaused;
        parryCounter = 0;
        if (enemy->curHp <= 0) { // Killed
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          printf("You mustered up your courage and stabbed the goblin mage with a fatal blow.\n");
          printf("Congratulations! You won the fight.\n");
          getchar();
          return BattleWin;
        }
        if (player->curHp <= 0) { // Failed
          printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          printf("You hit the goblin and cause %d damage.\n",
                 (int) playerCaused);
          if (_goblinChargeCounter == 2) {
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
        // Not yet killed
        // count the offense to defense
        if (_parryCounter >= 2) {
          printf("Your skill \"Shield Bash\" is triggered.\n");
        }
        switch (_goblinChargeCounter) {
          case -1: {
            printf("You attacked the goblin mage and caused %d damage.\n",
                   (int) playerCaused);
            printf("The goblin mage cast a fireball on you, dealing %d damage.\n", (int) goblinCaused);
          }
            break;
          case 0: {
            printf("The goblin mage is charging, and a magic barrier appears in front of them.\n");
            printf("You attacked the goblin mage, but the effect is weak, only caused %d damage.\n",
                   (int) playerCaused);
          }
            break;
          case 1: {
            printf("The goblin mage is still charging, and the magic barrier is about to burst.\n");
            printf("You attacked the goblin mage, but the effect is weak, only caused %d damage.\n",
                   (int) playerCaused);
          }
            break;
          case 2: {
            printf("You hit the goblin and cause %d damage.\n",
                   (int) playerCaused);
            printf(
              "The goblin mage has charged up and released pyroblast upon you, inflicting a huge damage up to %d!\n",
              (int) goblinCaused);
          }
            break;
        }
        getchar();
        getchar();
        continue;
      }
      case Parry: {
        // update counter
        attackCounter = 0;
        parryCounter += 1;
        player->armor *= 2;
        float goblinCaused = 0.0f;
        // Check goblin charging
        switch (_goblinChargeCounter) {
          case -1: {
            if (randf() <= goblinSkillTriggerChance) {
              goblinChargeCounter = 0;
            }
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower);
          }
            break;
          case 0: { // Goblin is charging at 1st turn.
            goblinChargeCounter = 1;
          }
            break;
          case 1: { // Goblin is still charging at 2nd turn.
            goblinChargeCounter = 2;
          }
            break;
          case 2: { // Goblin has charged and prepare to release.
            // Check player skill "Offense To Defense"
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * goblinSkillDmgFactor);
            goblinChargeCounter = -1;
          }
            break;
        }
        if (_attackCounter >= 3) { // if trigger
          goblinCaused *= 1.0f - offense2DefenseResistance;
        }
        player->curHp -= goblinCaused;
        if (player->curHp <= 0) { // Failed
          printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          if (_attackCounter >= 3) {
            printf("Your skill \"Offense To Defense\" is triggered.\n");
          }
          printf("You raised the shield and defended.\n");
          if (_goblinChargeCounter == 2 && _attackCounter >= 3) {
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
        //Not failed
        if (_attackCounter >= 3) {
          printf("Your skill \"Offense To Defense\" is triggered.\n");
        }
        printf("You raised the shield and defended.\n");
        switch (_goblinChargeCounter) {
          case -1:
            printf("Goblin mage cast fireball on you, dealing %d damage.\n", (int) goblinCaused);
            break;
          case 0:
            printf("The goblin mage is charging, and a magic barrier appears in front of them.\n");
            break;
          case 1:
            printf("The goblin mage is still charging, and the magic barrier is about to burst.\n");
            break;
        }
        if (_goblinChargeCounter == 2) {
          if (_attackCounter >= 3) {
            printf(
              "The goblin released the pyroblast upon you, but blocked by your tough shield. You're damaged by only %d.\n",
              (int) goblinCaused);
          } else {
            printf("After the goblin mage has charged up, they released the pyroblast, dealing %d damage.\n",
                   (int) goblinCaused);
          }
        }
        player->armor = player->type->armor;
        getchar();
        getchar();
        continue;
      }
      case Withdraw: {
        if (randf() <= escapeChance) {
          return BattleEscape;
        }
        // update counter
        parryCounter = 0;
        attackCounter = 0;
        float goblinCaused = 0.0f;
        printf(
          "The goblin mage chanted a series of incantations, released a magic circle under your feet, and you were imprisoned!\n");

        // Check goblin charging
        switch (_goblinChargeCounter) {
          case -1: { // Goblin is not charging. roll to start charging
            if (randf() <= goblinSkillTriggerChance) {
              goblinChargeCounter = 0;
            }
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * 1.5);
          }
            break;
          case 0: { // Goblin is charging at 1st turn.
            goblinChargeCounter = 1;
          }
            break;
          case 1: { // Goblin is still charging at 2nd turn.
            goblinChargeCounter = 2;
          }
            break;
          case 2: { // Goblin has charged and prepare to release.
            goblinCaused = calcDamageFor(enemy, player, enemy->type->attackPower * goblinSkillDmgFactor * 1.5f);
            goblinChargeCounter = 0;
            break;
          }
        }
        player->curHp -= goblinCaused;
        if (player->curHp <= 0) {
          printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
          if (_goblinChargeCounter == 2) {
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
        switch (_goblinChargeCounter) {
          case -1:
            printf("Goblin mage cast fireball on you, dealing %d damage.\n",
                   (int) goblinCaused);
            break;
          case 0:
            printf("The goblin mage is charging, and a magic barrier appears in front of them.\n");
            break;
          case 1:
            printf("The goblin mage is still charging, and the magic barrier is about to burst.\n");
            break;
        }
        if (_goblinChargeCounter == 2) {
          printf(
            "When you turn your back on the goblin mage, he has charged up and cast pyroblast upon you, dealing %d damage.\n",
            (int) goblinCaused);
        } else {
          printf("It's an opportunity for goblin to cast fireball on you, dealing %d damage.\n",
                 (int) goblinCaused);
        }
        getchar();
        getchar();
        continue;
      }
    }
  }
}
