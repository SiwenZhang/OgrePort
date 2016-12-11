LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= libogreplugins

LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/../ \
                       $(OGRE_ROOT)/OgreMain/include \
                       $(OGRE_ROOT)/Components/RTShaderSystem/include \
                       $(OGRE_ROOT)/RenderSystems/GLES2/include \
                       $(OGRE_ROOT)/RenderSystems/GLES2/src/GLSLES/include \
                       $(OGRE_ROOT)/RenderSystems/GLES2/include/Android \
                       $(OGRE_ROOT)/Plugins/ParticleFX/include \
                       $(OGRE_ROOT)/Plugins/OctreeSceneManager/include \
                       $(FREEIMAGE_ROOT)/Source \
                       $(ZZIP_ROOT)

LOCAL_CFLAGS		:= -DFREEIMAGE_LIB=1 -DOGRE_NONCLIENT_BUILD=1
#LOCAL_LDLIBS		:= -ldl -llog -lz -lGLESv2
LOCAL_SRC_FILES		:= \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreAreaEmitter.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreBoxEmitter.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreColourFaderAffector.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreColourFaderAffector2.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreColourImageAffector.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreColourInterpolatorAffector.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreCylinderEmitter.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreDeflectorPlaneAffector.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreDirectionRandomiserAffector.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreEllipsoidEmitter.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreHollowEllipsoidEmitter.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreLinearForceAffector.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreParticleFXPlugin.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgrePointEmitter.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreRingEmitter.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreRotationAffector.cpp \
				$(OGRE_ROOT)/PlugIns/ParticleFX/src/OgreScaleAffector.cpp \
				$(OGRE_ROOT)/PlugIns/OctreeSceneManager/src/OgreOctree.cpp \
                $(OGRE_ROOT)/PlugIns/OctreeSceneManager/src/OgreOctreeCamera.cpp \
                $(OGRE_ROOT)/PlugIns/OctreeSceneManager/src/OgreOctreeNode.cpp \
                $(OGRE_ROOT)/PlugIns/OctreeSceneManager/src/OgreOctreePlugin.cpp \
                $(OGRE_ROOT)/PlugIns/OctreeSceneManager/src/OgreOctreeSceneManager.cpp \
                $(OGRE_ROOT)/PlugIns/OctreeSceneManager/src/OgreOctreeSceneManagerDll.cpp \
                $(OGRE_ROOT)/PlugIns/OctreeSceneManager/src/OgreOctreeSceneQuery.cpp \

include $(BUILD_STATIC_LIBRARY)