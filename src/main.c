/**
 * PIXEL CITY - 2D Smart City Traffic Simulator
 * CG Group 03 - Daffodil International University
 * Contributors: Shoumik Bala Somu(232-15-657), Nusrat Jahan Nishi(232-15-480),
 *   Proma Dey(232-15-637), Sharmin Islam Eity(232-15-435), Afrin Maharin Shama(232-15-056)
 * Build: gcc src/main.c -o build/app -lfreeglut -lopengl32 -lglu32 -lm
 * Topics: [1]DDA [2]Bresenham [3]Midpoint Circle [4]2D Transform [5]Animation [6]Shapes
 */
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
const int WIN_W=1000,WIN_H=700;
const float WW=1000.0f,WH=700.0f;
float g_time=0,g_day=0,g_cang=0,g_wm=0;
int g_pause=0,g_ts=0;
float g_tt=0,g_c1x=-50,g_c2x=1050,g_c3y=-50,g_c4y=750,g_bx=-200;
float g_cl1=100,g_cl2=600,g_cl3=350,g_tx=-300;
float g_b1x=0,g_b1y=550,g_b2x=200,g_b2y=580;
float g_sm[5]={0,0,0,0,0};

/* [1] DDA Line Drawing */
void DDA(float x1,float y1,float x2,float y2){
    float dx=fabs(x2-x1),dy=fabs(y2-y1),s=fmax(dx,dy);
    if(s==0){glBegin(GL_POINTS);glVertex2f(x1,y1);glEnd();return;}
    float xi=(x2-x1)/s,yi=(y2-y1)/s,x=x1,y=y1;
    glBegin(GL_POINTS);
    for(int i=0;i<=(int)s;i++){glVertex2f(round(x),round(y));x+=xi;y+=yi;}
    glEnd();}
void DDAT(float x1,float y1,float x2,float y2,float th){
    float dx=x2-x1,dy=y2-y1,l=sqrt(dx*dx+dy*dy);if(l==0)return;
    float nx=-dy/l,ny=dx/l;
    for(float t=-th/2;t<=th/2;t+=1)DDA(x1+nx*t,y1+ny*t,x2+nx*t,y2+ny*t);}

/* [2] Bresenham Line Drawing */
void Bres(float x1,float y1,float x2,float y2){
    float dx=fabs(x2-x1),dy=fabs(y2-y1);
    float xc=(x1<x2)?1:-1,yc=(y1<y2)?1:-1,p;
    glBegin(GL_POINTS);glVertex2f(x1,y1);
    if(dx>=dy){p=2*dy-dx;float x=x1,y=y1;
        while(x!=x2){x+=xc;if(p<0)p+=2*dy;else{y+=yc;p+=2*dy-2*dx;}glVertex2f(x,y);}
    }else{p=2*dx-dy;float x=x1,y=y1;
        while(y!=y2){y+=yc;if(p<0)p+=2*dx;else{x+=xc;p+=2*dx-2*dy;}glVertex2f(x,y);}
    }glEnd();}
void BresD(float x1,float y1,float x2,float y2,float dl,float gl){
    float dx=x2-x1,dy=y2-y1,tl=sqrt(dx*dx+dy*dy);if(tl==0)return;
    float ux=dx/tl,uy=dy/tl,d=0;int dr=1;
    while(d<tl){float sl=dr?dl:gl,ed=fmin(d+sl,tl);
        if(dr)Bres(x1+ux*d,y1+uy*d,x1+ux*ed,y1+uy*ed);d=ed;dr=!dr;}}

/* [3] Midpoint Circle */
void MC(float cx,float cy,float r){
    float x=0,y=r,p=1-r;glBegin(GL_POINTS);
    while(x<=y){glVertex2f(cx+x,cy+y);glVertex2f(cx-x,cy+y);
        glVertex2f(cx+x,cy-y);glVertex2f(cx-x,cy-y);
        glVertex2f(cx+y,cy+x);glVertex2f(cx-y,cy+x);
        glVertex2f(cx+y,cy-x);glVertex2f(cx-y,cy-x);
        x++;if(p<0)p+=2*x+1;else{y--;p+=2*(x-y)+1;}}glEnd();}
void MF(float cx,float cy,float r){
    float x=0,y=r,p=1-r;glBegin(GL_LINES);
    while(x<=y){glVertex2f(cx-x,cy+y);glVertex2f(cx+x,cy+y);
        glVertex2f(cx-x,cy-y);glVertex2f(cx+x,cy-y);
        glVertex2f(cx-y,cy+x);glVertex2f(cx+y,cy+x);
        glVertex2f(cx-y,cy-x);glVertex2f(cx+y,cy-x);
        x++;if(p<0)p+=2*x+1;else{y--;p+=2*(x-y)+1;}}glEnd();}
void MT(float cx,float cy,float r,float th){
    for(float t=-th/2;t<=th/2;t+=1)MC(cx,cy,r+t);}

/* [4] 2D Transformations */
void Tr(float x,float y){glTranslatef(x,y,0);}
void Rt(float a){glRotatef(a,0,0,1);}
void Sc(float x,float y){glScalef(x,y,1);}

/* [6] Shapes */
void Rect(float x,float y,float w,float h){
    glBegin(GL_QUADS);glVertex2f(x,y);glVertex2f(x+w,y);
    glVertex2f(x+w,y+h);glVertex2f(x,y+h);glEnd();}
void Tri(float x1,float y1,float x2,float y2,float x3,float y3){
    glBegin(GL_TRIANGLES);glVertex2f(x1,y1);glVertex2f(x2,y2);glVertex2f(x3,y3);glEnd();}

void Draw_Sky(void){
    float df=(cos(g_day*2*M_PI)+1)/2;
    glBegin(GL_QUADS);
    glColor3f(.4f+.5f*df,.5f+.4f*df,.3f+.5f*df);glVertex2f(0,0);glVertex2f(WW,0);
    glColor3f(.1f+.4f*df,.1f+.6f*df,.2f+.8f*df);glVertex2f(WW,WH);glVertex2f(0,WH);
    glEnd();}
void Draw_Sun(void){
    float cx=500+400*cos(g_cang),cy=100+500*sin(g_cang);
    float df=(cos(g_day*2*M_PI)+1)/2;
    if(df>.3f){glColor3f(1,.9f,.2f);MF(cx,cy,35);
        glColor3f(1,.85f,0);
        for(int i=0;i<12;i++){float a=(i*30+g_time*20)*M_PI/180;
            DDA(cx+40*cos(a),cy+40*sin(a),cx+55*cos(a),cy+55*sin(a));}
    }else{glColor3f(.9f,.9f,.8f);MF(cx,cy,25);
        glColor3f(.75f,.75f,.7f);MF(cx-8,cy+5,6);MF(cx+10,cy-8,4);
        glColor3f(1,1,.9f);glBegin(GL_POINTS);
        for(int i=0;i<50;i++){float sx=i*137.5f+50,sy=i*97.3f+400;
            if(sx<WW&&sy<WH&&sin(g_time*3+i)>.3f)glVertex2f(sx,sy);}glEnd();}}
void Draw_Clouds(void){
    float df=(cos(g_day*2*M_PI)+1)/2,b=.6f+.4f*df;glColor3f(b,b,b);
    MF(g_cl1,580,25);MF(g_cl1+25,590,30);MF(g_cl1+55,580,22);
    MF(g_cl2,620,20);MF(g_cl2+22,628,25);MF(g_cl2+48,620,18);
    MF(g_cl3,550,18);MF(g_cl3+20,558,22);MF(g_cl3+42,550,16);}
void Draw_Birds(void){
    float w=g_time*8;glColor3f(.1f,.1f,.1f);glBegin(GL_LINES);
    glVertex2f(g_b1x,g_b1y);glVertex2f(g_b1x-10,g_b1y+5*sin(w));
    glVertex2f(g_b1x,g_b1y);glVertex2f(g_b1x+10,g_b1y+5*sin(w));
    glVertex2f(g_b2x,g_b2y);glVertex2f(g_b2x-10,g_b2y+5*sin(w+2));
    glVertex2f(g_b2x,g_b2y);glVertex2f(g_b2x+10,g_b2y+5*sin(w+2));glEnd();}
void Draw_Ground(void){
    glColor3f(.2f,.6f,.2f);Rect(0,0,WW,250);
    glColor3f(.7f,.7f,.65f);Rect(0,250,WW,20);}
void Draw_Roads(void){
    glColor3f(.25f,.25f,.25f);Rect(0,270,WW,100);Rect(430,0,100,500);
    glColor3f(.9f,.9f,.9f);
    DDAT(0,270,WW,270,3);DDAT(0,370,WW,370,3);
    DDAT(430,0,430,270,3);DDAT(530,0,530,270,3);
    DDAT(430,370,430,500,3);DDAT(530,370,530,500,3);
    glColor3f(1,.85f,0);
    BresD(0,320,430,320,30,20);BresD(530,320,WW,320,30,20);
    BresD(480,0,480,270,25,15);BresD(480,370,480,500,25,15);
    glColor3f(1,1,1);
    for(int i=0;i<8;i++){float y=275+i*12;Bres(395,y,425,y);Bres(535,y,565,y);}
    for(int i=0;i<6;i++){float x=435+i*16;Bres(x,240,x,265);Bres(x,375,x,400);}}
void Draw_Round(void){
    glColor3f(.3f,.3f,.3f);MF(480,320,50);
    glColor3f(.15f,.5f,.15f);MF(480,320,30);
    glColor3f(1,1,1);MT(480,320,50,3);MT(480,320,30,2);
    glColor3f(.8f,.2f,.2f);MF(480,320,8);
    glColor3f(1,1,.5f);
    for(int i=0;i<4;i++){float a=(i*90+g_time*30)*M_PI/180;MF(480+40*cos(a),320+40*sin(a),3);}}
void Draw_Bld(float x,float y,float w,float h,float r,float g,float b,int fl){
    glPushMatrix();Tr(x,y);glColor3f(r,g,b);Rect(0,0,w,h);
    glColor3f(r*.7f,g*.7f,b*.7f);Tri(-5,h,w/2,h+25,w+5,h);
    float ww=w/(fl+1),df=(cos(g_day*2*M_PI)+1)/2;
    for(int f=0;f<fl;f++)for(int c=0;c<fl;c++){
        if(df<.4f&&(f+c)%2==0)glColor3f(1,.9f,.4f);else glColor3f(.6f,.8f,1);
        Rect(8+c*(ww+5),10+f*(h/fl),ww-3,15);}
    glColor3f(.4f,.25f,.1f);Rect(w/2-8,0,16,25);glPopMatrix();}
void Draw_Tree(float x,float y,float s){
    glPushMatrix();Tr(x,y);Sc(s,s);
    glColor3f(.5f,.3f,.1f);Rect(-5,0,10,35);
    glColor3f(.1f,.55f,.1f);MF(0,50,22);MF(-15,40,16);MF(15,40,16);MF(0,62,14);
    glPopMatrix();}
void Draw_Park(void){
    glColor3f(.25f,.65f,.25f);Rect(600,100,180,140);
    glColor3f(.6f,.4f,.2f);DDAT(600,100,780,100,3);DDAT(780,100,780,240,3);
    DDAT(600,240,780,240,3);DDAT(600,100,600,240,3);
    glColor3f(.2f,.4f,.8f);MF(690,160,30);glColor3f(.3f,.5f,.9f);MF(690,160,20);
    glColor3f(.5f,.35f,.15f);Rect(620,200,30,5);Rect(622,195,3,5);Rect(645,195,3,5);
    for(int i=0;i<6;i++){float fx=610+(i%3)*25,fy=110+(i/3)*20;
        if(i%3==0)glColor3f(1,.3f,.3f);else if(i%3==1)glColor3f(1,.8f,0);else glColor3f(.9f,.3f,.9f);
        MF(fx,fy,4);glColor3f(0,.5f,0);Bres(fx,fy-4,fx,fy-12);}}
void Draw_Car(float x,float y,float r,float g,float b,int fl){
    glPushMatrix();Tr(x,y);if(fl)Sc(-1,1);
    glColor3f(r,g,b);Rect(0,0,50,18);
    glColor3f(r*.8f,g*.8f,b*.8f);Tri(10,18,20,30,40,18);
    glColor3f(.7f,.9f,1);Tri(14,18,21,27,28,18);Tri(30,18,33,27,38,18);
    glColor3f(.1f,.1f,.1f);MF(12,0,7);MF(38,0,7);
    glColor3f(.6f,.6f,.6f);MF(12,0,3);MF(38,0,3);
    glColor3f(1,1,.5f);MF(50,10,3);glColor3f(1,0,0);MF(0,10,2);glPopMatrix();}
void Draw_Bus(float x,float y){
    glPushMatrix();Tr(x,y);glColor3f(.9f,.6f,.1f);Rect(0,0,90,30);
    glColor3f(.9f,.9f,.9f);Rect(0,12,90,5);glColor3f(.6f,.85f,1);
    for(int i=0;i<5;i++)Rect(8+i*16,18,12,10);
    glColor3f(.1f,.1f,.1f);MF(20,0,8);MF(70,0,8);
    glColor3f(.5f,.5f,.5f);MF(20,0,3);MF(70,0,3);glPopMatrix();}
void Draw_TL(float x,float y,int v){
    glPushMatrix();Tr(x,y);glColor3f(.3f,.3f,.3f);Rect(-3,0,6,50);
    glColor3f(.15f,.15f,.15f);Rect(-10,50,20,45);
    int sg,sy,sr;
    if(v){sg=(g_ts==0);sy=(g_ts==1);sr=(g_ts==2||g_ts==3);}
    else{sg=(g_ts==2);sy=(g_ts==3);sr=(g_ts==0||g_ts==1);}
    glColor3f(sr?1:.3f,0,0);MF(0,85,6);
    glColor3f(1,sy?1:.3f,0);MF(0,72,6);
    glColor3f(0,sg?1:.3f,0);MF(0,59,6);glPopMatrix();}
void Draw_WM(float x,float y){
    glPushMatrix();Tr(x,y);glColor3f(.8f,.8f,.8f);
    glBegin(GL_QUADS);glVertex2f(-8,0);glVertex2f(8,0);glVertex2f(4,80);glVertex2f(-4,80);glEnd();
    glPushMatrix();Tr(0,80);Rt(g_wm);glColor3f(.9f,.9f,.95f);
    for(int i=0;i<4;i++){glPushMatrix();Rt(i*90);Tri(-3,0,0,40,3,0);glPopMatrix();}
    glColor3f(.4f,.4f,.4f);MF(0,0,5);glPopMatrix();glPopMatrix();}
void Draw_Train(void){
    glPushMatrix();Tr(g_tx,35);glColor3f(.2f,.2f,.6f);Rect(0,0,70,30);
    glColor3f(.15f,.15f,.5f);Rect(50,30,20,15);glColor3f(.3f,.3f,.3f);Rect(10,30,10,15);
    glColor3f(.7f,.7f,.7f);
    for(int i=0;i<5;i++)MF(15+sin(g_time*2+i)*5,50+g_sm[i],4+i*2);
    glColor3f(.1f,.1f,.1f);MF(15,0,8);MF(40,0,8);MF(60,0,8);
    for(int w=0;w<3;w++){float wx=-80-w*75;
        glColor3f(.6f+w*.1f,.3f,.2f);Rect(wx,0,65,25);
        glColor3f(.1f,.1f,.1f);MF(wx+15,0,7);MF(wx+50,0,7);}glPopMatrix();}
void Draw_Lamp(float x,float y){
    glPushMatrix();Tr(x,y);glColor3f(.3f,.3f,.35f);Rect(-2,0,4,60);Rect(-2,58,15,3);
    float df=(cos(g_day*2*M_PI)+1)/2;
    if(df<.4f){glColor3f(1,.95f,.6f);MF(13,55,5);glColor3f(1,.9f,.4f);MC(13,55,10);}
    else{glColor3f(.5f,.5f,.5f);MF(13,55,4);}glPopMatrix();}

/* [5] Animation */
void Update(void){
    if(g_pause)return;float dt=.016f;g_time+=dt;
    g_day+=dt/60;if(g_day>1)g_day-=1;g_cang=g_day*2*M_PI-M_PI/2;
    g_tt+=dt;if(g_tt>4){g_tt=0;g_ts=(g_ts+1)%4;}
    float cs=2;
    if(g_ts==0||g_ts==1){if(g_c1x>350&&g_c1x<530)g_c1x+=cs*.2f;else g_c1x+=cs;}
    else g_c1x+=cs;if(g_c1x>WW+60)g_c1x=-60;
    if(g_ts==0||g_ts==1){if(g_c2x<600&&g_c2x>430)g_c2x-=cs*.2f;else g_c2x-=cs;}
    else g_c2x-=cs;if(g_c2x<-60)g_c2x=WW+60;
    g_bx+=1.2f;if(g_bx>WW+100)g_bx=-200;
    if(g_ts==2||g_ts==3){if(g_c3y>220&&g_c3y<370)g_c3y+=cs*.2f;else g_c3y+=cs*.8f;}
    else g_c3y+=cs*.8f;if(g_c3y>550)g_c3y=-50;
    if(g_ts==2||g_ts==3){if(g_c4y<420&&g_c4y>270)g_c4y-=cs*.2f;else g_c4y-=cs*.8f;}
    else g_c4y-=cs*.8f;if(g_c4y<-50)g_c4y=750;
    g_wm+=1.5f;if(g_wm>360)g_wm-=360;
    g_cl1+=.3f;g_cl2+=.2f;g_cl3+=.25f;
    if(g_cl1>WW+80)g_cl1=-80;if(g_cl2>WW+80)g_cl2=-80;if(g_cl3>WW+80)g_cl3=-80;
    g_tx+=1.5f;if(g_tx>WW+400)g_tx=-400;
    for(int i=0;i<5;i++){g_sm[i]+=.5f;if(g_sm[i]>30)g_sm[i]=0;}
    g_b1x+=.8f;g_b2x+=.6f;g_b1y=550+sin(g_time*.5f)*20;g_b2y=580+cos(g_time*.4f)*15;
    if(g_b1x>WW+50)g_b1x=-50;if(g_b2x>WW+50)g_b2x=-50;}

void Display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    Draw_Sky();Draw_Sun();Draw_Clouds();Draw_Birds();Draw_Ground();
    Draw_Park();
    Draw_Tree(60,200,1);Draw_Tree(160,210,.8f);Draw_Tree(350,195,1.1f);
    Draw_Tree(620,205,.9f);Draw_Tree(750,200,1);Draw_Tree(920,210,.85f);
    Draw_Bld(30,370,70,120,.8f,.4f,.3f,3);Draw_Bld(120,370,60,90,.5f,.6f,.8f,2);
    Draw_Bld(200,370,80,150,.7f,.7f,.5f,4);Draw_Bld(310,370,55,80,.6f,.4f,.6f,2);
    Draw_Bld(580,370,75,130,.4f,.6f,.6f,3);Draw_Bld(680,370,65,100,.8f,.6f,.4f,3);
    Draw_Bld(770,370,90,160,.5f,.5f,.7f,4);Draw_Bld(890,370,70,110,.7f,.5f,.5f,3);
    glColor3f(.4f,.3f,.2f);Bres(0,30,WW,30);Bres(0,50,WW,50);
    glColor3f(.5f,.4f,.3f);for(float x=0;x<WW;x+=25)Bres(x,25,x,55);
    Draw_Train();Draw_Roads();Draw_Round();
    Draw_TL(415,220,1);Draw_TL(545,220,0);Draw_TL(415,375,1);Draw_TL(545,375,0);
    Draw_Car(g_c1x,285,.8f,.2f,.2f,0);Draw_Car(g_c2x,340,.2f,.4f,.8f,1);Draw_Bus(g_bx,282);
    glPushMatrix();glTranslatef(445,g_c3y,0);glRotatef(90,0,0,1);
    glColor3f(.2f,.7f,.3f);Rect(0,0,45,16);glColor3f(.15f,.55f,.25f);Tri(8,16,18,26,36,16);
    glColor3f(.1f,.1f,.1f);MF(10,0,6);MF(35,0,6);glPopMatrix();
    glPushMatrix();glTranslatef(510,g_c4y,0);glRotatef(-90,0,0,1);
    glColor3f(.7f,.2f,.7f);Rect(0,0,45,16);glColor3f(.55f,.15f,.55f);Tri(8,16,18,26,36,16);
    glColor3f(.1f,.1f,.1f);MF(10,0,6);MF(35,0,6);glPopMatrix();
    Draw_WM(900,100);Draw_Lamp(100,250);Draw_Lamp(300,250);Draw_Lamp(650,250);Draw_Lamp(850,250);
    glutSwapBuffers();}
void Reshape(int w,int h){if(h==0)h=1;glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);glLoadIdentity();glOrtho(0,WW,0,WH,-100,100);
    glMatrixMode(GL_MODELVIEW);glLoadIdentity();}
void Timer(int v){Update();glutPostRedisplay();glutTimerFunc(16,Timer,0);}
void Key(unsigned char k,int x,int y){
    switch(k){case 'p':case 'P':g_pause=!g_pause;break;
        case 'r':case 'R':g_time=0;g_day=0;g_c1x=-50;g_c2x=1050;g_c3y=-50;g_c4y=750;
            g_bx=-200;g_tx=-300;g_ts=0;break;
        case 'n':case 'N':g_day+=.25f;if(g_day>1)g_day-=1;break;
        case 27:exit(0);}glutPostRedisplay();}
void Spec(int k,int x,int y){
    if(k==GLUT_KEY_UP){g_day+=.02f;if(g_day>1)g_day-=1;}
    if(k==GLUT_KEY_DOWN){g_day-=.02f;if(g_day<0)g_day+=1;}glutPostRedisplay();}
void Init(void){glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);glLoadIdentity();glOrtho(0,WW,0,WH,-100,100);
    glMatrixMode(GL_MODELVIEW);glLoadIdentity();
    glEnable(GL_POINT_SMOOTH);glEnable(GL_LINE_SMOOTH);
    printf("\n  ==========================================\n");
    printf("  =  PIXEL CITY - 2D Smart City Simulator  =\n");
    printf("  =  CG Lab Project - Group 03 - DIU       =\n");
    printf("  ==========================================\n");
    printf("  P=Pause R=Reset N=Night ESC=Exit\n\n");}
int main(int argc,char**argv){
    glutInit(&argc,argv);glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(WIN_W,WIN_H);glutInitWindowPosition(50,50);
    glutCreateWindow("PixelCity - 2D Smart City Traffic Simulator | CG Group 03");
    Init();glutDisplayFunc(Display);glutReshapeFunc(Reshape);
    glutKeyboardFunc(Key);glutSpecialFunc(Spec);glutTimerFunc(16,Timer,0);
    glutMainLoop();return 0;}
