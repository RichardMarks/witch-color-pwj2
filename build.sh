#!/bin/bash
CC_ERR="\x1b[31;4m"
CC_OK="\x1b[32;1m"
CC_RESET="\x1b[0m"
if [ `which i686-w64-mingw32-gcc` != "" ]; then
  echo -e "${CC_OK}MingW is installed. Excellent${CC_RESET}"
else
  echo -e "${CC_ERR}MingW not found. Installing with brew${CC_RESET}"
  brew install mingw-w64
fi

# prepare build directory
echo -e "${CC_OK}Preparing build directory...${CC_RESET}"
mkdir -p ./dist
mkdir -p ./dist/i686/bin
mkdir -p ./dist/x86_64/bin

# copy assets
echo -e "${CC_OK}Copying assets...${CC_RESET}"
cp -R ./data ./dist/i686
cp -R ./data ./dist/x86_64

# copy docs
echo -e "${CC_OK}Copying docs...${CC_RESET}"
cp -R ./docs/*.md ./dist/i686/
cp -R ./docs/*.md ./dist/x86_64/

# copy SDL binaries
echo -e "${CC_OK}Copying SDL binaries...${CC_RESET}"
cp -R ./external/SDL2/32/bin/*.dll ./dist/i686/bin
cp -R ./external/SDL2/64/bin/*.dll ./dist/x86_64/bin

# build exes
echo -e "${CC_OK}Building 32-bit binary...${CC_RESET}"
source ./build32.sh
build_32_bit_executable

echo -e "${CC_OK}Building 64-bit binary...${CC_RESET}"
source ./build64.sh
build_64_bit_executable

# and we are done
echo -e "${CC_OK}Building Finished.${CC_RESET}"
