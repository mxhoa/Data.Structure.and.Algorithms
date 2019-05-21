/**
 * @brief Evaluate an expression represented by a String.
 *
 *  Test Cases:
 *    "10 + 2 * 6"            ---> 22
 *    "100 * 2 + 12"          ---> 212
 *    "100 * ( 2 + 12 )"      ---> 1400
 *    "100 * ( 2 + 12 ) / 14" ---> 100 
 * 
 * @file expressionEvaluation.cpp
 * @author mxhoa
 * @date 2018-06-18
 */
#include <iostream>
#include <string>
#include <stack>
#include <vector>


using namespace std;

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

void lowest(int &den3, int &num3)
{
    int common_factor = gcd(num3, den3);

    den3 = den3 / common_factor;
    num3 = num3 / common_factor;
}

void addFraction(int num1, int den1, int num2,
                 int den2, int &num3, int &den3)
{
    den3 = gcd(den1, den2);
    den3 = (den1 * den2) / den3;
    num3 = (num1) * (den3 / den1) + (num2) * (den3 / den2);

    lowest(den3, num3);
}

vector<string> reducedFractionSums(vector<string> expressions)
{
    vector<string> results;

    for (int i = 0; i < expressions.size(); i++)
    {
        stack<int> values;
        string tokens = expressions[i];

        for (int j = 0; j < tokens.length(); j++)
        {
            if (tokens[j] >= '0' && tokens[j] <= '9')
            {
                string num("");
                while(j < tokens.length() && tokens[i] >= '0' && tokens[j] <= '9')
                    num += tokens[j++];
                    
                values.push(stoi(num));
            }
        }

        int den2 = values.top(); values.pop();
        int num2 = values.top(); values.pop();
        int den1 = values.top(); values.pop();
        int num1 = values.top(); values.pop();

        int num, den;
        addFraction(num1, den1, num2, den2, num, den);
        string res = to_string(num) + "/" + to_string(den);
        results.push_back(res);
    }    

    return results;
}
int main()
{
    vector<string> str = {"722/148+360/176", "978/1212+183/183"};
    vector<string> results;
    results = reducedFractionSums(str);
    cout << results.size() << endl;
    return 0;
}
