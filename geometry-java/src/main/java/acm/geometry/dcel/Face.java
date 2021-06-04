package acm.geometry.dcel;

import acm.geometry.ConvexHull3d;
import acm.geometry.CycleList;
import acm.geometry.Utils;
import acm.geometry.Vector;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Face {
    Edge firstEdge;

    public Face(){
    }

    public void setFirstEdge(Edge firstEdge) {
        this.firstEdge = firstEdge;
    }
    public CycleList<Edge> getEdges(){
        CycleList<Edge> ret = new CycleList<>();
        Edge tmp = firstEdge;
        do{
            ret.add(tmp);
            tmp = tmp.getNext();
        }while (!tmp.equals(firstEdge));
        return ret;
    }
    public CycleList<Vertex> getVertices(){
        CycleList<Vertex> ret = new CycleList<>();
        getEdges().forEach(e->ret.add(e.getFrom()));
        return ret;
    }
    public CycleList<Face> getNeighborFaces(){
        CycleList<Face> ret = new CycleList<>();
        getEdges().forEach(e->ret.add(e.getTwin().getFace()));
        return ret;
    }
    public Vector getDirection(){
        Edge e1 = firstEdge;
        Edge e2 = firstEdge.getNext();
        Vector a = e1.getFrom().getVector();
        Vector b = e1.getTo().getVector();
        Vector c = e2.getTo().getVector();
        return Vector.triCross(a, b, c);
    }
    public Vector normalizeWithRespectToFirstVertex(Vector v){
        return v.add(firstEdge.getFrom().getVector().neg());
    }
    public Vector getSpecialVector(){
        Edge e1 = firstEdge;
        Edge e2 = firstEdge.getNext();
        Vector a = e1.getFrom().getVector();
        Vector b = e1.getTo().getVector();
        Vector c = e2.getTo().getVector();
        return normalizeWithRespectToFirstVertex(b).cross(normalizeWithRespectToFirstVertex(c));
    }
    public boolean isVisibleFromOutside(Vector v){
        v = normalizeWithRespectToFirstVertex(v);
        return getSpecialVector().dot(v) < -Utils.eps;
    }
    public boolean isVisibleFromOutsideByPlane(Vector pos, Vector direction){
        pos = normalizeWithRespectToFirstVertex(pos);
        return direction.dot(getSpecialVector()) > Utils.eps &&
                direction.dot(pos) < -Utils.eps;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        getVertices().forEach(v -> sb.append(v.getVector()));
        return sb.toString();
    }
}
