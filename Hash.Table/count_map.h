/***************************************************************************************************
 *              COUNT MAP
 * Below is CountMap<T> implementation over C++ collection HashMap<T>, this interface is important
 * if you have repeted values can come and you want to keep track of there count.
 * CountMap<T> is our implementation that we will use to solve many problems.
 * *************************************************************************************************/
#ifndef __COUNT_MAP__
#define __COUNT_MAP__

#include <iostream>
#include <unordered_map>

template <typename T>

class CountMap
{
  public:
    std::unordered_map<T, int> hm;
    virtual void add(T key)
    {
        if (hm.find(key) != hm.end())
            hm[key] = hm[key] + 1;
        else
            hm[key] = 1;
    }

    virtual void remove(T key)
    {
        if (hm.find(key) != hm.end())
        {
            if (hm[key] == 1)
                hm.erase(key);
            else
                hm[key] = hm[key] - 1;
        }
    }

    virtual int get(T key)
    {
        if (hm.find(key) != hm.end())
            return hm[key];
        return 0;
    }

    virtual bool containsKey(T key)
    {
        return hm.find(key) != hm.end();
    }

    virtual int size()
    {
        return hm.size();
    }
};

#endif 