#ifndef Card
#define Card

#include "Structs.cpp"
#include "Exception.cpp"

class sellCard {
protected:
	CARD* px;
	int n;
public:
	sellCard() : n(0), px(NULL) {}
	~sellCard() { if (px != NULL) delete[]px; }
	sellCard(sellCard& z);
	sellCard& operator=(sellCard& z);

	friend ostream& operator << (ostream& out, sellCard& z);
	friend ifstream& operator >> (ifstream& in, sellCard& z);
	friend ofstream& operator << (ofstream& out, sellCard& z);

	void inputDataFromFile();
	virtual void saveDataToFile();
	void addCard();
	void deleteCard();
	virtual void outputDataToScreen();
	void sortTrainNumber();
	void sortDestinationAlphabet();
	virtual void sortTimeDeparture();
};

#endif

