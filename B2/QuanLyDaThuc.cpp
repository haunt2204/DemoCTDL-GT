#include <iostream>
using namespace std;

//Khai bao cau truc
struct Term {
	int coef;//He so
	int exp;//Bac 
};

struct Node {
	Term info;
	Node *next;
};

//Khoi tao rong
void init(Node *&head) {
	head = NULL;
}

//Cac thao tac 
Node *createNode(Term t) {
	Node *p = new Node;
	p->info = t;
	p->next = NULL;
	return p;
}

void insertOrderedList(Node *&head, Term x) {
	if (head == NULL || x.exp < head->info.exp) {
		Node *p = createNode(x);
		p->next = head;
		head = p;
		return;
	}

	Node *q = head;
	
	while (q->next != NULL && q->next->info.exp <= x.exp)
		q = q->next;

	if (q->info.exp == x.exp) {
		q->info.coef = x.coef;
		return;
	}

	Node *p = createNode(x);
	p->next = q->next;
	q->next = p;
}

//Duyet danh sach
void printList(Node *head) {
	//2x^2+2x^5
	if (head != NULL) {
		Node *p = head;
		while (p != NULL) {
			cout << p->info.coef << "x^" << p->info.exp;
			if (p->next != NULL)
				cout << "+";
			p = p->next;
		}
		cout << endl;
	}
}

int f(Node *head, const int x) {
	Node *p = head;
	int tong = 0;
	while (p != NULL) {
		tong += p->info.coef*pow(x, p->info.exp);
		p = p->next;
	}
	return tong;
}

//Xoa vung nho
void delFirst(Node *&head) {
	if (head != NULL) {
		Node *p = head;
		head = head->next;
		p->next = NULL;
		delete p;
	}
}

void destroyList(Node *&head) {
	while (head != NULL) {
		delFirst(head);
	}
}

int main() {
	Node *head;
	init(head);

	Term t1, t2, t3, t4;
	t1.coef = 2;
	t1.exp = 3;
	insertOrderedList(head, t1);

	t2.coef = 3;
	t2.exp = 2;
	insertOrderedList(head, t2);
	
	t3.coef = 5;
	t3.exp = 5;
	insertOrderedList(head, t3);

	t4.coef = 4;
	t4.exp = 4;
	insertOrderedList(head, t4);

	printList(head);

	t4.coef = 2;
	t4.exp = 4;
	insertOrderedList(head, t4);

	printList(head);

	cout << "f(2) = " << f(head, 2) << endl;

	destroyList(head);
	system("pause");
	return 1;
}