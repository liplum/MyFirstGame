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
#ifdef _WIN32
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
      case BattleWin: {
        printf("Press Enter to continue...");
        getchar();
        getchar();
        continue;
      }
      case BattleLoss: {
        getchar();
        printf("*----*------*------*------*------*-------*\n");
        printf("|             Game Over                  |\n");
        printf("|       Don't be sad, just try again.    |\n");
        printf("*-----*------*------*------*------*------*\n");
        return 0;
      }
    }
  }

  printf("*----*------*------*------*------*------*------*------*------*------*\n");
  printf("|              Congratulations! you passed the game.                |\n");
  printf("|       Thank you for playing, please wait for my next work! UwU    |\n");
  printf("*-----*------*------*------*------*------*------*------*------*-----*");
  getchar();
  getchar();
  return 0;
}

#pragma clang diagnostic pop
