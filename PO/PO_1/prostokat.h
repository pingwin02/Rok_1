#ifndef prostokat_h

#define prostokat_h

#include "figuraplaska.h"

class Prostokat : public FiguraPlaska {
private:
	double a, b;
protected:
	void Wypisz(std::ostream& out) const override;
public:
	Prostokat(double a, double b);
	double GetA() const;
	void SetA(double a);
	double GetB() const;
	void SetB(double b);
	double Obwod() override;
	double Pole() override;
	~Prostokat() override;
};

#endif