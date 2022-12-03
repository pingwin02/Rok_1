package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.Panorama;

public class MistrzPanoram extends Czlowiek{

    public MistrzPanoram(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 5,18,18);
    }

    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 4;
    }

    @Override
    public void reagujNaAtrakcje(Atrakcja a, double czas) {
        if (a instanceof Panorama) {
            mow("Ale piękny widok!");
            regeneruj(2*czas);

        }
        else {
            super.reagujNaAtrakcje(a, czas);
        }
    }
}
