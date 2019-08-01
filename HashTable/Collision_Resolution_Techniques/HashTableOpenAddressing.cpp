/**************************************************************************************************
 *              HASHING WITH OPEN ADDRESSING
 * When using linear open addressing, the Hash-Table is represented by a one-dimensional array
 * with indices that range from 0 to the desired table size-1
 * 
 * One method of resolving collision is the look into a Hash-Table and find another free slot
 * the hold the object that have caused the collion. A simple way is to move from one slot to
 * another in some sequential order until we find a free space. This collision resolution process
 * is called Open Addressing
 * 
 * ************************************************************************************************/
#include <iostream>
#include <vector>

class HashTableOpenAddressing
{
private:
    const int EMPTY_NODE    =   0;
    const int LAZY_DELETED  =   1;
    const int FILLED_NODE   =   2;

private:
    int tableSize = 0;
    std::vector<int> Arr;
    std::vector<int> Flag;

private:
    virtual int ComputeHash(int key);
    virtual int ResolverFun(int index);

public:
    HashTableOpenAddressing(int tSize);
    virtual bool Add(int value);
    virtual bool Find(int value);
    virtual bool Remove(int value);
    virtual void Print();
};

HashTableOpenAddressing::HashTableOpenAddressing(int tSize)
{
    tableSize = tSize;
    Arr.assign(tableSize, 0);
    Flag.assign(tableSize, EMPTY_NODE);
}

int HashTableOpenAddressing::ComputeHash(int key)
{
    return key % tableSize;
}

int HashTableOpenAddressing::ResolverFun(int index)
{
    return index;
}

bool HashTableOpenAddressing::Add(int value)
{
    int hashValue = ComputeHash(value);
    for (int i = 0; i < tableSize; i++)
    {
        if (Flag[hashValue] == EMPTY_NODE || Flag[hashValue] == LAZY_DELETED)
        {
            Arr[hashValue] = value;
            Flag[hashValue] = FILLED_NODE;
            return true;
        }
        hashValue += ResolverFun(i);
        hashValue %= tableSize;
    }
    return false;
}

bool HashTableOpenAddressing::Find(int value)
{
    int hashValue = ComputeHash(value);
    for (int i = 0; i < tableSize; i++)
    {
        if (Flag[hashValue] == EMPTY_NODE)
            return false;

        if (Flag[hashValue] == FILLED_NODE && Arr[hashValue] == value)
            return true;
        
        hashValue += ResolverFun(i);
        hashValue %= tableSize;
    }
    return false;
}

bool HashTableOpenAddressing::Remove(int value)
{
    int hashValue = ComputeHash(value);
    for (int i = 0; i < tableSize; i++)
    {
        if (Flag[hashValue] == EMPTY_NODE)
            return false;
        
        if (Flag[hashValue] == FILLED_NODE && Arr[hashValue] == value)
        {
            Flag[hashValue] = LAZY_DELETED;
            return true;
        }
        hashValue += ResolverFun(i);
        hashValue %= tableSize;
    }
    return false;
}

void HashTableOpenAddressing::Print()
{
    std::cout << "\nValues Stored in Hash-Table using Open-Addressing";
    std::cout << "\n--TABLE-----------------\n";
    for (int i = 0; i < tableSize; i++)
    {
        if (Flag[i] == FILLED_NODE)
            std::cout << "Index[" << i << "] = " << Arr[i] << std::endl;
    }
    std::cout << "------------------------\n\n";
}

int main()
{
    HashTableOpenAddressing *ht = new HashTableOpenAddressing(1000);

    ht->Add(89); ht->Add(18); ht->Add(49); ht->Add(58); ht->Add(69);
    ht->Add(89); ht->Add(18); ht->Add(49); ht->Add(58); ht->Add(69);
    ht->Print();

    std::cout << "\n#### Remove 89, 18, 49, 58, 69" << std::endl;
    ht->Remove(89); ht->Remove(18); ht->Remove(49); ht->Remove(58); ht->Remove(69);
    ht->Print();

    return 0;
}