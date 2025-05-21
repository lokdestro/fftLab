#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <complex>

const int N = 16;
const double PI = 3.14159265358979323846;

typedef std::complex<double> base;

void fft(std::vector<base> &a, bool invert) {
    int n = (int)a.size();
    if (n == 1) return;

    std::vector<base> a0(n/2), a1(n/2);
    for (int i=0, j=0; i<n; i+=2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2*PI/n * (invert ? -1 : 1);
    base w(1), wn(cos(ang), sin(ang));
    for (int i=0; i<n/2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i+n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i+n/2] /= 2;
        }
        w *= wn;
    }
}

void saveToFile(const std::vector<double>& data, const std::string& filename) {
    std::ofstream out(filename);
    for (const auto& val : data) {
        out << val << "\n";
    }
    out.close();
}

void saveComplexToFile(const std::vector<base>& data, const std::string& filename) {
    std::ofstream out(filename);
    for (const auto& val : data) {
        out << std::abs(val) << "\n"; // Save magnitude
    }
    out.close();
}

int main() {
    std::vector<double> input(N);
    std::vector<double> x_values(N);
    
    // Generate input signal y = sin(3x) + cos(x)
    for (int i = 0; i < N; ++i) {
        x_values[i] = 2 * PI * i / N;
        input[i] = sin(3 * x_values[i]) + cos(x_values[i]);
    }
    saveToFile(input, "original.txt");
    saveToFile(x_values, "x_values.txt");
    
    // Prepare FFT input
    std::vector<base> fft_input(N);
    for (int i = 0; i < N; ++i) {
        fft_input[i] = base(input[i], 0);
    }
    
    // Forward FFT
    fft(fft_input, false);
    saveComplexToFile(fft_input, "fft.txt");
    
    // Inverse FFT
    fft(fft_input, true);
    
    // Save inverse FFT results (real part)
    std::vector<double> inverse(N);
    for (int i = 0; i < N; ++i) {
        inverse[i] = fft_input[i].real();
    }
    saveToFile(inverse, "inverse.txt");
    
    return 0;
}