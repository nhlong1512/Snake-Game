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
bool checkEatSnakeTail(SNAKE snake,int x, int y) {
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
		if (checkTouchWall(snake.x.at(0), snake.y.at(0)) == true  || checkEatSnakeTail(snake, x, y) == true) 
		{
			removeOldSnake(snake);
			gotoxy(50, 13);
			cout << "Game Over!";
			break;
		}
		else {
			removeOldSnake(snake);
			if (_kbhit()) {
				char c = _getch();
				if (c == -32) {
					c = _getch();
					if (c == 72 && (direction != UP && direction != DOWN)) {
						direction = UP;
					}
					else if (c == 80 && (direction != DOWN && direction != UP)) {
						direction = DOWN;
					}
					else if (c == 75 && (direction != RIGHT && direction != LEFT)) {
						direction = LEFT;
					}
					else if (c == 77 && (direction != LEFT && direction != RIGHT)) {
						direction = RIGHT;
					}
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
			Sleep(200);
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
	char c = _getch();
}

