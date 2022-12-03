package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class Punkt {

    private final double x, y;

    public Punkt(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return this.x;
    }

    public double getY() {
        return this.y;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Punkt) {
            Punkt other = (Punkt) obj;
            if (x == other.x && y == other.y) {
                return true;
            }
        }
        return false;
    }

    @Override
    public int hashCode() {
        return Double.hashCode(x) + Double.hashCode(y);
    }

    @Override
    public String toString() {
        return "Instancja klasy Punkt (" + x + ", " + y + ")";
    }

    public static final Punkt O = new Punkt(0, 0);

    public static final Punkt E_X = new Punkt(1, 0);

    public static final Punkt E_Y = new Punkt(0, 1);
}
