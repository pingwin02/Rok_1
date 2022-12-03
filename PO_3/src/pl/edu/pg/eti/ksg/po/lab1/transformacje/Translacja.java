package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class Translacja implements Transformacja{

    private final double dX,dY;

    public Translacja(double dX, double dY) {
        this.dX=dX;
        this.dY=dY;
    }

    @Override
    public Transformacja getTransformacjaOdwrotna() {

        return new Translacja(-dX, -dY);
    }

    @Override
    public Punkt transformuj(Punkt p) {

        return new Punkt(p.getX() + dX, p.getY() + dY);
    }

    @Override
    public Wektor transformuj(Wektor p) {

        Punkt newpkt = new Punkt(p.getPKT().getX() + dX, p.getPKT().getY() + dY);

        return new Wektor(newpkt,p.getModul(),p.getZwrot());
    }


    public double getdX() {
        return dX;
    }
    public double getdY() {
        return dY;
    }

    @Override
    public String toString() {
        return "Translacja o wektor ("+dX+","+dY+")";
    }

}
