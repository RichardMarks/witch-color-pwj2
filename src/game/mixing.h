#ifndef MIXING_H
#define MIXING_H

#include "colors.h"

#define BAD_MIX -1

extern char* colorNames[];

/* returns BAD_MIX if the colors do not mix */
int mix_colors(int color1, int color2);

#endif
