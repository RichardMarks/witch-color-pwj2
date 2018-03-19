#!/bin/bash

mkdir -p ./dmg/WitchColorJamEdition.app/Contents/{MacOS,Resources}

cp ./bin/witch-color ./dmg/WitchColorJamEdition.app/Contents/MacOS/WitchColorJamEdition
cp Info.plist ./dmg/WitchColorJamEdition.app/Contents/

cp -R ./data ./dmg/WitchColorJamEdition.app/Contents/Resources/
