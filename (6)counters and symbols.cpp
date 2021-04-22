#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <windows.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int rusCounter = 0;
	int digitsCounter = 0;
	char str[20];

	fgets(str, 20, stdin);
	cout << str << endl;

	for (int i = 0; i < strlen(str); i++)
	{
		if (isdigit(str[i]))
		{
			digitsCounter++;
		}
		if (str[i] >= 'А' && str[i] <= 'я')
		{
			rusCounter++;
		}
	}

	cout << digitsCounter << endl;
	cout << rusCounter << endl;

	if (digitsCounter > rusCounter)
	{
		for (int i = 0; i < strlen(str); i++)
		{
			if (isdigit(str[i]))
			{
				str[i] = '*';
			}
		}
	}

	if (digitsCounter < rusCounter)
	{
		for (int i = 0; i < strlen(str); i++)
		{
			if (ispunct(str[i]))
			{
				str[i] = ' ';
			}
		}
	}
	cout << str << endl;
}
