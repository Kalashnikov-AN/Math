#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
vector <double> x = { -10,-7,-4,-1,2,5 };
vector <double> y = {-10,3,0,0,-6,4};


void SwapRows(int i, int j, std::vector<std::vector<double>>& mxx) {
    for (size_t k = 0; k < mxx[0].size(); ++k) {
        double temp = mxx[i][k];
        mxx[i][k] = mxx[j][k];
        mxx[j][k] = temp;
    }
}

void print_a(vector<vector<double>> matr) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            cout << fixed << setprecision(2) << setw(11) << matr[i][j];

        }
        cout << endl;
    }
    cout << endl;
}

void JG(std::vector<std::vector<double>>& mx) {
    int lRaws = 0;
    int uRaws = mx.size() - 1;
    int lCols = 0;
    int uCols = mx[0].size() - 1;

    for (int k = lCols; k < uCols; ++k) {
        if (std::abs(mx[k][k]) < 0.00001) {
            int o = k + 1;
            do {
                if ((std::abs(mx[o][k]) > 0.00001) || (o > uRaws)) {
                    break;
                }
                o++;
            } while (true);
            SwapRows(k, o, mx);
        }

        for (int i = lRaws; i <= uRaws; ++i) {
            for (int j = k + 1; j <= uCols; ++j) {
                if (i != k) {
                    mx[i][j] = (mx[i][j] * mx[k][k] - mx[k][j] * mx[i][k]) / mx[k][k];
                }
            }
        }

        for (int i = lRaws; i <= uRaws; ++i) {
            if (i != k) {
                mx[i][k] = 0;
            }
        }

        for (int j = uCols; j >= k; --j) {
            mx[k][j] = mx[k][j] / mx[k][k];
        }
        print_a(mx);
    }
    
}

int main() {
    const int n = 5;
    std::vector<std::vector<double>> m(n + 1, std::vector<double>(n + 2));

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n + 1; ++j) {
            if (j == n + 1) {
                m[i][j] = y[i]; 
            }
            else {
                m[i][j] = std::pow(x[i], j); 
            }
        }
    }

    print_a(m);

    JG(m);

    for (int i = 0; i <= n; ++i) {
       cout <<  m[i][n + 1] << "\n";  
    }

    return 0;
}








