//
//  main.cpp
//  class02
//
//  Created by brian on 9/13/22.
//  recursive fucntion that counts the number of times that t appears in an unsigned int
//
#include <iostream>
using namespace std;

int count5(int);

int main()
{
    cout << count5(42156789) << endl;
    
    return 0;
}

int count5(int input)
{
    int count = 0;
    
    if (input == 0)
        return count;
    else
    {
        if (input % 10 == 5)
            count++;
        return count + count5(input / 10);
    }
}
