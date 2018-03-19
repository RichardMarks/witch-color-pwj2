#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "scenes.h"
#include "dimmer.h"

void destroy_game() {
   if (!currentGamePtr) {
    fprintf(stderr, "Error occurred in destroy_game()\nUnable to destroy game because: currentGamePtr is NULL!\n");
    return;
  }

  /* do your game cleanup here */
  destroy_play_scene();
  destroy_title_scene();
  destroy_credits_scene();

  destroy_dimmer();

  TTF_Quit();

  Mix_CloseAudio();
  while (Mix_Init(0)) {
    Mix_Quit();
  }

  SDL_DestroyRenderer(mainRendererPtr);
  SDL_DestroyWindow(mainWindowPtr);

  SDL_Quit();

  currentGamePtr = NULL;

#ifndef PRODUCTION
  printf("executing destroy_game() -> currentGamePtr de-initialized.\n");
#endif
}
