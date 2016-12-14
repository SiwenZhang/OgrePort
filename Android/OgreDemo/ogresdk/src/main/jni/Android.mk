LOCAL_PATH := $(call my-dir)

#define the source for the app
SOURCE_ROOT := $(LOCAL_PATH)/../../../../../../Source
ZZIP_ROOT = $(SOURCE_ROOT)/Zzip
FREEIMAGE_ROOT = $(SOURCE_ROOT)/FreeImage
OGRE_ROOT = $(SOURCE_ROOT)/Ogre
FREETYPE_ROOT = $(SOURCE_ROOT)/FreeType
OIS_ROOT = $(SOURCE_ROOT)/ois

include $(call all-subdir-makefiles)