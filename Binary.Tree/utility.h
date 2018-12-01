#ifndef UTILITY_H
#define UTILITY_H

#include <iostream> // standard iostream operations
#include <limits>   // numeric limits
#include <cmath>    // mathematical functions
#include <cstdlib>  // C-String functions
#include <cstddef>  // C library language support
#include <fstream>  // file input and output
#include <cctype>   // character classification
#include <ctime>    // data and time functions
#include <string>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

enum ERROR_CODE
{
    RES_SUCCESS,
    RES_FAIL,
    RES_RANGE_ERROR,
    RES_UNDERFLOW,
    RES_OVERFLOW,
    RES_FATAL,
    RES_NOT_PRESENT,
    RES_DUPLICATE_ERROR,
    RES_ENTRY_INSERTED,
    RES_ENTRY_FOUND,
    RES_INTERNAL_ERROR
};

#endif // UTILITY_H