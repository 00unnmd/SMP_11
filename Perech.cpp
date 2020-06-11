#ifndef pPerech
#define pPerech

#include "Structs.cpp"
#include "Exception.cpp"
#include "Perech.h"

perech::perech(perech& z) try: search(z) {
	DS = z.DS;
	if (DS == 0) {
		a = NULL;
	}
	else {
		try {
			a = new PERECH_DESTINATION[DS];
		}
		catch (bad_alloc) {
			throw 3;
		}
		for (int j = 0; j < DS; j++) {
			a[j] = z.a[j];
		}
	}

	DT = z.DT;
	if (DT == 0) {
		b = NULL;
	}
	else {
		try {
			b = new PERECH_DEPARTURE_TIME[DT];
		}
		catch(bad_alloc) {
			throw 4;
		}
		for (int j = 0; j < DT; j++) {
			b[j] = z.b[j];
		}
	}

	TN = z.TN;
	if (TN == 0) {
		c = NULL;
	}
	else {
		try {
			c = new PERECH_TRAIN_NUMBER[TN];
		}
		catch(bad_alloc) {
			throw 5;
		}
		for (int j = 0; j < TN; j++) {
			c[j] = z.c[j];
		}
	}
}
catch (int m) {
	if (m == 1) throw ErrMem("��� ������", "�������� ������ px", "sellCard(sellCard & z)");
	if (m == 2) throw ErrMem("��� ������", "������ ������ py", "search(search & z)");
	if (m == 3) throw ErrMem("��� ������", "������ ������� a", "perech(perech &z)");
	if (m == 4) throw ErrMem("��� ������", "������ ������� b", "perech(perech &z)");
	if (m == 5) throw ErrMem("��� ������", "������ ������� c", "perech(perech &z)");
	throw string("����������� ����������");
}

perech& perech::operator=(perech& z) {
	search::operator=(z);

	// PERECH_DESTINATION
	if (DS == z.DS) {
		for (int j = 0; j < DS; j++) {
			a[j] = z.a[j];
		}
	}
	else {
		if (a != NULL) delete[] a;
		DS = z.DS;

		try {
			a = new PERECH_DESTINATION[DS];
		}
		catch(bad_alloc) {
			throw ErrMem("��� ������", "������ ������� a", "perech& operator=(perech &z)");
		}

		if (a == NULL) {} //?????????? ????????
		for (int j = 0; j < DS; j++) {
			a[j] = z.a[j];
		}
	}

	// PERECH_DEPARTURE_TIME
	if (DT == z.DT) {
		for (int j = 0; j < DT; j++) {
			b[j] = z.b[j];
		}
	}
	else {
		if (b != NULL) delete[] b;
		DT = z.DT;
		
		try {
			b = new PERECH_DEPARTURE_TIME[DT];
		}
		catch(bad_alloc) {
			throw ErrMem("��� ������", "������ ������� b", "perech& operator=(perech &z)");
		}

		if (b == NULL) {} //?????????? ????????
		for (int j = 0; j < DT; j++) {
			b[j] = z.b[j];
		}
	}

	// PERECH_TRAIN_NUMBER
	if (TN == z.TN) {
		for (int j = 0; j < TN; j++) {
			c[j] = z.c[j];
		}
	}
	else {
		if (c != NULL) delete[] c;
		TN = z.TN;

		try {
			c = new PERECH_TRAIN_NUMBER[TN];
		}
		catch(bad_alloc) {
			throw ErrMem("��� ������", "������ ������� c", "perech& operator=(perech &z)");
		}

		if (c == NULL) {} //?????????? ????????
		for (int j = 0; j < TN; j++) {
			c[j] = z.c[j];
		}
	}

	return *this;
}

ostream& operator << (ostream& out, perech& z) {
	int i;

	// PERECH_DESTINATION
	out << endl;
	out << "�������� ������� ����������:\n";
	out << left;
	out << " -------------------------------------\n";
	out << " |�����|      �����     | ���������� |\n";
	out << " |     |   ����������   |   �������  |\n";
	out << " -------------------------------------\n";

	for (i = 0; i < z.DS; i++) {
		out << " |" << setw(5) << i + 1 << "|" << setw(16) << z.a[i].destination << "|" << setw(12) << z.a[i].trainCount << "|" << endl;
		out << " -------------------------------------\n";

	}

	// PERECH_DEPARTURE_TIME
	out << endl;
	out << "�������� ����� �����������:\n";
	out << left;
	out << " ----------------------------\n";
	out << " |�����|   ����    | �����  |\n";
	out << " |     |�����������| ������ |\n";
	out << " ----------------------------\n";

	for (i = 0; i < z.DT; i++) {
		out << " |" << setw(5) << i + 1 << "|" << setw(2) << z.b[i].departureTime.hour << ":" << setw(2) << z.b[i].departureTime.min << "      " << "|" << setw(8) << z.b[i].tripNumber << "|" << endl;
		out << " ----------------------------\n";

	}

	// PERECH_TRAIN_NUMBER
	out << endl;
	out << "�������� ������� ������:\n";
	out << left;
	out << " -------------------------\n";
	out << " |�����| �����  | �����  |\n";
	out << " |     | ������ | ������ |\n";
	out << " -------------------------\n";

	for (i = 0; i < z.TN; i++) {
		out << " |" << setw(5) << i + 1 << "|" << setw(8) << z.c[i].trainNumber << "|" << setw(8) << z.c[i].tripCount << "|" << endl;
		out << " -------------------------\n";
	}

	_getch();
	return out;
}

ofstream& operator << (ofstream& out, perech& z) {
	string file;
	int i;

	cout << "������� ��� �����: ";
	cin >> file;
	out.open(file.c_str());

	if (out.fail()) {
		cout << "���� " << file << " �� ������.\n";
		_getch();
		exit(0);
	}

	// PERECH_DESTINATION
	out << "�������� ������� ����������:\n";
	out << left;
	out << " -------------------------------------\n";
	out << " |�����|      �����     | ���������� |\n";
	out << " |     |   ����������   |   �������  |\n";
	out << " -------------------------------------\n";

	for (i = 0; i < z.DS; i++) {
		out << " |" << setw(5) << i + 1 << "|" << setw(16) << z.a[i].destination << "|" << setw(12) << z.a[i].trainCount << "|" << endl;
		out << " -------------------------------------\n";
	}

	// PERECH_DEPARTURE_TIME
	out << endl;
	out << "�������� ����� �����������:\n";
	out << left;
	out << " ----------------------------\n";
	out << " |�����|   ����    | �����  |\n";
	out << " |     |�����������| ������ |\n";
	out << " ----------------------------\n";

	for (i = 0; i < z.DT; i++) {
		out << " |" << setw(5) << i + 1 << "|" << setw(2) << z.b[i].departureTime.hour << ":" << setw(2) << z.b[i].departureTime.min << "      " << "|" << setw(8) << z.b[i].tripNumber << "|" << endl;
		out << " ----------------------------\n";
	}

	// PERECH_TRAIN_NUMBER
	out << endl;
	out << "�������� ������� ������:\n";
	out << left;
	out << " -------------------------\n";
	out << " |�����| �����  | �����  |\n";
	out << " |     | ������ | ������ |\n";
	out << " -------------------------\n";
	for (i = 0; i < z.TN; i++) {
		out << " |" << setw(5) << i + 1 << "|" << setw(8) << z.c[i].trainNumber << "|" << setw(8) << z.c[i].tripCount << "|" << endl;
		out << " -------------------------\n";
	}
	cout << "���������� ��������� � ���� " << file << endl;

	_getch();
}

void perech::makeDestinationPerech() {
	PERECH_DESTINATION* h;
	int fl, i, j;

	try {
		h = new PERECH_DESTINATION[n];
	}
	catch(bad_alloc) {
		throw ErrMem("��� ������", "������� ������ h", "makeDestinationPerech()");
	}

	DS = 0;
	for (i = 0; i < n; i++) {
		fl = 0;
		for (j = 0; j < DS; j++) {
			if (px[i].train.dest == h[j].destination) {
				fl = 1;
				h[j].trainCount++;
			}
		}
		if (fl == 0) {
			h[DS].destination = px[i].train.dest;
			h[DS].trainCount = 1;
			DS++;
		}
	}
	
	try {
		a = new PERECH_DESTINATION[DS];
	}
	catch(bad_alloc) {
		delete[] h;
		DS = 0;
		throw ErrMem("��� ������", "������ ������� a", "makeDestinationPerech()");
	}

	for (j = 0; j < DS; j++) {
		a[j] = h[j];
	}

	delete[] h;
	cout << "�������� ������.\n";

	sortDestinationPerech();

	_getch();
}

void perech::sortDestinationPerech() {
	PERECH_DESTINATION t;
	int i, fl, nn = DS;

	do {
		fl = 0;
		nn--;

		for (i = 0; i < nn; i++) {
			if (a[i].destination > a[i + 1].destination) {
				fl = 1;
				t = a[i];
				a[i] = a[i + 1];
				a[i + 1] = t;
			}
		}
	} while (fl == 1);
}

void perech::outputDestinationPerech() {
	cout << "�������� ������� ����������:\n";
	cout << left;
	cout << " -------------------------------------\n";
	cout << " |�����|      �����     | ���������� |\n";
	cout << " |     |   ����������   |   �������  |\n";
	cout << " -------------------------------------\n";

	for (int i = 0; i < DS; i++) {
		cout << " |" << setw(5) << i + 1 << "|" << setw(16) << a[i].destination << "|" << setw(12) << a[i].trainCount << "|" << endl;
		cout << " -------------------------------------\n";
	}

	_getch();
}

void perech::outputDestinationPerechFile() {
	string file;
	ofstream fout;

	cout << "������� ��� �����: ";
	cin >> file;

	fout.open(file.c_str());
	if (fout.fail()) {
		cout << file << " �� ������\n";
		_getch();
		return;
	}

	fout << "�������� ������� ����������:\n";
	fout << left;
	fout << " -------------------------------------\n";
	fout << " |�����|      �����     | ���������� |\n";
	fout << " |     |   ����������   |   �������  |\n";
	fout << " -------------------------------------\n";

	for (int i = 0; i < DS; i++) {
		fout << " |" << setw(5) << i + 1 << "|" << setw(16) << a[i].destination << "|" << setw(12) << a[i].trainCount << "|" << endl;
		fout << " -------------------------------------\n";
	}
	fout.close();

	_getch();
}

int departureTimePerechHelper(TIME A, TIME B) {
	if (A.hour > B.hour) return 1;
	if (A.hour < B.hour) return -1;
	if (A.min > B.min) return 1;
	if (A.min < B.min) return -1;
	return 0;
}
void perech::makeDepartureTimePerech() {
	PERECH_DEPARTURE_TIME* h;
	int i, j, fl;

	try {
		h = new PERECH_DEPARTURE_TIME[n];
	}
	catch(bad_alloc) {
		throw ErrMem("��� ������", "������� ������ h", "makeDepartureTimePerech()");
	}

	DT = 0;
	for (i = 0; i < n; i++) {
		fl = 0;
		for (j = 0; j < DT; j++) {
			if (departureTimePerechHelper(px[i].train.time, h[j].departureTime) == 0) {
				fl = 1;
				h[j].tripNumber++;
			}
		}
		if (fl == 0) {
			h[DT].departureTime = px[i].train.time;
			h[DT].tripNumber = 1;
			DT++;
		}
	}
	
	try {
		b = new PERECH_DEPARTURE_TIME[DT];
	}
	catch(bad_alloc) {
		delete[] h;
		DT = 0;
		throw ErrMem("��� ������", "������ ������� b", "makeDepartureTimePerech()");
	}

	for (j = 0; j < DT; j++) {
		b[j] = h[j];
	}
	delete[] h;
	cout << "�������� ������. \n";

	sortDepartureTimePerech();

	_getch();
}

void perech::sortDepartureTimePerech() {
	PERECH_DEPARTURE_TIME t;
	int i, fl, nn = DT;

	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++) {
			if (departureTimePerechHelper(b[i].departureTime, b[i + 1].departureTime) > 0) {
				fl = 1;
				t = b[i];
				b[i] = b[i + 1];
				b[i + 1] = t;
			}
		}
	} while (fl == 1);
}

void perech::outputDepartureTimePerech() {
	cout << "�������� ����� �����������:\n";
	cout << left;
	cout << " ----------------------------\n";
	cout << " |�����|   ����    | �����  |\n";
	cout << " |     |�����������| ������ |\n";
	cout << " ----------------------------\n";

	for (int i = 0; i < DT; i++) {
		cout << " |" << setw(5) << i + 1 << "|" << setw(2) << b[i].departureTime.hour << ":" << setw(2) << b[i].departureTime.min << "      " << "|" << setw(8) << b[i].tripNumber << "|" << endl;;
		cout << " ----------------------------\n";
	}

	_getch();
}

void perech::outputDepartureTimePerechFile() {
	string file;
	ofstream fout;

	cout << "������� ��� �����: ";
	cin >> file;

	fout.open(file.c_str());
	if (fout.fail()) {
		cout << "���� " << file << " �� ������. \n";
		_getch();
		return;
	}
	
	fout << "�������� ����� �����������:\n";
	fout << left;
	fout << " ----------------------------\n";
	fout << " |�����|   ����    | �����  |\n";
	fout << " |     |�����������| ������ |\n";
	fout << " ----------------------------\n";

	for (int i = 0; i < DT; i++) {
		fout << " |" << setw(5) << i + 1 << "|" << setw(2) << b[i].departureTime.hour << ":" << setw(2) << b[i].departureTime.min << "      " << "|" << setw(8) << b[i].tripNumber << "|" << endl;
		fout << " ----------------------------\n";
	}

	_getch();
}

void perech::makeTrainNumberPerech() {
	PERECH_TRAIN_NUMBER* h;
	int i, j, fl;

	try {
		h = new PERECH_TRAIN_NUMBER[n];
	}
	catch(bad_alloc) {
		throw ErrMem("��� ������", "������� ������ h", "makeTrainNumberPerech()");
	}

	TN = 0;
	for (i = 0; i < n; i++) {
		fl = 0;
		for (j = 0; j < TN; j++) {
			if (px[i].train.number == h[j].trainNumber) {
				fl = 1;
				h[j].tripCount++;
			}
		}
		if (fl == 0) {
			h[TN].trainNumber = px[i].train.number;
			h[TN].tripCount = 1;
			TN++;
		}
	}
	
	try {
		c = new PERECH_TRAIN_NUMBER[TN];
	}
	catch(bad_alloc) {
		delete[] h;
		TN = 0;
		throw ErrMem("��� ������", "������ ������� c", "makeTrainNumberPerech()");
	}

	for (j = 0; j < TN; j++) {
		c[j] = h[j];
	}
	delete[] h;
	cout << "�������� ������. \n";

	sortTrainNumberPerech();

	_getch();
}

void perech::sortTrainNumberPerech() {
	PERECH_TRAIN_NUMBER t;
	int i, fl, nn = TN;

	do {
		fl = 0;
		nn--;
		for (i = 0; i < nn; i++) {
			if (c[i].trainNumber > c[i + 1].trainNumber) {
				fl = 1;
				t = c[i];
				c[i] = c[i + 1];
				c[i + 1] = t;
			}
		}
	} while (fl == 1);
}

void perech::outputTrainNumberPerech() {
	cout << "�������� ������� ������:\n";
	cout << left;
	cout << " -------------------------\n";
	cout << " |�����| �����  | �����  |\n";
	cout << " |     | ������ | ������ |\n";
	cout << " -------------------------\n";

	for (int i = 0; i < TN; i++) {
		cout << " |" << setw(5) << i + 1 << "|" << setw(8) << c[i].trainNumber << "|" << setw(8) << c[i].tripCount << "|" << endl;;
		cout << " -------------------------\n";
	}

	_getch();
}

void perech::outputTrainNumberPerechFile() {
	string file;
	ofstream fout;

	cout << "������� ��� �����: ";
	cin >> file;

	fout.open(file.c_str());
	if (fout.fail()) {
		cout << "���� " << file << " �� ������.\n";
		_getch();
		return;
	}

	fout << "�������� ������� ������:\n";
	fout << left;
	fout << " -------------------------\n";
	fout << " |�����| �����  | �����  |\n";
	fout << " |     | ������ | ������ |\n";
	fout << " -------------------------\n";

	for (int i = 0; i < TN; i++) {
		fout << " |" << setw(5) << i + 1 << "|" << setw(8) << c[i].trainNumber << "|" << setw(8) << c[i].tripCount << "|" << endl;
		fout << " -------------------------\n";
	}

	_getch();
}

void perech::outputPerechToScreen() {
	cout << "�������� ������� ����������:\n";
	cout << left;
	cout << " -------------------------------------\n";
	cout << " |�����|      �����     | ���������� |\n";
	cout << " |     |   ����������   |   �������  |\n";
	cout << " -------------------------------------\n";

	for (int i = 0; i < DS; i++) {
		cout << " |" << setw(5) << i + 1 << "|" << setw(16) << a[i].destination << "|" << setw(12) << a[i].trainCount << "|" << endl;
		cout << " -------------------------------------\n";
	}

	cout << "�������� ����� �����������:\n";
	cout << left;
	cout << " ----------------------------\n";
	cout << " |�����|   ����    | �����  |\n";
	cout << " |     |�����������| ������ |\n";
	cout << " ----------------------------\n";

	for (int i = 0; i < DT; i++) {
		cout << " |" << setw(5) << i + 1 << "|" << setw(2) << b[i].departureTime.hour << ":" << setw(2) << b[i].departureTime.min << "      " << "|" << setw(8) << b[i].tripNumber << "|" << endl;;
		cout << " ----------------------------\n";
	}

	cout << "�������� ������� ������:\n";
	cout << left;
	cout << " -------------------------\n";
	cout << " |�����| �����  | �����  |\n";
	cout << " |     | ������ | ������ |\n";
	cout << " -------------------------\n";

	for (int i = 0; i < TN; i++) {
		cout << " |" << setw(5) << i + 1 << "|" << setw(8) << c[i].trainNumber << "|" << setw(8) << c[i].tripCount << "|" << endl;;
		cout << " -------------------------\n";
	}
}

void perech::outputPerechToFile() {
	string file;
	ofstream fout;

	cout << "������� ��� �����: ";
	cin >> file;

	fout.open(file.c_str());
	if (fout.fail()) {
		throw ErrFile("�� ���������", file, "perech::outputPerechToFile");
	}

	fout << "�������� ������� ����������:\n";
	fout << left;
	fout << " -------------------------------------\n";
	fout << " |�����|      �����     | ���������� |\n";
	fout << " |     |   ����������   |   �������  |\n";
	fout << " -------------------------------------\n";

	for (int i = 0; i < DS; i++) {
		fout << " |" << setw(5) << i + 1 << "|" << setw(16) << a[i].destination << "|" << setw(12) << a[i].trainCount << "|" << endl;
		fout << " -------------------------------------\n";
	}

	fout << "�������� ����� �����������:\n";
	fout << left;
	fout << " ----------------------------\n";
	fout << " |�����|   ����    | �����  |\n";
	fout << " |     |�����������| ������ |\n";
	fout << " ----------------------------\n";

	for (int i = 0; i < DT; i++) {
		fout << " |" << setw(5) << i + 1 << "|" << setw(2) << b[i].departureTime.hour << ":" << setw(2) << b[i].departureTime.min << "      " << "|" << setw(8) << b[i].tripNumber << "|" << endl;
		fout << " ----------------------------\n";
	}

	fout << "�������� ������� ������:\n";
	fout << left;
	fout << " -------------------------\n";
	fout << " |�����| �����  | �����  |\n";
	fout << " |     | ������ | ������ |\n";
	fout << " -------------------------\n";

	for (int i = 0; i < TN; i++) {
		fout << " |" << setw(5) << i + 1 << "|" << setw(8) << c[i].trainNumber << "|" << setw(8) << c[i].tripCount << "|" << endl;
		fout << " -------------------------\n";
	}

	_getch();
}

#endif
