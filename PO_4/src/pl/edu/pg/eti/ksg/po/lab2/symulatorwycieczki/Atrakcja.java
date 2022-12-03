package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki;

public abstract class Atrakcja implements ElementWycieczki{
    private final double czasZwiedzania;
    private final String miejscowosc;


    public Atrakcja(String Miejscowosc, double czasZwiedzania) {
        this.czasZwiedzania = czasZwiedzania;
        this.miejscowosc = Miejscowosc;
    }

    public double getCzasZwiedzania() {
        return czasZwiedzania;
    }

    public String getMiejscowosc() {
        return miejscowosc;
    }
}
