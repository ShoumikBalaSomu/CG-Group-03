#!/bin/bash
mkdir -p build
gcc src/main.c -o build/PixelCity -lfreeglut -lopengl32 -lglu32 -lm -O2 -Wall
