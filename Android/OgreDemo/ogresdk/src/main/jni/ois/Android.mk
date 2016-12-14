LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    	:= libois

LOCAL_C_INCLUDES	:= $(OIS_ROOT)/includes

LOCAL_SRC_FILES 	:=  \
                $(OIS_ROOT)/src/OISEffect.cpp \
                $(OIS_ROOT)/src/OISException.cpp \
                $(OIS_ROOT)/src/OISForceFeedback.cpp \
                $(OIS_ROOT)/src/OISInputManager.cpp \
                $(OIS_ROOT)/src/OISJoystick.cpp \
                $(OIS_ROOT)/src/OISKeyboard.cpp \
                $(OIS_ROOT)/src/OISObject.cpp

LOCAL_CFLAGS		:= -DBUILD_FOR_ANDROID

include $(BUILD_STATIC_LIBRARY)