/*
 * Copyright (c) 2012 lailai. All Rights Reserved.
 */

#include <jni.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "MikuMikuPlayer.h"
#include "CMMPRenderer.h"

static CMMPRenderer renderer;

JNIEXPORT void JNICALL Java_net_lailai_android_mmd_mikumikuplayer_MMPRenderer_NDKonDrawFrame(JNIEnv *env, jobject obj)
{
    renderer.render();
}

JNIEXPORT void JNICALL Java_net_lailai_android_mmd_mikumikuplayer_MMPRenderer_NDKonSurfaceChanged(JNIEnv *env, jobject obj, jint width, jint height)
{
	renderer.changed(width, height);
}

JNIEXPORT void JNICALL Java_net_lailai_android_mmd_mikumikuplayer_MMPRenderer_NDKonSurfaceCreated(JNIEnv *env, jobject obj)
{
    renderer.init();
}
