# PixelCity - 2D Smart City Traffic Simulator

### Computer Graphics Lab Project | Group 03

![C](https://img.shields.io/badge/Language-C-blue)
![OpenGL](https://img.shields.io/badge/Graphics-OpenGL-green)
![Platform](https://img.shields.io/badge/Platform-Windows_MSYS2-orange)
![License](https://img.shields.io/badge/License-MIT-yellow)

*A real-world 2D city simulation featuring roads, buildings, vehicles, traffic systems,*
*day/night cycle, and animations -- all rendered using fundamental Computer Graphics algorithms.*

---

## Overview

**PixelCity** is a comprehensive 2D Smart City Traffic Simulator developed as a final lab project for the Computer Graphics course. It integrates **all fundamental CG algorithms** into a single, cohesive, real-world application.

The simulation features:
- Animated vehicles obeying traffic signals
- Automated 4-state traffic light system
- Dynamic day/night cycle with sun, moon, stars
- Buildings with illuminated windows at night
- Parks, trees, pond, flowers
- Animated train with smoke particles
- Rotating windmill (2D transformation)
- Drifting clouds and flying birds

---

## Algorithms Implemented

| # | Algorithm | Used For | Functions |
|---|-----------|----------|-----------|
| 1 | DDA Line Drawing | Road borders, park boundaries, sun rays | DDA(), DDAT() |
| 2 | Bresenham Line | Dashed markings, crosswalks, railway | Bres(), BresD() |
| 3 | Midpoint Circle | Roundabout, sun, wheels, traffic lights | MC(), MF(), MT() |
| 4 | 2D Transformations | Vehicle movement, windmill rotation | Tr(), Rt(), Sc() |
| 5 | Animation (Timer) | All moving objects, day/night cycle | Update(), Timer() |
| 6 | Shape Primitives | Buildings, vehicles, environment | Rect(), Tri() |

---

## Team Members

| # | Name | Registration ID | Contribution |
|---|------|----------------|--------------|
| 1 | **Shoumik Bala Somu** | 232-15-657 | DDA Algorithm, Road System, Project Lead |
| 2 | **Nusrat Jahan Nishi** | 232-15-480 | Bresenham Algorithm, Animation System |
| 3 | **Proma Dey** | 232-15-637 | Midpoint Circle, Roundabout, Traffic Lights |
| 4 | **Sharmin Islam Eity** | 232-15-435 | 2D Transformations, Windmill, Vehicles |
| 5 | **Afrin Maharin Shama** | 232-15-056 | Shapes, Buildings, Environment Design |

**Course:** Computer Graphics (CG)
**University:** Daffodil International University (DIU)
**Group:** 03 | **Semester:** Summer 2026

---

## How to Run (Windows + MSYS2 MINGW64)

### Prerequisites

1. Install MSYS2 from https://www.msys2.org/
2. Open MSYS2 MINGW64 terminal
3. Install: `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-freeglut`
4. Add to PATH: `C:\msys64\mingw64\bin`

### Quick Start

    # Method 1: Double-click setup_and_run.bat

    # Method 2: Command line
    git clone https://github.com/ShoumikBalaSomu/CG-Group-03.git
    cd CG-Group-03
    mkdir -p build
    gcc src/main.c -o build/PixelCity -lfreeglut -lopengl32 -lglu32 -lm
    ./build/PixelCity

    # Method 3: make && make run

### Verify Installation

    gcc --version
    ls /mingw64/lib | grep glut

---

## Controls

| Key | Action |
|-----|--------|
| P | Pause / Resume |
| R | Reset scene |
| N | Jump time (day/night) |
| UP/DOWN | Adjust time of day |
| ESC | Exit |

---

## Project Structure

    CG-Group-03/
    |-- src/main.c              # Complete source (single file)
    |-- scripts/                # Build/run scripts
    |-- docs/                   # Algorithm notes
    |-- build.bat / run.bat     # Windows scripts
    |-- setup_and_run.bat       # One-click build+run
    |-- Makefile                # GNU Make
    |-- LICENSE                 # MIT
    |-- README.md
    +-- index.html              # GitHub Pages

---

## Build Flags

    gcc src/main.c -o build/PixelCity -lfreeglut -lopengl32 -lglu32 -lm -O2 -Wall

| Flag | Purpose |
|------|---------|
| -lfreeglut | OpenGL Utility Toolkit |
| -lopengl32 | OpenGL core |
| -lglu32 | GLU library |
| -lm | Math library |

---

## Technical Details

- Frame Rate: ~60 FPS (16ms timer)
- Day/Night Cycle: 60 seconds
- Traffic Light: 4 seconds per state
- Scene: 16 layers rendered back-to-front

---

## License

MIT License - see LICENSE file.

---

**Made with love by Group 03 | Daffodil International University | Summer 2026**