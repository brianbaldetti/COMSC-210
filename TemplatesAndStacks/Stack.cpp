//
//  main.cpp
//  lab02
//
//  Created by brian on 9/7/22.
//
#include <iostream>
#include <string>
#include <stack>
#include <fstream>
using namespace std;

int main()
{
    //creates a input file obj called inFile
    ifstream inFile("/Users/messenger01/Desktop/stack.txt");
    
    //checks if inFile opens if is it then "check stack" code is ran
    if (inFile)
    {
        stack<int> isStack;         //defines stack
        string tmpString;           //creates a temporary string to hold inFile data
        bool flagFail = false;      //set to false if "check stack" is not a stack
        
        
        inFile >> tmpString;
        do
        {
            inFile >> tmpString;
            
            //runs if 'i' is ran into and 'flagFail is set to false
            if (tmpString[0] == 'i' && !flagFail)
                isStack.push(stoi(tmpString.substr(1)));
            
            //runs is remove value is run into
            else if (tmpString[0] == 'r' && !isStack.empty())
            {
                //checks if top of stack is equal to the remove value if not then contents
                //are cleared and 'flagFail' is set to true
                if (isStack.top() != stoi(tmpString.substr(1)))
                {
                    cout << "Not Stack.\n";
                    
                    //clears contents of 'isStack'
                    while (!isStack.empty())
                        isStack.pop();
                    
                    flagFail = true;
                }
                else
                    isStack.pop();
                
            }
            //runs a value other than a 'i' or 'r' is encountered
            else if (tmpString[0] != 'i' && tmpString[0] != 'r')
            {
                if (isStack.empty() && !flagFail)
                    cout << "Stack.\n";
                
                else if (!isStack.empty())
                    cout << "Not Stack.\n";
                
                //clears contents of 'isStack'
                while (!isStack.empty())
                    isStack.pop();
                
                flagFail = false;
            }
            
        } while(!inFile.eof());
        
        //checks the final state of isStack to determine if it is a stack or not
        if (isStack.empty() && !flagFail)
            cout << "Stack.\n";
        else
            cout << "Not stack.\n";
    }
    else
    {
        return 1;
    }
    return 0;
}

