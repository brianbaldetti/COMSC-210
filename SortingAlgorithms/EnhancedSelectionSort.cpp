//
//  main.cpp
//  ExampleSelectionSort
//
//  Created by brian on 9/27/22.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
// This code sorts an array of SORTNUM numbers using selectionSort.
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

int findIndexOfLargest(const int theArray[], int size, bool asc, int &comps)
{
   int indexSoFar = 0; // Index of largest entry found so far
   for (int currentIndex = 1; currentIndex < size; currentIndex++)
   {
      // At this point, theArray[indexSoFar] >= all entries in
      // theArray[0..currentIndex − 1]
      comps++;
      if (asc) {
        if (theArray[currentIndex] > theArray[indexSoFar])
         indexSoFar = currentIndex;
      } else {
        if (theArray[currentIndex] < theArray[indexSoFar])
         indexSoFar = currentIndex;
      }
   }
   return indexSoFar;
}

void selectionSort(int theArray[], int n, int rv[], bool asc)
{
   // last = index of the last item in the subarray of items yet
   //        to be sorted;
   // largest = index of the largest item found
   int comps = 0;
   int swaps = 0;
   rv[2] = -1;
   for (int last = n - 1; last >= 1; last--) {
      // At this point, theArray[last+1..n–1] is sorted, and its
      // entries are greater than those in theArray[0..last].
      // Select the largest entry in theArray[0..last]
      int largest = findIndexOfLargest(theArray, last+1, asc, comps);
      
      // Swap the largest entry, theArray[largest], with
      // theArray[last]
      swaps++;
      std::swap(theArray[largest], theArray[last]);
   }
   rv[0] = comps;
   rv[1] = swaps;
}

int main()
{
    int array1[SORTNUM];
    int v[3];

    unsigned seed = time(0);
    srand(seed);
    fill(array1, SORTNUM);

    cout << "(worst) descending sorted first" << endl
         << "-------------------------------"
         << endl;
    selectionSort(array1, SORTNUM, v, false); /* sort in descending order */
    selectionSort(array1, SORTNUM, v, true); /* sort in ascending order */
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

    selectionSort(array1, SORTNUM, v, true);
    selectionSort(array1, SORTNUM, v, true);
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
    selectionSort(array1, SORTNUM, v, true);
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
