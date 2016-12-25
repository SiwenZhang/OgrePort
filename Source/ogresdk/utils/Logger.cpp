//
//  Logger.cpp
//  ogresdk
//
//  Created by liu enbao on 12/25/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#include "Logger.h"

#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>

#include <string>

#include <log4cpp/Portability.hh>
#include <log4cpp/LayoutAppender.hh>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/Category.hh>

#ifdef BUILD_TARGET_ANDROID
#include <android/log.h>
#endif

namespace log4cpp {
    
    /**
     * OgreAppender appends LoggingEvents to custom appender.
     **/
    class OgreAppender : public LayoutAppender {
    public:
        OgreAppender(const std::string& name);
        virtual ~OgreAppender();
        
        virtual bool reopen();
        virtual void close();
        
    protected:
        virtual void _append(const LoggingEvent& event);
    };
    
    OgreAppender::OgreAppender(const std::string& name) :
    LayoutAppender(name) {
    }
    
    OgreAppender::~OgreAppender() {
        close();
    }
    
    void OgreAppender::close() {
        // empty
    }
    
    void OgreAppender::_append(const LoggingEvent& event) {
        switch (event.priority) {
            case Priority::NOTICE:
#ifdef BUILD_TARGET_ANDROID
                __android_log_write(ANDROID_LOG_VERBOSE, event.categoryName.c_str(), event.message.c_str());
#else
                printf("%s: %s\n", event.categoryName.c_str(), event.message.c_str());
#endif
                break;
            case Priority::DEBUG:
#ifdef BUILD_TARGET_ANDROID
                __android_log_write(ANDROID_LOG_DEBUG, event.categoryName.c_str(), event.message.c_str());
#else
                printf("%s: %s\n", event.categoryName.c_str(), event.message.c_str());
#endif
                break;
            case Priority::INFO:
#ifdef BUILD_TARGET_ANDROID
                __android_log_write(ANDROID_LOG_INFO, event.categoryName.c_str(), event.message.c_str());
#else
                printf("%s: %s\n", event.categoryName.c_str(), event.message.c_str());
#endif
                break;
            case Priority::WARN:
#ifdef BUILD_TARGET_ANDROID
                __android_log_write(ANDROID_LOG_WARN, event.categoryName.c_str(), event.message.c_str());
#else
                printf("%s: %s\n", event.categoryName.c_str(), event.message.c_str());
#endif
                break;
            case Priority::ERROR:
#ifdef BUILD_TARGET_ANDROID
                __android_log_write(ANDROID_LOG_ERROR, event.categoryName.c_str(), event.message.c_str());
#else
                printf("%s: %s\n", event.categoryName.c_str(), event.message.c_str());
#endif
                break;
            default:
                break;
        }
    }
    
    bool OgreAppender::reopen() {
        return true;
    }
}

static pthread_once_t once = PTHREAD_ONCE_INIT;
static log4cpp::Appender *appender = NULL;
static log4cpp::Layout *layout = NULL;

bool Logger::InitLoggerContext() {
    layout = new log4cpp::SimpleLayout();
    appender = new log4cpp::OgreAppender("OgreAppender");
    
    appender->setLayout(layout);
    return true;
}

void once_run(void){
    Logger::InitLoggerContext();
}

Logger* Logger::GetLogger(const char* name) {
    pthread_once(&once, once_run);
    
    log4cpp::Category& category = log4cpp::Category::getInstance(name);
    category.setAppender(appender);
    category.setPriority(log4cpp::Priority::DEBUG);
    return new Logger(&category);
}

Logger::Logger(void* context)
    :mContext(context) {
    
}

void Logger::verbose(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log4cpp::Category* cat = (log4cpp::Category*)mContext;
    cat->logva(log4cpp::Priority::NOTICE, fmt, args);
    va_end(args);
}

void Logger::debug(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log4cpp::Category* cat = (log4cpp::Category*)mContext;
    cat->logva(log4cpp::Priority::DEBUG, fmt, args);
    va_end(args);
}

void Logger::info(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log4cpp::Category* cat = (log4cpp::Category*)mContext;
    cat->logva(log4cpp::Priority::INFO, fmt, args);
    va_end(args);
}

void Logger::warn(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log4cpp::Category* cat = (log4cpp::Category*)mContext;
    cat->logva(log4cpp::Priority::WARN, fmt, args);
    va_end(args);
}

void Logger::error(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    log4cpp::Category* cat = (log4cpp::Category*)mContext;
    cat->logva(log4cpp::Priority::ERROR, fmt, args);
    va_end(args);
}
