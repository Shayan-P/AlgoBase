package acm.geometry.dcel;

import acm.geometry.CycleList;
import acm.geometry.Vector;

import java.util.*;

public class DCEL {
    List<Face> faces = new ArrayList<>();
    HashMap<Vertex, HashMap<Vertex, Edge>> verticesToEdge = new HashMap<>();
    HashMap<Vector, Vertex> vertexMap = new HashMap<>();

    public DCEL(){
    }

    public void addFace(Vector... vectors){
        int sz = vectors.length;
        if(sz < 3)
            throw new RuntimeException("vectors length is less than 3");
        CycleList<Vertex> vertices = new CycleList<>();
        CycleList<Edge> edges = new CycleList<>();
        Face face = new Face();
        for(Vector vector : vectors){
            if(!vertexMap.containsKey(vector)) {
                vertexMap.put(vector, new Vertex(vector));
//                System.out.println("new vertice" + vector);
            }
            vertices.add(vertexMap.get(vector));
        }
        for(int i = 0; i < vertices.size(); i++){
            Vertex a = vertices.get(i), b = vertices.getRel(i, 1);
            Edge e = new Edge(a, b, face);
            addEdge(a, b, e);
            edges.add(e);
        }
        for(int i = 0; i < edges.size(); i++){
            edges.get(i).setNext(edges.getRel(i, 1));
        }
        face.setFirstEdge(edges.get(0));
        faces.add(face);
    }
    public void removeFace(Face face){
        Edge startEdge = face.firstEdge;
        Edge tmp = startEdge;
        do{
            removeEdge(tmp);
            tmp = tmp.getNext();
        }while (!tmp.equals(startEdge));
        faces.remove(face);
    }

    private Edge getEdgeByVertices(Vertex a, Vertex b){
        if(verticesToEdge.containsKey(a)){
            if(verticesToEdge.get(a).containsKey(b))
                return verticesToEdge.get(a).get(b);
        }
        return null;
    }
    private void addEdge(Vertex a, Vertex b, Edge e){
        if(!verticesToEdge.containsKey(a))
            verticesToEdge.put(a, new HashMap<>());
        assert !verticesToEdge.get(a).containsKey(b);
        Edge e2 = getEdgeByVertices(b, a);
        verticesToEdge.get(a).put(b, e);
        if(e2 != null){
            e.setTwin(e2);
            e2.setTwin(e);
        }
    }
    private void removeEdge(Edge e){
        verticesToEdge.get(e.getFrom()).remove(e.getTo());
        Edge twin = getEdgeByVertices(e.getTo(), e.getFrom());
        if(twin != null){
            twin.setTwin(null);
        }
    }

    public List<Face> getFaces() {
        return faces;
    }
    public List<Vertex> getVertices() {
        HashSet<Vertex> hashSet = new HashSet<>();
        for(Face face : getFaces())
            hashSet.addAll(face.getVertices());
        ArrayList<Vertex> ret = new ArrayList<>();
        ret.addAll(hashSet);
        return ret;
    }
}
