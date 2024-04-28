#include <iostream>

class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void insertNode(TreeNode* &root, int value) {
    if (!root) {
        root = new TreeNode(value);
    } else if (value < root->val) {
        insertNode(root->left, value);
    } else {
        insertNode(root->right, value);
    }
}

void preorder(TreeNode* root) {
    if (!root) return;
    std::cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    std::cout << root->val << " ";
    inorder(root->right);
}

void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    std::cout << root->val << " ";
}

int main() {
    TreeNode* root = nullptr;
    insertNode(root, 10);
    insertNode(root, 5);
    insertNode(root, 15);
    insertNode(root, 3);
    insertNode(root, 7);

    std::cout << "Preorder traversal: ";
    preorder(root);
    std::cout << "\nInorder traversal: ";
    inorder(root);
    std::cout << "\nPostorder traversal: ";
    postorder(root);
    std::cout << std::endl;

    return 0;
}
