#include <iostream>
#include <vector>
#include <functional>

/****************************************************** DAY 05 *****************************************************
 * This problem was asked by Jane Street.
 * 
 * cons(a, b) constructs a pair, and car(pair) and cdr(pair) returns the first and last element of that pair. 
 * For example, car(cons(3, 4)) returns 3, and cdr(cons(3, 4)) returns 4.
 * 
 * Given this implementation of cons:
 * 
 * 		def cons(a, b):
 * 		    def pair(f):
 * 		        return f(a, b)
 * 		    return pair
 * 		    
 * Implement car and cdr.
 *******************************************************************************************************************/

std::function<int(int (*f)(int, int))> cons(int a, int b)
{
    auto pair = [a, b](int (*f)(int, int)) -> int {
        return (*f)(a, b);
    };
    return pair;
}

int car(std::function<int(int (*f)(int, int))> cons)
{
    auto get_a = [](int a, int b) -> int {
        return a;
    };
    return cons(*get_a);
}

int cdr(std::function<int(int (*f)(int, int))> cons)
{
    auto get_b = [](int a, int b) -> int {
        return b;
    };
    return cons(*get_b);
}

int main()
{
    std::function<int(int (*f)(int, int))> cons_v = cons(1, 2);
    int a = car(cons_v);
    int b = cdr(cons_v);

    std::cout << "The value of a is: " << a << "\n";
    std::cout << "The value of b is: " << b << "\n";

    return 0;
}