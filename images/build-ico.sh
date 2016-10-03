#!/bin/bash

# builds the hanoi.ico-file from hanoi-icon.svg

# requires: inkscape, icotool

# create png-files from the svg:

EXPORTSIZE=16
inkscape --without-gui --file=hanoi-icon.svg --export-png=hanoi-w${EXPORTSIZE}.png --export-width=${EXPORTSIZE}
EXPORTSIZE=32
inkscape --without-gui --file=hanoi-icon.svg --export-png=hanoi-w${EXPORTSIZE}.png --export-width=${EXPORTSIZE}
EXPORTSIZE=64
inkscape --without-gui --file=hanoi-icon.svg --export-png=hanoi-w${EXPORTSIZE}.png --export-width=${EXPORTSIZE}
EXPORTSIZE=128
inkscape --without-gui --file=hanoi-icon.svg --export-png=hanoi-w${EXPORTSIZE}.png --export-width=${EXPORTSIZE}

# create the icon:
icotool --create --output hanoi.ico hanoi-w*.png
