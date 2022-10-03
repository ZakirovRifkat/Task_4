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
    while (a <= b)
    {
        x.push_back(a);
        a = a + h;
    }
    return x;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Задание 4. Разностный метод решения краевой задачи для ОДУ 2-го порядка. Вариант 8.\n"
        << "Уравнение вида: \np(x) = (4-x)/(5-2x); \nq(x) = (1-x)/2; \nr(x) = 1/2*ln(3+x); \nf(x) = 1+x/3 \nu(-1) = u(1) = 0";

    double a = 0, b = 0, n = 0, h = 0;
    vector<double> x;

    cout << "Введите границы отрезка:\n"
        << "a = "; cin >> a; cout << "b = "; cin >> b;
    cout << "Введите число разбиений n = "; cin >> n;
    x = mainGrid(a, b, n);




    return 0;
}

