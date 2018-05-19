/*************************************************************************************************************************
 * COURSE:   DATA STRUCTURE and ALGORITHM
 *
 * TOPIC:    STACK
 * DESCRIPTION: A stack is a basic data structure that organized items in last-in-first-out (LIFO) manner
 *              Last element inserted in a stack will be the first to be removed from it.
 * CREATED ON : Sat May 19 2018
 *************************************************************************************************************************/

/* ============================================== Header includes ====================================================== */
#include <iostream>
#include "Stack.h"

Stack::Stack() : Stack(MIN_STACK)
{
    std::cout << "Default initial Stack :::: Capacity = " << MIN_STACK << std::endl;
}

Stack::Stack(int nCapacity)
{
    std::cout << "Initial Stack :::: Capacity = " << nCapacity << std::endl;
    capacity = nCapacity;
    entry = new Stack_entry[capacity];
}

Stack::~Stack()
{
    delete[] entry;
}

bool Stack::empty() const
{
    return count > 0 ? false : true;
}

ERROR_CODE Stack::pop()
{
    ERROR_CODE eErr = ERR_NO_ERROR;
    if (count > 0)
        count--;
    else
        eErr = ERR_UNDERFLOW;

    return eErr;
}

ERROR_CODE Stack::top(Stack_entry &item) const
{
    ERROR_CODE eErr = ERR_NO_ERROR;
    if (count > 0)
        item = entry[count - 1];
    else
        eErr = ERR_UNDERFLOW;

    return eErr;
}

ERROR_CODE Stack::push(const Stack_entry &item)
{
    ERROR_CODE eErr = ERR_NO_ERROR;
    if (count < capacity)
        entry[count++] = item;
    else
        eErr = ERR_OVERFLOW;

    return eErr;
}

bool Stack::full() const
{
    return count < capacity ? false : true;
}

int Stack::size() const
{
    return count;
}