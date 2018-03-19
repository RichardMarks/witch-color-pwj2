#!/bin/bash

function build_32_bit_executable() {
  INCP="-I/usr/local/Cellar/mingw-w64/5.0.3_2/toolchain-i686/i686-w64-mingw32/include -I./external/SDL2/32/include/SDL2"
  LIBP="-L/usr/local/Cellar/mingw-w64/5.0.3_2/toolchain-i686/i686-w64-mingw32/lib -L./external/SDL2/32/lib"
  FLAGS="-w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer"
  EXE="dist/i686/bin/game_i686.exe"
  SRC=`find ./src -name *.c`
  i686-w64-mingw32-gcc $SRC $INCP $LIBP -D PRODUCTION $FLAGS -o $EXE
}
