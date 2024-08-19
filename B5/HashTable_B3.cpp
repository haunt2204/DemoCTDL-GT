#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define M 17

int hashFunc(int key) {
	return key%M;
}

struct User
{
	int id;
	string username;
	int freq;
};

struct Node
{
	User *data;
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

void insertNode(HashTable &ht, User *x) {
	int k = hashFunc(x->id);

	if (ht.h[k].data == NULL) {
		ht.h[k].data = x;
	}
	else {
		if (ht.h[k].data->id == x->id) {
			ht.h[k].data->freq += 1;
		}
		else {
			while (ht.h[k].next != -1) {
				k = ht.h[k].next;
				if (ht.h[k].data->id == x->id) {
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
			cout << "BUCKET " << i << ": " << ht.h[i].data->id << "-" << ht.h[i].data->username << "--> " << ht.h[i].next << " SO LUOT TRUY CAP: " << ht.h[i].data->freq << endl;
	}
}

int main() {
	HashTable h;
	init(h);
	ifstream inFile("user.txt");
	User listUser[10];

	int i = 0;
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			User u;
			inFile >> u.id;
			inFile.ignore();
			inFile >> u.username;
			u.freq = 1;

			listUser[i++] = u;
		}
		inFile.close();
	}

	//Gia lap truy cap
	insertNode(h, &listUser[0]);
	insertNode(h, &listUser[0]);
	insertNode(h, &listUser[0]);
	insertNode(h, &listUser[4]);
	insertNode(h, &listUser[2]);
	insertNode(h, &listUser[0]);
	insertNode(h, &listUser[2]);


	printHashTable(h);

	system("pause");
	return 1;
}