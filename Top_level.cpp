#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
using namespace std;

//Declaring a function that generates the Linear Programs
void Generate_LP(int round, float *pricing, ofstream &lpfile);
//Declaring a function that saves the values from the output text file
void Copy_Text(ifstream &lpout, ofstream &finaloutput);

int main()
{
    //Initialising the variables needed 
    char userletter = 'a';
    int ReadyTime[50];
    int Deadline[50];
    int MaximumEnergy[50];
    int EnergyDemand[50];
    int ReadyTimeRound;
    int FinalTimeRound;
    int cnt;
    string price;
    float pricing[25];
    float pricefloat;
    string line;
    
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
    lpfile.open("output.txt");
    finaloutput.open("finaloutput.txt");

    //Gets the user task Data and places it into arrays
    for (cnt = 0; cnt < 50; cnt++)
    {
        f1 >> ReadyTime[cnt];
        f2 >> Deadline[cnt];
        f3 >> MaximumEnergy[cnt];
        f4 >> EnergyDemand[cnt];
    }
    //Create a for loop that iterates for each of the 10,000 pricing curves
    for (size_t round = 0; round < 10000; round++)
    {
        //Get the pricing values for one iteration
        
        for (cnt = 0; cnt < 25; cnt++)
        {
            getline(fp, price,',');
            pricefloat = stof(price);
            pricing[cnt] = pricefloat;
        }

        //Call a function that Generates the Linear Program while feeding into it the iteration we are in so that the function can use the correct pricing guideline
        Generate_LP(round, pricing, lpfile);
        //Use a system call that calls on lpsolve to run the LP
        //Call a function that saves the values from the output text file made by LP solve into seperate text files

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
void Generate_LP(int round, float *pricing, ofstream &lpfile){

}

//Create a function that saves the values from the output text file
void Copy_Text(ifstream lpout, ofstream finaloutput){

}