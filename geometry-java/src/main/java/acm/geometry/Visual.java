package acm.geometry;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class Visual extends Application {
    double width = 1000;
    double height = 1000;
    double randomLen = (width/2) - 100;

    Pane pane = new Pane();
    Scene scene = new Scene(pane, width, height);

    Vector normalize(Vector v){
        return new Vector(v.x + width/2, -v.y + height/2);
    }
    void putPoint(Vector v, Color color){
        v = normalize(v);
        pane.getChildren().add(new Circle(v.x, v.y, 5, color));
    }
    void putTextUnderPoint(Vector v, String txt){
        v = normalize(v);
        Text text = new Text(txt);
        text.setX(v.x);
        text.setY(v.y - 10);
        pane.getChildren().add(text);
    }

    void putLine(Vector a, Vector b, Color color){
        a = normalize(a);
        b = normalize(b);
        Line line = new Line(a.x, a.y, b.x, b.y);
        line.setStroke(color);
        pane.getChildren().add(line);
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
        for(int i = 0; i < 30; i++) {
            Vector randomPoint = Vector.random(randomLen);
            if(hull.checkStrictInside(randomPoint))
                continue;
            putPoint(randomPoint, Color.GREEN);
            putLine(randomPoint, hull.getFistLineIntersection(randomPoint), Color.BLUE);
            putLine(randomPoint, hull.getSecondLineIntersection(randomPoint), Color.BLUE);
        }

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
