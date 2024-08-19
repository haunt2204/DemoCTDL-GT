#include <iostream>
using namespace std;

#define M 17

int hashFunc(int key) {
	return key%M;
}

struct IntValue
{
	int key;
	int freq;
};

struct Node
{
	IntValue *data;
	int next;
};

struct HashTable
{
	Node h[M];
	int r;
};

void init(HashTable &ht) {
	for (int i = 0; i < M; i++) {
		ht.h[i].data = NULL;
		ht.h[i].next = -1;
	}
	ht.r = M - 1;
}

void insertNode(HashTable &ht, IntValue *x) {
	int k = hashFunc(x->key);

	if (ht.h[k].data == NULL) {
		ht.h[k].data = x;
	}
	else {
		if (ht.h[k].data->key == x->key) {
			ht.h[k].data->freq += 1;
		}
		else {
			while (ht.h[k].next != -1) {
				k = ht.h[k].next;
				if (ht.h[k].data->key == x->key) {
					ht.h[k].data->freq += 1;
					return;
				}
			}
			ht.h[ht.r].data = x;
			ht.h[k].next = ht.r;
		}
	}

	while (ht.r >= 0 && ht.h[ht.r].data != NULL) {
		ht.r--;
	}
}

void printHashTable(HashTable ht) {
	for (int i = 0; i < M; i++) {
		if (ht.h[i].data != NULL)
			cout << "BUCKET " << i << ": " << ht.h[i].data->key << "--> " << ht.h[i].next << " SO LAN: "<< ht.h[i].data->freq << endl;
	}
}

int main() {

	int a[] = {15, 7, 9, 7, 13, 15, 20, 11, 9, 15, 20};
	int n = sizeof(a) / sizeof(a[0]);

	HashTable h;
	init(h);

	for (int i = 0; i < n; i++) {
		IntValue *x = new IntValue;
		x->key = a[i];
		x->freq = 1;
		insertNode(h, x);
	}

	printHashTable(h);

	system("pause");
	return 1;
}