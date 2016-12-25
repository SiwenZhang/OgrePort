//
//  Logger.hpp
//  ogresdk
//
//  Created by liu enbao on 12/25/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#ifndef LOGGER_H
#define LOGGER_H

#ifndef LOGGER_DISABLED

class Logger {
public:
    void verbose(const char* fmt, ...);
    void debug(const char* fmt, ...);
    void info(const char* fmt, ...);
    void warn(const char* fmt, ...);
    void error(const char* fmt, ...);

public:
    static bool InitLoggerContext();
    static Logger* GetLogger(const char* name);
    
private:
    Logger(void* context);
    
private:
    void* mContext;
};

#define LOGGER_GLOBAL_INIT() \
        Logger::InitLoggerContext()

#define LOGGER_DECLARE(name)    \
                    static Logger* logger##name

#define LOGGER_IMPLEMENT(name)  \
                Logger* name::logger##name = Logger::GetLogger(#name)

#define LOGGER_DEFINE(name) \
                Logger* logger##name = Logger::GetLogger(#name)

#define LVERBOSE(name, ...) \
                logger##name->verbose(__VA_ARGS__)

#define LDEBUG(name, ...)   \
                logger##name->debug(__VA_ARGS__)

#define LINFO(name, ...)    \
                logger##name->info(__VA_ARGS__)

#define LWARN(name, ...)    \
                logger##name->warn(__VA_ARGS__)

#define LERROR(name, ...)   \
                logger##name->error(__VA_ARGS__)

#else

#define LOGGER_GLOBAL_INIT()
#define LOGGER_DECLARE(name)
#define LOGGER_IMPLEMENT(name)
#define LOGGER_DEFINE(name)

#define LVERBOSE(name, ...)
#define LDEBUG(name, ...)
#define LINFO(name, ...)
#define LWARN(name, ...)
#define LERROR(name, ...)

#endif

#endif /* LOGGER_H */
