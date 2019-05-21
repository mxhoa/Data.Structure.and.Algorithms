#include <iostream>
#include "LinkedListSimple.h"

using namespace std;


bool deleteMiddleNode(Node *mid) 
{
	if (mid == nullptr || mid->next == nullptr) 
	{
		return false;
	}

	Node *next = mid->next;
	mid->data = next->data;
	mid->next = next->next;

	delete(next);

	return true;
}

Node* getMiddleNode(Node *head)
{
    if (head == nullptr || head->next == nullptr)
            return nullptr;

    Node *slow = head;
    Node *fast = head;

    while (fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}


int main()
{
	LinkedListSimple *l = new LinkedListSimple();

	l->insert_node(1);
    l->insert_node(2);
    l->insert_node(3);
    l->insert_node(4);
    l->insert_node(5);
    l->insert_node(6);
    l->insert_node(7);
    
    
    l->print_list();
    
    Node *mid = getMiddleNode(l->head);

    deleteMiddleNode(mid);
    
    l->print_list();
    
    return 0;

}