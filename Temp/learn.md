# PixelCity - Complete Learning Script (Beginner Guide)
## CG Group 03 | Daffodil International University | CSE

> You don't need to know everything. You just need to understand YOUR part deeply, and know how it connects to the whole.

---

## How To Use This Script

1. **Read your assigned section FIRST** (marked with your name)
2. **Watch the YouTube videos** listed under your name
3. **Open src/main.c** and find YOUR functions
4. **Run the project**, press your mode key, and SEE your code in action
5. **Draw it on paper** - trace the algorithm step by step
6. **Explain it to another member** - if you can teach it, you know it

---

## YouTube Playlist (Watch These!)

**Playlist:** [Computer Graphics Lab Full Playlist Bangla](https://www.youtube.com/playlist?list=PL2nHwXBd7fkCIE5OK33BTT5X7yyDhikw2)

| # | Video Title | Duration | Topic |
|---|-------------|----------|-------|
| 1 | OpenGL installation with Code Blocks in Bangla | 7:16 | Setup |
| 2 | Triangle, Pentagon, Trapezoid and shapes making | 30:48 | Shapes |
| 3 | House making using GL_LINE | 15:35 | Shapes + Lines |
| 4 | Make a hut/home/house OpenGL GLUT | 10:57 | Shapes |
| 5 | Rotation of shapes in OpenGL | 22:29 | 2D Transform |
| 6 | DDA line drawing algorithm | 10:34 | DDA |
| 7 | Mid-point circle algorithm | 8:29 | Midpoint |
| 8 | Bresenham line drawing algorithm | 14:08 | Bresenham |
| 9 | Keyboard and mouse input (Part 1) | 13:57 | Interaction |
| 10 | Keyboard and mouse input (Part 2) | 9:43 | Interaction |
| 11 | Lighting - ambient and diffuse | 15:34 | Lighting |
| 12 | 3D shapes in OpenGL | 11:30 | 3D |
| 13 | Object move using keyboard and mouse | 18:15 | Animation |
| 14 | OpenGL GLUT install step by step | 10:06 | Setup |
| 15 | Aliasing and Anti-Aliasing | 1:37 | Theory |

---
---

# PERSON 1: Shoumik Bala Somu (232-15-657)
## Your Topic: DDA Algorithm + Road System + Project Setup

### Videos You MUST Watch:
| Priority | Video | Why |
|----------|-------|-----|
| 1st | Video #14 - OpenGL GLUT install step by step | You set up the project |
| 2nd | Video #1 - OpenGL installation with Code Blocks | Understand compilation |
| 3rd | Video #6 - DDA line drawing algorithm | YOUR core algorithm |
| 4th | Video #15 - Aliasing and Anti-Aliasing | Theory for viva |

---

### Concept 1: What is DDA? (Digital Differential Analyzer)

**REAL LIFE ANALOGY:**
Imagine you are walking from point A to point B on a tiled floor. You can only stand on tile centers (integer coordinates). DDA figures out which tiles to step on to make a straight line.

**The Math (SUPER SIMPLE):**

```text
Given: Start (x1,y1) = (100,100), End (x2,y2) = (200,150)

Step 1: Find differences
   dx = x2 - x1 = 200 - 100 = 100
   dy = y2 - y1 = 150 - 100 = 50

Step 2: How many steps? Use the BIGGER one
   steps = max(|dx|, |dy|) = max(100, 50) = 100

Step 3: How much to add each step?
   x_increment = dx / steps = 100 / 100 = 1.0
   y_increment = dy / steps = 50 / 100 = 0.5

Step 4: Loop! Start at (100,100), add increments each time:
   Step 0:   (100.0, 100.0) -> plot (100, 100)
   Step 1:   (101.0, 100.5) -> plot (101, 101)  [round!]
   Step 2:   (102.0, 101.0) -> plot (102, 101)
   Step 3:   (103.0, 101.5) -> plot (103, 102)
   ...
   Step 100: (200.0, 150.0) -> plot (200, 150) DONE!
```

### Concept 2: Your Code in main.c

```c
void drawDDA(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = (float)dx / steps;
    float yInc = (float)dy / steps;
    float x = x1, y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2f(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}
```

### Concept 3: Where DDA is Used in PixelCity
Press **1** in the project -> Road borders, park boundaries, sun rays - all drawn pixel-by-pixel using DDA!

### Concept 4: Compilation (Your Job as Setup Lead)
```bash
gcc src/main.c -o build/PixelCity -lfreeglut -lopengl32 -lglu32 -lm
```

### Viva Questions for Shoumik:

| Question | Answer |
|----------|--------|
| What is DDA? | Digital Differential Analyzer. Draws lines by incrementing x,y by dx/steps and dy/steps |
| Why max(dx,dy)? | Prevents gaps - ensures every column/row gets a pixel |
| Disadvantage of DDA? | Uses floating-point math (slower than Bresenham integer-only approach) |
| What is aliasing? | Staircase/jagged effect on diagonal lines because pixels are square |
| What is anti-aliasing? | Blending edge pixels with background color to reduce jaggedness |
| How to compile? | gcc main.c -o app -lfreeglut -lopengl32 -lglu32 -lm |

---
---

# PERSON 2: Nusrat Jahan Nishi (232-15-480)
## Your Topic: Bresenham Algorithm + Animation System

### Videos You MUST Watch:
| Priority | Video | Why |
|----------|-------|-----|
| 1st | Video #8 - Bresenham line drawing algorithm | YOUR core algorithm |
| 2nd | Video #13 - Object move using keyboard and mouse | Animation concept |
| 3rd | Video #6 - DDA (for comparison) | Know the difference |

---

### Concept 1: Why Bresenham is BETTER than DDA

```text
DDA:       Uses DECIMAL math -> x += 0.5, y += 0.333 (floating point = SLOW)
Bresenham: Uses ONLY INTEGERS -> addition/subtraction only (FAST!)
           Uses a "decision parameter" to decide:
           "Should I go RIGHT or RIGHT+UP?"
```

**REAL LIFE:** You are drawing a line on graph paper. At each column, you decide: "Do I color THIS row, or the row ABOVE?" Bresenham gives you a simple rule.

### Concept 2: The Decision Parameter (THE KEY IDEA)

```text
Given: (0,0) to (8,5)
dx = 8, dy = 5
Initial: p0 = 2*dy - dx = 2(5) - 8 = 2

RULE: Always x++. Then check p:
   IF p < 0:  stay same y,  p = p + 2*dy
   IF p >= 0: y++,          p = p + 2*dy - 2*dx

TRACE:
Step 1: p=2  >=0 -> (1,1)  p = 2+10-16 = -4
Step 2: p=-4 <0  -> (2,1)  p = -4+10 = 6
Step 3: p=6  >=0 -> (3,2)  p = 6+10-16 = 0
Step 4: p=0  >=0 -> (4,3)  p = 0+10-16 = -6
Step 5: p=-6 <0  -> (5,3)  p = -6+10 = 4
Step 6: p=4  >=0 -> (6,4)  p = 4+10-16 = -2
Step 7: p=-2 <0  -> (7,4)  p = -2+10 = 8
Step 8: p=8  >=0 -> (8,5)  p = 8+10-16 = 2 DONE!

Pixels: (0,0)(1,1)(2,1)(3,2)(4,3)(5,3)(6,4)(7,4)(8,5)
```

### Concept 3: Your Code in main.c

```c
void drawBresenham(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (1) {
        glVertex2i(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx)  { err += dx; y1 += sy; }
    }
    glEnd();
}
```

This is the **GENERAL version** - works for ALL slopes and directions!

### Concept 4: Animation (Timer Callback)

```c
void timerCallback(int value) {
    carX += carSpeed;
    cloudX += 0.2;
    dayNightCycle += 0.001;
    glutPostRedisplay();
    glutTimerFunc(33, timerCallback, 0);
}
```

**Animation Loop:**
```text
timerCallback fires (every 33ms)
    -> Update positions (x += speed)
    -> glutPostRedisplay() triggers display()
    -> display() redraws everything
    -> Schedule next timerCallback
    -> (repeat forever)
```

### Viva Questions for Nusrat:

| Question | Answer |
|----------|--------|
| Why Bresenham over DDA? | Integer-only math (addition/subtraction). No float division. Faster! |
| What is decision parameter? | Value that decides: next pixel at same y or y+1. p<0=same, p>=0=y+1 |
| How does animation work? | glutTimerFunc calls a function every N ms. Updates positions then requests redraw |
| What is glutPostRedisplay? | Marks window for redraw. OpenGL calls display() on next loop iteration |
| What is glutTimerFunc? | glutTimerFunc(ms, callback, value) - calls callback after ms milliseconds |
| Frame rate? | 33ms timer = ~30 FPS. 16ms = ~60 FPS |

---
---

# PERSON 3: Proma Dey (232-15-637)
## Your Topic: Midpoint Circle Algorithm + Traffic System

### Videos You MUST Watch:
| Priority | Video | Why |
|----------|-------|-----|
| 1st | Video #7 - Mid-point circle algorithm | YOUR core algorithm |
| 2nd | Video #2 - Triangle, Pentagon, shapes | Understanding shapes |
| 3rd | Video #8 - Bresenham (related concept) | Decision parameter idea |

---

### Concept 1: Why Not Use y = sqrt(r^2 - x^2)?

```text
PROBLEM: sqrt() is expensive, gaps appear near sides, SLOW!
SOLUTION: Midpoint Circle Algorithm
   - Integer addition/subtraction ONLY
   - Draws 8 pixels at once using SYMMETRY
   - No gaps, no sqrt, super fast!
```

### Concept 2: 8-Way Symmetry (THE MAGIC)

```text
Calculate ONE point (x,y), get 8 points FREE:

   ( x, y)   ( y, x)   (-x, y)   (-y, x)
   ( x,-y)   ( y,-x)   (-x,-y)   (-y,-x)

We only compute 1/8 of the circle. The rest is MIRRORING!
```

### Concept 3: Algorithm Step by Step

```text
Given: radius r = 5, center (0,0)
Start: x=0, y=5, p = 1-r = -4

LOOP while x <= y:
   1. Plot all 8 symmetric points
   2. x++  (always)
   3. IF p < 0:  p = p + 2x + 1         (stay same y)
      ELSE:      y--, p = p + 2x - 2y + 1  (decrease y)

TRACE for r=5:
x=0, y=5, p=-4 -> plot 8 points
x=1, y=5, p=-3 -> plot 8 points
x=2, y=5, p= 0 -> plot 8 points
x=3, y=4, p=-3 -> plot 8 points  [y decreased!]
x=4, y=4, p= 2 -> plot 8 points  [x==y, last!]
DONE! (x > y, stop)
```

### Concept 4: Your Code in main.c

```c
void drawMidpointCircle(int cx, int cy, int r)
{
    int x = 0, y = r;
    int p = 1 - r;

    glBegin(GL_POINTS);
    while (x <= y) {
        glVertex2i(cx+x, cy+y);
        glVertex2i(cx-x, cy+y);
        glVertex2i(cx+x, cy-y);
        glVertex2i(cx-x, cy-y);
        glVertex2i(cx+y, cy+x);
        glVertex2i(cx-y, cy+x);
        glVertex2i(cx+y, cy-x);
        glVertex2i(cx-y, cy-x);

        x++;
        if (p < 0)
            p = p + 2*x + 1;
        else {
            y--;
            p = p + 2*x - 2*y + 1;
        }
    }
    glEnd();
}
```

### Concept 5: Where Circles Are Used in PixelCity
Press **3** -> Roundabout, sun, car wheels, traffic lights, trees, clouds!

### Viva Questions for Proma:

| Question | Answer |
|----------|--------|
| Why plot 8 points? | Circle has 8-way symmetry. Compute 1 point, mirror to get 8 free! |
| Initial p value? | p = 1 - r. Comes from circle equation evaluated at midpoint |
| Why y decreases? | We trace first octant (0 to 45 degrees). x increases, y decreases |
| Advantage over sqrt method? | No floating point, no gaps, 8x faster due to symmetry |
| What is an octant? | 1/8th of a circle (45 degrees). We compute one, mirror to get all 8 |

---
---

# PERSON 4: Sharmin Islam Eity (232-15-435)
## Your Topic: 2D Transformations + Windmill

### Videos You MUST Watch:
| Priority | Video | Why |
|----------|-------|-----|
| 1st | Video #5 - Rotation of shapes in OpenGL | YOUR core topic |
| 2nd | Video #9 - Keyboard and mouse input (Part 1) | Interaction |
| 3rd | Video #10 - Keyboard and mouse input (Part 2) | More interaction |

---

### Concept 1: Three Basic Transformations

```text
TRANSLATION -> Move (slide) without rotating    [car on road]
ROTATION    -> Spin around a point              [windmill blade]
SCALING     -> Grow or shrink                   [zoom in/out]
```

### Concept 2: The Math

```text
TRANSLATION:  x_new = x + tx,  y_new = y + ty    (Just ADD!)
ROTATION:     x_new = x*cos(theta) - y*sin(theta)  (Trigonometry!)
              y_new = x*sin(theta) + y*cos(theta)
SCALING:      x_new = x * sx,  y_new = y * sy     (Just MULTIPLY!)
```

### Concept 3: OpenGL Transform Functions

```c
glTranslatef(tx, ty, 0);     // Move by (tx, ty)
glRotatef(angle, 0, 0, 1);  // Rotate angle degrees around Z-axis
glScalef(sx, sy, 1);         // Scale by (sx, sy)
```

### Concept 4: Push/Pop Matrix (CRITICAL CONCEPT!)

```text
Think of it like SAVE/LOAD in a video game:

glPushMatrix();              <- SAVE current position/rotation
   glTranslatef(5, 3, 0);   <- Move
   glRotatef(45, 0, 0, 1);  <- Rotate
   drawMyShape();            <- Draw (affected by above!)
glPopMatrix();               <- RESTORE to saved state

Without push/pop, transforms ACCUMULATE forever!
```

### Concept 5: The Windmill (Your Code)

```c
void drawWindmill(float x, float y, float bladeAngle)
{
    // Pole (NOT rotating)
    glColor3f(0.4, 0.3, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(x-2, y); glVertex2f(x+2, y);
    glVertex2f(x+1.5, y+25); glVertex2f(x-1.5, y+25);
    glEnd();

    // Blades (ROTATING!)
    glPushMatrix();
    glTranslatef(x, y+25, 0);
    glRotatef(bladeAngle, 0, 0, 1);
    for (int i = 0; i < 4; i++) {
        glColor3f(0.9, 0.9, 0.9);
        glBegin(GL_TRIANGLES);
        glVertex2f(0, 0); glVertex2f(-2, 12); glVertex2f(2, 12);
        glEnd();
        glRotatef(90, 0, 0, 1);
    }
    glPopMatrix();
}
```

**Animation:** bladeAngle += 2 every frame -> SPINNING WINDMILL!

### Concept 6: Keyboard Control

```c
void keyboardHandler(unsigned char key, int x, int y) {
    switch(key) {
        case 'w': carY += 5; break;
        case 's': carY -= 5; break;
        case 'a': carX -= 5; break;
        case 'd': carX += 5; break;
        case 27: exit(0); break;   // ESC = ASCII 27
    }
    glutPostRedisplay();
}
glutKeyboardFunc(keyboardHandler);
```

### Viva Questions for Sharmin:

| Question | Answer |
|----------|--------|
| Name 3 basic transforms? | Translation (move), Rotation (spin), Scaling (resize) |
| Why glPushMatrix/PopMatrix? | Transforms are cumulative. Push saves, Pop restores |
| Rotation matrix formula? | [cos, -sin; sin, cos] - rotates counterclockwise |
| glRotatef(angle,0,0,1) means? | Rotates by angle degrees around Z-axis = 2D rotation |
| How to move object with keyboard? | Change x,y in keyboard callback, call glutPostRedisplay() |
| What is modelview matrix? | 4x4 matrix storing all current transforms |

---
---

# PERSON 5: Afrin Maharin Shama (232-15-056)
## Your Topic: Shapes + Buildings + Scene Composition

### Videos You MUST Watch:
| Priority | Video | Why |
|----------|-------|-----|
| 1st | Video #2 - Triangle, Pentagon, Trapezoid and shapes | YOUR core topic |
| 2nd | Video #3 - House making using GL_LINE | Building shapes |
| 3rd | Video #4 - Make a hut/home/house | Complex shapes |
| 4th | Video #11 - Lighting (ambient and diffuse) | Visual quality |
| 5th | Video #12 - 3D shapes in OpenGL | Extension knowledge |

---

### Concept 1: OpenGL Drawing Primitives

```text
GL_POINTS      -> Individual dots (one vertex = one dot)
GL_LINES       -> Separate line segments (every 2 vertices = one line)
GL_LINE_STRIP  -> Connected lines (chain of vertices)
GL_LINE_LOOP   -> Like strip but closes back to start
GL_TRIANGLES   -> Filled triangles (every 3 vertices = one triangle)
GL_QUADS       -> Filled rectangles (every 4 vertices = one quad)
GL_POLYGON     -> Filled convex polygon (any number of vertices)
```

### Concept 2: Drawing a Building

```c
void drawBuilding(float x, float y, float w, float h)
{
    glColor3f(0.5, 0.5, 0.6);
    glBegin(GL_QUADS);
    glVertex2f(x, y); glVertex2f(x+w, y);
    glVertex2f(x+w, y+h); glVertex2f(x, y+h);
    glEnd();

    // Windows
    for (int row = 0; row < 5; row++)
        for (int col = 0; col < 3; col++) {
            glColor3f(1.0, 0.9, 0.4);
            glBegin(GL_QUADS);
            float wx = x + 5 + col * (w/3);
            float wy = y + 5 + row * (h/5);
            glVertex2f(wx, wy); glVertex2f(wx+8, wy);
            glVertex2f(wx+8, wy+8); glVertex2f(wx, wy+8);
            glEnd();
        }
}
```

### Concept 3: Drawing a Car (Composite Shape)

```text
        +--------+           <- Roof (small quad)
   +----+--------+----+     <- Body (big quad)
   |  O            O  |     <- Wheels (circles!)
   +------------------+

A car = rectangle body + rectangle roof + 2 circles!
```

### Concept 4: Scene Composition (Drawing Order!)

```text
DRAW BACK TO FRONT (Painter's Algorithm):
   1. Sky (background)        <- furthest back
   2. Sun/Moon + Clouds
   3. Buildings (skyline)
   4. Roads
   5. Road markings
   6. Trees, street lamps
   7. Cars                    <- closest to viewer

If you draw cars FIRST, buildings will COVER them!
```

### Concept 5: Day/Night Color Interpolation

```c
// t = 0 -> night, t = 1 -> day
float skyR = 0.05 + t * (0.53 - 0.05);
float skyG = 0.05 + t * (0.81 - 0.05);
float skyB = 0.15 + t * (0.92 - 0.15);
glClearColor(skyR, skyG, skyB, 1.0);
```

### Viva Questions for Afrin:

| Question | Answer |
|----------|--------|
| What is GL_QUADS? | Draws filled quadrilaterals. Every 4 vertices = one rectangle |
| Why drawing order matters? | Later objects cover earlier ones (painter's algorithm) |
| Complex shape like car? | Combine primitives: rects for body, circles for wheels |
| Color interpolation? | color = colorA + t*(colorB-colorA). Blends two colors |
| GL_TRIANGLES vs GL_POLYGON? | Triangles: 3 vertices each. Polygon: any N convex vertices |
| Painter's algorithm? | Draw back-to-front. Far objects first, near objects last |

---
---

## EVERYONE Must Know (Common Viva Questions)

| Question | Answer |
|----------|--------|
| What is OpenGL? | Open Graphics Library. API for 2D/3D rendering. Talks to GPU |
| What is GLUT/FreeGLUT? | OpenGL Utility Toolkit. Handles window, keyboard, mouse, event loop |
| What is glutMainLoop()? | Infinite event loop. Waits for events, calls callbacks. Never returns |
| What is a display callback? | Function called when window needs redraw. Clear -> Draw -> SwapBuffers |
| What is double buffering? | Draw to hidden back buffer, swap to front. Prevents flickering |
| What is gluOrtho2D(l,r,b,t)? | Sets 2D coordinate system. E.g., (0,800,0,600) |
| What are glBegin/glEnd? | Wraps vertex calls. glBegin(GL_QUADS) -> glVertex -> glEnd |
| What is a vertex? | A point in space. glVertex2f(x,y) specifies one point |
| Graphics pipeline? | Vertices -> Transform -> Clip -> Rasterize -> Fragment -> Pixels |
| What is rasterization? | Converting shapes into pixels on screen |

---

## 7-Day Study Schedule

| Day | Task | Time |
|-----|------|------|
| Day 1 | Watch YOUR assigned YouTube videos. Take handwritten notes | 2 hours |
| Day 2 | Read YOUR section. Draw algorithm diagrams on paper | 2 hours |
| Day 3 | Open src/main.c, find YOUR functions. Add comments | 2 hours |
| Day 4 | Run the project, press YOUR mode key. Trace mentally | 1.5 hours |
| Day 5 | Practice viva questions. Quiz another member | 2 hours |
| Day 6 | Explain YOUR topic to another member | 1.5 hours |
| Day 7 | Full group review. Everyone explains everything | 3 hours |

---

## OpenGL Quick Reference Card

```text
+-------------------------------------------------------------+
|                    OPENGL CHEAT SHEET                        |
+-------------------------------------------------------------+
|  SETUP:                                                     |
|  glutInit(&argc, argv)        -> Initialize GLUT            |
|  glutInitDisplayMode(mode)    -> Set display mode           |
|  glutInitWindowSize(w, h)     -> Set window size            |
|  glutCreateWindow("Title")    -> Create window              |
|  glutMainLoop()               -> Start event loop           |
+-------------------------------------------------------------+
|  CALLBACKS:                                                 |
|  glutDisplayFunc(fn)          -> Called on redraw           |
|  glutReshapeFunc(fn)          -> Called on resize           |
|  glutKeyboardFunc(fn)         -> Called on key press        |
|  glutSpecialFunc(fn)          -> Called on arrow keys       |
|  glutTimerFunc(ms, fn, val)   -> Called after ms millisec   |
|  glutIdleFunc(fn)             -> Called when idle           |
+-------------------------------------------------------------+
|  DRAWING:                                                   |
|  glClear(GL_COLOR_BUFFER_BIT) -> Clear screen               |
|  glClearColor(r, g, b, a)     -> Background color           |
|  glColor3f(r, g, b)           -> Drawing color              |
|  glPointSize(size)            -> Point size                 |
|  glLineWidth(width)           -> Line width                 |
|  glBegin(GL_QUADS)            -> Start drawing              |
|  glVertex2f(x, y)             -> Add vertex                 |
|  glEnd()                      -> Finish drawing             |
|  glutSwapBuffers()            -> Show frame                 |
+-------------------------------------------------------------+
|  TRANSFORMS:                                                |
|  glPushMatrix()               -> SAVE state                 |
|  glPopMatrix()                -> RESTORE state              |
|  glTranslatef(x, y, z)        -> Move                       |
|  glRotatef(deg, x, y, z)      -> Rotate                     |
|  glScalef(x, y, z)            -> Scale                      |
|  glLoadIdentity()             -> Reset matrix               |
|  gluOrtho2D(l, r, b, t)       -> Set 2D coords             |
+-------------------------------------------------------------+
|  PRIMITIVES:                                                |
|  GL_POINTS / GL_LINES / GL_LINE_STRIP / GL_LINE_LOOP        |
|  GL_TRIANGLES / GL_QUADS / GL_POLYGON                       |
+-------------------------------------------------------------+
|  glutPostRedisplay()  -> Request redraw                     |
+-------------------------------------------------------------+
```

---

## Final Tips for Viva

1. **DO NOT memorize code.** Understand the LOGIC and FLOW.
2. **Draw on paper.** If asked "explain Bresenham," draw the pixel grid and trace.
3. **Know WHY.** "Why Bresenham over DDA?" -> "Integer math = faster."
4. **Connect to project.** "Where is DDA used?" -> "Road borders in PixelCity."
5. **Be honest.** If you don't know, say "I understand the concept but need to review."
6. **Practice together.** Quiz each other. Teaching = Learning.
7. **Know your role.** Be ready to say "I was responsible for..."
8. **Run the project live.** Show the professor the running project.

---

## Project Architecture

```text
+-----------------------------------------------------------+
|                    PixelCity                                |
+-----------------------------------------------------------+
|  +----------+  +--------------+  +-----------------+     |
|  |   DDA    |  |  Bresenham   |  | Midpoint Circle |     |
|  | (Shoumik)|  |  (Nusrat)    |  |    (Proma)      |     |
|  +----+-----+  +------+-------+  +--------+--------+     |
|       |               |                    |              |
|       v               v                    v              |
|  +--------------------------------------------------+    |
|  |         SCENE COMPOSITION (Afrin - Shapes)        |    |
|  |   Sky -> Buildings -> Roads -> Trees -> Cars      |    |
|  +---------------------+----------------------------+    |
|       +----------------+----------------+                |
|       v                v                v                |
|  +---------+   +------------+   +------------+          |
|  |   2D    |   | Animation  |   | Keyboard   |          |
|  |Transform|   |  (Timer)   |   |  Control   |          |
|  |(Sharmin)|   |  (Nusrat)  |   |  (Sharmin) |          |
|  +---------+   +------------+   +------------+          |
+-----------------------------------------------------------+
```

---

## Contributor Summary

| Name | Registration ID | Topic | Key Functions |
|------|----------------|-------|---------------|
| Shoumik Bala Somu | 232-15-657 | DDA + Setup | drawDDA(), compilation |
| Nusrat Jahan Nishi | 232-15-480 | Bresenham + Animation | drawBresenham(), timerCallback() |
| Proma Dey | 232-15-637 | Midpoint Circle | drawMidpointCircle() |
| Sharmin Islam Eity | 232-15-435 | 2D Transformations | glTranslate/Rotate/Scale, windmill |
| Afrin Maharin Shama | 232-15-056 | Shapes + Scene | Buildings, cars, drawing order |

---

> **Made with love by CG Group 03**
> Shoumik - Nusrat - Proma - Sharmin - Afrin
> Daffodil International University | CSE | 2026
>
> "The best way to learn is to teach. The best way to understand is to draw."
