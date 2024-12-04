#include <iostream>
using namespace std;

class BST;

class BST {
private:
	int data = 0;
	BST* left = nullptr;
	BST* right = nullptr;
public:
	BST *findMinimum(BST* root) {
		BST* current = root;
		while (current && current->left) {
			current = current->left;
		}
		return current;
	}
	BST() {}
	BST(int value) : data(value) {}
	BST* Insert(BST* root, int value) {
		if (!root) {
			return new BST(value);
		}

		if (value > root->data) {
			root->right = Insert(root->right, value);
		}
		else {
			root->left = Insert(root->left, value);
		}

		return root;
	}

	void Inorder(BST* root) {
		if (!root) return;
		Inorder(root->left);
		cout << root->data << endl;
		Inorder(root->right);
	}

	BST *remove(BST* root, int value) {
		if (!root) return nullptr;

		if (root->data > value) {
			root->left = remove(root->left, value);
		} else if (root->data < value) {
			root->right =  remove(root->right, value);
		}
		else {
			// Remove leaf node or Remove a parent node with only one child node
			if (root->left == nullptr) {
				BST *temp = root->right;
				delete root;
				root = nullptr;
				return temp;
			}
			else if (root->right == nullptr) {
				BST* temp = root->left;
				delete root;
				root = nullptr;
				return temp;
			}
			else {
				// Remove a parent node with full child nodes
				// Find minimum of the right child tree
				BST * temp = findMinimum(root->right);
				root->data = temp->data;
				root->right = remove(root->right, temp->data);
			}
		}
		return root;
	}
};


int main() {
	BST* root = nullptr;
	root = root->Insert(root, 50);
	root->Insert(root, 30);
	root->Insert(root, 20);
	root->Insert(root, 40);
	root->Insert(root, 70);
	root->Insert(root, 60);
	root->Insert(root, 80);
	root->Inorder(root);

	// Remove leaf node
	root->remove(root, 20);
	root->Inorder(root);

	// Remove a parent node with only one child node
	root->remove(root, 30);
	root->Inorder(root);

	// Remove a parent node with full child nodes
	root->remove(root, 50);
	root->Inorder(root);

	root->Inorder(root);
	return 0;
}