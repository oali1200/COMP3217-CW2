Pricing = readtable('finaltestingoutput.txt');

Pa = table2array(Pricing);

%this variable contains the predicted abnromal values
FinalValues = [1 0 0 0 1 1 0 1 1 0 0 1 1 0 0 0 1 1 1 1 0 0 0 1 0 0 0 0 0 1 0 1 1 0 1 1 0 0 1 0 0 0 0 1 1 1 1 1 0 0 0 0 1 0 1 0 0 0 1 1 0 1 0 0 1 0 0 1 1 1 0 0 1 1 0 0 1 0 1 1 0 1 1 1 1 1 0 1 1 1 0 0 0 1 1 1 0 1 0 0]

for i = 1:100
   if(FinalValues(i))
      f1 = figure; 
       
   end
end
xlabel('x axis')
ylabel('y axis')
figName = 'myFigure'; %specify the path, too;  use fullfile()
saveas(fh,figName,'jpg');