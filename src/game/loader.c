#include "game.h"

char* res_path(char* filename) {
  char* basePath = SDL_GetBasePath();
  if (basePath) {
    int filenameLen = 0;
    int baseLen = 0;
    char* a = basePath;
    while (*a) { baseLen += 1; a += 1; }
    a = filename;
    while (*a) { filenameLen += 1; a += 1; }
    char* path = malloc(sizeof(char) * 2 + filenameLen + baseLen);
    int p = 0;
    a = basePath;
    while (*a) { path[p] = *a; p += 1; a += 1; }
    a = filename + 3;
    while (*a) { path[p] = *a; p += 1; a += 1; }
    path[p] = '\0';
    return path;
  } else {
    return 0;
  }
}

SDL_Texture* load_texture(char* filename) {
  char* resPath = res_path(filename);
  SDL_Surface* surface = 0;
  if (resPath) {
    surface = IMG_Load(resPath);
    free(resPath);
  } else {
    surface = IMG_Load(filename);
  }
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
  char* resPath = res_path(filename);
  TTF_Font* font = 0;
  if (resPath) {
    font = TTF_OpenFont(resPath, fontSize);
    free(resPath);
  } else {
    font = TTF_OpenFont(filename, fontSize);
  }
  // TTF_Font* font = TTF_OpenFont(filename, fontSize);
  if (!font) {
    SDL_Log("Error occurred in load_font()\nUnable to load font %s\n%s\n", filename, TTF_GetError());
    return 0;
  }
  return font;
}

Mix_Music* load_music(char* filename) {
  char* resPath = res_path(filename);
  Mix_Music* music = 0;
  if (resPath) {
    music = Mix_LoadMUS(resPath);
    free(resPath);
  } else {
    music = Mix_LoadMUS(filename);
  }
  // Mix_Music* music = Mix_LoadMUS(filename);
  if (!music) {
    SDL_Log("Error occurred in load_music()\nUnable to load music %s\n%s\n", filename, Mix_GetError());
    return 0;
  }
  return music;
}

Mix_Chunk* load_sfx(char* filename) {
  char* resPath = res_path(filename);
  Mix_Chunk* sfx = 0;
  if (resPath) {
    sfx = Mix_LoadWAV(resPath);
    free(resPath);
  } else {
    sfx = Mix_LoadWAV(filename);
  }
  // Mix_Chunk* sfx = Mix_LoadWAV(filename);
  if (!sfx) {
    SDL_Log("Error occurred in load_sfx()\nUnable to load sfx %s\n%s\n", filename, Mix_GetError());
    return 0;
  }
  return sfx;
}
