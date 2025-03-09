#include <iostream>
#include <vector>
using namespace std;

int main() {
    const int n = 5;
    vector<double> x(n + 1);
    vector<double> y(n + 1);
    vector<double> a(n + 1);
    vector<double> b(n + 1);
    vector<double> c(n + 1);
    vector<double> d(n + 1);
    vector<double> z(n + 1);
    vector<double> w(n + 1);

    x = { -2, 1, 4, 7, 10, 13 };
    y = {4, -8, 7, -2, 4, 6};
    z[0] = -1;
    w[0] = 1; 

    for (int k = 1; k <= n; ++k) {
        double dx = x[k] - x[k - 1];
        double dy = y[k] - y[k - 1];
        a[k] = dy / (dx * dx * dx) - z[k - 1] / (dx * dx) - w[k - 1] / (2 * dx);
        b[k] = 3 * dy / (dx * dx) - 3 * z[k - 1] / dx - w[k - 1];
        c[k] = 3 * dy / dx - 2 * z[k - 1] - w[k - 1] * dx / 2;
        d[k] = y[k];
        z[k] = c[k];
        w[k] = 2 * b[k];
        
    }
    
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "]" << " = " << a[i] << "\n";
        cout << "b[" << i << "]" << " = " << b[i] << "\n";
        cout << "c[" << i << "]" << " = " << c[i] << "\n";
        cout << "d[" << i << "]" << " = " << d[i] << "\n";
        cout << "\n";
    }

}

