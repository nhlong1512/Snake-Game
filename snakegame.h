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
void drawRightButton(int, int);
void drawLeftButton(int, int);
void drawStarButton(int, int);
void drawQuitButton(int, int);
void removeButton(int, int);
void removeStartButton(int, int);
void removeQuitButton(int, int);
void menuTutorial();
void TextColor(int color);
#endif // !SNAKEGAME_H
