package acm.geometry.dcel;

public class Edge {
    private Edge twin, next;
    private final Vertex from, to;
    private final Face face;

    public Edge(Vertex from, Vertex to, Face face){
        this.from = from;
        this.to = to;
        this.face = face;
    }

    public void setNext(Edge next) {
        this.next = next;
    }

    public void setTwin(Edge twin) {
        this.twin = twin;
    }

    public Edge getNext() {
        return next;
    }

    public Vertex getFrom() {
        return from;
    }

    public Face getFace() {
        return face;
    }

    public Vertex getTo() {
        return to;
    }

    public Edge getTwin() {
        return twin;
    }
}
