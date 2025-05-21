#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

std::vector<double> generate_signal(int N) {
    std::vector<double> signal(N);
    double step = 2.0 * M_PI / (N - 1);
    for (int i = 0; i < N; ++i) {
        double x = i * step;
        signal[i] = std::sin(3 * x) + std::cos(x);
    }
    return signal;
}

std::pair<std::vector<double>, std::vector<double>> haar_dwt(const std::vector<double>& signal) {
    int N = signal.size();
    if (N % 2 != 0) {
        return {{}, {}};
    }

    std::vector<double> approx(N / 2), detail(N / 2);
    double norm = 1.0 / std::sqrt(2.0);

    for (int i = 0; i < N / 2; ++i) {
        approx[i] = (signal[2*i] + signal[2*i+1]) * norm;
        detail[i] = (signal[2*i] - signal[2*i+1]) * norm;
    }

    return {approx, detail};
}

int main() {
    int N = 16;
    std::vector<double> signal = generate_signal(N);

    auto [A1, D1] = haar_dwt(signal);
    auto [A2, D2] = haar_dwt(A1);
    auto [A3, D3] = haar_dwt(A2);
    auto [A4, D4] = haar_dwt(A3);

    std::ofstream out("wavelet_coeffs.txt");
    out << std::fixed << std::setprecision(6);

    for (double a : A1) out << a << std::endl;
    for (double d : D1) out << d << std::endl;

    for (double a : A2) out << a << std::endl;
    for (double d : D2) out << d << std::endl;

    for (double a : A3) out << a << std::endl;
    for (double d : D3) out << d << std::endl;

    for (double a : A4) out << a << std::endl;
    for (double d : D4) out << d << std::endl;

    return 0;
}