package pl.edu.pg.eti.ksg.po.lab1.transformacje;

import java.lang.Math;

public class Obrot implements Transformacja {
    private final double alfa;

    public Obrot(double alfa) {
        this.alfa = alfa;
    }

    public double getAlfa() {
        return alfa;
    }

    @Override
    public Punkt transformuj(Punkt p) {
        double newX = p.getX() * Math.cos(alfa) - p.getY() * Math.sin(alfa);
        double newY = p.getX() * Math.sin(alfa) + p.getY() * Math.cos(alfa);
        return new Punkt(newX, newY);
    }

    @Override
    public Wektor transformuj(Wektor p) {
        double newzwrot = (p.getZwrot()+alfa)%(2*Math.PI);
        return new Wektor(p.getPKT(), p.getModul(), newzwrot);
    }

    @Override
    public Transformacja getTransformacjaOdwrotna()
            throws BrakTransformacjiOdwrotnejException {
        if (alfa == 0)
            throw new BrakTransformacjiOdwrotnejException("Kąt nie może być zerowy!");
        return new Obrot(-alfa);
    }

    @Override
    public String toString() {
        return "Obrót o "+alfa+" stopni";
    }
}
