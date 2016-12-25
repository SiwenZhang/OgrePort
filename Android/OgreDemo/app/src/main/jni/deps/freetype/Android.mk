LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := libfreetype

LOCAL_C_INCLUDES    := $(FREETYPE_ROOT)/include $(FREETYPE_ROOT)/builds/unix

LOCAL_SRC_FILES     :=\
		$(FREETYPE_ROOT)/src/autofit/autofit.c\
		$(FREETYPE_ROOT)/src/base/ftbase.c\
		$(FREETYPE_ROOT)/src/base/ftbbox.c\
		$(FREETYPE_ROOT)/src/base/ftbitmap.c\
		$(FREETYPE_ROOT)/src/base/ftfstype.c\
		$(FREETYPE_ROOT)/src/base/ftgasp.c\
		$(FREETYPE_ROOT)/src/base/ftglyph.c\
		$(FREETYPE_ROOT)/src/base/ftinit.c\
		$(FREETYPE_ROOT)/src/base/ftmm.c\
		$(FREETYPE_ROOT)/src/base/ftpfr.c\
		$(FREETYPE_ROOT)/src/base/ftstroke.c\
		$(FREETYPE_ROOT)/src/base/ftsynth.c\
		$(FREETYPE_ROOT)/src/base/ftsystem.c\
		$(FREETYPE_ROOT)/src/base/fttype1.c\
		$(FREETYPE_ROOT)/src/base/ftwinfnt.c\
		$(FREETYPE_ROOT)/src/bdf/bdf.c\
		$(FREETYPE_ROOT)/src/bzip2/ftbzip2.c\
		$(FREETYPE_ROOT)/src/cache/ftcache.c\
		$(FREETYPE_ROOT)/src/cff/cff.c\
		$(FREETYPE_ROOT)/src/cid/type1cid.c\
		$(FREETYPE_ROOT)/src/gzip/ftgzip.c\
		$(FREETYPE_ROOT)/src/lzw/ftlzw.c\
		$(FREETYPE_ROOT)/src/pcf/pcf.c\
		$(FREETYPE_ROOT)/src/pfr/pfr.c\
		$(FREETYPE_ROOT)/src/psaux/psaux.c\
		$(FREETYPE_ROOT)/src/pshinter/pshinter.c\
		$(FREETYPE_ROOT)/src/psnames/psmodule.c\
		$(FREETYPE_ROOT)/src/raster/raster.c\
		$(FREETYPE_ROOT)/src/sfnt/sfnt.c\
		$(FREETYPE_ROOT)/src/smooth/smooth.c\
		$(FREETYPE_ROOT)/src/truetype/truetype.c\
		$(FREETYPE_ROOT)/src/type1/type1.c\
		$(FREETYPE_ROOT)/src/type42/type42.c\
		$(FREETYPE_ROOT)/src/winfonts/winfnt.c

LOCAL_CFLAGS := -O3 -fPIC
LOCAL_CFLAGS += -W -Wall
LOCAL_CFLAGS += -fPIC -DPIC
LOCAL_CFLAGS += "-DDARWIN_NO_CARBON"
LOCAL_CFLAGS += -DFT2_BUILD_LIBRARY

include $(BUILD_STATIC_LIBRARY)