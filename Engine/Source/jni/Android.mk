LOCAL_PATH := $(call my-dir)
FILE_LIST := $(wildcard $(LOCAL_PATH)/../*.cpp)

include $(CLEAR_VARS)

LOCAL_LDLIBS := -llog
LOCAL_CPPFLAGS += -DPLATFORM_ANDROID

LOCAL_MODULE    := engine
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

include $(BUILD_SHARED_LIBRARY)