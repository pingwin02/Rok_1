package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class Panorama extends Atrakcja {
    public Panorama(String Miejscowosc) {
        super(Miejscowosc, 0.17);
    }

    @Override
    public String getNazwa() {
        return "Panorama";
    }
}
