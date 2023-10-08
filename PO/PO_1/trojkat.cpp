#include "trojkat.h"

#include <iostream>
#include <math.h>

using namespace std;

Trojkat::Trojkat(double a, double b, double c)
	: a(a), b(b), c(c)
{
	cout << "Konstruktor Trojkata(" << a << "," << b << "," << c << ")" << endl;
}
double Trojkat::GetA() const {
	return a;
}
double Trojkat::GetB() const {
	return b;
}
double Trojkat::GetC() const {
	return c;
}
void Trojkat::SetA(double a) {
	this->a = a;
}
void Trojkat::SetB(double b) {
	this->b = b;
}
void Trojkat::SetC(double c) {
	this->c = c;
}
double Trojkat::Obwod() {
	return GetA() + GetB() + GetC();
}
double Trojkat::Pole() {
	double p = Obwod() / 2;
	double heron = sqrt(p * (p - GetA()) * (p - GetB()) * (p - GetC()));
	return heron;
}
void Trojkat::Wypisz(std::ostream& out) const {
	cout << "Trojkat. Bok A " << GetA() << " Bok B " << GetB() << " Bok C " << GetC() << endl;

}
Trojkat::~Trojkat() {
	cout << "Destruktor trojkata. (" << GetA() << GetB() << GetC() << ")" << endl;
	cout << "Obwod " << Obwod() << " Pole " << Pole() << endl;
}