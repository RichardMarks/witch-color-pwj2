#include "game.h"

SDL_Texture* load_texture(char* filename) {
  SDL_Surface* surface = IMG_Load(filename);
  if (!surface) {
    SDL_Log("Error occurred in load_texture()\nUnable to load %s\n%s\n", filename, SDL_GetError());
    return 0;
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(mainRendererPtr, surface);
  if (!texture) {
    SDL_FreeSurface(surface);
    SDL_Log("Error occurred in load_texture()\nUnable to create texture from surface\n%s\n", SDL_GetError());
    return 0;
  }
  SDL_FreeSurface(surface);
  return texture;
}

TTF_Font* load_font(char* filename, int fontSize) {
  TTF_Font* font = TTF_OpenFont(filename, fontSize);
  if (!font) {
    SDL_Log("Error occurred in load_font()\nUnable to load font %s\n%s\n", filename, TTF_GetError());
    return 0;
  }
  return font;
}

Mix_Music* load_music(char* filename) {
  Mix_Music* music = Mix_LoadMUS(filename);
  if (!music) {
    SDL_Log("Error occurred in load_music()\nUnable to load music %s\n%s\n", filename, Mix_GetError());
    return 0;
  }
  return music;
}

Mix_Chunk* load_sfx(char* filename) {
  Mix_Chunk* sfx = Mix_LoadWAV(filename);
  if (!sfx) {
    SDL_Log("Error occurred in load_sfx()\nUnable to load sfx %s\n%s\n", filename, Mix_GetError());
    return 0;
  }
  return sfx;
}
