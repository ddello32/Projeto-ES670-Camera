package com.example.camera;

import android.hardware.Camera;
import android.util.Log;

public class MyFaceDetectionListener implements Camera.FaceDetectionListener {
    private final MirrorControler mirrorControler;
    private final FaceView faceView;

    public MyFaceDetectionListener(MirrorControler mirrorControler, FaceView faceView){
        this.mirrorControler = mirrorControler;
        this.faceView = faceView;
    }

    @Override
    public void onFaceDetection(Camera.Face[] faces, Camera camera) {
        if (faces.length > 0){
            Log.d("PORRA", "Found Face: X = " + faces[0].rect.centerX() + ", Y = " + faces[0].rect.centerY());
            mirrorControler.foundFace(faces[0]);
            faceView.setFace(faces[0]);
        }else {
            faceView.setFace(null);
        }
    }
}
