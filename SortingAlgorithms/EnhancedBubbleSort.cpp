//
//  main.cpp
//  ExampleBubbleSort
//
//  Created by brian on 9/27/22.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

// This code sorts an array of SORTNUM numbers using bubbleSort.
// Instrumentation is added to the sort function that will output:
// - number of swaps
// - number of comparisons

#define SORTNUM 1000   // Size of the array to be sorted
#define MAXNUM  1000  // Max random number + 1

// Fill an array with random numbers
void fill(int array[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        array[i] = rand() % MAXNUM;
    }
}

// Verify that an array is sorted
bool verify(int array[], int n, bool asc) {
  for (int i = 0; i < n - 1; i++) {
    if (asc && (array[i] > array[i + 1]))
      return (false);
    if (!asc && (array[i] < array[i + 1]))
      return (false);
  }
  return (true);
}

// theArray - array to be sorted
// n - size of theArray
// rvals - additional info to fill-in, after this function completes,
//  rvals[0] is the number of comparisons
//  rvals[1] is the number of swaps
//  rvals[2] is how many passes were made, if less than n, otherwise -1
//  asc - is true if the array should be sorted in ascending order, else false
void bubbleSort(int theArray[], int n, int rvals[], bool asc)
{
       bool sorted = false; // False when swaps occur
       int pass = 1;
       int swaps = 0;
       int comps = 0;
       bool exch = false;
       while (!sorted && (pass < n)) {
           sorted = true;
           for (int index = 0; index < n - 1; index++) {
             // now all entries in theArray[0..index–1]
             // are <= theArray[index]
             int nextIndex = index + 1;
             comps++;
             exch = asc ? (theArray[index] > theArray[nextIndex] ? true : false) :
                 (theArray[index] < theArray[nextIndex] ? true : false);
             if (exch) {
                // Exchange entries
                std::swap(theArray[index], theArray[nextIndex]);
                sorted = false; // Signal exchange
                swaps++;
             }
          }
          pass++;
       }
       rvals[2] = -1;
       if (sorted && pass < n) {
           rvals[2] = pass - 1;
       }
       rvals[0] = comps;
       rvals[1] = swaps;
}

int main()
{
    int array1[SORTNUM];
    int v[3];

    unsigned seed = static_cast<unsigned>(time(0));
    srand(seed);
    fill(array1, SORTNUM);

    cout << "(worst) descending sorted first" << endl
         << "-------------------------------"
         << endl;
    bubbleSort(array1, SORTNUM, v, false); /* sort in descending order */
    bubbleSort(array1, SORTNUM, v, true); /* sort in ascending order */
    if (!verify(array1, SORTNUM, true)) {
      cout << "Sort failed!" << endl;
      return (-1);
    }
    cout << "n: " << SORTNUM << endl;
    cout << "Comparisons: "<< v[0] << endl;
    cout << "Swaps: " << v[1] << endl;
    if (v[2] != -1)
        cout << "Stopped sorting after " << v[2] << " pass(es)" << endl;
    cout << endl;

    fill(array1, SORTNUM);
    cout << "(best) ascending sorted first" << endl
         << "-----------------------------" << endl;

    bubbleSort(array1, SORTNUM, v, true);
    bubbleSort(array1, SORTNUM, v, true);
    if (!verify(array1, SORTNUM, true)) {
      cout << "Sort failed!" << endl;
      return (-1);
    }
    cout << "n: " << SORTNUM << endl;
    cout << "Comparisons: "<< v[0] << endl;
    cout << "Swaps: " << v[1] << endl;
    if (v[2] != -1)
        cout << "Stopped sorting after " << v[2] << " pass(es)" << endl;
    cout << endl;

    fill(array1, SORTNUM);
    cout << "(average) random" << endl
         << "----------------" << endl;
    bubbleSort(array1, SORTNUM, v, true);
    if (!verify(array1, SORTNUM, true)) {
      cout << "Sort failed!" << endl;
      return (-1);
    }
    cout << "n: " << SORTNUM << endl;
    cout << "Comparisons: "<< v[0] << endl;
    cout << "Swaps: " << v[1] << endl;
    if (v[2] != -1)
        cout << "Stopped sorting after " << v[2] << " pass(es)" << endl;
    cout << endl;

    return (0);
}

