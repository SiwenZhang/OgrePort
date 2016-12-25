LOCAL_PATH := $(call my-dir)

#define the source for the app
SOURCE_ROOT := $(LOCAL_PATH)/../../../../../../Source
OGRESDK_ROOT = $(SOURCE_ROOT)/ogresdk
OGREAPP_ROOT = $(SOURCE_ROOT)/ogreapp
THIRDPARTY_ROOT = $(SOURCE_ROOT)/thirdparty
ZZIP_ROOT = $(THIRDPARTY_ROOT)/Zzip
FREEIMAGE_ROOT = $(THIRDPARTY_ROOT)/FreeImage
OGRE_ROOT = $(THIRDPARTY_ROOT)/Ogre
FREETYPE_ROOT = $(THIRDPARTY_ROOT)/FreeType
OIS_ROOT = $(THIRDPARTY_ROOT)/ois
MYGUI_ROOT = $(THIRDPARTY_ROOT)/MyGUI
LOG4CPP_ROOT = $(THIRDPARTY_ROOT)/log4cpp

include $(call all-subdir-makefiles)