//
// Created by Liplum on 4/24/2023.
//

#include <stdlib.h>
#include <stdio.h>

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void alert() {
  printf("\a");
}