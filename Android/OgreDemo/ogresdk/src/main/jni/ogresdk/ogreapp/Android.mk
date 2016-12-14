LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= ogreapp

LOCAL_C_INCLUDES	:= \
               $(LOCAL_PATH)/../../ogre \
               $(OGRE_ROOT)/OgreMain/include \
               $(OGRE_ROOT)/OgreMain/include/Android \
               $(OGRE_ROOT)/Components/RTShaderSystem/include \
               $(OGRE_ROOT)/Components/Overlay/include \
               $(OGRE_ROOT)/RenderSystems/GLES2/include \
               $(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/include \
               $(OGRE_ROOT)/RenderSystems/GLES2/include/Android \
               $(OGRE_ROOT)/RenderSystems/GLES2/include/EGL \
               $(OGRE_ROOT)/RenderSystems/GLES2/include/EGL/Android \
               $(OGRE_ROOT)/PlugIns/OctreeSceneManager/include \
               $(OGRE_ROOT)/Plugins/ParticleFX/include \
               $(OIS_ROOT)/includes \

LOCAL_LDLIBS		:= -ldl -llog -lz -landroid -lEGL -lGLESv2

LOCAL_SRC_FILES		:= \
                OgreApp.cpp \
                AndroidLogListener.cpp \


LOCAL_STATIC_LIBRARIES := \
                libzzip \
                libFreeImage \
                libogrecomponents \
                libogremain \
                libogrerendersystems \
                libogreplugins \
                cpufeatures \
                libois \
#                android_native_app_glue \

LOCAL_SHARED_LIBRARIES := \
				ogrenative

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/cpufeatures)
#$(call import-module,android/native_app_glue)