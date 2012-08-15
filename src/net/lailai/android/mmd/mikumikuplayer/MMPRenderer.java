/*
 * Copyright (c) 2012 lailai All Rights Reserved.
 */

package net.lailai.android.mmd.mikumikuplayer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;

/**
 * OpenGL ESの描画クラスです。
 * @author lailai
 */
public class MMPRenderer implements Renderer {

    static {
        System.loadLibrary("mmp");
    }

    /**
     * 描画用クラスのインスタンスを生成します。
     */
    public MMPRenderer() {
        // nothing to do
    }

    /**
     * NDKでフレームを描画します。
     */
    public native static void NDKonDrawFrame();

    /**
     * NDKでSurface変更時の設定をします。
     * @param width 画面幅
     * @param height 画面高さ
     */
    public native static void NDKonSurfaceChanged(int width, int height);

    /**
     * NDKでSurface作成処理を実施します。
     */
    public native static void NDKonSurfaceCreated();

    /* (非 Javadoc)
     * @see android.opengl.GLSurfaceView.Renderer#onDrawFrame(javax.microedition.khronos.opengles.GL10)
     */
    public void onDrawFrame(GL10 arg0) {
        NDKonDrawFrame();
    }

    /* (非 Javadoc)
     * @see android.opengl.GLSurfaceView.Renderer#onSurfaceChanged(javax.microedition.khronos.opengles.GL10, int, int)
     */
    public void onSurfaceChanged(GL10 arg0, int arg1, int arg2) {
        NDKonSurfaceChanged(arg1, arg2);
    }

    /* (非 Javadoc)
     * @see android.opengl.GLSurfaceView.Renderer#onSurfaceCreated(javax.microedition.khronos.opengles.GL10, javax.microedition.khronos.egl.EGLConfig)
     */
    public void onSurfaceCreated(GL10 arg0, EGLConfig arg1) {
        NDKonSurfaceCreated();
    }

}
