#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#define M 17

int hashFunc(char* str) {
	int key = 0;
	for (int i = 0; i < strlen(str); i++) {
		key += (int) *(str + i)*(i + 1);
	}
	return key%M;
}

struct StrValue
{
	char* key;
	int freq;
};

struct Node
{
	StrValue *data;
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

void insertNode(HashTable &ht, StrValue *x) {
	int k = hashFunc(x->key);

	if (ht.h[k].data == NULL) {
		ht.h[k].data = x;
	}
	else {
		if (strcmp(ht.h[k].data->key, x->key)==0) {
			ht.h[k].data->freq += 1;
		}
		else {
			while (ht.h[k].next != -1) {
				k = ht.h[k].next;
				if (strcmp(ht.h[k].data->key, x->key)==0) {
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
			cout << "BUCKET " << i << ": " << ht.h[i].data->key << "--> " << ht.h[i].next << " SO LAN: " << ht.h[i].data->freq << endl;
	}
}

int main() {

	char str[] = "apple banana apple cherry date banana cherry fig grape date";

	HashTable h;
	init(h);

	char *p = strtok(str, " ");
	while (p != NULL) {
		StrValue *v = new StrValue;
		v->key = p;
		v->freq = 1;
		insertNode(h, v);
		p = strtok(NULL, " ");
	}

	printHashTable(h);

	system("pause");
	return 1;
}