package acm.geometry;

import java.util.Comparator;
import java.util.Random;

public class Vector {
    double x, y;
    Vector(double x, double y){
        this.x = x;
        this.y = y;
    }
    public Vector add(Vector other){
        return new Vector(this.x + other.x, this.y + other.y);
    }
    public Vector neg(){
        return new Vector(-this.x, -this.y);
    }
    double dot(Vector v){
        return this.x * v.x + this.y * v.y;
    }
    double cross(Vector v){
        return this.x * v.y - this.y * v.x;
    }
    double len(){
        return Math.sqrt(dot(this));
    }
    double len2(){
        return dot(this);
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public static Comparator<Vector> xFirstComparator = Comparator.comparing(Vector::getX).thenComparing(Vector::getY);

    public static int signCross(Vector a, Vector b, Vector c){
        b = b.add(a.neg());
        c = c.add(a.neg());
        double ret = b.cross(c);
        if(ret < 0)
            return -1;
        if(ret == 0)
            return 0;
        return 1;
    }

    public static Vector random(double lim){
        Random rnd = new Random();
        return new Vector(rnd.nextDouble() * 2 * lim - lim, rnd.nextDouble() * 2 * lim - lim);
    }
}
