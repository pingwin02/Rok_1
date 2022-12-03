package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public interface Transformacja {
    Punkt transformuj(Punkt p);
    Wektor transformuj(Wektor p);
    Transformacja getTransformacjaOdwrotna()
        throws BrakTransformacjiOdwrotnejException;
}
