#include "game.h"
#include "scenes.h"
#include "mixing.h"
#include "text_renderer.h"

TTF_Font* targetColorFont = 0;
TTF_Font* selectedPotionFont = 0;
TTF_Font* mixedColorFont = 0;

// #define MAX_TEXTS 10
// Text textObjects[MAX_TEXTS];
// int numTexts = 0;

Text* targetColorText = 0;
Text* mixedColorText = 0;
Text* selectedPotionText = 0;

Mix_Music* bgm = 0;
Mix_Chunk* sfxWitchMove = 0;
Mix_Chunk* sfxMixFailed = 0;
Mix_Chunk* sfxMixSuccess = 0;
Mix_Chunk* sfxMenuClick = 0;
Mix_Chunk* sfxPourPotion = 0;

SDL_Texture* bgTexture = 0;
SDL_Texture* spellbookTexture = 0;
SDL_Texture* cauldronTexture = 0;
SDL_Texture* witchTexture1 = 0;
SDL_Texture* witchTexture2 = 0;

// need 7 copies of the same texture to apply color effects separately
SDL_Texture* potionTexture1 = 0;
SDL_Texture* potionTexture2 = 0;
SDL_Texture* potionTexture3 = 0;
SDL_Texture* potionTexture4 = 0;
SDL_Texture* potionTexture5 = 0;
SDL_Texture* potionTexture6 = 0;
SDL_Texture* potionTexture7 = 0;

SDL_Texture* selectionTexture = 0;

SDL_Texture* menuButtonTexture = 0;
SDL_Texture* audioMutedTexture = 0;
SDL_Texture* audioUnmutedTexture = 0;

SDL_Texture* bookTableTexture = 0;
SDL_Texture* potionTableTexture = 0;
SDL_Texture* bookTargetTexture = 0;
SDL_Texture* cauldronFillTexture = 0;
SDL_Texture* potionBottleTexture = 0;

#define SPRITE_VISIBLE 0x00
#define SPRITE_HIDDEN 0xFF

typedef struct t_Sprite {
  float x;
  float y;
  float xv;
  float yv;
  void* data;
  int state;
  SDL_Texture* texture;
  SDL_Rect src;
  unsigned char visible;
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

Potion bluePotion = BLUE_POTION;
Potion yellowPotion = YELLOW_POTION;
Potion pinkPotion = PINK_POTION;
Potion redPotion = RED_POTION;
Potion greenPotion = GREEN_POTION;
Potion blackPotion = BLACK_POTION;
Potion whitePotion = WHITE_POTION;
Potion purple_heartPotion = PURPLE_HEART_POTION;
Potion rougePotion = ROUGE_POTION;
Potion jungle_greenPotion = JUNGLE_GREEN_POTION;
Potion limePotion = LIME_POTION;
Potion buttercupPotion = BUTTERCUP_POTION;
Potion apricotPotion = APRICOT_POTION;
Potion citronPotion = CITRON_POTION;
Potion mandyPotion = MANDY_POTION;
Potion fedoraPotion = FEDORA_POTION;
Potion deep_bluePotion = DEEP_BLUE_POTION;
Potion saratogaPotion = SARATOGA_POTION;
Potion finnPotion = FINN_POTION;
Potion cocoa_beanPotion = COCOA_BEAN_POTION;
Potion parsleyPotion = PARSLEY_POTION;
Potion portagePotion = PORTAGE_POTION;
Potion portafinoPotion = PORTAFINO_POTION;
Potion chantillyPotion = CHANTILLY_POTION;
Potion sea_pinkPotion = SEA_PINK_POTION;
Potion reefPotion = REEF_POTION;
Potion laserPotion = LASER_POTION;
Potion lemon_gingerPotion = LEMON_GINGER_POTION;
Potion careys_pinkPotion = CAREYS_PINK_POTION;
Potion copper_rosePotion = COPPER_ROSE_POTION;
Potion danubePotion = DANUBE_POTION;
Potion contessaPotion = CONTESSA_POTION;
Potion scampiPotion = SCAMPI_POTION;
Potion daisy_bushPotion = DAISY_BUSH_POTION;
Potion bouquetPotion = BOUQUET_POTION;
Potion cretePotion = CRETE_POTION;

Potion* basePotions[] = {
  &bluePotion,
  &yellowPotion,
  &pinkPotion,
  &redPotion,
  &greenPotion,
  &blackPotion,
  &whitePotion
};

Potion* allPotions[] = {
  &bluePotion,
  &yellowPotion,
  &pinkPotion,
  &redPotion,
  &greenPotion,
  &blackPotion,
  &whitePotion,
  &purple_heartPotion,
  &rougePotion,
  &jungle_greenPotion,
  &limePotion,
  &buttercupPotion,
  &apricotPotion,
  &citronPotion,
  &mandyPotion,
  &fedoraPotion,
  &deep_bluePotion,
  &saratogaPotion,
  &finnPotion,
  &cocoa_beanPotion,
  &parsleyPotion,
  &portagePotion,
  &portafinoPotion,
  &chantillyPotion,
  &sea_pinkPotion,
  &reefPotion,
  &laserPotion,
  &lemon_gingerPotion,
  &careys_pinkPotion,
  &copper_rosePotion,
  &danubePotion,
  &contessaPotion,
  &scampiPotion,
  &daisy_bushPotion,
  &bouquetPotion,
  &cretePotion
};

int startingCauldronColors[] = {
  BLUE,
  YELLOW,
  PINK,
  RED,
  GREEN,
  BLACK,
  WHITE
};
int startingCauldronColor = GREEN;
int cauldronColor = GREEN;

int mixableColors[] = {
  PURPLE_HEART,
  ROUGE,
  JUNGLE_GREEN,
  LIME,
  BUTTERCUP,
  APRICOT,
  CITRON,
  MANDY,
  FEDORA,
  DEEP_BLUE,
  SARATOGA,
  FINN,
  COCOA_BEAN,
  PARSLEY,
  PORTAGE,
  PORTAFINO,
  CHANTILLY,
  SEA_PINK,
  REEF,
  LASER,
  LEMON_GINGER,
  CAREYS_PINK,
  COPPER_ROSE,
  DANUBE,
  CONTESSA,
  SCAMPI,
  DAISY_BUSH,
  BOUQUET,
  CRETE
};

int spellbookColor = FEDORA;
void select_spellbook_color () {
  int index = WHITE + (rand() % (CRETE - WHITE));
  spellbookColor = mixableColors[index];
}

void select_starting_cauldron_color () {
  int index = rand() % 7;
  startingCauldronColor = startingCauldronColors[index];
  cauldronColor = startingCauldronColor;
}

#define MAX_SPRITES 200
Sprite sprites[MAX_SPRITES];
int numSprites = 0;

Sprite* Sprite__init(Sprite* sprite, SDL_Texture* texture, SDL_Rect* src);
void Sprite__render(Sprite* sprite);
int Sprite__collides_with_point(Sprite* sprite, int x, int y);
void Sprite__change_texture(Sprite* sprite, SDL_Texture* texture, SDL_Rect* src);

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
Sprite* potionSprite[] = { 0, 0, 0, 0, 0, 0, 0 };
Sprite* selectionSprite = 0;

Sprite* spellbookFillSprite = 0;
Sprite* cauldronFillSprite = 0;
Sprite* bookTableSprite = 0;
Sprite* potionTableSprite = 0;

Sprite* potionBottleSprite[] = { 0, 0, 0, 0, 0, 0, 0 };

void mute_audio () {
  audioSprite->state = AUDIO_MUTED;
  audioSprite->texture = audioMutedTexture;
  Mix_PauseMusic();
  Mix_Pause(-1);
}

void unmute_audio () {
  audioSprite->state = AUDIO_UNMUTED;
  audioSprite->texture = audioUnmutedTexture;
  Mix_ResumeMusic();
  Mix_Resume(-1);
}

void play_sfx(Mix_Chunk* sfx, float volume);
void play_sfx(Mix_Chunk* sfx, float volume) {
  if (audioSprite->state == AUDIO_MUTED) {
    return;
  }

  int sfxChannel = Mix_PlayChannel(-1, sfx, 0);
  if (sfxChannel == -1) {
    SDL_Log("Error occurred in play_sfx()\nUnable to play sample: %s\n", Mix_GetError());
    return;
  }
  int sfxVolume = (int)(128.0f * volume);
  Mix_Volume(sfxChannel, sfxVolume);
}

void init_play_scene() {
  // printf("loading fonts\n");
  targetColorFont = load_font("../data/fonts/fawn.ttf", 24);
  mixedColorFont = load_font("../data/fonts/Timoteo.ttf", 24);
  selectedPotionFont = load_font("../data/fonts/fawn.ttf", 24);

  // printf("loading music\n");
  bgm = load_music("../data/audio/mixing_bgm.ogg");

  // printf("loading sounds\n");
  sfxWitchMove = load_sfx("../data/audio/witch_move.ogg");
  sfxMixFailed = load_sfx("../data/audio/mix_failed.ogg");
  sfxMixSuccess = load_sfx("../data/audio/mix_success.ogg");
  sfxMenuClick = load_sfx("../data/audio/menu_click.ogg");
  sfxPourPotion = load_sfx("../data/audio/pour.ogg");

  // printf("loading textures\n");
  bgTexture = load_texture("../data/backgrounds/Room.png");
  spellbookTexture = load_texture("../data/sprites/Book.png");
  cauldronTexture = load_texture("../data/sprites/CauldronEmpty.png");
  witchTexture1 = load_texture("../data/sprites/witch.png");
  witchTexture2 = load_texture("../data/sprites/witch2.png");
  potionTexture1 = load_texture("../data/sprites/BottleFill.png");
  potionTexture2 = load_texture("../data/sprites/BottleFill.png");
  potionTexture3 = load_texture("../data/sprites/BottleFill.png");
  potionTexture4 = load_texture("../data/sprites/BottleFill.png");
  potionTexture5 = load_texture("../data/sprites/BottleFill.png");
  potionTexture6 = load_texture("../data/sprites/BottleFill.png");
  potionTexture7 = load_texture("../data/sprites/BottleFill.png");
  selectionTexture = load_texture("../data/ui/selection.png");
  menuButtonTexture = load_texture("../data/ui/Menu.png");
  audioMutedTexture = load_texture("../data/ui/SoundOff.png");
  audioUnmutedTexture = load_texture("../data/ui/SoundOn.png");
  bookTableTexture = load_texture("../data/sprites/Potiontable.png");
  potionTableTexture = load_texture("../data/sprites/Potiontable.png");
  bookTargetTexture = load_texture("../data/sprites/BookFill.png");
  cauldronFillTexture = load_texture("../data/sprites/CauldronFill.png");
  potionBottleTexture = load_texture("../data/sprites/BottleEmpty.png");

  // printf("init text\n");
  targetColorText = Text__create(targetColorFont, 0xFFFFFFFF);
  mixedColorText = Text__create(mixedColorFont, 0xFFFFFFFF);
  selectedPotionText = Text__create(selectedPotionFont, 0xFFFFFFFF);

  // printf("init sprites\n");
  // initialize sprites
  numSprites = 0;
  Sprite__init(&sprites[numSprites], bgTexture, 0); numSprites += 1;

  bookTableSprite = Sprite__init(&sprites[numSprites], potionTableTexture, 0); numSprites += 1;
  spellbookSprite = Sprite__init(&sprites[numSprites], spellbookTexture, 0); numSprites += 1;
  spellbookFillSprite = Sprite__init(&sprites[numSprites], bookTargetTexture, 0); numSprites += 1;

  cauldronSprite = Sprite__init(&sprites[numSprites], cauldronTexture, 0); numSprites += 1;
  cauldronFillSprite = Sprite__init(&sprites[numSprites], cauldronFillTexture, 0); numSprites += 1;

  witchSprite = Sprite__init(&sprites[numSprites], witchTexture1, 0); numSprites += 1;

  potionTableSprite = Sprite__init(&sprites[numSprites], potionTableTexture, 0); numSprites += 1;

  potionBottleSprite[0] = Sprite__init(&sprites[numSprites], potionBottleTexture, 0); numSprites += 1;
  potionBottleSprite[1] = Sprite__init(&sprites[numSprites], potionBottleTexture, 0); numSprites += 1;
  potionBottleSprite[2] = Sprite__init(&sprites[numSprites], potionBottleTexture, 0); numSprites += 1;
  potionBottleSprite[3] = Sprite__init(&sprites[numSprites], potionBottleTexture, 0); numSprites += 1;
  potionBottleSprite[4] = Sprite__init(&sprites[numSprites], potionBottleTexture, 0); numSprites += 1;
  potionBottleSprite[5] = Sprite__init(&sprites[numSprites], potionBottleTexture, 0); numSprites += 1;
  potionBottleSprite[6] = Sprite__init(&sprites[numSprites], potionBottleTexture, 0); numSprites += 1;

  potionSprite[0] = Sprite__init(&sprites[numSprites], potionTexture1, 0); numSprites += 1;
  potionSprite[1] = Sprite__init(&sprites[numSprites], potionTexture2, 0); numSprites += 1;
  potionSprite[2] = Sprite__init(&sprites[numSprites], potionTexture3, 0); numSprites += 1;
  potionSprite[3] = Sprite__init(&sprites[numSprites], potionTexture4, 0); numSprites += 1;
  potionSprite[4] = Sprite__init(&sprites[numSprites], potionTexture5, 0); numSprites += 1;
  potionSprite[5] = Sprite__init(&sprites[numSprites], potionTexture6, 0); numSprites += 1;
  potionSprite[6] = Sprite__init(&sprites[numSprites], potionTexture7, 0); numSprites += 1;

  selectionSprite = Sprite__init(&sprites[numSprites], selectionTexture, 0); numSprites += 1;

  menuButtonSprite = Sprite__init(&sprites[numSprites], menuButtonTexture, 0); numSprites += 1;
  audioSprite = Sprite__init(&sprites[numSprites], audioUnmutedTexture, 0); numSprites += 1;
}

void destroy_play_scene() {
  // printf("destroying texts\n");
  Text__destroy(targetColorText);
  Text__destroy(mixedColorText);
  Text__destroy(selectedPotionText);
  // printf("destroying music\n");
  kill_music(bgm);
  // printf("destroying textures\n");
  kill_texture(bgTexture);
  kill_texture(spellbookTexture);
  kill_texture(cauldronTexture);
  kill_texture(witchTexture1);
  kill_texture(witchTexture2);
  kill_texture(potionTexture1);
  kill_texture(potionTexture2);
  kill_texture(potionTexture3);
  kill_texture(potionTexture4);
  kill_texture(potionTexture5);
  kill_texture(selectionTexture);
  kill_texture(menuButtonTexture);
  kill_texture(audioMutedTexture);
  kill_texture(audioUnmutedTexture);
  kill_texture(bookTableTexture);
  kill_texture(potionTableTexture);
  kill_texture(bookTargetTexture);
  kill_texture(cauldronFillTexture);
  kill_texture(potionBottleTexture);
  // printf("destroying sfx\n");
  kill_sfx(sfxWitchMove);
  kill_sfx(sfxMixFailed);
  kill_sfx(sfxMixSuccess);
  kill_sfx(sfxMenuClick);
  kill_sfx(sfxPourPotion);
  // printf("destroying font target color\n");
  kill_font(targetColorFont);
  // printf("destroying font mixed color\n");
  kill_font(mixedColorFont);
  // printf("destroying font selected potion\n");
  kill_font(selectedPotionFont);
  // printf("end play scene destroy\n");
}

void enter_play_scene() {
  // position the cauldron in the center of the screen
  cauldronSprite->x = (SCREEN_WIDTH - cauldronSprite->src.w) / 2;
  cauldronSprite->y = 222;
  cauldronFillSprite->x = cauldronSprite->x;
  cauldronFillSprite->y = cauldronSprite->y;

  // position the spellbook above the cauldron
  spellbookSprite->x = (SCREEN_WIDTH - spellbookSprite->src.w) / 2;
  spellbookSprite->y = 133;

  spellbookFillSprite->x = spellbookSprite->x;
  spellbookFillSprite->y = spellbookSprite->y;

  bookTableSprite->x = (SCREEN_WIDTH - bookTableSprite->src.w) / 2;
  bookTableSprite->y = 136;

  // position the witch below the cauldron
  witchSprite->x = (SCREEN_WIDTH - witchSprite->src.w) / 2;
  witchSprite->y = cauldronSprite->y + cauldronSprite->src.h - 16;

  // position the potion table
  potionTableSprite->x = (SCREEN_WIDTH - potionTableSprite->src.w) / 2;
  potionTableSprite->y = SCREEN_HEIGHT - (potionTableSprite->src.h + 66);

  // position the potion bottles near the bottom of the screen
  for (int i = 0; i < 5; i += 1) {
    Sprite* sprite = potionSprite[i];
    sprite->x = 42 + ((sprite->src.w + 12) * i);
    sprite->y = SCREEN_HEIGHT - (sprite->src.h + 91);

    Sprite* bottle = potionBottleSprite[i];
    bottle->x = sprite->x;
    bottle->y = sprite->y;

    // initialize the potion bottles with base colors
    Potion__init_sprite(sprite, basePotions[i]);

    sprite->state = BOTTLE_FULL;
  }

  // position the black and white potions on either side of the spellbook
  potionSprite[5]->x = potionSprite[0]->x;
  potionSprite[6]->x = potionSprite[4]->x;
  potionSprite[5]->y = spellbookSprite->y - 4;
  potionSprite[6]->y = spellbookSprite->y - 4;
  potionBottleSprite[5]->x = potionSprite[5]->x;
  potionBottleSprite[6]->x = potionSprite[6]->x;
  potionBottleSprite[5]->y = potionSprite[5]->y;
  potionBottleSprite[6]->y = potionSprite[6]->y;
  Potion__init_sprite(potionSprite[5], basePotions[5]);
  Potion__init_sprite(potionSprite[6], basePotions[6]);
  potionSprite[5]->state = BOTTLE_FULL;
  potionSprite[6]->state = BOTTLE_FULL;

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

  // init the spellbook
  select_spellbook_color();
  Potion* bookPotion = allPotions[spellbookColor];
  SDL_SetTextureColorMod(spellbookFillSprite->texture, bookPotion->r, bookPotion->g, bookPotion->b);

  // init the cauldron
  select_starting_cauldron_color();

  Potion* cauldronPotion = allPotions[cauldronColor];
  SDL_SetTextureColorMod(cauldronFillSprite->texture, cauldronPotion->r, cauldronPotion->g, cauldronPotion->b);

  // start bgm
  int bgmVolume = (int)(0.25f * 128.0f);
  Mix_VolumeMusic(bgmVolume);
  if (Mix_FadeInMusic(bgm, -1, 500) < 0) {
    printf("Error occurred in enter_play_scene()\nUnable to play BGM\n");
    return;
  }

  // init the text objects
  //void Text__set_text(Text* ptr, char* text);
  Text__set_text(targetColorText, colorNames[spellbookColor]);
  Text__set_text(mixedColorText, "");
  Text__set_text(selectedPotionText, "");
  targetColorText->x = SCREEN_WIDTH / 2;
  targetColorText->y = spellbookSprite->y - 40;

  selectedPotionText->x = SCREEN_WIDTH / 2;
  selectedPotionText->y = SCREEN_HEIGHT - 48;

  mixedColorText->x = SCREEN_WIDTH / 2;
  mixedColorText->y = SCREEN_HEIGHT / 2;
  // Text__set_text(targetColorText, colorNames[spellbookColor]);
  // Text__set_text(mixedColorText, colorNames[result]);
  // Text__set_text(selectedPotionText, colorNames[potion->id]);
}

void exit_play_scene() {

}

int mouseDown = 0;
void update_play_scene(float dt) {
  Input* input = &currentGamePtr->inputs;
  Mouse* mouse = &currentGamePtr->mouse;

  // Sprite* mover = cauldronSprite;
  // if (input->down) {
  //   mover->y += 1;
  //   printf("Y = %d\n", (int)mover->y);
  // } else if (input->up) {
  //   mover->y -= 1;
  //   printf("Y = %d\n", (int)mover->y);
  // }
  // if (input->left) {
  //   mover->x -= 1;
  //   printf("X = %d\n", (int)mover->x);
  // } else if (input->right) {
  //   mover->x += 1;
  //   printf("X = %d\n", (int)mover->x);
  // }


  if (mouse->state == SDL_PRESSED && mouseDown == 0) {
    mouseDown = 1;

    // clicked on potion?
    for (int i = 0; i < 7; i += 1) {
      Sprite* sprite = potionSprite[i];
      if (Sprite__collides_with_point(sprite, mouse->x, mouse->y)) {
        Potion* potion = sprite->data;
        printf("clicked on potion bottle %d: %s color (R 0x%02X, G 0x%02X, B 0x%02X)\n", i, colorNames[potion->id], potion->r, potion->g, potion->b);

        // move witch in front of potion
        if (i < 5) {
          // face south
          if (witchSprite->texture != witchTexture1) {
            Sprite__change_texture(witchSprite, witchTexture1, 0);
          }
          witchSprite->y = sprite->y - (witchSprite->src.h + 12);
        } else {
          // face north
          if (witchSprite->texture != witchTexture2) {
            Sprite__change_texture(witchSprite, witchTexture2, 0);
          }
          witchSprite->y = sprite->y + (sprite->src.h + 24);
        }
        witchSprite->x = mouse->x - (witchSprite->src.w / 2);
        play_sfx(sfxWitchMove, 0.25f);

        // make or break selection
        if (selectedPotionIndex == i) {
          selectedPotionIndex = -1;
          selectionSprite->x = -selectionSprite->src.w;
          selectionSprite->y = -selectionSprite->src.h;
          Text__set_text(selectedPotionText, "");
        } else {
          selectedPotionIndex = i;
          selectionSprite->x = (sprite->x + (sprite->src.w / 2)) - (selectionSprite->src.w / 2);
          selectionSprite->y = (sprite->y + (sprite->src.h / 2)) - (selectionSprite->src.h / 2);
          Text__set_text(selectedPotionText, colorNames[potion->id]);
        }
      }
    }

    // clicked on cauldron?

    // + click on cauldron to add selected potion to cauldron
    // + click on cauldron with no potion selected to reset cauldron to starting base color
    // + click on cauldron with selected empty potion bottle to fill with cauldron color

    if (Sprite__collides_with_point(cauldronSprite, mouse->x, mouse->y)) {
      printf("clicked on cauldron: ");
      Text__set_text(mixedColorText, "");

      if (witchSprite->texture != witchTexture2) {
        Sprite__change_texture(witchSprite, witchTexture2, 0);
      }
      witchSprite->y = cauldronSprite->y + (cauldronSprite->src.h - 24);
      witchSprite->x = cauldronSprite->x + ((cauldronSprite->src.w - witchSprite->src.w) / 2);

      if (cauldronColor == BAD_MIX) {
        printf("dumping failed mix from cauldron\n");
        play_sfx(sfxPourPotion, 0.6f);
        cauldronColor = basePotions[startingCauldronColor]->id;
        Potion* cauldronPotion = allPotions[cauldronColor];
        SDL_SetTextureColorMod(cauldronFillSprite->texture, cauldronPotion->r, cauldronPotion->g, cauldronPotion->b);
        cauldronFillSprite->visible = SPRITE_VISIBLE;
      } else {
        // potion selected?
        if (selectedPotionIndex != -1) {
          Sprite* selectedPotionSprite = potionSprite[selectedPotionIndex];
          Potion* selectedPotion = (Potion*)selectedPotionSprite->data;

          // is the bottle empty?
          if (selectedPotionSprite->state == BOTTLE_EMPTY) {
            printf("filling selected empty potion bottle with cauldron color\n");
            play_sfx(sfxPourPotion, 0.6f);
            Potion* cauldronPotion = allPotions[cauldronColor];
            SDL_SetTextureColorMod(selectedPotionSprite->texture, cauldronPotion->r, cauldronPotion->g, cauldronPotion->b);
            selectedPotion->r = cauldronPotion->r;
            selectedPotion->g = cauldronPotion->g;
            selectedPotion->b = cauldronPotion->b;
            selectedPotion->id = cauldronPotion->id;
            selectedPotionSprite->visible = SPRITE_VISIBLE;
          } else {
            printf("adding selected potion to cauldron...\n");
            selectedPotionSprite->state = BOTTLE_EMPTY;
            selectedPotionSprite->visible = SPRITE_HIDDEN;
            play_sfx(sfxPourPotion, 0.6f);
            int result = mix_colors(cauldronColor, selectedPotion->id);
            if (result != BAD_MIX) {
              play_sfx(sfxMixSuccess, 0.8f);
              cauldronColor = result;
              Potion* cauldronPotion = allPotions[cauldronColor];
              SDL_SetTextureColorMod(cauldronFillSprite->texture, cauldronPotion->r, cauldronPotion->g, cauldronPotion->b);
              printf("SUCCESS! Got %s\n", colorNames[result]);

              Text__set_text(mixedColorText, colorNames[result]);

              if (result == spellbookColor) {
                printf("\nCREATED %s! CLEARED LEVEL!\n", colorNames[result]);
              }
            } else {
              play_sfx(sfxMixFailed, 0.8f);
              cauldronColor = BAD_MIX;
              cauldronFillSprite->visible = SPRITE_HIDDEN;
              // SDL_SetTextureColorMod(cauldronFillSprite->texture, 0xff, 0xff, 0xff);
              printf("FAILED! click on cauldron to reset\n");
            }
          }

          // deselect
          selectedPotionIndex = -1;
          selectionSprite->x = -selectionSprite->src.w;
          selectionSprite->y = -selectionSprite->src.h;
        } else {
          play_sfx(sfxPourPotion, 0.6f);
          // no potion selected
          printf("resetting to starting base color\n");
          cauldronColor = basePotions[startingCauldronColor]->id;
          Potion* cauldronPotion = allPotions[cauldronColor];
          SDL_SetTextureColorMod(cauldronFillSprite->texture, cauldronPotion->r, cauldronPotion->g, cauldronPotion->b);
          cauldronFillSprite->visible = SPRITE_VISIBLE;
        }
      }
    }

    // clicked on spellbook?
    if (Sprite__collides_with_point(spellbookSprite, mouse->x, mouse->y)) {
      printf("clicked on spellbook\n");
      play_sfx(sfxMenuClick, 0.5f);
    }

    // clicked on menu button?
    if (Sprite__collides_with_point(menuButtonSprite, mouse->x, mouse->y)) {
      printf("TODO: show pause menu\n");
      play_sfx(sfxMenuClick, 0.5f);
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

  Text__render(targetColorText);
  Text__render(mixedColorText);
  Text__render(selectedPotionText);
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

void Sprite__change_texture(Sprite* sprite, SDL_Texture* texture, SDL_Rect* src) {
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
}

SDL_Rect dst;
void Sprite__render(Sprite* sprite) {
  if (sprite->visible == SPRITE_HIDDEN) {
    return;
  }

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
