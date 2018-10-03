#include <iostream>
#include <string>
using namespace std;

/* 
 * Implement a method to perform basic string compression using the counts of repeated characters.
 * Example:
 *          aabccccaaa ----> a2b1c4a3
 */
string compress(string str)
{
    string res;
    int count = 0;
    int curIndex = 0;
    for (int i = 0; i < (int)str.length(); i++)
    {
        if (str[i] == ' ')
            continue;

        if (res.empty())
            res += str[i];
        
        if (res[curIndex] == str[i])
        {
            count++;
        }
        else
        {
            res += to_string(count);
            curIndex += count/10 + 2;
            res += str[i];
            count = 1;
        }
    }
    res += to_string(count);
    
    return res;
}

/*
 * Implement a method to perfom string decompression 
 * Example:
 *          a3b2c1d3 ----> aaabbcddd
 */
string subDecompress(string sub) {
    string res;
    res += sub[0];
    int num = stoi(sub.substr(1, sub.length() - 1)) - 1;
    
    for (int i = 0; i < num; i++)
        res += sub[0];
    return res;
}

string decompress(string str)
{
    int index = 0;
    string res;
    
    for (int i = 0; i < (int)str.length(); i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            if (i == index) continue;
            
            res += subDecompress(str.substr(index, i - index));
            
            index  = i;
            
        }
        
    }
    res += subDecompress(str.substr(index, str.length() - index));
    return res;
}


int main(){
    string str1 = "aaaabbbbbccccccccccdddfhh";
    cout << str1 << endl;
    cout << "Compression    " << "= " << compress(str1) << endl;
    cout << "Decompression  " << "= " << decompress(compress(str1)) << endl;
    return 0;
}
