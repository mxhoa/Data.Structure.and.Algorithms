#include <iostream>
#include <stack>
#include "LinkedListSimple.h"

using namespace std;


void print_list(Node *head, const string nameList)
{
    cout << nameList << " ||";
    while (head)
    {
        cout << " ->" << head->data;
        head = head->next;
    }
    
    cout << endl;
}
/**
 * @brief       Sum of two list (unordered)
 *              l1 = 7->1->6 => 617
 *              l2 = 5->9->2 => 295
 *              l  = 2->1->9 <= 912
 *              
 *
 * @param      l1    The fisrt list
 * @param      l2    The second list
 *
 * @return     sum of two lists
 */
LinkedListSimple* sumList_Unordered(LinkedListSimple *l1, LinkedListSimple *l2)
{
    LinkedListSimple *l = new LinkedListSimple();
    
    Node *runner1 = l1->head;
    Node *runner2 = l2->head;
    
    int carry = 0;
    int sum = 0;

    while (runner1 || runner2)
    {
        sum = 0;
        if (runner1 && runner2)
        {
            sum = runner1->data + runner2->data + carry;
            runner1 = runner1->next;
            runner2 = runner2->next;
        }
        else if (runner1 != nullptr && runner2 == nullptr)
        {
            sum = runner1->data + carry;
            runner1 = runner1->next;
        }
        else if (runner1 == nullptr && runner2 != nullptr)
        {
            sum = runner2->data + carry;
            runner2 = runner2->next;
        }
        carry = sum / 10;
        sum = sum % 10;

        l->insert_node(sum);
    }

    return l;
}


/**
 * @brief       Sum of two list ( Ordered )
 *              l1 = 6->1->7 => 617
 *              l2 = 2->9->5 => 295
 *              l  = 9->1->2 <= 912
 *              
 *
 * @param      l1    The fisrt list
 * @param      l2    The second list
 *
 * @return     sum of two lists
 */
LinkedListSimple* sumList_Ordered(LinkedListSimple *l1, LinkedListSimple *l2)
{
    LinkedListSimple *l = new LinkedListSimple();
    stack<int> stk1;
    stack<int> stk2;
    stack<int> stk;

    Node *runner1 = l1->head;
    Node *runner2 = l2->head;

    while (runner1)
    {
        stk1.push(runner1->data);
        runner1 = runner1->next;
    }
    while (runner2)
    {
        stk2.push(runner2->data);
        runner2 = runner2->next;
    }

    int sum = 0;
    int carry = 0;

    while (!stk1.empty() || !stk2.empty())
    {
        sum = 0;
        if (!stk1.empty() && !stk2.empty())
        {
            sum = stk1.top() + stk2.top() + carry;
            stk1.pop();
            stk2.pop();
        }
        else if (!stk1.empty() && stk2.empty())
        {
            sum = stk1.top() + carry;
            stk1.pop();
        }
        else if (stk1.empty() && !stk2.empty())
        {
            sum = stk2.top() + carry;
            stk2.pop();
        }
        carry = sum / 10;
        sum = sum % 10;

        stk.push(sum);
    }

    while (!stk.empty())
    {
        l->insert_node(stk.top());
        stk.pop();
    }
    return l;

}
int main()
{
    LinkedListSimple *l1 = new LinkedListSimple();
    LinkedListSimple *l2 = new LinkedListSimple();

    l1->insert_node(7);
    l1->insert_node(1);
    l1->insert_node(6);

    l2->insert_node(5);
    l2->insert_node(9);
    l2->insert_node(2);
    l2->insert_node(1);

    LinkedListSimple *l = sumList_Unordered(l1, l2);
    LinkedListSimple *m = sumList_Ordered(l1, l2);

    print_list(l1->head, "L1");
    print_list(l2->head, "L2");
    print_list(l->head, "L ");
    print_list(m->head, "M ");


    return 0;

}