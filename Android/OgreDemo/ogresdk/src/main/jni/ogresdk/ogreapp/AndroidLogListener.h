#ifndef __ANDROID_LOG_LISTENER_H
#define __ANDROID_LOG_LISTENER_H

#include "OgreLog.h"

class AndroidLogListener : public Ogre::LogListener
{
public:
    AndroidLogListener();

    virtual void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName);
};

#endif