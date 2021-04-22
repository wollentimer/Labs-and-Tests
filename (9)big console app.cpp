#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include<iomanip>

using namespace std;

const int MAX = 20;

struct zavod
{
	char name[20];
	int colich;
	int number;
};

void print_menu()
{
	system("cls");
	cout << "выберите пункт меню" << endl;
	cout << "1. вывести данные на экран" << endl;
	cout << "2. добавить данные" << endl;
	cout << "3. удалить данные" << endl;
	cout << "4. редактировать данные" << endl;
	cout << "5. записать массив в файл" << endl;
	cout << "6. считать массив из файла" << endl;
	cout << "7. выполнение задачи" << endl;
	cout << "0. выход" << endl;
	cout << ">";
}

void clearAll(zavod* l)
{
	for (int i = 0; i < MAX; i++)
	{
		l[i].name[0] = '\0';
		l[i].colich = 0;
		l[i].number = 0;
	}
}

void printzavod(zavod a)
{
	cout << a.name << "\t";

	if (a.colich > 0)
	{
		cout << a.colich << "\t";
	}
	if (a.number > 0)
	{
		cout << a.number << "\t" << endl;
	}
}

void printAll(zavod* l)
{
	bool fl = false;

	for (int i = 0, n = 0; i < MAX; i++)
	{
		if (l[i].name[0] == '\0')
			continue;
		printf("%3d) ", n++);
		printzavod(l[i]);
		fl = true;
	}

	if (!fl)
	{
		cout << "список пуст" << endl;
	}
}

bool addzavod(zavod* list, int n)
{
	char otvet[50];
	zavod a;
	int number;
	while (true)
	{
		cout << "Введите наименование продукции : " << endl;
		gets_s(otvet, 50);
		if (strlen(otvet) == 0)
			return false;
		strcpy_s(a.name, otvet);

		cout << "Количество выпущенных изделий : " << endl;
		gets_s(otvet, 50);
		number = atoi(otvet);
		if (strlen(otvet) == 0)
			return false;       //cin>> a.colich;
		a.colich = number;

		cout << "Номер цеха : " << endl;
		gets_s(otvet, 50);
		number = atoi(otvet);
		if (strlen(otvet) == 0)
			return false;
		a.number = number;
		list[n] = a;
		return true;
	}
}

void add(zavod* list)
{
	cout << "Ввод данных" << endl;
	int ins = -1;
	for (int i = 0; i < MAX; i++)
	{
		if (list[i].name[0] == '\0')
		{
			ins = i;
			break;
		}
	}

	if (ins == -1)
	{
		cout << "Нет места в списке!" << endl;
		return;
	}

	if (addzavod(list, ins))
	{
		cout << "Запись добавлена" << endl;
	}
}

void del(zavod* list)
{
	printAll(list);
	cout << "введите индекс записи для удаления" << endl;
	char otvet[80];
	int number;

	gets_s(otvet, 80);
	number = atoi(otvet);
	if (number < 0 || number >= MAX)
	{
		cout << "Неверный индекс" << endl;;
		return;
	}

	for (int i = 0, j = 0; i < MAX; i++)
	{
		if (list[i].name[0] != '\0')
		{
			if (j == number)
			{
				list[i].name[0] = '\0';
				list[i].number = 0;
				list[i].colich = 0;
				cout << "запись удалена" << endl;
				break;
			}
			j++;
		}
	}
}

bool editzavod(zavod& a)
{
	char otvet[80];
	int number;
	bool fl = false;
	printzavod(a);
	while (true)
	{
		cout << "Введите наименование продукции : " << endl;
		gets_s(otvet, 79);
		if (strlen(otvet) == 0)
			break;
		strcpy_s(a.name, otvet);
		fl = true;

		cout << "Количество выпущенных изделий : " << endl;
		gets_s(otvet, 79);
		if (strlen(otvet) != 0)
		{
			a.colich = atoi(otvet);
			fl = true;
		}

		cout << "Номер цеха: " << endl;
		gets_s(otvet, 79);
		if (strlen(otvet) != 0)
		{
			number = atoi(otvet);
			a.number = number;
			fl = true;
		}
		return fl;
	}
}

void edit(zavod* list)
{
	printAll(list);

	cout << "введите индекс записи для редактирования" << endl;
	char otvet[80];
	int number;
	gets_s(otvet, 80);
	if (strlen(otvet) == 0)
		return;
	number = atoi(otvet);

	if (number < 0 || number >= MAX)
	{
		cout << "неверный индекс" << endl;
		return;
	}

	for (int i = 0, j = 0; i < MAX; i++)
	{
		if (list[i].name[0] != '\0')
		{
			if (j == number)
			{
				if (editzavod(list[i]))

					cout << "запись отредактирована";
				else
					cout << "запись не менялась";
				break;
			}
			j++;
		}
	}
}

void save(zavod* list)
{
	FILE* file;
	char otvet[80];
	cout << "введите имя файла (без раасширения)" << endl;
	gets_s(otvet, 80);
	strcat_s(otvet, ".bin");
	int rez = fopen_s(&file, otvet, "w");
	if (rez != 0)
	{
		cout << "ошибка записи в файл";
		return;
	}

	for (int i = 0; i < MAX; i++)
	{
		if (list[i].name[0] != '\0')
			fwrite(&list[i], sizeof(zavod), 1, file);
	}
	fclose(file);
	cout << "сохранено" << endl;
}

void load(zavod* list)
{
	FILE* file;
	char otvet[80];
	cout << "введите имя файла(без расширения)" << endl;
	gets_s(otvet, 80);
	strcat_s(otvet, ".bin");
	clearAll(list);
	int rez = fopen_s(&file, otvet, "r");
	if (rez != 0)
	{
		cout << "ошибка чтения из файла";
		return;
	}
	fread(list, sizeof(zavod), MAX, file);
	fclose(file);
	cout << "список заполнен" << endl;
}

void task(zavod* l, zavod* list)
{
	int cex;
	cout << "Введите номер цеха: " << endl;
	cin >> cex;

	for (int i = 0; i < MAX; i++)
	{
		if (l[i].number == cex)
		{
			zavod temp;
			for (int i = 0; i < MAX - 1; i++)
			{
				for (int j = i + 1; j < MAX; j++)
				{
					if (l[i].colich < l[j].colich)
					{
						temp = list[j];
						list[j] = list[i];
						list[i] = temp;
						printzavod(list[i]);
					}
				}
			}
		}
	}
}

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	zavod list[MAX];

	clearAll(list);

	while (true)
	{
		print_menu();
		char otvet[80];
		gets_s(otvet, 80);

		switch (otvet[0])
		{
		case '1': printAll(list); break;

		case '2': add(list); break;

		case '3': del(list); break;

		case '4': edit(list); break;

		case '5':save(list); break;

		case '6': load(list); break;

		case '7': task(list, list); break;

		case '0': exit(0);
		}
		system("pause");
	}
	return 0;
}
