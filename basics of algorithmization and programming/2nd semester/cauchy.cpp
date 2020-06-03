#include <iostream>
#include <cmath>
#include <iomanip>


//Вариант 1, f1 = u1/x - u2/e^x +1, f2 = u1/(2x) + u2 - 1, a = 1, b = 3, U1(a) = 2, u2(a) = e, Method - M1


void functions(double x, double* y);
void output(double x, double* y);

double f[2], y[2];
double a = 1, b = 3, x, h;
int num_of_h = 20, np = 1, num_of_funcions = 2;


int main()
{
	h = (b - a) / num_of_h; //вычисляем шаг

	x = a; // ставим икс в начало 

	y[0] = 2 * x; // определяем первую функцию
	y[1] = exp(x); // определяем вторую функцию


	output(x, y);


	for (int n = 1; n <= num_of_h; n++)
	{
		functions(x, y);

		for (int i = 0; i < num_of_funcions; i++)
			y[i] += h * f[i]; // тут по формуле из методы

		x += h; 

		output(x, y);
	}

	return 1;
}


void functions(double x, double* y) //вычисление функций
{
	f[0] = (y[0] / x) - (y[1] / exp(x)) + 1;
	f[1] = y[0] / (2 * x) + y[1] - 1;
}


void output(double x, double* y) // вывод
{
	std::cout << "x =" << std::setw(5) << x << std::setw(10) << "y1 =" << std::setw(10) << y[0] << std::setw(10) << "u1 =" << std::setw(5) << 2 * x << std::setw(13) << "d1 =" << std::setw(10) << 2 * x - y[0] << std::endl
		<< std::setw(18) << "y2 =" << std::setw(10) << y[1] << std::setw(10) << "u2 =" << std::setw(8) << exp(x) << std::setw(10) << "d2 =" << std::setw(10) << exp(x) - y[1] << std::endl << std::endl;
}
