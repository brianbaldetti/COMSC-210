//
//  main.cpp
//  lab05
//
//  Created by brian on 9/28/22.
//
#include <iostream>
#include <ctime>
#include "SortableBag.hpp"
using namespace std;

int main()
{
    const int SIZE = 25;
    SortableBag<int> QA(SIZE);  //initializes 'QA' obj
    srand(static_cast<unsigned>(time(0)));  //seeds 'rand()' function
    
    while(QA.add((rand() % 101))) {}    //fills 'QA' obj with int values between 100-1
    
    //output
    cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n";
    cout << "Currently, the bag contains the data: \n\n";
    QA.printBag();
    cout << "\n––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n";
    
    cout << "After sorting the array the bag contains the data int the form: \n\n";
    QA.sort();
    QA.printBag();
    cout << "\n––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n";

    //conditional statement
    QA.verify() ? cout << "The bag HAS BEEN verified to have been sucessfully sorted.\n" : cout << "The bag is NOT sucessfully sorted!\n";
    cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n";

    
    
    
    return 0;
}
