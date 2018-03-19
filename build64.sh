#!/bin/bash

function build_64_bit_executable() {
  INCP="-I/usr/local/Cellar/mingw-w64/5.0.3_2/toolchain-x86_64/x86_64-w64-mingw32/include -I./external/SDL2/64/include/SDL2"
  LIBP="-L/usr/local/Cellar/mingw-w64/5.0.3_2/toolchain-x86_64/x86_64-w64-mingw32/lib -L./external/SDL2/64/lib"
  FLAGS="-w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer"
  EXE="dist/x86_64/bin/game_x86_64.exe"
  SRC=`find ./src -name *.c`
  x86_64-w64-mingw32-gcc $SRC $INCP $LIBP -D PRODUCTION $FLAGS -o $EXE
}
