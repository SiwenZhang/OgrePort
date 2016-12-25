LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE        := ogrenative

LOCAL_C_INCLUDES    := \
               $(OGRENATIVE_ROOT)/ \
               $(OGRESDK_ROOT)/interface \

LOCAL_SRC_FILES := $(OGRENATIVE_ROOT)/NativeActivity.cpp \
                   $(OGRENATIVE_ROOT)/Android.cpp \
                   $(OGRENATIVE_ROOT)/Notification.cpp \
                   $(OGRENATIVE_ROOT)/ClassLoader.cpp \
                   $(OGRENATIVE_ROOT)/NotificationManager.cpp \
                   $(OGRENATIVE_ROOT)/AndroidMain.cpp \

LOCAL_STATIC_LIBRARIES := \

LOCAL_LDLIBS        := -ldl -llog -lz -landroid

LOCAL_CFLAGS += -DBUILD_TARGET_ANDROID

include $(BUILD_SHARED_LIBRARY)