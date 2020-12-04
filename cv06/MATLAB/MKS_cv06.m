% MKS cv06
clear all

M = csvread('ntc.csv');
t = M(:,1);
r = M(:,2);
c = length(r);

adcnt = 1024;
ad = zeros(c,1);

for ii = 1:c
    ad(ii,1) = (r(ii,1)/(10+r(ii,1)))*(adcnt-1);
end
plot(ad,t,'o')
grid on
hold on
p = polyfit(ad,t,10);

ad2 = 0:1023;
t2 = round(polyval(p, ad2),1);
plot(ad2,t2,'r')

xlabel('ADC value')
ylabel('Temperature [°C]')

dlmwrite('data.dlm', t2*10, ',')