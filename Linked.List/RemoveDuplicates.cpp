#include <iostream>
#include <unordered_map>
#include "LinkedListSimple.h"

using namespace std;

/**
 * @brief      Removes a duplicates 1.
 *
 * @param      head  The head
 * 
 * 				Time Complexity	O(N^2)
 * 				Space Complextiy	O(1)
 * 
 */
void removeDuplicates1(Node *head)
{
	Node *cur = head;
	if (head == nullptr || head->next == nullptr)
		return;
	
	while (cur)
	{
		Node *runner = cur;
		while (runner->next)
		{
			if (runner->next->data == cur->data)
			{
				runner->next = runner->next->next;
			}
			else
			{
				runner = runner->next;
			}
		}
		cur = cur->next;
	}
}

/**
 * @brief      Removes duplicates.
 *
 * @param      head  The head
 * 				Time Complexity 	O(N)
 * 				Space Complexity 	O(N)
 */

void removeDuplicates(Node *head)
{
	Node *cur = head;
	Node *prev = head;
	unordered_map<int, bool> mp;

	if (head == nullptr || head->next == nullptr)
		return;

	while (cur)
	{
		if (!mp[cur->data])
		{
			mp[cur->data] = true;
			prev = cur;
			cur = cur->next;
		}
		else
		{
			Node *tmp = cur;
			cur = cur->next;
			prev->next = cur;
			delete tmp;
		}
	}

}

int main()
{
	LinkedListSimple *l = new LinkedListSimple();

    l->insert_node(1);
    l->insert_node(1);
    l->insert_node(2);
    l->insert_node(2);
    l->insert_node(3);
    l->insert_node(4);
    l->insert_node(5);
    l->insert_node(4);
    l->insert_node(6);
    l->insert_node(6);

    // print_list(l->head);
    l->print_list();

    removeDuplicates1(l->head);

    // print_list(l->head);
    l->print_list();

	return 0;
}