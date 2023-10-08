package pl.edu.pg.eti.ksg.po.lab1;

import pl.edu.pg.eti.ksg.po.lab1.transformacje.*;

public class Javalab1 {
    public static void main(String[] args) {
        try {
            Punkt pkt1 = new Punkt(1, 1);

            Punkt pkt2 = new Punkt(0, 0);

            Wektor wek1 = new Wektor(pkt1, 5, Math.PI / 6);
            Wektor wek2 = new Wektor(pkt2, 25, 0);
            System.out.println("Przed");
            System.out.println(wek1);
            System.out.println(wek2);

            Transformacja tr1 = new Skalowanie(3, 4);

            Transformacja tr2 = new Translacja(1, 1);

            Transformacja tr3 = new Obrot(Math.PI / 6);

            wek1 = tr1.transformuj(wek1);
            System.out.println("Po modyfikacji wek1");
            System.out.println(wek1);

            wek2 = tr2.transformuj(wek2);
            wek2 = tr3.transformuj(wek2);
            System.out.println("Po modyfikacji wek2");
            System.out.println(wek2);
            System.out.println("Sa takie same?");
            System.out.println(wek1.hashCode()+", "+wek2.hashCode());
            System.out.println(wek1.equals(wek2));
            System.out.println("Referencja?");
            System.out.println(wek1==wek2);

            Transformacja tab[] = new Transformacja[2];
            tab[0] = tr2;
            tab[1] = tr3;

            Transformacja tr4 = new ZlozenieTransformacji(tab).getTransformacjaOdwrotna();

            wek2 = tr4.transformuj(wek2);
            System.out.println(tr4);
            System.out.println("Powrot do poczatku wek2");
            System.out.println(wek2);

        }catch (BrakTransformacjiOdwrotnejException ex) {
            ex.printStackTrace();
        }
    }

    /*public static void main(String[] args) {
        Punkt pkt1 = new Punkt(5, 10);
        System.out.println(pkt1);

        System.out.println("Wspolrzedne X pkt1: " + pkt1.getX());

        Punkt pkt2 = new Punkt(5, 10);
        System.out.println(pkt2);

        System.out.println(pkt1.hashCode() + ", " + pkt2.hashCode());
        System.out.println(pkt1.equals(pkt2));
        System.out.println(pkt1 == pkt2);

        System.out.println(Punkt.O);

    }

    public static void main(String[] args) {
        try {
            Punkt p1 = Punkt.E_X;
            System.out.println(p1);
            Transformacja tr = new Translacja(5, 6);
            System.out.println(tr);
            Punkt p2 = tr.transformuj(p1);
            System.out.println(p2);
            Transformacja trr = tr.getTransformacjaOdwrotna();
            System.out.println(trr);
            Punkt p3 = trr.transformuj(p2);
            System.out.println(p3);
        } catch (BrakTransformacjiOdwrotnejException ex) {
            ex.printStackTrace();
        }
        System.out.println();

        try {
            Punkt p1 = new Punkt(2, 2);
            System.out.println(p1);
            Transformacja tr2 = new Skalowanie(5, 4);
            System.out.println(tr2);
            Punkt p2 = tr2.transformuj(p1);
            System.out.println(p2);
            Transformacja trr2 = tr2.getTransformacjaOdwrotna();
            System.out.println(trr2);
            Punkt p3 = trr2.transformuj(p2);
            System.out.println(p3);
        } catch (BrakTransformacjiOdwrotnejException ex) {
            ex.printStackTrace();
        }
        System.out.println();


        try {
            Punkt p1 = new Punkt(2, 2);
            Transformacja tr2 = new Skalowanie(5, 0);
            System.out.println(tr2);
            System.out.println(p1);
            Punkt p2 = tr2.transformuj(p1);
            System.out.println(p2);
            Transformacja trr2 = tr2.getTransformacjaOdwrotna();
            System.out.println(trr2);
            Punkt p3 = trr2.transformuj(p2);
            System.out.println(p3);
        } catch (BrakTransformacjiOdwrotnejException ex) {
            ex.printStackTrace();
        }
        System.out.println();

        try {
            Punkt p1 = new Punkt(5, 0);
            Transformacja tr3 = new Obrot(45);
            System.out.println(tr3);
            System.out.println(p1);
            Punkt p2 = tr3.transformuj(p1);
            System.out.println(p2);
            Transformacja trr3 = tr3.getTransformacjaOdwrotna();
            System.out.println(trr3);
            Punkt p3 = trr3.transformuj(p2);
            System.out.println(p3);
        } catch (BrakTransformacjiOdwrotnejException ex) {
            ex.printStackTrace();
        }
        System.out.println();
    }

    public static void main(String[] args) {
        try {
            Punkt p1 = new Punkt(1, 2);
            Transformacja[] tab = new Transformacja[2];
            tab[0] = new Skalowanie(5,2).getTransformacjaOdwrotna();
            tab[1] = new Translacja(5,10);
            Transformacja tr1 = new ZlozenieTransformacji(tab).getTransformacjaOdwrotna();
            System.out.println(tr1);
            System.out.println(p1);
            p1 = tr1.transformuj(p1);
            System.out.println(p1);
            tr1 = tr1.getTransformacjaOdwrotna();
            System.out.println(tr1);
            p1 = tr1.transformuj(p1);
            System.out.println(p1);

        } catch (BrakTransformacjiOdwrotnejException ex) {
            ex.printStackTrace();
        }
    }*/
}