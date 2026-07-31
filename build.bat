@echo off
echo Building PixelCity...
if not exist build mkdir build
gcc src/main.c -o build/PixelCity.exe -lfreeglut -lopengl32 -lglu32 -lm -O2 -Wall
if %errorlevel% equ 0 (echo Success!) else (echo FAILED!)
pause
