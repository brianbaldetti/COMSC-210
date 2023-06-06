//
//  main.cpp
//  lab01
//
//  Created by brian on 9/4/22.
//  program receives user input validates the input and then shows the hailstone sequences for that number
//  program will only continue to calculate the sequence until it reaches 1 or untill it reaches a recursive limit
//
#include <iostream>
#include <iomanip>
using namespace std;

void hailstone(int, int, int&, int&);

int main()
{
    int inputNum = 0, maxNum = 0, count = 0, peak = 0;
    
    //validates user input
    while (inputNum <= 1 || maxNum <= 1)
    {
        cout << "Input Number: ";
        cin >> inputNum;
        cout << "Max Recursion: ";
        cin >> maxNum;
        
        if (inputNum <= 1 || maxNum <= 1)
            cout << "Please enter values greater than 1 for the input number the the recursion number.\n";
    }
    
    //used to format hailstone output
    cout << "Input:      Value:\n";
    cout << "––––––––––––––––––\n";
    
    hailstone(inputNum, maxNum, count, peak);
    
    return 0;
}

void hailstone(int in, int max, int &count, int &peak)
{
    count++;
    
    //if the input is higher than that past peak value then the peak is set to the input value;
    if (in > peak)
        peak = in;
    
    //test if recursive conditions
    if (in == 1)
    {
        cout << "Sequence has ended.\n";
        cout << "Highest number reached: " << peak << endl;
        return;
    }
    else if (max == count)
    {
        cout << "Sequence aborted.\n";
        cout << "Highest number reached: " << peak << endl;
        return;
    }
    else if (in % 2)
    {
        cout << setw(4) << in << setw(10) << (3 * in + 1) << endl;
        hailstone((3 * in + 1), max, count, peak);
    }
    else
    {
        cout << setw(4) << in << setw(10) << (in / 2) << endl;
        hailstone((in / 2), max, count, peak);
    }
}
