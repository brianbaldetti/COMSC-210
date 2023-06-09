//
//  main.cpp
//  lab09
//
//  Created by brian on 11/8/22.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

//
// This is a starter file to help frame your ideas around
// Lab #9.  The reading of each line in the file is completed
// for you.
//

const string DATAFILE = "/Users/messenger01/Desktop/netflix.csv";     // Input file (CSV)
const int NFIELDS = 5;                     // Number of fields in
                                           // each line of the input file
const char DELIMITER = ',';                // The field separator for the file.
                                           // For a CSV, this is a comma.

// This holds a single Netflix entry.  Each line in the file should
// correspond to one of these structs.  If you use separate chaining, each bucket
// will have a linked list.
//
// Note: this structure is not yet ready to be part of a linked list.  It
// needs an additional pointer to the 'next' entry.
//
struct netflix_entry
{
    string type = "";                   // The type of entry (movie or tv show)
    string title = "";                  // Title
    string director = "";               // Director's full name
    string country = "";                // Country of release
    int year = 0;                      // Year of release
    netflix_entry * next = nullptr; //ptr to next entry
    
    void resetToDefault()
    {
        type = "";
        title = "";
        director = "";
        country = "";
        year = 0;
        next = nullptr;
    }
};

// Starting number of buckets, adjust as needed -- should be a prime number.
const int HASH_SIZE = 2089;

// Hash table for all of the entries -- static so it's zeroed for free.
static netflix_entry * entryHash[HASH_SIZE];

// Generate a hash key, given a string (this would come from the
// string the user typed to find).  your hash function goes here.
//
// Don't use this one, it's bad! (everything will hash to only a few buckets).
unsigned int getHashKey(string key) {
    unsigned int hash = 5381;

    // use the first letter of the key
    //sum = (int)key[0];
    
    //use the value of the entire title
    for (int i = 0; i < key.length(); i++)
        hash = ((hash << 5) + hash) + key[i];

    // for debugging -- add a statement like this to
    // see the hash key generated for an entry.
    //
    //cout << "title: " << key << " hash key: " << sum % HASH_SIZE << endl;

    // Return the key which can be used as an index into entryHash
    // to select which bucket.
    
    //basically tmp is the value of HASH_SIZE multiplied by 33 (a prime number) plus sum which is a psudo-random number
    return (hash % HASH_SIZE);
}

// Reads a single entry, filling in the
// fields (title, etc.) passed by the caller.
void readSingleEntry(const string &str, netflix_entry *newEnt)
{
    istringstream istr(str);
    string fields[NFIELDS];
    string tmp;
    int i = 0;

    // Read each field separated by a comma
    while (getline(istr, tmp, DELIMITER) && i < NFIELDS) {
        fields[i++] = tmp;
    }

    // Make a new Netflix entry based on the
    // fields just read from the file.
    newEnt->type = fields[0];
    newEnt->title = fields[1];
    newEnt->director = fields[2];
    newEnt->country = fields[3];
    newEnt->year = atoi(fields[4].c_str()); // Convert the string to an int
}

// Insert a new entry into the hash table
void entryInsert(netflix_entry * newEnt) {

    //
    // Complete this function.
    //
    // Accepts a new entry 'newEnt' and finds the correct hash bucket
    // based on its hash key.  Adds the entry to a bucket.
    //
    netflix_entry * tmp = entryHash[(getHashKey(newEnt->title))];
    
    if (!tmp)
    {
        entryHash[(getHashKey(newEnt->title))] = newEnt;
    }
    else
    {
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        
        tmp->next = newEnt;
    }
}

// This function accepts a string title and a reference
// to an empty entry.
//
// Upon return,
// - 'foundEnt' will be filled-in with what was found.
// - The function will return 'true' if something was found, 'false' otherwise.
// - The 'ncmp' parameter tracks the number of comparisons required
//
bool entryFind(const string & title, netflix_entry & foundEnt, int & ncmp)
{
    unsigned int key = getHashKey(title);
    foundEnt.resetToDefault();
    ncmp = 0;
    
    //debugging statement to return key of searched for index
    //cout << "Key: " << key << endl;

    //
    // Complete this function.
    // (These are example parameters)
    //
    // Accepts a key, a reference to a found entry, and reference to
    // number of comparisons.  Fill-in the values of the 'foundEnt' with
    // the values from the entry found in the hash table.
    //
    netflix_entry * tmp = entryHash[key];
    if (tmp == nullptr)
    {
        ncmp++;
        return false;
    }
    else
    {
        while (tmp->next)
        {
            if (tmp->title == title)
            {
                foundEnt = *tmp;
                ncmp++;
                return true;
            }
            
            ncmp++;
            tmp = tmp->next;
        }
    }
    
    return false;
}

//function can be used to find max chain length of hash table

void findMaxChain()
{
    //defines variables
    int max = 0;
    int curr = 0;
    netflix_entry * tmp = nullptr;
    
    for (int i = 0; i < HASH_SIZE; i++)
    {
        //'tmp' and 'curr' must be reset each time
        tmp = entryHash[i];
        curr = 0;
        
        if (tmp)
        {
            curr++;
            
            while (tmp->next)
            {
                curr++;
                tmp = tmp->next;
            }
            
            //test if chain length is a new max
            if (curr > max)
                max = curr;
        }
    }
    
    cout << "Max is: " << max << endl;
}


//
// Sample main().
//
int main() {
    ifstream inFile(DATAFILE);
    string inputLine, inputStr;
    int linesRead = 0, comparisons = 0;
    netflix_entry returnValue;


    if (!inFile.good()) {
        cerr << "Cannot open the input file!" << endl;
        exit(-1);
    }

    // Read in each entry
    while (getline(inFile, inputLine)) {
        // Keep a counter of read lines.
        linesRead++;

        // Dynamically allocate a new entry
        netflix_entry *entp = new netflix_entry;

        // Read the next line from the file, passing a pointer
        // to the newly allocated entry.
        readSingleEntry(inputLine, entp);

        // Now we have a complete entry, find where it goes
        // in the hash table and add it.
        entryInsert(entp);

        // Extra debugging statement: uncomment this to
        // see how many lines are being read from the file
        // in real-time.
        //
        //if (linesRead % 25 == 0)
        //    cerr << "Inserted " << linesRead << " entries" << endl;
    }

    // Handle errors and/or summarize the read
    if (linesRead == 0) {
        cerr << "Nothing was read from the file!" << endl;
        return (-1);
    } else {
        cout << "Read " << linesRead << " entries." << endl;
        cout << fixed << setprecision(2) << endl;
    }
    
    findMaxChain();
    
    // (example) Forever loop until the user requests an exit
    for (;;) {

        //
        // Your input loop goes here.
        //
        // If the user enters a blank line, use 'break'.
        // to exit the loop.
        //
        inputStr = "";
        cout << "Enter a movie or tv-show title, or press return to quit: ";
        getline(cin, inputStr);
        
        if (!inputStr.empty())
        {
            if (entryFind(inputStr, returnValue, comparisons))
            {
                cout << "\n–––––––––––––––––––––––––––––––––––––––––––\n";
                cout << "Comparisions: " << comparisons << endl;
                cout << "Type: " << returnValue.type << endl;
                cout << "Title: " << returnValue.title << endl;
                cout << "Director: " << returnValue.director << endl;
                cout << "Country: " << returnValue.country << endl;
                cout << "Year of release: " << returnValue.year << endl;
                cout << "–––––––––––––––––––––––––––––––––––––––––––\n";

            }
            else
            {
                cout << "\n–––––––––––––––––––––––––––––––––––––––––––\n";
                cout << "Not Found.\n";
                cout << "Comparisions: " << comparisons << endl;
                cout << "–––––––––––––––––––––––––––––––––––––––––––\n";
            }
        }
        else
        {
            break;
        }
        
        
    }

    // And we're done!
    cout << "Exiting..." << endl;

    return (0);
}
