#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

void show(vector<vector<double>> solve, vector<double> grid)
{
    for (int i = 0; i < grid.size(); i++)
        cout << "\t|" <<setw(12) << grid[i]
        << "|" << setw(10) << solve[0][i]
        << "|" << setw(10) << solve[1][i]
        << "|" << setw(10) << solve[2][i]
        << "|" << setw(10) << solve[3][i]
        << "|" << setw(10) << solve[4][i]
        << "|" << setw(10) << solve[5][i]
        << "|" << setw(10) << solve[6][i]
        <<"|\n";
}
void clear(vector<vector<double>> table, vector<vector<double>> coefficients, vector<double> x)
{
    for (int i = 0; i < x.size(); i++)
    {
        x[i] = 0;
        for (int j = 0; j < coefficients.size(); j++)
            coefficients[j][i] = 0;
        for (int j = 0; j < table.size(); j++)
            table[j][i] = 0;
    }
}
double p(double x)
{
    return (4 - x) / (5 - 2 * x);
}
double q(double x)
{
    return (1 - x) / 2;
}
double r(double x)
{
    return 1 * log(3 + x) / 2;
}
double f(double x)
{
    return 1 + x / 3;
}
vector<double> mainGrid(double a, double b, double h)
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
    return x;
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
    return table;
}
vector<vector<double>> coef_2(vector<double> offset_grid, double h, double a_1, double b_1, double a, double b)
{
    int n = offset_grid.size();
    vector<double> A(n), B(n), C(n), G(n);
    vector<vector<double>> table(4, vector<double>(n));
    A[0] = 0;
    A[n - 1] = -h * b_1;
    B[0] = h * a_1;
    B[n - 1] = h * b_1;
    C[0] = -h * a_1;
    C[n - 1] = 0;
    G[0] = -2 * h * a;
    G[n - 1] = -2 * h * b;
    for (int i = 1; i < n - 1; i++)
    {
        A[i] = -p(offset_grid[i] - h / 2) - ((q(offset_grid[i]) * h) / 2);
        C[i] = -p(offset_grid[i] + h / 2) + ((q(offset_grid[i]) * h) / 2);
        B[i] = A[i] + C[i] - h * h * r(offset_grid[i]);
        G[i] = h * h * f(offset_grid[i]);
    }
    for (int i = 0; i < n; i++)
    {
        table[0][i] = A[i];
        table[1][i] = B[i];
        table[2][i] = C[i];
        table[3][i] = G[i];
    }
    return table;
}
vector<vector<double>> sweep_method(vector<vector<double>> coef, int size)
{
    int n = size;
    vector<double> s(n), t(n), y(n);
    vector<double> A(n), B(n), C(n), G(n);
    vector<vector<double>> solution(7, vector<double>(n));
    for (int i = 0; i < n; i++)
    {
        A[i] = (coef[0][i]);
        B[i] = (coef[1][i]);
        C[i] = (coef[2][i]);
        G[i] = (coef[3][i]);
    }
    s[0] = (C[0] / B[0]);
    t[0] = (-G[0] / B[0]);
    for (int i = 1; i < n; i++)
    {
        s[i] = (C[i] / (B[i] - A[i] * s[i - 1]));
        t[i] = ((A[i] * t[i - 1] - G[i]) / (B[i] - A[i] * s[i - 1]));
    }
    y[n - 1] = t[n - 1];
    for (int i = n - 2; i >= 0; i--)
        y[i] = s[i] * y[i + 1] + t[i];
    for (int i = 0; i < n; i++)
    {
        solution[0][i] = A[i];
        solution[1][i] = B[i];
        solution[2][i] = C[i];
        solution[3][i] = G[i];
        solution[4][i] = s[i];
        solution[5][i] = t[i];
        solution[6][i] = y[i];
    }
    return solution;
}
vector<double> Richardson(vector<vector<double>> table, int size, int s)
{
    vector<double> y_i(size), solve(size/2);
    vector<double> R(size/2);
    for (int i = 0; i < size; i++)
        y_i[i] = table[6][i];
    for (int i = 0; i < size/2; i++)
        R[i] = (y_i[2*i+1] - y_i[2*i]) / (pow(2,s) - 1);
    for (int i = 0; i < size/2; i++)
        solve[i] = y_i[2 * i + 1] + R[i];
    return solve;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Задание 4. Разностный метод решения краевой задачи для ОДУ 2-го порядка. Вариант 8.\n"
        << "Уравнение вида: \np(x) = (4-x)/(5-2x); \nq(x) = (1-x)/2; \nr(x) = 1/2*ln(3+x); \nf(x) = 1+x/3 \nu(-1) = u(1) = 0";
    int choise = 0;
    char op = '+';
    double a = -1, b = 1, n = 0, h, alpha_1 = 1, beta_1 = 1, alpha = 0 , beta= 0;
    vector<double> x, extrapol;
    vector<vector<double>> coefficients, final_table;

    cout << "\nГраницы отрезка: [ -1; 1 ]\n";
   /*     << "a = "; cin >> a; cout << "b = "; cin >> b;*/
    while (op != '-')
    {
        cout << "Введите число разбиений n = "; cin >> n;
        h = (b - a) / n;
        cout << "Выберите точность:\n1) О(h)\n2) O(h^2)\n";
        cin >> choise;
        switch (choise)
        {
        case 1:
            x = mainGrid(a, b, h);
            coefficients = coef_1(x, h, alpha_1, beta_1, alpha, beta);
            final_table = sweep_method(coefficients, x.size());
            show(final_table, x);
            if (n == 20)
            {
                cout << "Экстраполяция по Ричардсону:\n";
                extrapol = Richardson(final_table, x.size(), 1);
                for (int i = 0; i < extrapol.size(); i++)
                    cout << "\t|" << setw(12) << extrapol[i] << "|\n";
            }
            break;
        case 2:
            x = offsetGrid(a, b, n);
            coefficients = coef_2(x, h, alpha_1, beta_1, alpha, beta);
            final_table = sweep_method(coefficients, x.size());
            show(final_table, x);
            if (n == 20)
            {
                cout << "Экстраполяция по Ричардсону:\n";
                extrapol = Richardson(final_table, x.size(), 2);
                for (int i = 0; i < extrapol.size(); i++)
                    cout << "\t|" << setw(12) << extrapol[i] << "|\n";
            }
            break;
        }
        for (int i = 0; i < x.size(); i++)
        {
            x[i] = 0;
            for(int j=0; j<coefficients.size();j++)          
                coefficients[j][i] = 0;
            for (int j = 0; j < coefficients.size(); j++)
                final_table[j][i] = 0;
        }
        cout << "\nПродолжим? +/-\n";
        cin >> op;
    }
    return 0;
}

