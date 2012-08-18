LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := mmp
LOCAL_SRC_FILES := MikuMikuPlayer.cpp CMMPRenderer.cpp CImageLoader.cpp bitmap24.cpp
LOCAL_CPPFLAGS  :=
LOCAL_LDLIBS    := -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
