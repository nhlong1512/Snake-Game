#include "snakegame.h"
const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;
int score = 0;
//tạo số ngẫu nhiên
int random(int minN, int maxN) {
	return minN + rand() % (maxN + 1 - minN);
}
//đi đến điểm cần vẽ 
void gotoxy(int column, int line) {
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}
//xóa trỏ
void setcursor(bool visible, DWORD size) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (size == 0)
	{
		size = 20;
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}
//chỉnh màu sắc 
void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//vẽ tường cho game
void drawGameWall() {
	TextColor(14);
	for (int x = 2, y = 1; x <= 88; x += 2) {
		gotoxy(x, y);
		cout << "v";
	}
	for (int x = 89, y = 2; y < 27; y += 1) {
		gotoxy(x, y);
		cout << "<";
	}
	for (int x = 88, y = 27; x >= 1; x -= 2) {
		gotoxy(x, y);
		cout << "^";
	}
	for (int x = 1, y = 26; y > 1; y -= 1) {
		gotoxy(x, y);
		cout << ">";
	}
}
//khỏi tạo rắn
void createSnake(SNAKE& snake) {
	snake.length = 7;
	int x = 40, y = 11;
	for (int i = 0; i < snake.length; i++) {
		snake.x.push_back(x);
		snake.y.push_back(y);
		x--;
	}
}
//vẽ rắn
void drawSnake(SNAKE snake) {
	for (int i = 0; i < snake.length; i++) {
		TextColor(random(2, 15));
		gotoxy(snake.x[i], snake.y[i]);
		cout << "o";
	}
}
//xóa rắn cũ
void removeOldSnake(SNAKE snake) {
	for (int i = 0; i < snake.length; i++) {
		gotoxy(snake.x[i], snake.y[i]);
		cout << " ";
	}
}
//xử lí di chuyển cho rắn
void setSnake(SNAKE& snake, int x, int y) {
	snake.x.insert(snake.x.begin(), x);
	snake.y.insert(snake.y.begin(), y);
	snake.length += 1;
	snake.x.pop_back();
	snake.y.pop_back();
	snake.length -= 1;
	drawSnake(snake);
}
//kiểm tra chạm biên
bool checkTouchWall(int x0, int y0) {
	if ((x0 >= 2 && x0 <= 88) && (y0 == 1 || y0 == 27))
		return true;
	if ((y0 >= 1 && y0 <= 27) && (x0 == 2 || x0 == 88))
		return true;
	return false;
}
//kiểm tra tự ăn
bool checkEatSnakeTail(SNAKE snake, int x, int y) {
	for (int i = 2; i < snake.length; i++) {
		if (snake.x[i] == x && snake.y[i] == y)
			return true;
	}
	return false;
}
//tạo mồi và vẽ mồi
void createAndDrawFood(FOOD& food) {
	food.x = random(2, 88);
	food.y = random(2, 26);
	gotoxy(food.x, food.y);
	cout << "$";
}
//xóa mồi
void removeFood(FOOD food) {
	gotoxy(food.x, food.y);
	cout << " ";
}
//vẽ điểm người chơi
void drawScore() {
	TextColor(14);
	gotoxy(1, 0);
	cout << "Score: " << score;
}
//hàm game rắn
void snakeGame() {

	srand(time(NULL));
	drawScore();
	drawGameWall();
	SNAKE snake;
	createSnake(snake);
	drawSnake(snake);
	FOOD food;
	createAndDrawFood(food);
	int x = snake.x.at(0);
	int y = snake.y.at(0);
	int direction = RIGHT;
	int timeDelay = 100;
	setcursor(0,0);
	while (true) {
		gotoxy(40, 0);
		cout << "SNAKE GAME";
		if (checkTouchWall(snake.x.at(0), snake.y.at(0)) == true || checkEatSnakeTail(snake, x, y) == true)
		{
			score = 0;
			gotoxy(40, 0);
			cout << "SNAKE GAME";
			removeOldSnake(snake);
			removeFood(food);
			drawGameWall();
			gotoxy(40, 13);
			cout << "Game Over!";
			for (int i = 10; i >= 0; i--) {
				gotoxy(36, 24);
				if(i != 10)
					cout << setw(14) << "Restart after 0" << i << "s!";
				else
					cout << setw(14) << "Restart after " << i << "s!";
				Sleep(1000);
				gotoxy(36, 24);
				cout << "                  ";
			}
			drawScore();
			gotoxy(40, 13);
			cout <<"          ";
			break;
		}
		else {
			removeOldSnake(snake);
			if (_kbhit()) {
				char c = _getch();
				if (c == 'w' && (direction != UP && direction != DOWN)) {
					direction = UP;
					timeDelay = 200;
				}
				else if (c == 's' && (direction != DOWN && direction != UP)) {
					direction = DOWN;
					timeDelay = 200;
				}
				else if (c == 'a' && (direction != RIGHT && direction != LEFT)) {
					direction = LEFT;
					timeDelay = 100;
				}
				else if (c == 'd' && (direction != LEFT && direction != RIGHT)) {
					direction = RIGHT;
					timeDelay = 100;
				}
			}
			switch (direction)
			{
			case UP:
				y -= 1;
				break;
			case DOWN:
				y += 1;
				break;
			case RIGHT:
				x += 1;
				break;
			case LEFT:
				x -= 1;
				break;
			}
			setSnake(snake, x, y);
			Sleep(timeDelay);
			if (snake.x.at(0) == food.x && snake.y.at(0) == food.y) {
				snake.x.insert(snake.x.begin(), food.x);
				snake.y.insert(snake.y.begin(), food.y);
				snake.length += 1;
				drawSnake(snake);
				createAndDrawFood(food);
				score += 1;
				x = snake.x.at(0);
				y = snake.y.at(0);
				drawScore();
			}
			else {
				for (int i = 1; i < snake.length; i++) {
					if (snake.x[i] == food.x && snake.y[i] == food.y) {
						createAndDrawFood(food);
					}
				}
			}
		}

	}
	drawStarButton(43, 12);
	drawQuitButton(43, 15);
	drawRightButton(35, 12);
	drawLeftButton(53, 12);

}
//vẽ nút mũi tên phải
void drawRightButton(int x, int y) {
	gotoxy(x, y);
	cout << ">>>";
}
//xóa nút
void removeButton(int x, int y) {
	gotoxy(x, y);
	cout << "   ";
}
//vẽ nút trái
void drawLeftButton(int x, int y) {
	gotoxy(x, y);
	cout << "<<<";
}
//vẽ nút quit
void drawQuitButton(int x, int y) {
	gotoxy(x, y);
	cout << "Quit";
}
//xóa nút start
void removeStartButton(int x, int y) {
	gotoxy(x, y);
	cout << "     ";
}
//vẽ nút start
void drawStarButton(int x, int y) {
	gotoxy(x, y);
	cout << "Start";
}
//xóa nút quit
void removeQuitButton(int x, int y) {
	gotoxy(x, y);
	cout << "     ";
}
//tạo menu
void menu() {
	int pos = UP;
	drawScore();
	gotoxy(40, 0);
	cout << "SNAKE GAME";
	setcursor(0, 0);
	drawGameWall();
	drawStarButton(43, 12);
	drawQuitButton(43, 15);
	drawRightButton(35, 12);
	drawLeftButton(53, 12);
	while (1) {
		menuTutorial();
		if (_kbhit) {

			char c = _getch();
			if (c == 's' && c != 'w' && c!= 13) {
				removeButton(35, 12);
				drawRightButton(35, 15);
				removeButton(53, 12);
				drawLeftButton(53, 15);
				pos = DOWN;
			}
			else if (c == 'w' && c != 's' && c!=13) {
				removeButton(35, 15);
				drawRightButton(35, 12);
				removeButton(53, 15);
				drawLeftButton(53, 12);
				pos = UP;
			}
			else if (c == 13) {
				if (pos == UP) {
					system("cls");
					snakeGame();
				}
				else if (pos == DOWN) {
					system("cls");
					drawGameWall();
					gotoxy(40, 13);
					cout << "Good Bye!";
					break;
				}
			}
		}

	}

}
//menu hướng dẫn
void menuTutorial() {
	setcursor(0, 0);
	gotoxy(35, 24);
	cout << "Press enter to start!";
	gotoxy(32, 25);
	cout << "Use keys (W,S,A,D) to move!";
}