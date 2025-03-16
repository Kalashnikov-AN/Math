#include <iostream>
#include <cmath>
#include <locale>
using namespace std;

double f(double x) {
    return 1 / sqrt(x*x+0.5);
}

int main() {
    setlocale(LC_ALL, "Russian");
    const double Pi = 3.14159265358979;
    int n = 20;
    double a = 1.2;
    double b = 2.4;
    double h = (b - a) / n;
    double s = 0;

    for (int k = 1; k < n; ++k) {
        s += f(a + k * h);
    }

    s = (h / 2) * (f(a) + f(b) + 2 * s);
    cout << "Интеграл: " << s << endl;

}

