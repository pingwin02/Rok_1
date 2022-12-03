package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;

public class Sciezka extends Wedrowka {
    /**
     * @param odleglosc - długość wędrówki w GOT-ach
     */
    public Sciezka(double odleglosc) {
        super(odleglosc);
    }

    @Override
    public String getNazwa() {
        return "Ścieżka";
    }

    @Override
    public double modyfikujPredkoscGrupy(double predkosc) {
        return 1.2 * predkosc;
    }

    @Override
    public int getTrudnoscNawigacyjna() {
        return 1;
    }
}
