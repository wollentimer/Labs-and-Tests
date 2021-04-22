#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <windows.h>

using namespace std;

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char str[50];
	int i = 1;
	int* pi = &i;
	char name[20];

	cout << "Enter name\n";
	gets_s(name);
	strcat(name, ".txt");
	FILE* file = fopen(name, "a+");

	if (file)
	{
		while (str[0])
		{
			fprintf(file, "%d ", *pi);
			gets_s(str);
			fputs(str, file);
			fputc('\n', file);
			(*pi)++;
		}
		fclose(file);
	}
	return 0;
}
