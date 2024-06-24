#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define MAX 100

//Dinh nghia
struct SinhVien
{
	int MSSV;
	string hoVaTen;
	char ngaySinh[11];
	string queQuan;
	double diemTB;
};

struct DSSV
{
	SinhVien ds[MAX];
	int n;
};

//Cac ham cua SinhVien
void nhap1Sv(SinhVien &sv) {
	cout << "Nhap MSSV: "; cin >> sv.MSSV;
	cin.ignore();
	cout << "Nhap ho va ten: "; 
	getline(cin, sv.hoVaTen, '\n');
	cout << "Nhap ngay sinh: ";
	cin >> sv.ngaySinh;
	cin.ignore();
	cout << "Nhap que quan: ";
	getline(cin, sv.queQuan, '\n');
	cout << "Nhap diem TB: ";
	cin >> sv.diemTB;
}

void xuat1Sv(const SinhVien sv) {
	cout << "=======================\n";
	cout << "MSSV: " << sv.MSSV << endl;
	cout << "Ho va ten: " << sv.hoVaTen << endl;
	cout << "Ngay sinh: " << sv.ngaySinh << endl;
	cout << "Que quan: " << sv.queQuan << endl;
	cout << "Diem TB: " << sv.diemTB << endl;
	cout << "=======================\n";
}

//Cac ham cua DSSV
void nhapDsSv(DSSV &l) {
	do {
		cout << "Nhap so luong SV: "; cin >> l.n;
		if (l.n <= 0 || l.n > 100)
			cout << "Nhap lai!\n";
	} while (l.n <= 0 || l.n > 100);

	for (int i = 0; i < l.n; i++) {
		nhap1Sv(l.ds[i]);
	}
}
//Tim kiem
int search(const DSSV l, int key) {//
	for (int i = 0; i < l.n; i++) {
		if (l.ds[i].MSSV == key)
			return i;
	}
	return -1;
}

int search(const DSSV l, string key) {
	for (int i = 0; i < l.n; i++) {
		if (l.ds[i].hoVaTen == key || l.ds[i].queQuan==key)
			return i;
	}
	return -1;
}

void swap(SinhVien &sv1, SinhVien &sv2) {
	SinhVien tam = sv1;
	sv1 = sv2;
	sv2 = tam;
}

int cmpWithIdDESC(const SinhVien sv1, const SinhVien sv2) {
	/*if (sv1.MSSV > sv2.MSSV)
		return 1;
	if (sv1.MSSV < sv2.MSSV)
		return -1;
	return 0;*/

	return sv1.MSSV > sv2.MSSV ? 1 : (sv1.MSSV < sv2.MSSV) ? -1 : 0;
}

int cmpWithIdASC(const SinhVien sv1, const SinhVien sv2) {
	return -(sv1.MSSV > sv2.MSSV ? 1 : (sv1.MSSV < sv2.MSSV) ? -1 : 0);
}


int cmpWithNameDESC(const SinhVien sv1, const SinhVien sv2) {
	return sv1.hoVaTen > sv2.hoVaTen ? 1 : (sv1.hoVaTen < sv2.hoVaTen) ? -1 : 0;
}
//Sap xep
void sort(DSSV &l, int comparator(SinhVien, SinhVien)) {
	for (int i = 0; i < l.n - 1; i++) {
		for (int j = i + 1; j < l.n; j++) {
			if (comparator(l.ds[i], l.ds[j])==-1)
				swap(l.ds[i], l.ds[j]);
		}
	}
}

//Xoa 1 sinh vien
void delSv(DSSV &l, const int id) {
	int index = search(l, id);
	if (index != -1) {
		for (int i = index; i < l.n - 1; i++) {
			l.ds[i] = l.ds[i + 1];
		}
		l.n--;
	}
}

//Them 1 sinh vien vao danh sach
void insertSv(DSSV &l, const int key, const SinhVien sv) {
	int index = search(l, key);
	if (index != -1 && l.n < MAX) {
		index += 1;
		for (int i = l.n; i > index; i--) {
			l.ds[i] = l.ds[i - 1];
		}
		l.ds[index] = sv;
		l.n++;
	}
}

void nhapDsSvTuFile(DSSV &l, string tenFile) {
	ifstream inFile(tenFile);
	if (inFile.is_open()) {
		inFile >> l.n;
		int i = 0;

		while (i<l.n) {
			SinhVien sv;
			inFile >> sv.MSSV;
			inFile.ignore();
			getline(inFile, sv.hoVaTen, '#');
			inFile.getline(sv.ngaySinh, 11, '#');
			getline(inFile, sv.queQuan, '#');
			inFile >> sv.diemTB;
			l.ds[i++] = sv;
		}

		inFile.close();
	}
}

void xuatDsSv(const DSSV l) {
	for (int i = 0; i < l.n; i++) {
		xuat1Sv(l.ds[i]);
	}
}

void hienThiTungSv(const DSSV l) {
	int i = 0, chon = 1;
	while (i < l.n && chon != 0) {
		xuat1Sv(l.ds[i++]);
		cout << "Tiep tuc (1-Co/0-Khong): "; cin >> chon;
		system("cls");
	}
}

int main() {
	DSSV l;
	nhapDsSvTuFile(l, "SinhVien.txt");
	hienThiTungSv(l);
	/*nhapDsSv(l);*/
	/*xuatDsSv(l);
	cout << "==========THEM SINH VIEN=============\n";
	SinhVien sv;
	nhap1Sv(sv);
	insertSv(l, 2018004, sv);
	xuatDsSv(l);*/
	/*cout << "==========XOA SINH VIEN=============\n";
	delSv(l, 2018004);
	xuatDsSv(l);*/
	/*cout << "==========SAP XEP=============\n";
	sort(l, cmpWithNameDESC);
	xuatDsSv(l);*/
	/*cout << "==================TIM KIEM==============\n";
	int kq = search(l, "Can Tho");
	if (kq != -1)
		xuat1Sv(l.ds[kq]);
	else
		cout << "Khong tim thay!\n";*/
	system("pause");
	return 1;
}