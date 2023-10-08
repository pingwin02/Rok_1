#include <iostream>

#include "figuraplaska.h"
#include "prostokat.h"
#include "trojkat.h"
#include "kolo.h"
#include "zad3.h"

using namespace std;

int main() {

	Prostokat* prostokat = new Prostokat(13,10);

	Trojkat* trojkat = new Trojkat(3, 4, 5);

	Kolo* kolo = new Kolo(35);

	FiguraPlaska* tab[] = { prostokat,trojkat,kolo };

	kolo->SetR(10);

	cout << trojkat->GetB() << endl;

	cout << *prostokat;

	for (int i = 0; i < 3; i++) {
		cout << tab[i]->Obwod() << endl;
		cout << tab[i]->Pole() << endl;
	}

	delete prostokat;
	delete trojkat;
	delete kolo;

	zad3();

	return 0;

}