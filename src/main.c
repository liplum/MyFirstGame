#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "entity.h"
#include "levels.h"
#include "game.h"


void alert() {
  printf("\a");
}

const float shieldBashMul = 2.0f;
const float shieldBashPenetrate = 0.5f;


void showDeath() {
  printf("\nYou failed...\n");
  printf("\t\t***********\n");
  printf("\t\t*Game Over*\n");
  printf("\t\t***********\n");
}


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
