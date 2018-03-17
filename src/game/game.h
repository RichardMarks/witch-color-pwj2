#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 1920

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern SDL_Window* mainWindowPtr;
extern SDL_Renderer* mainRendererPtr;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

typedef struct t_Input {
  unsigned char up;
  unsigned char down;
  unsigned char left;
  unsigned char right;
  unsigned char quit;
  unsigned char confirm;
  unsigned char cancel;
  unsigned char padding;
} Input;

/*
  a simple structure to hold game-related information
*/
typedef struct Game {
  /* number of arguments passed on the command line. (includes the program itself as the 0th element) */
  int cmdLineCount;

  /* actual array of arguments passed on the command line. program name is the 0th element */
  char** cmdLine;

  /* current game state */
  int gameState;

  int paused;
  float timeScale;

  Input inputs;
} Game;

/*
  global pointer to the game instance that has been init by init_game()
  destroy_game() will use this to clean up when the program's main() exits.
*/
extern Game* currentGamePtr;

extern int init_game(Game* gamePtr, int cmdLineCount, char** cmdLine);
extern int run_game(Game* gamePtr);
extern void destroy_game();

#endif
