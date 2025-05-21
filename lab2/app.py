import numpy as np
import matplotlib.pyplot as plt

def read_coeffs(filename):
    with open(filename, 'r') as f:
        return [float(line.strip()) for line in f]

coeffs = read_coeffs('wavelet_coeffs.txt')

A1 = np.array(coeffs[0:8])    # Уровень 1: A1 (8 элементов)
D1 = np.array(coeffs[8:16])   # Уровень 1: D1 (8 элементов)
A2 = np.array(coeffs[16:20])  # Уровень 2: A2 (4 элемента)
D2 = np.array(coeffs[20:24])  # Уровень 2: D2 (4 элемента)
A3 = np.array(coeffs[24:26])  # Уровень 3: A3 (2 элемента)
D3 = np.array(coeffs[26:28])  # Уровень 3: D3 (2 элемента)
A4 = np.array(coeffs[28:29])  # Уровень 4: A4 (1 элемент)
D4 = np.array(coeffs[29:30])  # Уровень 4: D4 (1 элемент)

plt.figure(figsize=(12, 10))
plt.subplot(5, 1, 1).plot(A1, 'r-o')  # A1
plt.subplot(5, 1, 2).plot(D1, 'g-o')  # D1
plt.subplot(5, 1, 3).plot(A2, 'm-o')  # A2
plt.subplot(5, 1, 4).plot(D2, 'c-o')  # D2
plt.tight_layout()
plt.show()