package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.Droga;

public class Kierowca extends Czlowiek {
    public Kierowca(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 10, 18, 18);
    }

    @Override
    public void reagujNaWedrowke(Wedrowka w, double czas) {
        if (w instanceof Droga) {
            mow("Nie chce mi się iść. Wsiadam do auta.");
            regeneruj(czas);
        }
        else {
            super.reagujNaWedrowke(w, czas);
        }
    }

    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 5;
    }
}
