//
//  IAppInterface.h
//  ogresdk
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#ifndef I_APPINTERFACE_H
#define I_APPINTERFACE_H

class IAppLifeCycle;

#include <string>

#ifdef BUILD_TARGET_ANDROID
// #include "AndroidMessage.h"

#include <android/native_window_jni.h> // requires ndk r5 or newer
#include <android/asset_manager_jni.h>

// typedef void (*MessageCallbackFunction)( const AndroidMessage& );

class ClassLoader;
class NotificationManager;
#endif

class IAppInterface {
public:
    virtual void PollEvents() = 0;
    virtual void SetEventHandler( IAppLifeCycle* pHandler ) = 0;
    
#ifdef BUILD_TARGET_ANDROID
    // virtual void SetEventCallback( MessageCallbackFunction pCallback ) = 0;
    
    virtual ANativeWindow* GetWindow() = 0;
    virtual AAssetManager* GetAssetManager() = 0;
    virtual bool IsWindowVisible() = 0;
    
    virtual void ShowKeyboard() = 0;
    virtual void HideKeyboard() = 0;
    
    virtual const char* GetAppDir() = 0;
    
    virtual JNIEnv* GetJNIEnv() = 0;
    virtual jobject GetJNIActivity() = 0;
    
    virtual ClassLoader* GetClassLoader() = 0;
    virtual NotificationManager* GetNotificationManager() = 0;
#else
    virtual void* getOgrePlayer() = 0;
    virtual std::string getResourcesPath() = 0;
#endif
    
    virtual ~IAppInterface() {
    
    }
};

#endif /* I_APPINTERFACE_H */
