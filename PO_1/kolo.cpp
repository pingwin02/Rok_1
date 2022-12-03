#include "kolo.h"

#include <iostream>

#define PI 3.14159

using namespace std;

Kolo::Kolo(double r)
	: r(r)
{
	cout << "Konstruktor Kola(" << r << ")" << endl;
}
double Kolo::GetR() const {
	return r;
}
void Kolo::SetR(double r) {
	this->r = r;
}
double Kolo::Obwod() {
	return 2 * PI * r;
}
double Kolo::Pole() {
	return PI * r * r;
}
void Kolo::Wypisz(std::ostream& out) const {
	cout << "Kolo. Promien R " << GetR() << endl;

}
Kolo::~Kolo() {
	cout << "Destruktor kola. (" << GetR() << ")" << endl;
	cout << "Obwod " << Obwod() << " Pole " << Pole() << endl;
}