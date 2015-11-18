#!/bin/sh
export PROJECT_DIR=`pwd`
export XCODE_SUPPORT_DIR="$PROJECT_DIR/../../Support/XCode"

gcc -E -P  -I"$PROJECT_DIR/../../Sources"   "$XCODE_SUPPORT_DIR/myplc.c" | grep my_ |"$XCODE_SUPPORT_DIR/24u_plist_compiler.sh"

# Create the file Pckginfo
echo "BNDL????" > "$BUILD_DIR/$PKGINFO_PATH"


#sudo cp "$PROJECT_DIR/../../Output/Sync2APIDebug.fmplugin" "/Applications/FileMaker Pro 13 Advanced/Extensions"

