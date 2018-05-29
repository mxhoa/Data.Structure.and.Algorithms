/************************************************************************************************************************* 
 * COURSE: DATA STRUCTURE and ALGORITHMS
 *
 * TOPIC:   TREE
 * DESCRIPTION: - A tree is a nonlinear data structure, which is used to represent hierarchical relationships
 *              (parent-child relationship). Each node is connected by another node by directed edges.
 *              
 *              -> ROOT      - The root of the tree is the only node in the tree that has no incoming edges.
 *                          It is the top node of a tree
 * 
 *              -> NODE      - It is a fundamental element of a tree. Each node has data and two pointers that
 *                          may point to null or its child's
 * 
 *              -> EDGE      - It is also a fundamental part of a tree, which is used to connect two nodes
 * 
 *              -> PATH      - A path is an ordered list of nodes that are connected by edges
 * 
 *              -> LEAF      - A leaf node is a node that has no children.
 * 
 *              -> HEIGHT    - The height of a tree is the number of edges on the longest path between the root
 *                          and a leaf.
 * 
 *              -> LEVEL     - The level of a node is the number of edges on the path from the root node to that node
 * 
 *              -> CHILDREN  - Nodes that have incoming edges from the same node to be said to be the children 
 *                          of that node
 * 
 *              -> PARENT    - Node is a parent of all the child nodes that are linked by outgoing edges.
 * 
 *              -> SIBLING   - Nodes in the tree that are children of the same parent are said to be siblings.
 * 
 *              -> ANCESTOR  - A node reachable by repeated moving from child to parent.
 * 
 *              - A binary tree is a type tree in which each node has at most two children (0, 1 or 2),
 *              which are referred to as the left child and the right child.
 * CREATED ON : Sat May 19 2018
 *************************************************************************************************************************/
#include "BinaryNode.h"
#include "utility.h"

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template <class Entry>
class Binary_tree
{
public:
    /**
     * @brief   Constructor Function
     */
    Binary_tree();

    /**
     * @brief   The method empty tests whether root is NULL to determine whether a Binary_tree is empty
     * @return  TRUE - if the binary tree is empty, otherwise FALSE
     */
    bool empty() const;

    /**
     * @brief   The tree has been traversed in prefix order sequence
     *          Under PREORDER traversal:   
     *          -> the ROOT is visited first. 
     *          -> the LEFT SUBTREE is visited second
     *          -> the RIGHT SUBTREE is visited third
     */
    void preorder(void(*visit)(Entry &));

    /**
     * @brief   The tree has been traversed in infix order sequence
     *          Under INORDER traversal:   
     *          -> the LEFT SUBTREE is visited first
     *          -> the ROOT is visited second
     *          -> the RIGHT SUBTREE is visited third
     */
    void inorder(void (*visit)(Entry &));

    /**
     * @brief   The tree has been traversed in postfix order sequence
     *          Under POSTORDER traversal:   
     *          -> the LEFT SUBTREE is visited first
     *          -> the RIGHT SUBTREE is visited second
     *          -> the ROOT is visited third
     */
    void postorder(void (*visit)(Entry &));

    /**
     * @brief   Get the numbers of nodes in the tree
     * @return  The number of nodes in the tree
     */
    int size() const;

    /**
     * @brief   All nodes of tree have been deleted, root set to NULL
     */
    void clear();

    /**
     * @brief   Get the height of the tree
     * @return  0 - an empty tree
     *          1 - none-node tree
     */
    int height() const;

    /**
     * @brief   PRE: Data of type Entry has been passed for insertion - note that 
     *          the prototype need not include parameter names, only data type
     *          POST: Parametter has been inserted into the shortest subtree
     *          or into the left subtree if equal height.
     */
    void insert(const Entry &);

    /**
     * @brief   Copy constructor
     *          Creates a deep copy of tree original
     */
    Binary_tree(const Binary_tree<Entry> &original);

    /**
     * @brief   Overloaded assignment operator
     *          The calling tree is reset as a deep copy of tree pointed to by original
     */
    Binary_tree &operator=(const Binary_tree<Entry> &original);
    
    /**
     * @brief   Destructor Function
     */
    virtual ~Binary_tree();
  protected:
    // Add auxiliary function prototypes here
    void recursive_preorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &));
    void recursive_inorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &));
    void recursive_postorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &));
    
    /**
     * @brief   sub_root is NULL or pointernts to a subtree of the Binary_tree
     * @return  a pointer to a deep copy of tree pointed to by sub_root
     */
    Binary_node<Entry>* recursive_copy(Binary_node<Entry> *sub_root);

    int recursive_size(Binary_node<Entry> *sub_root) const;
    int recursive_height(Binary_node<Entry> * const &sub_root) const;
    int recursive_insert(Binary_node<Entry> *&sub_root, const Entry &);
    void recursive_clear(Binary_node<Entry> *sub_root);

    Binary_node<Entry> *root;
};
#endif /* BINARY_NODE_H */