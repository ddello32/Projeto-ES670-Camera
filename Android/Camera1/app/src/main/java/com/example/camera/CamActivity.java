package com.example.camera;

import android.os.Bundle;
import android.app.Activity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;

import java.io.IOException;

public class CamActivity extends Activity {
    CameraManager camManager = new CameraManager(this);
    SerialComManager comManager;
    MirrorControler mirrorControler;
    ViewGroup previewFrame;
    FaceView faceView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        comManager = new SerialComManager(this);
        mirrorControler = new MirrorControler(comManager);
        setContentView(R.layout.activity_cam);
        previewFrame = (FrameLayout) findViewById(R.id.camera_preview);
        camManager.initCameraPreview(previewFrame, mirrorControler);
        comManager.initUsbConnection();
        // Add a listener to the Up button
        Button upButton = (Button) findViewById(R.id.Button_Up);
        upButton.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        mirrorControler.moveUp();
                    }
                }
        );

        // Add a listener to the Down button
        Button downButton = (Button) findViewById(R.id.Button_Down);
        downButton.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        mirrorControler.moveDown();
                    }
                }
        );

        // Add a listener to the Center button
        Button centerButton = (Button) findViewById(R.id.Button_Center);
        centerButton.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        mirrorControler.setAngle(90);
                    }
                }
        );
        downButton.bringToFront();
        upButton.bringToFront();
        centerButton.bringToFront();
    }

    @Override
    public void onPause(){
        super.onPause();
        camManager.stopCameraPreview();
        comManager.stopUsbConnection();
        mirrorControler.pauseMirrorController();
    }

    @Override
    protected void onResume() {
        super.onResume();
        camManager.initCameraPreview(previewFrame, mirrorControler);
        comManager.initUsbConnection();
        mirrorControler.initMirrorControler();
    }
}