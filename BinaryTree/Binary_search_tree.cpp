/************************************************************************************************************************* 
 * COURSE: DATA STRUCTURE AND ALGORITHMS    
 *
 * TOPIC:   BINARY SEARCH TREE
 * DESCRIPTION: 
 * CREATED ON : Fri Jun 01 2018
 *************************************************************************************************************************/

/* ============================================== Header includes ====================================================== */
#include "Binary_search_tree.h"



/* ============================================== Declaration ========================================================== */
template <class Entry>
Binary_search_tree<Entry>::Binary_search_tree()
{
    std::cout << "Binary_search_tree - Constructor\n";
}

/* ============================================== Declaration ========================================================== */
template <class Entry>
ERROR_CODE Binary_search_tree<Entry>::remove(const Entry &old_data)
{
    return search_and_destroy(root, target);
}

template <class Entry>
ERROR_CODE Binary_search_tree<Entry>::remove_root(Binary_node<Entry> *&sub_root)
{
    if (sub_root == NULL)
        return RES_NOT_PRESENT;
    
    // Remember node to delete at end
    Binary_node<Entry> *to_delete = sub_root;

    if (sub_root->right == NULL)
        sub_root = sub_root->left;
    else if (sub_root->left == NULL)
        sub_root = sub_root->right;
    else 
    {
        to_delete = sub_root->left;
        Binary_node<Entry> *parent = sub_root;
        while(to_delete->right != NULL)
        {
            parent = to_delete;
            to_delete = to_delete->right;
        }
        sub_root->data = to_delete->data;   // Move from to_delete to root.
        if (parent == sub_root)
            sub_root->left = to_delete->left;
        else
            parent->right = to_delete->left;
    }
    delete to_delete;

    return RES_SUCCESS;
}

template <class Entry>
ERROR_CODE Binary_search_tree<Entry>::search_and_destroy(Binary_node<Entry>* &sub_root, const Entry &target)
{
    if (sub_root == NULL || sub_root == target)
        return remove_root(sub_root);
    else if (sub_root->data > target)
        return search_and_destroy(sub_root->left, target);
    else 
        return search_and_destroy(sub_root->right, target);
}
/* ============================================== Declaration ========================================================== */
template <class Entry>
ERROR_CODE Binary_search_tree<Entry>::tree_search(Entry &target) const
{
    if (!search_for_node(root, target))
        return RES_NOT_PRESENT;

    return RES_SUCCESS;
}

template <class Entry>
Binary_node<Entry> *Binary_search_tree<Entry>::search_for_node(Binary_node<Entry> *sub_root, const Entry &target) const
{
    #define _RECURSION_
#if defined _RECURSION_    
    /* USE RECURSION */
    if (sub_root == NULL || sub_root->data == target)
        return sub_root;
    else if (sub_root->data > target)
        return search_for_node(sub_root->left, target);
    else
        return search_for_node(sub_root->right, target);
#elif defined _LOOP_
    /* USER LOOP */
    while (sub_root != NULL && sub_root->data != target)
    {
        if (sub_root->data > target)
            sub_root = sub_root->left;
        else 
            sub_root = sub_root->right;
    }
    return sub_root;
#endif
}

/* ============================================== Declaration ========================================================== */
template <class Entry>
ERROR_CODE Binary_search_tree<Entry>::insert(const Entry &new_data)
{
    return search_and_insert(root, new_data);
}

template <class Entry>
ERROR_CODE Binary_search_tree<Entry>::search_and_insert(Binary_node<Entry>* &sub_root, const Entry &new_data)
{
    if (sub_root == NULL)
    {
        sub_root = new Binary_node<Entry>(new_data);
        return RES_SUCCESS;
    }

    if (sub_root->data > new_data)
        search_and_insert(sub_root->left, new_data);
    else if (sub_root->data < new_data)
        search_and_insert(sub_root->right, new_data);
    else
        return RES_DUPLICATE_ERROR;
}

/* ============================================== Declaration ========================================================== */
template <class Entry>
ERROR_CODE Binary_search_tree<Entry>::remove_root(Binary_node<Entry> *&sub_root) 
{
    if (sub_root == NULL) 
        return RES_NOT_PRESENT;
    Binary_node<Entry> *to_delete = sub_root;
    if (sub_root->right == NULL)
    {
        sub_root = sub_root->left;
    }
    else if (sub_root->left == NULL)
    {
        sub_root = sub_root->right;
    }
    else 
    {
        to_delete = sub_root->left;
        Binary_node<Entry> *parent = sub_root;
        while (to_delete->right != NULL) 
        {
            parent = to_delete;
            to_delete = to_delete->right;
        }
        sub_root->data = to_delete->data;
        if (parent == sub_root) 
        {
            sub_root->left = to_delete->left;
        }
        else
        {
            parent->right = to_delete->left;
        }
    }
    delete to_delete;

    return RES_SUCCESS;
}


template<class Entry>
ERROR_CODE Binary_search_tree<Entry>::remove(const Entry &target)
{
    return search_and_destroy(this->root, target);
}

template<class Entry>
ERROR_CODE Binary_search_tree<Entry>::search_and_destroy(Binary_node<Entry>* &sub_root, const Entry &target)
{
    if (sub_root == NULL || sub_root->data == target)
        return remove_root(sub_root);
    else if (target < sub_root->data) 
        return search_and_destroy(sub_root->left, target);
    else
        return search_and_destroy(sub_root->right, target);
}


template <class Entry>
Entry Binary_search_tree<Entry>::Max_value() const {
    return recursive_max(this->root);
}

template <class Entry>
Entry Binary_search_tree<Entry>::recursive_max(Binary_node<Entry>* sub_root) const {
    if (sub_root->right == NULL)
    {
        return sub_root->data;
    }
    else
    {
        recursive_max(sub_root->right);
    }
}