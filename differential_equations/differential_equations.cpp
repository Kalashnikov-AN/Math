#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <locale>
using namespace std;

// Функция правой части уравнения: f(x, y) = sin(x)*cos(y)
double f(double x, double y) {
    return sin(x) * cos(y);
}

// Метод Эйлера
void Euler(double xo, double yo, double h, int steps) {
    vector<double> x(steps + 1), y(steps + 1);
    x[0] = xo;
    y[0] = yo;
    cout << "\nМетод Эйлера:\n";
    cout << "n\tx\ty\n";
    for (int n = 0; n <= steps; n++) {
        cout << n << "\t" << x[n] << "\t" << y[n] << "\n";
        if (n < steps) {
            x[n + 1] = x[n] + h;
            y[n + 1] = y[n] + h * f(x[n], y[n]);
        }
    }
}

// Модифицированный метод Эйлера
void EulerMod(double xo, double yo, double h, int steps) {
    vector<double> x(steps + 1), y(steps + 1);
    x[0] = xo;
    y[0] = yo;
    cout << "\nМодифицированный метод Эйлера:\n";
    cout << "n\tx\ty\n";
    for (int n = 0; n <= steps; n++) {
        cout << n << "\t" << x[n] << "\t" << y[n] << "\n";
        if (n < steps) {
            x[n + 1] = x[n] + h;
            double k1 = f(x[n], y[n]);
            double k2 = f(x[n] + h / 2.0, y[n] + (h / 2.0) * k1);
            y[n + 1] = y[n] + h * k2;
        }
    }
}

// Метод Рунге–Кутты (4 этапа)
void RungeKutt(double xo, double yo, double h, int steps) {
    vector<double> x(steps + 1), y(steps + 1);
    x[0] = xo;
    y[0] = yo;
    cout << "\nМетод Рунге–Кутты:\n";
    cout << "n\tx\ty\n";
    for (int n = 0; n <= steps; n++) {
        cout << n << "\t" << x[n] << "\t" << y[n] << "\n";
        if (n < steps) {
            x[n + 1] = x[n] + h;
            double a = h * f(x[n], y[n]);
            double b = h * f(x[n] + h / 2.0, y[n] + a / 2.0);
            double c = h * f(x[n] + h / 2.0, y[n] + b / 2.0);
            double d = h * f(x[n] + h, y[n] + c);
            y[n + 1] = y[n] + (a + 2 * b + 2 * c + d) / 6.0;
        }
    }
}

// Метод Адамса порядка 1 (двухшаговый метод Адамса–Башфорта)
// Для старта вычислений используем метод Рунге–Кутты для вычисления y1.
void AdamsOrder1(double xo, double yo, double h, int steps) {
    vector<double> x(steps + 1), y(steps + 1);
    x[0] = xo;
    y[0] = yo;
    if (steps >= 1) {
        x[1] = x[0] + h;
        double a = h * f(x[0], y[0]);
        double b = h * f(x[0] + h / 2.0, y[0] + a / 2.0);
        double c = h * f(x[0] + h / 2.0, y[0] + b / 2.0);
        double d = h * f(x[0] + h, y[0] + c);
        y[1] = y[0] + (a + 2 * b + 2 * c + d) / 6.0;
    }
    cout << "\nМетод Адамса (порядок 1):\n";
    cout << "n\tx\ty\n";
    for (int n = 0; n <= steps; n++) {
        cout << n << "\t" << x[n] << "\t" << y[n] << "\n";
        if (n < steps && n >= 1) {
            x[n + 1] = x[n] + h;
            double f_n = f(x[n], y[n]);
            double f_prev = f(x[n - 1], y[n - 1]);
            y[n + 1] = y[n] + (h / 2.0) * (3 * f_n - f_prev);
        }
    }
}

// Метод Адамса порядка 2 (трёхшаговый метод Адамса–Башфорта)
// Для старта вычислений первые два шага вычисляем методом Рунге–Кутты.
void AdamsOrder2(double xo, double yo, double h, int steps) {
    vector<double> x(steps + 1), y(steps + 1);
    x[0] = xo;
    y[0] = yo;
    if (steps >= 1) {
        x[1] = x[0] + h;
        double a = h * f(x[0], y[0]);
        double b = h * f(x[0] + h / 2.0, y[0] + a / 2.0);
        double c = h * f(x[0] + h / 2.0, y[0] + b / 2.0);
        double d = h * f(x[0] + h, y[0] + c);
        y[1] = y[0] + (a + 2 * b + 2 * c + d) / 6.0;
    }
    if (steps >= 2) {
        x[2] = x[1] + h;
        double a = h * f(x[1], y[1]);
        double b = h * f(x[1] + h / 2.0, y[1] + a / 2.0);
        double c = h * f(x[1] + h / 2.0, y[1] + b / 2.0);
        double d = h * f(x[1] + h, y[1] + c);
        y[2] = y[1] + (a + 2 * b + 2 * c + d) / 6.0;
    }
    cout << "\nМетод Адамса (порядок 2):\n";
    cout << "n\tx\ty\n";
    for (int n = 0; n <= steps; n++) {
        cout << n << "\t" << x[n] << "\t" << y[n] << "\n";
        if (n < steps && n >= 2) {
            x[n + 1] = x[n] + h;
            double f_n = f(x[n], y[n]);
            double f_n1 = f(x[n - 1], y[n - 1]);
            double f_n2 = f(x[n - 2], y[n - 2]);
            y[n + 1] = y[n] + (h / 12.0) * (23 * f_n - 16 * f_n1 + 5 * f_n2);
        }
    }
}

// Метод Адамса порядка 3 (четырёхшаговый метод Адамса–Башфорта)
// Для старта вычислений первые три шага вычисляем методом Рунге–Кутты.
void AdamsOrder3(double xo, double yo, double h, int steps) {
    vector<double> x(steps + 1), y(steps + 1);
    x[0] = xo;
    y[0] = yo;
    if (steps >= 1) {
        x[1] = x[0] + h;
        double a = h * f(x[0], y[0]);
        double b = h * f(x[0] + h / 2.0, y[0] + a / 2.0);
        double c = h * f(x[0] + h / 2.0, y[0] + b / 2.0);
        double d = h * f(x[0] + h, y[0] + c);
        y[1] = y[0] + (a + 2 * b + 2 * c + d) / 6.0;
    }
    if (steps >= 2) {
        x[2] = x[1] + h;
        double a = h * f(x[1], y[1]);
        double b = h * f(x[1] + h / 2.0, y[1] + a / 2.0);
        double c = h * f(x[1] + h / 2.0, y[1] + b / 2.0);
        double d = h * f(x[1] + h, y[1] + c);
        y[2] = y[1] + (a + 2 * b + 2 * c + d) / 6.0;
    }
    if (steps >= 3) {
        x[3] = x[2] + h;
        double a = h * f(x[2], y[2]);
        double b = h * f(x[2] + h / 2.0, y[2] + a / 2.0);
        double c = h * f(x[2] + h / 2.0, y[2] + b / 2.0);
        double d = h * f(x[2] + h, y[2] + c);
        y[3] = y[2] + (a + 2 * b + 2 * c + d) / 6.0;
    }
    cout << "\nМетод Адамса (порядок 3):\n";
    cout << "n\tx\ty\n";
    for (int n = 0; n <= steps; n++) {
        cout << n << "\t" << x[n] << "\t" << y[n] << "\n";
        if (n < steps && n >= 3) {
            x[n + 1] = x[n] + h;
            double f_n = f(x[n], y[n]);
            double f_n1 = f(x[n - 1], y[n - 1]);
            double f_n2 = f(x[n - 2], y[n - 2]);
            double f_n3 = f(x[n - 3], y[n - 3]);
            y[n + 1] = y[n] + (h / 24.0) * (55 * f_n - 59 * f_n1 + 37 * f_n2 - 9 * f_n3);
        }
    }
}

// Метод Милна
// В этом методе первые 4 шага вычисляются методом Рунге–Кутты, далее – по схеме Милна.
// Если относительная погрешность (|y2 - y1|/29) превышает заданный eps,
// программа выводит сообщение о необходимости уменьшения шага.
void Miln(double xo, double yo, double h, double eps, int steps) {
    vector<double> x(steps + 1), y(steps + 1);
    x[0] = xo;
    y[0] = yo;

    // Вычисляем первые 4 значения методом Рунге–Кутты
    for (int n = 0; n < 3 && n < steps; n++) {
        x[n + 1] = x[n] + h;
        double a = h * f(x[n], y[n]);
        double b = h * f(x[n] + h / 2.0, y[n] + a / 2.0);
        double c = h * f(x[n] + h / 2.0, y[n] + b / 2.0);
        double d = h * f(x[n] + h, y[n] + c);
        y[n + 1] = y[n] + (a + 2 * b + 2 * c + d) / 6.0;
    }

    int n = 3;
    while (n < steps) {
        x[n + 1] = x[n] + h;
        // Предсказание y с помощью Милна (первое предсказание)
        double y1_pred = y[n - 3] + (4 * h / 3.0) * (2 * f(x[n - 2], y[n - 2])
            - f(x[n - 1], y[n - 1]) + 2 * f(x[n], y[n]));
        // Коррекция y с использованием y1_pred
        double y2_pred = y[n - 1] + (h / 3.0) * (f(x[n - 1], y[n - 1])
            + 4 * f(x[n], y[n]) + f(x[n + 1], y1_pred));
        if (fabs(y2_pred - y1_pred) / 29.0 < eps) {
            y[n + 1] = y2_pred;
        }
        else {
            cout << "Пришлось уменьшить шаг на итерации " << n + 1 << "\n";
            break; // Можно реализовать логику пересчёта с меньшим h
        }
        n++;
    }
    cout << "\nМетод Милна:\n";
    cout << "n\tx\ty\n";
    for (int i = 0; i <= n; i++) {
        cout << i << "\t" << x[i] << "\t" << y[i] << "\n";
    }
}

void Miln2(double xo, double yo, double h, double eps, int k) {
    std::vector<double> x(k + 1);
    std::vector<double> y(k + 1);
    x[0] = xo;
    y[0] = yo;
    std::cout << 0 << "\t" << x[0] << "\t" << y[0] << std::endl;
    bool IsDone = false;

    while (!IsDone) {
        for (int n = 1; n <= k; n++) {
            if (n <= 3) {
                x[n] = x[n - 1] + h;
                double a = h * f(x[n - 1], y[n]);
                double b = h * f(x[n - 1] + h / 2, y[n - 1] + a / 2);
                double c = h * f(x[n - 1] + h / 2, y[n - 1] + b / 2);
                double d = h * f(x[n - 1] + h, y[n - 1] + c);
                y[n] = y[n - 1] + (a + 2 * b + 2 * c + d) / 6;
            }
            else {
                if (n <= k) {
                    x[n] = x[n - 1] + h;
                    double aa = f(x[n - 1], y[n - 1]);
                    double bb = f(x[n - 2], y[n - 2]);
                    double cc = f(x[n - 3], y[n - 3]);
                    double dd = f(x[n - 4], y[n - 4]);
                    double y1 = y[n - 4] + (4 * h / 3) * (2 * cc - bb + 2 * aa);
                    double y2 = y[n - 2] + (h / 3) * (bb + 4 * aa + y1);
                    if (std::abs(y2 - y1) / 29 < eps) {
                        y[n] = y2;
                    }
                    else {
                        h = h / 2;
                        std::cout << "Пришлось уменьшить шаг..." << std::endl;
                        break;
                    }
                }
            }
            if (n == k) {
                IsDone = true;
            }
            std::cout << (n) << "\t" << x[n] << "\t" << y[n] << std::endl;
        }
    }
}

int main() {

    setlocale(LC_ALL, "Russian");

    // Параметры для методов (примерные значения, как в Visual Basic)
    double xo = 0.0, yo = 1.0;
    double h = 0.75;
    int steps = 10;

    // Вызов методов для табуляции решения
    Euler(xo, yo, h, steps);
    EulerMod(xo, yo, h, steps);
    RungeKutt(xo, yo, h, steps);
    AdamsOrder1(xo, yo, h, steps);
    AdamsOrder2(xo, yo, h, steps);
    AdamsOrder3(xo, yo, h, steps);

    // Метод Милна с иными параметрами
    xo = 0.0;
    yo = 1.0;
    h = 0.1;
    double eps = 0.001;
    steps = 10;
    Miln(xo, yo, h, eps, steps);
    xo = 0.0;
    yo = 1.0;
    h = 0.1;
    eps = 0.001;
    steps = 10;
    Miln2(xo,yo,h,eps,steps);
    return 0;
}
