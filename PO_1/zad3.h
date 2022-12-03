#ifndef zad3_h

#define zad3_h

void zad3();

class klasa1 {
public: 
	int Wymnoz(int a, int b);
};

class klasa2 : public klasa1 {
public:
	int Wymnoz(int a, int b);
};

class klasa3 {
public:
	void Wypisz();
	void Wypisz(int a);
	void Wypisz(char a);
};

#endif