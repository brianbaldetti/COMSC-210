//
//  main.cpp
//  lab07
//
//  Created by brian on 10/17/22.
//
#include <iostream> //used for output
#include <map>  //used for map
#include <fstream>  //used for file input
#include <string>   //used for integer conversion
using namespace std;

int main()
{
    ifstream iFile("/Users/messenger01/Desktop/trees.txt");
    map<string, int> adrSearch;
    map<int, string> idSearch;
    
    string adr, id, input;
    int choice;
    
    if (iFile.good())   //runs if 'iFile' opens successfully
    {
        //primes iFile input
        getline(iFile, id);
        getline(iFile, adr);

        while (!iFile.eof())    //runs as long as the end of the file is not reached yet
        {
            //adds data to the map with the address as the key or the ID as the key
            adrSearch[adr] = stoi(id);
            idSearch[stoi(id)] = adr;
            
            getline(iFile, id);
            getline(iFile, adr);
        }
        
    }
    else    //runs if 'iFile' doesn't open successfully
    {
        cout << "Error! Can't open file!\n";
        return EXIT_FAILURE;
    }
    
    //do while loops runs while the user does not choose '3' which causes a msg to be displayed and closes the program
    do
    {
        cout << "–––––––––––––––––––––––––––––––––––––––––––\n";
        cout << "Menu: \n";
        cout << "1 - Find adress from ID number: \n";
        cout << "2 - Find ID from address: \n";
        cout << "3 - Exit the program: \n";
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();
        cout << endl;
        
            switch(choice)
            {
                //runs while the user tries to search for an address from an ID number
                case 1:
                {
                    cout << "\nEnter the ID number: ";
                    cin >> input;
                    
                    auto val = idSearch.find(stoi(input));
                    
                    if (val != idSearch.end())  //runs if found
                        cout << "The address is: " << idSearch[stoi(input)] << endl;
                    else    //runs if not found
                        cout << "The id " << input << " is not a valid ID.\n";
                    break;
                }
                //runs while the user tries to search for an ID number from an address
                case 2:
                {
                    cout << "\nEnter the address: ";
                    getline(cin, input);
                    
                    auto val = adrSearch.find(input);
                    
                    if (val != adrSearch.end())     //runs if found
                        cout << "The ID is: " << adrSearch[input] << endl;
                    else    //runs if not found
                        cout << "The address " << input << " is not a valid address.\n";
                    break;
                }
                //runs if the user wants to exit the program
                case 3:
                {
                    cout << "Exiting the program now. Bye!\n\n";
                    break;
                }
                //catch statment for invalid inputs that causes the loop to continue running
                default:
                {
                    cout << "Error! The input is invalid try again or enter '3' to exit the program.\n";
                }
            }
    } while (choice != 3);  //exit statement
    
    return 0;
}
