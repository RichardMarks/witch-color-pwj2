#ifndef COLORS_H
#define COLORS_H

// because the colorset was created using 1-indexing :facepalm:
#define UNUSED 0

// Base Colors -- these cannot be created, only used to mix new
#define BLUE 1
#define YELLOW 2
#define PINK 3
#define RED 4
#define GREEN 5
#define BLACK 6
#define WHITE 7

#define BLUE_POTION { BLUE, 0, 0, 255 }
#define YELLOW_POTION { YELLOW, 255, 255, 0 }
#define PINK_POTION { PINK, 229, 76, 202 }
#define RED_POTION { RED, 221, 76, 52 }
#define GREEN_POTION { GREEN, 48, 255, 0 }
#define BLACK_POTION { BLACK, 16, 12, 24 }
#define WHITE_POTION { WHITE, 255, 254, 242 }

// Base Mixable Results -- these are the products of mixing base colors

#define PURPLE_HEART 8
#define ROUGE 9
#define JUNGLE_GREEN 10
#define LIME 11
#define BUTTERCUP 12
#define APRICOT 13
#define CITRON 14
#define MANDY 15
#define FEDORA 16
#define DEEP_BLUE 17
#define SARATOGA 18
#define FINN 19
#define COCOA_BEAN 20
#define PARSLEY 21
#define PORTAGE 22
#define PORTAFINO 23
#define CHANTILLY 24
#define SEA_PINK 25
#define REEF 26

#define PURPLE_HEART_POTION { PURPLE_HEART, 162, 54, 218 }
#define ROUGE_POTION { ROUGE, 164, 56, 106 }
#define JUNGLE_GREEN_POTION { JUNGLE_GREEN, 29, 150, 108 }
#define LIME_POTION { LIME, 180, 255, 0 }
#define BUTTERCUP_POTION { BUTTERCUP, 243, 192, 19 }
#define APRICOT_POTION { APRICOT, 240, 150, 118 }
#define CITRON_POTION { CITRON, 143, 156, 29 }
#define MANDY_POTION { MANDY, 224, 76, 116 }
#define FEDORA_POTION { FEDORA, 115, 112, 114 }
#define DEEP_BLUE_POTION { DEEP_BLUE, 10, 7, 115 }
#define SARATOGA_POTION { SARATOGA, 93, 90, 16 }
#define FINN_POTION { FINN, 82, 43, 81 }
#define COCOA_BEAN_POTION { COCOA_BEAN, 97, 37, 35 }
#define PARSLEY_POTION { PARSLEY, 24, 77, 18 }
#define PORTAGE_POTION { PORTAGE, 149, 148, 247 }
#define PORTAFINO_POTION { PORTAFINO, 255, 255, 178 }
#define CHANTILLY_POTION { CHANTILLY, 245, 181, 226 }
#define SEA_PINK_POTION { SEA_PINK, 238, 163, 145 }
#define REEF_POTION { REEF, 182, 255, 156 }

// Mixable Combo Results -- products of mixing base and mixed colors

#define LASER 27
#define LEMON_GINGER 28
#define CAREYS_PINK 29
#define COPPER_ROSE 30
#define DANUBE 31
#define CONTESSA 32
#define SCAMPI 33
#define DAISY_BUSH 34
#define BOUQUET 35
#define CRETE 36

#define LASER_POTION { LASER, 198, 188, 119 }
#define LEMON_GINGER_POTION { LEMON_GINGER, 172, 152, 32 }
#define CAREYS_PINK_POTION { CAREYS_PINK, 210, 156, 174 }
#define COPPER_ROSE_POTION { COPPER_ROSE, 151, 105, 111 }
#define DANUBE_POTION { DANUBE, 108, 150, 199 }
#define CONTESSA_POTION { CONTESSA, 195, 110, 138 }
#define SCAMPI_POTION { SCAMPI, 97, 102, 163 }
#define DAISY_BUSH_POTION { DAISY_BUSH, 91, 31, 170 }
#define BOUQUET_POTION { BOUQUET, 181, 150, 180 }
#define CRETE_POTION { CRETE, 102, 143, 51 }

#endif
