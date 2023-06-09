//
//  main.cpp
//  lab04part2
//
//  Created by brian on 9/22/22.
//
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include <cassert> // for assert
#include <cmath>   // for log and pow
#include <cstdlib> // for srand and rand
#include <ctime>   // for clock( ), clock_t,
                   // time, and CLOCKS_PER_SEC

#define INFILE "/Users/messenger01/Desktop/names.txt"  // File from which to read the data
#define NLINES  1000000      // Number of lines to read -- make this large enough
                            // so all the tests can be run.

// Read the file.  'len' is the requested number of lines,
// 'c' is the actual count of lines read. Returns true if
// the requested number of lines was read, false otherwise.
bool readFile(vector<string> &v, int len, int &c) {
        string tmp;

        // Open the file.
        ifstream inFile(INFILE);
        if (inFile.fail()) {
                cout << "Failed to open the file: "
                         << INFILE << endl;
                    return (false);
        }
        while (getline(inFile, tmp)) {
            // Successful read of all the lines
            if (++c == len) {
                inFile.close();
                return (true);
            }

            // Hit end of file before reading requested amount.
            if (inFile.eof())
                break;

            // Add to our vector.
            v.push_back(tmp);
        }

        // If we got here we hit end of file before reading
        // all of the requested lines.
        inFile.close();
        return (false);
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    rand(); // seed the RNG (we'll need it)

    // programmer customizations go here
    int n = 1000;          // <---- THE STARTING PROBLEM SIZE
    string bigOh = "O(n squared)";  // <---- YOUR PREDICTION: O(n),
                            //       O(n log n), or O(n squared)
                            
    vector<string> names;   // The test data
    int c = 0;              // Actual number of lines read as test data
                            // (in case of a problem reading the file)
    
    cout.setf(ios::fixed);
    cout.precision(4);
    double elapsedSecondsNorm = 0;
    double expectedSeconds = 0;

    // Setup the data for our tests
    if (readFile(names, NLINES, c) == false) {
        cerr << "Error: could not read " << NLINES << " lines from "
             << INFILE << ", actual read: " << c << ", exiting..." << endl;
        return (-1);
    }

    
    for (int cycle = 0; cycle < 4; cycle++, n*= 2) {

        // Any pre-problem setup goes here
        int count = 0;
        vector<string> sortVec;
        
        // General flow:
        // start the timer, do something, and stop the timer
        clock_t startTime = clock();

        // Add your algorithm here
        readFile(sortVec, n, count);
        
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (sortVec[i] > sortVec[j])
                {
                    swap(sortVec[i], sortVec[j]);
                }
            }
        }
        
        // do something where n is the "size" of the problem
        clock_t endTime = clock();

        // validation block -- assure that process worked
        // if applicable
        // cleanup if applicable
        for (int i = 1; i < n; i++)
            assert(sortVec[i - 1] <= sortVec[i]);
        

        // compute timing results
        double elapsedSeconds = (double) (endTime - startTime) / CLOCKS_PER_SEC;
        double factor = pow(2.0, double(cycle));
        
        if (cycle == 0)
            elapsedSecondsNorm = elapsedSeconds;

        // Calculate what we "expected" the result to be based
        // on what bigOh is set to above
        else if (bigOh == "O(n)")
            expectedSeconds = factor * elapsedSecondsNorm;
        else if (bigOh == "O(n log n)")
            expectedSeconds = factor *
                              log(double(n)) / log(n / factor) *
                              elapsedSecondsNorm;
        else if (bigOh == "O(n squared)")
            expectedSeconds = factor * factor * elapsedSecondsNorm;
        
        // reporting block
        cout << elapsedSeconds;
        if (cycle == 0) cout << " (expected " << bigOh << ')';
        else cout << " (expected " << expectedSeconds << ')';
        cout << " for n=" << n << endl;
    }
     
     
    
    return 0;
}
