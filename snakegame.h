
﻿#ifndef SNAKEGAME_H
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
//Nhóm hàm tạo
void createAndDrawFood(FOOD&);
void createSnake(SNAKE&);

//Nhóm hàm vẽ
void drawSnake(SNAKE);
void drawGameWall();
void drawScore();
void drawRightButton(int, int);
void drawLeftButton(int, int);
void drawStartButton(int, int);
void drawQuitButton(int, int);
void snakeGame();
void menu();
void menuTutorial();

//Nhóm hàm xoá
void removeButton(int, int);
void removeStartButton(int, int);
void removeQuitButton(int, int);
void removeOldSnake(SNAKE);

//Nhóm hàm bổ trợ
void setSnake(SNAKE&, int, int);
bool checkTouchWall(int, int);
bool checkEatSnakeTail(SNAKE, int, int);
void TextColor(int color);
int random(int, int);
void setcursor(bool, DWORD);
void gotoxy(int, int);

#endif // !SNAKEGAME_H
