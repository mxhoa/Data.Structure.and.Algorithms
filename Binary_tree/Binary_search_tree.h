/************************************************************************************************************************* 
 * COURSE:  DATA STRUCTURE and ALGORITHMS
 *
 * TOPIC:   BINARY SEARCH TREE
 * DESCRIPTION: A BINARY SEARCH TREE is a binary tree that is either empty or in which every
 *              node has a key (within its data entry) and satifies the following conditions:
 *              1. The key of the root (if it exists) is greater than the key in any node in
 *                  the left subtree of the root
 *              2. The key of the root (if it exists) is less than the key in any node in 
 *                  the right subtree of the root
 *              3. The left and right subtrees of the root are again binary search trees.
 * CREATED ON : Mon May 28 2018
 *************************************************************************************************************************/
#include "Binary_tree.h"

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H


template <class Entry>
class Binary_search_tree : public Binary_tree<Entry>
{
public:
    /**
     * @brief   Constructor
     *          Empty tree has been created
     */
    Binary_search_tree();

    /**
     * @brief   If an entry with a key matching that of new_data already belongs to the Search_tree,
     *          a code of RES_DUPLICATE_ERROR is returned. Otherwise, the entry new_data is inserted
     *          into the tree in such a way that the properties of a binary search tree are preserved
     *          and a code of success is returned.
     * 
     * @Use     Recursive function search_and_insert
     */
    ERROR_CODE insert(const Entry &new_data);

    /**
     * @brief   If an Entry with a key matching that of target belongs to the Search_tree, a code of 
     *          success is returned and the corresponding node is removed from the tree. Otherwise, 
     *          a code of not_present is returned
     * 
     * @use     recursive function search_and_destroy
     */
    ERROR_CODE remove(const Entry &old_data);

    /**
     * @brief   If there is an entry in the tree whose key matches that in target, 
     *          the parameter target is replaced by the corresponding entry from the
     *          tree and a code of success is returned. Otherwise a code of not_present
     *          is returned.
     * @use     function search_for_node
     */
    ERROR_CODE tree_search(Entry &target) const;

    /**
     * @brief   The maximum value stored in the BST has been returned.
     * @use     function recursive_max
     */
    Entry Max_value() const;

  protected:
    /**
     * @brief   sub_root is either NULL or points to a subtree of the Seach_tree
     *          If sub_root is NULL, a code of not_present is returned. Otherwise,
     *          the root of the subtree is removed in such a way that the properties
     *          of a binary search tree are preserved.
     *          The parameter sub_root is reset as the root of the modified subtree,
     *          ans success is returned.
     */
    ERROR_CODE remove_root(Binary_node<Entry> *&sub_root);

private:
    /**
     * @brief   sub_root is either NULL or points to a subtree of a Search_tree
     *          If the key of target is not in the subtree, it is inserted in the 
     *          proper spot and a value of sucess is returned.
     *          Otherwise, the key is already in the tree and a value of duplicate_error
     *          is returned     
     */
    ERROR_CODE search_and_insert(Binary_node<Entry> *&sub_root, const Entry &new_data);

    /**
     * @brief   sub_root is either NULL or points to a subtree of the Search_tree. 
     *          If the key of target is not in tree, a code of not_present is returned.
     *          Otherwise, a code of success is returned and the subtree node containing
     *          target has been removed in such a way that the properties of binary search
     *          tree have been preserved.
     */
    ERROR_CODE search_and_destroy(Binary_node<Entry> *&sub_root, const Entry &target);

    /**
     * @brief   sub_root is either NULL or points to a subtree of a Search_tree
     *          If the key of target is not in the subtree, a result of NULL is returned
     *          Otherwise, a pointer to the subtree node containing target is returned.
     * @return          
     */
    Binary_node<Entry> *search_for_node(Binary_node<Entry> *sub_root, const Entry &target) const;

    /**
     * @brief   sub_root is NULL or points to a subtree
     * @return  returns the maximum valued node in the subtree
     */
    Entry recursive_max(Binary_node<Entry> *sub_root) const;
};
#endif

/* ============================================== Declaration ========================================================== */
template <class Entry>
Binary_search_tree<Entry>::Binary_search_tree() : Binary_tree<Entry>()
{
    std::cout << "Binary Search Tree Contructor\n";
}

/* ============================================== Declaration ========================================================== */
template <class Entry>
ERROR_CODE Binary_search_tree<Entry>::remove(const Entry &old_data)
{
    return search_and_destroy(this->root, old_data);
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
        while (to_delete->right != NULL)
        {
            parent = to_delete;
            to_delete = to_delete->right;
        }
        sub_root->data = to_delete->data; // Move from to_delete to root.
        if (parent == sub_root)
            sub_root->left = to_delete->left;
        else
            parent->right = to_delete->left;
    }
    delete to_delete;

    return RES_SUCCESS;
}

template <class Entry>
ERROR_CODE Binary_search_tree<Entry>::search_and_destroy(Binary_node<Entry> *&sub_root, const Entry &target)
{
    if (sub_root == NULL || sub_root->data == target)
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
    ERROR_CODE ret = RES_SUCCESS;
    Binary_node<Entry> *found = search_for_node(this->root, target);

    if (found == NULL)
    {
        ret = RES_NOT_PRESENT;
    }
    else
    {
        target = found->data;
    }

    return ret;
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
    return search_and_insert(this->root, new_data);
}

template <class Entry>
ERROR_CODE Binary_search_tree<Entry>::search_and_insert(Binary_node<Entry> *&sub_root, const Entry &new_data)
{
    if (sub_root == NULL)
    {
        sub_root = new Binary_node<Entry>(new_data);
        return RES_SUCCESS;
    }
    else if (sub_root->data > new_data)
        return search_and_insert(sub_root->left, new_data);
    else if (sub_root->data < new_data)
        return search_and_insert(sub_root->right, new_data);
    else
        return RES_DUPLICATE_ERROR;
}

template <class Entry>
Entry Binary_search_tree<Entry>::Max_value() const
{
    return recursive_max(this->root);
}

template <class Entry>
Entry Binary_search_tree<Entry>::recursive_max(Binary_node<Entry> *sub_root) const
{
    if (sub_root->right == NULL)
    {
        return sub_root->data;
    }
    else
    {
        recursive_max(sub_root->right);
    }
}