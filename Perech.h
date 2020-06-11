#ifndef Perech
#define Perech

#include "Structs.cpp"
#include "Exception.cpp"

class perech : public search {
protected:
	PERECH_DESTINATION* a;
	int DS;
	PERECH_DEPARTURE_TIME* b;
	int DT;
	PERECH_TRAIN_NUMBER* c;
	int TN;

public:
	perech() : DS(0), DT(0), TN(0), a(NULL), b(NULL), c(NULL) {}
	~perech() {
		if (a != NULL) delete[] a;
		if (b != NULL) delete[] b;
		if (c != NULL) delete[] c;
	}
	perech(perech& z);

	perech& operator=(perech& z);

	friend ostream& operator << (ostream& out, perech& z);
	friend ofstream& operator << (ofstream& out, perech& z);

	// PERECH_DESTINATION
	void makeDestinationPerech();
	void sortDestinationPerech();
	void outputDestinationPerech();
	void outputDestinationPerechFile();

	// PERECH_DEPARTURE_TIME
	void makeDepartureTimePerech();
	void sortDepartureTimePerech();
	void outputDepartureTimePerech();
	void outputDepartureTimePerechFile();

	// PERECH_TRAIN_NUMBER
	void makeTrainNumberPerech();
	void sortTrainNumberPerech();
	void outputTrainNumberPerech();
	void outputTrainNumberPerechFile();

	void outputPerechToScreen();
	void outputPerechToFile();
};

#endif

