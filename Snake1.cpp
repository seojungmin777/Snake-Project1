#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <chrono>

using namespace std;

bool GameOver;
const int Height = 20;
const int Width = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100], nTail;

enum eDirection { STOP = 0, UP, DOWN, LEFT, RIGHT };
eDirection dir;


void Setup() 
{
	GameOver = false;
	dir = STOP;
	x = Width / 2;
	y = Height / 2;
	fruitX = rand() % Width;// 무작위 위치
	fruitY = rand() % Height;

}
void Draw() 
{
	system("CLS");

	for (int i = 0; i < Width; i++)
	{
		cout << "#";
	}
	cout << endl;


	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (j == 0 || j == Width - 1)
			{
				cout << "#";
			}
			else if(i == y && j == x)
			{
				cout << "O";
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}
			else
			{
				bool print = false;

				for (int k = 0; k < nTail; k++)
				{
					if (i == tailY[k] && j == tailX[k])
					{
						print = true;
						cout << "o";
						
					}
				}
				if (!print) { cout << " "; }
			}
		}
		cout << endl;
	}



	for (int i = 0; i < Width; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < Width; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << endl;
	cout << "Score: " << score << endl;


}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		default:
			break;
		

	
		
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int prev2X, prev2Y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	tailX[0] = x;
	tailY[0] = y;


	switch (dir)
	{
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}

	if (x < 0 || x > Width || y < 0 || y > Height)
	{
		GameOver = true;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (x == tailX[i] && y == tailY[i])
		{
			GameOver = true;
		}
	}


	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % Width;// 무작위 위치
		fruitY = rand() % Height;
		nTail++;
	}

}


int main()
{
	Setup();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(40);
	}
	

	return 0;
}

