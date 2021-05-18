Pricing = readtable('finaltestingoutput.txt');

Pa = table2array(Pricing);

%this variable contains the predicted abnromal values
FinalValues = [1 0 0 0 1 1 0 1 1 0 0 1 1 0 0 0 1 1 1 1 0 0 0 1 0 0 0 0 0 1 0 1 1 0 1 1 0 0 1 0 0 0 0 1 1 1 1 1 0 0 0 0 1 0 1 0 0 0 1 1 0 1 0 0 1 0 0 1 1 1 0 0 1 1 0 0 1 0 1 1 0 1 1 1 1 1 0 1 1 1 0 0 0 1 1 1 0 1 0 0];
x = 0:23;

for i = 1:100
   if(FinalValues(i))
      f1 = figure;
      hold on
      y = Pa(i,2:25);
      plot(x,y)
      xlabel('time of day')
      ylabel('hours spent running tasks')
      figName = 'D:\Work\PARTIII\COMP3217\CW2\GIT\COMP3217\Matlab_Graphs\Images\' + string(i); %specify the path, too;  use fullfile()
      saveas(f1,figName,'jpg');
      hold off
   end
end
