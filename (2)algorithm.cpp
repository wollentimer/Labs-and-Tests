#define _USE_MATH_DEFINES
#include <cmath>
#include<iostream>
#include <stdio.h>

using namespace std;

int* fooD(int m[], int size)
{
	for (int i = 0; i < size; i++) 
	{
		if (m[i] == 0)
		{
			return m + i;
			break;
		}
	}
	return nullptr;
}

int main()
{
	setlocale(LC_ALL, "ru");
	
	const int size = 5;
	int m[] = { 1, 0, 1, 1, 1 };
	int* p = fooD(m, 5);
	
	if (p == nullptr)
	{
		cout << "нет нулей в массиве" << endl;
	}

	if ((*p) == 0)
	{
		cout << "Адрес первого ноля - " << p << endl;
	}
}
