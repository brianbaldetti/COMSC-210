//
//  main.cpp
//  class01
//
//  Created by brian on 9/13/22.
//  test recursion of ackermans functions
//
#include <iostream>
using namespace std;

int ack(int, int);

int main()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << i << ", " << j << " = " << ack(i, j) << endl;
        }
    }
    
    return 0;
}

int ack(int i, int j)
{
    if (i == 0)
        return (j + 1);
    if (i > 0 && j == 0)
        return ack((i - 1), 1);
    else
        return ack((i - 1), (ack(j, i - 1)));
}
