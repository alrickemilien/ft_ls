#!/usr/bin/env bash

set -xe

rm -rf ./fonts/

FONT_DIRECTORY=${HOME}/.fonts/

if [ `uname` = "Darwin" ]; then
  FONT_DIRECTORY=${HOME}/Library/Fonts/
fi

rm -f ${FONT_DIRECTORYcons}/*.ttf

# run fc-cache -fv ~/.fonts to let freetype2 know of those fonts
if [ `uname` != "Darwin" ]; then
  fc-cache -fvr --really-force > /dev/null
fi

set +xe

echo "ttf uninstalled. Close all your terminal windows."
