#include <iostream>
using namespace std;

////Khai bao cau truc
struct Node
{
	int info;
	Node *next, *prev;
};

struct DoublyLinkedList
{
	Node *head, *tail;
};

////Khoi tao rong
void init(DoublyLinkedList &dl) {
	dl.head = dl.tail = NULL;
}

////Cac thao tac

//Tim kiem
Node* findMax(DoublyLinkedList dl) {
	Node *res = dl.head;
	Node *p = dl.head;
	while (p != NULL) {
		if (p->info > res->info)
			res = p;
		p = p->next;
	}
	return res;
}
Node* findMin(DoublyLinkedList dl) {
	Node *res = dl.head;
	Node *p = dl.head;
	while (p != NULL) {
		if (p->info < res->info)
			res = p;
		p = p->next;
	}
	return res;
}

Node* findNode(DoublyLinkedList dl, const int key) {
	//Xuat hien dau tien trong danh sach
	if (dl.head != NULL) {
		Node *p = dl.head;
		while (p != NULL) {
			if (p->info == key)
				return p;
			p = p->next;
		}
	}
	return NULL;
}

Node* createNode(const int x) {
	Node *p = new Node;
	p->info = x;
	p->next = p->prev = NULL;

	return p;
}

void insertFirst(DoublyLinkedList &dl, const int x) {
	Node *p = createNode(x);
	if (dl.head == NULL) {
		dl.head = dl.tail = p;
	}
	else {
		p->next = dl.head;
		dl.head->prev = p;
		dl.head = p;
	}
}

void insertLast(DoublyLinkedList &dl, const int x) {
	Node *p = createNode(x);
	if (dl.head == NULL) {
		dl.head = dl.tail = p;
	}
	else {
		dl.tail->next = p;
		p->prev = dl.tail;
		dl.tail = p;
	}
}

void insertAfter(DoublyLinkedList &dl, const int key, const int x) {
	Node *q = findNode(dl, key);
	if (q != NULL) {
		if (q == dl.tail)
			insertLast(dl, x);
		else {
			Node *p = createNode(x);
			p->next = q->next;
			q->next->prev = p;

			p->prev = q;
			q->next = p;
		}
	}
	else
		cout << "Khong tim thay!\n";
}

void insertOrderedList(DoublyLinkedList &dl, const int x) {
	Node *p = createNode(x);
	//Danh sach rong
	if (dl.head == NULL) {
		dl.head = dl.tail = p;
		return;
	}

	//Can them o dau
	if (p->info <= dl.head->info) {
		insertFirst(dl, x);
		return;
	}

	//Them o giua
	Node *cur = dl.head;
	while (cur->next != NULL&&cur->next->info < p->info)
		cur = cur->next;

	if (cur == dl.tail) {
		insertLast(dl, x);
		return;
	}

	p->next = cur->next;
	cur->next->prev = p;

	p->prev = cur;
	cur->next = p;
}

//Xoa
void delNode(Node *&p) {
	p->next = NULL;
	p->prev = NULL;
	delete p;
}

void delFirst(DoublyLinkedList &dl) {
	if (dl.head != NULL) {
		Node *p = dl.head;
		dl.head = dl.head->next;
		if (dl.head == NULL)
			dl.tail = NULL;
		else
			dl.head->prev = NULL;
		delNode(p);
	}
}

void delLast(DoublyLinkedList &dl) {
	if (dl.head != NULL) {
		Node *p = dl.tail;
		dl.tail = dl.tail->prev;
		if (dl.tail == NULL)
			dl.head = NULL;
		else
			dl.tail->next = NULL;
		delNode(p);
	}
}

void destroyList(DoublyLinkedList &dl) {
	while (!isEmpty(dl))
		delFirst(dl);
}

//Kiem tra rong
bool isEmpty(DoublyLinkedList dl) {
	return dl.head == NULL;
}


//Sap xep
void swap(int &a, int &b) {
	a = a + b;
	b = a - b;
	a = a - b; 
}

void sortList(DoublyLinkedList &dl) {
	if (dl.head != NULL) {
		for (Node* i = dl.head; i->next != NULL; i = i->next) {
			for (Node *j = i->next; j != NULL; j = j->next) {
				if (i->info > j->info)
					swap(i->info, j->info);
			}
		}
	}
}

//Dem so luong node
int countNode(DoublyLinkedList dl) {
	int count = 0;
	Node *p = dl.head;
	while (p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}

//Duyet
void printListFromHead(DoublyLinkedList dl) {
	Node *p = dl.head;
	while (p != NULL) {
		cout << p->info << " ";
		p = p->next;
	}
	cout << endl;
}


void printListFromTail(DoublyLinkedList dl) {
	Node *p = dl.tail;
	while (p != NULL) {
		cout << p->info << " ";
		p = p->prev;
	}
	cout << endl;
}



int main() {
	DoublyLinkedList dl;
	init(dl);

	/*insertLast(dl, 4);*/
	/*insertLast(dl, 7);
	insertLast(dl, 1);
	insertLast(dl, 5);
	insertAfter(dl, 7, 8);*/
	printListFromHead(dl);
	printListFromTail(dl);
	cout << "===========SAP XEP==========\n";
	sortList(dl);

	printListFromHead(dl);
	printListFromTail(dl);

	cout << "So luong node: " << countNode(dl) << endl;

	insertOrderedList(dl, -1);
	printListFromHead(dl);
	printListFromTail(dl);
	/*insertFirst(dl, 6);
	insertFirst(dl, 5);*/
	/*delLast(dl);
	delLast(dl);
	delLast(dl);*/
	
	/*Node *kq = findNode(dl, 80);
	if (kq != NULL)
		cout << kq->info << endl;
	else
		cout << "Khong tim thay!\n";*/
	destroyList(dl);
	printListFromHead(dl);
	printListFromTail(dl);
	system("pause");
	return 1;
}