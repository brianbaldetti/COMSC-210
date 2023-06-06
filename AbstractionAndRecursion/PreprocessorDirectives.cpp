//
//  main.cpp
//  InClassQuestion02
//
//  Created by brian on 8/30/22.
//
#include <iostream>
#define VALUE 1
using namespace std;

int peak(int[], int);

int main()
{
    int testArr[] {10, 10, 10, 10, 10, 10, 10, 10};
    int testArr2[2] = {1, 2};
    int testArr3[4] = {1, 2, 3, 2};
#ifdef VALUE
    cout << __LINE__ << endl;
#endif

    cout << VALUE << endl;
    
    cout << "Testing array with no peaks.\n";
    cout << peak(testArr, 8) << endl;
    cout << "Testing array with no peaks.\n";
    cout << peak(testArr2, 2) << endl;
    cout << "Testing array with one peak.\n";
    cout << peak(testArr3, 4) << endl;
    
    return 0;
}

int peak(int inArr[], int length)
{
    int peaks = 0;
    
    if (length >= 3)
    {
        for (int i = 1; i < length - 1; i++)
        {
            if (inArr[i] > inArr[i - 1] && inArr[i] > inArr[i + 1])
                peaks++;
        }
    }
    
    return peaks;
}
