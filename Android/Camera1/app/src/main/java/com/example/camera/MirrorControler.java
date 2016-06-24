package com.example.camera;


import android.app.job.JobScheduler;
import android.hardware.Camera;

public class MirrorControler {
    private final SerialComManager comManager;
    private int angle = 0;
    private boolean goingUp = false;
    private boolean gotFace = false;
    private Thread mThread;

    MirrorControler(SerialComManager comManager){
        this.comManager = comManager;
    }

    public void foundFace(Camera.Face face){
        gotFace = true;
        if(face.rect.centerY() < -175 ){
            setAngle(angle-1);
        }
        if(face.rect.centerY() > 175){
            setAngle(angle+1);

        }
    }


    public void initMirrorControler(){
        mThread = new Thread(new MoveMirrorTask());
        mThread.start();
    }

    public void pauseMirrorController(){
        mThread.interrupt();
    }
    public void moveUp(){
        setAngle(angle+5);
    }

    public void moveDown(){
        setAngle(angle-5);
    }

    public void setAngle(int angle){
        goingUp = angle > this.angle;
        if(angle < 0){
            this.angle = 0;
        }else if(angle > 180){
            this.angle = 180;
        }
        else {
            this.angle = angle;
        }
//        sendMvCmd(angle);
    }

    private void sendMvCmd(int angle){
        if(comManager.opened) {
            comManager.usbWrite(String.format("M%d\n", angle));
        }
    }

    public class MoveMirrorTask implements Runnable{
        @Override
        public void run() {
            while (true) {
                if (gotFace) {
                    gotFace = false;
                }else{
                    if(goingUp){
                        if(angle == 180){
                            setAngle(angle-1);
                        }else{
                            setAngle(angle+1);
                        }
                    }else{
                        if(angle == 0){
                            setAngle(angle+1);
                        }else{
                            setAngle(angle-1);
                        }
                    }
                }
                sendMvCmd(angle);
                synchronized (this) {
                    try {
                        wait(100);
                    } catch (InterruptedException e) {
                        break;
                    }
                }
            }
        }
    }
}
