#include <iostream>
using namespace std;

#define M 7

int hashFunc(int key) {
	return key%M;
}

struct Node {
	int key;
	int next;
};

struct HashTable {
	Node h[M];
	int r;
};

void init(HashTable &ht) {
	for (int i = 0; i<M; i++) {
		ht.h[i].key = -1;
		ht.h[i].next = -1;
	}
	ht.r = M - 1;
}

void insert(HashTable &ht, int x) {
	int k = hashFunc(x);

	if (ht.h[k].key == -1) {
		ht.h[k].key = x;
	}
	else {
		if (ht.r >= 0) {
			ht.h[ht.r].key = x;
			while (ht.h[k].next != -1) {
				k = ht.h[k].next;
			}
			ht.h[k].next = ht.r;
		}
	}
	while (ht.r >= 0 && ht.h[ht.r].key != -1) {
		ht.r--;
	}
}

void printHashTable(HashTable ht) {
	for (int i = 0; i<M; i++) {
		if (ht.h[i].key != -1)
			cout << "BUCKET " << i << ": " << ht.h[i].key << "->" << ht.h[i].next << endl;
	}
}

void delNode(HashTable &ht, int key) {
	int k = hashFunc(key);

	while (k != -1 && ht.h[k].key != key) {
		k = ht.h[k].next;
	}

	if (k == -1)
		return;

	int prev = -1;
	while (ht.h[k].next != -1) {
		prev = k;
		k = ht.h[k].next;

		ht.h[prev].key = ht.h[k].key;
	}

	ht.h[k].key = -1;
	if (prev != -1)
		ht.h[prev].next = -1;
	if (ht.r < k)
		ht.r = k;
}

int main() {
	HashTable ht;
	init(ht);

	insert(ht, 7);
	insert(ht, 28);
	insert(ht, 10);
	insert(ht, 12);
	insert(ht, 14);
	insert(ht, 8);

	printHashTable(ht);

	cout << "==========SAU KHI XOA==========\n" << endl;
	delNode(ht, 7);


	insert(ht, 35);
	printHashTable(ht);

	return 1;
}
