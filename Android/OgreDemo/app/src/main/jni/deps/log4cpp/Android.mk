LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := liblog4cpp

LOCAL_C_INCLUDES    := $(LOG4CPP_ROOT)/include \
                       $(LOG4CPP_ROOT)/src

LOCAL_SRC_FILES     :=\
        $(LOG4CPP_ROOT)/src/AbortAppender.cpp \
        $(LOG4CPP_ROOT)/src/Appender.cpp \
        $(LOG4CPP_ROOT)/src/AppendersFactory.cpp \
        $(LOG4CPP_ROOT)/src/AppenderSkeleton.cpp \
        $(LOG4CPP_ROOT)/src/BasicConfigurator.cpp \
        $(LOG4CPP_ROOT)/src/BasicLayout.cpp \
        $(LOG4CPP_ROOT)/src/BufferingAppender.cpp \
        $(LOG4CPP_ROOT)/src/Category.cpp \
        $(LOG4CPP_ROOT)/src/CategoryStream.cpp \
        $(LOG4CPP_ROOT)/src/Configurator.cpp \
        $(LOG4CPP_ROOT)/src/DailyRollingFileAppender.cpp \
        $(LOG4CPP_ROOT)/src/DllMain.cpp \
        $(LOG4CPP_ROOT)/src/DummyThreads.cpp \
        $(LOG4CPP_ROOT)/src/FactoryParams.cpp \
        $(LOG4CPP_ROOT)/src/FileAppender.cpp \
        $(LOG4CPP_ROOT)/src/Filter.cpp \
        $(LOG4CPP_ROOT)/src/FixedContextCategory.cpp \
        $(LOG4CPP_ROOT)/src/HierarchyMaintainer.cpp \
        $(LOG4CPP_ROOT)/src/IdsaAppender.cpp \
        $(LOG4CPP_ROOT)/src/LayoutAppender.cpp \
        $(LOG4CPP_ROOT)/src/LayoutsFactory.cpp \
        $(LOG4CPP_ROOT)/src/LevelEvaluator.cpp \
        $(LOG4CPP_ROOT)/src/Localtime.cpp \
        $(LOG4CPP_ROOT)/src/LoggingEvent.cpp \
        $(LOG4CPP_ROOT)/src/Manipulator.cpp \
        $(LOG4CPP_ROOT)/src/MSThreads.cpp \
        $(LOG4CPP_ROOT)/src/NDC.cpp \
        $(LOG4CPP_ROOT)/src/NTEventLogAppender.cpp \
        $(LOG4CPP_ROOT)/src/OmniThreads.cpp \
        $(LOG4CPP_ROOT)/src/OstreamAppender.cpp \
        $(LOG4CPP_ROOT)/src/PassThroughLayout.cpp \
        $(LOG4CPP_ROOT)/src/PatternLayout.cpp \
        $(LOG4CPP_ROOT)/src/PortabilityImpl.cpp \
        $(LOG4CPP_ROOT)/src/Priority.cpp \
        $(LOG4CPP_ROOT)/src/Properties.cpp \
        $(LOG4CPP_ROOT)/src/PropertyConfigurator.cpp \
        $(LOG4CPP_ROOT)/src/PropertyConfiguratorImpl.cpp \
        $(LOG4CPP_ROOT)/src/PThreads.cpp \
        $(LOG4CPP_ROOT)/src/RemoteSyslogAppender.cpp \
        $(LOG4CPP_ROOT)/src/RollingFileAppender.cpp \
        $(LOG4CPP_ROOT)/src/SimpleConfigurator.cpp \
        $(LOG4CPP_ROOT)/src/SimpleLayout.cpp \
        $(LOG4CPP_ROOT)/src/SmtpAppender.cpp \
        $(LOG4CPP_ROOT)/src/snprintf.c \
        $(LOG4CPP_ROOT)/src/StringQueueAppender.cpp \
        $(LOG4CPP_ROOT)/src/StringUtil.cpp \
        $(LOG4CPP_ROOT)/src/SyslogAppender.cpp \
        $(LOG4CPP_ROOT)/src/TimeStamp.cpp \
        $(LOG4CPP_ROOT)/src/TriggeringEventEvaluatorFactory.cpp \
        $(LOG4CPP_ROOT)/src/Win32DebugAppender.cpp \

LOCAL_CFLAGS := -O3 -fPIC
LOCAL_CFLAGS += -W -Wall
LOCAL_CFLAGS += -fPIC -DPIC
LOCAL_CFLAGS += -DLOG4CPP_HAVE_SSTREAM
LOCAL_CFLAGS += -DBUILD_TARGET_ANDROID

include $(BUILD_STATIC_LIBRARY)