/*********************************************************************************
 *                  HASHING WITH SEPARATE CHANING
 * Another method for collision resolution is based on idea of putting the keys
 * that collide in a linked list. This method is called separate chaining. 
 * To speed up search we use Insertion-Sort or keeping the linked list sorted
 *********************************************************************************/
#include <iostream>
#include <vector>

#define PRIME_NUMBER 103

class HashTableSC
{
private:
    struct Node
    {
        int value;
        Node *next;
        Node(int v, Node *n);
    };

    int tableSize;
    std::vector<Node*> listArray;

    int ComputeHash(int key);  // division method

public:
    HashTableSC();
    virtual void Add(int value);
    virtual bool Remove(int value);
    virtual bool Find(int value);
    virtual void Print();
};

HashTableSC::Node::Node(int v, Node *n)
{
    value = v;
    next = n;
}

HashTableSC::HashTableSC()
{
    tableSize = PRIME_NUMBER;
    listArray = std::vector<Node*>(tableSize);
    for (int i = 0; i < tableSize; i++)
    {
        listArray[i] = nullptr;
    }
}
void HashTableSC::Add(int value)
{
    int index = ComputeHash(value);
    listArray[index] = new Node(value, listArray[index]);
}

bool HashTableSC::Remove(int value)
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

void HashTableSC::Print()
{
    for (int i = 0; i < tableSize; i++)
    {
        Node *head = listArray[i];
        if (head)
            std::cout << "Index :: " << i << "Value :: " << std::endl;
        
        while (head != nullptr)
        {
            std::cout << head->value << std::endl;
            head = head->next;
        }
    }
}

bool HashTableSC::Find(int value)
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