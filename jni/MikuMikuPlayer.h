#ifndef _MIKUMIKUPLAYER_H_
#define _MIKUMIKUPLAYER_H_

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_net_lailai_android_mmd_mikumikuplayer_MMPRenderer_NDKonDrawFrame(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_net_lailai_android_mmd_mikumikuplayer_MMPRenderer_NDKonSurfaceChanged(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_net_lailai_android_mmd_mikumikuplayer_MMPRenderer_NDKonSurfaceCreated(JNIEnv *env, jobject obj);

#ifdef __cplusplus
}
#endif

#endif
