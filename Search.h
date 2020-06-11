#ifndef Search
#define Search

#include "Structs.cpp"
#include "Exception.cpp"

class search : public sellCard {
protected:
	CARD* py;
	int k;
public:
	search() : k(0), py(NULL) {}
	~search() { if (py != NULL) delete[]py; }
	search(search& z);

	search& operator=(search& z);

	friend ostream& operator<<(ostream& out, search& z);
	friend ofstream& operator<<(ofstream& out, search& z);

	void searchDestinationName();
	void searchCarriageType();
	void searchTrainNumber();
	void searchFullnameInfo();
	void outputSearchResult();
	void outputSearchResultFile();
};

#endif
