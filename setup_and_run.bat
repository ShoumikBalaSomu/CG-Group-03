@echo off
echo === PixelCity - CG Group 03 ===
gcc --version >nul 2>&1
if %errorlevel% neq 0 (echo Install MSYS2! & pause & exit /b 1)
if not exist build mkdir build
gcc src/main.c -o build/PixelCity.exe -lfreeglut -lopengl32 -lglu32 -lm -O2 -Wall
if %errorlevel% neq 0 (echo Install freeglut! & pause & exit /b 1)
echo Starting...
build/PixelCity.exe
