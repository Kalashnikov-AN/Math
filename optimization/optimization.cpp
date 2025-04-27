#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция f: f(x1,x2,x3) = ln(0.6(x1-0.2)^4 + 0.9(x2-0.1)^4 + 0.7(x3-0.5)^4 + 7)
double f(const vector<double>& x) {
    double g = 0.6 * pow(x[0] - 0.2, 4)
        + 0.9 * pow(x[1] - 0.1, 4)
        + 0.7 * pow(x[2] - 0.5, 4)
        + 7.0;
    return log(g);
}

// Градиент функции f
auto GradF(const vector<double>& x) {
    vector<double> grad(3);
    double g = 0.6 * pow(x[0] - 0.2, 4)
        + 0.9 * pow(x[1] - 0.1, 4)
        + 0.7 * pow(x[2] - 0.5, 4)
        + 7.0;
    grad[0] = 2.4 * pow(x[0] - 0.2, 3) / g;
    grad[1] = 3.6 * pow(x[1] - 0.1, 3) / g;
    grad[2] = 2.8 * pow(x[2] - 0.5, 3) / g;
    return grad;
}

// Векторное сложение
vector<double> plusVec(const vector<double>& a, const vector<double>& b) {
    vector<double> c(3);
    for (int i = 0; i < 3; i++) c[i] = a[i] + b[i];
    return c;
}

// Векторное вычитание
vector<double> minusVec(const vector<double>& a, const vector<double>& b) {
    vector<double> c(3);
    for (int i = 0; i < 3; i++) c[i] = a[i] - b[i];
    return c;
}

// Умножение вектора на скаляр
vector<double> multVec(const vector<double>& a, double t) {
    vector<double> c(3);
    for (int i = 0; i < 3; i++) c[i] = a[i] * t;
    return c;
}

// Скалярное произведение
double scalProd(const vector<double>& a, const vector<double>& b) {
    double scp = 0.0;
    for (int i = 0; i < 3; i++) scp += a[i] * b[i];
    return scp;
}

// Длина вектора
double length(const vector<double>& a) {
    return sqrt(scalProd(a, a));
}

pair<double, double> Swenn(const vector<double>& x, double d) {
    double t = 0.0, a, b, h;
    vector<double> x_l = minusVec(x, multVec(GradF(x), t - d));
    vector<double> x_c = minusVec(x, multVec(GradF(x), t));
    vector<double> x_h = minusVec(x, multVec(GradF(x), t + d));

    double f_l = f(x_l), f_c = f(x_c), f_h = f(x_h);

    if (f_l < f_c && f_c > f_h) {
        cout << "Функция не унимодальна!!!" << endl;
        return make_pair(0.0, 0.0);
    }
    else if (f_l > f_c && f_c < f_h) {
        a = t - d;
        b = t + d;
    }
    else {
        if (f_l > f_c && f_c > f_h) h = d;
        else h = -d;
        double t_prev = t - h;
        vector<double> x_prev = minusVec(x, multVec(GradF(x), t_prev));
        double t_curr = t;
        vector<double> x_curr = minusVec(x, multVec(GradF(x), t_curr));
        double t_next = t + h;
        vector<double> x_next = minusVec(x, multVec(GradF(x), t_next));
        while (!(f(x_prev) > f(x_curr) && f(x_curr) < f(x_next))) {
            h *= 2;
            t_prev = t_curr;
            x_prev = x_curr;
            t_curr = t_next;
            x_curr = x_next;
            t_next = t + h;
            x_next = minusVec(x, multVec(GradF(x), t_next));
        }
        if (h > 0) { a = t_prev; b = t_next; }
        else { a = t_next; b = t_prev; }
    }
    return make_pair(a, b);
}

double HalfDivision(const vector<double>& x, pair<double, double> ab, double eps) {
    double t0 = ab.first, t4 = ab.second;
    double t1, t2, t3;
    do {
        t1 = (3 * t0 + t4) / 4.0;
        t2 = (2 * t0 + 2 * t4) / 4.0;
        t3 = (t0 + 3 * t4) / 4.0;
        vector<double> x1 = minusVec(x, multVec(GradF(x), t1));
        vector<double> x2 = minusVec(x, multVec(GradF(x), t2));
        vector<double> x3 = minusVec(x, multVec(GradF(x), t3));
        double f1 = f(x1), f2 = f(x2), f3 = f(x3);
        if (f1 > f2 && f2 < f3) { t0 = t1; t4 = t3; }
        else if (f1 > f2 && f2 > f3) { t0 = t2; }
        else /*if(f1 < f2 && f2 < f3)*/ { t4 = t2; }
    } while (t4 - t0 >= 2 * eps);
    return (t0 + t4) / 2.0;
}

int main() {
    setlocale(LC_ALL, ""); 
    double eps = 1e-4;
    double d = 0.01;
    vector<double> x_old = { 5.317, 4.196, 3.174 };
    vector<double> x_new = x_old;

    cout << "k\t x1\t x2\t x3\t f(x)" << endl;
    int k = 0;
    cout << k << "\t" << fixed << setprecision(6)
        << x_new[0] << "\t" << x_new[1] << "\t" << x_new[2]
        << "\t" << f(x_new) << endl;

    do {
        x_old = x_new;
        auto ab = Swenn(x_old, d);
        double alpha = HalfDivision(x_old, ab, eps);
        vector<double> grad = GradF(x_old);
        vector<double> step = multVec(grad, alpha);
        x_new = minusVec(x_old, step);
        k++;
        cout << k << "\t"
            << x_new[0] << "\t" << x_new[1] << "\t" << x_new[2]
            << "\t" << f(x_new) << endl;
    } while (!(length(GradF(x_new)) < eps || length(minusVec(x_new, x_old)) < eps));

    cout << "Приближенное решение: ("
        << x_new[0] << "; " << x_new[1] << "; " << x_new[2] << ")" << endl;
    return 0;
}
