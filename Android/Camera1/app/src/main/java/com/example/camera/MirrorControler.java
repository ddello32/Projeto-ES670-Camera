package com.example.camera;


import android.hardware.Camera;

public class MirrorControler {
    private final SerialComManager comManager;
    private int angle = 0;

    MirrorControler(SerialComManager comManager){
        this.comManager = comManager;
    }

    public void foundFace(Camera.Face face){
        if(face.rect.centerY() < -175 ){
            setAngle(angle--);
        }
        if(face.rect.centerY() > 175){
            setAngle(angle++);

        }
    }

    public void moveUp(){
        setAngle(angle++);
    }

    public void moveDown(){
        setAngle(angle--);
    }

    public void setAngle(int angle){
        if(angle < 0){
            this.angle = 0;
        }else if(angle > 180){
            this.angle = 180;
        }
        else {
            this.angle = angle;
        }
        sendMvCmd(angle);
    }

    private void sendMvCmd(int angle){
        comManager.usbWrite(String.format("M%d\n", angle));
    }
}
