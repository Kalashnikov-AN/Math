#include <iostream>
#include <cmath>
#include <string>
#include <locale>
using namespace std;

double f(double x) {
    return 2 * (sin(x));
}

int main() {
    setlocale(LC_ALL, "Russian");

    const double Pi = 3.141592654;
    int M1 = 2;
    int M2 = 2;
    double xo = Pi / 4;
    double eps = 0.001;

    string s1 = "По первой формуле верхний порог для h = ";
    s1 += to_string(sqrt(6 * eps / M1)) + ". Введите желаемое h...";
    double h1;
    cout << s1 << endl;
    cin >> h1;
    double diff1 = (f(xo + h1) - f(xo - h1)) / (2 * h1);
    cout << "Производная, вычисленная по первой формуле: " << diff1 << endl;

    string s2 = "По второй формуле верхний порог для h = ";
    s2 += to_string(pow(30 * eps / M2, 0.25)) + ". Введите желаемое h...";
    double h2;
    cout << s2 << endl;
    cin >> h2;
    double diff2 = (f(xo - 2 * h2) - 8 * f(xo - h2) + 8 * f(xo + h2) - f(xo + 2 * h2)) / (12 * h2);
    cout << "Производная, вычисленная по второй формуле: " << diff2 << endl;

    return 0;
}