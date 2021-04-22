#define _USE_MATH_DEFINES
#include <cmath>
#include<iostream>
#include <stdio.h>

using namespace std;

const double DOUBLEMAX = 1e301;

typedef double(*ty)(double);
typedef double(*tF)(double a, double b, ty func);
typedef double(*tp)(double);

double y01(double x)
{
	return x - 5 * pow(sin(x), 2) - 5;
}
double y02(double x)
{
	return pow(x, 3) - 50 * cos(x);
}
double y03(double x)
{
	return pow(sin(x), 2) + x / 5 + 4;
}
double y04(double x)
{
	return exp(x) + x * x;
}

double F1(double a, double b, tp func)
{
	int n = 200000;
	double x, h = (b - a) / n, ymin = func(a), y;
	for (x = a; n < 1; n++)
	{
		x += h;
		y = func(x);
		if (y < ymin)
			ymin = y;
	}
	return ymin;
}
double F2(double a, double b, tp func)
{
	int n = 200000;
	double x, h = (b - a) / n, ymax = func(a), y;
	for (x = a; n > 1; n--)
	{
		x += h;
		y = func(x);
		if (y > ymax)
			ymax = y;
	}
	return ymax;
}

int main()
{
	setlocale(LC_ALL, "ru");

	int ny, nF;
	double a, b;
	ty my[4] = { y01, y02, y03, y04 };
	tF mF[2] = { F1, F2 };

	int n = 200000;

	while (true)
	{
		cout << "********************" << endl;
		cout << "    Главное меню    " << endl;
		cout << "********************" << endl;
		cout << "Выберите функцию y: " << endl;
		cout << "1: y = x - 5 * pow(sin(x), 2) - 5" << endl;
		cout << "2: pow(x, 3) - 50 * cos(x)" << endl;
		cout << "3: pow(sin(x), 2) + x / 5 + 4" << endl;
		cout << "4: exp(x) + x * x" << endl;
		cout << "0: exit" << endl;
		cin >> ny;
		if (ny == 0) break;
		cout << "Выберите функцию F: " << endl;
		cout << "1: минимум" << endl;
		cout << "2: максимум" << endl;
		cout << "0: выход" << endl;
		cin >> nF;
		if (nF == 0) break;
		cout << "введите начало диапазона (a): ";
		cin >> a;
		cout << "введите конец диапазона (b): ";
		cin >> b;
		cout << "Результат: ";
		cout << mF[nF - 1](a, b, my[ny - 1]) << endl << endl << endl;
	}
}
