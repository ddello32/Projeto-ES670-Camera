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
            angle--;
            sendMvCmd(angle);
        }
        if(face.rect.centerY() > 175){
            angle++;
            sendMvCmd(angle);
        }
    }

    public void moveUp(){
        angle++;
        sendMvCmd(angle);
    }

    public void moveDown(){
        angle--;
        sendMvCmd(angle);
    }

    public void setAngle(int angle){
        this.angle = angle;
        sendMvCmd(angle);
    }

    private void sendMvCmd(int angle){
        comManager.usbWrite(String.format("P%d\n", angle));
    }
}
