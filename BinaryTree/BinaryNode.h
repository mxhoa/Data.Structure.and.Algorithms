/************************************************************************************************************************* 
 * COURSE:  DATA STRUCTURE and ALGORITHMS
 *
 * TOPIC:   BINARY NODE
 * DESCRIPTION: This is a binary node struct that contains the data member and pointers to the left and right children 
 *              of this node
 * CREATED ON : Sat May 19 2018
 *************************************************************************************************************************/

/* ============================================== Header includes ====================================================== */
#ifndef BINARY_NODE_H
#define BINARY_NODE_H

typedef enum {
    left_higher,
    equal_height,
    right_hegher
} Balance_factor;

/**
 * @brief   Each node of a binary tree has both a left and a right subtree.
 *          These subtrees can be located by pointers to their root nodes.
 */
template <class Entry>
struct Binary_node
{
    // data memebers
    Entry data;
    Binary_node<Entry> *left;
    Binary_node<Entry> *right;

    // Constructor
    Binary_node();
    Binary_node(const Entry &x);
    virtual ~Binary_node();

};
#endif /* BINARY_NODE_H */