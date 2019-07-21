#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    int val;
    Node *next;

public:
    Node(int data)
    {
        this->val = data;
        this->next = nullptr;
    }
};

void printList(Node *head)
{
    if (!head)
        return;

    Node *curr = head;
    while (curr)
    {
        cout << "->" << curr->val;
        curr = curr->next;
    }
    cout << endl;
}

Node *split(Node *head, int size)
{
    if (!head || !head->next)
        return nullptr;
    while (--size && head)
    {
        head = head->next;
    }
    if (!head)
        return nullptr;

    Node *second = head->next;
    head->next = nullptr;
    return second;
}

Node *merge(Node *l1, Node *l2, Node *tail)
{
    Node *head = tail;
    while (l1 && l2)
    {
        if (l1->val <= l2->val)
        {
            head->next = l1;
            l1 = l1->next;
        }
        else
        {
            head->next = l2;
            l2 = l2->next;
        }
        head = head->next;
    }
    head->next = l1 ? l1 : l2;
    while (head->next)
        head = head->next;
    return head;
}

Node *sortList(Node *head)
{
    if (!head || !head->next)
        return head;

    Node *curr = head;
    int len = 0;
    while (curr)
    {
        len++;
        curr = curr->next;
    }

    Node dummy(0);
    Node *left, *right, *tail;
    tail = &dummy;
    dummy.next = head;

    printList(head);
    for (int step = 1; step < len; step <<= 1)
    {
        curr = dummy.next;
        tail = &dummy;
        while (curr)
        {
            left = curr;
            right = split(left, step);
            curr = split(right, step);
            tail = merge(left, right, tail);
        }
    }
    // curr = dummy.next;
    return dummy.next;
}

Node *mergeList(Node *l1, Node *l2)
{
    Node *l = new Node(0);
    Node *curr = l;
    cout << "mergeList" << endl;

    while (l1 || l2)
    {
        if (l1->val <= l2->val)
        {
            curr->next = l1;
            l1 = l1->next;
        }
        else
        {
            curr->next = l2;
            l2 = l2->next;
        }
        cout << "In while :: " << curr->val << endl;
        curr = curr->next;
    }
    if (l1)
        curr->next = l1;
    if (l2)
        curr->next = l2;
    return l->next;
}

int main()
{
    // Node *head;
    // head = new Node(2);
    // head->next = new Node(9);
    // head->next->next = new Node(4);
    // head->next->next->next = new Node(3);
    // head->next->next->next->next = new Node(7);
    // head->next->next->next->next->next = new Node(8);
    // head->next->next->next->next->next->next = new Node(1);
    // head->next->next->next->next->next->next->next = new Node(13);
    // head->next->next->next->next->next->next->next->next = new Node(6);
    // head->next->next->next->next->next->next->next->next->next = new Node(4);
    // head->next->next->next->next->next->next->next->next->next->next = new Node(5);

    // printList(head);
    // Node *sort = sortList(head);
    // printList(sort);
    // printList(head);

    Node *l1 = new Node(1);
    l1->next = new Node(3);
    l1->next->next = new Node(5);

    Node *l2 = new Node(2);
    l2->next = new Node(4);
    l2->next->next = new Node(6);

    Node *sort = mergeList(l1, l2);

    printList(sort);

    return 0;
}