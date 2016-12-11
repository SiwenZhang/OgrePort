LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= libogrerendersystems

LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/../ \
                       $(OGRE_ROOT)/OgreMain/include \
                       $(OGRE_ROOT)/Components/RTShaderSystem/include \
                       $(OGRE_ROOT)/RenderSystems/GLES2/include/EGL/Android \
                       $(OGRE_ROOT)/RenderSystems/GLES2/include/EGL \
                       $(OGRE_ROOT)/RenderSystems/GLES2/include \
                       $(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/include \
                       $(OGRE_ROOT)/RenderSystems/GLES2/src/StateCacheManager \
                       $(OGRE_ROOT)/Plugins/ParticleFX/include \
                       $(FREEIMAGE_ROOT)/Source \
                       $(ZZIP_ROOT)

LOCAL_CFLAGS		:= -DFREEIMAGE_LIB=1 -DOGRE_NONCLIENT_BUILD=1
#LOCAL_LDLIBS		:= -ldl -llog -lz -lEGL -lGLESv2

LOCAL_STATIC_LIBRARIES := \
				libogremain

LOCAL_SRC_FILES		:= \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2Context.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2DefaultHardwareBufferManager.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2DepthBuffer.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2EngineDLL.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2FBOMultiRenderTarget.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2FBORenderTexture.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2FrameBufferObject.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2GpuProgram.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2GpuProgramManager.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2HardwareBufferManager.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2HardwareIndexBuffer.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2HardwarePixelBuffer.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2HardwareVertexBuffer.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2PixelFormat.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2Plugin.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2RenderSystem.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2RenderTexture.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2Support.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2Texture.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2TextureManager.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2HardwareOcclusionQuery.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2StateCacheManager.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2HardwareUniformBuffer.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2RenderToVertexBuffer.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/StateCacheManager/OgreGLES2StateCacheManagerImp.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/StateCacheManager/OgreGLES2UniformCacheImp.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESExtSupport.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESGpuProgram.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESLinkProgram.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESLinkProgramManager.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESPreprocessor.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESProgram.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESProgramFactory.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESProgramPipelineManager.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESProgramPipeline.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESProgramCommon.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESProgramManagerCommon.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2UniformCache.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/OgreGLES2VertexDeclaration.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/EGL/OgreEGLSupport.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/EGL/OgreEGLContext.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/EGL/OgreEGLWindow.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/EGL/Android/OgreAndroidEGLContext.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/EGL/Android/OgreAndroidEGLSupport.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/EGL/Android/OgreAndroidEGLWindow.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/EGL/Android/OgreAndroidResource.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/EGL/Android/OgreAndroidResourceManager.cpp \
				$(OGRE_ROOT)/RenderSystems/GLES2/src/gles3w.cpp \

include $(BUILD_STATIC_LIBRARY)