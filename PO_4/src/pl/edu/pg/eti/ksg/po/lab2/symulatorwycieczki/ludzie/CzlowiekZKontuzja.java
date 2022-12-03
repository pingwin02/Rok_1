package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;

public class CzlowiekZKontuzja extends Czlowiek {


    public CzlowiekZKontuzja(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 3, 18, 12);
    }

    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 1;
    }

    @Override
    public void reagujNaWedrowke(Wedrowka w, double czas) {
        mow("Ała wszystko mnie boli!");
        aktualizujZmeczenie(1.1*czas);
    }

    @Override
    public void reagujNaAtrakcje(Atrakcja a, double czas) {
        mow("Meh. Daleko jeszcze? Wezmę witaminy.");
        regeneruj(3 * czas);
    }
}
