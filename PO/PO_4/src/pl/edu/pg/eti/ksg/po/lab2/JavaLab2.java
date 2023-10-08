package pl.edu.pg.eti.ksg.po.lab2;

import java.util.HashSet;
import java.util.Set;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.*;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.*;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.CmentarzZIWojny;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.DrewnianaCerkiew;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.Panorama;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.*;

/**
 * @author TB
 */
public class JavaLab2 {
    public static void main(String[] args) {
        Wycieczka w = doBukowca();

        PrzewodnikStudencki przewodnik = new PrzewodnikStudencki("Stefan", "Długonogi", Uczestnik.Plec.MEZCZYZNA);
        Set<Uczestnik> uczestnicy = new HashSet<>();
       // uczestnicy.add(new Student("Adam", "Studencki", Uczestnik.Plec.MEZCZYZNA));
        uczestnicy.add(new LesnyBiegacz("Basia", "Leśna", Uczestnik.Plec.KOBIETA));
       // uczestnicy.add(new CzlowiekZKontuzja("Jan", "Połamany", Uczestnik.Plec.MEZCZYZNA));
        uczestnicy.add(new StudentKSG("Piotr", "Teledetekcyjny", Uczestnik.Plec.MEZCZYZNA));
      //  uczestnicy.add(new Kierowca("Robert", "Kubica", Uczestnik.Plec.MEZCZYZNA));
     //   uczestnicy.add(new MistrzPanoram("Marek", "Panoramiczny", Uczestnik.Plec.MEZCZYZNA));

        Grupa g = new Grupa(przewodnik, uczestnicy);

        SymulatorWycieczki symulator = new SymulatorWycieczki(g, w);

        symulator.symuluj();
    }

    public static Wycieczka doDydiowki() {
        Wycieczka ret = new Wycieczka("Do Dydiówki");
        ret.dodajElementWycieczki(new Droga(1.0));
        ret.dodajElementWycieczki(new DrewnianaCerkiew("Smolnik"));
        ret.dodajElementWycieczki(new Droga(4.0));
        ret.dodajElementWycieczki(new PrzeprawaPrzezRzeke(1.0));
        ret.dodajElementWycieczki(new GestyLas(2.0));
        ret.dodajElementWycieczki(new Las(2.0));
        ret.dodajElementWycieczki(new Droga(5.0));

        return ret;
    }

    public static Wycieczka doBukowca() {
        Wycieczka ret = new Wycieczka("Do Bukowca");
        ret.dodajElementWycieczki(new GestyLas(2));
        ret.dodajElementWycieczki(new CmentarzZIWojny("Baligród"));
        ret.dodajElementWycieczki(new Droga(10));
        ret.dodajElementWycieczki(new Panorama("Polańczyk"));
        ret.dodajElementWycieczki(new Las(3));
        ret.dodajElementWycieczki(new Sciezka(3));
        ret.dodajElementWycieczki(new DrewnianaCerkiew("Krempna"));
        ret.dodajElementWycieczki(new PrzeprawaPrzezRzeke(0.25));
        return ret;
    }

}
