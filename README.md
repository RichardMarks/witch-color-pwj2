# SDL2 Project Template

This is a really basic SDL2 project template for the `C` programming language.

Included is some boilerplate code to get you up and running quickly, and a Makefile to build.

It is intended for use on the `*nix` operating systems so linux, OSX, etc...

## What do we have here?

+ `Makefile` - use `make` to build and `make clean` to delete built files between major builds
+ `src/main.c` - program entry point. Creates an instance of the `Game` struct and calls the `init_game`, `run_game`, and `destroy_game` functions.
+ `src/game/init_game.c` - initializes the game
+ `src/game/run_game.c` - runs the game
+ `src/game/destroy_game.c` - destroys (cleans up allocations of) the game
+ `src/game/game.h` - master game header include file - defines the `Game` struct and function prototypes for the other .c files.

## What does it do?

Currently, nothing but opens up a window that is `640x480` in size and clears the window to a nice blue color while waiting for you to press the escape key on your keyboard or just close the window.

## Why do I need this?

You don't need it. But it's here if you want to quickly start up an SDL2 project in C and not have to think about how to do so.

## LICENSE
MIT License (c) 2018, Richard Marks
See the included LICENSE.md file for more details.
