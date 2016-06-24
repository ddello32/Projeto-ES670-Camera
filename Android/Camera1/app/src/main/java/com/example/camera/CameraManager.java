package com.example.camera;

import android.content.Context;
import android.hardware.Camera;
import android.util.Log;
import android.view.ViewGroup;

public class CameraManager {
    public CameraManager(Context context){
        this.context = context;
    }

    private final Context context;

    private Camera mCamera;
    private CameraPreview mPreview;
    private FaceView faceView;

    public void initCameraPreview(ViewGroup parent, MirrorControler mirrorControler){

        // Create an instance of Camera
        if(mCamera == null) mCamera = getCameraInstance();
        faceView = new FaceView(context);

        mCamera.setFaceDetectionListener(new MyFaceDetectionListener(mirrorControler, faceView));

        // Create our Preview view and set it as the content of our activity.
        mPreview = new CameraPreview(context, mCamera);
        parent.addView(mPreview);
        parent.addView(faceView);
    }

    public void stopCameraPreview(){
        if(mCamera != null) {
            mCamera.release();
            mCamera = null;
        }
    }

    /** A safe way to get an instance of the Camera object. */
    public static Camera getCameraInstance(){
        Camera c = null;
        try {
            int i;
            Camera.CameraInfo teste = new Camera.CameraInfo();
            for (i=0; i < Camera.getNumberOfCameras(); i++){
                Camera.getCameraInfo(i, teste);
                if(teste.facing == Camera.CameraInfo.CAMERA_FACING_FRONT){
                    break;
                }
            }
            Log.d("PORRA", ""+i);
            c = Camera.open(i);
        }
        catch (Exception e){
            // Camera is not available (in use or does not exist)
        }
        return c; // returns null if camera is unavailable
    }
}
