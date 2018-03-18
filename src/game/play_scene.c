#include "game.h"
#include "scenes.h"
#include "mixing.h"

/*

  ## BASE COLORS

  + black
  + white
  + red
  + green
  + blue

  ## MIXING COLORS

  + mixed color = [mixed color | base color] + [mixed color | base color]
  + every color has a unique id integer
  + define mixed colors by giving the id numbers of the two parts and id of the resulting mixed color

  ## STARTUP

  + cauldron starts with a random base color
  + spellbook shows a random locked target color
  + potion bottles start with base colors

  ## INTERACTIONS

  + click on a potion bottle to select it
  + click on a selected potion bottle to deselect it

  + click on cauldron to add selected potion to cauldron
  + click on cauldron with no potion selected to reset cauldron to starting base color
  + click on cauldron with selected empty potion bottle to fill with cauldron color

  + click on witch with selected potion to empty selected potion bottle
  + click on witch with no selected potion to reset all potion bottles to starting base colors

  + click on menu button to display pause menu [resume, guidebook, quit]
  + click on volume speaker icon to toggle audio on / off
 */

SDL_Texture* bgTexture = 0;
SDL_Texture* spellbookTexture = 0;
SDL_Texture* cauldronTexture = 0;
SDL_Texture* witchTexture = 0;

// need 5 copies of the same texture to apply color effects separately
SDL_Texture* potionTexture1 = 0;
SDL_Texture* potionTexture2 = 0;
SDL_Texture* potionTexture3 = 0;
SDL_Texture* potionTexture4 = 0;
SDL_Texture* potionTexture5 = 0;

SDL_Texture* selectionTexture = 0;

SDL_Texture* menuButtonTexture = 0;
SDL_Texture* audioMutedTexture = 0;
SDL_Texture* audioUnmutedTexture = 0;

typedef struct t_Sprite {
  float x;
  float y;
  float xv;
  float yv;
  void* data;
  int state;
  SDL_Texture* texture;
  SDL_Rect src;
} Sprite;

typedef struct t_Potion {
  int id;
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Potion;

void Potion__init_sprite(Sprite* sprite, Potion* potion) {
  sprite->data = potion;
  SDL_SetTextureColorMod(sprite->texture, potion->r, potion->g, potion->b);
}

Potion blackPotion = { BLACK, 0x20, 0x20, 0x20 };
Potion whitePotion = { WHITE, 0xEA, 0xEA, 0xEA };
Potion redPotion = { RED, 0xEA, 0x00, 0x00 };
Potion greenPotion = { GREEN, 0x00, 0xEA, 0x00 };
Potion bluePotion = { BLUE, 0x00, 0x00, 0xEA };
Potion yellowPotion = { YELLOW, 0xEA, 0xEA, 0x00 };
Potion orangePotion = { ORANGE, 0xEA, 0x80, 0x00 };
Potion cyanPotion = { CYAN, 0x00, 0xEA, 0xEA };
Potion purplePotion = { PURPLE, 0xA9, 0x00, 0xA9 };
Potion pinkPotion = { PINK, 0xEA, 0x00, 0xEA };

Potion* basePotions[] = {
  &blackPotion,
  &whitePotion,
  &redPotion,
  &greenPotion,
  &bluePotion
};

Potion* allPotions[] = {
  &blackPotion,
  &whitePotion,
  &redPotion,
  &greenPotion,
  &bluePotion,
  &yellowPotion,
  &orangePotion,
  &cyanPotion,
  &purplePotion,
  &pinkPotion
};

int startingCauldronColors[] = {
  BLACK,
  WHITE,
  RED,
  GREEN,
  BLUE
};
int startingCauldronColor = GREEN;
int cauldronColor = GREEN;

void select_starting_cauldron_color () {
  int index = rand() % 5;
  startingCauldronColor = startingCauldronColors[index];
  cauldronColor = startingCauldronColor;
}

#define MAX_SPRITES 200
Sprite sprites[MAX_SPRITES];
int numSprites = 0;

Sprite* Sprite__init(Sprite* sprite, SDL_Texture* texture, SDL_Rect* src);
void Sprite__render(Sprite* sprite);
int Sprite__collides_with_point(Sprite* sprite, int x, int y);

int selectedPotionIndex = -1;

#define BOTTLE_EMPTY 0
#define BOTTLE_FULL 1

#define AUDIO_UNMUTED 0
#define AUDIO_MUTED 1

Sprite* menuButtonSprite = 0;
Sprite* audioSprite = 0;
Sprite* witchSprite = 0;
Sprite* cauldronSprite = 0;
Sprite* spellbookSprite = 0;
Sprite* potionSprite[] = { 0, 0, 0, 0, 0 };
Sprite* selectionSprite = 0;

void mute_audio () {
  audioSprite->state = AUDIO_MUTED;
  audioSprite->texture = audioMutedTexture;
  printf("TODO: mute audio\n");
}

void unmute_audio () {
  audioSprite->state = AUDIO_UNMUTED;
  audioSprite->texture = audioUnmutedTexture;
  printf("TODO: unmute audio\n");
}

void init_play_scene() {
  bgTexture = load_texture("../data/backgrounds/bg.png");
  spellbookTexture = load_texture("../data/sprites/spellbook.png");
  cauldronTexture = load_texture("../data/sprites/cauldron.png");
  witchTexture = load_texture("../data/sprites/witch.png");
  potionTexture1 = load_texture("../data/sprites/potion.png");
  potionTexture2 = load_texture("../data/sprites/potion.png");
  potionTexture3 = load_texture("../data/sprites/potion.png");
  potionTexture4 = load_texture("../data/sprites/potion.png");
  potionTexture5 = load_texture("../data/sprites/potion.png");
  selectionTexture = load_texture("../data/ui/selection.png");
  menuButtonTexture = load_texture("../data/ui/menu_button.png");
  audioMutedTexture = load_texture("../data/ui/audio_muted.png");
  audioUnmutedTexture = load_texture("../data/ui/audio_unmuted.png");

  // initialize sprites
  numSprites = 0;
  Sprite__init(&sprites[numSprites], bgTexture, 0); numSprites += 1;
  spellbookSprite = Sprite__init(&sprites[numSprites], spellbookTexture, 0); numSprites += 1;
  cauldronSprite = Sprite__init(&sprites[numSprites], cauldronTexture, 0); numSprites += 1;
  witchSprite = Sprite__init(&sprites[numSprites], witchTexture, 0); numSprites += 1;

  potionSprite[0] = Sprite__init(&sprites[numSprites], potionTexture1, 0); numSprites += 1;
  potionSprite[1] = Sprite__init(&sprites[numSprites], potionTexture2, 0); numSprites += 1;
  potionSprite[2] = Sprite__init(&sprites[numSprites], potionTexture3, 0); numSprites += 1;
  potionSprite[3] = Sprite__init(&sprites[numSprites], potionTexture4, 0); numSprites += 1;
  potionSprite[4] = Sprite__init(&sprites[numSprites], potionTexture5, 0); numSprites += 1;

  selectionSprite = Sprite__init(&sprites[numSprites], selectionTexture, 0); numSprites += 1;

  menuButtonSprite = Sprite__init(&sprites[numSprites], menuButtonTexture, 0); numSprites += 1;
  audioSprite = Sprite__init(&sprites[numSprites], audioUnmutedTexture, 0); numSprites += 1;
}

void destroy_play_scene() {
  kill_texture(bgTexture);
  kill_texture(spellbookTexture);
  kill_texture(cauldronTexture);
  kill_texture(witchTexture);
  kill_texture(potionTexture1);
  kill_texture(potionTexture2);
  kill_texture(potionTexture3);
  kill_texture(potionTexture4);
  kill_texture(potionTexture5);
  kill_texture(selectionTexture);
  kill_texture(menuButtonTexture);
  kill_texture(audioMutedTexture);
  kill_texture(audioUnmutedTexture);
}

void enter_play_scene() {
  // position the cauldron in the center of the screen
  cauldronSprite->x = (SCREEN_WIDTH - cauldronSprite->src.w) / 2;
  cauldronSprite->y = (SCREEN_HEIGHT - cauldronSprite->src.h) / 2;

  // position the spellbook above the cauldron
  spellbookSprite->x = (SCREEN_WIDTH - spellbookSprite->src.w) / 2;
  spellbookSprite->y = 100;

  // position the witch below the cauldron
  witchSprite->x = (SCREEN_WIDTH - witchSprite->src.w) / 2;
  witchSprite->y = cauldronSprite->y + cauldronSprite->src.h - 20;

  // position the potion bottles near the bottom of the screen
  for (int i = 0; i < 5; i += 1) {
    Sprite* sprite = potionSprite[i];
    sprite->x = 24 + ((sprite->src.w + 8) * i);
    sprite->y = SCREEN_HEIGHT - (sprite->src.h + 16);

    // initialize the potion bottles with base colors
    Potion__init_sprite(sprite, basePotions[i]);

    sprite->state = BOTTLE_FULL;
  }

  // position the selection box off screen
  selectionSprite->x = -selectionSprite->src.w;
  selectionSprite->y = -selectionSprite->src.h;

  // position menu button
  menuButtonSprite->x = 10;
  menuButtonSprite->y = 10;

  // position audio toggle
  audioSprite->x = SCREEN_WIDTH - (audioSprite->src.w + 10);
  audioSprite->y = 10;
  audioSprite->state = AUDIO_UNMUTED;


  // init the cauldron
  select_starting_cauldron_color();

  Potion* cauldronPotion = allPotions[cauldronColor];
  SDL_SetTextureColorMod(cauldronSprite->texture, cauldronPotion->r, cauldronPotion->g, cauldronPotion->b);
}

void exit_play_scene() {

}

int mouseDown = 0;
void update_play_scene(float dt) {
  Input* input = &currentGamePtr->inputs;
  Mouse* mouse = &currentGamePtr->mouse;

  if (mouse->state == SDL_PRESSED && mouseDown == 0) {
    mouseDown = 1;

    // clicked on potion?
    for (int i = 0; i < 5; i += 1) {
      Sprite* sprite = potionSprite[i];
      if (Sprite__collides_with_point(sprite, mouse->x, mouse->y)) {
        Potion* potion = sprite->data;
        printf("clicked on potion bottle %d: key[%d] color (R 0x%02X, G 0x%02X, B 0x%02X)\n", i, potion->id, potion->r, potion->g, potion->b);

        // move witch in front of potion
        witchSprite->x = mouse->x - (witchSprite->src.w / 2);

        // make or break selection
        if (selectedPotionIndex == i) {
          selectedPotionIndex = -1;
          selectionSprite->x = -selectionSprite->src.w;
          selectionSprite->y = -selectionSprite->src.h;
          // SDL_SetTextureColorMod(sprite->texture, 0xff, 0xff, 0xff);
        } else {
          selectedPotionIndex = i;
          selectionSprite->x = (sprite->x + (sprite->src.w / 2)) - (selectionSprite->src.w / 2);
          selectionSprite->y = (sprite->y + (sprite->src.h / 2)) - (selectionSprite->src.h / 2);
          Potion* potion = (Potion*)sprite->data;
          // SDL_SetTextureColorMod(sprite->texture, potion->r, potion->g, potion->b);
        }
      }
    }

    // clicked on cauldron?

    // + click on cauldron to add selected potion to cauldron
    // + click on cauldron with no potion selected to reset cauldron to starting base color
    // + click on cauldron with selected empty potion bottle to fill with cauldron color

    if (Sprite__collides_with_point(cauldronSprite, mouse->x, mouse->y)) {
      printf("clicked on cauldron: ");

      if (cauldronColor == BAD_MIX) {
        printf("dumping failed mix from cauldron\n");
        cauldronColor = basePotions[startingCauldronColor]->id;
        Potion* cauldronPotion = allPotions[cauldronColor];
        SDL_SetTextureColorMod(cauldronSprite->texture, cauldronPotion->r, cauldronPotion->g, cauldronPotion->b);
      } else {
        // potion selected?
        if (selectedPotionIndex != -1) {
          Sprite* selectedPotionSprite = potionSprite[selectedPotionIndex];
          Potion* selectedPotion = (Potion*)selectedPotionSprite->data;

          // is the bottle empty?
          if (selectedPotionSprite->state == BOTTLE_EMPTY) {
            printf("filling selected empty potion bottle with cauldron color\n");
          } else {
            printf("adding selected potion to cauldron...\n");
            int result = mix_colors(cauldronColor, selectedPotion->id);
            if (result != BAD_MIX) {
              cauldronColor = result;
              Potion* cauldronPotion = allPotions[cauldronColor];
              SDL_SetTextureColorMod(cauldronSprite->texture, cauldronPotion->r, cauldronPotion->g, cauldronPotion->b);
              printf("SUCCESS! Got %d\n", result);
            } else {
              cauldronColor = BAD_MIX;
              SDL_SetTextureColorMod(cauldronSprite->texture, 0xff, 0xff, 0xff);
              printf("FAILED! click on cauldron to reset\n");
            }
          }

          // deselect
          selectedPotionIndex = -1;
          selectionSprite->x = -selectionSprite->src.w;
          selectionSprite->y = -selectionSprite->src.h;
        } else {
          // no potion selected
          printf("resetting to starting base color\n");
          cauldronColor = basePotions[startingCauldronColor]->id;
          Potion* cauldronPotion = allPotions[cauldronColor];
          SDL_SetTextureColorMod(cauldronSprite->texture, cauldronPotion->r, cauldronPotion->g, cauldronPotion->b);
        }
      }
    }

    // clicked on spellbook?
    if (Sprite__collides_with_point(spellbookSprite, mouse->x, mouse->y)) {
      printf("clicked on spellbook\n");
    }

    // clicked on menu button?
    if (Sprite__collides_with_point(menuButtonSprite, mouse->x, mouse->y)) {
      printf("TODO: show pause menu\n");
    }

    // clicked on audio toggle?
    if (Sprite__collides_with_point(audioSprite, mouse->x, mouse->y)) {
      if (audioSprite->state == AUDIO_UNMUTED) {
        mute_audio();
      } else {
        unmute_audio();
      }
    }

    // clicked on witch?
    if (Sprite__collides_with_point(witchSprite, mouse->x, mouse->y)) {
      printf("clicked on witch\n");
    }
  } else if (mouse->state != SDL_PRESSED && mouseDown == 1) {
    mouseDown = 0;
  }

  for (int i = 0; i < numSprites; i += 1) {
    Sprite* sprite = &sprites[i];
    sprite->x += sprite->xv * dt;
    sprite->y += sprite->yv * dt;
  }
}

void render_play_scene() {
  for (int i = 0; i < numSprites; i += 1) {
    Sprite* sprite = &sprites[i];
    Sprite__render(sprite);
  }
}

Sprite* Sprite__init(Sprite* sprite, SDL_Texture* texture, SDL_Rect* src) {
  memset(sprite, 0, sizeof(Sprite));
  sprite->texture = texture;

  if (src) {
    sprite->src.x = src->x;
    sprite->src.y = src->y;
    sprite->src.w = src->w;
    sprite->src.h = src->h;
  } else {
    int w, h;
    SDL_QueryTexture(sprite->texture, 0, 0, &w, &h);
    sprite->src.x = 0;
    sprite->src.y = 0;
    sprite->src.w = w;
    sprite->src.h = h;
  }

  return sprite;
}

SDL_Rect dst;
void Sprite__render(Sprite* sprite) {
  dst.x = (int)sprite->x;
  dst.y = (int)sprite->y;

  int w, h;
  SDL_QueryTexture(sprite->texture, 0, 0, &w, &h);

  dst.w = w;
  dst.h = h;
  SDL_RenderCopy(mainRendererPtr, sprite->texture, &sprite->src, &dst);
}

int Sprite__collides_with_point(Sprite* sprite, int x, int y) {
  if (
    x >= (int)sprite->x && x <= (int)(sprite->x + sprite->src.w) &&
    y >= (int)sprite->y && y <= (int)(sprite->y + sprite->src.h)) {
    return 1;
  }
  return 0;
}
