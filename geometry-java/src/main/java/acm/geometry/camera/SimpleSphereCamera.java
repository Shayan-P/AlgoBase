package acm.geometry.camera;

import acm.geometry.Vector;
import javafx.scene.Scene;
import javafx.scene.input.KeyCode;

public class SimpleSphereCamera extends Camera {
    double cameraAlpha;
    double cameraTeta;

    public SimpleSphereCamera(Scene scene, Vector position) {
        super(scene, position, position.neg());
        setAnglesBasedOnPosition();
    }

    public void setAnglesBasedOnPosition(){
        Vector pos = getPosition().changeLen(1/getPosition().len());
        cameraAlpha = Math.acos(pos.dot(new Vector(0, 0, 1)));
        Vector pos2d = new Vector(pos.dot(new Vector(1, 0, 0)), pos.dot(new Vector(0, 1, 0)));
        pos2d.changeLen(1/pos2d.len());
        cameraTeta = Math.atan2(pos2d.getY(), pos2d.getX());
        cameraTeta += Math.PI * 4;
        cameraTeta %= Math.PI * 2;
    }

    @Override
    public Vector translate(Vector v) {
        Vector[] axis = getRelAxis();
        v = v.add(getPosition().neg());
        double cof = 5000 / getPosition().len();
        return new Vector(
                axis[0].dot(v) * cof + width/2,
                - axis[1].dot(v) * cof + height/2,
                0);
    }

    @Override
    protected void keyboardControl() {
        if(isPressed.contains(KeyCode.UP)) {
            cameraAlpha -= 0.06;
            cameraAlpha = Math.max(cameraAlpha, 0.1);
        }
        if(isPressed.contains(KeyCode.DOWN)) {
            cameraAlpha += 0.06;
            cameraAlpha = Math.min(cameraAlpha, Math.PI - 0.1);
        }
        if(isPressed.contains(KeyCode.LEFT)) {
            cameraTeta -= 0.03;
            cameraTeta = (cameraTeta + Math.PI * 2) % (Math.PI * 2);
        }
        if(isPressed.contains(KeyCode.RIGHT)) {
            cameraTeta += 0.03;
            cameraTeta = (cameraTeta + Math.PI * 2) % (Math.PI * 2);
        }
        if(isPressed.contains(KeyCode.A)) {
            setPosition(getPosition().add(getDirection().changeLen(-getPosition().len() * 0.3)));
        }
        if(isPressed.contains(KeyCode.B)) {
            setPosition(getPosition().add(getDirection().changeLen(getPosition().len() * 0.3)));
        }

        Vector dir = new Vector(
                Math.sin(cameraAlpha) * Math.cos(cameraTeta),
                Math.sin(cameraAlpha) * Math.sin(cameraTeta),
                Math.cos(cameraAlpha)
        );
        setPosition(dir.changeLen(getPosition().len()));
        setDirection(dir.neg());
    }
}
