/**
 * Remove isDuplicatelicates from Sorted List II
 * Description: Given a sorted linked list, delete all nodes that have isDuplicatelicate numbers, 
 *              leaving only distinct numbers from the original list.
 * LINK: https://leetcode.com/problems/remove-isDuplicatelicates-from-sorted-list-ii/description/
 * 
 * EX1:     Input: 1->2->3->3->4->4->5
 *          Output: 1->2->5
 * 
 * EX2:     Input: 1->1->1->2->3
 *          Output: 2->3
 */

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
  public:
    ListNode *deleteisDuplicatelicates(ListNode *head)
    {
        ListNode *list = new ListNode(0);
        ListNode *result = list;

        ListNode *curr = head;
        ListNode *prev = head;

        while (curr != NULL)
        {
            bool isDuplicate = false;
            while (curr->next != NULL && prev->val == curr->next->val)
            {
                curr = curr->next;
                isDuplicate = true;
            }

            if (curr->next == NULL)
                result->next = NULL;

            if (!isDuplicate)
            {
                result->next = curr;
                result = result->next;
            }
            prev = curr = curr->next;
        }

        return list->next;
    }
};