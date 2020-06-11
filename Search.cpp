#ifndef pSearch
#define pSearch

#include "Structs.cpp"
#include "Exception.cpp"
#include "Search.h"

search::search(search& z) : sellCard(z) {
	k = z.k;
	
	try {
		py = new CARD[k];
	}
	catch(bad_alloc) {
		throw 2;
	}

	for (int j = 0; j < k; j++) {
		py[j] = z.py[j];
	}
	cout << "����������� �����������.\n";
}

search& search::operator=(search& z) {
	sellCard::operator=(z);

	if (this == &z) return z;
	k = z.k;
	
	try {
		py = new CARD[k];
	}
	catch(bad_alloc) {
		throw ErrMem("��� ������", "������ ������ py", "search& operator=(search &z)");
	}

	for (int j = 0; j < k; j++) {
		py[j] = z.py[j];
	}
}

ostream& operator << (ostream& out, search& z) {
	int i;

	out << "��������� ������:\n";
	out << left;
	out << " -----------------------------------------------------------------------\n";
	out << " |�����|  ������� �.�.  | ����� |     �����    | �����  |     ���      |\n";
	out << " |     |                |������ |  ����������  |        |    ������    |\n";
	out << " -----------------------------------------------------------------------\n";

	for (i = 0; i < z.k; i++) {
		out << " |" << setw(5) << i + 1 << "|" << setw(16) << z.py[i].FIO << "|" << setw(7) << z.py[i].train.number << "|" << setw(14) << z.py[i].train.dest << "|" << setw(2) << z.py[i].train.time.hour << ":" << setw(2) << z.py[i].train.time.min << "   " << "|" << setw(14) << z.py[i].type << "|" << endl;
		out << " -----------------------------------------------------------------------\n";
	}

	_getch();
	return out;
}

ofstream& operator << (ofstream& out, search& z) {
	string file;
	int i;

	cout << "��� ��������� �����: ";
	cin >> file;
	out.open(file.c_str()); //????? ?????? ?????? ??????-??????
	if (out.fail()) {
		cout << "���� " << file << " �� ������.\n";
		_getch();
		exit(0);
	}

	cout << left;
	out << " -----------------------------------------------------------------------\n";
	out << " |�����|  ������� �.�.  | ����� |     �����    | �����  |     ���      |\n";
	out << " |     |                |������ |  ����������  |        |    ������    |\n";
	out << " -----------------------------------------------------------------------\n";

	for (i = 0; i < z.k; i++) {
		out << " |" << setw(5) << i + 1 << "|" << setw(16) << z.py[i].FIO << "|" << setw(7) << z.py[i].train.number << "|" << setw(14) << z.py[i].train.dest << "|" << setw(2) << z.py[i].train.time.hour << ":" << setw(2) << z.py[i].train.time.min << "   " << "|" << setw(14) << z.py[i].type << "|" << endl;
		out << " ------------------------------------------------------------------------\n";
	}
	out.close();
	cout << "���������� ��������� � ���� " << file << endl;

	_getch();
}

int sortTrainNumberHelper(CARD V, CARD W) {
	if (V.train.number > W.train.number) return 1;
	if (V.train.number < W.train.number) return -1;
	return 0;
}
void search::searchDestinationName() { // ????? ?? ???????? ?????? ?????????? (+?????????? ?? ?????? ??????)
	CARD* p = new CARD[n];
	string destination;
	int j = 0, fl, i;

	cout << "������� ������� ����� ����������: ";
	cin >> destination;

	if (p == NULL) {
		cout << "��� ������.\n";
		cout << "����� �� ��������.\n";
		_getch();
		return;
	}

	for (i = 0; i < n; i++) {
		if (px[i].train.dest == destination) {
			p[j] = px[i];
			j++;
		}
	}
	if (py != NULL) {
		delete[]py;
		k = 0;
		py = NULL;
	}
	
	try {
		py = new CARD[j];	
	}
	catch(bad_alloc) {
		throw ErrMem("��� ������", "������ ������ py", "searchDestinationName()");
	}

	for (i = 0; i < j; i++) {
		py[i] = p[i];
	}
	k = j;
	delete[] p;

	CARD t;
	do {
		fl = 0;
		for (i = 0; i < k - 1; i++) {
			if (sortTrainNumberHelper(py[i], py[i + 1]) > 0) {
				fl = 1;
				t = py[i];
				py[i] = py[i + 1];
				py[i + 1] = t;
			}
		}
	} while (fl == 1);

	cout << "����� ��������. ��������� ������������ �� ������ ������.\n";
	_getch();
}

void search::searchCarriageType() { // ????? ?? ???? ?????? (+?????????? ?? ???)
	CARD* p = new CARD[n];
	string carriageType;
	int j = 0, i, fl;

	cout << "������� ��� ������: ";
	cin >> carriageType;

	if (p == NULL) {
		cout << "��� ������.\n";
		cout << "����� �� ��������.\n";
		_getch();
		return;
	}

	for (int i = 0; i < n; i++) {
		if (px[i].type == carriageType) {
			p[j] = px[i];
			j++;
		}
	}
	if (py != NULL) {
		delete[] py;
		k = 0;
		py = NULL;
	}
	
	try {
		py = new CARD[j];	
	}
	catch(bad_alloc) {
		throw ErrMem("��� ������", "������ ������ py", "searchCarriageType()");
	}

	for (int i = 0; i < j; i++) {
		py[i] = p[i];
	}
	k = j;
	delete[] p;

	CARD t;
	do {
		fl = 0;
		for (i = 0; i < k - 1; i++) {
			if (py[i].FIO > py[i + 1].FIO) {
				fl = 1;
				t = py[i];
				py[i] = py[i + 1];
				py[i + 1] = t;
			}
		}
	} while (fl == 1);

	cout << "����� ��������. ��������� ������������ �� ���.\n";
	_getch();
}

void search::searchTrainNumber() { // ????? ?? ?????? ?????? (+?????????? ?? ???? ??????)
	CARD* p = new CARD[n];
	int trainNumber, j = 0, i, fl;

	cout << "������� ����� ������: ";
	cin >> trainNumber;

	if (p == NULL) {
		cout << "��� ������. \n";
		cout << "����� �� ��������. \n";
		_getch();
		return;
	}

	for (i = 0; i < n; i++) {
		if (px[i].train.number == trainNumber) {
			p[j] = px[i];
			j++;
		}
	}
	if (py != NULL) {
		delete[] py;
		k = 0;
		py = NULL;
	}
	
	try {
		py = new CARD[j];	
	}
	catch(bad_alloc) {
		throw ErrMem("��� ������", "������ ������ py", "searchTrainNumber()");
	}

	for (i = 0; i < j; i++) {
		py[i] = p[i];
	}
	k = j;
	delete[]p;

	CARD t;
	do {
		fl = 0;
		for (i = 0; i < k - 1; i++) {
			if (py[i].type > py[i + 1].type) {
				fl = 1;
				t = py[i];
				py[i] = py[i + 1];
				py[i + 1] = t;
			}
		}
	} while (fl == 1);
	cout << "����� ��������. ��������� ������������ �� ���� ������.\n";

	_getch();
}

void search::searchFullnameInfo() { // ????? ?? ??? ?????????? ? ????????????
	CARD* p = new CARD[n];
	int i, j = 0, fl;
	string fullname, init;

	cout << "������� ������� ���: ";
	cin >> fullname;
	cin >> init;
	fullname = fullname + " " + init;

	if (p == NULL) {
		cout << "��� ������.\n";
		cout << "����� �� ��������.\n";
		_getch();
		return;
	}

	for (i = 0; i < n; i++) {
		if (px[i].FIO == fullname) {
			p[j] = px[i];
			j++;
		}
	}
	if (py != NULL) {
		delete[] py;
		k = 0;
		py = NULL;
	}

	try {
		py = new CARD[j];	
	}
	catch(bad_alloc) {
		throw ErrMem("��� ������", "������ ������ py", "searchFullnameInfo()");
	}

	for (i = 0; i < j; i++) {
		py[i] = p[i];
	}
	k = j;
	delete[]p;
	cout << "����� ��������.\n";

	_getch();
}

void search::outputSearchResult() {
	int i;

	cout << "��������� ������:\n";
	cout << left;
	cout << " -----------------------------------------------------------------------\n";
	cout << " |�����|  ������� �.�.  | ����� |     �����    | �����  |     ���      |\n";
	cout << " |     |                |������ |  ����������  |        |    ������    |\n";
	cout << " -----------------------------------------------------------------------\n";

	for (i = 0; i < k; i++) {
		cout << " |" << setw(5) << i + 1 << "|" << setw(16) << py[i].FIO << "|" << setw(7) << py[i].train.number << "|" << setw(14) << py[i].train.dest << "|" << setw(2) << py[i].train.time.hour << ":" << setw(2) << py[i].train.time.min << "   " << "|" << setw(14) << py[i].type << "|" << endl;
		cout << " -----------------------------------------------------------------------\n";
	}

	_getch();
}

void search::outputSearchResultFile() {
	string file;
	ofstream fout;
	int i;

	cout << "��� �����: ";
	cin >> file;

	fout.open(file.c_str());
	if (fout.fail()) {
		throw ErrFile("�� ���������", file, "search::outputSearchResultFile");
	}

	fout << " -----------------------------------------------------------------------\n";
	fout << " |�����|  ������� �.�.  | ����� |     �����    | �����  |     ���      |\n";
	fout << " |     |                |������ |  ����������  |        |    ������    |\n";
	fout << " -----------------------------------------------------------------------\n";

	for (i = 0; i < k; i++) {
		fout << " |" << setw(5) << i + 1 << "|" << setw(16) << py[i].FIO << "|" << setw(7) << py[i].train.number << "|" << setw(14) << py[i].train.dest << "|" << setw(2) << py[i].train.time.hour << ":" << setw(2) << py[i].train.time.min << "   " << "|" << setw(14) << py[i].type << "|" << endl;
		fout << " -----------------------------------------------------------------------\n";
	}

	fout.close();
	cout << "���������� ��������� � ����� " << file << endl;

	_getch();
}

#endif
