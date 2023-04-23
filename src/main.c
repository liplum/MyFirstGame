#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "entity.h"
#include "levels.h"

#define ATTACK  1
#define PARRY  2
#define Withdraw  3

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Progress
bool isGameOver = false;
int turn = 0, part = 1;

Player player;
Enemy curEnemy;

/// Return a random number between [0f,1f]
float randf() {
  return (float) rand() / (float) RAND_MAX;
}

/// Return a random number between [min,max]
float randfIn(float min, float max) {
  float range = max - min;
  return randf() * range + min;
}

float calcDamage(int aLv, float aAttack, float aPower, float bArmor) {
  float randomFactor = randfIn(0.85f, 1.0f);
  bArmor = bArmor > 1 ? bArmor : 1;
  float damageFactor = aAttack / bArmor;
  float attackerLvFactor = 2 * (float) aLv / 5 + 2;
  float damage = attackerLvFactor * aPower * damageFactor / 50;
  return damage * randomFactor;
}

float calcPlayerDamage(float power) {
  return calcDamage(player.type->level, player.attack, power, curEnemy.armor);
}

float calcEnemyDamage(float power) {
  return calcDamage(curEnemy.type->level, curEnemy.attack, power, player.armor);
}

void newTurnStart() {
  turn++;
#if !defined(__CLION__)
  clearScreen();
#endif
  printf("------------------------------------------------------------\n");
  printf("[Turn %d]\n\n", turn);
  printf("Your Hp is %d. The %s Hp is %d.\n", (int) player.curHp, curEnemy.type->name, (int) curEnemy.curHp);
}

int getChoice() {
  int choice;
  printf("Attack=1, Parry=2, Withdraw=3\n");
  printf("Your choice:");
  scanf("%d", &choice);
  return choice;
}

void warning() {
  printf("\a");
}

const float shieldBashMul = 2.0f;
const float shieldBashPenetrate = 0.5f;

int main(void) {
#ifndef __CLION__
  setvbuf(stdout, NULL, _IONBF, 0);
#endif
  srand((unsigned) time(NULL));
  clearScreen();
  printf("\t\t**********************\n");
  printf("\t\t* First Game v1.5.0  *\n");
  printf("\t\t**********************\n");
  printf("\t\t\t\tLast Change: 4/23/2023    by Liplum\n");
  part_slime:
  {
    player = createPlayer(&playerLv1);
    curEnemy = createEnemy(&enemySlime);
    part = 1;
    turn = 0;
    isGameOver = false;
    printf("Press Enter to start.");
    getchar();
    printf("You were found in a forest.");
    getchar();
    warning();
    printf("A slime is coming here...");
    getchar();
    printf("Start fighting!");
    getchar();

    printf("Your Hp is %d. Slime's is %d.", (int) player.curHp, (int) curEnemy.curHp);
    getchar();

    loop_slime:
    {
      newTurnStart();
      int choice = getChoice();
      printf("\n");
      switch (choice) {
        case ATTACK: {
          float playerCaused = calcPlayerDamage(player.type->attackPower);
          curEnemy.curHp -= playerCaused;
          float slimeCaused = calcEnemyDamage(curEnemy.type->attackPower);
          player.curHp -= slimeCaused;
          if (curEnemy.curHp > 0 && player.curHp > 0) { //Not yet killed
            printf("You slashed the enemy and cause %d damage!\n", (int) playerCaused);
            printf("Slime hit you and caused %d damage!\n", (int) slimeCaused);
            getchar();
            getchar();
            goto loop_slime;
          } else if (curEnemy.curHp <= 0) { //Killed
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("A critical strike is performed!\n");
            printf("Congratulations! You won the fight.\n");
            isGameOver = true;
            part += 1;
            goto end;
          } else { //Failed
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("You slashed the enemy and cause %d damage!\n", (int) playerCaused);
            printf("Slime rushed swiftly and consumed you!\n");
            getchar();
            getchar();
            goto die;
          }
        }
        case PARRY: {
          player.armor *= 2;
          float slimeCaused = calcEnemyDamage(curEnemy.type->attackPower);
          player.curHp -= slimeCaused;
          if (player.curHp > 0) {
            printf("You raised the shield and defended.\n");
            printf("Slime hit you and cause %d!\n", (int) slimeCaused);
            getchar();
            getchar();
            player.armor = player.type->armor;
            goto loop_slime;
          } else {
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("You raised the shield and tried to defend.\n");
            printf("But enemy countered your defense...\n");
            isGameOver = false;
            getchar();
            goto die;
          }
        }
        case Withdraw: {
          printf("Slime stuck your legs.\n");
          float slimeCaused = calcEnemyDamage(curEnemy.type->attackPower * 1.5f);
          player.curHp -= curEnemy.attack;
          if (player.curHp > 0) {
            printf("You were distracted and caught by slimes. You lost %d damage.\n", (int) slimeCaused);
            getchar();
            getchar();
            goto loop_slime;
          } else {
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("Slime caught you and consumed your body. How poor you are!\n");
            isGameOver = false;
            getchar();
            goto die;
          }
        }
        default: {
          turn--;
          goto loop_slime;
        }
      }
    }
  }

  part_rat:
  {
    player = createPlayer(&playerLv2);
    curEnemy = createEnemy(&enemyRat);
    part = 2;
    turn = 0;
    isGameOver = false;
    clearScreen();
    printf("Upgraded! Your level is %d now!\n", player.type->level);
    printf("You learnt a new skill \"Shield Bash\"!\n");
    printf(
      "Description: Parry twice in a row will charge your next attack with 200%% damage and penetrate 50%% armor.\n");
    clearScreen();
    getchar();
    getchar();
    warning();
    printf("A giant rat followed closely.");
    getchar();
    printf("You have to fight again!");
    getchar();

    printf("Your Hp is %d. Rat's is %d.", (int) player.curHp, (int) curEnemy.curHp);
    getchar();
    // Skill: Whenever rat attacks twice in a row,
    // the third attack will be a critical strike (this attack does not count as two consecutive attacks),
    // causing double attack.
    int playerSkill1Counter = 0;
    int ratSkillCounter = 0;
    loop_rat:
    {
      newTurnStart();
      int choice = getChoice();
      printf("\n");
      switch (choice) {
        case ATTACK: {
          float ratCaused;
          float playerCaused;
          int thisTurnRatSkill;
          int thisTurnPlayerSkill1;
          // Check the skill "Shield Bash"
          if (playerSkill1Counter >= 2) {// if trigger
            curEnemy.armor *= 1.0f - shieldBashPenetrate;
            playerCaused = calcPlayerDamage(player.type->attackPower * shieldBashMul);
            curEnemy.armor = curEnemy.type->armor;
            playerSkill1Counter = 0;
            thisTurnPlayerSkill1 = 1;
          } else { // if not trigger
            playerCaused = calcPlayerDamage(player.type->attackPower);
            playerSkill1Counter = 0;
            thisTurnPlayerSkill1 = 0;
          }
          curEnemy.curHp -= playerCaused;
          // Check rat's skill
          if (ratSkillCounter >= 2) { // if trigger
            ratCaused = calcEnemyDamage(curEnemy.type->attackPower * 2);
            ratSkillCounter = 0;
            thisTurnRatSkill = 1;
          } else { // if not trigger
            ratCaused = calcEnemyDamage(curEnemy.type->attackPower);
            ratSkillCounter += 1;
            thisTurnRatSkill = 0;
          }
          player.curHp -= ratCaused;
          if (curEnemy.curHp > 0 && player.curHp > 0) { //Not yet killed
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
            goto loop_rat;
          } else if (curEnemy.curHp <= 0) {  //Killed
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            if (thisTurnPlayerSkill1 == 1) {
              printf("Your skill \"Shield Bash\" is triggered.\n");
            }
            printf("You made a critical strike on the rat!\n");
            printf("Congratulations! You won the fight.\n");
            isGameOver = true;
            part += 1;
            getchar();
            goto end;
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
            isGameOver = false;
            getchar();
            goto die;
          }
        }
        case PARRY: {
          float ratCaused;
          player.armor *= 2;
          bool thisTurnRatSkill;
          // Check rat's skill
          if (ratSkillCounter >= 2) { // if trigger
            ratCaused = calcEnemyDamage(curEnemy.type->attackPower * 2);
            ratSkillCounter = 0;
            thisTurnRatSkill = true;
          } else { // if not trigger
            ratCaused = calcEnemyDamage(curEnemy.type->attackPower);
            ratSkillCounter += 1;
            thisTurnRatSkill = false;
          }
          player.curHp -= ratCaused;
          if (player.curHp > 0) {
            if (player.type->level == 2) {
              playerSkill1Counter += 1;
            }
            printf("You raised the shield and defended.\n");
            if (thisTurnRatSkill == 1) {
              printf("The giant rat has attacked twice in a row, and this time it is full of energy!\n");
            }
            printf("The giant Rat bit you heavily and caused %d damage.\n", (int) ratCaused);
            player.armor = player.type->armor;
            getchar();
            getchar();
            goto loop_rat;
          } else {
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("You raised the shield and tried to defend.\n");
            if (thisTurnRatSkill == 1) {
              printf("The giant rat has attacked twice in a row, and this time it is full of energy!\n");
            }
            printf("But giant rat countered your defense...\n");
            isGameOver = false;
            getchar();
            goto die;
          }
        }
        case Withdraw: {
          printf("The giant rat bit your shoulder. You can't not move!\n");
          float ratCaused = calcEnemyDamage(curEnemy.type->attackPower * 1.5f);
          player.curHp -= ratCaused;
          if (player.curHp > 0) {
            printf("You were controlled by a giant rat, and it bit at your neck causing %d damage!\n",
                   (int) ratCaused);
            getchar();
            getchar();
            goto loop_rat;
          } else {
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("You were held by the giant rat, and it bit off your neck!\n");
            getchar();
            isGameOver = false;
            goto die;
          }
        }
        default: {
          turn--;
          goto loop_rat;
        }
      }
    }
  }

  part_goblin:
  {
    player = createPlayer(&playerLv3);
    curEnemy = createEnemy(&enemyGoblinMage);
    part = 3;
    turn = 0;
    isGameOver = false;
    int goblinSkillCounter = 0;
    clearScreen();
    printf("Upgraded! Your level is %d now!\n", player.type->level);
    printf("You learnt a new skill \"Offense To Defense\"!\n");
    printf("Description: Attack three times in a row will charge your next parry to reduce 90%% damage.\n");
    getchar();
    clearScreen();
    getchar();
    printf("You continue to explore forward.");
    getchar();
    warning();
    printf("A goblin mage with a staff suddenly jumped out.");
    getchar();
    printf("You have no choice but keep fighting!");
    getchar();

    printf("Your Hp is %d. Goblin Mage Hp is %d.", (int) player.curHp, (int) curEnemy.curHp);
    getchar();
    // Skill 1:
    // Each round has a 20% chance to charge for two turns (it won't trigger itself during the charge),
    // and release a spell barrier that can resist 50% of oncoming attack,
    // deal 220% damage and break 50% of armor on the next attack.

    // Skill 2: TODO: Finish this skill
    // After being attacked for three times in a row,
    // the next time goblin are attacked,
    // 50% of the damage caused is reflected to the attacker,
    // and goblin will only take 50% of the damage.
    int shieldBashCounter = 0;
    int playerSkill2Counter = 0;
    const int goblinSkillTriggerChance = 4;
    const float goblinSkillDmgFactor = 3.5f;
    loop_goblin:
    {
      int GRand;
      newTurnStart();
      int choice = getChoice();
      printf("\n");
      switch (choice) {
        case ATTACK: {
          bool isShieldBashTriggered;
          float goblinCaused;
          float playerCaused;
          // Check the skill "Shield Bash"
          if (shieldBashCounter >= 2) { // if trigger
            curEnemy.armor *= 1.0f - shieldBashPenetrate;
            playerCaused = calcPlayerDamage(player.type->attackPower * shieldBashMul);
            curEnemy.armor = curEnemy.type->armor;
            isShieldBashTriggered = true;
          } else { // if not trigger
            playerCaused = calcPlayerDamage(player.type->attackPower);
            isShieldBashTriggered = false;
          }

          // Check goblin charging
          switch (goblinSkillCounter) {
            case 0: { // Goblin is not charging. roll to start charging
              GRand = rand() % goblinSkillTriggerChance;
              if (GRand == 0) { // Goblin starts charging
                goblinSkillCounter = 1;
                playerCaused *= 0.5f;
                curEnemy.curHp -= playerCaused;
              } else { // Goblin won't charge
                curEnemy.curHp -= playerCaused;
                goblinCaused = calcEnemyDamage(curEnemy.type->attackPower);
                player.curHp -= goblinCaused;
              }
            }
              break;
            case 1: { // Goblin is charging, already spent 1 turns
              playerCaused *= 0.5f;
              curEnemy.curHp -= playerCaused;
              goblinSkillCounter += 1;
            }
              break;
            case 2: { // Goblin has charged up
              curEnemy.curHp -= playerCaused;
              goblinCaused = calcEnemyDamage(curEnemy.type->attackPower * goblinSkillDmgFactor);
              player.curHp -= goblinCaused;
              goblinSkillCounter = 0;
            }
              break;
            default:
              break;
          }
          // Reset skill 1
          shieldBashCounter = 0;
          if (curEnemy.curHp > 0 && player.curHp > 0) { // Not yet killed
            if (player.type->level >= 3) {
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
            goto loop_goblin;
          } else if (curEnemy.curHp <= 0) { // Killed
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("You mustered up your courage and stabbed the goblin mage with a fatal blow\n");
            printf("Congratulations! You won the fight.\n");
            isGameOver = true;
            part += 1;
            getchar();
            goto win;
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
            isGameOver = false;
            getchar();
            goto die;
          }
        }
        case PARRY: {
          bool thisTurnPlayerSkill2;
          bool thisTurnGoblinSkill;
          player.armor *= 2;
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
                if (playerSkill2Counter >= 3 && player.type->level >= 3) { // if trigger
                  goblinCaused = calcEnemyDamage(curEnemy.type->attackPower) * 0.1f;
                  thisTurnPlayerSkill2 = true;
                } else { // if not trigger
                  goblinCaused = calcEnemyDamage(curEnemy.type->attackPower) * 0.1f;
                  thisTurnPlayerSkill2 = false;
                }
                player.curHp -= goblinCaused;
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
              goblinCaused = calcEnemyDamage(curEnemy.type->attackPower * goblinSkillDmgFactor);
              if (playerSkill2Counter >= 3) {
                goblinCaused *= 0.1f; // -90% damage
                thisTurnPlayerSkill2 = true;
              } else {
                thisTurnPlayerSkill2 = false;
              }
              player.curHp -= goblinCaused;
              goblinSkillCounter = 0;
              thisTurnGoblinSkill = true;
            }
              break;
            default:
              break;
          }
          playerSkill2Counter = 0;
          if (player.curHp > 0) { //Not failed
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
            player.armor = player.type->armor;
            getchar();
            getchar();
            goto loop_goblin;
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
            isGameOver = false;
            getchar();
            goto die;
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
                goblinCaused = calcEnemyDamage(curEnemy.type->attackPower * 1.5f);
                player.curHp -= goblinCaused;
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
              goblinCaused = calcEnemyDamage(curEnemy.type->attackPower * goblinSkillDmgFactor * 1.5f);
              player.curHp -= goblinCaused;
              goblinSkillCounter = 0;
              thisTurnGoblinSkill = true;
              break;
            }
            default:
              break;
          }
          if (player.curHp > 0) {
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
            goto loop_goblin;
          }
          if (player.curHp <= 0) {
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
            isGameOver = false;
            goto die;
          }
        }
        default: {
          turn--;
          goto loop_goblin;
        }
      }
    }
  }

  die:
  {
    printf("\nYou failed...\n");
  }

  end:
  {
    getchar();

    if (isGameOver == 1) {
      printf("You spent %d turns\n", turn);
      printf("Press Enter to continue...");
      getchar();
      switch (part) { // Goto part
        case 2:
          goto part_rat;
        case 3:
          goto part_goblin;
      }
    } else {
      // do nothing
    }
    clearScreen();
    printf("\t\t***********\n");
    printf("\t\t*Game Over*\n");
    printf("\t\t***********\n");
    return 0;
  }
  win:
  {
    getchar();
    printf("*----*------*------*------*------*------*------*------*------*-----*");
    printf("|              Congratulations! you passed the game.                |\n");
    printf("|       Thank you for playing, please wait for my next work! UwU    |\n");
    printf("*-----*------*------*------*------*------*------*------*------*-----*");
  }

  getchar();
  return 0;
}

#pragma clang diagnostic pop
