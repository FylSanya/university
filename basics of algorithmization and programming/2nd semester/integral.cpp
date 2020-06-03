#include <iostream>
#include <cmath>


double fillingX(int a, int b, int i);
double fillingY(double x_j);
double firstDifferentiation(int a, int b, double x_j, double h, int i, int m);
double secondDifferentiation(int a, int b, double x_j, double h, int i, int m);
double integration(int a, int b, int i, int m);


// ������� 1, 4x-7sin(x), a = -2, b = 3, ����� �������������� - �������, �������� ��������� = ~5,983


int main() {
	int a = -2, b = 3, j = 21, m;

	std::cout << "m = ";
	std::cin >> m; // ������ m ��� ���������

	double h;
	std::cout << "h = ";
	std::cin >> h; // ������ h ��� �����������

	double dif_d1 = 0, dif_d2 = 0;

	for (int i = 1; i < j; i++) {
		double x_j = fillingX(a, b, i);
		std::cout << "x_j: " << x_j << std::endl;

		double y_j = fillingY(x_j);
		std::cout << "y_j: " << y_j << std::endl;

		double accurate_d1 = 4 - 7 * cos(x_j);
		dif_d1 += accurate_d1;
		std::cout << "accurate d1: " << accurate_d1 << std::endl; // ������� ������ ������� �������

		double d1 = firstDifferentiation(a, b, x_j, h, i, m);
		dif_d1 -= d1;
		std::cout << "d1: " << d1 << std::endl;

		if (i != 1 && i != j - 1) { // ������ ����������� �� ������ � ������� ������ a � b
			double accurate_d2 = 7 * sin(x_j);
			dif_d2 += accurate_d2;
			std::cout << "accurate d2: " << accurate_d2 << std::endl; // ������� ������ ������� �������

			double d2 = secondDifferentiation(a, b, x_j, h, i, m); 
			dif_d2 -= d2;
			std::cout << "d2: " << d2 << std::endl;
		}
		std::cout << '\n';
	}

	std::cout << "dif_d1 = " << dif_d1 << std::endl << "dif_d2 = " << dif_d2 << std::endl;

	double accurate_integral = (2 * pow(b, 2) + 7 * cos(b)) - (2 * pow(a, 2) + 7 * cos(a)); // ������� ������ ������� �������
	std::cout << '\n'<< "accurate int: " << accurate_integral << std::endl;

	double integral = 0;
	for (int i = 1; i < m; i++) {
		integral += integration(a, b, i, m); // �������� �������� = ����� ���� ���������� �� ��������
	}
	std::cout << "int: " << integral << std::endl << '\n';

	double dif_int = accurate_integral - integral;
	std::cout << "dif_int = " << dif_int;

	return 1;
}


double fillingX(int a, int b, int i) { // ���������� ����
	return a + (((i - 1.0) * (static_cast<double>(b) - static_cast<double>(a))) / 20.0);
}


double fillingY(double x_j) { // ���������� �������
	return (4.0 * x_j) - (7.0 * sin(x_j));
}


double firstDifferentiation(int a, int b, double x_j, double h, int i, int m) { // ������ �����������
	if (x_j == a) // ������� ������ ����������� ��� ����� a
		return (fillingY(x_j)-fillingY(x_j-h))/h;
	else if (x_j == b) // ������� ������ ����������� ��� ����� b
		return (fillingY(x_j+h) - fillingY(x_j)) / h;
		//return (3.0 * fillingY(x_j-h) - 4.0 * fillingY(x_j) + fillingY(x_j+h)) / (2.0 * h);
	else return (fillingY(x_j+h) - fillingY(x_j-h)) / (2.0 * h); // ������� ������ ����������� ��� ����������� �����
}


double secondDifferentiation(int a, int b, double x_j, double h, int i, int m){ // ������ �����������
	return (fillingY(x_j-h) - 2.0 * fillingY(x_j) + fillingY(x_j + h)) / pow(h, 2);
}


double integration(int a, int b, int i, int m) { // ����� ��������� �� �������
	double h = (static_cast<double>(b) - static_cast<double>(a)) / m; // ���������� ����
	double middle = ((a + (i - 1.0) * h) + (a + (i * h))) / 2.0; // ������� �����, � ������� ������ ��������
	return h * fillingY(middle); // �������� = �������, ������� ������ ���� �
}