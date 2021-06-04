package acm.geometry.dcel;

import acm.geometry.Vector;

public class Vertex {
    Vector vector;
    private static int counter = 1;
    int id;

    public Vertex(Vector vector){
        this.vector = vector;
        this.id = counter;
        counter += 1;
    }

    public Vector getVector() {
        return vector;
    }

    @Override
    public String toString() {
        return "V" + id;
    }
}
