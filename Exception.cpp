#ifndef pExc
#define pExc

class Err {
	protected:
		string message1;
		string message2;
	public:
		Err(string mes10, string mes20) : message1(mes10), message2(mes20) { };
		virtual void ErrOutput();
};

class ErrFile : public Err {
	protected:
		string message3;
	public:
		ErrFile(string mes10, string mes20, string mes30) : Err(mes10, mes20), message3(mes30) { };
		void ErrOutput();
};

class ErrMem : public ErrFile {
	public:
		ErrMem(string mes10, string mes20, string mes30) : ErrFile(mes10, mes20, mes30) { };
		void ErrOutput();
};

void Err::ErrOutput() {
	cout << "������: " << message1 << endl << "� �������: " << message2 << endl;
}

void ErrFile::ErrOutput() {
	cout << "������: " << message1 <<  endl << "��������� ��� ������ � ������: " << message2 <<  endl << "� ������: " << message3 <<  endl;
}

void ErrMem::ErrOutput() {
	cout << "������: " << message1 <<  endl << "��� ��������� ������ ���: " << message2 <<  endl << "� ������: " << message3 <<  endl;
}

#endif
