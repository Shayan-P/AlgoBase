package acm.geometry;

import acm.geometry.camera.Camera;
import acm.geometry.camera.SimpleSphereCamera;
import acm.geometry.dcel.Face;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.scene.shape.Polygon;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.util.Duration;
import javafx.util.Pair;

import java.util.*;

public class Visual3d extends Application {
    double width = 1000;
    double height = 1000;
    double randomLen = (width/2) - 100;

    Pane pane = new Pane();
    Scene scene = new Scene(pane, width, height);
    Camera camera = new SimpleSphereCamera(scene, new Vector(6000,100,6000));
    List<Pair<Integer, Runnable>> renderingFunctions = new ArrayList<>();
    List<Pair<Integer, Node>> stackedNodes = new ArrayList<>();

    public void refresh(){
        for(Pair<Integer, Runnable> pair : renderingFunctions) {
            pair.getValue().run();
        }
    }
    public void prepareLoop(){
        renderingFunctions.sort(Comparator.comparingInt(Pair::getKey));
        stackedNodes.sort(Comparator.comparingInt(Pair::getKey));
        stackedNodes.forEach(e->pane.getChildren().add(e.getValue()));
    }
    public void setFunction(int layerId, Runnable runnable){
        renderingFunctions.add(new Pair<>(layerId, runnable));
    }

    Text putTextUnderPoint(Vector v, String txt){
        Text text = new Text(txt);
        stackedNodes.add(new Pair<>(4, text));
        setFunction(4, ()->{
            Vector newVec = camera.translate(v);
            text.setX(newVec.x);
            text.setY(newVec.y - 10);
        });
        return text;
    }

    Circle putPoint(Vector v, Color color){
        Circle circle = new Circle(5, color);
        stackedNodes.add(new Pair<>(3, circle));
        setFunction(3, ()->{
            Vector newVec = camera.translate(v);
            circle.setCenterX(newVec.x);
            circle.setCenterY(newVec.y);
        });
        return circle;
    }

    Line putLine(Vector a, Vector b, Color color){
        Line line = new Line();
        line.setStroke(color);
        stackedNodes.add(new Pair<>(2, line));
        setFunction(2, ()->{
            Vector newA = camera.translate(a);
            Vector newB = camera.translate(b);
            line.setStartX(newA.x);
            line.setStartY(newA.y);
            line.setEndX(newB.x);
            line.setEndY(newB.y);
        });
        return line;
    }

    Polygon putPolygon(Color color, boolean glass, Vector... vertices){
        Polygon poly = new Polygon();
        poly.setFill(color);
        stackedNodes.add(new Pair<>(0, poly));
        setFunction(glass ? 0 : 1, ()->{
            poly.getPoints().clear();
            Arrays.stream(vertices).forEach(v->{
                Vector newVector = camera.translate(v);
                poly.getPoints().addAll(newVector.x, newVector.y);
            });
        });
        return poly;
    }

    Polygon putFace(Face face, Color color){
        int sz = face.getVertices().size();
        Vector[] vectors = new Vector[sz];
        for(int i = 0; i < sz; i++)
            vectors[i] = face.getVertices().get(i).getVector();

        List<Node> nodes = new ArrayList<>();

        for (int i = 0; i < sz; i++) {
            Vector A = vectors[i];
            Vector B = vectors[(i+1) % sz];
            nodes.add(putLine(A, B, Color.BLACK));
            nodes.add(putPoint(A, Color.RED));
            nodes.add(putTextUnderPoint(A, face.getVertices().get(i).toString()));
        }
        Polygon polygon = putPolygon(color, false, vectors);
        nodes.add(polygon);

        setFunction(5, ()->{
            nodes.forEach(node->node.setVisible(face.isVisibleFromOutsideByPlane(camera.getPosition(), camera.getDirection())));
            if (face.isVisibleFromOutside(camera.getPosition()))
                polygon.setFill(color);
            else
                polygon.setFill(Color.GREENYELLOW);
        });
//        scene.setOnMouseClicked(e->{
//            System.out.println("this is camera: " + camera.getPosition());
//            System.out.println(face.dummy(camera.getPosition()));
//        });
        return polygon;
    }

    public void putConvexHull3d(ConvexHull3d hull3d){
        List<Face> faces = hull3d.getFaces();
        for (Face face : faces) {
            putFace(face, Color.gray(0.4));
        }
    }

    private ConvexHull3d getHull(){
        CycleList<Vector> tmp = new CycleList<>();

//        tmp.add(new Vector(-500, -500, -200));
//        tmp.add(new Vector(500, -500, -200));
//        tmp.add(new Vector(-500, 500, -200));
//        tmp.add(new Vector(0, 0, 200));
//        tmp.add(new Vector(0, 0, 0));
//        tmp.add(new Vector(0, 0, 250));

//        for(int i = 0; i < 100; i++){
//            Random rnd = new Random();
//            double alpha = rnd.nextDouble() * Math.PI;
//            double teta = rnd.nextDouble() * Math.PI * 2;
//            double r = 200;
//            tmp.add(new Vector(
//                    r * Math.sin(alpha) * Math.cos(teta),
//                    r * Math.sin(alpha) * Math.sin(teta),
//                    r * Math.cos(alpha)
//            ));
//        }
//        ConvexHull3d hull3d = new ConvexHull3d(tmp);

        ConvexHull3d hull3d = new ConvexHull3d();
        hull3d.randomFill(100, randomLen);

        hull3d.incrementalN2();
//        hull3d.trivialN4();

        System.out.println("Number of faces" + hull3d.getFaces().size());
        System.out.println("Number of vertices" + hull3d.getVertices().size());

        return hull3d;
    }

    @Override
    public void start(Stage primaryStage) {
        putConvexHull3d(getHull());
        prepareLoop();
        refresh();

        Timeline tt = new Timeline(new KeyFrame(Duration.millis(50), e->refresh()));
        tt.setCycleCount(Timeline.INDEFINITE);
        tt.play();

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
