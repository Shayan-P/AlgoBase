package acm.geometry.camera;

import acm.geometry.Utils;
import acm.geometry.Vector;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.Scene;
import javafx.scene.input.KeyCode;
import javafx.util.Duration;

import java.util.HashMap;
import java.util.HashSet;

abstract public class Camera {
    final double width = 1000;
    final double height = 1000;

    protected final HashSet<KeyCode> isPressed = new HashSet<>();

    private Vector direction;
    private Vector position;

    Scene scene;

    Camera(Scene scene, Vector position, Vector direction){
        this.scene = scene;
        setPosition(position);
        setDirection(direction);
        setControllers();
    }

    abstract public Vector translate(Vector v);

    abstract protected void keyboardControl();

    private void setControllers(){
        scene.setOnKeyPressed(e->{
            isPressed.add(e.getCode());
        });
        scene.setOnKeyReleased(e->{
            isPressed.remove(e.getCode());
        });
        Timeline tt = new Timeline(new KeyFrame(Duration.millis(50), e->keyboardControl()));
        tt.setCycleCount(Timeline.INDEFINITE);
        tt.play();
    }

    public Vector getPosition(){
        return position;
    }
    public Vector getDirection(){
        return direction;
    }
    protected void setPosition(Vector position) {
        this.position = position;
    }
    protected void setDirection(Vector direction){
        this.direction = direction.changeLen(1/direction.len());
    }

    protected Vector[] getRelAxis(){
        Vector xAxis = direction.cross(new Vector(0, 0, 1)); // this is up
        Vector yAxis = xAxis.cross(direction);
        if(xAxis.len2() < Utils.eps){
            xAxis = new Vector(1, 0, 0);
            yAxis = new Vector(0, 1, 0);
        }
        xAxis = xAxis.changeLen(1/xAxis.len());
        yAxis = yAxis.changeLen(1/yAxis.len());
        return new Vector[]{xAxis, yAxis, direction};
    }
}
