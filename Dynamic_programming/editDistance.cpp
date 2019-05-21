#include <iostream>
#include <algorithm>
using namespace std;

int min(int x, int y, int z)
{
   return min(min(x, y), z);
}

int editDistance_recursive(string str1, string str2, int m, int n)
{
    if (m == 0) return n;
    if (n == 0) return m;

    if (str1[m - 1] == str2[n - 1])
        return editDistance_recursive(str1, str2, m - 1, n - 1);

    return 1 + min(editDistance_recursive(str1, str2, m,     n - 1), // Insert
                   editDistance_recursive(str1, str2, m - 1, n    ), // Remove
                   editDistance_recursive(str1, str2, m - 1, n - 1)  // Replace
                  );
}

int editDistance(string str1, string str2)
{
    int m = str1.length();
    int n = str2.length();

    int L[m+1][n+1];

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0)
                L[i][j] = j;
            else if (j == 0)
                L[i][j] = i;
            else if (str1[i - 1] == str2[j - 1])
                L[i][j] = L[i - 1][j - 1];
            else
                L[i][j] = 1 + min(L[i][j-1], L[i-1][j], L[i-1][j-1]);
        }
    }

    return L[m][n];
}

int main(){
    string str1 = "geek", str2 = "gessek";
    cout << "edit Distance = " << editDistance_recursive(str1, str2, str1.length(), str2.length()) << endl;
    cout << "edit Distance = " << editDistance(str1, str2) << endl;
    return 0;
}
