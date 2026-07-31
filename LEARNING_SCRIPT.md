# PixelCity Learning Script
## CG Group 03 | DIU

> Understand YOUR part, connect to whole.

---

## How To Use
1.Read YOUR section 2.Watch videos
3.Find code in src/main.c 4.Run project
5.Draw on paper 6.Teach teammate

---

## YouTube Playlist
https://www.youtube.com/playlist?list=PL2nHwXBd7fkCIE5OK33BTT5X7yyDhikw2

| # | Title | Topic |
|---|-------|-------|
| 1 | OpenGL install | Setup |
| 2 | Shapes making | Shapes |
| 3 | House GL_LINE | Shapes |
| 4 | Hut OpenGL | Shapes |
| 5 | Rotation | Transform |
| 6 | DDA algorithm | DDA |
| 7 | Midpoint circle | Circle |
| 8 | Bresenham | Bresenham |
| 9 | Keyboard P1 | Input |
| 10 | Keyboard P2 | Input |
| 11 | Lighting | Light |
| 12 | 3D shapes | 3D |
| 13 | Object move | Animation |
| 14 | GLUT install | Setup |
| 15 | Aliasing | Theory |

---

# PERSON 1: Shoumik Bala Somu (232-15-657)
## Topic: DDA Algorithm + Road System + Setup

### Watch Videos: #14,#1,#6,#15

DDA = Digital Differential Analyzer
Math: dx=x2-x1 dy=y2-y1
steps=max(abs(dx),abs(dy))
x_inc=dx/steps y_inc=dy/steps
Loop: plot(round(x),round(y))
Then x+=x_inc y+=y_inc
Used: Road borders sun rays
Viva: max=no gaps float=slow

---

# PERSON 2: Nusrat Jahan Nishi (232-15-480)
## Topic: Bresenham Algorithm + Animation

### Watch Videos: #8,#13,#6

Bresenham: Integer-only line drawing
p0 = 2*dy - dx
if p<0: p=p+2dy
else: y++ p=p+2dy-2dx
Always x++
Used: Road dashes crosswalks railway
Viva: Faster than DDA no floats

---

# PERSON 3: Proma Dey (232-15-637)
## Topic: Midpoint Circle + Traffic System

### Watch Videos: #7,#2,#8

Midpoint Circle: 8-way symmetry
Start: x=0 y=r p=1-r
Plot 8 points: (+-x,+-y)(+-y,+-x)
x++ if p<0: p+=2x+1
else: y-- p+=2x-2y+1
Stop when x>y
Used: Roundabout sun wheels trees
Viva: 8 symmetry=free pixels

---

# PERSON 4: Sharmin Islam Eity (232-15-435)
## Topic: 2D Transformations + Windmill

### Watch Videos: #5,#9,#10

Translate=move Rotate=spin Scale=size
glTranslatef(x,y,0)
glRotatef(angle,0,0,1)
glScalef(sx,sy,1)
glPushMatrix=SAVE glPopMatrix=LOAD
Used: Windmill spin car move
Viva: push/pop isolates transforms

---

# PERSON 5: Afrin Maharin Shama (232-15-056)
## Topic: Shapes + Buildings + Scene

### Watch Videos: #2,#3,#4,#11,#12

GL_QUADS=rects GL_TRIANGLES GL_POLYGON
Buildings=quads roofs=triangles
Draw back-to-front painter algorithm
Used: Buildings cars trees roads
Viva: order matters in 2D

---

## Common Viva Questions
OpenGL=Graphics API GLUT=Window toolkit
glutMainLoop=infinite event loop
Double buffer=draw back swap front
gluOrtho2D=sets 2D coords
glBegin/glEnd=wrap vertex calls

## 7-Day Study Plan
Day1:Videos Day2:Read Day3:Find code
Day4:Run Day5:Practice Day6:Teach Day7:Review

---
Made by CG Group 03 - DIU CSE 2026