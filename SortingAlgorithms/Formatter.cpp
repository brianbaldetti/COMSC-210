//
//  main.cpp
//  class04
//
//  Created by brian on 9/27/22.
//  this program finds the chars in a sting and returns the 'hidden' (non-upercase chars)
//  next the program will display the non-uppercase chars that it finds in a string
//
#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
using namespace std;

string findWord(string);
char * findWord2(char[], int);

int main()
{
    
    string test = "brHHuHHHHHhHHH";
    char test2[] = "brFuFh";
    cout << findWord(test) << endl;
    cout << findWord2(test2, 6) << endl;
    
    return 0;
}

string findWord(string inputStr)
{
    string outputStr = "";
    
    for (int i = 0; i < inputStr.length(); i++)
    {
        if (islower(inputStr[i]))
        {
            outputStr += inputStr[i];
        }
    }
    
    return outputStr;
}

char * findWord2(char input[], int size)
{
    char output[100];
    int index = 0;
    
    for (int i = 0; i < size; i++)
    {
        if (islower(input[i]))
        {
            output[index++] = input[i];
        }
    }
    
    output[index] = '\0';
    return output;
}
