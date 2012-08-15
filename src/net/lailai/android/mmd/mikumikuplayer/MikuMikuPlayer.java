/*
 * Copyright (c) 2012 lailai All Rights Reserved.
 */

package net.lailai.android.mmd.mikumikuplayer;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.Menu;

public class MikuMikuPlayer extends Activity {

    // OpenGL ESのViewを作成
    GLSurfaceView glView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        glView = new GLSurfaceView(this);

        // OpenGL ESのバージョンは2.0
        glView.setEGLContextClientVersion(2);

        // Rendererをセット
        glView.setRenderer(new MMPRenderer());

        setContentView(glView);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_mmp, menu);
        return true;
    }

}
