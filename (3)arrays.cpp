#define _USE_MATH_DEFINES
#include <cmath>
#include<iostream>
#include <stdio.h>

using namespace std;
int* fooe(int** p, int size)
{
	int* result = new int[size];
	for (int i = 0; i < size; i++)
	{
		result[i] = 0;
		for (int j = 0; j < size; j++)
		{
			if (p[i][j] < 0)
			{
				result[i] = p[i][j];
				break;
			}
		}
	}
	return result;
}

int main()
{
	setlocale(LC_ALL, "ru");

	int SIZE = 10;
	int min = -10, max = 20;
	int** ppm = new int* [SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		ppm[i] = new int[SIZE];

		for (int j = 0; j < SIZE; j++)
		{
			ppm[i][j] = min + rand() % (max - min + 1);
			cout << ppm[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	int * r = fooe(ppm, SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		cout << r[i] << endl;
	}

	//удаление массива
	for (int i = 0; i < SIZE; i++)
	{
		delete[] ppm[i];
	}
	delete[] ppm;
}
