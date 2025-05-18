#include <iostream>
#include <cmath>
#include <clocale>
#include <iomanip>
#include <vector>
#include <random>

using namespace std;

double func(const vector<double>& x)
{
    return std::log(
        0.6 * std::pow(x[0] - 0.2, 4) +
        0.9 * std::pow(x[1] - 0.1, 4) +
        0.7 * std::pow(x[2] - 0.5, 4) +
        7.0
    );
}

int main()
{
    setlocale(LC_ALL, "rus");
    setlocale(LC_NUMERIC, "en");
    vector<double> x_old(3);
    vector<double> x_new(3);
    x_old[0] = -1.4;
    x_old[1] = 3.7;
    x_old[2] = 2.2;
    double t = 10000;
    double t_min = 0.001;
    double max_step = 1.1;
    int k = 0;
    cout << "k" << setw(13) << "t" << setw(12) << "x1" << setw(10) << "x2" << setw(10) << "x3" << setw(10) << "fx" << setw(15) << "dfx" << setw(10) << "p" << setw(30) << "решение\n";
    cout << k << setw(13) << t << setw(12) << x_old[0] << setw(10) << x_old[1] << setw(10) << x_old[2] << setw(12) << func(x_old) << setw(12) << 0 << setw(10) << 0 << setw(35) << "начальная точка\n";
    string s;
    while (t > t_min)
    {
        k++;
        t *= 0.99;
        double a = max_step * (static_cast<double>(rand()) / RAND_MAX - 0.5);
        double b = max_step * (static_cast<double>(rand()) / RAND_MAX - 0.5);
        double c = max_step * (static_cast<double>(rand()) / RAND_MAX - 0.5);
        x_new[0] = x_old[0] + a;
        x_new[1] = x_old[1] + b;
        x_new[2] = x_old[2] + c;
        double df = func(x_new) - func(x_old);
        if (df <= 0)
        {
            x_old[0] = x_new[0];
            x_old[1] = x_new[1];
            x_old[2] = x_new[2];
            s = "Перешли в новую точку с уменьшением f(x)\n";
        }
        else
        {
            if (static_cast<double>(rand()) / RAND_MAX < exp(-df / t))
            {
                x_old[0] = x_new[0];
                x_old[1] = x_new[1];
                x_old[2] = x_new[2];
                s = "Перешли в новую точку с увеличением f(x)\n";
            }
            else
            {
                s = "Остались в старой точке\n";
            }
        }
        cout << k << setw(13) << setprecision(6) << t << setw(12) << x_old[0] << setw(10) << x_old[1] << setw(10) << x_old[2] << setw(12) << func(x_old) << setw(14) << df << setw(15) << exp(-df / t) << setw(45) << s;
    }

}