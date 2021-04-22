#define _USE_MATH_DEFINES
#include <cmath>
#include<iostream>
#include <stdio.h>

using namespace std;

void fooA()
{
	int min = 16;
	int max = 199;
	int sum = 0;

	for (int i = min; i <= max; i = i + 7)
	{
		sum += i;
	}
	cout << "Сумма чисел от " << min << " до " << max << " с шагом 7 = " << sum << endl;
}

bool fooB(int a)
{
	return a % 11 == 0;
}

void fooC(double& x, double y, double z)
{
	x = x * y * z;
}

int main()
{
	setlocale(LC_ALL, "ru");
	//a
	fooA();

	//b
	int x;
	cout<<"Введите число"<<endl;
	cin >> x;
	cout << (fooB(x) ? "kratno" : "ne kratnoe") << endl;

	//c
	cout << "Найдем произведение трёх чисел и присвоим значение первому.\n Введите 3 действительных числа." << endl;
	double q, w, e;
	cin >> q >> w >> e;
	fooC(q, w, e);
	cout << "Произведение чисел равно = " << q << endl;
}
