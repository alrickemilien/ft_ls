#!/usr/bin/env bash

#
# What does this script ?
#
# Create the files:
#    ~/.fonts/icons-in-terminal.ttf
#    ~/.config/fontconfig/conf.d/30-icons.conf
#
# Create the directory:
#    ~/.local/share/icons-in-terminal
# or $XDG_DATA_HOME/icons-in-terminal (if $XDG_DATA_HOME is set)
#
# Copy the built files in the created directory
#
# Run the command:
# fc-cache
#

# Create local fonts directory
mkdir -p ./fonts/

# Download Devicons
curl "https://codeload.github.com/konpa/devicon/zip/master" > master.zip
unzip "master.zip" -d "./devicons"
rm -rf "master.zip"
mv ./devicons/devicon-master/fonts/devicon.ttf ./fonts/devicon.ttf
rm -rf devicons

set -xe

FONT_DIRECTORY=${HOME}/.fonts/

if [ `uname` = "Darwin" ]; then
  FONT_DIRECTORY=${HOME}/Library/Fonts/
fi

mkdir -p ${FONT_DIRECTORY}
cp ./fonts/*.ttf ${FONT_DIRECTORY}

# run fc-cache -fv ~/.fonts to let freetype2 know of those fonts
if [ `uname` != "Darwin" ]; then
  fc-cache -fvr --really-force ${FONT_DIRECTORY}
fi

set +xe

echo -e "\n${YELLOW}Recommended additional step:"
echo "Check that the font(s) you are using in your terminal(s) is listed and remove all the others lines"
echo -e "\n${NORMAL}Font successfully installed. :)"
