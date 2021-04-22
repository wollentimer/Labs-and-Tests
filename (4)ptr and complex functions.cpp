#define _USE_MATH_DEFINES
#include <cmath>
#include<iostream>
#include <stdio.h>

using namespace std;

const double DOUBLEMAX = 1e301;

double y01(double x)
{
	return x - 5 * pow(sin(x), 2) - 5;
}

double y02(double x)
{
	return pow(x, 3) - 50 * cos(x);
}

double min(double a, double b, int n, double(*func)(double))
{
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

double max(double a, double b, int n, double(*func)(double))
{
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

	double a = 3, b = 9;
	double a2 = -4, b2 = 3;
	int n = 200000;
	double s;
	
	s = min(a, b, n, y01);
	cout << "минимум функции x - 5 * pow(sin(x), 2) - 5 на интервале [" << a << "," << b << "] =" << s << ". Точность е = " << (b - a) / n << '\n';

	s = min(a2, b2, n, y02);
	cout << "минимум функции pow(x, 3) - 50 * cos(x) на интервале [" << a2 << "," << b2 << "] =" << s << ". Точность е = " << (b - a) / n << '\n';

	s = max(a, b, n, y01);
	cout << "максимум функции x - 5 * pow(sin(x), 2) - 5 на интервале [" << a << "," << b << "] =" << s << ". Точность е = " << (b - a) / n << '\n';
	
	s = max(a2, b2, n, y02);
	cout << "максимум функции pow(x, 3) - 50 * cos(x) на интервале [" << a2 << "," << b2 << "] =" << s << ". Точность е = " << (b - a) / n << '\n';
}
