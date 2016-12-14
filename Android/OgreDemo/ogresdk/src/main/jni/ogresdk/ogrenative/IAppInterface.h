#ifndef OGRE_IAPPINTERFACE_H
#define OGRE_IAPPINTERFACE_H

#include "IAndroidHandler.h"
#include "AndroidMessage.h"

#include <android/native_window_jni.h> // requires ndk r5 or newer
#include <android/asset_manager_jni.h>

namespace OgreNative
{

typedef void (*MessageCallbackFunction)( const AndroidMessage& );

class ClassLoader;
class NotificationManager;

class IAppInterface {
public:
	virtual void PollEvents() = 0;
	virtual void SetEventCallback( MessageCallbackFunction pCallback ) = 0;
	virtual void SetEventHandler( IAndroidHandler* pHandler ) = 0;

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

	virtual ~IAppInterface() {}
};

}

#endif