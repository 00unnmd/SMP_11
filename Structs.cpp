#ifndef pstruct
#define pstruct

struct TIME {
	int hour;
	int min;
};
struct TRAIN {
	string dest;
	int number;
	TIME time;
};
struct CARD {
	TRAIN train;
	string FIO;
	string type;
};

struct PERECH_DESTINATION {
	string destination;
	int trainCount;
};
struct PERECH_DEPARTURE_TIME {
	TIME departureTime;
	int tripNumber;
};
struct PERECH_TRAIN_NUMBER {
	int trainNumber;
	int tripCount;
};

#endif
