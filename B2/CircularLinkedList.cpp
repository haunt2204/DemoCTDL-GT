#include <iostream>
using namespace std;

//Khai bao cau truc
struct Node
{
	int info;

	Node *next;
};

struct CircularLinkedList
{
	Node *head;
};

//Khoi tao rong
void init(CircularLinkedList &cl) {
	cl.head = NULL;
}

//Cac thao tac 

Node* createNode(const int x) {
	Node *p = new Node;
	p->info = x;
	p->next = NULL;

	return p;
}

void insertFirst(CircularLinkedList &cl, const int x) {
	Node *p = createNode(x);
	if (cl.head == NULL) {
		cl.head = p;
		cl.head->next = p;
	}
	else {
		Node *pLast = cl.head;
		while (pLast->next != cl.head)
			pLast = pLast->next;
		pLast->next = p;
		p->next = cl.head;

		cl.head = p;
	}
}

void insertLast(CircularLinkedList &cl, const int x) {
	Node *p = createNode(x);
	if (cl.head == NULL) {
		cl.head = p;
		cl.head->next = p;
	}
	else {
		Node *pLast = cl.head;
		while (pLast->next != cl.head)
			pLast = pLast->next;
		pLast->next = p;
		p->next = cl.head;
	}
}

void delFirst(CircularLinkedList &cl) {
	if (cl.head != NULL) {
		Node *p = cl.head; //Node can xoa
		Node *pLast = cl.head;

		while (pLast->next != cl.head)
			pLast = pLast->next;

		if (pLast == cl.head) {
			cl.head = NULL;
		}
		else {
			cl.head = cl.head->next;
			pLast->next = cl.head;
		}

		p->next = NULL;
		delete p;
	}
}

void printList(CircularLinkedList cl) {
	if (cl.head != NULL) {
		Node *p = cl.head;
		do {
			cout << p->info << " ";
			p = p->next;
		} while (p!=cl.head);
	}
	cout << endl;
}

void destroyList(CircularLinkedList &cl) {
	while (cl.head != NULL) {
		delFirst(cl);
	}
}

int main() {
	CircularLinkedList cl;
	init(cl);

	insertLast(cl, 5);
	insertLast(cl, 6);
	insertLast(cl, 7);
	printList(cl);

	delFirst(cl);
	printList(cl);

	destroyList(cl);
	system("pause");
	return 1;
}