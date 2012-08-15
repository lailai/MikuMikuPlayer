LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := mmp
LOCAL_SRC_FILES := MikuMikuPlayer.cpp
LOCAL_CPPFLAGS  :=
LOCAL_LDLIBS    := -lGLESv2

include $(BUILD_SHARED_LIBRARY)
