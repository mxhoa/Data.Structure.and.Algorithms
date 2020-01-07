#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/****************************************************** DAY 03 *****************************************************
 * This problem was asked by Google.
 *
 * Given the root to a binary tree, implement serialize(root), which serializes the tree into a string, 
 * and deserialize(s), which deserializes the string back into the tree.
 * 
 * Example: You may serialize the following tree:
 *
 *        1
 *       / \
 *      2   3
 *         / \
 *        4   5
 * 
 *   as "[1,2,3,null,null,4,5]"
 *******************************************************************************************************************/

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

public:
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec
{
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode *root)
    {
        std::ostringstream out;
        serialize(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(std::string data)
    {
        std::istringstream in(data);
        return deserialize(in);
    }

private:
    void serialize(TreeNode *root, std::ostringstream &out)
    {
        if (root)
        {
            out << root->val << ' ';
            serialize(root->left, out);
            serialize(root->right, out);
        }
        else
        {
            out << "# ";
        }
    }

    TreeNode *deserialize(std::istringstream &in)
    {
        std::string val;
        in >> val;
        if (val == "#")
            return nullptr;
        TreeNode *root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
};

class DisplayBinaryTree
{
public:
    static void show(const TreeNode *node)
    {
        std::cout << "Tree image\n";
        printBinaryTreeUtil("", node, false);
    }

private:
    static void printBinaryTreeUtil(const std::string &prefix, const TreeNode *node, bool isLeft)
    {
        if (node != nullptr)
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──");

            // Print the value of the node
            std::cout << node->val << std::endl;

            // Enter the next tree level - left and right branch
            printBinaryTreeUtil(prefix + (isLeft ? "│   " : "    "), node->left, true);
            printBinaryTreeUtil(prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main()
{
    TreeNode *tree = new TreeNode(1);
    tree->left = new TreeNode(2);
    tree->right = new TreeNode(3);
    tree->right->left = new TreeNode(4);
    tree->right->right = new TreeNode(5);

    Codec *cd = new Codec();
    std::string serial = cd->serialize(tree);
    std::cout << serial << std::endl;

    TreeNode *dTree = cd->deserialize(serial);
    DisplayBinaryTree::show(dTree);

    return 0;
}
