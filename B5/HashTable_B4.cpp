#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define M 101

int hashFunc(string str) {
	int key = 0;
	for (int i = 0; i < str.length(); i++) {
		key += (int)tolower(str[i])*(i + 1);
	}
	return key%M;
}

struct Word {
	string word;//Tu tieng Anh
	string type;//Loai tu
	string mean;//Y nghia
};

struct Node
{
	Word data;
	Node *next;
};

void init(Node *heads[]) {
	for (int i = 0; i < M; i++) {
		heads[i] = NULL;
	}
}

Node* createWord(Word w) {
	Node *p = new Node;
	p->data = w;
	p->next = NULL;
	return p;
}

string normalize(string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}

void insertWord(Node *heads[], Word w) {
	int k = hashFunc(w.word);

	Node *p = heads[k];

	if (p == NULL)
		heads[k] = createWord(w);
	else {
		while (p != NULL) {
			if (normalize(p->data.word) == normalize(w.word))
				return;

			if (p->next != NULL) {
				p = p->next;
			}
			else
				break;
		}
		p->next = createWord(w);
	}
}

Node *search(Node*heads[], string key) {
	int k = hashFunc(key);

	Node *p = heads[k];
	while (p != NULL && normalize(p->data.word) != normalize(key)) {
		p = p->next;
	}
	return p;
}

void uppdateWord(Node *heads[], Word w) {
	int k = hashFunc(w.word);

	Node *p = heads[k];

	while (p != NULL) {
		if (normalize(p->data.word) == normalize(w.word)) {
			p->data.type = w.type;
			p->data.mean = w.mean;
			return;
		}
		p = p->next;
	}
}

void deleteWord(Node *heads[], string key) {
	int k = hashFunc(key);

	Node *p = heads[k];
	Node *par = NULL;
	while (p != NULL && normalize(p->data.word) != normalize(key)) {
		par = p;
		p = p->next;
	}
	//Khong tim thay
	if (p == NULL)
		return;

	//Tim thay node dau va node o giua
	if (par == NULL)
		heads[k] = p->next;
	else
		par->next = p->next;

	delete p;
}

void printDict(Node *heads[]) {
	for (int i = 0; i < M; i++) {
		if (heads[i] != NULL) {
			cout << "BUCKET " << i << ": ";
			Node *p = heads[i];
			while (p != NULL) {
				cout << p->data.word << "(" << p->data.type << "): " << p->data.mean ;
				if (p->next != NULL)
					cout << "==>";
				p = p->next;
			}
			cout << endl;
		}
	}
}

void readData(Node *heads[]) {
	ifstream inFile("dictionary.txt");
	if (inFile.is_open()) {

		while (!inFile.eof()) {
			Word w;
			getline(inFile,w.word, '#');
			getline(inFile, w.type, '#');
			getline(inFile, w.mean, '\n');

			insertWord(heads, w);
		}

		inFile.close();
	}
}

int main() {

	Node *heads[M];
	init(heads);

	Word w1, w2, w3, w4, w5;

	w1.word = "Apple";
	w1.type = "N";
	w1.mean = "Trai tao";

	w2.word = "Teacher";
	w2.type = "N";
	w2.mean = "Giang vien";

	w3.word = "Happy";
	w3.type = "Adj";
	w3.mean = "Hanh phuc";

	w4.word = "Go";
	w4.type = "V";
	w4.mean = "Di";

	w5.word = "apple";
	w5.type = "N";
	w5.mean = "Tao";


	insertWord(heads, w1);
	insertWord(heads, w2);
	insertWord(heads, w3);
	insertWord(heads, w4);
	/*uppdateWord(heads, w5);*/


	readData(heads);

	printDict(heads);

	/*Node *kq = search(heads, "banana");
	if (kq != NULL)
		cout << kq->data.type << "-" << kq->data.mean << endl;
	else
		cout << "Khong tim thay!\n";*/

	/*deleteWord(heads, "apple");
	printDict(heads);*/

	system("pause");
	return 1;
}