#include <iostream>
#include <cmath>

//Вариант 1, 4x-7sin(x), a = –2, b = 2, Метод - MI 

double functionY(double x);
double functionF(double x);
double method(double e, double x_arr);

int main() {

	double a = -2, b = 2, m;
	double e = 0.0001;
	std::cout << "m = ";
	std::cin >> m;
	std::cout << '\n';

	double h = (b - a) / m;

	double x_arr, y, solution;

	for (a; a < b; a += h) {
		x_arr = a;
		y = functionY(x_arr);
		if (y * functionY(x_arr+h) < 0) {
			solution = method(e, x_arr);
			std::cout << "Solution: " << solution << std::endl;
			std::cout << "X in range of "<< x_arr << " - " << x_arr+h << std::endl;
			std::cout << "Y in range of " << y << " - " << functionY(x_arr + h) << std::endl;
			std::cout << '\n';
		}
		else {
			std::cout << "No solutions in that range. " << std::endl;
			std::cout << "X in range of " << x_arr << " - " << x_arr + h << std::endl;
			std::cout << "Y in range of " << y << " - " << functionY(x_arr + h) << std::endl;
			std::cout << '\n';
		}
	}

	return 1;
}

double functionY(double x) {
	return 4 * x - 7 * sin(x);
}

double functionF(double x) {
	return 7*sin(x)/4; //4x-7sin(x) = y => y = 0 => 4x=7sinx => x = 7sinx/4
}

double method(double e, double x_arr){
	int it = 0;
	double dif, temp_x = 0;
	for (dif = 1, it; dif > e || it >= 100; it++) {
		temp_x = functionF(x_arr);
		if (it == 0 && temp_x < x_arr) {
			return 0;
		}
		dif = fabs(temp_x - x_arr);
		x_arr = temp_x;
	}
	return temp_x;
}