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

TreeNode* findMin(TreeNode* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return root; // 如果树为空，直接返回

    // 定位要删除的节点
    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    } else {
        // 找到要删除的节点，并且
        // 1. 节点是叶子节点或仅有一个子节点
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // 2. 节点有两个子节点
        TreeNode* temp = findMin(root->right); // 寻找右子树中的最小节点
        root->val = temp->val; // 替换值
        root->right = deleteNode(root->right, temp->val); // 删除右子树中的最小节点
    }
    return root;
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
