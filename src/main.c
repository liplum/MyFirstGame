#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ATTACK  1
#define PARRY  2
#define Withdraw  3

struct Player {
  int curHp;
  int maxHp;
  int damage;
  int armor;
  int exp;
  int level;
};
struct Upgrade {
  int hp;
  int damage;
  int armor;
};
struct Enemy {
  char *name;
  int curHp;
  int damage;
  int armor;
  int exp;
};

struct Upgrade createUpgrade(int hp, int dmg, int armor) {
  return (struct Upgrade) {.hp = hp, .damage=dmg, .armor=armor};
}

int waving(int value);

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Progress
int ending = 0, turn = 0, part = 1;


struct Player player;

float randomness = 0.1f;
struct Enemy curEnemy;

void playerAttributesUpgrade(struct Upgrade upgrade) {
  printf("\nYour max HP+%d, damage+%d, armor+%d.\n\n", upgrade.hp, upgrade.damage, upgrade.armor);
  player.maxHp += upgrade.hp;
  player.damage += upgrade.damage;
  player.armor += upgrade.armor;
}

void playerRestoreAttributes() {
  player.curHp = player.maxHp;
}

void newTurnStart() {
  turn++;
  clearScreen();
  printf("------------------------------------------------------------");
  printf("\n[Turn %d]\n\n", turn);
  printf("Your Hp is %d. The %s Hp is %d.\n", player.curHp, curEnemy.name, curEnemy.curHp);
}

void getChoice(int* choice){
  printf("Attack=1, Parry=2, Withdraw=3\n");
  printf("Your choice:");
  scanf("%d", choice);
}

void warning() {
  printf("\a");
}

int main(void) {
  srand((unsigned) time(NULL));
  player = (struct Player) {
    .maxHp = waving(150),
    .damage =waving(10),
    .armor=4,
    .level=1,
    .exp=0
  };
  clearScreen();
  printf("                ********************\n");
  printf("                * First Game V 1.4 *\n");
  printf("                ********************       Last Change: 10/30/202    by Liplum\n");
  part_slime:
  {
    part = 1;
    playerRestoreAttributes();
    turn = 0;
    ending = 0;
    printf("Press Enter to start.\n");
    getchar();
    curEnemy = (struct Enemy) {
      .name = "Slime",
      .curHp = waving(50),
      .damage = waving(12),
      .armor = 0,
      .exp = waving(200)
    };
    printf("You were found in a forest.\n");
    getchar();
    warning();
    printf("A slime is coming here... \n");
    getchar();
    printf("Start fighting!\n");
    getchar();

    printf("Your Hp is %d. Slime's is %d.\n", player.curHp, curEnemy.curHp);
    getchar();

    loop_slime:
    {
      int actionChoice;
      int playerCaused;
      int slimeCaused;
      newTurnStart();
      getChoice(&actionChoice);
      printf("\n");
      switch (actionChoice) {
        case ATTACK: {
          playerCaused = waving(player.damage);
          curEnemy.curHp -= playerCaused;
          slimeCaused = waving(curEnemy.damage) - player.armor;
          player.curHp -= slimeCaused;
          if (curEnemy.curHp > 0 && player.curHp > 0) { //Not yet killed
            printf("\nYou slashed the enemy and cause %d damage!\n\n", playerCaused);
            printf("\nSlime hit you and caused %d damage!", slimeCaused);
            getchar();
            getchar();
            goto loop_slime;
          } else if (curEnemy.curHp <= 0) { //Killed
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("\nA critical strike is performed!\n\n");
            printf("Congratulations! You won the fight.\n\n");
            ending = 1;
            part += 1;
            goto end;
          } else { //Failed
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("\nYou slashed the enemy and cause %d damage!\n\n", playerCaused);
            printf("\nSlime rushed swiftly and consumed you!\n\n");
            getchar();
            getchar();
            goto die;
          }
        }
          break;
        case PARRY: {
          slimeCaused = waving(curEnemy.damage) - player.armor * 2;
          player.curHp -= slimeCaused;
          if (player.curHp > 0) {
            printf("\nYou raised the shield and defended.\n");
            printf("\nSlime hit you and cause %d!\n\n", slimeCaused);
            getchar();
            getchar();
            goto loop_slime;
          } else {
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("\nYou raised the shield and tried to defend.\n");
            printf("\nBut enemy countered your defense...\n\n");
            ending = 0;
            goto die;
          }
        }
          break;
        case Withdraw: {
          printf("\nSlime stuck your legs.\n");
          slimeCaused = waving(curEnemy.damage);
          player.curHp -= curEnemy.damage;
          if (player.curHp > 0) {
            printf("\nYou were distracted and caught by slimes. You lost %d damage.\n\n", slimeCaused);
            getchar();
            getchar();
            goto loop_slime;
          } else {
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("\nSlime caught you and consumed your body. How poor you are!\n\n");
            ending = 0;
            goto die;
          }
        }
          break;
        default: {
          turn--;
          goto loop_slime;
        }
      }
    }
  }

  part_rat:
  {
    part = 2;
    turn = 0;
    ending = 0;
    curEnemy = (struct Enemy) {
      .name = "Rat",
      .curHp = waving(85),
      .damage = waving(17),
      .armor = 1,
      .exp = waving(300)
    };
    clearScreen();
    if (player.exp >= 100 && player.level == 1) {
      player.level += 1;
      player.exp -= 100;
      printf("\nUpgraded! Your level is %d now!\n", player.level);
      getchar();
      playerAttributesUpgrade(createUpgrade(80, 6, 8));
      getchar();
      printf("\nYou learnt a new skill \"Shield Bash\"!\n");
      printf(
        "Description: Parry twice in a row will charge your next attack with 300%% damage and pass through armor.\n");
    }
    clearScreen();
    playerRestoreAttributes();
    getchar();
    warning();
    printf("A giant rat followed closely.\n");
    getchar();
    printf("You have to fight again!\n");
    getchar();

    printf("Your Hp is %d. Rat's is %d.\n", player.curHp, curEnemy.curHp);
    getchar();
    // Skill: Whenever rat attacks twice in a row,
    // the third attack will be a critical strike (this attack does not count as two consecutive attacks),
    // causing double damage.
    int playerSkill1Counter = 0;
    int ratSkillCounter = 0;
    loop_rat:
    {
      int actionChoice;
      int ratCaused;
      int playerCaused;
      int thisTurnRatSkill;
      int thisTurnPlayerSkill1;
      newTurnStart();
      getChoice(&actionChoice);
      printf("\n");
      switch (actionChoice) {
        case ATTACK: {
          // Check the skill "Shield Bash"
          if (playerSkill1Counter >= 2 && player.level == 2) {// if trigger
            playerCaused = waving(player.damage) * 3;
            curEnemy.curHp -= playerCaused;
            playerSkill1Counter = 0;
            thisTurnPlayerSkill1 = 1;
          } else {
            playerCaused = waving(player.damage) - curEnemy.armor;
            curEnemy.curHp -= playerCaused;
            playerSkill1Counter = 0;
            thisTurnPlayerSkill1 = 0;
          }
          // Check rat's skill
          if (ratSkillCounter >= 2) { // if trigger
            ratCaused = waving(curEnemy.damage) * 2;
            ratCaused -= player.armor;
            player.curHp -= ratCaused;
            ratSkillCounter = 0;
            thisTurnRatSkill = 1;
          } else {
            ratCaused = waving(curEnemy.damage) - player.armor;
            player.curHp -= ratCaused;
            ratSkillCounter += 1;
            thisTurnRatSkill = 0;
          }
          if (curEnemy.curHp > 0 && player.curHp > 0) { //Not yet killed
            if (thisTurnPlayerSkill1 == 1) {
              printf("Your skill \"Shield Bash\" is triggered.\n");
            }
            printf("\nYou hit the rat and cause %d damage.\n\n", playerCaused);
            if (thisTurnRatSkill == 1) {
              printf("The Giant rat has attacked twice in a row, and this time it is full of energy!\n\n");
            }
            printf("The Giant rat bit you heavily and caused %d damage.\n\n", ratCaused);
            getchar();
            getchar();
            goto loop_rat;
          } else if (curEnemy.curHp <= 0) {  //Killed
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            if (thisTurnPlayerSkill1 == 1) {
              printf("Your skill \"Shield Bash\" is triggered.\n");
            }
            printf("\nYou made a critical strike on the rat!\n\n");
            printf("Congratulations! You won the fight.\n\n");
            ending = 1;
            part += 1;
            goto end;
          } else { //Failed
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            if (thisTurnPlayerSkill1 == 1) {
              printf("Your skill \"Shield Bash\" is triggered.\n");
            }
            printf("\nYou hit the rat and cause %d damage.\n\n", playerCaused);
            if (thisTurnRatSkill == 1) {
              printf("The giant rat has attacked twice in a row, and this time it is full of energy!\n\n");
            }
            printf("\nThe giant rat suddenly hit you with a fatal blow!\n\n");
            ending = 0;
            getchar();
            getchar();
            goto die;
          }
        }
          break;
        case PARRY: {
          // Check rat's skill
          if (ratSkillCounter >= 2) {
            ratCaused = waving(curEnemy.damage) * 2;
            ratCaused = ratCaused - player.armor * 2;
            player.curHp -= ratCaused;
            ratSkillCounter = 0;
            thisTurnRatSkill = 1;
          } else {
            ratCaused = waving(curEnemy.damage) - player.armor * 2;
            player.curHp -= ratCaused;
            ratSkillCounter += 1;
            thisTurnRatSkill = 0;
          }
          if (player.curHp > 0) {
            if (player.level == 2) {
              playerSkill1Counter += 1;
            }
            printf("\nYou raised the shield and defended.\n");
            if (thisTurnRatSkill == 1) {
              printf("The giant rat has attacked twice in a row, and this time it is full of energy!\n\n");
            }
            printf("The giant Rat bit you heavily and caused %d damage.\n\n", ratCaused);
            getchar();
            getchar();
            goto loop_rat;
          } else {
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("\nYou raised the shield and tried to defend.\n");
            if (thisTurnRatSkill == 1) {
              printf("The giant rat has attacked twice in a row, and this time it is full of energy!\n\n");
            }
            printf("\nBut giant rat countered your defense...\n\n");
            ending = 0;
            getchar();
            getchar();
            goto die;
          }
        }
          break;
        case Withdraw: {
          printf("\nThe giant rat bit your shoulder. You can't not move!\n");
          ratCaused = waving(curEnemy.damage) * 1.5f;
          player.curHp -= ratCaused;
          if (player.curHp > 0) {
            printf("\nYou were controlled by a giant rat, and it bit at your neck causing %d damage!\n\n",
                   ratCaused);
            getchar();
            getchar();
            goto loop_rat;
          } else {
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("\nYou were held by the giant rat, and it bit off your neck!\n\n");
            getchar();
            getchar();
            ending = 0;
            goto die;
          }
        }
          break;
        default: {
          turn--;
          goto loop_rat;
        }
          break;
      }
    }
  }

  part_goblin:
  {
    curEnemy = (struct Enemy) {
      .name = "Goblin Mage",
      .curHp = waving(180),
      .damage = waving(20),
      .armor = 8,
      .exp = waving(600)
    };
    part = 3;
    turn = 0;
    ending = 0;
    int gSkillCounter = 0;
    clearScreen();
    if (player.exp >= 300 && player.level == 2) {
      player.level += 1;
      player.exp -= 300;
      printf("\nUpgraded! Your level is %d now!\n", player.level);
      getchar();
      playerAttributesUpgrade(createUpgrade(150, 10, 10));
      getchar();
      printf("\nYou learnt a new skill \"Offense To Defense\"!\n");
      printf(
        "Description: Attack three times in a row will charge your next parry to reduce 90%% damage.\n");
    }
    clearScreen();
    playerRestoreAttributes();

    getchar();
    printf("\nYou continue to explore forward.\n");
    getchar();
    warning();
    printf("A goblin mage with a staff suddenly jumped out.\n");
    getchar();
    printf("You have no choice but keep fighting!\n");
    getchar();

    printf("Your Hp is %d. Goblin Mage Hp is %d.\n", player.curHp, curEnemy.curHp);
    getchar();
    // Skill 1:
    // Each round has a 20% chance to charge for two turns (it won't trigger itself during the charge),
    // and release a spell barrier that can resist 50% of oncoming damage,
    // deal 220% damage and break 50% of armor on the next attack.

    // Skill 2: TODO: Finish this skill
    // After being attacked for three times in a row,
    // the next time goblin are attacked,
    // 50% of the damage caused is reflected to the attacker,
    // and goblin will only take 50% of the damage.
    int playerSkill1Counter = 0;
    int playerSkill2Counter = 0;
    const int goblinSkillTriggerChance = 4;
    const float goblinSkillDmgFactor = 2.2f;
    loop_goblin:
    {
      int GRand;
      int actionChoice;
      int thisTurnPlayerSkill1;
      int thisTurnPlayerSkill2 = 0;
      int thisTurnGoblinSkill = 0;
      int goblinCaused = 0;
      int playerCaused;
      newTurnStart();
      getChoice(&actionChoice);
      printf("\n");
      switch (actionChoice) {
        case ATTACK: {
          // Check the skill "Shield Bash"
          if (playerSkill1Counter >= 2 && player.level >= 2) {
            playerCaused = waving(player.damage) * 3;
            thisTurnPlayerSkill1 = 1;
          } else {
            playerCaused = waving(player.damage) - curEnemy.armor;
            thisTurnPlayerSkill1 = 0;
          }

          // Check goblin charging
          switch (gSkillCounter) {
            case 0: { // Goblin is not charging. roll to start charging
              GRand = rand() % goblinSkillTriggerChance;
              if (GRand == 0) { // Goblin starts charging
                gSkillCounter = 1;
                playerCaused *= 0.5f;
                curEnemy.curHp -= playerCaused;
                thisTurnGoblinSkill = 0;
              } else { // Goblin won't charge
                curEnemy.curHp -= playerCaused;
                goblinCaused = waving(curEnemy.damage) - player.armor;
                player.curHp -= goblinCaused;
                thisTurnGoblinSkill = 0;
              }
            }
              break;
            case 1: { // Goblin is charging, already spent 1 turns
              playerCaused *= 0.5f;
              curEnemy.curHp -= playerCaused;
              gSkillCounter += 1;
              thisTurnGoblinSkill = 0;
            }
              break;
            case 2: { // Goblin has charged up
              curEnemy.curHp -= playerCaused;
              goblinCaused = waving((curEnemy.damage * goblinSkillDmgFactor)) - ((float) player.armor / 2.0f);
              player.curHp -= goblinCaused;
              gSkillCounter = 0;
              thisTurnGoblinSkill = 1;
            }
              break;
            default:
              break;
          }
          // Reset skill 1
          playerSkill1Counter = 0;
          if (curEnemy.curHp > 0 && player.curHp > 0) { // Not yet killed
            if (player.level >= 3) {
              playerSkill2Counter += 1;
            } // count the skill 2
            if (thisTurnPlayerSkill1 == 1) {
              printf("Your skill \"Shield Bash\" is triggered.\n");
            }
            switch (gSkillCounter) {
              case 1:
                printf("The goblin mage is charging, and a magic barrier appears in front of them.\n\n");
                printf("You attacked the goblin mage, but the effect is weak, only caused %d damage.\n\n",
                       playerCaused);
                break;
              case 2:
                printf("The goblin mage is still charging, and the magic barrier is about to burst.\n\n");
                printf("You attacked the goblin mage, but the effect is weak, only caused %d damage.\n\n",
                       playerCaused);
                break;
              case 0:
                printf("\nYou attacked the goblin mage and caused %d damage.\n\n", playerCaused);
                break;
              default:
                break;
            }
            if (thisTurnGoblinSkill == 1) {
              printf(
                "The goblin mage has charged up and released pyroblast on you, inflicting a huge damage up to %d!\n\n",
                goblinCaused);
            }
            if (gSkillCounter == 0) {
              printf("The goblin mage cast a fireball on you, dealing %d damage.\n\n", goblinCaused);
            }
            getchar();
            getchar();
            goto loop_goblin;
          } else if (curEnemy.curHp <= 0) { // Killed
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("\nYou mustered up your courage and stabbed the goblin mage with a fatal blow\n\n");
            printf("Congratulations! You won the fight.\n\n");
            ending = 1;
            part += 1;
            goto win;
          } else { // Failed
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("\nYou hit the goblin and cause %d damage.\n\n", playerCaused);
            if (thisTurnGoblinSkill == 1) {
              printf(
                "After the goblin mage has charged up, they released the pyroblast, dealing %d damage.\n\n",
                goblinCaused);
              printf("You exploded in this havoc!\n\n");
            } else {
              printf(
                "The goblin released the dragon flame.\n\n");
              printf("You can't resist such a terrifying attack at all and evaporated in the flame...\n\n");
            }
            ending = 0;
            getchar();
            getchar();
            goto die;
          }
        }
          break;
        case PARRY: {
          // Check goblin charging
          switch (gSkillCounter) {
            case 0: { // Goblin is not charging. roll to start charging
              GRand = rand() % goblinSkillTriggerChance;
              if (GRand == 0) {// Goblin starts charging
                gSkillCounter = 1;
                thisTurnGoblinSkill = 0;
              } else { // Goblin won't charge
                // Check player skill "Offense To Defense"
                if (playerSkill2Counter >= 3 && player.level >= 3) {
                  goblinCaused = waving(curEnemy.damage) * 0.1f;
                  thisTurnPlayerSkill2 = 1;
                } else {
                  goblinCaused = waving(curEnemy.damage) - player.armor * 2;
                  thisTurnPlayerSkill2 = 0;
                }
                player.curHp -= goblinCaused;
                thisTurnGoblinSkill = 0;
              }
            }
              break;
            case 1: { // Goblin is charging, already spent 1 turn
              gSkillCounter += 1;
              thisTurnGoblinSkill = 0;
            }
              break;
            case 2: { // Goblin has charged and prepare to release.
              // Check player skill "Offense To Defense"
              goblinCaused = waving((curEnemy.damage * goblinSkillDmgFactor)) - ((float) player.armor / 2.0f);
              if (playerSkill2Counter >= 3 && player.level >= 3) {
                goblinCaused *= 0.1f; // -90% damage
                thisTurnPlayerSkill2 = 1;
              } else {
                thisTurnPlayerSkill2 = 0;
              }
              player.curHp -= goblinCaused;
              gSkillCounter = 0;
              thisTurnGoblinSkill = 1;
            }
              break;
            default:
              break;
          }
          playerSkill2Counter = 0;
          if (player.curHp > 0) { //Not failed
            if (player.level >= 2) {
              playerSkill1Counter += 1;
            }
            if (thisTurnPlayerSkill2 == 1) {
              printf("Your skill \"Offense To Defense\" is triggered.\n\n");
            }
            printf("You raised the shield and defended.\n");
            switch (gSkillCounter) {
              case 1:
                printf("The goblin mage is charging, and a magic barrier appears in front of them.\n\n");
                break;
              case 2:
                printf("The goblin mage is still charging, and the magic barrier is about to burst.\n\n");
                break;
              case 0:
                printf("Goblin mage cast fireball on you, dealing %d damage.\n\n", goblinCaused);
                break;
              default:
                break;
            }
            if (thisTurnGoblinSkill == 1) {
              if (thisTurnPlayerSkill2 == 0) {
                printf(
                  "After the goblin mage has charged up, they released the pyroblast, dealing %d damage.\n\n",
                  goblinCaused);
                printf("You exploded in this havoc!\n\n");
              } else {
                printf(
                  "The goblin released released the pyroblast on you, but blocked by your tough shield.\n\n");
              }
            }
            getchar();
            getchar();
            goto loop_goblin;
          } else { // Failed
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            if (thisTurnPlayerSkill2 == 1) {
              printf("Your skill \"Offense To Defense\" is triggered.\n\n");
            }
            printf("You raised the shield and defended.\n\n");
            if (thisTurnGoblinSkill == 1 && thisTurnPlayerSkill2 == 1) {
              printf("The goblin mage has charged up and released pyroblast on you, dealing %d damage.\n\n",
                     goblinCaused);
              printf("Your shield was burned and melted, and you were also wiped out in the flames...\n\n");
            } else {
              printf("The goblin mage cast dragon flames on you, dealing %d damage.\n\n",
                     goblinCaused);
              printf("You couldn't resist such a powerful spell at all. You were wiped out in the flames...\n\n");
            }
            ending = 0;
            getchar();
            getchar();
            goto die;
          }
        }
          break;
        case Withdraw: {
          printf(
            "\nThe goblin mage chanted a series of incantations, released a magic circle under your feet, and you were imprisoned!\n");

          // Check goblin charging
          switch (gSkillCounter) {
            case 0: {  // Goblin is not charging. roll to start charging
              GRand = rand() % goblinSkillTriggerChance;
              if (GRand == 0) { // Goblin starts charging
                gSkillCounter = 1;
                thisTurnGoblinSkill = 0;
              } else { // Goblin won't charge
                goblinCaused = waving(curEnemy.damage) * 1.5f;
                player.curHp -= goblinCaused;
                thisTurnGoblinSkill = 0;
              }
              break;
            }
            case 1: { // Goblin is charging, already spent 1 turn
              gSkillCounter += 1;
              thisTurnGoblinSkill = 0;
              break;
            }
            case 2: { // Goblin has charged and prepare to release.
              goblinCaused = (waving(curEnemy.damage) * 3) * 1.5f;
              player.curHp -= goblinCaused;
              gSkillCounter = 0;
              thisTurnGoblinSkill = 1;
              break;
            }
            default:
              break;
          }
          if (player.curHp > 0) {
            switch (gSkillCounter) {
              case 1:
                printf("The goblin mage is charging, and a magic barrier appears in front of them.\n\n");
                break;
              case 2:
                printf("The goblin mage is still charging, and the magic barrier is about to burst.\n\n");
                break;
              case 0:
                printf("Goblin mage cast fireball on you, dealing %d damage.\n\n", goblinCaused);
                break;
              default:
                break;
            }
            if (thisTurnGoblinSkill == 1) {
              printf("The goblin mage has charged up and cast pyroblast on you, dealing %d damage\n\n", goblinCaused);
            } else {
              printf("It's an opportunity for goblin to cast fireball on you, dealing %d damage\n\n", goblinCaused);
            }
            getchar();
            getchar();
            goto loop_goblin;
          }
          if (player.curHp <= 0) {
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            if (thisTurnGoblinSkill == 1) {
              printf(
                "After the goblin mage has charged up, they cast the pyroblast, dealing %d damage.\n\n",
                goblinCaused);
              printf("You exploded in this havoc!\n\n");
            } else {
              printf("The goblin released the dragon flame, dealing %d damage.\n\n",
                     goblinCaused);
              printf("You can't resist such a terrifying attack at all and evaporated in the flame...\n\n");
            }
            getchar();
            getchar();
            ending = 0;
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

    if (ending == 1) {
      int expGain = curEnemy.exp - turn * 3;

      if (expGain <= 0)
        expGain = 0;

      player.exp += expGain;

      printf("You spent %d turns and gain %d exp!\n\n", turn, expGain);
      printf("Now you have %d exp\n", player.exp);
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
    printf("             ***********\n");
    printf("             *Game Over*\n");
    printf("             ***********\n");
    printf("Press Enter to restart.");
    getchar();
    clearScreen();
    goto part_slime;
  }
  win:
  {
    getchar();
    printf("\n\n\n\n\n------*------*------*------*------*------*------*------*------*------\n\n\n");
    printf("Congratulations! you cleared the game. Thank you for playing, please wait for my next work! UwU\n");
    printf("\n\n------*------*------*------*------*------*------*------*------*------\n");
  }

  getchar();
  return 0;
}

/// Return a random number between [0f,1f]
float randf() {
  return (float) rand() / (float) RAND_MAX;
}


/// Return a random number between [min,max]
float randfIn(float min, float max) {
  return randf() * max + min;
}


int waving(int value) {
  return (int) ((float) value * randfIn(1.0f - randomness, 1.0f + randomness));
}


#pragma clang diagnostic pop
