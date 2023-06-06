/*
 * This header file implements a simple (template) 'bag' of items with a fixed
 * capacity.
 */

#ifndef SORTABLEBAG_h
#define SORTABLEBAG_h
#include <algorithm>

template<class ItemType>
class SortableBag {

    // Inside the class, the bag is represented with a dynamic array of items.
    // The array is sized by a mandatory parameter passed to the constructor.
    
private:
    ItemType *items = 0;                    // Array of bag items
    int itemCount = 0;                      // Current count of bag items 
    int maxItems = 0;                       // Max capacity of the bag
   
public:
    SortableBag(int howMany);               // Constructor -- your code
    int getItemCount() const;               // Retrieve the number of items
    bool add(const ItemType&);              // Add an item to the bag
    void clear();                           // Clear all items

    // Here are the prototypes for your sort(), verify() and printBag()
    // member functions.
    void sort();
    bool verify();
    void printBag();
};

// Add the code for your constructor sort(), verify() and printBag()
// member functions here.
template<class ItemType>
void SortableBag<ItemType>::sort()
{
    for (int i = 0; i < maxItems - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < maxItems; j++)
        {
            if (items[minIndex] > items[j])
                minIndex = j;
        }
        
        std::swap(items[i], items[minIndex]);
    }
}

template<class ItemType>
bool SortableBag<ItemType>::verify()
{
    for (int i = 0; i < maxItems - 1; i++)
    {
        if (items[i] > items[i + 1])
        {
            return false;
        }
    }
    
    return true;
}

template<class ItemType>
void SortableBag<ItemType>::printBag()
{
    
    for (int i = 0; i < maxItems; i++)
        std::cout << items[i] << " ";
}

// Example starter constructor.
//
// This function accepts one argument (howMany) indicating the size of the bag.
// Note, this is the only constructor needed.
//
template<class ItemType>
SortableBag<ItemType>::SortableBag(int howMany) {
    // Your code here
    if (howMany < 0)
    {
        std::cout << "Value MUST NOT be a negative value!\n";
        while (howMany < 0)
        {
            std::cout << "Enter a valid input for the bag: ";
            std::cin >> howMany;
        }
    }
    
    ItemType * ptrToArr = new ItemType[howMany];
    items = ptrToArr;
    maxItems = howMany;
}


// Provided template functions.  No modification needed.
// -----------------------------------------------------

// Return the number of items currently in the bag
template<class ItemType>
int SortableBag<ItemType>::getItemCount() const {
    return itemCount;
}

// Adds a new item to the bag, returning whether there was space (false
// if the add failed)
template<class ItemType>
bool SortableBag<ItemType>::add(const ItemType& newEntry)
{
    bool hasRoomToAdd = (itemCount < maxItems);
    if (hasRoomToAdd) {
        items[itemCount] = newEntry;
        itemCount++;
    }
    
    return hasRoomToAdd;
}

// Resets the number of items held in the bag.  The data values are NOT
// cleared and the memory allocated for the bag stays the same.
template<class ItemType>
void SortableBag<ItemType>::clear() {
    itemCount = 0;
}
#endif
