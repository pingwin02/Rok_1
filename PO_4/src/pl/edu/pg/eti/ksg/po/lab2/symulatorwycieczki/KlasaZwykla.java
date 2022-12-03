package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki;

public class KlasaZwykla {
    public static void MetodaStatyczna(ElementWycieczki elementWycieczki, int lp, int liczbaElementow) {
        System.out.println("***");
        System.out.println("Metoda statyczna");
        System.out.println("Postęp " + (lp + 1) + "/" + liczbaElementow);
        System.out.println("Etap: "+elementWycieczki.getNazwa());
        System.out.println("***");
    }

    public void MetodaZwykla(ElementWycieczki elementWycieczki, int lp, int liczbaElementow) {
        System.out.println("***");
        System.out.println("Metoda zwykla");
        System.out.println("Postęp " + (lp + 1) + "/" + liczbaElementow);
        System.out.println("Etap: "+elementWycieczki.getNazwa());
        System.out.println("***");
    }
}
