#include <iostream>
#include <cmath>
#include <locale>
using namespace std;

double f(double x) {
    return cos(x)/(x+2);
}

int main() {
    setlocale(LC_ALL, "Russian");
    const double Pi = 3.14159265358979;
    int n = 4;
    int m = n / 2;
    double a = 0.4;
    double b = 1.2;
    double h = (b - a) / n;
    double s1 = 0;

    for (int k = 1; k <= m; ++k) {
        s1 += f(a + (2 * k - 1) * h);
    }

    double s2 = 0;
    for (int k = 1; k <= m - 1; ++k) {
        s2 += f(a + 2 * k * h);
    }

    double s = (h / 3) * (f(a) + f(b) + 4 * s1 + 2 * s2);
    cout << "Интеграл: " << s << endl;

}

