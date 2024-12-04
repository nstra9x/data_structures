#include <iostream>
using namespace std;

#define COUNT 10

struct Node {
	int key;
	Node* left;
	Node* right;
	int height;

	Node(int k, Node* l, Node* r, int h) : key(k), left(l), right(r), height(h) {}
};

int getHeight(Node* root) {
	if (root == nullptr)
		return 0;
	return root->height;
}

Node* leftRotate(Node* root) {
	// Rotate left
	Node* temp = root->right;
	root->right = temp->left;
	temp->left = root;

	// Update height
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));

	// Then, temp will be root
	return temp;
}

Node* rightRotate(Node* root) {
	Node* temp = root->left;
	root->left = temp->right;
	temp->right = root;

	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));
	
	return temp;
}

int valueBalance(Node* root) {
	if (root == NULL)
		return 0;
	return getHeight(root->left) - getHeight(root->right);
}

Node* rotateRoot(Node* root) {
	// 1. Get height
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));

	// 2. Rotate
	int balance = valueBalance(root);

	// Check 4 cases
	// 2.1. Left left
	if (balance > 1 && valueBalance(root->left) >= 0)
		return rightRotate(root);

	// 2.2 Right right
	if (balance < -1 && valueBalance(root->right) <= 0)
		return leftRotate(root);

	// 2.3 Left right
	if (balance > 1 && valueBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// 2.4 Right left
	if (balance < -1 && valueBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

Node *insert(Node* root, int value) {
	// 1. Insert
	if (root == nullptr) {
		return new Node(value, nullptr, nullptr, 1);
	}

	if (value > root->key)
		root->right = insert(root->right, value);
	else if (value < root->key)
		root->left = insert(root->left, value);
	else
		return root;

	// 2. Rotate
	return rotateRoot(root);
}

Node* remove(Node* root, int value) {
	// 1. Remove 3 cases as BST
	// 2. Rotate
	return rotateRoot(root);
}

// In - Print 2D to console
void print2DUtil(Node* root, int space) {
	if (root == NULL)
		return;
	space += COUNT;

	print2DUtil(root->right, space);
	cout << endl;

	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->key << " (" << root->height << ") " << "\n";

	print2DUtil(root->left, space);
}

void print2D(Node* root) {
	print2DUtil(root, 0);
}

int main() {
	Node* tree = NULL;
	tree = insert(tree, 18);
	tree = insert(tree, 12);
	tree = insert(tree, 30);
	tree = insert(tree, 25);
	tree = insert(tree, 69);
	tree = insert(tree, 23);
	//tree = insert(tree, 10);
	//tree = insert(tree, 11);
	//tree = insert(tree, 13);
	print2D(tree);

	return 0;
}