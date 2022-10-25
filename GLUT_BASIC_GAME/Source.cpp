
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>


#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  20 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer
#define MO
#define D2R 0.0174532

/* Global Variables for Template File */
#define START 0
#define RUN 1
#define NORMAL 0

double R = 0, G = 0, B = 0;//car colors

int x, y, direction = 0, MODE = 0, GAME = 0;
bool up = false, down = false, right = false, left = false, timer = true;
int  winWidth, winHeight; // current Window width and height
int count = 0;//Number of car
int maxFar = 0;
bool startGame = false;

typedef struct
{
    int x, y;
}point;

point mouse;

typedef struct
{
    int x, y;
}carLocation;

carLocation carLoc[10];
//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

//
// To display onto window using OpenGL commands
//
void displayBackgroundAndCars() {
    //
    // clear window to black
    //
    glColor3f(255, 0, 0);
    vprint(-550, 350, GLUT_BITMAP_8_BY_13, "Emirhan KAYA");
    vprint(-23, 325, GLUT_BITMAP_8_BY_13, "- CARS -");
    vprint(-140, -360, GLUT_BITMAP_8_BY_13, "Press F1 to start the cars!");
    vprint(-210, -372, GLUT_BITMAP_8_BY_13, "Press F2 to change the color of cars and fruits!");


    glColor4ub(255, 255, 255, 10);
    glRectf(-600, 400, 600, -400);

    //road
    glColor3ub(96, 96, 96);
    glRectf(-450, -300, 450, -50);

    //sky
    glColor3ub(204, 255, 255);
    glRectf(-450, -50, 450, 300);

    //black line
    glColor3ub(0, 0, 0);
    glRectf(-450, -50, 450, -52);

    //traffic lines
    glColor3ub(255, 255, 255);
    glRectf(-40, -175, 40, -195);
    glRectf(60, -175, 140, -195);
    glRectf(-60, -175, -140, -195);
    glRectf(160, -175, 240, -195);
    glRectf(-160, -175, -240, -195);
    glRectf(260, -175, 340, -195);
    glRectf(-260, -175, -340, -195);
    glRectf(360, -175, 440, -195);
    glRectf(-360, -175, -440, -195);


    //house
    glColor3ub(0, 102, 102);
    glRectf(-150, 152, 150, -50);

    //roof
    glColor3ub(255, 0, 51);
    glRectf(-170, 152, 170, 192);

    //chimney
    glColor3ub(51, 0, 25);
    glRectf(60, 192, 90, 230);

    //door
    glColor3ub(255, 102, 255);
    glRectf(-33, -50, 33, 30);

    //door handle
    glColor3ub(0, 0, 0);
    glRectf(12, -23, 20, -32);

    //sun
    glColor4f(255, 255, 0, 1);
    circle(350, 250, 25);
    glColor4f(255, 255, 0, 0.4);
    circle(350, 250, 40);
    glColor4f(255, 255, 0, 0.2);
    circle(350, 250, 50);

    //smoke
    glColor4f(0, 0, 0, 0.5);
    circle(75, 250, 5);
    circle(80, 250, 5);
    circle(78, 250, 5);
    circle(72, 250, 5);
    circle(75, 245, 5);
    circle(80, 245, 5);
    circle(78, 245, 5);
    circle(72, 245, 5);
    circle(75, 240, 5);
    circle(78, 240, 5);
    circle(83, 255, 5);
    circle(80, 255, 5);
    circle(78, 255, 5);
    circle(75, 255, 5);
    circle(72, 255, 5);
    circle(69, 255, 5);


    //window
    glColor3ub(0, 204, 153);
    glRectf(60, 70, 100, 115);
    glRectf(-60, 70, -100, 115);

    //tree
    glColor3ub(102, 51, 0);
    glRectf(-350, -50, -300, 90);
    glColor3ub(0, 153, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-425, 90);
    glVertex2f(-225, 90);
    glVertex2f(-325, 300);
    glEnd();

    //fruits
    glColor3ub(255 + R, 256 + G, 100 + B);
    circle(-325, 150, 10);
    circle(-300, 150, 10);
    circle(-350, 150, 10);
    circle(-375, 150, 10);
    circle(-275, 150, 10);
    circle(-330, 125, 10);
    circle(-305, 125, 10);
    circle(-355, 125, 10);
    circle(-380, 125, 10);
    circle(-280, 125, 10);
    circle(-255, 125, 10);
    circle(-325, 102, 10);
    circle(-300, 102, 10);
    circle(-350, 102, 10);
    circle(-375, 102, 10);
    circle(-275, 102, 10);
    circle(-250, 102, 10);
    circle(-400, 102, 10);
    circle(-325, 200, 10);
    circle(-295, 200, 10);
    circle(-355, 200, 10);
    circle(-325, 175, 10);
    circle(-300, 175, 10);
    circle(-350, 175, 10);
    circle(-373, 175, 10);
    circle(-277, 175, 10);
    circle(-325, 225, 10);
    circle(-302, 225, 10);
    circle(-348, 225, 10);
    circle(-335, 250, 10);
    circle(-310, 250, 10);
    circle(-325, 275, 10);

    for (int i = 0; i < count; i++)
    {
        //
        glColor3ub(1, 1, 1);
        glRectf(carLoc[i].x + 100, carLoc[i].y + 45, carLoc[i].x + 90, carLoc[i].y + 60);
        glRectf(carLoc[i].x + 110, carLoc[i].y + 55, carLoc[i].x + 80, carLoc[i].y + 60);
        //car window
        glColor3ub(153, 204, 255);
        circle(carLoc[i].x + 50, carLoc[i].y + 25, 12);

        //car triangle part
        glColor3ub(R + 255, G, B);//i chose red as default
        glBegin(GL_TRIANGLES);
        glVertex2f(carLoc[i].x + 0, carLoc[i].y + 0);
        glVertex2f(carLoc[i].x + 100, carLoc[i].y + 0);
        glVertex2f(carLoc[i].x + 100, carLoc[i].y + 50);

        glEnd();
        //car tire part
        glColor3ub(1, 1, 1);
        circle(carLoc[i].x + 18, carLoc[i].y - 5, 8);
        circle(carLoc[i].x + 82, carLoc[i].y - 2, 15);
        glColor3ub(64, 64, 64);
        circle(carLoc[i].x + 18, carLoc[i].y - 5, 4);
        circle(carLoc[i].x + 82, carLoc[i].y - 2, 9);
        //car number
        glColor3ub(204, 255, 255);
        circle(carLoc[i].x + 58, carLoc[i].y + 15, 9);
        //car number
        glColor3ub(1, 1, 1);
        glRectf(carLoc[i].x + 57, carLoc[i].y + 10, carLoc[i].x + 59, carLoc[i].y + 20);
        glRectf(carLoc[i].x + 54, carLoc[i].y + 8, carLoc[i].x + 62, carLoc[i].y + 10);

    }

    glColor3ub(255, 0, 0);
    if (GAME == START)
        vprint(-244, -340, GLUT_BITMAP_9_BY_15, "CLICK ON THE ROAD TO CREATE A CAR(MAXIMUM 10 CARS)");

    glutSwapBuffers();
}


void display()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    displayBackgroundAndCars();




    glutSwapBuffers();
}
//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }

    // to refresh the window it calls display() function
    srand(time(NULL));
    if (key == GLUT_KEY_F2)
    {
        R = rand() % 256;
        G = rand() % 256;
        B = rand() % 256;
    }
    if (key == GLUT_KEY_F1)
        if (MODE == NORMAL)
        {
            MODE = RUN;
            timer = !timer;
        }
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
    int i = 0;
    // Write your codes here.
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
        startGame = true;
        //y > -300 && y<-50 && 
        if (y > 450 && y < 685 && count < 10)
        {
            carLoc[count].x = mouse.x;
            carLoc[count].y = mouse.y;
            count++;
            if (MODE == false && carLoc[i].x < carLoc[maxFar].x)
                maxFar = count;
        }
    }



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    displayBackgroundAndCars(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.




    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.

    mouse.x = x - winWidth / 2;
    mouse.y = winHeight / 2 - y;

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 1);
    // Write your codes here.
    int i = 0;
    if (MODE == RUN)
    {
        for (i = 0; i < 10; i++)
            carLoc[i].x--;

    }
    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(120, 0);
    glutCreateWindow("Emirhan KAYA HW1");

    glutDisplayFunc(displayBackgroundAndCars);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}