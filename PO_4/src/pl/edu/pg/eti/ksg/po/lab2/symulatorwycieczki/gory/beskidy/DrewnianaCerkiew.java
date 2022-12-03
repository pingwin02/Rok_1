package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class DrewnianaCerkiew extends Atrakcja {

    public DrewnianaCerkiew(String Miejscowosc) {
        super(Miejscowosc, 0.5);
    }

    @Override
    public String getNazwa() {
        return "Drewniana Cerkiew";
    }
}
