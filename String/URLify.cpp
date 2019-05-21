#include <iostream>
#include <string>
using namespace std;

/**
 * @brief   URLify   
 *          Write a method to replace all spaces in a string with '%20'. You may assume that the string
 *          has sufficient space at the end to hold the additional characters, and that you are given the "true"
 *          length of the string. (Note: if implementing in Java, please use a character array so that you can
 *          perform this operation in place.) 
 *          
 *          EXAMPLE
 *              Input: "Mr John Smith ", 13
 *              Output: "Mr%20John%20Smith"
 *
 * @param[io]  str         The string
 * @param[in]  trueLength  The true length
 */

void URLify(string &str, int trueLength)
{
    int cntSpace = 0;
    
    for (int i = 0; i < trueLength; i++)
    {
        if (str[i] == ' ')
            cntSpace++;
    }
    
    int index = trueLength + cntSpace * 2;
    cout << "New Length = " << index << endl;
    str[index] = '\0';
    
    for (int i = trueLength - 1; i >= 0; i--)
    {
        if (str[i] != ' ')
        {
            str[index - 1] = str[i];
            index--;
        }
        else
        {
            str[index - 1] = '0';
            str[index - 2] = '2';
            str[index - 3] = '%';
            index -= 3;
        }
    }
}

int main(){
    cout << "Hello, World!" << endl;
    string str = "Mr John Smith       ";
    int trueLength = 13;
    
    URLify(str, trueLength);
    
    cout << "str = " << str << endl;
    return 0;
}
