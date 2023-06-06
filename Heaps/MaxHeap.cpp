//
//  main.cpp
//  HeapExample
//
//  Created by brian on 11/3/22.
//
#include <iostream>

using namespace std;

//
// This is an example (non-template) function for creating
// a maxheap, using the array-based format.
//

// The default heap size.
#define HEAPSIZE 100

// C++ preprocessor macros for determining the left and right child, and the
// parent of a node.  These take arguments similar to functions (LEFT_CHILD(0) for example)
// but are implemented by the processor as a search-and-replace before the code is
// compiled.
#define LEFT_CHILD(x)       ((2 * x) + 1)
#define RIGHT_CHILD(x)      ((2 * x) + 2)
#define PARENT(x)           ((x - 1) / 2)

int heap[HEAPSIZE];
int itemCount = 0;

// Add a value to the heap.  This is the "bottom up" process where the
// node is added at the end of the array and continuously swapped until
// the right location is found.
void add(int val) {
    int addIndex = itemCount++;

    // Add it to the heap at the bottom
    heap[addIndex] = val;

    // If the heap is empty except for this node, we're done
    if (itemCount == 1) {
        return;
    }

    for (;;) {

        int parentIndex = PARENT(addIndex);

        // This is a maxheap so we must be less than
        // our parent node.  In this case, the relationship
        // does not hold (we are greater than)
        // so we need to swap.
        if (heap[addIndex] > heap[parentIndex]) {
                swap(heap[addIndex], heap[parentIndex]);

                // If we just swapped with the root, we're done.
                if (parentIndex == 0)
                    break;

                // Otherwise keep going

        } else {

            // In this case the relationship holds, we know
            // the node is in the right place.
            // Break out of the loop.
            break;
        }
        addIndex = parentIndex;
    }
}

int main()
{
    int myIndex = 0;

    // root is at index 0
    heap[0] = 10;

    // Set the root's right and left child
    heap[LEFT_CHILD(0)] = 12;
    heap[RIGHT_CHILD(0)] = 14;

    // Access the left child's parent
    myIndex = LEFT_CHILD(0);
    cout << "myIndex (root's left child) is: " << myIndex << endl;

    // This should give us the parent index
    // (which is 0 for the root)
    myIndex = PARENT(myIndex);
    cout << "myIndex (parent) is: " << myIndex << endl;

    // We just added 2 nodes to the tree
    itemCount += 2;

    return 0;
}
