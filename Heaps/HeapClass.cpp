//
//  main.cpp
//  lab08
//
//  Created by brian on 11/4/22.
//
//
//
// COMSC-210 Lab #8
// Array-based heap template.
//
// This is a starter file with a framework C++ template you can use as the
// basis for writing your heap.  In the 'private' section there are various
// utility functions that you can use to navigate around the tree.  The
// 'public' section contains the functions that your code in main() will use
// as an interface into the heap.
//
#include <iostream>
#include <ctime>
using namespace std;

template<class T>
class myHeap {
private:
   // Start with a small default size
   static const int DEFAULT_CAPACITY = 24;
   T * items;

   int itemCount; // Current count of heap items
   int maxItems;  // Maximum capacity of the heap

   // Returns the array index of the left child (if exists).
   int getLeftChildIndex(const int nodeIndex) const;
   
   // Returns the array index of the right child (if exists).
   int getRightChildIndex(int nodeIndex) const;
   
   // Returns the array index of the parent node.
   int getParentIndex(int nodeIndex) const;
   
   // Converts a semiheap to a heap.
   void heapRebuild(int nodeIndex);
   
   // Creates a heap from an unordered array.
   void heapCreate();
   
public:
   myHeap();
   myHeap(const T someArray[], const int arraySize);
   ~myHeap();
   
   // HeapInterface Public Methods:
   bool isEmpty() const;
   int getNumberOfNodes() const;
   void mySwap(T&, T&);
   T peekTop() const;
   bool add(const T& newData);
   bool remove();
   void clear();
};

// Given a nodeIndex, return its LEFT child index.  If the return
// value of this function is greater than or equal to itemCount, there is
// no left child (the node is a leaf).
template<class T>
int myHeap<T>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
}

// Given a nodeIndex, return its RIGHT child index.  Our array-based
// format implies that if a node has a right child, it must already have
// a left child.
template<class T>
int myHeap<T>::getRightChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 2;
}

// Given a nodeIndex, return its PARENT index.
template<class T>
int myHeap<T>::getParentIndex(const int nodeIndex) const
{
   return (nodeIndex - 1) / 2;
}

// Given a subheap rooted at index subIndex, rebuild the nodes
// so a heap is formed.
template<class T>
void myHeap<T>::heapRebuild(const int subIndex)
{
    //if the value of the left child index is within the range of the size of the heap and
    //if the left child is greater than its parent the values are swapped
    if (getLeftChildIndex(subIndex) <= itemCount && items[getLeftChildIndex(subIndex)] > items[subIndex])
        swap(items[getLeftChildIndex(subIndex)], items[subIndex]);
    
    //if the value of the right child indexn is within the range of the size of the heap and
    //if the right child is  greater than its parents then the values are swapped
    if (getRightChildIndex(subIndex) <= itemCount && items[getRightChildIndex(subIndex)] > items[subIndex])
        swap(items[getRightChildIndex(subIndex)], items[subIndex]);

}

// Rebuild the entire heap.  This is the 'bottom up' algorithm.
template<class T>
void myHeap<T>::heapCreate()
{
   for (int index = itemCount / 2; index >= 0; index--)
   {
      heapRebuild(index);
   }
}

// Constructor that accepts an existing array
template<class T>
myHeap<T>::myHeap(const T someArray[], const int arraySize)
{
    //sets the numer of nodes in the heap to the size of the array and the sets the size of the heap
    //to double the size of 'someArray'
    itemCount = arraySize;
    maxItems = arraySize * 2;
    items = new T[maxItems];
    
    //defines nodes in the heap with the value of 'someArray'
    for (int i = 0; i < itemCount; i++)
    {
        items[i] = someArray[i];
    }
    
    heapCreate();   //called to heapify the data
}

// Default constructor
template<class T>
myHeap<T>::myHeap()
{
   itemCount = 0;
   maxItems = DEFAULT_CAPACITY;
   items = new T[DEFAULT_CAPACITY];
}

// Default destructor
template<class T>
myHeap<T>::~myHeap()
{
    delete items;
}

// Return whether the heap is empty
template<class T>
bool myHeap<T>::isEmpty() const
{
   return itemCount == 0;
}

// Return the total number of nodes
template<class T>
int myHeap<T>::getNumberOfNodes() const
{
   return itemCount;
}

// Remove the root of the heap and rebuild it
template<class T>
bool myHeap<T>::remove()
{
    //return false if the heap has no nodes
    if (!itemCount)
        return false;
    
    //if the heap isn't empty set the root to the rightmost leaf, decrement the size of the heap, and rebuild the heap
    else
    {
        items[0] = items[itemCount];
        itemCount--;
        heapCreate();
        return true;
    }
}

// Clear all items (note we do not resize the array here).
template<class T>
void myHeap<T>::clear()
{
   itemCount = 0;
}

// Return the value at the root of the heap
template<class T>
T myHeap<T>::peekTop() const
{
   return items[0];
}

// Add a new item to the heap
template<class T>
bool myHeap<T>::add(const T& newData)
{
    if (itemCount == maxItems)
        return false;
    else
    {
        items[++itemCount] = newData;
        heapCreate();
        return true;
    }
}


int main()
{
    srand(static_cast<unsigned>(time(0)));  //seeds rand
    const int SIZE = 10;
    double testArr[SIZE];  //array to hold test data
    

    
    cout << "Existing array test: " << endl;
    cout << "–––––––––––––––––––––––––––––––––––––––––\n";
    
    //fills 'testArr' with random number from 0-999
    for (int i = 0; i < SIZE; i++)
    {
        testArr[i] = rand() % 100;
    }
    
    //displays value of elements in 'testArr'
    cout << "Array value: " << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << testArr[i] << " ";
    }
    
    myHeap<double> heap1(testArr, SIZE);   //initializes heap using 'testArr' data
    
    //displays status of 'heap1' and the number of elements in the heap
    heap1.isEmpty() ? cout << "\nThe heap is empty!\n" : cout << "\nThe heap isn't empty!\n";
    cout << "The number of nodes in the heap is: " << heap1.getNumberOfNodes() << endl;
    
    //displays the root of the heap and then removes the root from the heap
    cout << "Displaying the heap: " << endl;
    while (!heap1.isEmpty())
    {
        cout << heap1.peekTop() << " ";
        heap1.remove();
    }
    
    heap1.clear();
    
    cout << endl << endl << endl;
    //---------------------------------------------------------------------------------------------
    
    cout << "Empty array test: \n";
    cout << "–––––––––––––––––––––––––––––––––––––––––\n";
    
    //fills 'testArr' with random number from 0-999
    for (int i = 0; i < SIZE; i++)
    {
        testArr[i] = rand() % 1000;
    }
    
    //displays value of elements in 'testArr'
    cout << "Array value: " << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << testArr[i] << " ";
    }
    
    myHeap<int> heap2;  //declares an empty heap named 'heap2'
    
    //displays status of 'heap2' and the number of nodes in the heap
    heap2.isEmpty() ? cout << "\nThe heap is empty!\n" : cout << "\nThe heap isn't empty!\n";
    cout << "The number of nodes in the heap is: " << heap2.getNumberOfNodes() << endl;
    
    //fills 'heap2' with data from 'testArr'
    for (int i = 0; i < SIZE; i++)
    {
        try
        {
            if (!heap2.add(testArr[i]))
            {
                throw true;
            }
        }
        catch (bool full)
        {
            cout << "\n\nERROR! THERE IS NOT ENOUGH SPACE IN THE HEAP TO STORE THE ARRAY. EXITING PROGRAM NOW!\n\n";
            exit(EXIT_FAILURE);
        }
    }
    
    //displays root of 'heap2' then removes the root of the heap
    cout << "Displaying the heap: " << endl;
    while (!heap2.isEmpty())
    {
        cout << heap2.peekTop() << " ";
        heap2.remove();
    }

    heap2.clear();
    cout << endl << endl << endl;
    //---------------------------------------------------------------------------------------------
    
    return 0;
}
