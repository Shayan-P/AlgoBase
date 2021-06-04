package acm.geometry;

import acm.geometry.dcel.DCEL;
import acm.geometry.dcel.Edge;
import acm.geometry.dcel.Face;
import acm.geometry.dcel.Vertex;

import java.util.ArrayList;
import java.util.List;

public class ConvexHull3d extends ConvexHull2d {
    CycleList<Vector> points;
    private DCEL dcel = new DCEL();

    public ConvexHull3d(CycleList<Vector> points){
        this.points = points;
    }
    public ConvexHull3d(){
    }

    public void trivialN4() {
        for(int i = 0; i < points.size(); i++){
            for(int j = i+1; j < points.size(); j++){
                for(int k = j+1; k < points.size(); k++){
                    Vector A = points.get(i), B = points.get(j), C = points.get(k);
                    Vector crs = B.add(A.neg()).cross(C.add(A.neg()));
                    crs = crs.changeLen(1/crs.len());
                    boolean positive = false, negative = false;
                    for (Vector point : points) {
                        double val = crs.dot(point.add(A.neg()));
                        if(Math.abs(val) < Utils.eps)
                            continue;
                        negative |= val < 0;
                        positive |= val > 0;
                    }
                    if(!negative){
                        dcel.addFace(A, B, C);
                    }
                    else if(!positive){
                        dcel.addFace(C, B, A);
                    }
                }
            }
        }
    }

    // todo. it has bug. sometimes the number of faces becomes zero!

    public void incrementalN2() {
        if(points.size() < 3)
            throw new RuntimeException("vertices less than 3");
        dcel.addFace(points.get(0), points.get(1), points.get(2));

        for(int i = 3; i < points.size(); i++) {
            System.out.println("processing " + points.get(i));
            Vector p = points.get(i);
            List<Face> goodFaces = new ArrayList<>();
            List<Face> badFaces = new ArrayList<>();
            List<Edge> edges = new ArrayList<>();
            dcel.getFaces().forEach(face -> {
                if (face.isVisibleFromOutside(p))
                    badFaces.add(face);
                else
                    goodFaces.add(face);
            });
            badFaces.forEach(face -> {
                dcel.removeFace(face);
            });
            goodFaces.forEach(face -> {
                face.getEdges().forEach(e -> {
                    if (e.getTwin() == null)
                        edges.add(e);
                });
            });
            edges.forEach(e -> {
                dcel.addFace(p, e.getTo().getVector(), e.getFrom().getVector());
            });
        }
        System.out.println("end of processing. we have " + dcel.getFaces().size() + " faces!");
    }

    public void randomFill(int n, double lim){
        points = new CycleList<>();
        for(int i = 0; i < n; i++)
            points.add(Vector.random3d(lim));
    }

    public List<Face> getFaces(){
        return dcel.getFaces();
    }
    public List<Vertex> getVertices(){
        return dcel.getVertices();
    }
}
