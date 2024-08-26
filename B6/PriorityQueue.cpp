#include <iostream>
using namespace std;

#define MAX 4

struct Node
{
	int data;
	int priority;
};

struct Queue
{
	Node a[MAX];
	int front, rear;
};

void init(Queue &q) {
	q.front = q.rear = -1;
}

void enQueue(Queue &q, Node x) {
	if (q.rear - q.front == MAX - 1) {
		return;
	}

	if (q.front == -1) {
		q.a[0] = x;
		q.front = q.rear = 0;
	}
	else {
		if (q.rear == MAX - 1) {
			for (int i = q.front; i <= q.rear; i++) {
				q.a[i - q.front] = q.a[i];
			}
			q.rear = (MAX - 1) - q.front;
			q.front = 0;
		}
		int i;
		for (i = q.rear; i >= q.front; i--) {
			if (x.priority > q.a[i].priority) {
				q.a[i + 1] = q.a[i];
			}
			else
				break;
		}
		q.a[i + 1] = x;
		q.rear++;
		/*q.a[++q.rear] = x;*/
	}
}

Node* deQueue(Queue &q) {
	if (q.front == -1)
		return NULL;

	Node *tmp = &q.a[q.front++];

	if (q.front > q.rear) {
		q.front = q.rear = -1;
	}

	return tmp;
}

bool isEmpty(Queue q) {
	return q.front == -1;
}

void printQueue(Queue q) {
	while (!isEmpty(q)) {
		Node *tam = deQueue(q);
		cout << tam->data << "-" << tam->priority << endl;
	}
}

int main() {
	Queue q;
	init(q);

	Node n1, n2, n3, n4, n5;

	n1.data = 8;
	n1.priority = 1;

	n2.data = 11;
	n2.priority = 1;

	n3.data = 12;
	n3.priority = 2;

	n4.data = 15;
	n4.priority = 1;

	n5.data = 1;
	n5.priority = 3;

	enQueue(q, n1);
	enQueue(q, n2);
	enQueue(q, n3);
	enQueue(q, n4);
	

	deQueue(q);
	printQueue(q);


	cout << "====TRUONG HOP TRAN====\n";
	enQueue(q, n5);

	printQueue(q);

	return 1;
}