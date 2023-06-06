//
//  main.cpp
//  HashFunctions
//
//  Created by brian on 11/8/22.
//
#include <iostream>
using namespace std;
const int HASH_SIZE = 13577;

// Make an integer out of the first and last characters.
unsigned int genHashKey(string key) {
    int beg, end;
    unsigned int num;

    beg = (int) key[0];
    end = (int) key[key.size() - 1];

    num = (beg & 0xFF) | ((end & 0xFF) << 16);
     
    return (num % HASH_SIZE);
}

///////////// #2
// Make an integer out of the first and second characters.
unsigned int genHashKey(string key) {
    int beg, end;
    unsigned int num;

    beg = (int) key[0];
    end = (int) key[1];

    num = (beg & 0xFF) | ((end & 0xFF) << 16);

    return (num % HASH_SIZE);
}

///////////// #3
// Make an integer out of the first and middle characters.
unsigned int genHashKey(string key) {
    int beg, end;
    unsigned int num;

    beg = (int) key[0];
    end = (int) key[key.size() / 2];

    num = (beg & 0xFF) | ((end & 0xFF) << 16);

    return (num % HASH_SIZE);
}


///////////// #4
// The 'djb2' hash
// Reference for this one and the next three:
// http://www.cse.yorku.ca/~oz/hash.htmlLinks to an external site.
unsigned int genHashKey(string key) {
    unsigned int hash = 5381;
 
    for (int i = 0; i < key.size(); i++)
        hash = ((hash << 5) + hash) + key[i];

    return (hash % HASH_SIZE);
}

///////////// #5
// The 'sdbm' hash
unsigned int genHashKey(string key) {
    unsigned int hash = 0;

    for (int i = 0; i < key.size(); i++)
        hash = key[i] + (hash << 6) + (hash << 16) - hash;
    return (hash % HASH_SIZE);
}

///////////// #6
// The 'Jenkins' hash
unsigned int genHashKey(string key) {
    unsigned int hash = 0;

    for (int i = 0; i < key.size(); i++) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return (hash % HASH_SIZE);
}

///////////// #7
// The 'Kernighan and Ritchie' hash
unsigned int genHashKey(string key) {
    unsigned int hashval = 0;

    for (int i = 0; i < key.size(); i++)
        hashval = (int)key[i] + 31*hashval;

    return (hashval % HASH_SIZE);
}

int main()
{
    
    return 0;
}
