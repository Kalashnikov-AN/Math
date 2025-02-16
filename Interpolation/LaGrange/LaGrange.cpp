#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<double>> data = {
        {-2, 24}, {1, 12}, {3, -6}, {5, 24} 
    };
    double x = 1.5; 
    double LaGrange = 0;

    for (size_t k = 0; k < data.size(); ++k) {
        double Numer = 1;
        double Denom = 1;

        for (size_t m = 0; m < data.size(); ++m) {
            if (m != k) {
                Numer *= (x - data[m][0]);
                Denom *= (data[k][0] - data[m][0]);
            }
        }
        LaGrange += data[k][1] * Numer / Denom;
    }

    std::cout << "LaGrange: " << LaGrange << std::endl; 
    return 0;
}

