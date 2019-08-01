#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


void reverseWords(string &s)
{
    int index = 0;

    reverse(s.begin(), s.end());

	for (int i = 0; i < (int)s.length(); i++)
	{
		if (s[i] != ' ')
		{
			int j = i;
            if (index != 0)
			    s[index++] = ' ';
			while (s[j] != ' ' && j < (int)s.length())
			{
				s[index++] = s[j++];
			}

			reverse(s.begin() + index - (j - i), s.begin() + index);

			i = j;
		}
	}

	s.erase(s.begin() + index, s.end());
}


int main(){
    string s1 = "Good for you     ";
    string s2 = "   Hello every body";
    string s3 = "   How are   youu today!        ";

    cout << "____" <<s1 << "____" << endl;
    cout << "____" <<s2 << "____" << endl;
    cout << "____" <<s3 << "____" << endl;

    reverseWords(s1);
    reverseWords(s2);
    reverseWords(s3);

    cout << "RESULT AFTER REVERSE WORDS IN STRING" << endl;
    cout << "____" <<s1 << "____" << endl;
    cout << "____" <<s2 << "____" << endl;
    cout << "____" <<s3 << "____" << endl;

    return 0;
}
