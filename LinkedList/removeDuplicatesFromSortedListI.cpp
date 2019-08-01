/**
 * Remove Duplicates from Sorted List
 * Link: https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/
 */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL){}
};

class Solution {
    public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* curr = head;
        while (curr != NULL && curr->next != NULL)
        {
            if (curr->val == curr->next->val)
            {
                curr->next = curr->next->next;
            }
            else 
            {
                curr = curr->next;
            }
        }
        return head;
    }
}