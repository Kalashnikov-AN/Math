#include <iostream>
#include <vector>
using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");
    const int n = 3;
    std::vector<double> xx{-2,1,3,5};
    std::vector<double> yy{24,12,-6,24};
    std::vector<double> x(n + 1);
    std::vector<std::vector<double>> y(n + 1, std::vector<double>(n + 1));

    for (int i = 0; i <= n; ++i) {
        x[i] = xx[i];
        y[i][0] = yy[i];
    }

    for (int j = 1; j <= n; ++j) {
        cout << "Разделённые разности " << j << "-ого порядка:\n";
        for (int i = 0; i <= n - j; ++i) {
            y[i][j] = (y[i + 1][j - 1] - y[i][j - 1]) / (x[i + j] - x[i]);
            cout << y[i][j];
            cout << "\n";
        }
    }
    cout << "\n";
    double xo = 1;

    double NF = y[0][0];
    double d = 1;
    for (int k = 1; k <= n; ++k) {
        d = d * (xo - x[k - 1]);
        NF = NF + y[0][k] * d;
    }
    cout << "NF = " << NF << "\n";

    double NB = y[n][0];
    d = 1;
    for (int k = 1; k <= n; ++k) {
        d = d * (xo - x[n + 1 - k]);
        NB = NB + y[n - k][k] * d;
    }
    cout << "NB = " << NB;

    return 0;
}

