//
// Created by Liplum on 4/24/2023.
//

#include <stdlib.h>
#include "calculate.h"

float randf() {
  return (float) rand() / (float) RAND_MAX;
}

float randfIn(float min, float max) {
  float range = max - min;
  return randf() * range + min;
}
