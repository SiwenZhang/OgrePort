LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES	:= \
            $(ZZIP_ROOT)

LOCAL_SRC_FILES := \
            $(ZZIP_ROOT)/zzip/dir.c \
            $(ZZIP_ROOT)/zzip/err.c \
            $(ZZIP_ROOT)/zzip/fetch.c \
            $(ZZIP_ROOT)/zzip/file.c \
            $(ZZIP_ROOT)/zzip/fseeko.c \
            $(ZZIP_ROOT)/zzip/info.c \
            $(ZZIP_ROOT)/zzip/memdisk.c \
            $(ZZIP_ROOT)/zzip/mmapped.c \
            $(ZZIP_ROOT)/zzip/plugin.c \
            $(ZZIP_ROOT)/zzip/stat.c \
            $(ZZIP_ROOT)/zzip/write.c \
            $(ZZIP_ROOT)/zzip/zip.c

LOCAL_MODULE := libzzip
LOCAL_CFLAGS += -O3 -DUSE_MMAP

include $(BUILD_STATIC_LIBRARY)

