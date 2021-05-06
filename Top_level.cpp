#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
using namespace std;

//Declaring a function that generates the Linear Programs
void Generate_LP(int round, float pricing[24], ofstream lpfile);
//Declaring a function that saves the values from the output text file
void Copy_Text(ifstream lpout, ofstream finaloutput);

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
    
    //We want to open our files here
    ofstream lpfile;
    ofstream finaloutput;
    string line;
    
    //We want to read the excel file here for user task allocations
    ifstream f1("1.txt");
    ifstream f2("2.txt");
    ifstream f3("3.txt");
    ifstream f4("4.txt");
    ifstream fp("TrainingData.txt");
    ifstream lpout("lpout.txt");
    lpfile.open("output.txt");
    finaloutput.open("finaloutput.txt");

    //Create a for loop that iterates for each of the 10,000 pricing curves
    for (size_t round = 0; round < 10000; round++)
    {
        //Get the pricing values for one iteration
        
        //Call a function that Generates the Linear Program while feeding into it the iteration we are in so that the function can use the correct pricing guideline
        Generate_LP(round, )
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
void Generate_LP(int round, float pricing[24], ofstream lpfile){

}

//Create a function that saves the values from the output text file
void Copy_Text(ifstream lpout, ofstream finaloutput){

}