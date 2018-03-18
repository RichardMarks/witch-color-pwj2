#include "game.h"

SDL_Texture* load_texture(char* filename) {
  SDL_Surface* surface = IMG_Load(filename);
  if (!surface) {
    SDL_Log("Error occurred in load_texture()\nUnable to load %s\n%s", filename, SDL_GetError());
    return 0;
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(mainRendererPtr, surface);
  if (!texture) {
    SDL_FreeSurface(surface);
    SDL_Log("Error occurred in load_texture()\nUnable to create texture from surface\n%s", SDL_GetError());
    return 0;
  }
  SDL_FreeSurface(surface);
  return texture;
}

TTF_Font* load_font(char* filename, int fontSize) {
  TTF_Font* font = TTF_OpenFont(filename, fontSize);
  if (!font) {
    SDL_Log("Error occurred in load_font()\nUnable to load font %s\n%s", filename, TTF_GetError());
    return 0;
  }
  return font;
}
