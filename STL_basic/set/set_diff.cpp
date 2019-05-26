#include <iostream>
#include <set>
#include <unordered_set>

using namespace std;

void  set_example()
{
    cout << "########## SET EXAMPLE #############" << endl;
    set<int> s;

    // Elements added to set
    s.insert(12);   // 12
    s.insert(10);   // 10 12
    s.insert(2);    // 2 10 12
    s.insert(10);   // Duplicate added  => 2 10 12
    s.insert(90);   // 2 10 12 90
    s.insert(85);   // 2 10 12 85 90
    s.insert(45);   // 2 10 12 45 85 90

    // Iterator declared to traverse set elements
    set<int>::iterator it, it1, it2;
    cout << "Set elements after sort and removing duplicates" << endl;
    cout << "+++++ SET: ORIGIN: ";
    for(it = s.begin(); it != s.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;

    cout << "COUNT: s.count(10) = " << s.count(10) << endl;
    cout << "COUNT: s.count(1) = " << s.count(1) << endl;

    // Find elements
    it1 = s.find(10);
    cout << "FIND: s.find(10) = " << *it1 << endl;
    it2 = s.find(90);
    cout << "FIND: s.find(90) = " << *it2 << endl;
    cout << "FIND: s.find(40) = " << *s.find(40) << endl;
    cout << "FIND: s.end() = " << *s.end() << endl;

    // Elements from 10 to elements before 90 erased
    s.erase(it1, it2);
    cout << "Erase elements from 10 to elements before 90" << endl;
    cout << "+++++ SET: CHANGE: ";
    for (it = s.begin(); it != s.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
}


void multiset_example()
{
    cout << "########## MULTISET EXAMPLE #############" << endl;
    multiset<int> s;

    // Elements added to set
    s.insert(12);
    s.insert(10);
    s.insert(2);
    s.insert(10); // duplicate added
    s.insert(90);
    s.insert(85);
    s.insert(45);

    

    // Iterator declared to traverse set elements
    multiset<int>::iterator it, it1, it2;
    cout << "Multiset elements after sort" << endl;
    cout << "+++++ MULTISET: ORIGIN: ";
    for (it = s.begin(); it != s.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;

    cout << "COUNT: s.count(10) = " << s.count(10) << endl;
    cout << "COUNT: s.count(1)  = " << s.count(1) << endl;
    // Find elements
    it1 = s.find(10);
    it2 = s.find(90);

    cout << "FIND: s.find(10) = " << *it1 << endl;
    cout << "FIND: s.find(90) = " << *it2 << endl;

    // Element form 10 to elements before 90 erased
    cout << "ERASE elements From 10 to BEFORE 90" << endl;
    s.erase(it1, it2);

    cout << "Multiset Elements after erase" << endl;
    cout << "+++++ MULTISET: CHANGE: ";
    for (it = s.begin(); it != s.end(); it++)
    {
        cout << *it << ' ';
    }

    cout << endl;
}

void unordered_set_example()
{
    cout << "########## UNORDERED_SET EXAMPLE #############" << endl;
    // Require #include <unordered_set>
    unordered_set<int> s;

    // Elements added to set
    s.insert(12);
    s.insert(10);
    s.insert(2);
    s.insert(10);   // duplicate added
    s.insert(90);
    s.insert(85);
    s.insert(45);
    s.insert(12);
    s.insert(70);

    // Iterator declared to traverse set elements
    unordered_set<int>::iterator it, it1, it2;
    cout << "Unordered_set elements after added" << endl;
    cout << "+++++ UNORDERED_SET: ORIGIN: ";
    for (it = s.begin(); it != s.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;


    cout << "COUNT: s.count(10) = " << s.count(10) << endl;
    cout << "COUNT: s.count(1)  = " << s.count(1) << endl;

    it1 = s.find(10);
    it2 = s.find(90);
    cout << "FIND: s.find(10) = " << *it1 << endl;
    cout << "FIND: s.find(90) = " << *it2 << endl;

    // element 10 will be ERASE
    cout << "ERASE: s.erase([" << *it1 << "]) " << endl;
    s.erase(it1);
    cout << "+++++ UNORDERED_SET: CHANGE: ";
    for (it = s.begin(); it != s.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
}

void unordered_multiset_example()
{
    cout << "########## UNORDERED_SET EXAMPLE #############" << endl;

    unordered_multiset<int> s;

    // Elements added to set
    s.insert(12);
    s.insert(10);
    s.insert(2);
    s.insert(10); // duplicate added
    s.insert(90);
    s.insert(85);
    s.insert(45);

    // Iterator declared to traverse
    // set elements
    unordered_multiset<int>::iterator it, it1;
    cout << "+++++ UNORDERED_MULTISET: ORIGIN: ";
    for (it = s.begin(); it != s.end(); it++)
        cout << *it << ' ';
    cout << endl;

    cout << "COUNT: s.count(10) = " << s.count(10) << endl;
    cout << "COUNT: s.count(1)  = " << s.count(1) << endl;

    it1 = s.find(10);
    cout << "FIND: s.find(10) = " << *it1 << endl;

    cout << "ERASE: s.erase([" << *it1 << "])" << endl;
    s.erase(it1);
    
    cout << "+++++ UNORDERED_MULTISET: CHANGE: ";
    for (it = s.begin(); it != s.end(); it++)
    {   
        cout << *it << ' ';
    }
    cout << endl;
}
int main()
{
    set_example();
    multiset_example();
    unordered_set_example();
    unordered_multiset_example();
    return 0;
}