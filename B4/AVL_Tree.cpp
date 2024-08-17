#include <iostream>
using namespace std;

//Khai bao cau truc
struct Node
{
	int data;
	Node *left, *right;
	int height;
};

//Khoi tao rong
void treeEmpty(Node *&root) {
	root = NULL;
}

//Thao tac them
Node* createNode(int x) {
	Node *p = new Node;
	p->data = x;
	p->left = p->right = NULL;
	p->height = 1;
	return p;
}

int max(const int a, const int b) {
	return a > b ? a : b;
}

int getHeight(Node *root) {
	if (root == NULL)
		return 0;
	return root->height;
}

void updateHeight(Node *&root) {
	if (root != NULL)
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
}

void rightRotate(Node *&root) {
	Node *x = root->left;
	root->left = x->right;
	x->right = root;

	//Cap nhat chieu cao
	updateHeight(root);
	updateHeight(x);

	root = x;
}

void leftRotate(Node *&root) {
	Node *x = root->right;
	root->right = x->left;
	x->left = root;
	//Cap nhat chieu cao
	updateHeight(root);
	updateHeight(x);

	root = x;
}

int getBalance(Node *root) {
	if (root == NULL)
		return 0;
	return getHeight(root->left) - getHeight(root->right);
}

void insertNode(Node *&root, const int x) {
	if (root == NULL)
		root = createNode(x);
	else if (x > root->data)
		insertNode(root->right, x);
	else if (x < root->data)
		insertNode(root->left, x);
	else
		return;

	//Cap nhat chieu cao cua cay
	updateHeight(root);

	//Kiem tra can bang cay de dieu chinh
	int val = getBalance(root);

	if (val > 1 && x < root->left->data) {
		//Lech trai trai
		rightRotate(root);
	}
	else if (val > 1 && x > root->left->data) {
		//Lech trai phai
		leftRotate(root->left);
		rightRotate(root);
	}
	else if (val <-1 && x>root->right->data) {
		//Lech phai phai
		leftRotate(root);
	}
	else if (val < -1 && x < root->right->data) {
		//Lech phai trai
		rightRotate(root->right);
		leftRotate(root);
	}
}

//Thao tac xoa
void delNodeNoRec(Node *&root, const int x) {
	//Cay rong
	if (root == NULL)
		return;
	Node *cur = root;//Node can xoa
	Node *parent = NULL;

	while (cur != NULL&&cur->data != x) {
		parent = cur;
		if (x > cur->data)
			cur = cur->right;
		else
			cur = cur->left;
	}
	//Khong tim thay x trong cay
	if (cur == NULL)
		return;
	//Tim thay x co 3 truong hop
	//TH1: Node la hoac node bac 1
	if (cur->left == NULL || cur->right == NULL) {
		Node *temp;//Nhanh con cua node can xoa (trai hoac phai)
		if (cur->right == NULL)
			temp = cur->left;
		else
			temp = cur->right;

		//Dieu chinh lien ket cua node cha
		if (cur == root)
			root = temp;
		else if (x > parent->data)
			parent->right = temp;
		else
			parent->left = temp;

		delete cur;
	}
	else {
		//TH2: node bac 2
		Node *temp = cur->right;//Node the mang
		parent = NULL;
		while (temp->left != NULL) {
			parent = temp;
			temp = temp->left;
		}

		//Chep gia tri node the mang len cho nut can xoa
		cur->data = temp->data;

		//Xoa node the mang
		if (parent != NULL) {
			parent->left = temp->right;
		}
		else {
			cur->right = temp->right;
		}

		delete temp;
	}
}

void searchStandFor(Node *&cur, Node *&temp) {
	if (temp->left != NULL) {
		searchStandFor(cur, temp->left);
	}
	else {
		cur->data = temp->data;
		cur = temp;
		temp = temp->right;
	}
}

void delNode(Node *&root, const int key) {
	if (root == NULL)
		return;
	if (key > root->data)
		delNode(root->right, key);
	else if (key < root->data)
		delNode(root->left, key);
	else {
		//Tim thay node can xoa
		Node *cur = root;
		//TH1: node la hoac node bac
		if (root->left == NULL)
			root = root->right;
		else if (root->right == NULL)
			root = root->left;
		else {
			searchStandFor(cur, root->right);
		}
		delete cur;
	}

	//Cap nhat chieu cao
	if (root == NULL)
		return;

	updateHeight(root);

	int val = getBalance(root);

	if (val > 1 && getBalance(root->left) >= 0) {
		//Trai trai
		rightRotate(root);
	}
	else if (val > 1 && getBalance(root->left) < 0) {
		//Lech trai phai
		rightRotate(root->left);
		leftRotate(root);
	}
	else if (val < -1 && getBalance(root->right) <= 0) {
		//Lech phai phai
		leftRotate(root);
	}
	else if (val < -1 && getBalance(root->right)>0) {
		//Lech phai trai
		leftRotate(root->right);
		rightRotate(root);
	}
}

//Thao tac duyet
void NLR(Node *root) {
	if (root != NULL) {
		cout << root->data << "(" << root->height << ") ";
		NLR(root->left);
		NLR(root->right);
	}
}

void LNR(Node *root) {
	if (root != NULL) {
		LNR(root->left);
		cout << root->data << "(" << root->height << ") ";
		LNR(root->right);
	}
}
//Thao tac tren cay
int countNode(Node *root) {
	if (root != NULL) {
		return 1 + countNode(root->left) + countNode(root->right);
	}
	return 0;
}

void countNodeBac0(Node *root, int &count) {
	if (root != NULL) {
		if(root->left==NULL && root->right==NULL)
			count += 1;
		countNodeBac0(root->left, count);
		countNodeBac0(root->right, count);
	}
}

int calHeight(Node *root) {
	if (root != NULL) {
		int left = calHeight(root->left);
		int right = calHeight(root->right);

		return 1 + max(left, right);
	}
	return 0;
}

void printK(Node *root, int K, int k = 0) {
	if (root != NULL) {
		k += 1;
		printK(root->left, K, k);
		if (k == K) {
			cout << root->data << "(" << root->height << ") ";
		}
		printK(root->right, K, k);
	}
}

Node* search(Node *root, const int key) {
	if (root != NULL) {
		Node *p = root;
		while (p != NULL) {
			if (p->data == key)
				return p;
			if (key > p->data)
				p = p->right;
			else
				p = p->left;
		}
	}
	return NULL;
}

//Khai bao cau truc Stack
#define MAX 50

//Khai bao cau truc
struct Stack
{
	Node* a[MAX];
	int top;
};

//Khoi tao rong
void init(Stack &s) {
	s.top = -1;
}

//Cac thao tac
void push(Stack &s, Node* x) {
	if (s.top < MAX) {
		s.a[++s.top] = x;
	}
}

bool isEmpty(Stack s) {
	return s.top == -1;
}

Node* pop(Stack &s) {
	if (!isEmpty(s)) {
		return s.a[s.top--];
	}
}

void lnrNoRec(Node *root) {
	if (root != NULL) {
		Stack s;
		init(s);

		Node *p = root;

		while (!isEmpty(s) || p != NULL) {
			while (p != NULL) {
				push(s, p);
				p = p->left;
			}

			p = pop(s);
			cout << p->data << "(" << p->height << ") ";
			p = p->right;
		}
	}
}

void nlrNoRec(Node *root) {
	if (root != NULL) {
		Stack s;
		init(s);

		Node *p = root;

		while (!isEmpty(s) || p != NULL) {
			while (p != NULL) {
				cout << p->data << "(" << p->height << ") ";
				push(s, p);
				p = p->left;
			}
			p = pop(s);
			p = p->right;
		}
	}
}

int main() {
	Node *root;
	treeEmpty(root);

	insertNode(root, 40);
	insertNode(root, 20);
	insertNode(root, 60);
	insertNode(root, 15);
	insertNode(root, 25);
	insertNode(root, 7);

	NLR(root);
	cout << endl;

	cout << "SO NODE: " << countNode(root) << endl;

	int count = 0;
	countNodeBac0(root, count);
	cout << "SO NODE LA: " << count << endl;
	cout << "CHIEU CAO: " << getHeight(root) << endl;
	cout << "CHIEU CAO (REC): " << calHeight(root) << endl;
	cout << "XUAT MUC 2: ";
	printK(root, 2);
	cout << endl;

	/*delNode(root, 7);
	delNode(root, 15);
	NLR(root);
	cout << endl;*/

	cout << "NLR NO REC: ";
	nlrNoRec(root);
	cout << endl;

	LNR(root);
	cout << endl;
	cout << "LNR NO REC: ";
	lnrNoRec(root);
	cout << endl;
	/*Node *kq = search(root, 65);
	if (kq != NULL)
		cout << "TIM THAY!\n";
	else
		cout << "KHONG TIM THAY!\n";*/

	system("pause");
	return 1;
}