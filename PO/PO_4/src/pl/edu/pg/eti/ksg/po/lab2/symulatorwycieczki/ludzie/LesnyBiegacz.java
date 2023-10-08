package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.GestyLas;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.Las;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.CmentarzZIWojny;

public class LesnyBiegacz extends Czlowiek{

    public LesnyBiegacz(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 6,12,20);
    }

    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 5;
    }

    @Override
    public void reagujNaWedrowke(Wedrowka w, double czas) {
        if (w instanceof Las || w instanceof GestyLas)
        {
            mow("Ale fajny las! W ogóle się nie męcze!");
            aktualizujZmeczenie(0);
        }
        else {
            super.reagujNaWedrowke(w, czas);
        }
    }

    @Override
    public void reagujNaAtrakcje(Atrakcja a, double czas) {
        if (a instanceof CmentarzZIWojny) {
            mow("Bardzo stary cmentarz! Istnieje wiele legend o nich.");
            regeneruj(2*czas);
        }
        else {
            super.reagujNaAtrakcje(a, czas);
        }
    }
}
