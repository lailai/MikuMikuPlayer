#include <jni.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "MikuMikuPlayer.h"

JNIEXPORT void JNICALL Java_net_lailai_android_mmd_mikumikuplayer_MMPRenderer_NDKonDrawFrame(JNIEnv *env, jobject obj)
{
    glClearColor(1.0f, 1.0f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

JNIEXPORT void JNICALL Java_net_lailai_android_mmd_mikumikuplayer_MMPRenderer_NDKonSurfaceChanged(JNIEnv *env, jobject obj, jint width, jint height)
{
}

JNIEXPORT void JNICALL Java_net_lailai_android_mmd_mikumikuplayer_MMPRenderer_NDKonSurfaceCreated(JNIEnv *env, jobject obj)
{
}
