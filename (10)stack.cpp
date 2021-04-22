#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include<iomanip>
#include<new.h>

using namespace std;

const int MAX = 10;
int stack[MAX];
int stack2[MAX];
int tos = 0;

struct List
{
    int  pole1;
    List* pole2;
};

// Затолкать элемент в стек. 
int push10()
{
    for (int i = 0; i < 10; i++)
    {
        stack[tos] = rand() % 8;
        tos++;
    }
    return 0;
}

bool push(int i)
{
    stack[tos] = i;
    tos++;
    if (tos >= MAX)
        return true;
    return false;
}
   
void task()
{
    int a = 0;
    int b = 0;
    for (int i = 0; i < MAX; i++)
    {
        if (a < stack[i])
        {
            a = stack[i];
        }
    }
    for (int i = 0; i < MAX; i++)
    {
        if (a == stack[i])
        {
            b = i;
        }
    }
    for (int i = 0; i < MAX; i++)
    {
        if (i >= b)
        {
            stack2[i] = stack[i];  
            cout << "скопированные данные: " << endl;
            cout << stack2[i] << endl;
        }
    }
}

// Получить верхний элемент стека. 
int pop(void)
{
    tos--;
    if (tos < 0)
    {
        printf("Стек пуст\n");
        return 0;
    }
    return stack[tos];
}

void enter(void)
{
    int elem;
    if (tos >= MAX)
    {
        printf("Стек полон\n");
        return;
    }
    while (true)
    {
        printf("Введите число (0 - конец ввода): ");
        scanf("%d", &elem);
        if (elem == 0) break; 		// запись не была произведена 
        if (push(elem)) break;		// стек полон
    }
}

void review(void)
{
    for (int i = tos - 1; i >= 0; --i)
        printf("%d. %d\n", i, stack[i]);
}

void delete_ap(void)
{
    printf("%d\n", pop());
}

int main()
{
    setlocale(0, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int s;
    for (;;)
    {
        printf("Ввести (1), Список (2), Удалить (3), создать стек из 10 элементов (4), \nскопировать от вершины до максимального наибольшего элемента (5), Выход (6): ");
        cin >> (s);
        switch (s)
        {
            case 1:  enter();  break;
            case 2:  review(); break;
            case 3:  delete_ap(); break;
            case 4:  push10(); break;
            case 5:  task(); break;
            case 6:  exit(0);
        }
    }
    return 0;
}
