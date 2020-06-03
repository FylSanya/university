#include <iostream>
#include <cmath>

using namespace std;

void fillingMatrix(int, double**);
void showMatrix(int, double**, double*);
void fillingAnswers(int, double*);
void solve(double**, double*, double*, int);

void main() {
	int size;
	double* answers;
	double* solutions;
	double** matrix;

	cout << "Kol-vo N: " << endl;
	cin >> size;

	answers = new double [size];
	solutions = new double [size];

	matrix = new double* [size];
	for (int i = 0; i < size; i++)
		matrix[i] = new double[size];

	fillingMatrix(size, matrix);
	fillingAnswers(size, answers);

	solve(matrix, solutions, answers, size);


	showMatrix(size, matrix, answers);

}

void fillingMatrix(int size, double** matrix) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << "Enter [" << i+1 << "][" << j+1 << "]: ";
			cin >> matrix[i][j];
		}
	}
}

void fillingAnswers(int size, double* answers) {
	for (int i = 0; i < size; i++) {
		cout << "Enter term of " << i + 1 << " eqution: ";
		cin >> answers[i];
	}
}

void showMatrix(int size, double** matrix, double* answers) {
	cout << "Your matrix of equtions:\n";
	for (int i = 0, j = 0; i < size; i++) {
		for (int j = 0, asciiValue = 97; j < size && asciiValue <= 122; j++, asciiValue++) {
			char asciiChar = static_cast<char>(asciiValue);
			cout << matrix[i][j] << asciiChar;
			if (matrix[i][j+1] > 0 && j<size) cout << "+";
		}
		cout << " = " << answers[i] << "\n";
	}	
}

void solve(double** matrix, double* solutions, double* answers, int size) {
	int i=0, j=0;
	double factor; 
	for (i = 0; i < size; i++) {
		for (j = 0; j <= i; j++) {
			factor = matrix[i++][j] / matrix[0][j];
			matrix[i][j] *= factor;
			answers[i] *= factor;
			matrix[i++][j++] -= matrix[i][j];
			answers[i++] -= answers[i];
		}
	}
	
}