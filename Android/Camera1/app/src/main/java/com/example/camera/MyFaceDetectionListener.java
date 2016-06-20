package com.example.camera;

import android.hardware.Camera;
import android.util.Log;

public class MyFaceDetectionListener implements Camera.FaceDetectionListener {
    private final MirrorControler mirrorControler;

    public MyFaceDetectionListener(MirrorControler mirrorControler){
        this.mirrorControler = mirrorControler;
    }

    @Override
    public void onFaceDetection(Camera.Face[] faces, Camera camera) {
        if (faces.length > 0){
            Log.d("MyFaceDetector", "Found Face: X = " + faces[0].rect.centerX() + ", Y = " + faces[0].rect.centerY());
            mirrorControler.foundFace(faces[0]);
        }
    }
}
