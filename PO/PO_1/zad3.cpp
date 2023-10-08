#include <iostream>

#include "zad3.h"

using namespace std;

int klasa1::Wymnoz(int a, int b) {
	return a * b;
}
int klasa2::Wymnoz(int a, int b) {
	return a * b * a * b;
}
void klasa3::Wypisz() {
	cout << "Wypisuje nic" << endl;
}
void klasa3::Wypisz(int a) {
	cout << "Wypisuje cyfre " << a << endl;
}
void klasa3::Wypisz(char a) {
	cout << "Wypisuje litere " << a << endl;
}

void zad3() {
	//nadpisywanie
	klasa2 obiekt1;
	cout << obiekt1.Wymnoz(15, 15) << endl;

	//przeciazenie
	klasa3 obiekt2;

	obiekt2.Wypisz();
	obiekt2.Wypisz(10);
	obiekt2.Wypisz('z');


}