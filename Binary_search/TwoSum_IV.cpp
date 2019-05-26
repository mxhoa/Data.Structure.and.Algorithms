#include<iostream>
#include<vector>

using namespace std;

/**
 * @brief 653. Two Sum IV - Input is a BST
 * @ref: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/
 * Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.
 * Example 1:
 * 	Input: 
 *           5
 *          / \
 *         3   6
 *        / \   \
 *       2   4   7
 * 		
 * 		Target = 9
 *
 * 	Output: True
 * 		 
 * 		
 * Example 2:
 * 	Input: 
 * 		    5
 * 		   / \
 * 		  3   6
 * 		 / \   \
 * 		2   4   7
 * 		
 * 		Target = 28
 * 		
 *	Output: False
 * 		
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution_1 {
	/**
	 * This method also works for those who are not BSTs. The idea is to use a hashtable
	 * too save the values of the nodes in the BST. Each time when we insert the value of 
	 * a new node into the hashtable, we check if the hashtable contains (k - node->val)
	 *
	 * Time Complexity: O(n), 
	 * Space Complexity: O(n).
	*/
public:
    bool dfs(TreeNode* root, unordered_set<int> &set, int k) {
        if (root == nullptr) 
            return false;
        if (set.count(k - root->val) > 0) 
            return true;
        set.insert(root->val);
        
        return dfs(root->left, set, k) || dfs(root->right, set, k);
    }
    
    
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> set;
        
        return dfs(root, set, k);
    }
};

class Solution_2 {
	/**
	 * The idea is to use a sorted array to save the values of the nodes in the BST by using 
	 * an inorder traversal. Then, we use two pointers which begins from the start and end of 
	 * the array to find  if there is a sum k
	 * Time Complexity: O(n), 
	 * Space Complexity: O(n)
	*/
public:
	bool findTarget(TreeNode* root, int k)
	{
		vector<int> nums;
		inorder(root, nums);
		for (int i = 0, j = nums.size() - 1; i < j; )
		{
			if (nums[i] + nums[j] == k)
				return true;

			(nums[i] + nums[j] < k) ? i++ : j--;
		}
		return false;
	}

	void inorder(TreeNode* root, vector<int>& nums)
	{
		if (root == nullptr)	return;
		inorder(root->left, nums);
		nums.push_back(root->val);
		inorder(root->right, nums);
	}
};

class Solution_3 {
	/**
	 * The idea is to use binary search method. For each node, we check if (k - node->val) exists in this BST.
	 * 
	 * Time Complexity: O(nh)
	 * Space Complexity: O(h)
	 *    h is the height of the tree, which is logN at best case, and N at worst case 
	 */
public:
    bool findTarget(TreeNode* root, int k) {
        return dfs(root, root, k);
    }
    
    bool dfs(TreeNode* root, TreeNode* current, int k) {
        if (current == nullptr) return false;
        
        if (search(root, current, k - current->val))
            return true;
        
        return  dfs(root, current->left, k) || dfs(root, current->right, k);
    }
    
    // Find in the tree element which has value is k and different with the current node
    bool search(TreeNode* root, TreeNode *current, int k)
    {
        if (root == nullptr) return false;
        
        if (root->val > k)
            return search(root->left, current, k);
        else if (root->val < k)
            return search(root->right, current, k);
        else
            return current != root ? true : false;
        
    }
};