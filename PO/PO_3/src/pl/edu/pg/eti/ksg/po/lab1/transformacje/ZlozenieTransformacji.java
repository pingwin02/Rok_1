package pl.edu.pg.eti.ksg.po.lab1.transformacje;

import java.util.Arrays;
import java.util.Collections;

public class ZlozenieTransformacji implements Transformacja {
    private Transformacja tab[];

    public ZlozenieTransformacji(Transformacja tab[]) {
        this.tab = tab;
    }

    @Override
    public Punkt transformuj(Punkt p) {
        for (int i = 0; i < tab.length; i++) {
            p = tab[i].transformuj(p);
        }
        return p;
    }

    @Override
    public Wektor transformuj(Wektor p) {
        for (int i = 0; i < tab.length; i++) {
            p = tab[i].transformuj(p);
        }
        return p;
    }

    @Override
    public Transformacja getTransformacjaOdwrotna() throws BrakTransformacjiOdwrotnejException {

        for (int i = 0; i < tab.length; i++) {
            tab[i] = tab[i].getTransformacjaOdwrotna();
        }
        Collections.reverse(Arrays.asList(tab));
        return new ZlozenieTransformacji(tab);
    }

    @Override
    public String toString() {
        String odp="";
        odp+="Zlozenie " + tab.length + " transformacji:\n";
        for (int i = 0; i < tab.length; i++) {
            odp+=tab[i]+"\n";
        }
        return odp;
    }
}
