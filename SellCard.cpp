#ifndef pCARD
#define pCARD

#include "Structs.cpp"
#include "Exception.cpp"
#include "SellCard.h"

sellCard :: sellCard(sellCard& z) {
			n = z.n;

			if (n == 0) {
				px = NULL;
			}
			else {
				px = new CARD[n];
				if (px == NULL) {
					cout << "Нет памяти.\n";
					_getch();
					exit(1); 
				}
				for (int i = 0; i < n; i++) {
					px[i] = z.px[i];
				}
			}

			cout << "Конструктор копирования.\n";
		}

sellCard& sellCard::operator=(sellCard& z) {
	if (this == &z) return *this;

	if (n == z.n) {
		for (int i = 0; i < n; i++) {
			px[i] = z.px[i];
		}
	}
	else {
		if (px != NULL) delete[]px;

		n = z.n;
		try {
			px = new CARD[n];			
		}
		catch(bad_alloc) {
			throw ErrMem("Нет памяти", "Исходный массив px", "sellCard& sellCard::operator=(sellCard& z)");
		}

		if (px == NULL) {}
		for (int i = 0; i < n; i++) {
			px[i] = z.px[i];
		}
	}

	return *this;
}

ostream& operator<<(ostream& out, sellCard& z) {
	int i;

	out << "Проданные билеты: \n";
	out << left;
	out << " -----------------------------------------------------------------------\n";
	out << " |Номер|  Фамилия И.О.  | Номер |     Место    | Время  |     Тип      |\n";
	out << " |     |                |поезда |  назначения  |        |    вагона    |\n";
	out << " -----------------------------------------------------------------------\n";

	for (i = 0; i < z.n; i++) {
		out << " |" << setw(5) << i + 1 << "|" << setw(16) << z.px[i].FIO << "|" << setw(7) << z.px[i].train.number << "|" << setw(14) << z.px[i].train.dest << "|" << setw(2) << z.px[i].train.time.hour << ":" << setw(2) << z.px[i].train.time.min << "   " << "|" << setw(14) << z.px[i].type << "|" << endl;
		out << " -----------------------------------------------------------------------\n";
	}

	_getch();
	return out;
}

ifstream& operator>>(ifstream& in, sellCard& z) {
	CARD t;
	string file, init;
	int i;

	cout << "Имя входного файла: ";
	cin >> file;
	in.open(file.c_str());
	if (in.fail()) {
		throw ErrFile("Не открывается", file, "Перегруженная операция ввода для sellCard");
	}

	z.n = 0;
	if (z.px != NULL) delete[] z.px;
	while (1) {
		in >> t.FIO >> init >> t.train.number >> t.train.dest >> t.train.time.hour >> t.train.time.min >> t.type;
		if (!in) break;
		z.n++;
	}
	in.close();
	
	try {
		z.px = new CARD[z.n];
	}
	catch(bad_alloc) {
		throw ErrMem("Нет памяти", "исходный массив z.px", "Перегруженная операция ввода для sellCard");
	}

	in.open(file.c_str());
	if (in.fail()) {
		cout << file << "Повторно не открывается.\n";
		_getch();
		delete[] z.px;
		z.n = 0;
		z.px = NULL;
		exit(0);
	}

	for (i = 0; i < z.n; i++) {
		in >> z.px[i].FIO >> init >> z.px[i].train.number >> z.px[i].train.dest >> z.px[i].train.time.hour >> z.px[i].train.time.min >> z.px[i].type;
		z.px[i].FIO = z.px[i].FIO + " " + init;
	}
	cout << "Файл введен.\n";
	_getch();
	return in;
}

ofstream& operator<<(ofstream& out, sellCard& z) {
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

	out << " -----------------------------------------------------------------------\n";
	out << " |Номер|  Фамилия И.О.  | Номер |     Место    | Время  |     Тип      |\n";
	out << " |     |                |поезда |  назначения  |        |    вагона    |\n";
	out << " -----------------------------------------------------------------------\n";

	for (i = 0; i < z.n; i++) {
		out << " |" << setw(5) << i + 1 << "|" << setw(16) << z.px[i].FIO << "|" << setw(7) << z.px[i].train.number << "|" << setw(14) << z.px[i].train.dest << "|" << setw(2) << z.px[i].train.time.hour << ":" << setw(2) << z.px[i].train.time.min << "   " << "|" << setw(14) << z.px[i].type << "|" << endl;
		out << " ------------------------------------------------------------------------\n";
	}
	out.close();
	cout << "Результаты сохранены в файл " << file << endl;

	_getch();
}

void sellCard::inputDataFromFile() { //??????? ?? ?????
	ifstream fin;
	CARD t;
	string file, init;
	int i, y;

	cout << "Имя входного файла: ";
	cin >> file;
	fin.open(file.c_str()); //?????? ??????
	if (fin.fail()) {
		throw ErrFile("Не открывается", file, "inputDataFromFile");
	}

	n = 0;
	if (px != NULL) delete[] px;
	while (1) {
		fin >> t.FIO >> init >> t.train.number >> t.train.dest >> t.train.time.hour >> t.train.time.min >> t.type;
		if (!fin) break;
		n++;
	}
	fin.close();

	try {
		px = new CARD[n];
	}
	catch(bad_alloc) {
		throw ErrMem("Нет памяти", "исходный массив px", "inputDataFromFile");
	}

	fin.open(file.c_str()); //?????? ??????
	if (fin.fail()) {
		cout << file << "Повторно не открывается.\n";
		_getch();
		delete[] px;
		n = 0;
		px = NULL;
		return;
	}
	for (i = 0; i < n; i++) {
		fin >> px[i].FIO >> init >> px[i].train.number >> px[i].train.dest >> px[i].train.time.hour >> px[i].train.time.min >> px[i].type;
		px[i].FIO = px[i].FIO + " " + init;
	}

	cout << "Файл введен.\n";
	_getch();
}

void sellCard::saveDataToFile() { //????????? ? ????
	string file;
	ofstream fout;
	int i;

	cout << "Имя выходного файла: ";
	cin >> file;
	fout.open(file.c_str()); //??????
	if (fout.fail()) {
		throw ErrFile("Не создается", file, "sellCard::saveDataToFile");
	}

	fout << " -----------------------------------------------------------------------\n";
	fout << " |Номер|  Фамилия И.О.  | Номер |     Место    | Время  |     Тип      |\n";
	fout << " |     |                |поезда |  назначения  |        |    вагона    |\n";
	fout << " -----------------------------------------------------------------------\n";

	for (i = 0; i < n; i++) {
		fout << " |" << setw(5) << i + 1 << "|" << setw(16) << px[i].FIO << "|" << setw(7) << px[i].train.number << "|" << setw(14) << px[i].train.dest << "|" << setw(2) << px[i].train.time.hour << ":" << setw(2) << px[i].train.time.min << "   " << "|" << setw(14) << px[i].type << "|" << endl;
		fout << " ------------------------------------------------------------------------\n";
	}
	fout.close();
	cout << "Результаты сохранены в файл " << file << endl;
	_getch();
}

void sellCard::addCard() { //???????? ????? ??????(??????)
	CARD t, * p;
	int i;
	string init;
	
	try {
		p = new CARD[n + 1];
		if (p == NULL) {
			cout << "Нет памяти. Добавление не выполнено.";
			_getch();
			return;
		}
	
		cout << "ФИО: "; 
		cin >> t.FIO;
		cin >> init;
		t.FIO = t.FIO + " " + init;
		cout << "Номер поезда: "; cin >> t.train.number;
		cout << "Место назначения: "; cin >> t.train.dest;
		cout << "Время: "; cin >> t.train.time.hour; cin >> t.train.time.min;
		cout << "Тип вагона: "; cin >> t.type;
	
		for (i = 0; i < n; i++) {
			p[i] = px[i];
		}
		p[n] = t;
		if (px != NULL) delete[]px;
		px = p;
		n++;
	}
	catch(bad_alloc) {
		throw ErrMem("Нет памяти", "исходный массив px", "addCard()");
	}
	
	cout << "Запись добавлена.\n";
	_getch();
}

void sellCard::deleteCard() { //??????? ??????(??????)
	int i, j;
	string ch;
	CARD* p;

	sellCard::outputDataToScreen();

	cout << "Номер удаляемой строки: ";
	
	try {
		cin >> j;
		if (cin.fail()) {
			Err("Это не номер строки", "deleteCard");
		}
	}
	catch(string ex) {
		cin.clear();
		do {
			cin >> ch;
		}
		while (cin.fail());
		throw;
	}
	
	if((j < 1) || (j > n)) {
		throw Err("Нет такой строки", "deleteCard");
	}
	
	j--;

	cout << "Удаляемая строка: \n";
	cout << left;
	cout << " -----------------------------------------------------------------------\n";
	cout << " |Номер|  Фамилия И.О.  | Номер |     Место    | Время  |     Тип      |\n";
	cout << " |     |                |поезда |  назначения  |        |    вагона    |\n";
	cout << " -----------------------------------------------------------------------\n";
	cout << " |" << setw(5) << j + 1 << "|" << setw(16) << px[j].FIO << "|" << setw(7) << px[j].train.number << "|" << setw(14) << px[j].train.dest << "|" << setw(2) << px[j].train.time.hour << ":" << setw(2) << px[j].train.time.min << "   " << "|" << setw(14) << px[j].type << "|" << endl;
	cout << " |---------------------------------------------------------------------|" << endl;
	cout << "Удалить? (y/n)";
	cin >> ch;
	
	if (ch == "n") {
		throw Err("Это не та строка", "deleteCard");
	}
	if (ch != "y") {
		throw Err("Ответ ни да, ни нет", "deleteCard");
	}
	
	if (n == 1) {
		delete[] px;
		px = NULL;
		n = 0;
	}
	else {
		try {
			p = new CARD[n - 1];
		}
		catch(bad_alloc) {
			throw ErrMem("Нет памяти", "рабочий массив p", "deleteCard()");
		}
		
		for (i = 0; i < j; i++) {
			p[i] = px[i];
		}
		for (i = j + 1; i < n; i++) {
			p[i - 1] = px[i];
		}
		delete[]px;
		px = p;
		n--;
		
		cout << "Запись удалена.";
		_getch();
	}
}

void sellCard::outputDataToScreen() { //??????? ?????? ?? ?????
	int i;

	cout << "Проданные файлы:\n";
	cout << left;
	cout << " -----------------------------------------------------------------------\n";
	cout << " |Номер|  Фамилия И.О.  | Номер |     Место    | Время  |     Тип      |\n";
	cout << " |     |                |поезда |  назначения  |        |    вагона    |\n";
	cout << " -----------------------------------------------------------------------\n";

	for (i = 0; i < n; i++) {
		cout << " |" << setw(5) << i + 1 << "|" << setw(16) << px[i].FIO << "|" << setw(7) << px[i].train.number << "|" << setw(14) << px[i].train.dest << "|" << setw(2) << px[i].train.time.hour << ":" << setw(2) << px[i].train.time.min << "   " << "|" << setw(14) << px[i].type << "|" << endl;
		cout << " -----------------------------------------------------------------------\n";
	}

	_getch();
}

void sellCard::sortTrainNumber() { // ???????? ?????????? ?? ?????? ??????
	int i, fl;
	CARD t;

	do {
		fl = 0;
		for (i = 0; i < n - 1; i++) {
			if (px[i].train.number > px[i + 1].train.number) {
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
		}
	} while (fl == 1);

	cout << "Успешно отсортировано.\n";
	_getch();
}

void sellCard::sortDestinationAlphabet() { //?????????? ?????????? ?? ???????? ?????? ?????????? ?????
	int i, fl;
	CARD t;

	do {
		fl = 0;
		for (i = 0; i < n - 1; i++) {
			if (px[i].train.dest > px[i + 1].train.dest) {
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
		}
	} while (fl == 1);
	cout << "Успешно отсортировано.\n";
	_getch();
}

int timeDepartureHelper(CARD V, CARD W) {
	if (V.train.time.hour > W.train.time.hour) return 1;
	if (V.train.time.hour < W.train.time.hour) return -1;
	if (V.train.time.min > W.train.time.min) return 1;
	if (V.train.time.min < W.train.time.min) return -1;
	return 0;
}
void sellCard::sortTimeDeparture() { // ?????????? ?? ??????? ???????????
	int i, fl;
	CARD t;

	do {
		fl = 0;
		for (i = 0; i < n - 1; i++) {
			if (timeDepartureHelper(px[i], px[i + 1]) > 0) {
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
		}
	} while (fl == 1);

	cout << "Успешно отсортировано. \n";
	_getch();
}

#endif
