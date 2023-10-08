package pl.edu.pg.eti.ksg.po.lab1.transformacje;

import java.lang.Math;

public class Wektor{

    private final Punkt pkt;
    private final double modul, zwrot;

    public Wektor(Punkt pkt, double modul, double zwrot) {
        this.pkt=pkt;
        this.modul=modul;
        this.zwrot=zwrot;
    }

    public Punkt getPKT() {
        return this.pkt;
    }

    public double getModul() {
        return this.modul;
    }

    public double getZwrot() {
        return this.zwrot;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Wektor) {
            Wektor other = (Wektor) obj;
            if (pkt.equals(other.pkt) && modul==other.modul && zwrot==other.zwrot) {
                return true;
            }
        }
        return false;
    }

    @Override
    public int hashCode() {
        return pkt.hashCode() + Double.hashCode(modul+zwrot);
    }

    @Override
    public String toString() {
        return "Instancja klasy Wektor (" + pkt + ", " + modul + ", " + Math.ceil(zwrot*180/Math.PI) + ")";
    }



}
