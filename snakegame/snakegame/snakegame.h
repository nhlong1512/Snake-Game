#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <stdlib.h>    
#include <time.h>
#include <iomanip>
using namespace std;
struct SNAKE {
	vector<int>x;
	vector<int>y;
	int length;
};
struct FOOD {
	int x;
	int y;
};
int random(int, int);
void setcursor(bool, DWORD);
void gotoxy(int, int);
void setcolor(unsigned short);
void createSnake(SNAKE&);
void drawSnake(SNAKE);
void drawGameWall();
void removeOldSnake(SNAKE);
void setSnake(SNAKE&, int, int);
bool checkTouchWall(int, int);
bool checkEatSnakeTail(SNAKE, int, int);
void createAndDrawFood(FOOD&);
void drawScore();
void snakeGame();
void menu();
void drawButton(int, int);
void removeButton(int, int);
#endif // !SNAKEGAME_H

