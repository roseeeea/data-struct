#include <iostream>
#include <vector>

////////////for heap by vec
void preorder(vector<int>& heap, int index) {
    if (index >= heap.size()) return;
    cout << heap[index] << " ";
    preorder(heap, 2 * index + 1); // 左子树
    preorder(heap, 2 * index + 2); // 右子树
}

void inorder(vector<int>& heap, int index) {
    if (index >= heap.size()) return;
    inorder(heap, 2 * index + 1); // 左子树
    std::cout << heap[index] << " ";
    inorder(heap, 2 * index + 2); // 右子树
}

void postorder(vector<int>& heap, int index) {
    if (index >= heap.size()) return;
    postorder(heap, 2 * index + 1); // 左子树
    postorder(heap, 2 * index + 2); // 右子树
    std::cout << heap[index] << " ";
}





///////////for N tree
class Node {
public:
    int val;
    std::vector<Node*> children; //vector<*Node> 可以記起來這個方式

    Node(int x) : val(x) {}
};

void preorder(Node* root) {
    if (!root) return;
    std::cout << root->val << " ";  // 访问根节点
    for (Node* child : root->children) {
        preorder(child);  // 递归访问每个子节点
    }
}

void postorder(Node* root) {
    if (!root) return;
    for (Node* child : root->children) {
        postorder(child);  // 递归访问每个子节点
    }
    std::cout << root->val << " ";  // 访问根节点
}





//////////////////////////////////////////////

int main() {
  //heap
    std::vector<int> heap = {10, 20, 30, 40, 50, 60};
    std::cout << "Preorder traversal: ";
    preorder(heap, 0);
    std::cout << "\nInorder traversal: ";
    inorder(heap, 0);
    std::cout << "\nPostorder traversal: ";
    postorder(heap, 0);
    std::cout << std::endl;
    return 0;


  
  //N tree
  Node* root = new Node(1);
    root->children.push_back(new Node(2));
    root->children.push_back(new Node(3));
    root->children.push_back(new Node(4));

    root->children[0]->children.push_back(new Node(5));
    root->children[0]->children.push_back(new Node(6));

    root->children[2]->children.push_back(new Node(7));

    std::cout << "Preorder traversal: ";
    preorder(root);
    std::cout << "\nPostorder traversal: ";
    postorder(root);
    std::cout << std::endl;
}
