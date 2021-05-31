package acm.geometry;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.input.KeyCode;
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
    double cameraR = 100;
    double cameraAlpha = 0;
    double cameraTeta = 0;

    double width = 1000;
    double height = 1000;
    double randomLen = (width/2) - 100;

    Pane pane = new Pane();
    Scene scene = new Scene(pane, width, height);

    List<Pair<Integer, Runnable>> renderingFunctions = new ArrayList<>();
    List<Pair<Integer, Node>> stackedNodes = new ArrayList<>();

    private final HashSet<KeyCode> isPressed = new HashSet<>();

    Vector getCameraVector(){
        return new Vector(
                cameraR * Math.sin(cameraAlpha) * Math.cos(cameraTeta),
                cameraR * Math.sin(cameraAlpha) * Math.sin(cameraTeta),
                cameraR * Math.cos(cameraAlpha)
        );
    }

    Vector normalize(Vector v){
        Vector camera = getCameraVector();
        Vector yAxis = new Vector(
                Math.cos(cameraAlpha) * Math.cos(cameraTeta),
                Math.cos(cameraAlpha) * Math.sin(cameraTeta),
                - Math.sin(cameraAlpha)
        );
        Vector xAxis = yAxis.cross(camera);
        xAxis = xAxis.changeLen(1/xAxis.len());
        double cof = (100 * 100) /(cameraR * cameraR);
        return new Vector(
                xAxis.dot(v) * cof + width/2,
                -yAxis.dot(v) * cof + height/2,
                0);
    }

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

    void putTextUnderPoint(Vector v, String txt){
        Text text = new Text(txt);
        stackedNodes.add(new Pair<>(3, text));
        setFunction(3, ()->{
            Vector newVec = normalize(v);
            text.setX(newVec.x);
            text.setY(newVec.y - 10);
        });
    }

    void putPoint(Vector v, Color color){
        Circle circle = new Circle(5, color);
        stackedNodes.add(new Pair<>(2, circle));
        setFunction(2, ()->{
            Vector newVec = normalize(v);
            circle.setCenterX(newVec.x);
            circle.setCenterY(newVec.y);
        });
    }

    void putLine(Vector a, Vector b, Color color){
        Line line = new Line(a.x, a.y, b.x, b.y);
        line.setStroke(color);
        stackedNodes.add(new Pair<>(1, line));
        setFunction(1, ()->{
            Vector newA = normalize(a);
            Vector newB = normalize(b);
            line.setStartX(newA.x);
            line.setStartY(newA.y);
            line.setEndX(newB.x);
            line.setEndY(newB.y);
        });
    }

    private void addPolygon(Color color, Vector... vertices){
        Polygon poly = new Polygon();
        poly.setFill(color);
        stackedNodes.add(new Pair<>(0, poly));
        setFunction(0, ()->{
            poly.getPoints().clear();
            Arrays.stream(vertices).forEach(v->{
                Vector newVector = normalize(v);
                poly.getPoints().addAll(newVector.x, newVector.y);
            });
        });
    }

    private void setControllers(){
        scene.setOnKeyPressed(e->{
            isPressed.add(e.getCode());
        });
        scene.setOnKeyReleased(e->{
            isPressed.remove(e.getCode());
        });
        Timeline tt = new Timeline(new KeyFrame(Duration.millis(50), e->{
            if(isPressed.contains(KeyCode.UP)){
                cameraAlpha += 0.06;
                cameraAlpha = (cameraAlpha + Math.PI) % (Math.PI);
            }
            if(isPressed.contains(KeyCode.DOWN)){
                cameraAlpha -= 0.06;
                cameraAlpha = (cameraAlpha + Math.PI) % (Math.PI);
            }
            if(isPressed.contains(KeyCode.LEFT)){
                cameraTeta -= 0.03;
                cameraTeta = (cameraTeta + Math.PI * 2) % (Math.PI * 2);
            }
            if(isPressed.contains(KeyCode.RIGHT)){
                cameraTeta += 0.03;
                cameraTeta = (cameraTeta + Math.PI * 2) % (Math.PI * 2);
            }
            if(isPressed.contains(KeyCode.A)){
                cameraR += 10;
            }
            if(isPressed.contains(KeyCode.B)){
                cameraR -= 10;
            }
            refresh();
        }));
        tt.setCycleCount(Timeline.INDEFINITE);
        tt.play();
    }

    @Override
    public void start(Stage primaryStage) {
        GrahamScan hull = new GrahamScan();
        hull.randomFill(30, randomLen);
        for(Vector v : hull.points)
            putPoint(v, Color.BLACK);
        hull.compute();

        for(int i = 0; i < hull.points.size(); i++){
            Vector me = hull.points.get(i);
            Vector nxt = hull.points.getRel(i, 1);
            putPoint(me, Color.RED);
            putTextUnderPoint(me, Integer.toString(i));
            putLine(me, nxt, Color.BLACK);
        }

        for(int i = 0; i < 10; i++) {
            Vector randomPoint = Vector.random2d(randomLen);
            if(hull.checkStrictInside(randomPoint)){
                putPoint(randomPoint, Color.BROWN);
            }
            else {
                putPoint(randomPoint, Color.GREEN);
                putLine(randomPoint, hull.getFistLineIntersection(randomPoint), Color.BLUE);
                putLine(randomPoint, hull.getSecondLineIntersection(randomPoint), Color.BLUE);
            }
        }

        Vector bef = null;
        for(int i = 0; i < 30; i++){
            Vector nw = Vector.random3d(randomLen);
            if(bef != null)
                putLine(bef, nw, Color.GRAY);
            putPoint(nw, Color.PURPLE);
            bef = nw;
        }

        addPolygon(Color.LIGHTBLUE, new Vector(-500, -500), new Vector(500, -500), new Vector(500, 500), new Vector(-500, 500));

        prepareLoop();

        refresh();
        setControllers();

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
