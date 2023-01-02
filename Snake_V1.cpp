#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Windows.h"
#include <vector>

using namespace std;

bool GameOver;
const unsigned int width = 40;	//Ширина игрового поля
const unsigned int height = 20; //Высота игрового поля
int x, y, fruitX, fruitY, score, flag; //x и y отвечают за положение змейки. fruitX, fruitY отвечают за положение фруктов
enum eDirection { Stop = 0, LEFT, RIGT, UP, DOWN }; // В перечисление мы присваиваем целые значения, это наше управление
eDirection dir;
vector<char> kuzov;

void Setup(void);	//отвечает за начальное положение змейки и рандомизацию фруктов
void Draw(void);	//Отвечает за отрисовку карты, змейки, фруктов 
void Input(void);	//Отвечает за управление змейкой
void Logic(void);	//Содержит переменные, описывающие логику игры (конец игры, длинна змейки, фрукты и тд)


void Setup()
{
	GameOver = false; //Изначально игра не окончена, поэтому значение false
	dir = Stop; //Направление при запуске игры будет 0
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls"); //Очистка экрана, для того чтобы создать обновление анимации
	for (int i = 0; i <= width; i++)
		cout << "-";					// Отрисовываем верхнюю границу поля
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)			//Отрисовка стенки
				cout << "|";
			if (i == y && j == x)					//Отрисовка змейки
				cout << "#";
			else if (i == fruitY && j == fruitX)	//Отрисовка фрукта
				cout << "F";
			else
				cout << " ";
		}
		cout << endl;
	}
	int e = 0;
	while (e <= width)				//Отрисовываем нижнюю границу поля
	{
		cout << "-";
		e++;
	}
}

void Input()
{
	if (_kbhit())		//kbhit() - метод conio.h, отслеживает последнее нажатие клавиатуры
	{
		switch (_getch()) //Ожидает нажатие клавишь, после чего немедленно возвращает значения
		{
		case 'a':

			flag = 1;
			break;

		case 's':
			flag = 2;
			break;
		case 'd':
			flag = 3;
			break;
		case 'w':
			flag = 4;
			break;
		case 'x':
			GameOver = 1;
			break;
		}
	}
}

void Logic()
{
	Sleep(0.01);
	switch (flag)
	{
	case 1:
		x--;
		break;
	case 2:
		y++;
		break;
	case 3:
		x++;
		break;
	case 4:
		y--;
		break;
	default:
		break;
	}
	if (x < 0 || x > width || y < 0 || y > height)
		GameOver = 1;
	if (x == fruitX && y == fruitY)
	{
		fruitX = rand() % width;
		fruitY = rand() % height;
		score += 10;
	
	}
}

int main()
{
	int m, n;
	Setup();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		cout << "\n\nScore: " << score;
	}

	cout << "\n\nGameOver!";
	cin.get();
	return 0;
}
