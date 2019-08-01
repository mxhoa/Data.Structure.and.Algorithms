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

Node *merge(Node *l1, Node *l2)
{
    Node l(0);
    Node *curr = &l;

    while (l1 && l2)
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
        curr = curr->next;
    }

    curr->next = l1 ? l1 : l2;
    return l.next;
}

Node *sortList(Node *head)
{
    if (!head || !head->next)
        return head;

    Node *slow = head;
    Node *fast = head->next;
    Node *r = nullptr;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    r = slow->next;
    slow->next = nullptr;

    return merge(sortList(head), sortList(r));
}

void printList(Node *head)
{
    Node *curr = head;
    while (curr)
    {
        cout << "->" << curr->val;
        curr = curr->next;
    }
    cout << endl;
}

int main()
{
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