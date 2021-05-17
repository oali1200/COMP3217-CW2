Pricing = readtable('finaloutput.txt');

Pa = table2array(Pricing);

f1 = figure;
f2 = figure;
f3 = figure;
f4 = figure;
f5 = figure;
figure(f1);
for c = 1:5000
    x = 0:23;
    y1 = Pa(c,2:25);
    plot(x,y1)
    hold on;
end
hold off
figure(f2);
for c = 5001:10000
    x = 0:23;
    y2 = Pa(c,2:25);
    plot(x,y2)
    hold on;
end
hold off;
figure(f3);
y = Pa(1:5000,1);
histogram(y);
hold on;
hold off;
figure(f4);
y = Pa(5001:10000,1);
histogram(y);
hold on;
hold off;
figure(f5);
x = 0:23;
y = 0:22;
z = Pa(1:5000,2:25);
hist3(z);
hold on;
hold off;