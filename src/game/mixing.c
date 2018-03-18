#include <stdio.h>
#include "mixing.h"

char* colorNames[] = {
  "UNUSED",
  "Blue",
  "Yellow",
  "Pink",
  "Red",
  "Green",
  "Black",
  "White",
  "Purple Heart",
  "Rouge",
  "Jungle Green",
  "Lime",
  "Buttercup",
  "Apricot",
  "Citron",
  "Mandy",
  "Fedora",
  "Deep Blue",
  "Saratoga",
  "Finn",
  "Cocoa Bean",
  "Parsley",
  "Portage",
  "Portafino",
  "Chantilly",
  "Sea Pink",
  "Reef",
  "Laser",
  "Lemon Ginger",
  "Careys Pink",
  "Copper Rose",
  "Danube",
  "Contessa",
  "Scampi",
  "Daisy Bush",
  "Bouquet",
  "Crete"
};

/*
  the following N * 3 table consists of
  all possible combinations

  parent a, parent b, resulting child
*/

int combinationTable[] = {
1,3,8,
1,4,9,
1,5,10,
2,5,11,
2,4,12,
2,3,13,
4,5,14,
4,3,15,
6,7,16,
6,1,17,
6,2,18,
6,3,19,
6,4,20,
6,5,21,
7,1,22,
7,2,23,
7,3,24,
7,4,25,
7,5,26,
26,4,27,
2,19,28,
7,9,29,
10,15,30,
1,26,31,
8,12,32,
8,10,33,
8,17,34,
24,16,35,
11,17,36
};

int mix_colors(int color1, int color2) {
  printf("mixing %s and %s...\n", colorNames[color1], colorNames[color2]);
  int numCombinations = sizeof(combinationTable) / (3 * sizeof(int));
  for (int i = 0; i < numCombinations * 3; i += 3) {
    int parentA = combinationTable[i + 0];
    int parentB = combinationTable[i + 1];
    int child = combinationTable[i + 2];
    printf("checking %s + %s = %s\n", colorNames[parentA], colorNames[parentB], colorNames[child]);
    if (parentA == color1 && parentB == color2) {
      return child;
    } else if (parentA == color2 && parentB == color1) {
      return child;
    }
  }

  return BAD_MIX;
}
