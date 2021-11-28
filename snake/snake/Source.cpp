#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "console.h"
#include<iostream>


#define consoleWidth	120
#define consoleHeight	30
using namespace std;

enum TrangThai { UP, DOWN, LEFT, RIGHT };

struct ToaDo {
	int y, x;	// y là tung độ, x là hoành độ
}; 
struct HoaQua {
	ToaDo hq;
};
struct Snake
{
	ToaDo Dot[20];
	int n;
	TrangThai tt;
};

void ancontro()
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}

void KhoiTao(Snake& snake,int x,int y) {
	snake.n = 2;
	snake.Dot[0].x = x;
	snake.Dot[0].y = y;
	snake.tt = RIGHT;
}
void KhoiTao(HoaQua& A) {
	int a= 41 + rand() % 68;
	int b = 6 + rand() % 22;
	A.hq.x = a;
	A.hq.y = b;
}
void HienThiMenu(Snake contro) {
	clrscr();
	for (int i = 40; i < 111; i = i + 2) {
		gotoXY(i, 5);
		printf("+");
		gotoXY(i, 30);
		printf("+");
	}
	for (int i = 5; i < 31; i++) {
		gotoXY(40, i);
		printf("+");
		gotoXY(110, i);
		printf("+");
	}
	gotoXY(contro.Dot[0].x, contro.Dot[0].y);
	for (int i = 3; i >1; i--) {
		gotoXY(contro.Dot[i].x, contro.Dot[i].y);
		printf(">");
	}
}
void HienThiSnake(Snake snake,HoaQua hoaqua,int point) {
	clrscr();
	for (int i = 40; i < 111; i=i+2) {
		gotoXY(i, 5);
		printf("+");
		gotoXY(i, 30);
		printf("+");
	}
	for (int i = 5; i < 31; i++) {
		gotoXY(40, i);
		printf("+");
		gotoXY(110, i);
		printf("+");
	}
	gotoXY(42, 4); printf("Money : ");
	gotoXY(50, 4); printf("%d",point);
	gotoXY(53, 4); printf("$");
	gotoXY(hoaqua.hq.x, hoaqua.hq.y);
	printf("$");
	gotoXY(snake.Dot[0].x, snake.Dot[0].y);
	printf("0");
	for (int i = 1; i < snake.n; i++) {
		gotoXY(snake.Dot[i].x, snake.Dot[i].y);
		printf("o");
	}
}
void XuLy(Snake& snake, HoaQua hoaqua) {
		for (int i = snake.n; i > 0; i--) {
			snake.Dot[i] = snake.Dot[i - 1];
		}
		snake.n++;
		if (snake.tt == DOWN)
			snake.Dot[0].y++;
		else if (snake.tt == UP)
			snake.Dot[0].y--;
		else if (snake.tt == LEFT)
			snake.Dot[0].x--;
		else if (snake.tt == RIGHT)
			snake.Dot[0].x++;
	
}
int main() {
	ancontro();
	srand(time(NULL));
	Snake snake;
	Snake contro; contro.n = 3;
	HoaQua hoaqua;
	KhoiTao(snake,41,17);
	KhoiTao(contro, 67, 16);
	KhoiTao(hoaqua);
	int tocdox = 110;
	int tocdoy=200;
	int tinhhieu1=1;
	int tinhhieu2;
	int tinhhieu3;
	int point=0;
	//menu ngoai cung
	while (tinhhieu1) {
		HienThiMenu(contro);
		if (_kbhit()) {
			char key = _getch();
			if (key == 'W' || key == 'w')
				if (contro.Dot[0].y != 16) contro.Dot[0].y--;
			if (key == 'S' || key == 's')
				if (contro.Dot[0].y != 17) contro.Dot[0].y++;
			if (key == 13) {
				if (contro.Dot[0].y == 16) {
					tinhhieu1 = 0;
					tinhhieu2 = 1;
					tinhhieu3 = 0;
				}
				else {
					tinhhieu1 = 0;
					tinhhieu2 = 0;
					tinhhieu3 = 1;
				}
			}
		}

		gotoXY(70, 16); printf("Start");
		gotoXY(70, 17); printf("Quit");
		Sleep(100);
	}
	//bảng hướng dẫn

	/*while (tinhhieu3) {
		clrscr();
		for (int i = 40; i < 111; i = i + 2) {
			gotoXY(i, 5);
			printf("+");
			gotoXY(i, 30);
			printf("+");
		}
		for (int i = 5; i < 31; i++) {
			gotoXY(40, i);
			printf("+");
			gotoXY(110, i);
			printf("+");
		}
		gotoXY(45, 7);
		printf("Use W,S,A,D to move");
		Sleep(100);
	}*/
	// vao game
	while (tinhhieu2){
		// HienThi
		
		HienThiSnake(snake,hoaqua,point);
		
		//Dieu Khien
		if (_kbhit())	// phát hiện có phím nhấn vào
		{
			char key = _getch();
			// phát hiện quay đầu k gập người 
			if (snake.tt == RIGHT && key == 'A' || snake.tt == RIGHT && key == 'a') {
				tinhhieu2 = 0; clrscr();
				gotoXY(45, 14);
				printf("YOU ARE LOSER");
			}
			if (snake.tt == LEFT && key == 'D' || snake.tt == LEFT && key == 'd') {
				tinhhieu2 = 0; clrscr();
				gotoXY(45, 14);
				printf("YOU ARE LOSER");
			}
			if (snake.tt == UP && key == 'S' || snake.tt == UP && key == 's') {
				tinhhieu2 = 0; clrscr();
				gotoXY(45, 14);
				printf("YOU ARE LOSER");
			}
			if (snake.tt == DOWN && key == 'W' || snake.tt == DOWN && key == 'w') {
				tinhhieu2 = 0; clrscr();
				gotoXY(45, 14);
				printf("YOU ARE LOSER");
			}
			//điều kiển rắn
			if (key == 'A' || key == 'a')
				snake.tt = LEFT;
			if (key == 'D' || key == 'd')
				snake.tt = RIGHT;
			if (key == 'W' || key == 'w')
				snake.tt = UP;
			if (key == 'S' || key == 's')
				snake.tt = DOWN;
		}
		if (snake.n > 1) {
			for (int i = snake.n; i > 0; i--) {
				snake.Dot[i] = snake.Dot[i - 1];
			}
		}
		if (snake.tt == DOWN)
			snake.Dot[0].y++;
		else if (snake.tt == UP)
			snake.Dot[0].y--;
		else if (snake.tt == LEFT)
			snake.Dot[0].x--;
		else if (snake.tt == RIGHT)
			snake.Dot[0].x++;
		//Xu Ly khi ran an hoa qua
		if (snake.Dot[0].x == hoaqua.hq.x && snake.Dot[0].y == hoaqua.hq.y) {
			point++;
			KhoiTao(hoaqua);
			XuLy(snake, hoaqua);
			tocdox = tocdox - 5;
			tocdoy = tocdoy - 3;
		}

		//Xu ly ran cham khung
		if (snake.Dot[0].x==40 && snake.tt==LEFT|| snake.Dot[0].x == 110 && snake.tt == RIGHT
			|| snake.Dot[0].y == 30 && snake.tt == DOWN||snake.Dot[0].y == 5 && snake.tt == UP) {
			tinhhieu2 = 0;
			clrscr();
			gotoXY(45, 14);
			printf("YOU ARE LOSER");
		}
		//Xu ly ran can nguoi
		for (int i = 3; i < snake.n; i++){
			if (snake.Dot[0].x == snake.Dot[i].x && snake.Dot[0].y == snake.Dot[i].y) {
				tinhhieu2 = 0;
				clrscr();
				gotoXY(45, 14);
				printf("YOU ARE LOSER");
			}
		}

		// Toc Do game
		if (snake.tt == LEFT || snake.tt == RIGHT) {
			Sleep(tocdox);
		}
		if (snake.tt == UP || snake.tt == DOWN) {
			Sleep(tocdoy);
		}
	}
}
