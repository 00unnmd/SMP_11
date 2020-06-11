#include <iostream>
#include <fstream>
#include "string.h"
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <locale>
#include <Windows.h>
#include <iomanip>

using namespace std;
#include "Structs.cpp"
#include "Exception.cpp"
#include "SellCard.cpp"
#include "Search.cpp"
#include "Perech.cpp"

void print(sellCard& z) {
	z.outputDataToScreen();
}

void printFile(sellCard* z) {
	z->saveDataToFile();
}

void printA(perech* p) {
	p->sellCard::outputDataToScreen();
}

void printB(perech* p) {
	p->search::outputSearchResult();
}

void printC(perech* p) {
	p->outputPerechToScreen();
}

int main() {
	sellCard* pa, * pb, * pc;
	perech* pd;
	string ch;
	int j;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	try {
		pa = pd = new perech;
		pb = new perech;
		pc = new perech;
	}
	catch (bad_alloc) {
		cout << "Нет памяти для объектов";
		return 0;
	}

	while (1) {
		cout << "1. Загрузка из файла; \n";
		cout << "2. Сохранение результатов обработки в файл; \n";
		cout << "3. Добавление записи; \n";
		cout << "4. Удаление записи; \n";
		cout << "5. Вывод на экран; \n";
		cout << "6. Числовая сортировка по номеру поезда; \n";
		cout << "7. Алфавитная сортировка по названию пункта назначения рейса; \n";
		cout << "8. Сортировка по времени отправления; \n";
		cout << endl;
		cout << "Поиски: \n";
		cout << "9. Поиск по названию пункта назначения (отсортировано по номеру поезда); \n";
		cout << "10. Поиск по типу вагона (отсортировано по ФИО); \n";
		cout << "11. Поиск по номеру поезда (отсортировано по типу вагона); \n";
		cout << "12. Поиск по ФИО информации о пассажире; \n";
		cout << "13. Вывод результатов поиска на экран; \n";
		cout << "14. Вывод результатов поиска в файл; \n";
		cout << endl;
		cout << "Перечни: \n";
		cout << "15. Перечень пунктов назначения с указанием количества поездов; \n";
		cout << "16. Перечень часов отправления с указанием числа рейсов; \n";
		cout << "17. Перечень номеров поезда с указанием числа рейсов; \n";
		cout << endl;
		cout << "18. Вывод перечней на экран \n";
		cout << "19. Вывод перечней в файл \n";
		cout << endl;
		cout << "20. Проверка конструктора копирования \n";
		cout << "21. Проверка конструктора присваивания \n";
		cout << endl;
		cout << "0. Выход из программы; \n";
		cout << endl;

		try {
			cout << endl << "Ваш выбор (1-21): ";
			try {
				cin >> j;
				if (cin.fail()) throw Err("Это не пункт меню", "main");
			}
			catch (Err& ex) {
				cin.clear();
				do { cin >> ch; } while (cin.fail()); throw;
			}
			cout << endl;
			switch (j)
			{
			case 1: {
				pa->inputDataFromFile();
				break;
			}

			case 2: {
				pa->sellCard::saveDataToFile();
				break;
			}
			case 3: pa->addCard(); break;
			case 4: pa->deleteCard(); break;
			case 5: {
				pa->sellCard::outputDataToScreen();
				break;
			}
			case 6: pa->sortTrainNumber(); break;
			case 7: pa->sortDestinationAlphabet(); break;
			case 8: pa->sellCard::sortTimeDeparture(); break;

			case 9: ((search*)pa)->searchDestinationName(); break;
			case 10: ((search*)pa)->searchCarriageType(); break;
			case 11: ((search*)pa)->searchTrainNumber(); break;
			case 12: {
				((search*)pa)->searchFullnameInfo();
				break;
			}
			case 13: {
				pd->search::outputSearchResult();
				break;
			}
			case 14: {
				pd->search::outputSearchResultFile();
				break;
			}

			case 15: {
				((perech*)pa)->makeDestinationPerech();
				break;
			}

			case 16: {
				((perech*)pa)->makeDepartureTimePerech();
				break;
			}

			case 17: {
				((perech*)pa)->makeTrainNumberPerech();
				break;
			}
			case 18: {
				pd->perech::outputPerechToScreen();
				break;
			}
			case 19: {
				pd->perech::outputPerechToFile();
				break;
			}

			case 20: {

				perech c(*pd);
				printA(pd);
				printA(&c);

				printB(pd);
				printB(&c);

				printC(pd);
				printC(&c);

				break;
			}
			case 21: {
				perech a, b;
				a = b = *pd;
				printA(pd); printA(&b); printA(&a);
				printB(pd); printB(&b); printB(&a);
				printC(pd); printC(&b); printC(&a);
				break;
			}

			case 0: {
				delete pa;
				delete pb;
				delete pc;
				delete pd;
				cout << "Завершение работы";
				_getch();
				return 0;
				break;
			}
			default: throw Err("Нет такого пункта меню", "main");
				_getch();
			}
		}
		catch (Err& ex) {
			ex.ErrOutput();
			_getch();
		}
		catch (...) {
			cout << "Непредусмотренное исключение.\n";
			_getch();
		}
	}
	return 0;
}

