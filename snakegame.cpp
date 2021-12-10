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
void setcolor(unsigned short color) {                                                   //set the colour
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}
//vẽ tường cho game
void drawGameWall() {
	for (int x = 11, y = 1; x < 100; x += 2) {
		gotoxy(x, y);
		cout << "v";
	}
	for (int x = 100, y = 2; y < 27; y += 1) {
		gotoxy(x, y);
		cout << "<";
	}
	for (int x = 99, y = 27; x >= 11; x -= 2) {
		gotoxy(x, y);
		cout << "^";
	}
	for (int x = 10, y = 26; y > 1; y -= 1) {
		gotoxy(x, y);
		cout << ">";
	}

}
//khỏi tạo rắn
void createSnake(SNAKE& snake) {
	snake.length = 4;
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
	if ((x0 >= 10 && x0 <= 100) && (y0 == 1 || y0 == 27))
		return true;
	if ((y0 >= 1 && y0 <= 27) && (x0 == 10 || x0 == 100))
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
	int x = random(11, 99);
	int y = random(2, 26);
	food.x = x;
	food.y = y;
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
	gotoxy(10, 0);
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
	setcursor(0, 0);
	while (true) {
		gotoxy(50, 0);
		cout << "SNAKE GAME";
		if (checkTouchWall(snake.x.at(0), snake.y.at(0)) == true || checkEatSnakeTail(snake, x, y) == true)
		{
			gotoxy(50, 0);
			cout << "SNAKE GAME";
			removeOldSnake(snake);
			removeFood(food);
			drawGameWall();
			gotoxy(50, 13);
			cout << "Game Over!";
			for (int i = 10; i >= 0; i--) {
				gotoxy(45, 24);
				cout << "Restart after " << i << "s!";
				Sleep(700);
				gotoxy(45, 24);
				cout << "                  ";
			}
			gotoxy(50, 13);
			cout << "          ";
			break;
		}
		else {
			removeOldSnake(snake);
			if (_kbhit()) {
				char c = _getch();
				if (c == 'w' && (direction != UP && direction != DOWN)) {
					direction = UP;
				}
				else if (c == 's' && (direction != DOWN && direction != UP)) {
					direction = DOWN;
				}
				else if (c == 'a' && (direction != RIGHT && direction != LEFT)) {
					direction = LEFT;
				}
				else if (c == 'd' && (direction != LEFT && direction != RIGHT)) {
						direction = RIGHT;
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
			Sleep(100);
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
		}

	}
	drawStarButton(53, 13);
	drawQuitButton(53, 15);
	drawRightButton(45, 13);
	drawLeftButton(62, 13);
}
void drawRightButton(int x, int y) {
	gotoxy(x, y);
	cout << ">>>";
}
void removeButton(int x, int y) {
	gotoxy(x, y);
	cout << "   ";
}
void drawLeftButton(int x, int y) {
	gotoxy(x, y);
	cout << "<<<";
}

void drawQuitButton(int x, int y) {
	gotoxy(x, y);
	cout << "Quit";
}
void removeStartButton(int x, int y) {
	gotoxy(x, y);
	cout << "     ";
}
void drawStarButton(int x, int y) {
	gotoxy(x, y);
	cout << "Start";
}
void removeQuitButton(int x, int y) {
	gotoxy(x, y);
	cout << "     ";
}
void menu() {
	int pos = UP;
	drawGameWall();
	drawStarButton(53, 13);
	drawQuitButton(53, 15);
	drawRightButton(45, 13);
	drawLeftButton(62, 13);
	while (1) {
		
		if (_kbhit) {
			char c = _getch();
			if (c == 's' && c != 'w') {
				removeButton(45, 13);
				drawRightButton(45, 15);
				removeButton(62, 13);
				drawLeftButton(62, 15);
				pos = DOWN;
			}
			else if (c == 'w' && c != 's') {
				removeButton(45, 15);
				drawRightButton(45, 13);
				removeButton(62, 15);
				drawLeftButton(62, 13);
				pos = UP;
			}
			else if (c == 13) {
				if (pos == UP) {
					system("cls");
					snakeGame();
				}
				else if(pos == DOWN) {
					system("cls");
					drawGameWall();
					gotoxy(50, 13);
					cout << "Good Bye!";
					break;
				}
			}
		}
	}
}
