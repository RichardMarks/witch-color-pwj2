#include <stdio.h>
#include <stdlib.h>
#include "game.h"

static float epochTime() {
  return (float)SDL_GetTicks() * 0.001f;
}

#ifndef max
#define max(a,b) ((a) > (b) ? (b) : (a))
#endif

void quit_game() {
  currentGamePtr->gameState = 0;
}

int run_game(Game* gamePtr) {
  if (!gamePtr) {
    fprintf(stderr, "Error occurred in run_game()\nUnable to run game because: gamePtr is NULL!\n");
    return -1;
  }

#ifndef PRODUCTION
  printf("executing run_game()\n");
#endif

  u8 hidden = 0;
  float lastTime = epochTime();
  float newTime = 0;
  float deltaTime = 0.0f;

  SDL_Event event;
  while (gamePtr->gameState) {
    if (hidden) {
      SDL_Delay(max(0, (int)(16 - (epochTime() - lastTime) * 1000)));
    }

    if (gamePtr->paused == 0) {
      newTime = epochTime();
      if (newTime - lastTime < 1) {
        deltaTime = (newTime - lastTime) * gamePtr->timeScale;
        /* update game here */
      }
      lastTime = newTime;
    }

    if (hidden == 0) {
      SDL_SetRenderDrawColor(mainRendererPtr, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderClear(mainRendererPtr);
      /* render game here */
      SDL_RenderPresent(mainRendererPtr);
    }

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit_game();
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        gamePtr->inputs.confirm = 1;
      } else if (event.type == SDL_MOUSEBUTTONUP) {
        gamePtr->inputs.confirm = 0;
      } else if (event.type == SDL_KEYDOWN) {
        /*
         w or up -> up
         s or down -> down
         a or left -> left
         d or right -> right
         space or enter -> confirm
         esc -> cancel
         q -> quit
        */
        if (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.scancode == SDL_SCANCODE_UP) {
          gamePtr->inputs.up = 1;
        } else if (event.key.keysym.scancode == SDL_SCANCODE_S || event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
          gamePtr->inputs.down = 1;
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_A || event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
          gamePtr->inputs.left = 1;
        } else if (event.key.keysym.scancode == SDL_SCANCODE_D || event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
          gamePtr->inputs.right = 1;
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE || event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
          gamePtr->inputs.confirm = 1;
        } else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
          gamePtr->inputs.cancel = 1;
        } else if (event.key.keysym.scancode == SDL_SCANCODE_Q) {
          gamePtr->inputs.quit = 1;
        }
      } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.scancode == SDL_SCANCODE_UP) {
          gamePtr->inputs.up = 0;
        } else if (event.key.keysym.scancode == SDL_SCANCODE_S || event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
          gamePtr->inputs.down = 0;
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_A || event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
          gamePtr->inputs.left = 0;
        } else if (event.key.keysym.scancode == SDL_SCANCODE_D || event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
          gamePtr->inputs.right = 0;
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE || event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
          gamePtr->inputs.confirm = 0;
        } else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
          gamePtr->inputs.cancel = 0;
        } else if (event.key.keysym.scancode == SDL_SCANCODE_Q) {
          gamePtr->inputs.quit = 0;
        }
      } else if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_HIDDEN || event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
          hidden = 1;
        } else if (event.window.event == SDL_WINDOWEVENT_SHOWN || event.window.event == SDL_WINDOWEVENT_RESTORED) {
          hidden = 0;
        }
      }
    }

    if (gamePtr->inputs.quit) {
      quit_game();
    }
  }

  return 0;
}
