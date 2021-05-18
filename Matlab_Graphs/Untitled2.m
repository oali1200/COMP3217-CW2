Pricing = readtable('finaloutput.txt');

Pa = table2array(Pricing);


x1 = ones(5000,1);
x2 = 0 * ones(5000,1);

y1 = Pa(1:5000,1);
y2 = Pa(5001:10000,1);

x = [x1 x2];
y = [y2 y1];
c = 'blue';
s = swarmchart(x,y,10,c);
