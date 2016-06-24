package com.example.camera;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.RectF;
import android.hardware.Camera;
import android.view.View;

public class FaceView extends View{
    Camera.Face  face = null;
    Matrix matrix = new Matrix();
    Paint paint;
    RectF r = new RectF();

    public FaceView(Context context) {
        super(context);
        paint = new Paint();
        paint.setStrokeWidth(2);
        paint.setColor(Color.GREEN);
        paint.setStyle(Paint.Style.STROKE);
    }

    public void setFace(Camera.Face face){
        this.face = face;
        invalidate();
    }

    @Override
    protected void onAttachedToWindow() {
        super.onAttachedToWindow();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        if (face != null && matrix != null) {
            r.set(face.rect);
            // Need mirror for front camera.
            matrix.setScale(-1 , 1);
            matrix.postRotate(0);
            matrix.postScale(getWidth() / 2000f, getHeight() / 2000f);
            matrix.postTranslate(getWidth() / 2f, getHeight() / 2f);
            matrix.mapRect(r);
            canvas.drawRect(r, paint);
        }
    }
}
