Pricing = readtable('finaloutput.txt');

for c = 0:4999
    x = 0:23;
    y = Pricing(c,2:25);
end