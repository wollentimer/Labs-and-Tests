#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <windows.h>

using namespace std;

struct Figure
{
	char name[60];
	int length;

	void P(int length)
	{
		cout << "периметр = " << length * 4 << endl;
	}
	void P(double length)
	{
		cout << "периметр = " << length * 4 << endl;
	}

	void S(int length)
	{
		cout << "площадь = " << (length * length) << endl;
	}

	void V(int length)
	{
		cout << "объем = " << (length * length * length) << endl;
	}

	void print()
	{
		cout << "название фигуры: " << figure.name << endl;
		cout << "длина стороны: " << figure.length << endl;
	}

} figure = { "square" }, * ps = &figure;

struct Figure2
{
	char name[60];
	int length;
	int width;
	int height;

	void P(int length, int width)
	{
		cout << "периметр = " << (length + width) * 2 << endl;
	}

	void S(int length, int width)
	{
		cout << "площадь = " << (length * width) << endl;
	}

	void V(int length, int width, int height)
	{
		cout << "объем = " << (length * width * height) << endl;
	}

	void print()
	{
		cout << "название фигуры: " << figure2.name << endl;
		cout << "длина : " << figure2.length << endl;
		cout << "ширина: " << figure2.width << endl;
		cout << "высота: " << figure2.height << endl;
	}

} figure2 = { "rectangle" }, * pr = &figure2;

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	FILE* f1;
	fopen_s(&f1, "date1.bin", "ab+");

	cout << "Введите сторону квадрата" << endl;
	cin >> figure.length;

	figure.P(figure.length);
	figure.S(figure.length);
	figure.V(figure.length);

	cout << "---------------" << endl;
	figure.print();
	fwrite(&figure, sizeof(figure), 1, f1);
	cout << "-----------------------------" << endl;
	FILE* f2;
	fopen_s(&f2, "date2.bin", "ab+");

	cin >> figure2.length;
	cin >> figure2.width;
	cin >> figure2.height;

	figure2.P(figure2.length, figure2.width);
	figure2.S(figure2.length, figure2.width);
	figure2.V(figure2.length, figure2.width, figure2.height);
	cout << "---------------" << endl;
	figure2.print();
	fwrite(&figure2, sizeof(figure2), 1, f2);
	fclose(f2);
}
