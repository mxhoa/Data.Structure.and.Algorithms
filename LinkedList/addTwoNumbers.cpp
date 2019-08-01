/**
 *  Add Two Numbers
 * LINK: https://leetcode.com/problems/add-two-numbers/description/
 * 
 * EX:
 *      Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 *      Output: 7 -> 0 -> 8
 *      Explanation: 342 + 465 = 807.
 */

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL){}
};

class Solution
{
  public:
    ListNode* reverse(ListNode *head)
    {
        ListNode* prev = NULL;
        while (head != NULL)
        {
            ListNode* tmp = head->next;
            head->next = prev;
            prev = head;
            head = tmp;
        }
        return prev;
    }
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode* l3 = new ListNode(0);
        ListNode* result = l3;

        int carry = 0;

        while (l1 || l2)
        {
            int sum = 0;
            if (l1 != NULL)
            {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL)
            {
                sum += l2->val;
                l2 = l2->next;
            }
            sum += carry;
            carry = sum % 10;
            result->next = new ListNode(sum / 10);
            result = result->next;
        }

        if (carry > 0)
            result->next = new ListNode(carry);

        return reverse(l3->next);
    }
};