package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class CmentarzZIWojny extends Atrakcja {

    public CmentarzZIWojny(String Miejscowosc) {
        super(Miejscowosc, 0.34);
    }


    @Override
    public String getNazwa() {
        return "Cmentarz z I Wojny Światowej";
    }
}
