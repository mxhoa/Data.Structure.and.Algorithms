#include <iostream>
#include "LinkedListSimple.h"

using namespace std;

Node* deleteMiddle(Node *head)
{
    /* Base Cases */
    if (head == nullptr)
    {
        return nullptr;
    }
    
    if (head->next == nullptr)
    {
        delete head;
        return nullptr;
    }
    
    
    Node *slow = head;
    Node *fast = head;
    Node *prev = nullptr;
    
    while (fast->next)
    {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }
    prev->next = slow->next;
    
    return head;
}

int main(){
    LinkedListSimple *l = new LinkedListSimple();
    
    l->insert_node(1);
    l->insert_node(2);
    l->insert_node(3);
    l->insert_node(4);
    l->insert_node(5);
    l->insert_node(6);
    l->insert_node(7);
    
    
    l->print_list();
    
    deleteMiddle(l->head);
    
    l->print_list();
    
    return 0;
}



