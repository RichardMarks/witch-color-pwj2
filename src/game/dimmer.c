#include "game.h"
#include "dimmer.h"

SDL_Texture* dimmerTexture = 0;
SDL_Rect dimmerRect;

float dimmerOpacity = 0.0f;
int showDimmer = 0;

void init_dimmer(unsigned int color) {
  // printf("init dimmer 0x%08X\n", color);
  if (!dimmerTexture) {
    dimmerTexture = SDL_CreateTexture(mainRendererPtr, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, 2, 2);
    if (!dimmerTexture) {
      SDL_Log("Error occurred in init_dimmer()\n%s", SDL_GetError());
    }
  }
  u32 dimmerFill[] = { color, color, color, color };
  SDL_UpdateTexture(dimmerTexture, 0, &dimmerFill, 2 * sizeof(u32));
  SDL_SetTextureBlendMode(dimmerTexture, SDL_BLENDMODE_BLEND);
  dimmerRect.x = 0;
  dimmerRect.y = 0;
  dimmerRect.w = SCREEN_WIDTH;
  dimmerRect.h = SCREEN_HEIGHT;
  showDimmer = 0;
}

void destroy_dimmer() {
  kill_texture(dimmerTexture);
}

void show_dimmer(float opacity) {
  showDimmer = 1;
  dimmerOpacity = opacity;
  int alpha = (int)(255.0f * opacity);
  SDL_SetTextureAlphaMod(dimmerTexture, alpha);
}

void hide_dimmer() {
  showDimmer = 0;
}

void render_dimmer() {
  if (showDimmer) {
    SDL_RenderCopy(mainRendererPtr, dimmerTexture, 0, &dimmerRect);
  }
}
