LOCAL_PATH := $(call my-dir)
FILE_LIST := $(wildcard $(LOCAL_PATH)/../../../Engine/Source/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Engine/Source/**/*.cpp)

include $(CLEAR_VARS)

LOCAL_MODULE    := engine
LOCAL_LDLIBS := -llog -lEGL -lGLESv3
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Engine/Source
LOCAL_CPPFLAGS += -DPLATFORM_ANDROID
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

include $(BUILD_SHARED_LIBRARY)