#include "mixing.h"

/*
  the following N * 3 table consists of
  all possible combinations

  parent a, parent b, resulting child
*/

int combinationTable[] = {
 BLACK, BLACK, WHITE,
 WHITE, BLACK, RED,
 WHITE, WHITE, GREEN,
 WHITE, RED, BLUE,
 WHITE, GREEN, YELLOW,
 BLACK, RED, ORANGE,
 BLACK, GREEN, CYAN,
 WHITE, ORANGE, PURPLE,
 PURPLE, WHITE, PINK
};

int mix_colors(int color1, int color2) {
  int numCombinations = sizeof(combinationTable) / (3 * sizeof(int));
  for (int i = 0; i < numCombinations; i += 3) {
    int parentA = combinationTable[i + 0];
    int parentB = combinationTable[i + 1];
    int child = combinationTable[i + 2];
    if (parentA == color1 && parentB == color2) {
      return child;
    } else if (parentA == color2 && parentB == color1) {
      return child;
    }
  }

  return BAD_MIX;
}
