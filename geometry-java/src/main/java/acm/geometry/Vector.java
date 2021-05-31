package acm.geometry;

import java.util.Comparator;
import java.util.Random;

public class Vector {
    double x, y, z;
    Vector(double x, double y){
        this.x = x;
        this.y = y;
        this.z = 0;
    }
    Vector(double x, double y, double z){
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public Vector add(Vector other){
        return new Vector(this.x + other.x, this.y + other.y, this.z + other.z);
    }
    public Vector neg(){
        return new Vector(-this.x, -this.y, -this.z);
    }
    double dot(Vector v){
        return this.x * v.x + this.y * v.y + this.z * v.z;
    }
    public Vector cross(Vector v){
        return new Vector(
                this.y * v.z - this.z * v.y,
                this.z * v.x - this.x * v.z,
                this.x * v.y - this.y * v.x
        );
    }

    public Vector changeLen(double cof){
        return new Vector(this.x * cof, this.y * cof, this.z * cof);
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

    public double getZ(){
        return z;
    }

    public static Comparator<Vector> xFirstComparator = Comparator.comparing(Vector::getX).thenComparing(Vector::getY);

    public static int signCross(Vector a, Vector b, Vector c){
        b = b.add(a.neg());
        c = c.add(a.neg());
        double ret = b.cross(c).getZ();
        if(ret < 0)
            return -1;
        if(ret == 0)
            return 0;
        return 1;
    }

    public static Vector random3d(double lim){
        Random rnd = new Random();
        return new Vector(rnd.nextDouble() * 2 * lim - lim, rnd.nextDouble() * 2 * lim - lim, rnd.nextDouble() * 2 * lim - lim);
    }
    public static Vector random2d(double lim){
        Random rnd = new Random();
        return new Vector(rnd.nextDouble() * 2 * lim - lim, rnd.nextDouble() * 2 * lim - lim, 0);
    }

    @Override
    public String toString() {
        return "<" + x + "," + y + "," + z + ">";
    }
}
