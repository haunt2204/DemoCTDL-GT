#include <iostream>
using namespace std;

//Khai bao cau truc
struct Node
{
	int data;
	Node *left, *right;
};

//Khoi tao rong
void treeEmpty(Node *&root) {
	root = NULL;
}

//Cac thao tac tren cay
//Them 
Node *createNode(int x) {
	Node *p = new Node;
	p->data = x;
	p->left = p->right = NULL;
	return p;
}

void insertNode(Node *&root, int x) {
	if (root == NULL) {
		root = createNode(x);
	}
	else {
		Node *p = root;
		while (true) {
			if (p->data > x) {
				if (p->left == NULL) {
					p->left = createNode(x);
					return;
				}
				p = p->left;
			}
			else if (p->data < x) {
				if (p->right == NULL) {
					p->right = createNode(x);
					return;
				}
				p = p->right;
			}
			else
				return;
		}
	}
}

////Duyet
void LNR(Node *root) {
	if (root != NULL) {
		LNR(root->left);
		cout << root->data << " ";
		LNR(root->right);
	}
}

int main() {
	Node *root;
	treeEmpty(root);
	insertNode(root, 40);
	insertNode(root, 60);
	insertNode(root, 20);
	insertNode(root, 25);
	insertNode(root, 30);

	LNR(root);

	return 1;
}