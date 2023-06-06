//
//  main.cpp
//  Class03
//
//  Created by brian on 8/30/22.
//
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Array
{
private:
    static const int SIZE = 10;
    int values[SIZE];
public:
    void setAtIndex(int, int);
    int getAtIndex(int) const;
    int capacity() const;
    int operator[](int) const;
    int &operator[](int);
};

void Array::setAtIndex(int val, int index)
{
    if (index >= 0 && index < SIZE)
        values[index] = val;
}

int Array::getAtIndex(int index) const
{
    if (index >= 0 && index < SIZE)
        return values[index];
    return 0;
}

int Array::capacity() const
{
    return SIZE;
}

int Array::operator[](int index) const
{
    if (index >= 0 && index < SIZE)
        return values[index];
    return 0;
}

int main()
{
    Array tester;
    tester.setAtIndex(10, 10);
    tester.setAtIndex(2, -1);
    tester.setAtIndex(7, 7);
    
    cout << tester.getAtIndex(7);
    cout << endl;
    cout << tester[7];
    cout << endl;
    cout << tester.capacity();
    
    return 0;
}
