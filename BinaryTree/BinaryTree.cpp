/************************************************************************************************************************* 
 * COURSE:
 *
 * TOPIC:
 * DESCRIPTION: 
 * CREATED ON : Sat May 19 2018
 *************************************************************************************************************************/

/* ============================================== Header includes ====================================================== */
#include <iostream>
#include "BinaryTree.h"

/* ============================================== Declaration ====================================================== */
template <class Entry>
Binary_tree<Entry>::Binary_tree()
{
    root = NULL;
}

template <class Entry>
Binary_tree<Entry>::~Binary_tree()
{
}

template <class Entry>
bool Binary_tree<Entry>::empty()
{
    return root == NULL;
}

/* ============================================== SIZE() =============================================================== */
template <class Entry>
int Binary_tree<Entry>::size() const
{
    if (this->root == NULL)
        return 0;
    int s = this->recursive_size(this->root);
    
    return (s + 1);
}

template <class Entry>
int Binary_tree<Entry>::recursive_size(Binary_node<Entry> *sub_tree)
{
    if (sub_root == NULL)
        return 0;
    int s = 0;

    if (sub_root->left != NULL)
        s += this->recursive_size(sub_root->left) + 1;
    if (sub_root->right != NULL)
        s += this->recursive_size(sub_root->right) + 1;
    
    return s;
}

/* ============================================== TRAVERSAL ============================================================ */
template <class Entry>
void Binary_tree<Entry>::preorder(void (*visit)(Entry &))
{
    recursive_preorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::inorder(void (*visit)(Entry &))
{
    recursive_inorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::preorder(void (*visit)(Entry &))
{
    recursive_postorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry> *sub_root, void (*vist)(Entry &))
{
    if (sub_root != NULL)
    {
        recursive_preorder(sub_root->left, visit);
        (*visit)(sub_root->data);
        recursive_preorder(sub_root->right, visit);
    }
}


template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &))
{
    if (sub_root != NULL)
    {
        (*visit)(sub_root->data);
        recursive_inorder(sub_root->left, visit);
        recursive_inorder(sub_root->right, visit);
    }
}

template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &))
{
    if (sub_root != NULL)
    {
        recursive_postorder(sub_root->left, visit);
        recursive_postorder(sub_root->right, visit);
        (*visit)(sub_root->data);
    }
}

/* ============================================== CLEAR() ============================================================== */
template <class Entry>
void Binary_tree<Entry>::clear()
{
    if (this->root != NULL)
        recursive_clear(this->root);
}

template <class Entry>
void Binary_tree<Entry>::recursive_clear(Binary_node<Entry> *sub_root)
{
    if (sub_root->left != NULL)
        recursive_clear(sub_root->left);
    if (sub_root->right != NULL)
        recursive_clear(sub_root->right);
    delete sub_root;
}

/* ============================================== HEIGHT() ============================================================= */
template <class Entry>
int Binary_tree<Entry>::height() const
{
    return recursive_height(this->root);
}

template <class Entry>
int Binary_tree<Entry>::recursive_height(Binary_node<Entry> * const &sub_root) const
{
    if (sub_root == NULL)
        return 0;
    int left;
    int right;
    int h;

    hleft = recursive_height(sub_root->left) + 1;
    hright = recursive_height(sub_root->right) + 1;

    h = (left > right) ? (left + 1) : (right + 1);

    return h;
}

/* ============================================== INSERT() ============================================================= */
template <class Entry>
void Binary_tree<Entry>::insert(const Entry &e)
{
    this->recursive_insert(this->root, e);
}

template <class Entry>
void Binary_tree<Entry>::recursive_insert(Binary_node<Entry> *&sub_root, const Entry &e)
{
    // if root is NULL
    if (sub_root == NULL)
    {
        sub_root = new Binary_node<Entry>(e);
    }
    else
    {
        int left = recursive_height(sub_root->left);
        int right = recursive_height(sub_root->right);

        // tree is balanced
        if (left <= right)
        {
            if (sub_root->left == NULL)
            {
                sub_root->left = new Binary_node<Entry>(e);
            }
            else
            {
                recursive_insert(sub_root->left, e);
            }
        }
        else
        {
            if (sub_root->right == NULL)
            {
                sub_root->right = new Binary_node<Entry>(e);
            }
            else
            {
                recursive_insert(sub_root->right, e);
            }
            
        }
        
    }
    
}
/* ============================================== XXXXXXXXXX ====================================================== */