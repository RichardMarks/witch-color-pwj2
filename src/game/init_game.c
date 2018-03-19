#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "scenes.h"
#include "dimmer.h"

Game* currentGamePtr = NULL;
SDL_Window* mainWindowPtr = NULL;
SDL_Renderer* mainRendererPtr = NULL;

Scene currentScene;
Scene* currentScenePtr = NULL;

int init_game(Game* gamePtr, int cmdLineCount, char** cmdLine) {
  if (!gamePtr) {
    fprintf(stderr, "Error occurred in init_game()\nUnable to initialize game because: gamePtr is NULL!\n");
    return -1;
  }

  srand(time(0));

  gamePtr->cmdLineCount = cmdLineCount;
  gamePtr->cmdLine = cmdLine;
  gamePtr->gameState = 1;
  gamePtr->paused = 0;
  gamePtr->timeScale = 1.0f;
  memset(&gamePtr->inputs, 0, sizeof(Input));
  memset(&gamePtr->mouse, 0, sizeof(Mouse));

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    SDL_Log("Error occurred in init_game()\nUnable to initialize SDL2: %s", SDL_GetError());
    return -1;
  }

  mainWindowPtr = SDL_CreateWindow(
    "Witch Color :: PixelWeekendJam #2 - 03/17/2018",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
#if DEBUG
    SDL_WINDOW_RESIZABLE
#else
    SDL_WINDOW_FULLSCREEN_DESKTOP
#endif
  );

  if (!mainWindowPtr) {
    SDL_Log("Error occurred in init_game()\nUnable to create the main window: %s", SDL_GetError());
    return -1;
  }

  mainRendererPtr = SDL_CreateRenderer(
    mainWindowPtr,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE
  );

  if (!mainRendererPtr) {
    SDL_Log("Error occurred in init_game()\nUnable to create the main renderer: %s", SDL_GetError());
    return -1;
  }

  // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(mainRendererPtr, SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_MaximizeWindow(mainWindowPtr);

  currentGamePtr = gamePtr;

  int audioHz = 22050;
  unsigned short audioFormat = MIX_DEFAULT_FORMAT; // AUDIO_S16SYS
  int audioChannels = 2; // STEREO
  int audioChunkSize = 4096;
  if (Mix_OpenAudio(audioHz, audioFormat, audioChannels, audioChunkSize) == -1) {
    SDL_Log("Error occurred in init_game()\nUnable to open SDL mixer: %s\n", Mix_GetError());
    return -1;
  }

  int audioFlags = MIX_INIT_OGG;
  int audioInit = Mix_Init(audioFlags);
  if ((audioInit & audioFlags) != audioFlags) {
    SDL_Log("Error occurred in init_game()\nUnable to init SDL mixer: %s\n", Mix_GetError());
    return -1;
  }

  if (TTF_Init() == -1) {
    SDL_Log("Error occurred in init_game()\nUnable to init SDL TTF: %s\n", TTF_GetError());
    return -1;
  }

  currentScenePtr = &currentScene;
  currentScenePtr->id = 0;
  currentScenePtr->init = &init_title_scene;
  currentScenePtr->destroy = &destroy_title_scene;
  currentScenePtr->enter = &enter_title_scene;
  currentScenePtr->exit = &exit_title_scene;
  currentScenePtr->update = &update_title_scene;
  currentScenePtr->render = &render_title_scene;

#if 1
  currentScenePtr->id = 1;
  currentScenePtr->init = &init_play_scene;
  currentScenePtr->destroy = &destroy_play_scene;
  currentScenePtr->enter = &enter_play_scene;
  currentScenePtr->exit = &exit_play_scene;
  currentScenePtr->update = &update_play_scene;
  currentScenePtr->render = &render_play_scene;
#endif

  /* do your initialization here */
  init_dimmer(0xFF000000);
  init_title_scene();
  init_credits_scene();
  init_play_scene();
  currentScenePtr->enter();
  // enter_play_scene();

// #ifndef PRODUCTION
//   printf("executing init_game() -> currentGamePtr initialized.\n");
//   printf("Argument Count: %d\n", cmdLineCount);
//   printf("Arguments:\n");
//   int i = 0;
//   while (i < cmdLineCount) {
//     printf("  [%2d] = %s\n", i, cmdLine[i]);
//     i += 1;
//   }
// #endif

  return 0;
}
