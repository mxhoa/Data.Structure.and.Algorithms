/*********************************************************************************
 *                  HASHING WITH SEPARATE CHANING
 * Another method for collision resolution is based on idea of putting the keys
 * that collide in a linked list. This method is called separate chaining. 
 * To speed up search we use Insertion-Sort or keeping the linked list sorted
 *********************************************************************************/
#include <iostream>
#include <vector>

#define PRIME_NUMBER 103

class HashTableSeparateChaining
{
private:
    struct Node
    {
        int value;
        Node *next;
        Node(int v, Node *n);
    };

    int tableSize;
    std::vector<HashTableSeparateChaining::Node*> listArray;

    int ComputeHash(int key);  // division method

public:
    HashTableSeparateChaining();
    virtual void Add(int value);
    virtual bool Remove(int value);
    virtual bool Find(int value);
    virtual void Print();
};

HashTableSeparateChaining::Node::Node(int v, Node *n)
{
    value = v;
    next = n;
}

int HashTableSeparateChaining::ComputeHash(int key) {
    return key % this->tableSize;
}

HashTableSeparateChaining::HashTableSeparateChaining()
{
    tableSize = PRIME_NUMBER;
    listArray = std::vector<Node*>(tableSize);
    for (int i = 0; i < tableSize; i++)
    {
        listArray[i] = nullptr;
    }
}
void HashTableSeparateChaining::Add(int value)
{
    int index = ComputeHash(value);
    listArray[index] = new Node(value, listArray[index]);
}

bool HashTableSeparateChaining::Remove(int value)
{
    int index = ComputeHash(value);
    Node *nextNode, *head = listArray[index];
    Node *delMe;
    if (head != nullptr && head->value == value)
    {
        delMe = head;
        listArray[index] = head->next;
        delete(delMe);
        return true;
    }

    while (head != nullptr)
    {
        nextNode = head->next;
        if (nextNode != nullptr && nextNode->value == value)
        {
            delMe = head->next;
            head->next = nextNode->next;
            delete(delMe);
            return true;
        }
        else
        {
            head = nextNode;
        }
    }
    return false;
}

void HashTableSeparateChaining::Print()
{
    std::cout << "\nValues Stored in Hash-Table using Separate-Chaining";
    std::cout << "\n--TABLE-----------------";
    for (int i = 0; i < tableSize; i++)
    {
        Node *head = listArray[i];
        if (head)
            std::cout << "\nIndex[" << i << "] |HEAD|";
        
        while (head != nullptr)
        {
            std::cout << "-> " << head->value;
            head = head->next;
        }
    }
    std::cout << "\n------------------------\n\n";
}

bool HashTableSeparateChaining::Find(int value)
{
    int index = ComputeHash(value);
    Node *head = listArray[index];
    while (head != nullptr)
    {
        if (head->value == value)
            return true;
        
        head = head->next;
    }
    return false;
}

int main()
{
    HashTableSeparateChaining *ht = new HashTableSeparateChaining();
    ht->Add(15);
    ht->Add(89);
    ht->Add(18);
    ht->Add(18 + PRIME_NUMBER);
    ht->Add(58);
    ht->Add(88);
    ht->Add(18 + 2*PRIME_NUMBER);
    ht->Print();

    std::cout << "Find(18) = " << ht->Find(18) << std::endl;

    std::cout << "Remove 18 in HashTable" << std::endl;
    ht->Remove(18);
    ht->Print();
    std::cout << "Find(18) = " << ht->Find(18) << std::endl;

    return 0;
}