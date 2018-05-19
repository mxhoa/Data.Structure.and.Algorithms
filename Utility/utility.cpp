#include "utility.h"

bool user_say_yes()
{
    int c;
    bool initial_response = true;

    do {
        if (initial_response)
            std::cout << "(Y.N)?" << std::flush;
        else
            std::cout << "Respond with either Y or N: " << std::flush;

        do {
            c = std::cin.get();
        } while(c == '\n' || c == ' ' || c == '\t');

        initial_response = false;
    } while(c != 'y' && c != 'Y' && c != 'n' && c != 'N');

    return (c == 'y' || c == 'Y');
}