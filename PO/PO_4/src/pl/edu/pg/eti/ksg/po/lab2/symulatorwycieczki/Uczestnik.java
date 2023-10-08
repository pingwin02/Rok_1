package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.Czlowiek;

/**
 *
 * @author TB
 */
public interface Uczestnik {

    public enum Plec
    {
        KOBIETA,
        MEZCZYZNA;
    }
    
    /**
     * @return Bazowa prędkość, z którą porusza się uczestnik. Wyrażona w GOT/h.
     */
    double getBazowaPredkosc();
    
    /**
     * @return Umiejętność znajdywania drogi w terenie wyrażona w skali 1-5
     */
    int getUmiejetnosciNawigacyjne();
    
    /**
     * @return Poziom zmęczenia w skali 0-1, gdzie 0 to uczestnik wypoczęty a 1 zmęczony tak, że nie może dalej wędrować. 
     */
    double getPoziomZmeczenia();

    Plec getPlec();

    void opiszWycieczke(Wycieczka wycieczka);
    
    void reagujNaWedrowke(Wedrowka w, double czas);

    void reagujNaAtrakcje(Atrakcja a, double czas);
    
}
