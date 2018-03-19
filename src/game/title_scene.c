#include "game.h"
#include "scenes.h"
#include "sprite.h"

SDL_Texture* title_bgTexture = 0;
SDL_Texture* title_logoTexture = 0;
SDL_Texture* title_playButtonTexture = 0;
SDL_Texture* title_creditsButtonTexture = 0;
SDL_Texture* title_exitButtonTexture = 0;

#define BG_LAYER 0
#define MAX_SPRITES 4
Sprite title_sprites[MAX_SPRITES];
int title_numSprites = 0;

Sprite* title_logoSprite = 0;
Sprite* title_playButtonSprite = 0;
Sprite* title_exitButtonSprite = 0;
Sprite* title_creditsButtonSprite = 0;

void init_title_scene() {
  printf("init title\n");

  title_bgTexture = load_texture("../data/backgrounds/TitleScreen.png");
  title_logoTexture = load_texture("../data/sprites/Logo.png");
  title_playButtonTexture = load_texture("../data/ui/Play.png");
  title_creditsButtonTexture = load_texture("../data/ui/Credits.png");
  title_exitButtonTexture = load_texture("../data/ui/Exit.png");

  title_numSprites = 0;
  Sprite__init(&title_sprites[title_numSprites], title_bgTexture, 0, BG_LAYER); title_numSprites += 1;
  title_logoSprite = Sprite__init(&title_sprites[title_numSprites], title_logoTexture, 0, BG_LAYER); title_numSprites += 1;
  title_playButtonSprite = Sprite__init(&title_sprites[title_numSprites], title_playButtonTexture, 0, BG_LAYER); title_numSprites += 1;
  title_creditsButtonSprite = Sprite__init(&title_sprites[title_numSprites], title_creditsButtonTexture, 0, BG_LAYER); title_numSprites += 1;
  title_exitButtonSprite = Sprite__init(&title_sprites[title_numSprites], title_exitButtonTexture, 0, BG_LAYER); title_numSprites += 1;
}

void destroy_title_scene() {
  printf("destroy title\n");
  kill_texture(title_bgTexture);
  kill_texture(title_logoTexture);
  kill_texture(title_playButtonTexture);
  kill_texture(title_creditsButtonTexture);
  kill_texture(title_exitButtonTexture);
}

void enter_title_scene() {
  printf("entering title scene\n");
  title_logoSprite->y = 19;
  title_logoSprite->x = (SCREEN_WIDTH - title_logoSprite->src.w) / 2;

  title_playButtonSprite->x = (SCREEN_WIDTH - title_playButtonSprite->src.w) / 2;
  title_playButtonSprite->y = SCREEN_HEIGHT - (title_playButtonSprite->src.h + 38);

  title_creditsButtonSprite->x = 11;
  title_creditsButtonSprite->y = SCREEN_HEIGHT - (2 + title_creditsButtonSprite->src.h);

  title_exitButtonSprite->x = SCREEN_WIDTH - (11 + title_exitButtonSprite->src.w);
  title_exitButtonSprite->y = SCREEN_HEIGHT - (2 + title_exitButtonSprite->src.h);
}
int toCredits = 0;
void exit_title_scene() {
  printf("exiting title scene\n");
  if (toCredits) {
    printf("TODO: credits!\n");
    currentScenePtr->id = 2;
    currentScenePtr->init = &init_credits_scene;
    currentScenePtr->destroy = &destroy_credits_scene;
    currentScenePtr->enter = &enter_credits_scene;
    currentScenePtr->exit = &exit_credits_scene;
    currentScenePtr->update = &update_credits_scene;
    currentScenePtr->render = &render_credits_scene;
    currentScenePtr->enter();
  } else {
    currentScenePtr->id = 1;
    currentScenePtr->init = &init_play_scene;
    currentScenePtr->destroy = &destroy_play_scene;
    currentScenePtr->enter = &enter_play_scene;
    currentScenePtr->exit = &exit_play_scene;
    currentScenePtr->update = &update_play_scene;
    currentScenePtr->render = &render_play_scene;
    currentScenePtr->enter();
  }
}

int title_mouseDown = 0;
void update_title_scene(float dt) {
  Input* input = &currentGamePtr->inputs;
  Mouse* mouse = &currentGamePtr->mouse;
  if (mouse->state == SDL_PRESSED && title_mouseDown == 0) {
    title_mouseDown = 1;
    if (Sprite__collides_with_point(title_playButtonSprite, mouse->x, mouse->y)) {
      toCredits = 0;
      exit_title_scene();
    } else if (Sprite__collides_with_point(title_creditsButtonSprite, mouse->x, mouse->y)) {
      toCredits = 1;
      exit_title_scene();
    } else if (Sprite__collides_with_point(title_exitButtonSprite, mouse->x, mouse->y)) {
      currentGamePtr->inputs.quit = 1;
    }
  } else if (mouse->state != SDL_PRESSED && title_mouseDown == 1) {
    title_mouseDown = 0;
  }

  for (int i = 0; i < title_numSprites; i += 1) {
    Sprite* sprite = &title_sprites[i];
    sprite->x += sprite->xv * dt;
    sprite->y += sprite->yv * dt;
  }
}

void render_title_scene() {
  for (int i = 0; i < title_numSprites; i += 1) {
    Sprite* sprite = &title_sprites[i];
    Sprite__render(sprite);
  }
}
