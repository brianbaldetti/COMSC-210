/*
 * File: avltree.h
 * ---------------
 * This file defines the structure representation and basic operations for
 * the AVL tree.
 */

#ifndef _avltree_h
#define _avltree_h

/* Flag to enable tracing in the AVL tree */

extern bool traceBST;

/*
 * Type: BSTNode
 * -------------
 * This type represents a node in a binary search tree.
 */
struct BSTNode {
   int key; //holds key value
   BSTNode *left, *right;   //ptr to left and right child nodes
   int bf;  //contains the BF (balance factor) of the node; could be replaced with another more memory efficient datatype
};

/*
 * Function: displayTree
 * Usage: displayTree(t);
 *        displayTree(t, prefix);
 * ------------------------------
 * Displays the structure of the tree.  If prefix is supplied, it is
 * displayed before the line.
 */

void displayTree(BSTNode *t, const std::string & prefix = "");

/*
 * Function: insertNode
 * Usage: insertNode(t, key);
 * --------------------------
 * Enters the key into the tree that is passed by reference as the first
 * argument.
 */

void insertNode(BSTNode * & t, const int & key);

#endif
