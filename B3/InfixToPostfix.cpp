#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#define MAX 50

//Khai bao cau truc
struct Stack
{
	char* a[MAX];
	int top;
};

//Khoi tao rong
void init(Stack &s) {
	s.top = -1;
}

//Cac thao tac
void push(Stack &s, char* x) {
	if (s.top < MAX) {
		s.a[++s.top] = x;
	}
}

bool isEmpty(Stack s) {
	return s.top == -1;
}

char* pop(Stack &s) {
	if (!isEmpty(s)) {
		return s.a[s.top--];
	}
	return "";
}

char* peek(Stack &s) {
	if (!isEmpty(s)) {
		return s.a[s.top];
	}
	return "";
}

//Queue
struct Node
{
	char* info;
	Node *next;
};

struct Queue
{
	Node *head;
};

void init(Queue &q) {
	q.head = NULL;
}

Node* createNode(char* x) {
	Node *p = new Node;
	p->info = x;
	p->next = NULL;
	return p;
}

void enQueue(Queue &q, char* x) {
	Node *p = createNode(x);//New Node

	if (q.head == NULL) {
		q.head = p;
	}
	else {
		Node *pLast = q.head;
		while (pLast->next != NULL) {
			pLast = pLast->next;
		}
		pLast->next = p;
	}
}

char* deQueue(Queue &q) {
	char *data = "";

	if (q.head != NULL) {
		Node *p = q.head;
		q.head = q.head->next;
		data = p->info;
		p->next = NULL;
		delete p;
	}

	return data;
}

bool isEmpty(Queue q) {
	return q.head == NULL;
}

int getPriority(string op) {
	if (op == "/" || op == "*")
		return 2;
	if (op == "+" || op == "-")
		return 1;
	return 0;
}

void infixToPostfix(char str[]) {
	Stack s;
	init(s);

	Queue postfix;
	init(postfix);

	char *p = strtok(str, " ");
	while (p != NULL) {
		if (isdigit(*p))
			enQueue(postfix, p);
		else if (*p == '(') {
			push(s, p);
		}
		else if (*p == ')') {
			char*op = pop(s);
			while (*op != '(') {
				enQueue(postfix, op);
				op = pop(s);
			}
		}
		else {
			while (!isEmpty(s)&&getPriority(p) <= getPriority(peek(s))) {
				char *op = pop(s);
				enQueue(postfix, op);
			}
			push(s, p);
		}

		p = strtok(NULL, " ");
	}

	while (!isEmpty(s)) {
		char* op = pop(s);
		enQueue(postfix, op);
	}

	while (!isEmpty(postfix)) {
		cout << deQueue(postfix) << " ";
	}
}

int main() {
	char str[] = "2 + 4 - ( 5 - 3 ) / 2 + 3 - 1 * 5";
	infixToPostfix(str);
	return 0;
}