//
//  main.cpp
//  lab03
//
//  Created by brian on 9/14/22.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;

#define BUGGER 1

#ifdef BUGGER
#define BUG(x) do { \
        cout << endl <<  __FILE__ << " : " << __LINE__ << endl; \
        } while(0)
#else
#define BUG(x)
#endif

struct Custie
{
    int arrivalTime;
    int counter = 0;
};

bool custArrived(double);
void printReport(string, int, double, int, int, int, int, double, double);
void sim(string, int, double, int, int);


int main()
{
    srand((int) time(NULL));  //seeds time
    rand();
    
    string simName = "";
    int simTime = 0;
    double simArrivalRate = 0;
    int simServiceTime = 0;
    int simMaxSize = 0;
    
    ifstream iFile("/Users/messenger01/Desktop/simtest.txt");
        
    if (iFile)
    {
        iFile >> simName >> simTime >> simArrivalRate >> simServiceTime >> simMaxSize;

        
        while(!iFile.eof())
        {
            sim(simName, simTime, simArrivalRate, simServiceTime, simMaxSize);
            iFile >> simName >> simTime >> simArrivalRate >> simServiceTime >> simMaxSize;
        }

    }
    else
    {
        return -1;
    }
    
    iFile.close();
    
    return 0;
}



/*
    function returns true if it evaluates to true and false otherwise
    the functions receives a seed in the form of 'inRate' to determine the rate that it will be true or not
 */
bool custArrived(double inRate)
{
    //cout << "\n\n\nCUST ARRIVED CALLED\n\n\n";
    double randPercentage = rand() / ((double)(RAND_MAX) + 1);
    
    if (randPercentage < inRate)
    {
        return true;
    }
    
    return false;
}


/*
    function runs the line simulation using the input arguments and custArrived func
    after the line simulation is run and completed then sim will call print report
*/
void sim(string inName, int inTime, double inArrivalRate, int inServiceTime, int inMaxSize)
{
    int custServiced = 0, custDropped = 0;
    double waitTime = 0, lineLength = 0;
    
    queue<Custie> custQueue;
    
    for (int i = 0; i < inTime; i++)
    {
        if (custArrived(inArrivalRate))
        {
            if (custQueue.size() >= inMaxSize)
                custDropped++;
            else
            {
                Custie karen {i, 0};
                custQueue.emplace(karen);
            }
        }
        if (!custQueue.empty())
        {
            custQueue.front().counter++;
            
            if (custQueue.front().counter == 15)
            {
                waitTime += (i - custQueue.front().arrivalTime);
                custServiced++;
                custQueue.pop();
            }
        }
        
        lineLength += custQueue.size();

    }
    
    printReport(inName, inTime, inArrivalRate, inServiceTime, inMaxSize, custServiced, custDropped, waitTime, lineLength);
}

/*
    function will be called at the end of the simFunction
    after the function is called it returns the stats of a current line simulation to the user
    the format is text based
*/
void printReport(string inName, int inTime, double inArrivalRate, int inServiceTime, int inMaxSize, int custServiced, int custDropped, double waitTime, double lineLength)
{
    cout << "Simulation name: " << inName << endl;
    cout << "–––––––––––––––––––––––––––––––––––\n";
    cout << "Simulation time: " << inTime << endl;
    cout << "Simulation arrival rate: " << inArrivalRate << endl;
    cout << "Simulation service time: " << inServiceTime << endl;
    cout << "Simulation max line size: " << inMaxSize << endl << endl;
    cout << "Customers serviced: " << custServiced << endl;
    cout << "Customers dropped: " << custDropped << endl;
    cout << "Average wait time: " << (waitTime / custServiced) << endl;
    cout << "Average line length: " << (lineLength / inTime) << endl;
    cout << "–––––––––––––––––––––––––––––––––––\n\n\n";
}
