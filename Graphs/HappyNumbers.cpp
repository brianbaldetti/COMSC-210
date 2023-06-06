//
//  main.cpp
//  HappyNumbers
//
//  Created by brian on 11/22/22.
//
#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    //initializes variables
    srand(static_cast<unsigned>(time(NULL)));
    const int SIZE = 10;
    int happyNumsArr[SIZE];
    int unHappyCount = 0;
    
    //fills 'happyNumsArr' with data of ones and zeros
    for (int i = 0; i < SIZE; i++)
         rand() % 2 ? happyNumsArr[i] = 0 : happyNumsArr[i] = 1;
    
    if (happyNumsArr[0] != happyNumsArr[1])
        unHappyCount++;
    
    for (int i = 1; i < SIZE - 1; i++)
        if ((happyNumsArr[i - 1] != happyNumsArr[i]) && (happyNumsArr[i] != happyNumsArr[i + 1]))
            unHappyCount++;
    
    if (happyNumsArr[SIZE - 1] != happyNumsArr[SIZE - 2])
        unHappyCount++;
    
    //displays data
    cout << "The array is:\n";
    for (int i = 0; i < SIZE; i++)
        cout << happyNumsArr[i] << " ";
    cout << "\nThe number of unhappy numbers is: " << unHappyCount << endl;
    
    
    return 0;
}
