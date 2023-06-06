//
//  main.cpp
//  lab06
//
//  Created by brian on 10/11/22.
//
#include <iostream>
#include <ctime>
using namespace std;

const int ARRAYLEN = 10;

void merge(int a[], int first, int middle, int last) {
    
    //cout << "MERGE CALLED\n\n\n";
    
    int temp[ARRAYLEN] = { 0 };      // "Auxiliary" array to hold merged arrays
    int left = 0;                    // Counters to track positions in arrays, see below
    int right = 0;
    int cur = 0;
    int start = 0, stop = 0;
    
    //displays left side of the array
    cout << "\nLeft: ";
    for (int i = first; i < middle; i++)
        cout << a[i] << " ";
    //displays right side of array
    cout << "\nRight: ";
    for (int i = middle; i < last; i++)
        cout << a[i] << " ";
    

    // Loop through the left and right side sub-arrays, adding the next value
    // to the final array.  Remember, both sub-arrays are sorted at this point.
   
    for (left = first,         // 'left' will track the current position in the left side
         right = middle;       // 'right' will track the current position in the right side

         left < middle &&      // Continue as long as we have not exhausted the
         right < last;         // left OR right sides.

         cur++) {              // Each time through the array, increment the current position
                               // in the auxiliary array (contains the final, merged result)

        
        if (a[left] <= a[right]) {
            temp[cur] = a[left];     // Set the next value in the merged array
            left++;                  // "consume" one value in the left side

        } else {
        // The right side is next
            temp[cur] = a[right];    // Set the next value in the merged array
            right++;                 // "consume" one value in the right side
        }
    }

    // At this point we have exhausted either the left or right side.  Find
    // which one is *not* exhausted, then add each element to the final
    // merged array.
    if (left == middle) {
        start = right;          // The left side was exhausted first, right side needs copying
        stop = last;
    } else {
        start = left;           // The right side was exhausted first, left side needs copying
        stop = middle;
    }

    // Copy the remaining part of the array that still has elements
    while (start < stop) {
        temp[cur++] = a[start++];
    }
    
    //shows the merged array
    cout << "\nMerged array: ";
    for (int i = 0; i < cur; i++)
        cout << temp[i] << " ";
    cout << endl;


    // and we're done!  The 'temp' array contains the merged
    // values at this point.  Replace the values in the array that
    // was passed with the sorted values.
    for (int i = first, j = 0; i < last; i++, j++) { // 'i' holds the current position in the array
        a[i] = temp[j];                              // 'j' holds the current position in the temp array
    }

}


//
// A recursive version of merge sort.
// The function is first called with the entire array:
//     first == the beginning (index 0)
//     last == the size of the array (ARRAYLEN)
//
// Each subsequent (recursive) call divides the array into halves and a
// a call is made for each half, until there is an array of length 1.  An
// array of length 1 is already sorted, so the merge can continue.
//
void mergeSort(int a[], int first, int last) {

    int middle = first + (last - first) / 2;
    // To see the recursive calls, uncomment this and the indices will be printed
    //cout << "indices: " << first << " " << middle << " " << last << endl;

    // Base case:  the length of this sub-array is less than 1 for
    // each side (the total array length must be at least 2).
    if ((last - first) < 2)
        return;

    // Sort the left side
    mergeSort(a, first, middle);

    // Sort the right side
    mergeSort(a, middle, last);

    // Merge the left and right sub-arrays
    cout << (last - first) << endl;
    merge(a, first, middle, last);
}

//
// Add your main() function here. It should:
//  - Make an array to sort (a local variable is OK)
//  - Call mergeSort() to start the sorting and print the annotations
//  - Verify that the array is sorted
//

int main()
{
    //defines and initializes variables
    const int SIZE = 10;
    int QA[SIZE] = { 26, 12, 1, 56, 31, 3, 2, 88, 99, 94 };
    srand(static_cast<unsigned>(time(0)));
    
    
    //fills 'QA' with random numbers between 0-99
    for (int i = 0; i < SIZE; i++)
        cout << rand() % 100 << endl;
     
    
    //shows contents of 'QA' before being sorted
    cout << "Value of 'QA' before being sorted: \n";
    for (int i = 0; i < SIZE; i++)
        cout << QA[i] << " ";
    cout << "\n––––––––––––––––––––––––––––––––––––––––––––––––––––––";
    
    //calls 'mergSort' to sort the array
    mergeSort(QA, 0, SIZE);
    
    //check that forces the 'merSort' check to fail
    //uncomment to see unsuccessfull 'merSort' run
    //QA[0] = 100;
    
    //verifies that 'mergSort' successfully sorted the array
    cout << "\n––––––––––––––––––––––––––––––––––––––––––––––––––––––\n";
    for (int i = 0; i < SIZE - 1; i++)
    {
        if (QA[i] > QA[i + 1])
        {
            cout << "Error! Did not successfully sort.\n";
            return EXIT_FAILURE;
        }
    }
    cout << "The array has been successfully sorted using mergsort.\n";

    
    //shows the contents of 'QA' after being sorted
    cout << "Value of 'QA' after being sorted: \n";
    for (int i = 0; i < SIZE; i++)
        cout << QA[i] << " ";
    cout << endl << endl << endl;
        
    
    return 0;
}
