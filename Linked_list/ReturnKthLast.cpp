#include <iostream>
#include "LinkedListSimple.h"

using namespace std;

enum RET
{
	RET_OK = 0, 	// Success
	RET_ERR,		// Fail
	RET_MAX
};

#define Kth(ret,k,val)	if (ret == RET_OK) \
							cout << "Kth = " << k << "\t\t - val = " << val << endl; \
						else \
							cout << "Kth = " << k << "\t - ERROR" << endl; 


RET returnKthLast(Node *head, int k, int *ret)
{
	Node *cur = head;
    Node *res = head;
    int i = 0;

    while (i <= k && cur != nullptr)
    {
        cur = cur->next;
        if (cur == nullptr)
            return RET_ERR;
        i++;
    }


    while (cur)
    {
        res = res->next;
        cur = cur->next;
    }

    *ret = res->data;

    return RET_OK;
}

int main()
{
	LinkedListSimple *l = new LinkedListSimple();
	int val = 0;
	RET ret = RET_MAX;

    l->insert_node(1);
    l->insert_node(2);
    l->insert_node(3);
    l->insert_node(4);
    l->insert_node(5);
    l->insert_node(6);
    l->insert_node(7);
    l->insert_node(8);
    l->insert_node(9);
    l->insert_node(10);

    l->print_list();

    ret = returnKthLast(l->head, 3, &val);
    Kth(ret, 3, val);

    ret = returnKthLast(l->head, 10, &val);
    Kth(ret, 10, val);

    ret = returnKthLast(l->head, 0, &val);
    Kth(ret, 0, val);

    ret = returnKthLast(l->head, 5, &val);
    Kth(ret, 5, val);
    
	return 0;
}