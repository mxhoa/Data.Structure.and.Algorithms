#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

void map_example()
{
    cout << "########## MAP EXAMPLE ##########" << endl;
    // Empty map container
    map<int, int> mp1;

    // Insert elements in random order
    mp1.insert(pair<int,int>(2,30));
    mp1.insert(pair<int,int>(1,40));
    mp1.insert(pair<int,int>(3,60));
    mp1.insert(pair<int,int>(6,50));
    mp1.insert(pair<int,int>(4,20));
    mp1.insert(pair<int,int>(7,10));
    mp1.insert(pair<int,int>(5,50));

    // Print map 
    map<int,int>::iterator it;
    cout << "+++++ MAP : ORIGIN 1 +++++ " << endl;
    for (it = mp1.begin(); it != mp1.end(); it++)
    {
        cout << "\t\t[" << it->first << "|"
            <<  it->second << "]" << endl;
    }

    /* Create another map (mp2), and assign by mp1 */
    map<int,int> mp2(mp1.begin(), mp1.end());
    cout << "+++++ MAP : ORIGIN 2 +++++ " << endl;
    for (it = mp2.begin(); it != mp2.end(); it++)
    {
        cout << "\t\t[" << it->first << "|"
             << it->second << "]" << endl;
    }

    /* Remove all elements up to element with key = 3 in mp2 */
    cout << "\nREMOVE All Elements UP TO Element with KEY=3" << endl;
    mp2.erase(mp2.begin(), mp2.find(3));
    cout << "+++++ MAP : CHANGE 2 +++++ " << endl;
    for (it = mp2.begin(); it != mp2.end(); it++)
    {
        cout << "\t\t[" << it->first << "|"
             << it->second << "]" << endl;
    }

    cout << "\nREMOVE All Elements with KEY=4" << endl;
    cout << "ERASE: mp2.erase(4) = " << mp2.erase(4) << endl;
    cout << "ERASE: mp2.erase(9) = " << mp2.erase(9) << endl;
    cout << "+++++ MAP : CHANGE 2 +++++ " << endl;
    for (it = mp2.begin(); it != mp2.end(); it++)
    {
        cout << "\t\t[" << it->first << "|"
             << it->second << "]" << endl;
    }
}

void multimap_example()
{
    cout << "########## MULTIMAP EXAMPLE ##########" << endl;
    multimap<int,int> mmp1;

    // insert elements in random order
    mmp1.insert(pair<int, int>(1, 40));
    mmp1.insert(pair<int, int>(2, 30));
    mmp1.insert(pair<int, int>(4, 20));
    mmp1.insert(pair<int, int>(3, 60));
    mmp1.insert(pair<int, int>(6, 50));
    mmp1.insert(pair<int, int>(5, 50));
    mmp1.insert(pair<int, int>(6, 10));

    multimap<int,int>::iterator it;
    cout << "+++++ MAP : ORIGIN 1 +++++ " << endl;
    for (it = mmp1.begin(); it != mmp1.end(); it++)
    {
        cout << "\t\t[" << it->first << "|"
             << it->second << "]" << endl;
    }
    cout << endl;

    // Remove
    cout << "ERASE: after removal of elements less than KEY=3" << endl;
    mmp1.erase(mmp1.begin(), mmp1.find(3));
    cout << "+++++ MAP : CHANGE  +++++ " << endl;
    for (it = mmp1.begin(); it != mmp1.end(); it++)
    {
        cout << "\t\t[" << it->first << "|"
             << it->second << "]" << endl;
    }
    cout << endl;

    cout << "COUNT: mmp1.count(6) = "<< mmp1.count(6) << endl;

    cout << "ERASE: Remove All Elements with KEY=6" << endl;
    mmp1.erase(mmp1.find(6));
    cout << "+++++ MAP : CHANGE  +++++ " << endl;
    for (it = mmp1.begin(); it != mmp1.end(); it++)
    {
        cout << "\t\t[" << it->first << "|"
             << it->second << "]" << endl;
    }
    cout << endl;
}

void unordered_map_example()
{
    cout << "########## UNORDERED_MAP EXAMPLE ##########" << endl;
    unordered_map<int, int> ump;

    // insert elements in random order
    ump.insert(pair<int, int>(7, 10));
    ump.insert(pair<int, int>(4, 20));
    ump.insert(pair<int, int>(1, 40));
    ump.insert(pair<int, int>(6, 50));
    ump.insert(pair<int, int>(2, 30));
    ump.insert(pair<int, int>(3, 60));
    ump.insert(pair<int, int>(5, 50));

    unordered_map<int, int>::iterator it;
    cout << "+++++ UNORDERED_MAP : ORIGIN 1 +++++ " << endl;
    for (it = ump.begin(); it != ump.end(); it++)
    {
        cout << "\t\t[" << it->first << "|"
             << it->second << "]" << endl;
    }
    cout << endl;

    
    cout << "SIZE: ump.size() = " << ump.size() << endl;
    cout << "COUNT: (size_t) ump.count(6) = " << (size_t) ump.count(6) << endl;

    cout << "ERASE: Remove All Elements with KEY=6" << endl;
    ump.erase(ump.find(6));
    cout << "+++++ UNORDERED_MAP : CHANGE  +++++ " << endl;
    for (it = ump.begin(); it != ump.end(); it++)
    {
        cout << "\t\t[" << it->first << "|"
             << it->second << "]" << endl;
    }
    cout << endl;
}
int main()
{
    // map_example();
    // multimap_example();
    unordered_map_example();

    return 0;
}