/************************************************************************************************************************* 
 * COURSE:
 *
 * TOPIC:
 * DESCRIPTION: 
 * CREATED ON : Sat May 19 2018
 *************************************************************************************************************************/

/* ============================================== Header includes ====================================================== */
#include "Binary_node.h"
#include <iostream>

template <class Entry>
Binary_node<Entry>::Binary_node()
{
	this->left = NULL;
    this->right = NULL;
}

template <class Entry>
Binary_node<Entry>::Binary_node(const Entry &x)
{
    this->data = x;
    this->left = NULL;
    this->right = NULL;
}

template <class Entry>
Binary_node<Entry>::~Binary_node()
{
    this->data = NULL;
    this->left = NULL;
    this->right = NULL;
}

template <class Entry>
std::ostream& operator <<(std::ostream &stream, const Binary_node<Entry> &x)
{
    stream << x.data << std::endl;
    return stream;
}