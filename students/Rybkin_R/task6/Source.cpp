#include <iostream> 
#include <cstdio> 
#include <conio.h> 
#include <vector> 
#include <Windows.h> 
#include <clocale> 
#include <time.h> 


struct Body
{
	std::vector<int> x;
	std::vector<int> y;
	int LengthBody;
	Body(int _LengthBody = 5) :LengthBody(_LengthBody) {};
};
struct Snake
{
	Body SnakeBody;
	int HeadX, HeadY;
	Snake(int _HeadX = 0, int _HeadY = 0) : HeadX(_HeadX), HeadY(_HeadY) {};
};
struct Fruit
{
	int FruitX, FruitY;
	Fruit(int _FruitX = 5, int _FruitY = 5) : FruitX(_FruitX), FruitY(_FruitY) {};
	void CreateFruit(int _Width, int _Height)
	{
		srand(time(NULL));
		FruitX = rand() % _Width;
		FruitY = rand() % _Height;
		FruitX++;
		FruitY++;
	}
};
struct Map
{
	void gotoxy(int x, int y)
	{
		HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (!Console)
			return;

		COORD pos;
		pos.X = x;
		pos.Y = y;

		SetConsoleCursorPosition(Console, pos);
	}
	int Height, Width;
	Snake GameSnake;
	Fruit GameFruit;
	Map(int _Height = 10, int _Width = 10)
	{
		Height = _Height;
		Width = _Width;
	};
	void CreateSnake()
	{
		GameSnake.HeadX = (Width + 2) / 2;
		GameSnake.HeadY = (Height + 2) / 2;
		for (int i = 1; i < 5; i++)
		{
			GameSnake.SnakeBody.x.push_back(GameSnake.HeadX + i);
			GameSnake.SnakeBody.y.push_back(GameSnake.HeadY);
		}
	}
	void PaintMap()
	{
		for (int i = 0; i < Width + 2; i++)
			std::cout << "&";
		for (int i = 1; i < Height + 1; i++)
		{
			gotoxy(0, i);
			std::cout << "&";
			gotoxy(Width + 1, i);
			std::cout << "&";
		}
		gotoxy(0, Height + 1);
		for (int i = 0; i < Width + 2; i++)
			std::cout << "&";
		gotoxy(Width + 15, 0);
		std::cout << "Длина змейки: ";
		gotoxy(Width + 15, 2);
		std::cout << "Ваша цель: " << (Height*Width) / 2.5;
		CreateSnake();
	}
};
class TheGame
{
private:
	int Direction;
	int Purpose;
	enum Directon { LEFT, RIGHT, UP, DOWN };
	Directon direction;
	bool GameOver;
	bool GameVictory;
	Map GameMap;
	void gotoxy(int x, int y)
	{
		HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (!Console)
			return;

		COORD pos;
		pos.X = x;
		pos.Y = y;

		SetConsoleCursorPosition(Console, pos);
	}
public:
	TheGame(bool _GameOver = false, bool _GameVictory = false)
	{
		GameOver = _GameOver;
		GameVictory = _GameVictory;
		Purpose = (GameMap.Height*GameMap.Width) / 2.5;
		direction = LEFT;
	}
	void Input()
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case /*'a':*/75:
				if (direction != RIGHT)
					direction = LEFT;
				break;
			case /*'d':*/77:
				if (direction != LEFT)
					direction = RIGHT;
				break;
			case /*'w':*/72:
				if (direction != DOWN)
					direction = UP;
				break;
			case /*'s':*/80:
				if (direction != UP)
					direction = DOWN;
				break;
			}
		}
	}
	void Logic()
	{
		int TmpX = GameMap.GameSnake.SnakeBody.x[0];
		int TmpY = GameMap.GameSnake.SnakeBody.y[0];
		int Tmp2X, Tmp2Y;
		GameMap.GameSnake.SnakeBody.x[0] = GameMap.GameSnake.HeadX;
		GameMap.GameSnake.SnakeBody.y[0] = GameMap.GameSnake.HeadY;
		switch (direction)
		{
		case LEFT:
			GameMap.GameSnake.HeadX--;
			break;
		case RIGHT:
			GameMap.GameSnake.HeadX++;
			break;
		case UP:
			GameMap.GameSnake.HeadY--;
			break;
		case DOWN:
			GameMap.GameSnake.HeadY++;
			break;
		default:
			break;
		}
		for (int i = 1; i < GameMap.GameSnake.SnakeBody.LengthBody - 1; i++)
		{
			Tmp2X = GameMap.GameSnake.SnakeBody.x[i];
			Tmp2Y = GameMap.GameSnake.SnakeBody.y[i];
			GameMap.GameSnake.SnakeBody.x[i] = TmpX;
			GameMap.GameSnake.SnakeBody.y[i] = TmpY;
			TmpX = Tmp2X;
			TmpY = Tmp2Y;
		}
		if (GameMap.GameSnake.HeadX > GameMap.Width || GameMap.GameSnake.HeadX < 1 || GameMap.GameSnake.HeadY > GameMap.Height || GameMap.GameSnake.HeadY < 1)
			GameOver = true;

		//Если раскомментировать  и убрать 173 174 строки, то змейка сможет ходить сквозь стены
		/*if (GameMap.GameSnake.HeadX > GameMap.Width+1)
		GameMap.GameSnake.HeadX = 1;
		else if (GameMap.GameSnake.HeadX < 1)
		GameMap.GameSnake.HeadX = GameMap.Width +1;
		if (GameMap.GameSnake.HeadY > GameMap.Height+1)
		GameMap.GameSnake.HeadY =1 ;
		else if (GameMap.GameSnake.HeadY < 1)
		GameMap.GameSnake.HeadY = GameMap.Height+1;*/
		for (int i = 2; i < GameMap.GameSnake.SnakeBody.LengthBody - 1; i++)
			if ((GameMap.GameSnake.SnakeBody.x[i] == GameMap.GameSnake.HeadX) && (GameMap.GameSnake.SnakeBody.y[i] == GameMap.GameSnake.HeadY))
				GameOver = true;
		if ((GameMap.GameSnake.HeadX == GameMap.GameFruit.FruitX) && (GameMap.GameSnake.HeadY == GameMap.GameFruit.FruitY))
		{
			MessageBeep(0);
			bool flag = true;
			while (flag)
			{
				flag = false;
				GameMap.GameFruit.CreateFruit(GameMap.Width, GameMap.Height);
				for (int i = 0; i < GameMap.GameSnake.SnakeBody.LengthBody - 1; i++)
					if ((GameMap.GameFruit.FruitX == GameMap.GameSnake.SnakeBody.x[i]) && (GameMap.GameFruit.FruitY == GameMap.GameSnake.SnakeBody.y[i]))
					{
						flag = true;
						break;
					}
			}
			GameMap.GameSnake.SnakeBody.LengthBody++;
			gotoxy(GameMap.Width + 28, 0);
			std::cout << GameMap.GameSnake.SnakeBody.LengthBody;
			if (GameMap.GameSnake.SnakeBody.LengthBody == Purpose)
				GameOver = true;
			GameMap.GameSnake.SnakeBody.x.push_back(0);
			GameMap.GameSnake.SnakeBody.y.push_back(0);
		}
		if (GameMap.GameSnake.SnakeBody.LengthBody == Purpose)
			GameOver = true;
	}
	bool GetGameOver()
	{
		return GameOver;
	}
	bool GetGameVictory()
	{
		return GameVictory;
	}
	void MotionSnake()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO structCursorInfo;
		GetConsoleCursorInfo(hConsole, &structCursorInfo);
		structCursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(hConsole, &structCursorInfo);
		for (int i = 1; i < GameMap.Height + 1; i++)
		{
			for (int j = 1; j < GameMap.Width + 1; j++)
			{
				if (i == GameMap.GameSnake.HeadY && j == GameMap.GameSnake.HeadX)
				{
					gotoxy(j, i);
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
					std::cout << "O";
				}
				else if (i == GameMap.GameFruit.FruitY && j == GameMap.GameFruit.FruitX)
				{
					gotoxy(j, i);
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
					std::cout << "*";
				}
				else
				{
					bool print = false;
					for (int k = 0; k < GameMap.GameSnake.SnakeBody.LengthBody - 1; k++)
					{
						if (GameMap.GameSnake.SnakeBody.x[k] == j && GameMap.GameSnake.SnakeBody.y[k] == i)
						{
							gotoxy(j, i);
							SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
							std::cout << "@";
							print = true;
						}
					}
					if (!print)
					{
						gotoxy(j, i);
						SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 0));
						std::cout << " ";
					}
				}
			}
		}
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	}
	void Jury()
	{
		if (GameVictory)
		{
			gotoxy(GameMap.Width + 15, 4);
			std::cout << "Вы победили";
		}
		else
		{
			gotoxy(GameMap.Width + 15, 4);
			std::cout << "Вы проиграли ";
		}
	}
	void CreateMap(int _Width, int _Height)
	{
		GameMap.Width = _Width;
		GameMap.Height = _Height;
		GameMap.PaintMap();
	}
};
int main()
{
	setlocale(LC_ALL, ("rus"));
	// консоль во весь экран
	HWND hWnd = GetForegroundWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	int x, y;
	TheGame Games;
	std::cout << "Введите ширину карты: ";
	std::cin >> x;
	std::cout << std::endl;
	std::cout << "Введите высоту карты: ";
	std::cin >> y;
	system("cls");
	Games.CreateMap(x, y);
	while (!Games.GetGameOver())
	{
		Games.MotionSnake();
		Games.Input();
		Games.Logic();
	}
	Games.Jury();
	system("pause");
}
