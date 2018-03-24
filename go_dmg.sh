#!/bin/bash
CC_ERR="\x1b[31;4m"
CC_OK="\x1b[32;1m"
CC_RESET="\x1b[0m"

# AppName.app
# AppName.app/Contents
# AppName.app/Contents/Info.plist
# AppName.app/Contents/MacOS/
# AppName.app/Contents/Resources/
# AppName.app/Contents/MacOS/AppName
# AppName.app/Contents/MacOS/*.dylib
# AppName.app/Contents/Resources/AppName.icns|*.png|*.ogg|etc...

EXEC_PATH="./bin/witch-color"
APP_NAME="WitchColorJamEdition"
BUNDLE_NAME="${APP_NAME}.app"
BUILD_DIR="./dmg"
CONTENTS_DIR="${BUILD_DIR}/${BUNDLE_NAME}/Contents"
EXEC_DIR="${CONTENTS_DIR}/MacOS"
RES_DIR="${CONTENTS_DIR}/Resources"

echo -e "${CC_OK}Preparing .app directory...${CC_RESET}"
rm -rf "${BUILD_DIR}/${BUNDLE_NAME}"
mkdir -p $EXEC_DIR
mkdir -p $RES_DIR

echo -e "${CC_OK}Copying executable...${CC_RESET}"
cp $EXEC_PATH $EXEC_DIR/$APP_NAME

echo -e "${CC_OK}Copying Info.plist...${CC_RESET}"
cp ./Info.plist $CONTENTS_DIR/

echo -e "${CC_OK}Copying dylibs from system to local working directory...${CC_RESET}"
rm -f ./dmg/dylibs/*
cp /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib ./dmg/dylibs/
cp /usr/local/opt/sdl2_mixer/lib/libSDL2_mixer-2.0.0.dylib ./dmg/dylibs/
cp /usr/local/opt/sdl2_image/lib/libSDL2_image-2.0.0.dylib ./dmg/dylibs/
cp /usr/local/opt/sdl2_ttf/lib/libSDL2_ttf-2.0.0.dylib ./dmg/dylibs/
cp /usr/local/opt/libmodplug/lib/libmodplug.1.dylib ./dmg/dylibs/
cp /usr/local/opt/libvorbis/lib/libvorbisfile.3.dylib ./dmg/dylibs/
cp /usr/local/opt/libvorbis/lib/libvorbis.0.dylib ./dmg/dylibs/
cp /usr/local/opt/libpng/lib/libpng16.16.dylib ./dmg/dylibs/
cp /usr/local/opt/jpeg/lib/libjpeg.9.dylib ./dmg/dylibs/
cp /usr/local/opt/libtiff/lib/libtiff.5.dylib ./dmg/dylibs/
cp /usr/local/opt/webp/lib/libwebp.7.dylib ./dmg/dylibs/
cp /usr/local/opt/freetype/lib/libfreetype.6.dylib ./dmg/dylibs/
cp /usr/local/opt/libogg/lib/libogg.0.dylib ./dmg/dylibs/

echo -e "${CC_OK}Copying dylibs to app bundle executable directory...${CC_RESET}"
chown `whoami` ./dmg/dylibs/*
chmod 755 ./dmg/dylibs/*
cp ./dmg/dylibs/* $EXEC_DIR/

echo -e "${CC_OK}Copying resources...${CC_RESET}"
cp -R ./data $RES_DIR/

echo -e "${CC_OK}Editing ${APP_NAME} dylib paths 1 of 4...${CC_RESET}"
install_name_tool -change /usr/local/opt/sdl2_image/lib/libSDL2_image-2.0.0.dylib @executable_path/libSDL2_image-2.0.0.dylib $EXEC_DIR/$APP_NAME
echo -e "${CC_OK}Editing ${APP_NAME} dylib paths 2 of 4...${CC_RESET}"
install_name_tool -change /usr/local/opt/sdl2_ttf/lib/libSDL2_ttf-2.0.0.dylib @executable_path/libSDL2_ttf-2.0.0.dylib $EXEC_DIR/$APP_NAME
echo -e "${CC_OK}Editing ${APP_NAME} dylib paths 3 of 4...${CC_RESET}"
install_name_tool -change /usr/local/opt/sdl2_mixer/lib/libSDL2_mixer-2.0.0.dylib @executable_path/libSDL2_mixer-2.0.0.dylib $EXEC_DIR/$APP_NAME
echo -e "${CC_OK}Editing ${APP_NAME} dylib paths 4 of 4...${CC_RESET}"
install_name_tool -change /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib @executable_path/libSDL2-2.0.0.dylib $EXEC_DIR/$APP_NAME

echo -e "${CC_OK}Editing SDL2_mixer dylib paths 1 of 4...${CC_RESET}"
install_name_tool -change /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib @executable_path/libSDL2-2.0.0.dylib $EXEC_DIR/libSDL2_mixer-2.0.0.dylib
echo -e "${CC_OK}Editing SDL2_mixer dylib paths 2 of 4...${CC_RESET}"
install_name_tool -change /usr/local/opt/libmodplug/lib/libmodplug.1.dylib @executable_path/libmodplug.1.dylib $EXEC_DIR/libSDL2_mixer-2.0.0.dylib
echo -e "${CC_OK}Editing SDL2_mixer dylib paths 3 of 4...${CC_RESET}"
install_name_tool -change /usr/local/opt/libvorbis/lib/libvorbisfile.3.dylib @executable_path/libvorbisfile.3.dylib $EXEC_DIR/libSDL2_mixer-2.0.0.dylib
echo -e "${CC_OK}Editing SDL2_mixer dylib paths 4 of 4...${CC_RESET}"
install_name_tool -change /usr/local/opt/libvorbis/lib/libvorbis.0.dylib @executable_path/libvorbis.0.dylib $EXEC_DIR/libSDL2_mixer-2.0.0.dylib

echo -e "${CC_OK}Editing SDL2_image dylib paths 1 of 5...${CC_RESET}"
install_name_tool -change /usr/local/opt/libpng/lib/libpng16.16.dylib @executable_path/libpng16.16.dylib $EXEC_DIR/libSDL2_image-2.0.0.dylib
echo -e "${CC_OK}Editing SDL2_image dylib paths 2 of 5...${CC_RESET}"
install_name_tool -change /usr/local/opt/jpeg/lib/libjpeg.9.dylib @executable_path/libjpeg.9.dylib $EXEC_DIR/libSDL2_image-2.0.0.dylib
echo -e "${CC_OK}Editing SDL2_image dylib paths 3 of 5...${CC_RESET}"
install_name_tool -change /usr/local/opt/libtiff/lib/libtiff.5.dylib @executable_path/libtiff.5.dylib $EXEC_DIR/libSDL2_image-2.0.0.dylib
echo -e "${CC_OK}Editing SDL2_image dylib paths 4 of 5...${CC_RESET}"
install_name_tool -change /usr/local/opt/webp/lib/libwebp.7.dylib @executable_path/libwebp.7.dylib $EXEC_DIR/libSDL2_image-2.0.0.dylib
echo -e "${CC_OK}Editing SDL2_image dylib paths 5 of 5...${CC_RESET}"
install_name_tool -change /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib @executable_path/libSDL2-2.0.0.dylib $EXEC_DIR/libSDL2_image-2.0.0.dylib

echo -e "${CC_OK}Editing SDL2_ttf dylib paths 1 of 2...${CC_RESET}"
install_name_tool -change /usr/local/opt/freetype/lib/libfreetype.6.dylib @executable_path/libfreetype.6.dylib $EXEC_DIR/libSDL2_ttf-2.0.0.dylib
echo -e "${CC_OK}Editing SDL2_ttf dylib paths 2 of 2...${CC_RESET}"
install_name_tool -change /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib @executable_path/libSDL2-2.0.0.dylib $EXEC_DIR/libSDL2_ttf-2.0.0.dylib

echo -e "${CC_OK}Editing vorbisfile dylib paths 1 of 2...${CC_RESET}"
install_name_tool -change /usr/local/Cellar/libvorbis/1.3.5_1/lib/libvorbis.0.dylib @executable_path/libvorbis.0.dylib $EXEC_DIR/libvorbisfile.3.dylib
echo -e "${CC_OK}Editing vorbisfile dylib paths 2 of 2...${CC_RESET}"
install_name_tool -change /usr/local/opt/libogg/lib/libogg.0.dylib @executable_path/libogg.0.dylib $EXEC_DIR/libvorbisfile.3.dylib

echo -e "${CC_OK}Editing vorbis dylib paths 1 of 1...${CC_RESET}"
install_name_tool -change /usr/local/opt/libogg/lib/libogg.0.dylib @executable_path/libogg.0.dylib $EXEC_DIR/libvorbis.0.dylib

echo -e "${CC_OK}Editing tiff dylib paths 1 of 1...${CC_RESET}"
install_name_tool -change /usr/local/opt/jpeg/lib/libjpeg.9.dylib @executable_path/libjpeg.9.dylib $EXEC_DIR/libtiff.5.dylib

echo -e "${CC_OK}Editing freetype dylib paths 1 of 1...${CC_RESET}"
install_name_tool -change /usr/local/opt/libpng/lib/libpng16.16.dylib @executable_path/libpng16.16.dylib $EXEC_DIR/libfreetype.6.dylib

echo -e "${CC_OK}Preparing DMG image directory...${CC_RESET}"
rm -rf ././dmg/image
mkdir -p ./dmg/image

echo -e "${CC_OK}Copying bundle to DMG image...${CC_RESET}"
cp -R "${BUILD_DIR}/${BUNDLE_NAME}" ./dmg/image/

echo -e "${CC_OK}Copying docs to DMG image...${CC_RESET}"
cp docs/*.md ./dmg/image/

echo -e "${CC_OK}Creating mountable DMG...${CC_RESET}"
hdiutil create -size 10m -fs HFS+ -volname "Witch Color Jam Edition" -srcfolder ./dmg/image -format UDZO -o ./dmg/WitchColorJamEdition-OSX.dmg

echo -e "${CC_OK}DONE${CC_RESET}"
