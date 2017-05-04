figure;

nu = 1:0.1:10;
F = 1./(2.*pi^2.*nu.^2);
L = 10*log10(F);

plot(nu,L);