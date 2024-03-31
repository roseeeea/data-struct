//code is from Chat GPT 3.5
//introduction of tree

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class TreeNode {
public:
    string name;
    vector<TreeNode*> children; //指向子樹的地址(*) //用vector型態（宣告為TreeNode）可以無限增加節點

    TreeNode(string name) : name(name) {}

    ~TreeNode() {
        for (TreeNode* child : children) {
            delete child;
        }
    }
};

void printTree(TreeNode* root, int depth = 0) { //初始化數值depth
    if (root == nullptr) return; //此樹為空 無需列印

    // 打印当前节点的名称
    for (int i = 0; i < depth; ++i) {
        cout << "  "; // 缩进
    }
    cout << "|-- " << root->name << std::endl;

    // 递归打印子节点
    for (TreeNode* child : root->children) { //root 中的children
        printTree(child, depth + 1);
    }
}

int main() {
    TreeNode* root = new TreeNode("/");
    TreeNode* home = new TreeNode("home");
    TreeNode* var = new TreeNode("var");
    root->children.push_back(home);
    root->children.push_back(var);

    TreeNode* user1 = new TreeNode("user1");
    TreeNode* user2 = new TreeNode("user2");
    home->children.push_back(user1);
    home->children.push_back(user2);

    TreeNode* file1 = new TreeNode("file1.txt");
    TreeNode* file2 = new TreeNode("file2.txt");
    user1->children.push_back(file1);
    user1->children.push_back(file2);

    TreeNode* documents = new TreeNode("documents");
    TreeNode* music = new TreeNode("music");
    user2->children.push_back(documents);
    user2->children.push_back(music);

    TreeNode* report = new TreeNode("report.doc");
    TreeNode* notes = new TreeNode("notes.txt");
    documents->children.push_back(report);
    documents->children.push_back(notes);

    TreeNode* song1 = new TreeNode("song1.mp3");
    TreeNode* song2 = new TreeNode("song2.mp3");
    music->children.push_back(song1);
    music->children.push_back(song2);

    TreeNode* log = new TreeNode("log");
    TreeNode* tmp = new TreeNode("tmp");
    var->children.push_back(log);
    var->children.push_back(tmp);

    TreeNode* syslog = new TreeNode("syslog");
    TreeNode* errorLog = new TreeNode("error.log");
    log->children.push_back(syslog);
    log->children.push_back(errorLog);

    TreeNode* temp = new TreeNode("temp.txt");
    tmp->children.push_back(temp);

    // 打印整棵树
    printTree(root);

    // 释放内存
    delete root;

    return 0;
}


/*
 output:
 /
 ├── home
 │   ├── user1
 │   │   ├── file1.txt
 │   │   └── file2.txt
 │   └── user2
 │       ├── documents
 │       │   ├── report.doc
 │       │   └── notes.txt
 │       └── music
 │           ├── song1.mp3
 │           └── song2.mp3
 └── var
     ├── log
     │   ├── syslog
     │   └── error.log
     └── tmp
         └── temp.txt
 */

////////////////////////////////////////////////////////////////
//preorder inorder postorder travesal
#include <iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    return root;
}

void preorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    cout << root->val << " "; // 先访问根节点
    preorderTraversal(root->left); // 再递归遍历左子树
    preorderTraversal(root->right); // 最后递归遍历右子树
}

void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left); // 先递归遍历左子树
    std::cout << root->val << " "; // 再访问根节点
    inorderTraversal(root->right); // 最后递归遍历右子树
}

void postorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    postorderTraversal(root->left); // 先递归遍历左子树
    postorderTraversal(root->right); // 再递归遍历右子树
    std::cout << root->val << " "; // 最后访问根节点
}

int main() {
    TreeNode* root = createSampleTree();

    cout << "Preorder traversal: ";
    preorderTraversal(root);
    cout << std::endl;

    cout << "Inorder traversal: ";
    inorderTraversal(root);
    cout << std::endl;

    cout << "Postorder traversal: ";
    postorderTraversal(root);
    cout << std::endl;

    return 0;
}

/*
   1
/     \
2      3
/ \   / \
4  5 6   7

 Preorder traversal: 1 2 4 5 3 6 7
 Inorder traversal: 4 2 5,1,6 3 7 //對稱
 Postorder traversal: 4 5 2 6 7 3 1


 
 */


