#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;
vector<double> mainGrid(double a, double b, int n)
{
    double h;
    vector<double> x;
    h = (b - a) / n;
    x.push_back(h);
    while (a <= b)
    {
        x.push_back(a);
        a = a + h;
    }
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
vector<double> coef_A(vector<double> x)
{
    double h = x[0];
    int n = x.size();
    vector<double> A_i(n-1);
    for (int i = 0; i < n - 1; i++)
        A_i[i] = (-p(x[i + 1]) / pow(h, 2)) + (q(x[i + 1]) / (2 * h));
    return A_i;
}
vector<double> coef_B(vector<double> x)
{
    double h = x[0];
    int n = x.size();
    vector<double> B_i(n - 1);
    for (int i = 0; i < n - 1; i++)
        B_i[i] = (2 * p(x[i + 1]) / pow(h, 2)) + r(x[i + 1]);
    return B_i;
}
vector<double> coef_C(vector<double> x)
{
    double h = x[0];
    int n = x.size();
    vector<double> C_i(n - 1);
    for (int i = 0; i < n - 1; i++)
        C_i[i] = (-p(x[i + 1]) / pow(h, 2)) - (q(x[i + 1]) / (2 * h));
    return C_i;
}
vector<double> coef_G(vector< double> x)
{
    int n = x.size();
    vector<double> G_i(n - 1);
    for (int i = 0; i < n - 1; i++)
        G_i[i] = f(x[i + 1]);
    return G_i;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Задание 4. Разностный метод решения краевой задачи для ОДУ 2-го порядка. Вариант 8.\n"
        << "Уравнение вида: \np(x) = (4-x)/(5-2x); \nq(x) = (1-x)/2; \nr(x) = 1/2*ln(3+x); \nf(x) = 1+x/3 \nu(-1) = u(1) = 0";

    double a = 0, b = 0, n = 0, h = 0;
    vector<double> x, A, B, C;

    cout << "Введите границы отрезка:\n"
        << "a = "; cin >> a; cout << "b = "; cin >> b;
    cout << "Введите число разбиений n = "; cin >> n;
    x = mainGrid(a, b, n);
    h = x[0];
    A = coef_A(x);
    B = coef_B(x);
    C = coef_C(x);
    return 0;
}

