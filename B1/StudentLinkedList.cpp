#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Dinh nghia kieu du lieu
struct SinhVien
{
	int MSSV;
	string hoVaTen;
	char ngaySinh[11];
	string queQuan;
	double diemTB;
};

//Cac ham cua SinhVien
void xuat1Sv(const SinhVien sv) {
	cout << "=======================\n";
	cout << "MSSV: " << sv.MSSV << endl;
	cout << "Ho va ten: " << sv.hoVaTen << endl;
	cout << "Ngay sinh: " << sv.ngaySinh << endl;
	cout << "Que quan: " << sv.queQuan << endl;
	cout << "Diem TB: " << sv.diemTB << endl;
	cout << "=======================\n";
}

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

ostream& operator <<(ostream &out, const SinhVien sv) {
	cout << "=======================\n";
	cout << "MSSV: " << sv.MSSV << endl;
	cout << "Ho va ten: " << sv.hoVaTen << endl;
	cout << "Ngay sinh: " << sv.ngaySinh << endl;
	cout << "Que quan: " << sv.queQuan << endl;
	cout << "Diem TB: " << sv.diemTB << endl;
	cout << "=======================\n";
	return out;
}

//Khai bao cau truc
struct Node
{
	//Vung thong tin
	SinhVien info;
	//Vung lien ket
	Node *next;
};

//Khoi tao danh sach rong
void init(Node *&head) {
	head = NULL;
}

//Cac thao tac
Node* createNode(const SinhVien sv) {
	Node *p = new Node;
	p->info = sv;
	p->next = NULL;
	return p;
}

//Them vao dau danh sach
void insertFirst(Node *&head, SinhVien sv) {
	Node *p = createNode(sv);
	if (head == NULL)
		head = p;
	else {
		p->next = head;
		head = p;
	}
}
//Nhap danh sach sinh vien
void nhapDsSv(Node *&head) {
	int chon = 1;
	while (chon!=0) {
		SinhVien sv;
		nhap1Sv(sv);
		insertFirst(head, sv);
		cout << "Tiep tuc (1-Co/0-Khong): "; cin >> chon;
	}
}

void nhapDsSvTuFile(Node *&head, const string tenFile) {
	ifstream inFile(tenFile);
	if (inFile.is_open()) {
		int n;
		inFile >> n;
		int i = 0;

		while (i++<n) {
			SinhVien sv;
			inFile >> sv.MSSV;
			inFile.ignore();
			getline(inFile, sv.hoVaTen, '#');
			inFile.getline(sv.ngaySinh, 11, '#');
			getline(inFile, sv.queQuan, '#');
			inFile >> sv.diemTB;
			
			insertFirst(head, sv);
		}

		inFile.close();
	}
}


//Xoa dau
void delFirst(Node *&head) {
	if (head != NULL) {
		Node *p = head;
		head = head->next;
		p->next = NULL;
		delete p;
	}
}

//Duyet danh sach
void printList(Node *head) {
	if (head != NULL) {
		Node *p = head;
		while (p != NULL) {
			cout << p->info;
			//xuat1Sv(p->info);
			p = p->next;
		}
	}
}

//Huy toan bo danh sach
void detroyList(Node *&head) {
	while (head != NULL) {
		delFirst(head);
	}
}

int main() {
	Node *head;
	init(head);
	/*nhapDsSv(head);*/
	nhapDsSvTuFile(head, "SinhVien.txt");
	printList(head);
	/*cout << "========KET QUA XOA==============\n";
	delFirst(head);
	printList(head);*/
	detroyList(head);
	cout << "====KET QUA HUY====\n";
	printList(head);
	system("pause");
	return 1;
}