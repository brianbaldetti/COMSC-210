//
//  main.cpp
//  class00
//
//  Created by brian on 9/13/22.
//  finds the time it takes to solve a problem in seconds
//

#include <iostream>

int main()
{
    const int SIZE = 1000000;
    long arr[SIZE];
    unsigned long start = time(0);
    unsigned long end = 0;
    
    for (int i = 0; i < 250; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            arr[i] = time(0);
        }
    }
    
    end = time(0);
    std::cout << end - start << std::endl;
    
    return 0;
}
