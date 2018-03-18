#ifndef MIXING_H
#define MIXING_H

#define BAD_MIX -1

/* you start with only black potions */
#define BLACK 0

/* by mixing unlocked potions, you can unlock these potions */
#define WHITE 1
#define RED 2
#define GREEN 3
#define BLUE 4
#define YELLOW 5
#define ORANGE 6
#define CYAN 7
#define PURPLE 8
#define PINK 9

extern char* colorNames[10];

/* returns BAD_MIX if the colors do not mix */
int mix_colors(int color1, int color2);

#endif
