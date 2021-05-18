Pricing = readtable('finaltestingoutput.txt');

Pa = table2array(Pricing);


x1 = ones(98,1);
x2 = 0 * ones(2,1);
for j = 2:69
    y1(j-1) = Pa(j,1);
end
for j = 71:100
    y1(j-2) = Pa(j,1);
end
y3 = [Pa(70,1), Pa(1,1)];

c = 'blue';
swarmchart(x1,y1,10,c);
hold on;
swarmchart(x2,y3,10,c);
