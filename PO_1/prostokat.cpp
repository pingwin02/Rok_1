#include "prostokat.h"

#include <iostream>

using namespace std;

Prostokat::Prostokat(double a, double b)
	: a(a), b(b)
{
	cout << "Konstruktor Prostokata(" << a << "," << b << ")" << endl;
}
double Prostokat::GetA() const {
	return a;
}
double Prostokat::GetB() const {
	return b;
}
void Prostokat::SetA(double a) {
	this->a = a;
}
void Prostokat::SetB(double b) {
	this->b = b;
}
double Prostokat::Obwod() {
	return 2 * GetA() + 2 * GetB();
}
double Prostokat::Pole() {
	return GetA() * GetB();
}
void Prostokat::Wypisz(std::ostream& out) const {
	cout << "Prostokat. Bok A " << GetA() << " Bok B " << GetB() << endl;

}
Prostokat::~Prostokat() {
	cout << "Destruktor prostokata.(" << GetA() << GetB() << ")" << endl;
	cout << "Obwod " << Obwod() << " Pole " << Pole() << endl;
}