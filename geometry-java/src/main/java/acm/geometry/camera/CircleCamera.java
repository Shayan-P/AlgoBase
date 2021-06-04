package acm.geometry.camera;

import acm.geometry.Utils;
import acm.geometry.Vector;
import javafx.scene.Scene;
import javafx.scene.input.KeyCode;

public class CircleCamera extends Camera {
    double visibleAlphaRange = Math.PI * 0.35;

    public CircleCamera(Scene scene, Vector position, Vector direction) {
        super(scene, position, direction);
    }

    @Override
    public Vector translate(Vector v) {
        Vector[] axis = getRelAxis();
        v = v.add(getPosition().neg());
        double alpha = Math.acos(v.dot(getDirection()) / v.len());
        double x = axis[0].dot(v);
        double y = axis[1].dot(v);
        // alpha is to know how to stretch the picture
        alpha = Math.min(alpha, visibleAlphaRange - 0.1);
        double stretch = Math.tan(alpha / visibleAlphaRange * (Math.PI/2));
        return new Vector(
                width/2 + x * stretch,
                height/2 + y * stretch
        );
    }

    @Override
    protected void keyboardControl() {
        if(isPressed.contains(KeyCode.UP)) {
            setDirection(getDirection().add(getRelAxis()[1].changeLen(0.05)));
        }
        if(isPressed.contains(KeyCode.DOWN)) {
            setDirection(getDirection().add(getRelAxis()[1].changeLen(-0.05)));
        }
        if(isPressed.contains(KeyCode.LEFT)) {
            setDirection(getDirection().add(getRelAxis()[0].changeLen(-0.05)));
        }
        if(isPressed.contains(KeyCode.RIGHT)) {
            setDirection(getDirection().add(getRelAxis()[0].changeLen(0.05)));
        }
        if(isPressed.contains(KeyCode.A)) {
            setPosition(getPosition().add(getDirection().changeLen(7)));
        }
        if(isPressed.contains(KeyCode.B)) {
            setPosition(getPosition().add(getDirection().changeLen(-7)));
        }
    }
}
