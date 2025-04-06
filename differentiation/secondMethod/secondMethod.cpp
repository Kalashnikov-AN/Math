#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <locale>
using namespace std;

int main() {

    setlocale(LC_ALL, "Russian");

    const int n = 5;
    vector<double> x(n + 1);
    vector<vector<double>> y(n + 1, vector<double>(n + 1));
    double h = 0.1;

    x[0] = 0.2;
    x[1] = 0.4;
    x[2] = 0.6;
    x[3] = 0.8;
    x[4] = 1.0;
    x[5] = 1.2;

    y[0][0] = 1.2214;
    y[1][0] = 1.4918;
    y[2][0] = 1.8221;
    y[3][0] = 2.2255;
    y[4][0] = 2.7183;
    y[5][0] = 3.3201;
   
    cout << setw(5) << "k" << setw(10) << "x" << setw(10) << "y(x)" << endl;

    for (int i = 0; i <= n; ++i) {
        cout << setw(5) << i << setw(10) << x[i] << setw(10) << y[i][0] << endl;
    }

    for (int j = 1; j <= n; ++j) {
        cout << "D" << j << endl;
        for (int i = 0; i <= n - j; ++i) {
            y[i][j] = y[i + 1][j - 1] - y[i][j - 1];
            cout << setw(10) << y[i][j] << endl;
        }
        cout << endl;
    }

    cout << fixed << setprecision(5) << setw(10) << "y'(xo)" << fixed << setprecision(5) << setw(20) << "погр." << endl;

    double s = 0;
    double d = -1;
    double Delta = 0;

    for (int j = 1; j < n; ++j) {
        d = -d;
        s += d * y[0][j] / (j * h);
        Delta = abs(y[0][j + 1] / ((j + 1) * h));
        cout << setw(10) << s << setw(20) << Delta << endl;
    }

}