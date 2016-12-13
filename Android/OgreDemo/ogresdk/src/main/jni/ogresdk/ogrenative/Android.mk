LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= ogrenative

LOCAL_C_INCLUDES	:= \
               $(LOCAL_PATH)/ \

LOCAL_SRC_FILES := NativeActivity.cpp \
                    Android.cpp \
                    Notification.cpp \
                    ClassLoader.cpp \
                    NotificationManager.cpp \
                    AndroidMain.cpp \

LOCAL_STATIC_LIBRARIES := \

LOCAL_LDLIBS		:= -ldl -llog -lz -landroid

include $(BUILD_SHARED_LIBRARY)