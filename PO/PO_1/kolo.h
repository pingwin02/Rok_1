#ifndef kolo_h

#define kolo_h

#include "FiguraPlaska.h"

class Kolo : public FiguraPlaska {
private:
	double r;
protected:
	void Wypisz(std::ostream& out) const override;
public:
	Kolo(double r);
	double GetR() const;
	void SetR(double r);
	double Obwod() override;
	double Pole() override;
	~Kolo() override;
private:
};

#endif 