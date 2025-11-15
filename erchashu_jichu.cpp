#include <iostream>
using namespace std;

struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;
	
	TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

TreeNode* createSampleTree() {
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(5);
	root->right->left = new TreeNode(6);
	root->right->right = new TreeNode(7);
	return root;
}

void preorderTraversal(TreeNode* root) {
	if (root == nullptr) return;
	cout << root->data << " ";
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

void inorderTraversal(TreeNode* root) {
	if (root == nullptr) return;
	inorderTraversal(root->left);
	cout << root->data << " ";
	inorderTraversal(root->right);
}

void postorderTraversal(TreeNode* root) {
	if (root == nullptr) return;
	postorderTraversal(root->left);
	postorderTraversal(root->right);
	cout << root->data << " ";
}

void deleteTree(TreeNode* root) {
	if (root == nullptr) return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

int main() {
	TreeNode* root = createSampleTree();
	
	cout << "前序遍历: ";
	preorderTraversal(root);
	cout << endl;
	
	cout << "中序遍历: ";
	inorderTraversal(root);
	cout << endl;
	
	cout << "后序遍历: ";
	postorderTraversal(root);
	cout << endl;
	
	deleteTree(root);
	return 0;
}
