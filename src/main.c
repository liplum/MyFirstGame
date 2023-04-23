#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "console.h"
#include "level/level_1.h"
#include "level/level_2.h"
#include "level/level_3.h"

#define LevelCount 3

int main(void) {
#ifdef __CLION__
  setvbuf(stdout, NULL, _IONBF, 0);
#endif
  srand((unsigned) time(NULL));
  clearScreen();
  printf("\t\t**********************\n");
  printf("\t\t* First Game v1.5.0  *\n");
  printf("\t\t**********************\n");
  printf("\t\t\t\tLast Change: 4/23/2023    by Liplum\n");

  const BattleRunner levels[LevelCount] = {
    &slimeBattle,
    &giantRatBattle,
    &goblinMageBattle
  };

  for (int i = 0; i < LevelCount; ++i) {
    BattleResult result = levels[i]();
    switch (result) {
      case BattleWin:
        printf("Press Enter to continue...");
        getchar();
        continue;
      case BattleLoss: {
        clearScreen();
        printf("\t\t***********\n");
        printf("\t\t*Game Over*\n");
        printf("\t\t***********\n");
        return 0;
      }
    }
  }

  getchar();
  printf("*----*------*------*------*------*------*------*------*------*-----*");
  printf("|              Congratulations! you passed the game.                |\n");
  printf("|       Thank you for playing, please wait for my next work! UwU    |\n");
  printf("*-----*------*------*------*------*------*------*------*------*-----*");

  getchar();
  return 0;
}

#pragma clang diagnostic pop
