#include "game.h"
#include "scenes.h"
#include "sprite.h"

SDL_Texture* creditsTexture = 0;
SDL_Texture* creditsBackTexture = 0;

void init_credits_scene() {
  printf("init credits\n");

  creditsTexture = load_texture("../data/ui/CreditsText.png");
  creditsBackTexture = load_texture("../data/backgrounds/CreditsScreenfill.png");
}

void destroy_credits_scene() {
  printf("destroy credits\n");
  kill_texture(creditsTexture);
  kill_texture(creditsBackTexture);
}

void enter_credits_scene() {
  printf("entering credits scene\n");
  Mouse* mouse = &currentGamePtr->mouse;
  if (mouse->state == SDL_PRESSED) {
    mouse->state = SDL_RELEASED;
  }
}

void exit_credits_scene() {
  printf("exiting credits scene\n");
  currentScenePtr->id = 0;
  currentScenePtr->init = &init_title_scene;
  currentScenePtr->destroy = &destroy_title_scene;
  currentScenePtr->enter = &enter_title_scene;
  currentScenePtr->exit = &exit_title_scene;
  currentScenePtr->update = &update_title_scene;
  currentScenePtr->render = &render_title_scene;
  currentScenePtr->enter();
}

int credits_mouseDown = 0;
void update_credits_scene(float dt) {
  Input* input = &currentGamePtr->inputs;
  Mouse* mouse = &currentGamePtr->mouse;
  if (mouse->state == SDL_PRESSED && credits_mouseDown == 0) {
    credits_mouseDown = 1;
  } else if (mouse->state != SDL_PRESSED && credits_mouseDown == 1) {
    credits_mouseDown = 0;
    exit_credits_scene();
  }
}

void render_credits_scene() {
  SDL_RenderCopy(mainRendererPtr, creditsBackTexture, 0, 0);
  SDL_Rect dst;
  int w, h;
  SDL_QueryTexture(creditsTexture, 0, 0, &w, &h);
  dst.w = w;
  dst.h = h;
  dst.x = (SCREEN_WIDTH - w) / 2;
  dst.y = (SCREEN_HEIGHT - h) / 2;
  SDL_RenderCopy(mainRendererPtr, creditsTexture, 0, &dst);
}
