#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include<windows.h>
using namespace std;

//Declaring a function that generates the Linear Programs
void Generate_LP(float *pricing, ofstream &lpfile, int *ReadyTime, int *Deadline, int *MaximumEnergy, int *EnergyDemand);
//Declaring a function that saves the values from the output text file
void Copy_Text(ifstream &lpout, ofstream &finaloutput, float *pricing);

int main()
{
    //Initialising the variables needed 
    char userletter = 'a';
    int ReadyTime[50];
    int Deadline[50];
    int MaximumEnergy[50];
    int EnergyDemand[50];
    int cnt;
    int status;
    string price;
    float pricing[25];
    float pricefloat;
    
    //We want to open our files here
    ofstream lpfile;
    ofstream finaloutput;
    
    //We want to read the excel file here for user task allocations
    std::ifstream f1("1.txt");
    std::ifstream f2("2.txt");
    std::ifstream f3("3.txt");
    std::ifstream f4("4.txt");
    std::ifstream fp("TrainingData.txt");
    std::ifstream lpout("lpout.txt");
    finaloutput.open("finaloutput.txt", std::ofstream::out | std::ofstream::trunc);
    finaloutput.close();
    finaloutput.open("finaloutput.txt", std::ios_base::app);

    //Gets the user task Data and places it into arrays
    for (cnt = 0; cnt < 50; cnt++)
    {
        f1 >> ReadyTime[cnt];
        f2 >> Deadline[cnt];
        f3 >> MaximumEnergy[cnt];
        f4 >> EnergyDemand[cnt];
    }
    // Create a for loop that iterates for each of the 10,000 pricing curves
    for (int round = 0; round < 10000; round++)
    {
        //clear the lp file
        lpfile.open("lpfunction.lp", std::ofstream::out | std::ofstream::trunc);
        lpfile.close();
        lpfile.open("lpfunction.lp", std::ofstream::out);
        lpfile.open("lpout.txt", std::ofstream::out | std::ofstream::trunc);
        lpfile.close();
        lpfile.open("lpout.txt", std::ofstream::in);
        //Get the pricing values for one iteration   
        for (cnt = 0; cnt < 25; cnt++)
        {
            getline(fp, price,',');
            pricefloat = stof(price);
            pricing[cnt] = pricefloat;
        }
        //Call a function that Generates the Linear Program while feeding into it the iteration we are in so that the function can use the correct pricing guideline
        Generate_LP(pricing, lpfile, ReadyTime, Deadline, MaximumEnergy, EnergyDemand);
        //Use a system call that calls on lpsolve to run the LP
        system("C:\\lp\\lp_solve -s lpfunction.lp >lpout.txt");
        Sleep(750);
        //Call a function that saves the values from the output text file made by LP solve into seperate text files
        Copy_Text(lpout, finaloutput, pricing);
    }
    
    //We want to close our files here
    f1.close();
    f2.close();
    f3.close();
    f4.close();
    fp.close();
    lpfile.close();
    finaloutput.close();

    return 0;
}

//Create a function that generates the Linear Programs
void Generate_LP(float *pricing, ofstream &lpfile, int *ReadyTime, int *Deadline, int *MaximumEnergy, int *EnergyDemand){
    //Declaring variables needed
    int ReadyTimeRound;
    int FinalTimeRound;
    int MaximumEnergyRound;
    int EnergyDemandRound;
    string line;
    char userletter = 'a';

    lpfile << "min: Cost;" << endl;
    //Iterates for each user creating a set of LPs per user
    for (int user = 1; user < 6; user++)
    {
        //Creating a Linear Function describing the Energy demand of each function for task
        for (int task = 1; task < 11; task++)
        {
            ReadyTimeRound = ReadyTime[((user-1)*10+task-1)];
            FinalTimeRound = Deadline[((user-1)*10+task-1)];
            line = "";
            for (int timeofday = 0; timeofday < 24; timeofday++)
            {
                //if ((ReadyTimeRound <= timeofday) && (timeofday <= FinalTimeRound))
                //{
                    if (line == "")
                    {
                        line.push_back(userletter);
                        line = line + std::to_string(task) + "_" + std::to_string(timeofday);
                    }
                    else
                    {
                        line = line + "+" ;
                        line.push_back(userletter);
                        line = line + std::to_string(task) + "_" + std::to_string(timeofday);
                    }
                //}
            }
            line = line + "=" + std::to_string(EnergyDemand[((user-1)*10+task-1)]) + ";";
            lpfile << line << endl;
        }

        //Creating a Linear Function describing the range of times allowing to run a task
        for (int task = 1; task < 11; task++)
        {
            ReadyTimeRound = ReadyTime[((user-1)*10+task-1)];
            FinalTimeRound = Deadline[((user-1)*10+task-1)];
            MaximumEnergyRound = MaximumEnergy[((user-1)*10+task-1)];
            EnergyDemandRound = EnergyDemand[((user-1)*10+task-1)];
            for (int timeofday = 0; timeofday < 24; timeofday++)
            {
                line = "";
                if ((ReadyTimeRound <= timeofday) && (timeofday <= FinalTimeRound))
                {
                    line = line + "0" + "<=";
                    line.push_back(userletter);
                    line = line + std::to_string(task) + "_" + std::to_string(timeofday) + "<=" + std::to_string(MaximumEnergyRound) + ";";
                    lpfile << line << endl;
                }
            }
        }
        userletter++;
    }
    string userletterstring;
    //This Loop sums all the costs together per hour
    for (int timeofday = 0; timeofday < 24; timeofday++)
    {
        lpfile << "c" << timeofday << "=";
        for (int task = 1; task < 11; task++)
        {
            char userletter = 'a';
            for (int user = 0; user < 5; user++)
            {
                userletterstring.push_back(userletter);
                lpfile << userletterstring << std::to_string(task) << "_" << std::to_string(timeofday);
                if (user == 4 && task == 10)
                {
                    
                }
                else {
                    lpfile << "+";
                }
                userletterstring.clear();
                userletter++;
            }
        }
        lpfile << ";" << endl;
    }
    lpfile << "Cost = ";
    //Creating a Linear Function that represents the total cost
    float price;
    for (int timeofday = 0; timeofday < 24; timeofday++)
    {
        price = pricing[timeofday];
        lpfile << to_string(price) << "*" << "c" << to_string(timeofday);
        if (timeofday != 23)
        {
            lpfile << "+";  
        }
        
    }
    lpfile << ";" << endl;
}

//Create a function that saves the values from the output text file
void Copy_Text(ifstream &lpout, ofstream &finaloutput, float *pricing){
    string cost;
    string costs;
    string c[24] = {};
    string intermediate[25] = {};
    for (size_t i = 0; i < 12; i++)
    {
        lpout >> costs;
    }
    while (!lpout.eof())
    {
        lpout >> costs;
        if (costs == "c0")
        {
            for (int j = 0; j < 24; j++)
            {
                lpout >> costs;
                c[j] = costs;
                lpout >> costs;
            }
        }
        
    }
    for (int i = 0; i < 24; i++)
    {
        finaloutput << c[i] << ",";
    }
    int validity = (int)pricing[24];
    finaloutput << to_string(validity) << endl;
}