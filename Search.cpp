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
	cout << "Конструктор копирования.\n";
}

search& search::operator=(search& z) {
	sellCard::operator=(z);

	if (this == &z) return z;
	k = z.k;
	
	try {
		py = new CARD[k];
	}
	catch(bad_alloc) {
		throw ErrMem("Нет памяти", "Массив поиска py", "search& operator=(search &z)");
	}

	for (int j = 0; j < k; j++) {
		py[j] = z.py[j];
	}
}

ostream& operator << (ostream& out, search& z) {
	int i;

	out << "Проданные билеты:\n";
	out << left;
	out << " -----------------------------------------------------------------------\n";
	out << " |Номер|  Фамилия И.О.  | Номер |     Место    | Время  |     Тип      |\n";
	out << " |     |                |поезда |  назначения  |        |    вагона    |\n";
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

	cout << "Имя выходного файла: ";
	cin >> file;
	out.open(file.c_str()); //????? ?????? ?????? ??????-??????
	if (out.fail()) {
		cout << "Файл " << file << " не создан.\n";
		_getch();
		exit(0);
	}

	cout << left;
	out << " -----------------------------------------------------------------------\n";
	out << " |Номер|  Фамилия И.О.  | Номер |     Место    | Время  |     Тип      |\n";
	out << " |     |                |поезда |  назначения  |        |    вагона    |\n";
	out << " -----------------------------------------------------------------------\n";

	for (i = 0; i < z.k; i++) {
		out << " |" << setw(5) << i + 1 << "|" << setw(16) << z.py[i].FIO << "|" << setw(7) << z.py[i].train.number << "|" << setw(14) << z.py[i].train.dest << "|" << setw(2) << z.py[i].train.time.hour << ":" << setw(2) << z.py[i].train.time.min << "   " << "|" << setw(14) << z.py[i].type << "|" << endl;
		out << " ------------------------------------------------------------------------\n";
	}
	out.close();
	cout << "Результаты сохранены в файл " << file << endl;

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

	cout << "Введите искомый пункт назначения: ";
	cin >> destination;

	if (p == NULL) {
		cout << "Нет памяти.\n";
		cout << "Поиск не выполнен.\n";
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
		throw ErrMem("Нет памяти", "массив поиска py", "searchDestinationName()");
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

	cout << "Поиск завершен. Результат отсортирован по номеру поезда.\n";
	_getch();
}

void search::searchCarriageType() { // ????? ?? ???? ?????? (+?????????? ?? ???)
	CARD* p = new CARD[n];
	string carriageType;
	int j = 0, i, fl;

	cout << "Введите тип вагона: ";
	cin >> carriageType;

	if (p == NULL) {
		cout << "Нет памяти.\n";
		cout << "Поиск не выполнен.\n";
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
		throw ErrMem("Нет памяти", "массив поиска py", "searchCarriageType()");
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

	cout << "Поиск завершен. Результат отсортирован по ФИО.\n";
	_getch();
}

void search::searchTrainNumber() { // ????? ?? ?????? ?????? (+?????????? ?? ???? ??????)
	CARD* p = new CARD[n];
	int trainNumber, j = 0, i, fl;

	cout << "Введите номер поезда: ";
	cin >> trainNumber;

	if (p == NULL) {
		cout << "Нет памяти. \n";
		cout << "Поиск не выполнен. \n";
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
		throw ErrMem("Нет памяти", "массив поиска py", "searchTrainNumber()");
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
	cout << "Поиск завершен. Результат отсортирован по типу вагона.\n";

	_getch();
}

void search::searchFullnameInfo() { // ????? ?? ??? ?????????? ? ????????????
	CARD* p = new CARD[n];
	int i, j = 0, fl;
	string fullname, init;

	cout << "Введите искомое ФИО: ";
	cin >> fullname;
	cin >> init;
	fullname = fullname + " " + init;

	if (p == NULL) {
		cout << "Нет памяти.\n";
		cout << "Поиск не выполнен.\n";
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
		throw ErrMem("Нет памяти", "массив поиска py", "searchFullnameInfo()");
	}

	for (i = 0; i < j; i++) {
		py[i] = p[i];
	}
	k = j;
	delete[]p;
	cout << "Поиск завершен.\n";

	_getch();
}

void search::outputSearchResult() {
	int i;

	cout << "Проданные билеты:\n";
	cout << left;
	cout << " -----------------------------------------------------------------------\n";
	cout << " |Номер|  Фамилия И.О.  | Номер |     Место    | Время  |     Тип      |\n";
	cout << " |     |                |поезда |  назначения  |        |    вагона    |\n";
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

	cout << "Имя файла: ";
	cin >> file;

	fout.open(file.c_str());
	if (fout.fail()) {
		throw ErrFile("Не создается", file, "search::outputSearchResultFile");
	}

	fout << " -----------------------------------------------------------------------\n";
	fout << " |Номер|  Фамилия И.О.  | Номер |     Место    | Время  |     Тип      |\n";
	fout << " |     |                |поезда |  назначения  |        |    вагона    |\n";
	fout << " -----------------------------------------------------------------------\n";

	for (i = 0; i < k; i++) {
		fout << " |" << setw(5) << i + 1 << "|" << setw(16) << py[i].FIO << "|" << setw(7) << py[i].train.number << "|" << setw(14) << py[i].train.dest << "|" << setw(2) << py[i].train.time.hour << ":" << setw(2) << py[i].train.time.min << "   " << "|" << setw(14) << py[i].type << "|" << endl;
		fout << " -----------------------------------------------------------------------\n";
	}

	fout.close();
	cout << "Результаты сохранены в файле " << file << endl;

	_getch();
}

#endif
