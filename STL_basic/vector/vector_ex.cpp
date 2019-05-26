#include <iostream>
#include <vector>

using namespace std;

#define LINE(msg) cout << "______________________[" << msg << "]______________________\n"

template<typename T>
void vprint(vector<T> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v.at(i) << ' ';
    }

    cout << endl;
}

int main()
{
    LINE("DECLARE");
    vector<int> v1(9,11);
    vector<int> first;
    vector<int> second;
    vector<int> third;

    first.assign(7,100);    // vector has 7 elements with default value is 100

    vector<int>::iterator it = first.begin() + 1;
    second.assign(it, first.end() - 1);

    int myint[] = {1776, 7, 4};
    third.assign(myint, myint + 3); // Assign from array

    cout << "v1(9,11)   => size = " << v1.size() << " :: "; vprint(v1);
    cout << "first      => size = " << first.size() << " :: "; vprint(first);
    cout << "second     => size = " << second.size() << " :: "; vprint(second);
    cout << "third      => size = " << third.size() << " :: "; vprint(third);


    LINE("ADD ELEMENT"); 

    vector<int> myvector(10, 0);
    cout << "original           => size = " << myvector.size() << " :: "; vprint(myvector);
    
    myvector.push_back(30);
    cout << "push_back(30)      => size = " << myvector.size() << " :: "; vprint(myvector);
    
    myvector.insert(myvector.begin() + 1, 20);
    cout << "insert(i1,20)      => size = " << myvector.size() << " :: "; vprint(myvector);
    
    myvector.emplace(myvector.end(), 44);
    cout << "emplace(end,44)    => size = " << myvector.size() << " :: "; vprint(myvector);
    
    myvector.emplace_back(11);
    cout << "emplace_back(11)   => size = " << myvector.size() << " :: "; vprint(myvector);

    return 0;    
}
