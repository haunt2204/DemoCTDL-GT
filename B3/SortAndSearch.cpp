#include <iostream>
#include <fstream>
using namespace std;

void swap(long &a, long &b) {
	long c = a;
	a = b;
	b = c;
}

//Selection Sort
void selectionSort(long a[], int n) {
	int pos;
	for (int i = 0; i < n - 1; i++) {
		pos = i;
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[pos])
				pos = j;
		swap(a[pos], a[i]);
	}
}

//Insertion Sort
void insertionSort(long a[], int n) {
	int x, j;
	for (int i = 1; i < n; i++) {
		x = a[i];
		j = i - 1; 
		while (j >= 0 && a[j] > x) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = x;
	}
}

//Interchange Sort: SV tu cai dat

//Bubble Sort: SV tu cai dat

//Merge Sort: O(nlogn), SV tu cai dat

//Quick Sort O(nlogn), O(n^2)
void quickSort(long a[], int left, int right) {
	int l = left, r = right;
	int pivot = a[(left + right) / 2];
	while (l < r) {
		while (a[l] < pivot)
			l++;
		while (a[r] > pivot)
			r--;
		if (l <= r) {
			swap(a[l], a[r]);
			l++; r--;
		}
	}
	if (left < r)
		quickSort(a, left, r);
	if (l < right)
		quickSort(a, l, right);
}
//Heap Sort O(nlogn)
void heapify(long a[], int n, int i) {
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	int maxPos = i;

	if (l<n&&a[l]>a[maxPos])
		maxPos = l;
	if (r<n&&a[r]>a[maxPos])
		maxPos = r;

	if (maxPos == i)
		return;
	swap(a[i], a[maxPos]);
	heapify(a, n, maxPos);
}

void heapSort(long a[], int n) {
	int i = n / 2 - 1; 
	while (i >= 0) {
		heapify(a, n, i);
		i--;
	}

	for (int right = n - 1; right > 0; right--) {
		swap(a[0], a[right]);
		heapify(a, right, 0);
	}
}

void printList(long a[], int n) {
	ofstream outFile("SortedList.txt");
	if (outFile.is_open()) {
		for (int i = 0; i < n; i++) {
			outFile << a[i] << "\n";
		}
	}
}

//Tim kiem
//O(n)
int sequentialSearch(long a[], long n, long key) {
	for (long i = 0; i < n; i++) {
		if (a[i] == key)
			return i;
	}
	return -1;
}

//O(logn)
int binarySearch(long a[], long n, long key) {
	int left = 0, right = n - 1, mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (a[mid] == key)
			return mid;
		else if (a[mid] > key)
			left = mid + 1;
		else
			right = mid - 1;
	}
}

int main() {
	ifstream inFile("DaySo.txt");
	long *a = NULL;
	long n;

	if (inFile.is_open()) {
		inFile >> n;
		a = new long[n];
		for (long i = 0; i < n; i++) {
			inFile >> a[i];
		}
		inFile.close();
	}

	cout << "Da doc file xong!\n";

	heapSort(a, n);
	printList(a, n);
	cout << "Tim kiem!\n";
	long kq = binarySearch(a, n, 999997);
	if (kq != -1)
		cout << "Tim thay 999997\n";

	return 1;
}