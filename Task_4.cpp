#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

vector<double> mainGrid(double a, double b, int h)
{
    vector<double> x;
    while (a <= b)
    {
        x.push_back(a);
        a = a + h;
    }
    return x;
}
vector<double> offsetGrid(double a, double b, int n)
{
    double h = ((b - a) / n);
    vector<double>x(n+2);
    for (int i = 0; i < n + 1; i++)
        x[i] = a - h / 2 + i * h;
    x[n + 1] = b + h / 2;
    for (int i = 0; i < n; i++)
        cout << x[i] << endl;
    return x;
}
double p(double x)
{
    return (4 - x) / (5 - 2*x);
}
double q(double x)
{
    return (1 - x) / 2;
}
double r(double x)
{
    return 1* log(3 + x) / 2;
}
double f(double x)
{
    return 1 + x / 3;
}
vector<vector<double>> coef_1(vector<double> grid,double h, double a_1, double b_1, double a, double b)
{
    int n = grid.size();
    vector<double> A(n), B(n), C(n), G(n);
    vector<vector<double>> table(4, vector<double> (n));
        A[0] = 0;
        A[n - 1] = 0;
        B[0] = h * a_1;
        B[n - 1] = h * b_1;
        C[0] = 0;
        C[n - 1] = 0;
        G[0] = -h * a;
        G[n - 1] = -h * b;
        for (int i = 1; i < n - 1; i++)
        {
            A[i] = -p(grid[i]) - (q(grid[i]) * h / 2);
            C[i] = -p(grid[i]) + (q(grid[i]) * h / 2);
            B[i] = A[i] + C[i] - h * h * r(grid[i]);
            G[i] = h * h * f(grid[i]);
        }
    for (int i = 0; i < n; i++)
    {
        table[0][i] = A[i];
        table[1][i] = B[i];
        table[2][i] = C[i];
        table[3][i] = G[i];
    }
    //for (int i = 0; i < 4; i++)
    //{
    //    for (int j = 0; j < n; j++)
    //        cout << table[i][j] << "\t";
    //    cout << endl;
    //}
    return table;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Задание 4. Разностный метод решения краевой задачи для ОДУ 2-го порядка. Вариант 8.\n"
        << "Уравнение вида: \np(x) = (4-x)/(5-2x); \nq(x) = (1-x)/2; \nr(x) = 1/2*ln(3+x); \nf(x) = 1+x/3 \nu(-1) = u(1) = 0";

    double a = -1, b = 1, n = 0, h = 0, alpha_1 = 1, beta_1 = 1, alpha = 0 , beta= 0;
    vector<double> x, offset_x;
    vector<vector<double>> table;

    cout << "\nГраницы отрезка: [ -1; 1 ]\n";
   /*     << "a = "; cin >> a; cout << "b = "; cin >> b;*/
    cout << "Введите число разбиений n = "; cin >> n;
    h = (b - a) / n;
    x = mainGrid(a, b, h);
    offset_x = offsetGrid(a,b,n);
    table = coef_1(x, h, alpha_1, beta_1, alpha, beta);
    return 0;
}

