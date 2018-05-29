#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>     // standard iostream operations
#include <limits>       // numeric limits
#include <cmath>        // mathematical functions
#include <cstdlib>      // C-String functions
#include <cstddef>      // C library language support
#include <fstream>      // file input and output
#include <cctype>       // character classification
#include <ctime>        // data and time functions
#include <string>
#include <vector>
#include <iomanip>

bool user_says_yes();

enum ERROR_CODE {
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


std::ostream& operator << (std::ostream &stream, ERROR_CODE eErr)
{
    std::string error;
    
    switch (eErr)
    {
        case RES_SUCCESS:
            error = "RES_SUCCESS";
            break;
        case RES_FAIL:
            error = "RES_FAIL";
            break;
        case RES_RANGE_ERROR:
            error = "RES_RANGE_ERROR";
            break;
        case RES_UNDERFLOW:
            error = "RES_UNDERFLOW";
            break;
        case RES_OVERFLOW:
            error = "RES_OVERFLOW";
            break;
        case RES_FATAL:
            error = "RES_FATAL";
            break;
        case RES_NOT_PRESENT:
            error = "RES_NOT_PRESENT";
            break;
        case RES_DUPLICATE_ERROR:
            error = "RES_DUPLICATE_ERROR";
            break;
        case RES_ENTRY_INSERTED:
            error = "RES_ENTRY_INSERTED";
            break;
        case RES_ENTRY_FOUND:
            error = "RES_ENTRY_FOUND";
            break;
        case RES_INTERNAL_ERROR:
            error = "RES_INTERNAL_ERROR";
            break;
        default:
            error = "UNKNOWN";
            break;
    }

    stream << error;
    return stream;
}