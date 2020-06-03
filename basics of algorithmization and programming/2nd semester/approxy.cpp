#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;


void fillingX(int, int, int, double*);
void fillingY(double*, double*, int);
void showSheet(double*, double*, double*, double*, int, int);
void solution(const double* x, const double* y, double** x_matrix, double* y_matrix, int n, int m, double* c);
void fillingJ(int a, int b, int j, double* x_j, double* y_j);
void poly(int j, int n, double* x_j, double* y_j, const double* c, double* polynomial);


int main() {

    int a = -2, b = 3, m = 11, n = 3, j = 21;
    double *x = new double[m], 
            *x_j = new double[j - 1], 
            *y_j = new double[j - 1], 
            *y = new double[m], 
            *y_matrix = new double[3], 
            *c = new double[n + 1],
            *polynomial = new double[j],
            **x_matrix = new double* [n + 1];


    for (int i = 0; i < n + 1; i++) {
        x_matrix[i] = new double[n + 1];
    }

    fillingX(a, b, m, x);
    fillingY(y, x, m);
    fillingJ(a, b, j, x_j, y_j);
    showSheet(x, y, x_j, y_j, m, j);
    solution(x, y, x_matrix, y_matrix, n, m, c);
    poly(j, n, x_j, y_j, c, polynomial);
}



void fillingX(int a, int b, int m, double* x) { // ���������� �����
    for (int i = 1; i <= m; i++) { // �������� � i = 1, ��� ��� � �������
        double temp = a + (((i - 1.0) * (b - a)) / (m - 1));
        x[i - 1] = temp;
    }
}


void fillingY(double* y, double* x, int m) { // ���������� �������
    for (int i = 0; i < m; i++) {
        y[i] = (4 * x[i]) - (7 * sin(x[i]));
    }
}


void fillingJ(int a, int b, int j, double* x_j, double* y_j) {

    for (int i = 1; i <= j; i++) { // �������� � i = 1, ��� ��� � �������
        double temp = a + (((i - 1.0) * (b - a)) / 20.0);
        x_j[i - 1] = temp; // ����� �� ��������� x[0] = ��������� ����, ��������� ��� � ����
    }

    for (int i = 0; i < j; i++) {
        y_j[i] = (4 * x_j[i]) - (7 * sin(x_j[i]));
    }
}


void showSheet(double* x, double* y, double* x_j, double* y_j, int m, int j) { // ����� �����-�����
    cout << "x: ";
    for (int i = 0; i < m; i++) {
        cout << x[i] << " ";
    }
    cout << '\n' << "y: ";
    for (int i = 0; i < m; i++) {
        cout << y[i] << " ";
    }
    cout << '\n' << "x_j: ";
    for (int i = 0; i < j; i++) {
        cout << x_j[i] << " ";
    }
    cout << '\n';
}


void solution(const double* x, const double* y, double** x_matrix, double* y_matrix, int n, int m, double* c) { // ��� �� ������ ������� ��� �������� � ��������� �����
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            int cell = i + j;// cell = i+j - � ����� (0;0) ������� � ��� ������ �����, ����� � (0;1) - x^cell, � (1;0) - �^cell � �.�.
            double sum_x = 0;
            for (int p = 0; p < m; p++)
                sum_x += pow(x[p], cell); // ������� ����� ���� �����
            x_matrix[i][j] = sum_x;
        }

        //������ ��������� ������
        double sum_y = 0;
        for (int f = 0; f < m; f++)
            sum_y += y[f] * pow(x[f], i);
        y_matrix[i] = sum_y;

        //�����
        if (i == 3) {
            cout << '\n';
            for (int d = 0, g = i; d < g + 1; d++) {
                for (int j = 0; j < n + 1; j++) printf("%8g ", x_matrix[d][j]);
                printf("| %9.5g\n", y_matrix[d]);
            }
            cout << endl;
        }
    }

    //����� ������
    for (int j = 0; j < n + 1; j++) {
        for (int i = j + 1; i < n + 1; i++) {
            double factor = (x_matrix[i][j]) / (x_matrix[j][j]);
            for (int k = j; k < n + 1; k++) {
                x_matrix[i][k] -= factor * x_matrix[j][k];
            }
            y_matrix[i] -= (factor * y_matrix[j]);
        }
    }

    for (int q = 0; q < n + 1; q++) { // ���������� ������� ��������� � ��������
        y_matrix[q] /= x_matrix[q][q];
        for (int v = n; v >= 0; v--) {
            x_matrix[q][v] /= (x_matrix[q][q]);
        }
    }


    //����� ������� ����� ������ ������
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            cout << x_matrix[i][j];
            if (x_matrix[i][j + 1] >= 0 && j < n + 1 - 1) cout << " + ";
        }
        cout << " = " << y_matrix[i] << "\n";
    }

    //���������� ��������� ����������
    for (int i = n; i >= 0; i--) {
        c[i] = y_matrix[i];
        for (int j = i - 1; j >= 0; j--) {
            y_matrix[j] -= x_matrix[j][i] * y_matrix[i];
        }
    }


    //����� �������� ����������
    cout << endl;
    for (int h = 0; h < n + 1; h++) {
        printf("C%d:%8.5g\n", h + 1, c[h]);
    } cout << endl;

}


void poly(int j, int n, double* x_j, double* y_j, const double* c, double* polynomial) {
    for (int i = 0; i < j; i++) {

        polynomial[i] = 0;

        for (int temp = n; temp >= 0; temp--)
            polynomial[i] += c[temp] * pow(x_j[i], temp); //polynomial[i] = c[0] + c[1] * x_j[i] + c[2] * pow(x_j[i], 2) + c[3] * pow(x_j[i], 3);
    }


    double* dif = new double[j]; //���������� �����������
    for (int i = 0; i < j; i++)
        dif[i] = y_j[i] - polynomial[i];


    double dif_sum = 0; // ��������� ������� �����������
    for (int i = 0; i < j; i++)
        dif_sum += dif[i] / j;

    //����� ��������� �������
    cout << setw(5) <<"y_j" << setw(15) << "poly"<< setw(15) <<"dif"  << endl;;
    for (int i = 0; i < j; i++) {
        if (y_j[i] == 0) cout << y_j[i] << setw(22);
        else cout << y_j[i] << setw(15);
        cout << polynomial[i] << setw(15);
        cout << dif[i] << endl;
    }
    cout << '\n' << "total dif: " << dif_sum << '\n';
}