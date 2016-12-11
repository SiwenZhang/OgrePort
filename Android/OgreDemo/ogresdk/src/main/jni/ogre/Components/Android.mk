LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= libogrecomponents

LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/../ \
                       $(OGRE_ROOT)/OgreMain/include \
                       $(OGRE_ROOT)/Components/RTShaderSystem/include \
                       $(OGRE_ROOT)/Components/Overlay/include \
                       $(OGRE_ROOT)/RenderSystems/GLES2/include \
                       $(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/include \
                       $(OGRE_ROOT)/RenderSystems/GLES2/include/Android \
                       $(OGRE_ROOT)/Plugins/ParticleFX/include \
                       $(FREEIMAGE_ROOT)/Source \
                       $(ZZIP_ROOT) \
                       $(FREETYPE_ROOT)/include

LOCAL_CFLAGS		:= -DFREEIMAGE_LIB=1 -DOGRE_NONCLIENT_BUILD=1
#LOCAL_LDLIBS		:= -ldl -llog -lz -lGLESv2
LOCAL_SRC_FILES		:= \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderExIntegratedPSSM3.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderExLayeredBlending.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderExNormalMapLighting.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderExPerPixelLighting.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderExHardwareSkinning.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderFFPColour.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderFFPFog.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderFFPLighting.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderFFPRenderStateBuilder.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderFFPTexturing.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderFFPTransform.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderFunction.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderFunctionAtom.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderGenerator.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderGLSLESProgramProcessor.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderGLSLESProgramWriter.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderMaterialSerializerListener.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderParameter.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderProgram.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderProgramManager.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderProgramProcessor.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderProgramSet.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderProgramWriter.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderProgramWriterManager.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderRenderState.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderScriptTranslator.cpp \
                $(OGRE_ROOT)/Components/RTShaderSystem/src/OgreShaderSubRenderState.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreBorderPanelOverlayElement.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreFont.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreFontManager.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreOverlay.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreOverlayContainer.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreOverlayElement.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreOverlayElementCommands.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreOverlayElementFactory.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreOverlayManager.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreOverlayProfileSessionListener.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreOverlaySystem.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgrePanelOverlayElement.cpp \
                $(OGRE_ROOT)/Components/Overlay/src/OgreTextAreaOverlayElement.cpp \


LOCAL_STATIC_LIBRARIES := libfreetype \

include $(BUILD_STATIC_LIBRARY)