//
//  main.cpp
//  class03
//
//  Created by brian on 9/20/22.
//  program test if a string is a palindrome or not
//
#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool palindrome(string);
bool palindrome2(string);
bool palindrome3(string);

int main()
{
    string test = "ii88ii";
    palindrome3(test) ? cout << "True!\n" : cout << "False!\n";
    
    return 0;
}
/*
    compares string first element to its last element
    returns true if they are all the same and false otherwise
*/
bool palindrome(string inString)
{
    for (int i = 0; i < inString.length(); i++)
    {
        if (inString[i] != inString[(inString.length() - i - 1)])
            return false;
    }
    return true;
}

/*
    function returns if a string is a palindrome or not
    unlike the last funciton this function uses a stack
 */
bool palindrome2(string inString)
{
    string tmp = "";
    stack<char> charStack;
    
    for (int i = 0; i < inString.length(); i++)
        charStack.push(inString[i]);
    for (int i = 0; i < inString.size(); i++)
    {
        tmp += charStack.top();
        charStack.pop();
    }
    if (tmp != inString)
        return false;
    
    return true;
}
/*
    this function also returns true if a string is a palindrome or not
    this funciton is more efficient than the others
 */
bool palindrome3(string inString)
{
    string tmp = "";
    
    for (int i = static_cast<int>(inString.size() - 1); i > inString.size() / 2 - 1; i--)
        tmp += inString[i];
    if (tmp != inString.substr(0, inString.size() / 2))
        return false;
    
    return true;
}
