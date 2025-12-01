#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    void sleep_ms(int ms);
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
    void sleep_ms(int ms);
    int _kbhit(void);
    int _getch(void);
#endif

#define WIDTH 40
#define HEIGHT 20

extern int gameOver;
extern int x, y, fruitX, fruitY, score;
extern int tailX[100], tailY[100];
extern int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
extern enum eDirection dir;

void Setup();
void Draw();
void Input();
void Logic();

#endif
