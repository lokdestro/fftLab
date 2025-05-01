import numpy as np
import matplotlib.pyplot as plt

original = np.loadtxt('original.txt')
x_values = np.loadtxt('x_values.txt')
fft_mag = np.loadtxt('fft.txt')
inverse = np.loadtxt('inverse.txt')

plt.figure(figsize=(12, 8))

plt.subplot(3, 1, 1)
plt.plot(x_values, original, 'b-o')
plt.title('Original Signal: y = sin(3x) + cos(x)')
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

plt.subplot(3, 1, 2)
plt.stem(np.arange(16), fft_mag, 'r')
plt.title('FFT Magnitude')
plt.xlabel('Frequency bin')
plt.ylabel('Magnitude')
plt.grid()

plt.subplot(3, 1, 3)
plt.plot(x_values, original, 'b-o', label='Original')
plt.plot(x_values, inverse, 'r--x', label='Reconstructed')
plt.title('Comparison')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid()

plt.tight_layout()
plt.show()