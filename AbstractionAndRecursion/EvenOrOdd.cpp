//
//  main.cpp
//  InClassQuestion01
//
//  Created by brian on 8/30/22.
//
#include <iostream>
using namespace std;

int main()
{
    int inputInt;
    cout << "Enter int: ";
    cin >> inputInt;
    
    inputInt % 2 ? cout << "The number is odd.\n" : cout << "The number is even.\n";
    
    return 0;
}
