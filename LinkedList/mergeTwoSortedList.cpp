#include <iostream>

using namespace std;

class Node
{
public:
	int data;
	Node *next;
public:
	Node(int val)
	{
		this->data = val;
		this->next = nullptr;
	}
};

void printList(Node *head)
{
    Node *curr = head;
    while (curr != nullptr)
    {
        cout << "->" << curr->data;
        curr = curr->next;
    }
    cout << endl;
}


Node* mergeTwoSortedList_Ascending(Node *h1, Node *h2)
{
	Node l(0);
	Node *curr = &l;

	while (h1 && h2)
	{
		if (h1->data <= h2->data)
		{
			curr->next = h1;
			h1 = h1->next;
		} else {
			curr->next = h2;
			h2 = h2->next;
		}
		curr = curr->next;
	}

	curr->next = h1 ? h1 : h2;
	return l.next;
}


Node *mergeTwoSortedList_Descending(Node *h1, Node *h2)
{
	Node *prev = nullptr;
	Node *head;

	while (h1 && h2)
	{
		if (h1->data <= h2->data)
		{
			head = h1;
			h1 = h1->next;
			head->next = prev;
			prev = head;
		} else {
			head = h2;
			h2 = h2->next;
			head->next = prev;
			prev = head;
		}
	}

	while (h1)
	{
		head = h1;
		h1 = h1->next;
		head->next = prev;
		prev = head;

	}

	while (h2)
	{
		head = h2;
		h2 = h2->next;
		head->next = prev;
		prev = head;
	}

	return prev;
}


int main()
{
	Node *head1 = new Node(1);
    head1->next = new Node(5);
    head1->next->next = new Node(9);
    
    Node *head2 = new Node(3);
    head2->next = new Node(4);
    head2->next->next = new Node(7);
    head2->next->next->next = new Node(10);
    head2->next->next->next->next = new Node(15);
    head2->next->next->next->next->next = new Node(17);
    
    printList(head1);
    printList(head2);
    
    // Node *head = mergeTwoSortedList_Ascending(head1, head2);
    Node *head = mergeTwoSortedList_Descending(head1, head2);
    
    printList(head);
    
    
    return 0;
}