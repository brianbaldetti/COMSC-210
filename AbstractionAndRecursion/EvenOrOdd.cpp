//
//  main.cpp
//  Lab0-Part3
//
//  Created by brian on 8/22/22.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
    //defines variables
    const int SIZE = 50;
    int oddCount = 0, evenCount = 0;
    int randomArr[50], oddArr[50], evenArr[50];
    unsigned seed = time(0);
    srand(seed);
    
    //creates array of random ints btwn 1-100
    for (int i = 0; i < SIZE; i++)
        randomArr[i] = (rand() % (100)) + 1;
    
    //sorts the ints in the randomArr into the evenArry and oddArr
    for (int i = 0; i < SIZE; i++)
    {
        if ((randomArr[i] % 2) == 0)
            evenArr[evenCount++] = randomArr[i];
        else
            oddArr[oddCount++] = randomArr[i];
    }
    
    //outputs the array values
    cout << "Odd Integers: ";
    for (int i = 0; i < oddCount; i++)
        cout << oddArr[i] << " ";
    cout << endl;
    
    cout << "Even Integers: ";
    for (int i = 0; i < evenCount; i++)
        cout << evenArr[i] << " ";
    cout << endl << endl;
    
    return 0;
}
