#ifndef OGRE_NATIVE_ACTIVTIY_H
#define OGRE_NATIVE_ACTIVTIY_H

#include <jni.h>

#include "AndroidMessage.h"
#include "IAppInterface.h"
#include "IAndroidHandler.h"
#include "ClassLoader.h"
#include "NotificationManager.h"

namespace OgreNative
{
//	typedef void (*MessageCallbackFunction)( const AndroidMessage& );

	class NativeActivity
	{
	public:
		void PollEvents();
		void SetEventCallback( MessageCallbackFunction pCallback );
		void SetEventHandler( IAndroidHandler* pHandler );

		void SetJNI( JNIEnv* pEnv, jobject pObj );

		ANativeWindow* GetWindow();
		AAssetManager* GetAssetManager();
		bool IsVisible() const;

		void ShowKeyboard();
		void HideKeyboard();

		NativeActivity();
		~NativeActivity();

		const char* GetAppDir() const;

		JNIEnv* GetJNI();
		jobject	GetContext();
		jobject	GetObject();
		jclass 	GetClass();

		ClassLoader& GetClassLoader();
		NotificationManager& GetNotificationManager();

		jobject GetSystemService( const char* pServiceName );

			// Application state
			virtual void OnApplicationShutdown();
			virtual void OnApplicationPaused();
			virtual void OnApplicationResumed();
			virtual void OnLowMemory();

			// Surface
			virtual void OnSurfaceChanged( int iFormat, int iWidth, int iHeight );
			virtual void OnSurfaceCreated( jobject pSurface );
			virtual void OnSurfaceDestroyed();

			// Window state
			virtual void OnWindowHidden();
			virtual void OnWindowShown();

			// Input
			virtual void OnTouch( int iPointerID, float fPosX, float fPosY, int iAction );
			virtual void OnKeyUp( int iKeyCode, int iUnicodeChar );

//			// Play Services
//			virtual void OnSignInSucceeded( char* pAccountName );
//			virtual void OnSignInFailed();

			virtual void setAssetManager(jobject pAssetManager);

            IAppInterface* GetAppInterface() {
                return mAppInterface;
            }

//			// Interfaces
//			virtual IAppStateInterface* GetAppStateInterface();

	private:
		ClassLoader	 m_ClassLoader;
		NotificationManager m_NotificationManager;

		bool PeekEvent( AndroidMessage& message );
		void DispatchMessage( const AndroidMessage& message );
		// void DispatchMessage( AndroidMessageType eMessage );

		void SetSurface( jobject pSurface );
		void SetVisible( bool bVisible );

		// void setAssetManager(jobject pAssetManager);

		// Callbacks
		MessageCallbackFunction m_pMessageCallback;
		IAndroidHandler*		m_pEventHandler;

		// Member variables
		char*			m_pAppDir;
		ANativeWindow* 	m_pWindow;
		AAssetManager*  m_pAssetManager;
		bool			m_bIsVisible;

		// JNI Variables
		JNIEnv* 	m_pEnv;
		jobject 	m_pObj;
		jclass		m_pJavaClass;

		jmethodID	m_hPeekMessageMethod;	// Peek message
		jmethodID	m_hPollMessagesMethod;	// Poll messages

		jmethodID	m_hShowKeyboardMethod; // Show keyboard
		jmethodID	m_hHideKeyboardMethod; // Hide keyboard

		jmethodID	m_hGetAppDirMethod;

		jmethodID	m_hGetSystemServiceMethod;

		// Context
		jmethodID	m_hGetContextMethod;
		jobject		m_pContext;

		// Message class
		jclass		m_hMessageClass;
		jfieldID	m_hMessageIDField;

// 		class NativeInterface : public INativeInterface
// 		{
// 		public:
// 			NativeInterface( NativeActivity* pActivity );
// 			~NativeInterface();

// 			// Application state
// 			virtual void OnApplicationShutdown();
// 			virtual void OnApplicationPaused();
// 			virtual void OnApplicationResumed();
// 			virtual void OnLowMemory();

// 			// Surface
// 			virtual void OnSurfaceChanged( int iFormat, int iWidth, int iHeight );
// 			virtual void OnSurfaceCreated( jobject pSurface );
// 			virtual void OnSurfaceDestroyed();

// 			// Window state
// 			virtual void OnWindowHidden();
// 			virtual void OnWindowShown();

// 			// Input
// 			virtual void OnTouch( int iPointerID, float fPosX, float fPosY, int iAction );
// 			virtual void OnKeyUp( int iKeyCode, int iUnicodeChar );

// //			// Play Services
// //			virtual void OnSignInSucceeded( char* pAccountName );
// //			virtual void OnSignInFailed();

// 			virtual void setAssetManager(jobject pAssetManager);

// //			// Interfaces
// //			virtual IAppStateInterface* GetAppStateInterface();

// 		private:
// 			NativeActivity* m_pActivity;
// 		};

		class AppInterface : public IAppInterface {
		public:
			AppInterface(NativeActivity* pActivity);
			virtual ~AppInterface();

			virtual void PollEvents();
			virtual void SetEventCallback( MessageCallbackFunction pCallback );
			virtual void SetEventHandler( IAndroidHandler* pHandler );

			virtual ANativeWindow* GetWindow();
			virtual AAssetManager* GetAssetManager();
			virtual bool IsWindowVisible();

			virtual void ShowKeyboard();
			virtual void HideKeyboard();

			virtual const char* GetAppDir();

			virtual JNIEnv* GetJNIEnv();
			virtual jobject GetJNIActivity();

			virtual ClassLoader* GetClassLoader();
			virtual NotificationManager* GetNotificationManager();

		private:
			NativeActivity* s_NativeActivity;
		};

		friend class AppInterface;
		friend void SetJNI( JNIEnv* pEnv, jobject pObj);
		void InitAppDir();

	private:
	    AppInterface* mAppInterface;
	};

}

#endif