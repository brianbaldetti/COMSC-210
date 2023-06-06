//
//  main.cpp
//  iwannadie
//
//  Created by brian on 10/11/22.
//
#include <iostream>
using namespace std;

// Sort array 'a' in-place, length of array is 'len'
void superSort(int a[], int len) {
    int maxElement = len - 1;
    for (int i = len - 1; i >= 0; i--) {
        if (a[i] > a[maxElement]) {
                swap(a[i], a[maxElement]);
                maxElement = i;
        }
    }
}

int main()
{
    int arr[5] {5, 4, 3, 6, 7};
    superSort(arr, 5);
    
    for (int i : arr)
        cout << i << " ";
    
    
    return 0;
}
