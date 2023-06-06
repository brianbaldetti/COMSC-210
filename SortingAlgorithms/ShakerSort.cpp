//
//  main.cpp
//  ExampleShakerSort
//
//  Created by brian on 9/27/22.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

// This code sorts an array of SORTNUM numbers using shakerSort.
// Instrumentation is added to the sort function that will output:
// - number of swaps
// - number of comparisons

#define SORTNUM 1000   // Size of the array to be sorted
#define MAXNUM  1000  // Max random number + 1

void fill(int array[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        array[i] = rand() % MAXNUM + 1;
    }
}

// Verify that an array is sorted
bool verify(int array[], int n, bool asc) {
  for (int i = 0; i < n - 1; i++) {
    if (asc && (array[i] > array[i + 1])) {
      cerr << "verify failed idx " << i << ": " << array[i] << " -- " << array[i + 1] << endl;
      return (false);
    }
    if (!asc && (array[i] < array[i + 1])) {
      cerr << "verify failed idx " << i << ": " << array[i] << " -- " << array[i + 1] << endl;
      return (false);
    }
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
void shakerSort(int theArray[], int n, int rvals[], bool asc)
{
       bool sorted = false; // False when swaps occur
       int pass = 1;
       int swaps = 0;
       int comps = 0;
       bool exch = false;
       bool down = false;
       int index = 0;

       while (!sorted && (pass < n)) {
           sorted = true;

           //cout << "pass " << pass << " down " << down << endl;
           for (;;) {
             // now all entries in theArray[0..index–1]
             // are <= theArray[index]
             int nextIndex = down ? index - 1 : index + 1;
             comps++;
             if (down)
                exch = asc ? (theArray[index] < theArray[nextIndex] ? true : false) :
                  (theArray[index] > theArray[nextIndex] ? true : false);
             else
                exch = asc ? (theArray[index] > theArray[nextIndex] ? true : false) :
                  (theArray[index] < theArray[nextIndex] ? true : false);
             if (exch) {
                // Exchange entries
                //cout << "swapping " << index << " and " << nextIndex << endl;
                std::swap(theArray[index], theArray[nextIndex]);
                sorted = false; // Signal exchange
                swaps++;
             }
             if (down) {
               --index;
               if (index == pass - ((pass / 2) + 1))
                 break;
             } else {
               ++index;
               if (index == n - (pass - pass/2))
                 break;
             }
          }
          down = !down;
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
    shakerSort(array1, SORTNUM, v, false); /* sort in descending order */
    shakerSort(array1, SORTNUM, v, true); /* sort in ascending order */
    cout << "n: " << SORTNUM << endl;
    cout << "Comparisons: "<< v[0] << endl;
    cout << "Swaps: " << v[1] << endl;
    if (v[2] != -1)
        cout << "Stopped sorting after " << v[2] << " pass(es)" << endl;
    cout << endl;
    if (!verify(array1, SORTNUM, true)) {
      cout << "Sort failed!" << endl;
      return (-1);
    }

    fill(array1, SORTNUM);
    cout << "(best) ascending sorted first" << endl
         << "-----------------------------" << endl;

    shakerSort(array1, SORTNUM, v, true);
    shakerSort(array1, SORTNUM, v, true);
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
    shakerSort(array1, SORTNUM, v, true);
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

    cout << "(bad) lowest element at far right" << endl
         << "---------------------------------" << endl;
    fill(array1, SORTNUM);
    array1[SORTNUM - 1] = 0;
    shakerSort(array1, SORTNUM, v, true);
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
