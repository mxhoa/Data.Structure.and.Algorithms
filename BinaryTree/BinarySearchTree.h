#include "BinaryTree.h"

template <class Entry>
class BinarySearchTree : public Binary_tree<Entry>
{
private:
    /* data */
public:
    /**
     * @brief   Constructor
     *          Empty tree has been created
     */
    BinarySearchTree(/* args */);

    /**
     * @brief   
     * @return          
     */
    ERROR_CODE insert(const Entry &new_data);

    /**
     * @brief   
     * @return          
     */
    ERROR_CODE remove (const Entry &old_data);

    /**
     * @brief   
     * @return          
     */
    ERROR_CODE tree_search(Entry &target) const;

    /**
     * @brief   
     * @return          
     */
    Entry Max_value() const;

protected:
    /**
     * @brief   
     * @return          
     */
  ERROR_CODE remove_root(Binary_node<Entry> *&sub_root);

private:
    /**
     * @brief   
     * @return          
     */
    ERROR_CODE search_and_insert(Binary_node<Entry> *&sub_root, const Entry &new_data);

    /**
     * @brief   
     * @return          
     */
    ERROR_CODE search_and_destroy(Binary_node<Entry> *&sub_root, const Entry &target);

    /**
     * @brief   
     * @return          
     */
    Binary_node<Entry> *search_for_node(Binary_node<Entry> *sub_root, const Entry &target) const;

    /**
     * @brief   
     * @return          
     */
    Entry recursive_max(Binary_node<Entry> *sub_root) const;

    /**
     * @brief   
     * @return          
     */
    ~BinarySearchTree();
};