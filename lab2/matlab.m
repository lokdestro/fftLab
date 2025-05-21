N = 16;
x = linspace(0, 2*pi, N);
y = sin(3*x) + cos(x);

level = 4;
[c, l] = wavedec(y, level, 'haar');

coeffs_matlab = [];
for i = 1:level
    approx = appcoef(c, l, 'haar', i);
    detail = detcoef(c, l, i); 
    coeffs_matlab = [coeffs_matlab; approx(:); detail(:)];
end

dlmwrite('wavelet_coeffs_matlab.txt', coeffs_matlab, 'precision', '%.6f');

figure;
subplot(5,1,1);
plot(y, 'b-o', 'LineWidth', 1.5);
title('Исходный сигнал (MATLAB)');

subplot(5,1,2);
plot(coeffs_matlab(1:8), 'r-o', 'LineWidth', 1.5);
title('A1 (Уровень 1)');

subplot(5,1,3);
plot(coeffs_matlab(9:16), 'g-o', 'LineWidth', 1.5);
title('D1 (Уровень 1)');

subplot(5,1,4);
plot(coeffs_matlab(17:20), 'm-o', 'LineWidth', 1.5);
title('A2 (Уровень 2)');

subplot(5,1,5);
plot(coeffs_matlab(21:24), 'c-o', 'LineWidth', 1.5);
title('D2 (Уровень 2)');

coeffs_cpp = dlmread('wavelet_coeffs.txt');
difference = abs(coeffs_matlab - coeffs_cpp);
fprintf('Максимальное расхождение: %.6f\n', max(difference));